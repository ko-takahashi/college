/***************************************************************
// Kosuke Takahashi
// cssc0452
// CS 530, Spring 2019
// Assignment #3, Parser
// exp.h
***************************************************************/

/**************************************************************
This file is the Header File. This defines the parameters that 
each function takes in and also includes each public variable
that is used
***************************************************************/

#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 128
    
char sentence[SIZE];
int position;
char next;
int count = 0;
bool errorcheck = false;

void id();
void check();
void assign();
void express();
void parenth();
void move();
void printError(char n);
void parenthCheck();
    
#endif