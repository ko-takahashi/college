#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_INPUT 128
    
char sentence[MAX_INPUT];
int position;
char next;
int n = 0;
bool errorcheck = false;

void id();
void check();
void assign();
void expression();
void parenth();
void scan();
void error(char n);
void checkParenthesis();
    
#endif