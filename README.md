# Analyses Passes for LLVM-IR

## Passes
1. Print instructions of IR
2. Count the number of load and store instructions in each function
3. Count the number of each instruction present in a program
4. Identify and print the load and store instructions that access stack memory
5. Total amount of memory allocated by each alloca instruction in bytes

## Structure
Place the test and check files in `Test` directory

## Run
Each pass can be executed using `make`.

`in` -- input file on which pass is to be run on

`out` -- output of pass is saved in a `txt` file to analyze whether output is correct or not
```
make all in=<input_file> out=<output_file>
```

Each output can be tested using the command:

`chk` -- checks file in the format of FileCheck
```
make check chk=<checks_file> out=<output_file>
```

## Tutorial
```
cd analysis_5
make in=Test_1.c out=Output_1.txt
make chk=Check_1.txt out=Output_1.txt
```