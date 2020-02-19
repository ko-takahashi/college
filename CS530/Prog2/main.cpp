/********************************************
Megan Chua and Kosuke Takahashi
cssc0453 and cssc0452
820083726 & 820144293
CS 530 Spring 2019
Assignment #2 XE disassembler
main.cpp
********************************************/

#include <vector>
#include "Opcode.hpp"
#include "xed.hpp"

/**
Driver class for Lab 2 
**/
int main(int argc, char **argv) 
{
    
    if (argc != 2)  //error checking if the user inputs incorrect input
    {
        cout << "ERROR: INVALID INPUT" << endl;
        cout << "Enter: ./xed <filename>.obj" << endl;
        return 0;
    }
    else    //use disassembler to output the correct files
    {
        xed *disassembler = new xed;
        disassembler->readFile(*(argv+1));
        disassembler->disassemble();
    }

    return 0;
}