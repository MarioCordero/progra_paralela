#include <stdio.h>
#include <immintrin.h>
#include <stdint.h>
/*

The function `_mm_hadd_epi32` performs a horizontal sum of the 
elements in a register of type `__m128i`, adding pairs of adjacent 
elements. For example, if we have a register with values a, b, c, d, 
the horizontal sum would be a+b, c+d.

*/

// Function to sum all elements of an array using SIMD
int32_t sum_array(int32_t *array, size_t size) {
    __m128i sum = _mm_setzero_si128(); // Initialize a SSE sum register to zero

    // Sum elements in groups of 4
    for (size_t i = 0; i < size - 3; i += 4) {
        // Load 4 elements at once
        __m128i va = _mm_loadu_si128((__m128i*)(array + i)); 
        // Add to the sum register
        sum = _mm_add_epi32(sum, va); 
    }

    // Horizontal sum of the elements in the sum register
    sum = _mm_hadd_epi32(sum, sum);
    sum = _mm_hadd_epi32(sum, sum);

    // Extract the total sum from the sum register
    int32_t total_sum = _mm_extract_epi32(sum, 0);

    // Add the remaining elements that couldn't be processed with SIMD
    for (size_t i = size - (size % 4); i < size; ++i) {
        total_sum += array[i];
    }

    return total_sum;
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
    int32_t a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = 10;

    printf("Array ejemplo:");
    print_int_array(a,size);
    
    int32_t sum = sum_array(a, size);
    
    printf("Total sum: %d\n", sum);
    return 0;
}
