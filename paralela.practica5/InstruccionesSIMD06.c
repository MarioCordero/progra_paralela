#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <immintrin.h>

// Function to find the maximum element in an array using SIMD instructions
int32_t find_max_simd(int32_t *array, size_t size) {
    // Initialize SIMD register with INT32_MIN
    __m128i max_reg = _mm_set1_epi32(INT32_MIN);

    // Process elements in blocks of 128 bits (4 integers of 32 bits)
    for (size_t i = 0; i < size; i += 4) {
        // Load data from the array into a SIMD register
        __m128i data = _mm_load_si128((__m128i*)&array[i]);
        
        // Update SIMD register with the maximum of each element
        max_reg = _mm_max_epi32(max_reg, data);
    }

    // Create an array to store the result from the SIMD register
    int32_t max_elements[4];
    _mm_storeu_si128((__m128i*)max_elements, max_reg);

    // Find the maximum among the elements of the array
    int32_t max = INT32_MIN;
    for (size_t i = 0; i < 4; ++i) {
        if (max_elements[i] > max) {
            max = max_elements[i];
        }
    }

    // Process the remaining elements that couldn't be processed with SIMD
    for (size_t i = size - (size % 4); i < size; ++i) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    return max;
}

// Function to find the maximum element in an array using a traditional loop
int32_t find_max_traditional(int32_t *array, size_t size) {
    int32_t max = INT32_MIN;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

// A function to print arrays
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
    int32_t array[] = {3, 8, -2, 5, 10, -7, 4, 2};
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("\nArray de muestra: ");
    print_int_array(array, size);

    int32_t max_simd = find_max_simd(array, size);
    printf("\nMáximo elemento (SIMD) es: %d\n", max_simd);

    int32_t max_traditional = find_max_traditional(array, size);
    printf("Máximo elemento (tradicional) es: %d\n", max_traditional);

    printf("\n\n");
    return 0;
}
