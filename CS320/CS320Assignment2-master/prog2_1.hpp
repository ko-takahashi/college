#include <vector> 
#include <iostream> 
#include <sstream>
#include <string> 

using namespace std; //top of the code so we don't have to use it constantly 

class Tokenizer
{
	private:
		vector<string> *token; //vector of strings 
	public: 
		Tokenizer(); //constructor 
		~Tokenizer(); //deconstructor 
		void Tokenize(string); //tokenize input string 
		vector<string> GetTokens(); //retrieve single set of input tokens 
};
