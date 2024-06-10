#include <stdio.h>
#include <stdint.h>
#include <immintrin.h>
#include <x86intrin.h>

// Calculate dot_product
int32_t dot_product(int32_t *a, int32_t *b, int size) {
    
    // Initialize the variable in 0
    __m128i localResult = _mm_setzero_si128();

    // We are working on 4 bytes elements, do, we have to iterate in 4 bytes in each cycle
    for (int i = 0; i < size; i += 4) {

        // Load each element of each vector
        __m128i vectorA = _mm_loadu_si128((__m128i*)&a[i]);
        __m128i vectorB = _mm_loadu_si128((__m128i*)&b[i]);

        // Multiply each element
        __m128i product = _mm_mullo_epi32(vectorA, vectorB);

        // Sum the result
        localResult = _mm_add_epi32(localResult, product);
    }

    // Extract the elements from the SIMD result
    int32_t resultArray[4];
    _mm_storeu_si128((__m128i*)resultArray, localResult);

    // Reduce the elements to obtain the final result
    int32_t finalResult = resultArray[0] + resultArray[1] + resultArray[2] + resultArray[3];

    return finalResult;
}

int main(int argc, char *argv[]) {

    int32_t a[4] = {1, 2, 3, 4};
    int32_t b[4] = {5, 6, 7, 8};

    printf("\n");
    //Size of the array in bytes / size of the element in bytes to calculate correctly the number of elements of the array
    int size = sizeof(a) / sizeof(a[0]);

    // Calculate dot product
    int32_t result = dot_product(a, b, size);

    // Print result
    printf("Producto punto: %d\n", result);

    printf("\n\n");
    return 0;
}