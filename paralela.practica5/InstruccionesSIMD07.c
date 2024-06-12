#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <immintrin.h>
#include <x86intrin.h>

// Function to perform scalar multiplication using SIMD
void scalar_multiplication_simd(int32_t *array, size_t size, int32_t scalar) {
    // Set the scalar value into each position of a SIMD register
    __m128i vscalar = _mm_set1_epi32(scalar);

    size_t i;
    // Loop over the array in chunks of 4 elements
    for (i = 0; i + 4 <= size; i += 4) {
        // Load 4 integers from the array into a SIMD register
        __m128i va = _mm_loadu_si128((__m128i*)&array[i]);
        // Multiply the loaded values by the scalar
        __m128i vresult = _mm_mullo_epi32(va, vscalar);
        // Store the result back into the array
        _mm_storeu_si128((__m128i*)&array[i], vresult);
    }

    // Handle any remaining elements that don't fit into a SIMD register
    for (; i < size; ++i) {
        array[i] *= scalar;
    }
}

// Function to perform scalar multiplication traditionally
void scalar_multiplication_traditional(int32_t *array, size_t size, int32_t scalar) {
    // Loop over each element and multiply by the scalar
    for (size_t i = 0; i < size; ++i) {
        array[i] *= scalar;
    }
}

// Function to print an array of integers
void print_int_array(int32_t *array, size_t size) {
    printf("[");
    for (size_t i = 0; i < size; ++i) {
        printf("%d", array[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    // Initialize two arrays with the same values
    int32_t array1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int32_t array2[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int32_t scalar = 3;
    size_t size = 8;

    // Print the initial values of the arrays
    printf("\nArray #1: ");
    print_int_array(array1, size);

    printf("\nArray #2: ");
    print_int_array(array2, size);

    // Perform scalar multiplication using SIMD and traditional methods
    scalar_multiplication_simd(array1, size, scalar);
    scalar_multiplication_traditional(array2, size, scalar);

    // Print the results
    printf("\nSIMD Result: \t\t");
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", array1[i]);
    }

    printf("\nTraditional Result: \t");
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", array2[i]);
    }

    return 0;

    // Yes, in this case, the compiler optimized the traditional version of the code. 
    // This means that the compiler applied various optimization techniques to enhance 
    // the performance of the traditional code, making it run more efficiently. 
}
