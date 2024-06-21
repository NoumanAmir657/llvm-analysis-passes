// RUN: clang -mabi=lp64d -fpass-plugin=`echo ../build/skeleton/SkeletonPass.*` -O0 %s 2>&1 | FileCheck %s
// RUN: rm ./a.out
// RUN: rm -r ./Output

int gVal = 10;

int main() {
    double a[5][10];

    a[4][9] = 2;
}

// CHECK: store	1
// CHECK: ret	1
// CHECK: getelementptr	2
// CHECK: alloca	1
