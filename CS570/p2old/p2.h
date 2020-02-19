/*
    Kosuke Takahashi
    Carroll
    CS570
    cssc0097
    REDID: 820144293
    October 9th, 2019
    p2.h
*/

#ifndef PROGRAM2_P2_H
#define PROGRAM2_P2_H

#include "getword.h"
#include "p2.h"

#include <unistd.h>         //dup2, execvp, chdir, fork, access, setpgid, getpgrp
#include <stdlib.h>         //getenv, exit
#include <fcntl.h>          //open
#include <stdio.h>          //perror, fflush
#include <sys/wait.h>       //wait
#include <sys/stat.h>       //stat
#include <signal.h>         //sigaction, killpg, signal
#include <dirent.h>
#include <stdbool.h>
#include <zconf.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>     

#define MAXITEM 100         //MAXITEM represents the maximum words in a line
#define MAXSIZE 25500       //MAXSIZE represents the maximum size of a line

char *outputFile = NULL;    //> redirection pointer
char *inputFile = NULL;     //< redirection pointer
char *outampFile = NULL;    //>& redirection pointer
char *newArgv[MAXITEM];     //what is stored once the command line is processed
//char *bangArgv[MAXITEM];    //stores the old input into here if !! is called
char commandLine[MAXSIZE];       
int newArgvSize = 0;        //size of the newArgv
int size = 0;               //int value when getword() is called in parse method
int fileIndicator = 0;
int cla;                    //deals with Command Line Argument and opening argv[1]
int childPid = 0;

/*
    These are all individual flags to detect certain characters
*/
int promptFlag = 1;         //%1%
int backgroundFlag = 0;
//int bangFlag = 0;           //!!
int doneFlag = 0;
int eofFlag = 0;
int ampFlag = 0;            //&
int cdFlag = 0;
int outputFlag = 0;         //>
int inputFlag = 0;          //<
int outerrFlag = 0;         //>&

/*
    int parse()

    This method is used to parse the initial command line so p2.c can execute accordingly.
    It does this by using my getword.c code and calling getword() to parse the stdin.
    Once it parses, it places the now parced stdin into newArgv.
*/
int parse();

/*
    void execute()

    This method is used to fork the child to execute the command in newArgv[0].
    Once the forking is complete, it redirects accordingly, whether it is a '>', '<', or '>&' case.
    After the forking and redirection is complete, the command can now be executed using the execvp() function.
    In the execute() function, the wait() function is used if the child still needs to be complete.
    It prints out the pid of the command if the process is being backgrounded.
*/
void execute();

/*
    void sigHandler()

    This method is used to deal with SIGTERM
*/
void sigHandler();

#endif