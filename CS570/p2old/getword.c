/*
    Kosuke Takahashi
    Carroll
    CS570
    cssc0097
    REDID: 820144293
    October 9th, 2019
    getword.c
*/

#include "getword.h"
#include <stdio.h>

/*
    getword() retrieves the next character in the stdin and analyzes it. Depending on what the character is, getword() treat it differently. There are specific cases that had to be dealt with in getword(). These include leading spaces, metacharacters, backslashes, normal spaces, new lines, large inputs, and if the input is 'done'.
    
    NOTES:
    '\0' is a null terminator character that was used in this program to get rid of any excess space
    being used in the array
    A continue statement is used to loop back through the loop, it is the opposite as a break statement
    ungetc() was used to put a char back onto the input stream to loop back through when getword()
    is called again. The ungetc() function pushes the char back which allows for the following character to be read.
    The variable, initchar, is used in the code when getword() handles metacharacters. It is supposed to represent the initial char, or the char before iochar (if there is one).
    getchar() was used to help increment to the next character in the input
*/

int getword(char *w)
{
    int iochar;
    int initchar;
    int backslash = 0;
    char *c = w;
    int n = 0;
    while((iochar = getchar()) != EOF)
    {
        c[n] = iochar;

        /*
            'leading spaces' case
            Just moves onto the next char if there is a space in the beginning. Leading spaces are merely ignored in getword()
        */
        if (c[0] == ' ')
            continue;
        
        /*
            metacharacter case
            The metacharacters are '<', '>', '>&', '>>', '>>&', '|', '#', and '&'.
            If the metacharacters are does not include a '>', the processing is simpler.
            If the metacharacter does start with a '>', getword() process is "greedy" so there had to be a distinction between '>', '>&', '>>', and '>>&' as there is a hierarchy.
        */
        if(iochar == '<' || iochar == '|' || iochar == '#' || iochar == '&')
        {            
            if(n == 0)
            {
                c[n] = iochar;
                c[n+1] = '\0';
                return 1;
            }
            /* Without pushing the char back, the next char that is read will not be the actual next char. That char would be skipped. That is why we need ungetc(). */
            ungetc(iochar, stdin);
            c[n+1] = '\0';
            break;
        }
        initchar = iochar;
        if(iochar == '>')
        {
            iochar = getchar();
            if(iochar == '>')
            {
                if(iochar == '&')
                {
                    ungetc(iochar, stdin);
                    c[n] = initchar;
                    c[n+1] = initchar;
                    c[n+2] = iochar;
                    iochar = getchar();
                    return 3;
                }
                else
                {
                    ungetc(iochar, stdin);
                    c[n] = initchar;
                    c[n+1] = iochar;
                    return 2;
                }
            }
            else if(iochar == '&')
            {
                ungetc(iochar, stdin);
                c[n] = initchar;
                c[n+1] = iochar;
                c[n+2] = '\0';
                iochar = getchar();
                return 2;
            }
            else
            {   
                c[n] = initchar;
                c[n+1] = iochar;
                return 1;
            }
        }

        /*
            '\' case
            When '\' precedes a metacharacter, the metacharacter will be treated like a normal char
            Backslashes have a distinct rule in getword(). After a '\', the next character is treated normally. This makes '\' act similarly to a space. but it is different as it needs to combine characters in cases where it normally would not.
        */
        if(iochar == '\\')
        {
            backslash++;
            c[n] = iochar;
            iochar = getchar();
            if(iochar == '\n')
            {
                c[n] = '\0';
                ungetc(iochar, stdin);
                return n;
            }
            if(iochar == ' ' || iochar == '<' || iochar == '>' || iochar == '|' || iochar == '#' || iochar == '&')
            {
                c[n] = iochar;
                n++;
                c[n] = '\0';
                
                if((iochar = getchar()) == '<' || iochar == '>' || iochar == '|' || iochar == '#' || iochar == '&')
                {
                    ungetc(iochar, stdin);
                    break;
                }
                else
                {
                    ungetc(iochar, stdin);
                    continue;
                }
                
                if(n > 1)
                    continue; 
                else
                    break;
            }
            else
            {
                c[n] = iochar;
                n++;
            }
            c[n] = '\0';
            continue;
        }

        /*
            ' ' case
            Sets the space to NULL as is it unimportant to the output of getchar(). This acts as a parser as it splits the input by spaces.
        */
        if(iochar == ' ')
        {
            c[n] = '\0';
            break; 
            if(n == 0)
            {
                c[n] = '\0';
                return 0;
            }   
        }
        
        /*
            '\n' case
            Initially checks for an initial '\n' as the conditions for an initial '\n' is treated slightly differently, similarly to leading spaces. Then it deals with '\n' throughout the input. 
            The ungetc(iochar, stdin) was used in this case to ensure that the char that occurs after the '\n' gets registered into the array.
        */
        if(iochar == '\n' && n == 0)
        {
            c[n] = '\0';
            return 0;       
        }
        else if(iochar == '\n' || iochar == '>')
        {
            c[n] = '\0';
            ungetc(iochar, stdin);
            break;
        }

        /*
            'Normal Legal Char' case
            Loops back through the stdin by incrementing to the next char
        */
        n++;

        /*
            Large input case
            This set of code specifically handles inputs that are too large for the call getword() to process in one call. If the input size is larger then STORAGE-1, getword() must be called again separately to run the rest of the input.
        */
        if(n >= STORAGE-1)
            break;
    }

    /*
        'done' case
        This checks for the string 'done' by going through the created array, char by char.
        The condition of "c[4] == '\0' || feof(stdin)" was used to ensure that the input only read done without anything before or after it, except for a backslash
    */
    if(c[0] == 'd' && c[1] == 'o' && c[2] == 'n' && c[3] == 'e' && (c[4] == '\0' || feof(stdin)))
    {
        c[n] = '\0';
        ungetc(iochar,stdin);
        return -1;
    }

    /*
        This portion of the code deals with returning the proper output of n when getword() is called in the driver
        When the output is EOF or "done", the output returns a -1
        When the output is anything else, it returns the size of that specific character that is bring processed
    */
    if(n == 0)
    {
        c[n] = '\0';
        return -1; 
    }
    else if(n > 0)
    {
        c[n] = '\0';
        return n;
    }
    return -1;
}