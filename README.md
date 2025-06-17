## Build Instructions 
Run the command 'make' or 'make main'. This will generate all the binaries, and place them in the bin directory. 
Tried to use makefile since it automates the build process for the executable. If make does 
not work then run "g++ -I. -std=c++2a -c [REPLACE THIS FOR EACH SOURCE FILE]". 
Next, run "g++ -o main [REPLACE THIS WITH ALL BINARIES GENERATES]" which will generate the main executable. 

## Run Instructions
After building all the binaries there will be an executable named 'main' in the bin directory. Just run 
the executable, and follow any instructions that is requested. 
"./TOP_LEVEL/main [PATH TO CSV FILE]" is normally how I've been running the executable. The CVS file is located in ./scitec_files/  

example:
./bin/main ./scitec_files/SciTec_code_problem_data.csv 

## Clean Build Process
To clean all the binaries that have been generated and placed in bin directory just run the command 'make clean'

example:
make clean

## G++ Standard Version 
The version 20 for g++ library is being using the compile. This allows for using some keywords (not all) 
for some of the source files. Therefore, version 20 might not be needed but using it just in case. 

## G++ Debug 
The debug '-g' is used for each binary that have been generated. Can be removed by editing the Makefile. 
Only reason for debug symbols being added is for developer use only. However, feel free to run gdb command on the 
executable if you want. 

## DEBUG
Some of the source files have the DEBUG macro that allows for additions logging to be printed and etc...
To turn on this DEBUG just go into the Makefile and change DDEBUG=0 to DDEBUG=1. 

## TODOs 
If there are some todos in the code then that is just me thinking about possible ways of improving the code. However,
do to time constraint I was not able to implement those ideas.

