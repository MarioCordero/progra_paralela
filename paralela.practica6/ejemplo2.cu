#include <stdlib.h> 
#include <stdio.h> 
#include <cuda.h> 
#include <math.h> 
#include <time.h> 
#include <curand_kernel.h> 
 
#define TRIALS_PER_THREAD 4096 
#define BLOCKS 256 
#define THREADS 256 
// known value of pi
#define PI 3.1415926535
 
// With "__global__" the function will be called from the host but executed on the GPU, only works for this function
__global__ void gpu_monte_carlo(float *estimate, curandState *states) {

    unsigned int tid = threadIdx.x + blockDim.x * blockIdx.x; 
    int points_in_circle = 0; 
    float x, y; 

    // Initialize CURAND
    // 1234 es la semilla, tid es el id del hilo, 0 es el offset
    curand_init(1234, tid, 0, &states[tid]);

    for(int i = 0; i < TRIALS_PER_THREAD; i++) { 

        // -[x]
        // Generar valores aleatorios uniformes para x, y 
        x = curand_uniform(&states[tid]);
        y = curand_uniform(&states[tid]);

        /*
        
        -curand_uniform:
        This is a function from CURAND (CUDA Random Number Generation library) that 
        generates a uniformly distributed floating-point random number between 0 
        (inclusive) and 1 (exclusive).

        -&states[tid]:
        states is an array of CURAND states. Each thread has its own CURAND state 
        to maintain independent random number sequences. tid is the identifier of 
        the current thread, so &states[tid] accesses the specific state of the current thread.

        */

        points_in_circle += (x*x + y*y <= 1.0f); // count if x & y is in the circle. 
    }

    estimate[tid] = 4.0f * points_in_circle / (float) TRIALS_PER_THREAD; // return estimate of pi 
}
 
float host_monte_carlo(long trials) { 
    float x, y; 
    long points_in_circle = 0; // Inicializar correctamente points_in_circle
    for(long i = 0; i < trials; i++) {
        x = rand() / (float) RAND_MAX; 
        y = rand() / (float) RAND_MAX; 
        points_in_circle += (x*x + y*y <= 1.0f); 
    } 
    return 4.0f * points_in_circle / trials;
} 
 
int main (int argc, char *argv[]) {

    clock_t start, stop; 
    float host[BLOCKS * THREADS]; 
    float *dev; 
    curandState *devStates; 
 
    printf("# of trials per thread = %d, # of blocks = %d, # of threads/block = %d.\n", TRIALS_PER_THREAD, BLOCKS, THREADS); 
 
    start = clock(); 
 
    // -[x]
    // use cudaMalloc para pedir un bloque de memoria de tamaño BLOCKS * THREADS * sizeof(float). Guárdelo en dev. 
    cudaMalloc((void **)&dev, BLOCKS * THREADS * sizeof(float));

    /*
    

    -cudaMalloc:
    A function from the CUDA API used to allocate memory on the GPU (device). It is analogous to the 
    malloc function in C, but in this case, the memory is allocated in the GPU's memory space.

    -**(void )&dev:
    dev is a pointer to a variable that will store the address of the memory allocated on the GPU.
    (void **)&dev casts the pointer &dev to a void** type, which is the type required by cudaMalloc 
    for the first argument. This is because cudaMalloc needs a double pointer (a pointer to a pointer) 
    to store the address of the allocated memory.

    -BLOCKS * THREADS * sizeof(float):

    BLOCKS is the number of execution blocks.
    THREADS is the number of threads per block.
    sizeof(float) returns the size in bytes of a float type.
    BLOCKS * THREADS is the total number of threads that will be launched.
    BLOCKS * THREADS * sizeof(float) calculates the total amount of memory in bytes needed to store a 
    float value for each thread. In this case, enough memory is being allocated to store a float value 
    for each thread in all the blocks.

    */
    
    // -[x]
    // use cudaMalloc para pedir un bloque de memoria de tamaño THREADS * BLOCKS * sizeof(curandState). Será usado para guardar el estado del generador de números aleatorios. Guardelo en devStates. 
    cudaMalloc((void **)&devStates, BLOCKS * THREADS * sizeof(curandState));
    
    gpu_monte_carlo<<<BLOCKS, THREADS>>>(dev, devStates); 

    // Use cudaMemcpy para copiar los datos de dev a host. 
    cudaMemcpy(host, dev, BLOCKS * THREADS * sizeof(float), cudaMemcpyDeviceToHost);

    float pi_gpu = 0; // Inicializar correctamente pi_gpu

    for(int i = 0; i < BLOCKS * THREADS; i++) { 
        pi_gpu += host[i]; 
    } 
 
    pi_gpu /= (BLOCKS * THREADS); 
 
    stop = clock(); 
 
    printf("\nGPU pi calculated in %f s.\n", (stop-start)/(float)CLOCKS_PER_SEC); 
 
    start = clock(); 

    float pi_cpu = host_monte_carlo(BLOCKS * THREADS * TRIALS_PER_THREAD); 

    stop = clock();

    printf("\nCPU pi calculated in %f s.\n", (stop-start)/(float)CLOCKS_PER_SEC); 
 
    printf("\nCUDA estimate of PI = %f [error of %f]\n", pi_gpu, pi_gpu - PI); 

    printf("CPU estimate of PI = %f [error of %f]\n", pi_cpu, pi_cpu - PI); 
  
    // Free memory
    cudaFree(dev);
    cudaFree(devStates);

    return 0; 
}