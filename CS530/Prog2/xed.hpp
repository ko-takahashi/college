/********************************************
Megan Chua and Kosuke Takahashi
cssc0453 and cssc0452
820083726 & 820144293
CS 530 Spring 2019
Assignment #2 XE disassembler
xed.hpp
********************************************/

#ifndef __Prog2__xed
#define __Prog2__xed

#include <stdio.h>
#include "Opcode.hpp"

/**
Class:
    xed
Description:
    Initializes all the function and variables used in xed.cpp
**/
class xed
{
    public:
        void readFile (char *objFile);
        void disassemble();
    private:
        int readInstruc(int row, int current);
        vector<string> objStor;
        vector<string> symStor;
        vector<string> litName; //the literal name
        vector<int> litLength;
        vector<unsigned int> litAddr;
        vector<string> symbol;
        vector<unsigned int> symValue;
        vector<char> symFlag;
        unsigned int progLength;
        unsigned int currentAddr;
        unsigned int baseAddr;
        void format1 (Opcode code, int opcode, int row, int current);
        void format2 (Opcode code, int opcode, int row, int current);
        int format3 (Opcode code, int opcode, int row, int current);
        void header(int row); //the following functions analyze the record to create
        void text(int row); //the object code
        void modify(int row);
        void endObjCode(int row);
        void StorageLoader();
};

#endif