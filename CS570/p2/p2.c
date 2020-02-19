/*
    Kosuke Takahashi
    Carroll
    CS570
    cssc0097
    REDID: 820144293
    November 29th, 2019
    p2.c
*/

#include "p2.h"

/*
    p2.c is a simple command line interpreter.
    This interpreter can handle 'cd', '!!', redirection, running a script, single pipeline arguments, and backgrounding.
    Using my getword.c code, it parses the stdin in the parse() function.
    Then in main, it processes the newArgv and handles redirection.
*/
int main(int argc, char* argv[])
{
    int fi[2];
    commandLineFlag = 0;
    // a signal handler that catches SIGTERM when the process terminates
    setpgid(0,getpid());
    signal(SIGTERM, sigHandler);
    //Handles command line arguments, if the argv[1] can be open, it will redirect its data to stdin
    //This process is used to set up the parse() function properly
    if(argc > 0)
    {
        if((cla = open(argv[1], O_RDONLY)) != -1)
        {
            commandLineFlag = 1;
            dup2(cla, STDIN_FILENO);
            close(cla);
        }
    }
    while(1)
    {
        size = newArgvSize = ampFlag = backgroundFlag = inputFlag = outputFlag = fileIn = fileOut = 0;
        //Checks to see if it is appropriate to print out the prompt
        if(commandLineFlag == 1 || bangFlag == 1)
            promptFlag = 0;
        if(promptFlag == 0)
        {
            lineNum++;
            printf("%%%d%% ", lineNum);
        }
        else
            promptFlag = 0;
        //prompts for input using the string '%1%' in front of the line
        //when there is an error message, perror or fprintf(strd,""), the line does not prompt for '%1%'
        if(parse() == -1)
            break;
        if(newArgvSize == 0)
            continue;
        //Uses the bangFlag to see if there was !! in the command line
        //Puts all of what is in newArgv into another array called bangArgv
        if(bangFlag == 1)
        {
            for(j = 0; j <= newArgvSize; j++)
                newArgv[j] = bangArgv[j];
            bangFlag = 0;
        }
        //Checks if the redirection metacharacters have enough arguments to even perform a redirection
        if((inputFlag == 1 || outputFlag == 1 || outerrFlag == 1) && newArgvSize <= 2)
        {
            fprintf(stderr, "p2: redirection error, not enough arguments\n");
            promptFlag = 1;
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
                    promptFlag = 1;
                    continue;
                }
                continue;
            }
            //if there are arguments, cd goes to the newArgv[1] directory
            if(newArgvSize >= 3)
            {
                if(newArgvSize >= 4)
                {
                    fprintf(stderr, "p2: too many arguments\n");
                    promptFlag = 1;
                    continue;
                }
                if(chdir(newArgv[1]) == -1)
                {
                    perror("p2: child directory not found\n");
                    promptFlag = 1;
                    continue;
                }
                continue;
            }
        }
        //fflush acts as a clear function that clears the stdin and stderr
        //This avoids unintentional repeats
        fflush(stdin);
        fflush(stderr);
        /*
        NOTES:
        O_CREAT, O_EXCL, O_WRONLY, O_RDONLY are file access modes given in the open() function
        S_IRUSR, S_IWUSR are permission bits given from sys/stat.h
        These modes help open the file and give certain permissions to them
        Child process should strictly use _exit() instead of just exit()

        This acts as the execution portion of main(), formerly was an execute() function
        But I decided to consoladate all the functions into main.

        This portion of the code forks the child to execute the command in newArgv[0].
        Once the forking is complete, it redirects accordingly, whether it is a '>', '<', or '>&' case.
        After the forking and redirection is complete, the command can now be executed using the execvp() function.
        In the execute() function, the wait() function is used if the child still needs to be complete.
        It prints out the pid of the command if the process is being backgrounded.
        */
        if((childPid = fork()) == -1)
        {
            perror("p2: fork failed\n");
            _exit(1);
        }
        if(childPid == 0)
        {
            //in each redirection case, the fileIn/fileOut will attempt to open the apporporiate file and duplicate it
            //>& redirection
            if(outerrFlag == 1)
            {
                if((fileOut = open(outputFile, O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IWUSR)) == -1)
                {
                    perror("p2: failure to open output file\n");
                    _exit(-1);
                }
                if((dup2(fileOut, STDOUT_FILENO) == -1) || (dup2(fileOut, STDERR_FILENO) == -1))
                {
                    perror("p2: unable to redirect\n");
                    _exit(-1);
                }
                close(fileOut);
            }
            //>> redirection
            if(outoutFlag == 1)
            {
                if ((fileOut = open(outputFile, O_WRONLY | O_APPEND)) == -1)
                {
                    perror("p2: failed to open output file\n");
                    _exit(-1);
                }
                if (dup2(fileOut, STDOUT_FILENO) == -1)
                {
                    perror("p2: unable to redirect\n");
                    _exit(-1);
                }
                close(fileOut);
            }
            //>>& redirection
            if(outouterrFlag == 1)
            {
                if ((fileOut = open(outputFile, O_WRONLY | O_APPEND)) == -1)
                {
                    perror("p2: failed to open output file\n");
                    _exit(-1);
                }
                if((dup2(fileOut, STDOUT_FILENO) == -1) || (dup2(fileOut, STDERR_FILENO) == -1))
                {
                    perror("p2: unable to redirect\n");
                    _exit(-1);
                }
                close(fileOut);
            }
            //> redirection
            if(outputFlag == 1)
            {
                if((fileOut = open(outputFile, O_CREAT | O_EXCL| O_WRONLY, S_IRUSR | S_IWUSR)) == -1)
                {
                    perror("p2: failed to open output file\n");
                    _exit(-1);
                }
                if(dup2(fileOut, STDOUT_FILENO) == -1)
                {
                    perror("p2: unable to redirection\n");
                    _exit(-1);
                }
                close(fileOut);
            }
            //< redirection
            if(inputFlag == 1)
            {
                if((fileIn = open(inputFile, O_RDONLY)) == -1)
                {
                    perror("p2: failed to open file\n");
                    _exit(-1);
                }
                if(dup2(fileIn, STDIN_FILENO) == -1)
                {
                    perror("p2: unable to redirect\n");
                    _exit(-1);
                }
                close(fileIn);
            }
            //makes sure that the backgrounding does not go over its scope
            if (inputFile == NULL && backgroundFlag == 1)
            {
                if((fileIn = open("/dev/null", O_RDONLY)) == -1)
                {
                    perror("p2: failed to open\n");
                    _exit(-1);
                }
                if(dup2(fileIn, STDIN_FILENO) == -1)
                {
                    perror("p2: unable to redirect\n");
                    _exit(-1);
                }
                close(fileIn);
            }
            //pipe detection (vertical pipelining)
            if(pipeFlag > 0)
            {
                if(pipe(fi) == -1)
                {
                    perror("p2: pipeline failed\n");
                    _exit(-1);
                }
                fflush(stdout);
                fflush(stderr);
                if((grandPid = fork()) == -1)
                {
                    perror("p2: could not fork\n");
                    _exit(-1);
                }
                //Redirects the output to the input of the pipeline in the grandchild.
                else if(grandPid == 0)
                {
                    if(dup2(fi[1], STDOUT_FILENO) < 0)
                    {
                        perror("p2: pipeline output redirection failed\n");
                        _exit(-1);
                    }
                    //It is necessary to close these two ends of the pipeline to avoid a potential deadlock
                    close(fi[1]);
                    close(fi[0]);
                    //normal process execution
                    execvp(newArgv[0],newArgv);
                    fprintf(stderr,"%s: Command cannot execute\n", newArgv[0]);
                    _exit(5);
                }
                else
                {
                    if(backgroundFlag != 1)
                    {
                        while(wait(NULL) != grandPid);
                        //Redirects the input to the ouput of the pipeline in the child to read grandchild
                        if(dup2(fi[0], STDIN_FILENO) == -1)
                        {
                            perror("p2: pipeline input redirection failed\n");
                            _exit(-1);
                        }
                        //It is necessary to close these two ends of the pipeline to avoid a potential deadlock
                        close(fi[1]);
                        close(fi[0]);
                        //pipe process execution
                        execvp(newArgv[pipeCount + 1], newArgv + (pipeCount + 1));
                        fprintf (stderr,"%s: Command cannot execute\n", newArgv[0]);
                        _exit(5);
                    }
                    else
                    {
                        printf("%s [%d]\n", newArgv[0], grandPid);
                        if(dup2(fi[0], STDIN_FILENO) == -1)
                        {
                            perror("p2: pipeline input redirection failed\n");
                            _exit(-1);
                        }
                        //It is necessary to close these two ends of the pipeline to avoid a potential deadlock
                        close(fi[1]);
                        close(fi[0]);
                        //pipe process execution
                        execvp(newArgv[pipeCount + 1], newArgv + (pipeCount + 1));
                        fprintf (stderr,"%s: Command cannot execute\n", newArgv[0]);
                        _exit(5);
                    }
                }
            }
            else
            {
                //normal process execution
                execvp(newArgv[0], newArgv);
                fprintf (stderr,"%s: Command cannot execute\n", newArgv[0]);
                _exit(5);
            }
        }
        else
        {
            //Used if the child still needs to be complete.
            //It prints out the pid of the command if the process is being backgrounded
            if(backgroundFlag != 1)
                while(wait(NULL) != childPid);
            if(backgroundFlag == 1)
                printf("%s [%d]\n", newArgv[0], childPid);
        }
    }
    //kills the signal and terminates the command line
    killpg(getpgrp(), SIGTERM);
    if (commandLineFlag == 0)
        printf("p2 terminated.\n");
    exit(0);
}

