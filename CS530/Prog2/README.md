/**************************************************************
Megan Chua & Ko Takahashi 
cssc0453 & cssc0452
820083726 & 820144293
CS 530 Spring 2019
Assignment #2 XED Disassembler
README.txt
***************************************************************/

File Manifest:
    xed.cpp
    xed.hpp
    Opcode.cpp
    Opcode.hpp
    main.cpp
    Makefile
    testfile1.obj
    testfile1.sym
    testfile2.obj
    testfile2.sym

Compile Instructions:
    To perform the disassembly, input "xed <filename>.obj" into the command line argument. 
    The program will need to open both a .obj and .sym file in order to compile.
    We will need to compile the hexdump.c file while creating an operator file named "xed":
        gcc xed.cpp -o xed
    Once we have created the xed operator file we can run the whole program:
        ./xed <filename>.obj

Operating Instructions:
    Command line arguments: "./xed <filename>.obj" 
    Required inputs: N/A
    All the information that will be needed to run our program will be in the command line   
    arguments.

Novel/Significant Design Decisions:
    The program is programmed in C++.
    We decided to code most of the disassembler in the class xed.cpp and have it call on 
    another class to obtain the opcode instruction information.The main class calls on the
    disassembler function to perform the tasks required.

Extra features/algorthms/functionality included but not required:
    We utilize vectors and streams to store our file information. We also added some error
    checking.

Known deficiencies/bugs:
    In the output of our .sic and .lis files, some of our spacing is off. This program
    could probably be more efficient because we allocate a lot of memory.

Lessons Learned:
    We learned the process of changing object code to its corresponding opcode & sic 
    instructions.
    We consulted with another team on how to create a Makefile and now we understand how 
    to create the compiler in the Makefile.
    We learned how to use structs in C++.
