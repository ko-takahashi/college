/*
    Kosuke Takahashi
    Carroll
    CS570
    cssc0097
    REDID: 820144293
    October 9th, 2019
    p2.c
*/

#include "p2.h"

/*
    p2.c is a simple command line interpreter.
    This interpreter can handle 'cd', '!!', redirection, running a script, and backgrounding.
    Using my getword.c code, it parses the stdin in the parse() function.
    Then in main, it processes the newArgv and the execute() function handles redirection.
*/
int main(int argc, char* argv[])
{
    setpgid(0,getpid());
    signal(SIGTERM, sigHandler);

    if(argc > 0)
    {
        if((cla = open(argv[1], O_RDONLY)) != -1)
        {
            dup2(cla, STDIN_FILENO);
            close(cla);
        }
    }
    while(1)
    {
        size = newArgvSize = ampFlag = backgroundFlag = inputFlag = outputFlag = fileIndicator = 0;

        //prompts for input using the string '%1%' in front of the line
        //when there is an error message, perror or fprintf(strd,""), the line does not prompt for '%1%'
        if(promptFlag == 1)
            printf("%%1%% ");
        else
            promptFlag = 0;
        if(parse() == -1)
            break;
        if(newArgvSize == 0)
            continue;
        if((inputFlag == 1 || outputFlag == 1 || outerrFlag == 1) && newArgvSize <= 2)
        {
            fprintf(stderr, "p2: redirection error, not enough arguments\n");
            promptFlag = 0;
            continue;
        }
        //deals with 'cd' cases
        if(newArgv[0] != NULL && (strcmp(newArgv[0], "cd") == 0))
        {
            //if there are no arguments, cd goes back to 'HOME' directory
            if(newArgvSize == 2)
            {
                if(chdir(getenv("HOME")) == -1)
                {
                    perror("p2: home directory not found\n");
                    promptFlag = 0;
                    break;
                }
                continue;
            }
            //if there are arguments, cd goes to the newArgv[1] directory
            if(newArgvSize >= 3)
            {
                if(newArgvSize >= 4)
                {
                    fprintf(stderr, "p2: too many arguments\n");
                    promptFlag = 0;
                    continue;
                }
                if(chdir(newArgv[1]) == -1)
                {
                    perror("p2: child directory not found\n");
                    promptFlag = 0;
                    continue;
                }
                continue;
            }
        }
        //fflush acts as a clear function that clears the stdin and stderr
        //This avoids unintentional repeats
        fflush(stdin);
        fflush(stderr);
        execute();
    }
    //kills the signal and terminates the command line
    killpg(getpgrp(), SIGTERM);
    printf("p2 terminated.\n");
    exit(0);
}

/*
    NOTES:
    O_CREAT, O_EXCL, O_WRONLY, O_RDONLY are file access modes given in the open() function
    S_IRUSR, S_IWUSR are permission bits given from sys/stat.h
    These modes help open the file and give certain permissions to them
    Child process should strictly use _exit() instead of just exit()
*/
void execute()
{
    if((childPid = fork()) == 0)
    {
        //in each redirection case, the fileIndicator will attempt to open the apporporiate file and duplicate it

        //> redirection
        if(outputFlag == 1)
        {
            if((fileIndicator = open(outputFile, O_CREAT | O_EXCL| O_WRONLY, S_IRUSR | S_IWUSR)) == -1)
            {
                perror("p2: failed to open output file\n");
                _exit(-1);
            }
            if(dup2(fileIndicator, STDOUT_FILENO) == -1)
            {
                perror("p2: cannot redirection\n");
                _exit(-1);
            }
            close(fileIndicator);
        }
        //< redirection
        if(inputFlag == 1)
        {
            if((fileIndicator = open(outputFile, O_RDONLY)) == -1)
            {
                perror("p2: failed to open file\n");
                _exit(-1);
            }
            if(dup2(fileIndicator, STDIN_FILENO) == -1)
            {
                perror("p2: unable to redirect\n");
                _exit(-1);
            }
            close(fileIndicator);
        }
        //>& redirection
        if(outerrFlag == 1)
        {
            if((fileIndicator = open(outputFile, O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IWUSR)) == -1)
            {
                perror("p2: failure to open output file\n");
                _exit(-1);
            }
            if((dup2(fileIndicator, STDOUT_FILENO) == -1) || (dup2(fileIndicator, STDERR_FILENO) == -1))
            {
                perror("p2: cannot redirect\n");
                _exit(-1);
            }
            close(fileIndicator);
        }
        //makes sure that the backgrounding does not go over its scope
        if (inputFile == NULL && backgroundFlag == 1)
        {
            if((fileIndicator = open("/dev/null", O_RDONLY)) == -1)
            {
                perror("p2: failed to open\n");
                _exit(-1);
            }
            if(dup2(fileIndicator, STDIN_FILENO) == -1)
            {
                perror("p2: unable to redirect\n");
                _exit(-1);
            }
        }
        execvp(newArgv[0], newArgv);
        fprintf(stderr, "%s: command cannot execute\n", newArgv[0]);
        _exit(-1);
    }
    else if(childPid == -1)
    {
        perror("p2: fork failed\n");
        _exit(1);
    }
    else
    {
        //Used if the child still needs to be complete.
        //It prints out the pid of the command if the process is being backgrounded
        if(backgroundFlag != 1)
        {
            while(wait(NULL) != childPid);
        }
        if(backgroundFlag == 1)
        {
            printf("%s [%d]\n", newArgv[0], childPid);
        }
    }
}

