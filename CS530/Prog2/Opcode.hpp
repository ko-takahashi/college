/********************************************
Megan Chua and Kosuke Takahashi
cssc0453 and cssc0452
820083726 & 820144293
CS 530 Spring 2019
Assignment #2 XE disassembler
xed.cpp
********************************************/

#ifndef __Prog2__Opcode
#define __Prog2__Opcode

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

/**
Class:
    Opcode
Description:
    Initializes all the functions and variables used in Opcode.cpp
**/
class Opcode 
{
public:
    string getInstruction(int opCode);
    int getOpcode(int opCode);
    int getFormat(int opCode);
    int bitmasker(int opCode);
};

#endif