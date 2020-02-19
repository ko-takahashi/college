#include "getword.h"

int getword (char * w)
{
    int iochar; //variable that handles what is in getchar()
    int count = 0; //keeps track of the number of characters in the string
    char * word = w; //pointer to the character array
    int meta = 0; //keeps track of how many '>' characters are encountered
    int backslash = 0;   
    while ((iochar = getchar())!= EOF)
    {
        if (iochar == '\\') //this is what initially checks for a '\' character
        {
            backslash++;
            word[count] = iochar;
            iochar = getchar();
            if (iochar == '\n')
            {
                ungetc(iochar,stdin);
                word[count] = '\0';
                return count;
            }
            if (iochar == '<' || iochar == '>' || iochar == '|' || iochar == '#' || iochar == '&' || iochar == ' ')
            {
                word[count] = iochar;
                count++;
                word[count] = '\0';
                iochar = getchar();
                if (iochar == '<' || iochar == '>' || iochar == '|' || iochar == '#' || iochar == '&')
                {
                    ungetc(iochar,stdin);
                    break;
                }
                else
                {
                    ungetc(iochar,stdin);
                    continue;
                }
            }
            else
            {
                word[count] = iochar;
                count++;
            }
            word[count] = '\0';
            continue;
        }
        word[count] = iochar; //push iochar into the pointer array
        if (count == 254) 
        {
            word[count] = '\0';
            ungetc (iochar,stdin);
            break;
        }
        if (word[0] == ' ') //if space encountered at beginning, continue
        {
            continue;
        }
        if (count == 0 && iochar == '\n')
        {
            word[count] = '\0';
            return 0;
        }     
        if (meta == 1)
        {
            meta = 0; //set counter for meta back to 0
            if (word[1] == '>')
            { 
                count++;
                word[2] = getchar();
                if(word[2] ==  '&') //checks for >>&
                {
                    word[count+1] = '\0';
                    return 3;
                }
                else //checks for >>
                {
                    ungetc(word[2],stdin);
                    word[count] = '\0';
                    return 2;
                }
            }
            if (word[1] == '&') //checks for >&
            {
                word[count+1] = '\0';
                return 2;
            }
            ungetc (iochar,stdin); //else, checks for just >
            word[count] = '\0';
            return count;
        }
        if (word[0] == '>' && backslash == 0) //checks for greater than
        {
            meta = 1; 
            word[0] = iochar;
            count++;
            continue;
        }
        if ((word[0] == '<' || word[0] == '|' || word[0] == '#' || word[0] == '&') && backslash == 0) //checks for all other metacharacters that occur
        {
            word[count] = iochar;
            word[count+1] = '\0';
            return 1;
        }
        if (iochar == ' ') //break at every space
        {
            word[count] = '\0';
            break;
        }
        if (iochar == '<' || iochar == '|' || iochar == '#' || iochar == '&') //checks for the metacharacters that occur at any point in iochar to
        {
            ungetc(iochar,stdin);
            word[count+1] = '\0';
            break;
        }
        if (iochar == '\n' || iochar == '>') 
        {
            word[count] = '\0';
            ungetc (iochar, stdin);
            break;
        }
        count++; 
    } //end of while loop
    if (word[0] == 'd' && word[1] == 'o' && word[2] == 'n' && word[3] == 'e' && (feof(stdin) || word[4] == '\0')) //if the pointer encounters done with
    {
        word[count] = '\0';
        ungetc (iochar, stdin);
        return -1;
    }
    if (count > 0)
    {
        word[count] = '\0';
        return count;
    }
    else
    {
        word[count] = '\0';
    }
    return -1;
}