Build:

    $ cd llvm-pass-skeleton
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang -fpass-plugin=`echo ../build/skeleton/SkeletonPass.*` -O0 <input_file>
    
Test:

    $ llvm-lit test
