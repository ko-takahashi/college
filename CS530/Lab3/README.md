##################################################
# Kosuke Takahashi
# cssc0452 
# CS 530, Spring 2019
# Assignment #3, Parser
# README.MD
##################################################

Grammar:
    id :== identifier
    express :== expression
    assign :==
    op :== operator
    char :== character
    assign :== <id> = <express>;
    exp :== <id> <op> <id> | {(<id> <op> <id>)}
    id :== <char> <digit> | <id> <char> | <id> <digit>
    operation :== + | - | / | * | % |
    char :== A | B | C | ... | Z | a | b | c | ... | z |
    digit :== 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |

File Manifest:
    exp.c
    exp.h
    ex.txt
    Makefile
    README.md
    exp

Compile Instructions:
    To compile this program input "make" into the command line argument.
    Running make will create the exp operator file needed to run the actual parser.
    Once the exp operator file is created, the whole program can be run.
    To run an input file through the parser program type this in the command line argument:
        "./exp ex.txt"
    To run standard input through the parser program type this in the command line
    argument:
        "./exp"
        "<standard input here>"

Operating Instructions:
    Command line arguments: 
        File:
            "./exp ex.txt"
        Standard Input:
            "./exp"
            "<standard input here>"
    Required inputs:
        File:
            ex.txt
        Standard Input:
            <standard input>

Novel/Significant Design Decisions:
    The program is programmed in C.
    For the parser, each main grammar rule was separated into different functions (id(), express(), and assign()). The main method calls the id() function and the id()function jumps to the proper function after determining whether it is an expression or an assignment in the check() function. Then it parses the input accordingly

Extra features/algortihms/functionality included but not required:
    There is a global constant SIZE throughout the code to help denote the size of the input.

Known deficiencies/bugs: 
    Regarding parentheses, this program cannot check for spacing between <id> and ")" to see whether it follows the parenthesis rules.

Lessons Learned:
    How to diffrentiate between standard input or a file
    How to parse a file with certain grammar rules
