#include <iostream>
#include <string>
#include <cstdlib>

using namespace std; 

extern "C" { //tells the compiler that the variable is defined somewhere else
	#include <lua.h> //must do it like this since Lua is compiled as C code
	#include <lualib.h> //and we are using it in C++
	#include <lauxlib.h> 
}

int main(int argc, char *argv[]) {
	printf("Assignment #3-1, Bryan Phan, bryan.th.phan@gmail.com\n");
	lua_State *state = luaL_newstate();
	luaL_openlibs(state);
	
	if(argc == 2) { //if it's a single command line arg, otherwise close 
		string luaFile = argv[1];
		size_t isLua = luaFile.find(".lua"); //searches for a .lua file
		if(isLua != string::npos) { //if a .lua file was found, 
			luaL_dofile(state, argv[1]); //opens the named file and executes its contents 
		}
	}
	lua_close(state); //close the lua environment 
	return 0; 
}
