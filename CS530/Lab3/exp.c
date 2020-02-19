/***************************************************************
// Kosuke Takahashi
// cssc0452
// CS 530, Spring 2019
// Assignment #3, Parser
// exp.c
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "exp.h"
        
/***************************************************************
id():
Checks the proper grammar for the ID grammar rules. This
function is the base function for the other assign() and
express() functions.
id :== <char> <digit> | <id> <char> | <id> <digit>
****************************************************************/
void id() 
{
    if (isalpha(next))
    //id has to begin with an alphabetical character
    {  
        move();
        while (isalpha(next) || isdigit(next))
        {
            move();  
        }
        check();
        
    } 
    else printError(1);
    //id error
}

/***************************************************************
check(): 
The function that is called at the end of id(). This function
checks to see whether the input is an assignment or an 
expression. This will only need to be used once per input line.
****************************************************************/
void check()
{
    //This function will only be needed once per input line
    //Because once it determines whether to go to assign() or express(),
    //it will not need to determin that again for that input line
    if(count == 0)
    {
        if (next == '=')
        {
            //assignments includes an = sign
            move();    
            count++;
            assign();
            
        }
        else if (next == '+' || next == '-' || next == '*' || next == '/' || next == '%')
        {
            //expressions include operators
            count++;
            express();
        }
    } 
    count++;   
}

/***************************************************************
assign(): 
Checks the proper grammar for the ASSIGNMENT grammar rules.
assign :== <id> = <express>;
****************************************************************/
void assign() 
{
    if (next == '=')
    {
        printError('=');
        //too many = signs in the input
    }
    express();
    if (next == ';')
    //assignments must end with a ; 
    {
        move();
    }
    else printError (';');
    //assignment error
}
    
/***************************************************************
express():
Checks the proper grammar for the ASSIGNMENT grammar rules.
exp :== <id> <op> <id> | {(<id> <op> <id>)}
****************************************************************/
void express() 
{
    move();
    if (next == '(')
    //checking for parenthesis
    {    
        parenth();  
    }  
    id();
    if (next == '=')
    {
        printError('=');
    }
    if (next == NULL || next == ';')
    {
        return;
    }
    while (next == '+' || next == '-' || next == '*' || next == '/' || next == '%')
    //expressions must have operators in between id's
    {
        move();
        if (next == '(')
        {    
            parenth(); 
            if (next == ';')
                return;
            else if(next == '+' || next == '-' || next == '*' || next == '/' || next == '%')
            {
                move();
                if (next == '=')
                {
                    printError('=');
                }            
            } 
        }  
        id();
        if (next == '=')
        {
            printError('=');
        }
    }
    if (next == '+' || next == '-' || next == '*' || next == '/' || next == '%') //checks for duplicates
    {
        printError (2);
        //too many operators
    }    
    
}

/***************************************************************
parenth(): 
Checks for the proper parenthesis grammar. 
****************************************************************/
void parenth() 
{
    if (isalpha(next) || isdigit(next))
    //proper parenthesis grammar
    {
        move();
    }
    else if (next == '(' && sentence[position++] != ' ') 
    //if there is a space after a parenthesis, that is an error
    {
        express();

        if (next == ')')
        {
            move();
        }
        else printError(')');
        //insufficient ending parenthesis
    }
    else printError(2);
    //parenthesis error
}

/***************************************************************
move():
Moves next to the next possible non-whitespace character in the
input
****************************************************************/  
void move() 
{
    while (isspace(next = sentence[position++]));
}
    
/***************************************************************
printError(char n): 
Prints out the proper error message for each possible grammar
error. It also explains what the error is and in some cases
points to where the error is located. 
****************************************************************/
void printError(char n) 
{
    if (n == 1) 
    {
        printf("*** ERROR: Not a valid identifier.\n");
        errorcheck = true;
        return;
        
    }
    else if (n == 2) 
    {
        printf("*** ERROR: Not a valid expression.\n");
        errorcheck = true;
        return;
    }
    int i;
    for (i=0; i<position-1; i++) 
    {  
        printf(" ");
        //this locates the proper error to points to 
    }
    printf("^error here\n");
    if (n == 3) 
    {
        printf("*** ERROR: Too many )'s\n");
        errorcheck = true;
        return;
    }
    else if (n == 4) 
    {
        printf("*** ERROR: Too many ('s\n");
        errorcheck = true;
        return;
    }
    else 
    {
        printf("*** ERROR: '%c' this is an invalid entry. \n", n);
        errorcheck = true;
        return;
    }
}

/***************************************************************
parenthCheck():
Check if each left parenthesis has a matching right parenthesis
to pair together. 
****************************************************************/
void parenthCheck() 
{
    int i=0, left=0, right=0;
    for (i; i < SIZE; i++) 
    {
        
        if (sentence[i] == '(') 
        {
            left++;
        }
        else if (sentence[i] == ')') 
            right++;
        else if (sentence[i] == (char)NULL)
            break;
    }
        if (left < right) 
        {
            printError(3);
        }       

        else if (left > right) 
        {
            printError(4);
        }
}

/***************************************************************
main(int argc, char* argv[]): 
This is the main method that differentiates whether the input is
standard input or a file and runs the proper process to deal
with both situations
****************************************************************/
int main(int argc, char* argv[]) 
{
    
    
    if (argc == 1)
    {
        position = 0;
        scanf("%[^\n]s", sentence);
        parenthCheck();
        move();
        id();
        if (errorcheck == false)
        {
            printf("Successful parse\n");
        }
        
        
    }

    else if (strcmp(argv[1], "ex.txt") == 0)
    //checks if the input is ex.txt
    {
        FILE *file;
        file = fopen("ex.txt", "r");
        while (fgets(sentence, sizeof sentence, file) != NULL)
        {
            position = 0;
            count = 0;
            fputs(sentence, stdout);
            parenthCheck();
            move();
            id();
            if (errorcheck == false)
            {   
               printf("Successful parse\n");
            }
        }
        fclose(file);
    }
    
    return 0;
    
}