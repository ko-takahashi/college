#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "exp.h"
        
/*checks for proper grammer within id clause*/
void id() 
{
    if (isalpha(next)) //check if next char is in alphabet
    {  
        scan();
        while (isalpha(next) || isdigit(next))
        {
            scan();  
        }
        check();
        
    } 
    else error(1); //id error
}

void check ()
{
    if(n == 0)
    {
        if (next == '=') //check for the equal sign
        {
            scan();    
            n++;
            assign();
            
        }
        else if (next == '+' || next == '-' || next == '*' || next == '/' || next == '%')
        {
            n++;
            expression();
        }
    } 
    n++;   
}
    
/*checks for proper grammer within assign clause*/
void assign() 
{
    if (next == '=')
    {
        error('=');
    }
    expression();
    if (next == ';') 
    {
        scan();
    }
    else error (';');
}
    

/*checks for proper grammer within exp clause*/
void expression() 
{
    scan();
    //printf("Hi megan: %c", next);
    if (next == '(')
    {    
        //printf("HEREEEE: %c", next);
        parenth();  
    }  
    id();
    if (next == '=')
    {
        error('=');
    }
    if (next == NULL || next == ';')
    {
        return;
    }
    while (next == '+' || next == '-' || next == '*' || next == '/' || next == '%')
    {
        scan();
        if (next == '(')
        {    
            parenth(); 
            if (next == ';')
                return;
            else if(next == '+' || next == '-' || next == '*' || next == '/' || next == '%')
            {
                scan();
                if (next == '=')
                {
                    error('=');
                }            
            } 
        }  
        id();
        if (next == '=')
        {
            error('=');
        }
    }
    if (next == '+' || next == '-' || next == '*' || next == '/' || next == '%') //checks for duplicates
    {
        error (2);
    }    
    
}
    
/*checks for proper grammer within 'parenth' clause*/
void parenth() 
{
    //printf("Parenth NEXT: %c", next);
    if (isalpha(next) || isdigit(next))
    {
        scan();
    }
    else if (next == '(') 
    {
        //scan();
        expression();
        if (next == ')')
        {
            scan();
        }
        else error(')');
    }
    else error(2);
}
    
/*scans for the next non-whitespace character*/
void scan() 
{
    while (isspace(next = sentence[position++]));
}
    
/*prints error, with a brief description*/
void error(char n) 
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
    for (i=0; i<position-1; i++) //put spaces up to position where error occured
    {  
        printf(" ");
    }
    printf("^error here\n");    //the '^' symbol will point to where error occured
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
    
/*checks for matching left/right parenthesis*/
void checkParenthesis() 
{
    int i=0, left=0, right=0;
    for (i; i < MAX_INPUT; i++) 
    {
       if (sentence[i] == '(') 
       {
            left++;
       }
       else if (sentence[i] == ')') right++;
       else if (sentence[i] == (char)NULL) break;
    }
       if (left < right) 
       {
            error(3);
       }       

       else if (left > right) 
       {
            error(4);
       }
}

int main(int argc, char* argv[]) 
{
    
    
    if (argc == 1)
    {
        position = 0;
        scanf("%[^\n]s", sentence);
        checkParenthesis();
        scan();
        id();
        if (errorcheck == false)
        {
            printf("Successful parse\n");
        }
        
        
    }

    else if (strcmp(argv[1], "ex.txt") == 0)
    {
        FILE *file;
        file = fopen("ex.txt", "r");
        while (fgets(sentence, sizeof sentence, file) != NULL)
        {
            position = 0;
            n = 0;
            fputs(sentence, stdout);
            checkParenthesis();
            scan();
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