#include <vector> 
#include <iostream> 
#include <sstream>
#include <string> 

using namespace std; //top of the code so we don't have to use it constantly 

class Parser 
{
	public: 
		Parser(); //constructor
		~Parser(); //deconstructor 
		bool Parse(vector<string> token); //boolean function that parses given tokens
		int tokenLineError; //int variable that tracks which line the parser error occured 
};


