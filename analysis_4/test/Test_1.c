// RUN: clang -mabi=lp64d -fpass-plugin=`echo ../build/skeleton/SkeletonPass.*` -O0 %s 2>&1 | FileCheck %s
// RUN: rm ./a.out
// RUN: rm -r ./Output

int g[2][2];

int main() {
    int a[5][10];
    a[4][9] = 2;
    g[0][1] = 5;
    g[0][0] = g[0][1];
    int b = g[0][0];
}

// CHECK: store double 2.000000e+00, ptr %arrayidx1, align 8
