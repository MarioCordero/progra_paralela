#include <stdio.h>
#include <stdint.h>
#include <immintrin.h>
#include <x86intrin.h>

int main(int argc, char *argv[]) {

    // Align the data to 16 bytes
    int32_t a[4] __attribute__((aligned(16))) = {1, 2, 3, 4};
    int32_t b[4] __attribute__((aligned(16))) = {5, 6, 7, 8};
    int32_t result[4] __attribute__((aligned(16)));

    // Load data into SIMD registers from aligned memory
    __m128i va = _mm_load_si128((__m128i*)a);
    __m128i vb = _mm_load_si128((__m128i*)b);

    // Add the vectors
    __m128i vresult = _mm_add_epi32(va, vb);

    // Store the data from the SIMD register to aligned memory
    _mm_store_si128((__m128i*)result, vresult);

    // Print the result
    printf("\n");
    printf("Resultado: [");
    for (size_t i = 0; i < 4; i++) {
        printf("%d", result[i]);
        if (i != 3) {
            printf(",");
        }
    }
    printf("]");
    printf("\n\n");

    return 0;
}