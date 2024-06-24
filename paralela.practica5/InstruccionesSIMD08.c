#include <stdio.h>
void add_vectors(int *a, int *b, int *result, int n) { 
    for (int i = 0; i < n; i++) { 
        result[i] = a[i] + b[i]; 
    } 
} 
 
int main() { 
    int a[4] = {1, 2, 3, 4}; 
    int b[4] = {5, 6, 7, 8}; 
    int result[4]; 
 
    add_vectors(a, b, result, 4); 
 
    for (int i = 0; i < 4; i++) { 
        printf("%d ", result[i]); 
    } 
    return 0; 
}

/*

1) In the optimized version, there's an additional push %r12 instruction before push %rbp.

2) The -O3 optimization flag allows the compiler to apply more aggressive optimization strategies, 
such as loop vectorization, which can lead to changes in the structure of the generated code.

3) The presence of specific optimization flags like -ftree-vectorize and -fopt-info-vec-optimized 
suggests that the compiler is applying vectorization optimizations, which might significantly 
change the assembly code structure, especially within loops.

*/