/*
    NOTES:
    'commandPtr += size + 1' acts as an incrementor for the pointer
    Since this parse function deals with words in the line, the incrementation is not always +1.
*/
int parse()
{
    //Need to set all the variables to 0 or NULL to avoid a make splint warning/error
    char commandLine[MAXSIZE];
    char *commandPtr = commandLine;
    int metaCount = 0;
    size = newArgvSize = ampFlag = backgroundFlag = inputFlag = outputFlag = pipeFlag = pipeCount = commentFlag = postCommentFlag = outerrFlag = doneFlag = eofFlag = 0; 
    outputFile = inputFile = NULL;
    while(1)
    {
        size = getword(commandPtr);
        //multiple metacharacter detection
        if(metaCount == 1)
        {
            if(*commandPtr == '>' || *commandPtr == '<' || *commandPtr == '&' || *commandPtr == '|' || strcmp(commandPtr, ">&") == 0)
            {
                metaCount--;
                fprintf(stderr, "p2: invalid syntax\n");
                promptFlag = 1;
                break;
            }
        }
        //output redirection detection, pushes pointer according
        if(*commandPtr == '>' && size == 1)
        {
            if(outputFlag == 1)
            {
                fprintf(stderr, "p2: invalid output redirection\n");
                promptFlag = 1;
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
                promptFlag = 1;
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
                promptFlag = 1;
                break;
            }
            outerrFlag++;
            commandPtr += size + 1;
            outputFile = commandPtr;
            metaCount++;
        }
        //>> redirection detection
        else if(strcmp(commandPtr, ">>") == 0)
        {
            if(outoutFlag == 1)
            {
                fprintf(stderr, "p2: invalid redirection\n");
                promptFlag = 1;
                break;
            }
            outoutFlag++;
            commandPtr += size + 1;
            outputFile = commandPtr;
            metaCount++;
        }
        //>>& redirection detection
        else if(strcmp(commandPtr, ">>&") == 0)
        {
            if(outouterrFlag == 1)
            {
                fprintf(stderr, "p2: invalid redirection\n");
                promptFlag = 1;
                break;
            }
            outouterrFlag++;
            commandPtr += size + 1;
            outputFile = commandPtr;
            metaCount++;
        }
        //pipeline detection
        else if(*commandPtr == '|')
        {
            //regular pipeline
            if(size == 1)
            {
                if(pipeFlag > 1)
                {
                    fprintf(stderr, "p2: shell only handles one pipeline\n");
                    promptFlag = 1;
                    break;
                }
                pipeCount = newArgvSize;
                newArgv[newArgvSize] = NULL;
                newArgvSize++;
                commandPtr += size + 1;
                pipeFlag++;
            }
            //backslash pipeline
            else
            {
                size = 1;
                newArgv[newArgvSize] = commandPtr;
                if(bangFlag == 0)
                    bangArgv[newArgvSize] = strdup(commandPtr);
                commandPtr += size + 1;
                newArgvSize++;
            }
        }
        //bangbang detection
        else if(strcmp(commandPtr, "!!") == 0 && newArgvSize == 0)
        {
            bangFlag++;
            break;
        }
        //comment detection
        else if(postCommentFlag == 1)
            commandPtr += size + 1;
        else if(*commandPtr == '#' && commentFlag == 1)
        {
            newArgv[newArgvSize] = NULL;
            newArgvSize++;
            commentFlag = 0;
            postCommentFlag = 1;
        }
        else if(*commandPtr == '#' && commandLineFlag == 1 && commentFlag == 0)
        {
            commentFlag = 1;
            newArgv[newArgvSize] = commandPtr;
            if(bangFlag == 0)
                bangArgv[newArgvSize] = strdup(commandPtr);
            commandPtr += size + 1;
            newArgvSize++;
        }
        //ampersand detection
        //if there are no errors, it sets the ampFlag for the next iteration
        else if(*commandPtr == '&' && size == 1)
        {
            if(ampFlag == 2)
            {
                fprintf(stderr, "background attempt is invalid\n");
                promptFlag = 1;
                break;
                newArgvSize++;
            }
            ampFlag++;
            newArgv[newArgvSize] = commandPtr;
            if(bangFlag == 0)
                bangArgv[newArgvSize] = strdup(commandPtr);
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
            if(newArgvSize == 0)
            {
                doneFlag++;
                break;
            }
            else
            {
                size = 4;
                newArgv[newArgvSize] = commandPtr;
                if(bangFlag == 0)
                    bangArgv[newArgvSize] = strdup(commandPtr);
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

            if(bangFlag == 0)
                bangArgv[newArgvSize] = strdup(commandPtr);
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
    newArgv[newArgvSize-1] = NULL;
    return size;
}

void sigHandler(int signum) {}