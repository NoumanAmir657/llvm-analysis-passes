// RUN: clang -mabi=lp64d -fpass-plugin=`echo ../build/skeleton/SkeletonPass.*` -O0 %s 2>&1 | FileCheck %s
// RUN: rm ./a.out
// RUN: rm -r ./Output

int main() {
    double a[5][10];

    a[4][9] = 2;
}

// CHECK: Allocas   %a = alloca [5 x [10 x double]], align 8
// CHECK: Size: 400 bytes
