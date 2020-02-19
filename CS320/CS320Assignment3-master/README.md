Bryan Phan
bryan.th.phan@gmail.com

The project was to exercise our knowledge of the C/C++ language as well as LUA programming and parsers. 

The first part of this project was to create a C/C++ program that will take a single command line argument, that being the name of a lua file (.lua). The program then executed the Lua file in a lua environment created by the C/C++ program. In order to compile Program 1 by g++ prog3_1.cpp -o prog3_1 -I lua-5.3.4/src -L lua-5.3.4/src -1 m -1 d1

The second program(prog3_2.lua) was written in Lua and implemented the Infix to Postfix function. It takes in a single argument and tokenize that input string by space and then apply the algorithm to return a postfix string. 

The third program was written in C++(prog3.cpp) and is an extension of prog3_1.cpp. It created a lua environment and loaded the file specified by the command line argument. It will then take in a line of input from stdin and execute the InfixToPostfix() function in lua (using dostring). Then it will retrieve the resulting postfix string from the lua stack(useing the checkstring function) and then print the resultant postfix string. 