/*
    NOTES:
    'commandPtr += size + 1' acts as an incrementor for the pointer
    Since this parse function deals with words in the line, the incrementation is not always +1.
*/
int parse()
{
    char commandLine[MAXSIZE];
    char *commandPtr = commandLine;
    int metaCount = 0;

    outputFile = inputFile = outampFile = NULL;

    while(1)
    {
        size = getword(commandPtr);
        //output redirection detection
        if(*commandPtr == '>' && size == 1)
        {
            if(outputFlag == 1)
            {
                fprintf(stderr, "p2: invalid output redirection\n");
                promptFlag = 0;
                break;
            }
            outputFlag++;
            commandPtr += size + 1;
            outputFile = commandPtr;
            metaCount++;
        }
        //input redirection detection
        else if(*commandPtr == '<' && size == 1)
        {
            if(inputFlag == 1)
            {
                fprintf(stderr, "p2: invalid input redirection\n");
                promptFlag = 0;
                break;
            }
            inputFlag++;
            commandPtr += size + 1;
            inputFile = commandPtr;
            metaCount++;
        }
        //>& redirection detection
        else if(strcmp(commandPtr, ">&") == 0)
        {
            if(outerrFlag == 1)
            {
                fprintf(stderr, "p2: invalid redirection\n");
                promptFlag = 0;
                break;
            }
            outerrFlag++;
            commandPtr += size + 1;
            outputFile = commandPtr;
            metaCount++;
        }
        //ampersand detection
        //if there are no errors, it sets the ampFlag for the next iteration
        else if(*commandPtr == '&' && size == 1)
        {
            if(ampFlag == 2)
            {
                fprintf(stderr, "background attempt is invalid\n");
                promptFlag = 0;
                break;
            }
            ampFlag++;
            newArgv[newArgvSize] = commandPtr;
            commandPtr += size + 1;
            newArgvSize++;
        }
        //backgrounding detection at the end
        //this is different from above because it sets the flag for background as there was already an ampersand detected
        //It will only enter this if statement if there is an '&' at the end of the line
        else if(ampFlag == 1 && size <= 0)
        {
            backgroundFlag++;
            break;
        }
        //points the commandPtr past the metacharacters
        else if(metaCount == 1)
        {
            commandPtr += size + 1;
            metaCount = 0;
        }
        //done detection
        //p2 only really cares is done is at the beginning of the command line
        else if(strcmp(commandPtr, "done") == 0)
        {
            //if done is at the beginning of the stdin
            if(newArgvSize == 0)
            {
                doneFlag++;
                break;
            }
            else
            {
                size = 4;   //represents the length of "done"
                newArgv[newArgvSize] = commandPtr;
                commandPtr += size + 1;
                newArgvSize++;
            }
        }
        //EOF detection
        else if(size == -1 && newArgvSize == 0)
        {
            eofFlag++;
            break;
        }
        //push the word into newArgvSize and increment to the next word
        else
        {
            newArgv[newArgvSize] = commandPtr;
            commandPtr += size + 1;
            newArgvSize++;
            ampFlag = 0;
        }
        //EOF detection with multiple arguments
        if(size == -1 && newArgvSize != 0)
        {
            size = 1;
            break;
        }
        //if getword returns a value less then 0, break unless 'EOF' or 'done' termination signals are detected
        if(size <= 0 && doneFlag == 0 && eofFlag == 0)
            break;
    }
    newArgv[newArgvSize-1] = '\0';
    return size;
}

void sigHandler(int signum) {}