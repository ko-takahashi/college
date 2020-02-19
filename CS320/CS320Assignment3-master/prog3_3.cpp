#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include "lua.hpp"

using namespace std; 

extern "C" { //tells the compiler that the variable is defined somewhere else
	#include <lua.h> //must do it like this since Lua is compiled as C code
	#include <lualib.h> //and we are using it in C++
	#include <lauxlib.h> 
}

int main(int argc, char *argv[]) {
	printf("Assignment #3-3, Bryan Phan, bryan.th.phan@gmail.com\n");
	lua_State *state = luaL_newstate();
	luaL_openlibs(state);
	luaL_dofile(state,argv[1]);
		
	string buff = "return InfixToPostfix(\"";
	string stdInput;
	
	getline(cin,stdInput);
	buff+=stdInput;
	string end = "\")";
	buff+=end;
	
	char run[256];
	strcpy(run,buff.c_str());
	luaL_dostring(state,run); //execute InfixToPostfix algorithm 
	cout<<luaL_checkstring(state,1) << endl; //retrieve postfix string
	lua_close(state);
	return 0; //end program
}
