/*
    Kosuke Takahashi
    Carroll
    CS570
    cssc0097
    REDID: 820144293
    Due: September 4th, 2019
*/


#include "getword.h"
#include <stdio.h>

/*
    getword() retrieves the next character in the stdin and analyzes it. It will result in either a 0, -1, or the size of the char delimited by spaces, '\n', or and 'EOF'

    NOTES:

    '\0' is a null terminator character that was used in this program to get rid of any excess space being used in the array

    A continue statement is used to loop back through the loop, it is the opposite as a break statement

    ungetc() was used to put a char back onto the input stream to loop back through when getword() is called again (used in the cases of '\n' and 'done')
*/
int getword(char *w) 
{
        int iochar;
        char *c = w;
        int n = 0;
        int donecount = 0;

        /*
            This initial while loop handles any leading spaces in the stdin
        */
        while((iochar = getchar()) == ' ')
        {
            continue;
        }

        while(iochar != EOF)
        {
            /*
                iochar takes the next char in the stdin by using getchar() and it places it into a character array of c[n]
            */
            c[n] = iochar;

            /*
                ' ' case
                Have to ensure that this case returns the appropriate size of 0
            */
            if(c[n] == ' ')
            {
                if(n > 0)
                {
                    c[n] = '\0';
                    return n;
                }
                if(n == 0)
                {
                    c[n] = '\0';
                    return 0;
                }
                c[n] = '\0';
                break;
            }


        /*
            'done' case
            Only catches the word 'done' when it is by itself, not attached to other chars
            Unsure whether to incldue the 'done' test inside or outside the while loop
        */

            if(c[0] == 'd' && c[1] == 'o' && c[2] == 'n' && c[3] == 'e')
            {
                if(((iochar = getchar()) == ' ') || ((iochar = getchar()) == '\n'))
                {
                    return -1;
                } 
                else if((iochar = getchar()) == '\0')
                {
                    return -1;
                }
                else
                {
                    ungetc(iochar, stdin);
                }
            }           

            /*
                '\n' case
                Have to ensure that this case returns the appropriate size of 0
            */
            else if(c[n] == '\n')
            {
                if(c[0] == '\n')
                {
                    c[n] = '\0';
                    return 0;
                }
                if(n == 0)
                {
                    c[n] = '\0';
                    return 0;
                }
                c[n] = iochar;
                ungetc(iochar, stdin);
                c[n] = '\0';
                return n;
            }

            /*
                Normal Legal Char Input
                Loops back through the stdin by incrementing to the next char
            */
            else
            {
                n++;
                iochar = getchar();

            }

        }
    

    /*
        'done' case
        Only catches the word 'done' when it is by itself, not attached to other chars
        Unsure whether to incldue the 'done' test inside or outside the while loop
    */

    /*
    if(c[0] == 'd' && c[1] == 'o' && c[2] == 'n' && c[3] == 'e')
    {
        if(((iochar = getchar()) == ' ') || ((iochar = getchar()) == '\n'))
        {
            return -1;
        } 
        else if((iochar = getchar()) == '\0')
        {

            return -1;
        }
        else
        {
            printf("Nope\n");
            //c[n] = iochar;
            ungetc(iochar, stdin);
            //iochar = getchar();
            //c[n] = iochar;
        }
    }  
    */  


    /*
        Returns the size of the array or '-1' for EOF
    */

    if(n == 0)
    {
        //c[n] = iochar;
        c[n] = '\0';
        return -1;
    }
    else
    {
        return n;
    }
}

