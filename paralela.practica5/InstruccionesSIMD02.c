#include <stdio.h>
#include <stdint.h>
#include <immintrin.h>
#include <x86intrin.h>

int main(int argc, char *argv[]) {

    int32_t a[4] = {1, 2, 3, 4};
    int32_t b[4] = {5, 6, 7, 8};
    int32_t result[4];

    
    // __m128i es el tipo de dato de un registro SIMD de 128 bits que contiene enteros de 32 bits.
    // _mm_loadu_si128 se utiliza para cargar datos de 128 bits desde direcciones de memoria no alineadas en registros SIMD.
    // _mm_sub_epi32 es un intrínseco SIMD de Intel diseñado para realizar la resta de dos registros SIMD que contienen enteros de 32 bits.
    // _mm_storeu_si128 se utiliza para almacenar los datos de los registros SIMD en direcciones de memoria no alineadas.

    // Load 2 doubles from memory, using an pointer to a __m128i data
    //Vector a
    __m128i va = _mm_loadu_si128( (__m128i*)a );
    //Vector b
    __m128i vb = _mm_loadu_si128((__m128i*)b);
    //Vector resultant
    __m128i vresult = _mm_sub_epi32(va, vb);

    // Store 2 doubles to memory
    _mm_storeu_si128( (__m128i*) result, vresult);

    printf("\n");
    printf("Resultado: [");
    for (size_t i = 0; i < 4; i++) {
        
        printf("%d", result[i]);

        if(i!=3){
            printf(",");
        }
        
    }
    printf("]");
    printf("\n\n");
    return 0;
}