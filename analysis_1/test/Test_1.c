// RUN: clang -mabi=lp64d -fpass-plugin=`echo ../build/skeleton/SkeletonPass.*` -O0 %s 2>&1 | FileCheck %s
// RUN: rm ./a.out
// RUN: rm -r ./Output

#include <stdio.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Factorial of %d is: %llu\n", num, factorial(num));
    return 0;
}

// CHECK: Basic Block: return
// CHECK: Instructions: 
// CHECK:  %4 = load i64, ptr %retval, align 8
// CHECK:  ret i64 %4
