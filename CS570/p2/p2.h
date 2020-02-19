/*
    Kosuke Takahashi
    Carroll
    CS570
    cssc0097
    REDID: 820144293
    November 29th, 2019
    p2.h
*/

#ifndef PROGRAM2_P2_H
#define PROGRAM2_P2_H

#include "getword.h" 

#include "getword.h"
#include <stdio.h>      //perror, fflush
#include <signal.h>     //sigaction, killpg, signal
#include <unistd.h>     //dup2, execvp, chdir, fork, access, setpgid, getpgrp
#include <fcntl.h>      //open
#include <stdlib.h>     //getenv, exit
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <time.h>
#include <semaphore.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>   //stat
#include <sys/wait.h>   //wait
#include <dirent.h>
#include <errno.h>


#define MAXITEM 100         //MAXITEM represents the maximum words in a line
#define MAXSIZE 25500       //MAXSIZE represents the maximum size of a line

char *outputFile = NULL;    //> redirection pointer
char *inputFile = NULL;     //< redirection pointer
char *outampFile = NULL;    //>& redirection pointer
char *newArgv[MAXITEM];     //what is stored once the command line is processed
char *bangArgv[MAXITEM];    //stores the old input into here if !! is called
char commandLine[MAXSIZE];       
int newArgvSize = 0;        //size of the newArgv
int size = 0;               //int value when getword() is called in parse method
int fileIn;                 
int fileOut;
int cla;                    //deals with Command Line Argument and opening argv[1]
int childPid;               //the pid for the first time fork() is called
int grandPid;               //the pid for the second time fork() is called
int lineNum = 0;            //lineNum indicates the current line number in the output
int j;

/*
    These are all individual flags to detect certain characters
*/
int backgroundFlag = 0;     //flag for backgrounding
int doneFlag = 0;           //flag for done
int eofFlag = 0;            //flag for EOF
int ampFlag = 0;            //flag for &
int cdFlag = 0;             //flag for cd
int bangFlag = 0;           //flag for !!
int outputFlag = 0;         //flag for > 
int inputFlag = 0;          //flag for <
int outerrFlag = 0;         //flag for >&
int outoutFlag = 0;         //flag for >>
int outouterrFlag = 0;      //flag for >>&
int commentFlag = 0;        //flag for #
int postCommentFlag = 0;    //flag once # is flagged
int pipeFlag = 0;           //flag for |
int pipeCount = 0;          //flag for where piping occurs
int promptFlag = 1;         //flag to see whether or not to output %n%
int commandLineFlag;

/*
    int parse()

    This method is used to parse the initial command line so p2.c can execute accordingly.
    It does this by using my getword.c code and calling getword() to parse the stdin.
    Once it parses, it places the now parced stdin into newArgv.
*/
int parse();

/*
    void sigHandler()

    This method is used to deal with SIGTERM
*/
void sigHandler();

#endif