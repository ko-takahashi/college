#include <vector> 
#include <iostream> 
#include <sstream>
#include <string> 
#include <fstream>
#include <ctype.h>
#include <cstddef>
#include "prog2_1.hpp" 

Tokenizer::Tokenizer() { //constructor 
  	this->token=new vector<string>();
}

Tokenizer::~Tokenizer() { //deconstructor 
  	delete this->token;
}

void Tokenizer::Tokenize(string input) {
  	stringstream ss(input); //stream class to operate on strings, characters can be extracted 
  	string t; //string buffer 
  	bool validToken = false; //if token is invalid 
  	while(getline(ss,t,' ')) { //characters are extracted from ss and stored and t 
  		//searches the string for the first character that does not match the digits 
  		//string::npos = until the end of the file 
  		if(t.find_first_not_of("1234567890")==string::npos) 
  			validToken = true; //return true, because valid token is an integer 
  		//valid string tokens must be of these 10 tokens 
        	else if(t=="push" || t=="pop" || t=="add" || t=="sub" || t=="mul" || t=="div" || t=="mod" || t=="skip" || t=="save" || t=="get")
              		validToken = true;
        	else { 
              		validToken = false; //return false for all other input 
              		throw ("Unexpected token: " + t); //throws invalid token 
        	}
  	}
  	if(validToken)
        	token->push_back(input); //pushes all the valid tokens onto the vector 
}

vector<string> Tokenizer::GetTokens() {
  	if(this->token->empty()) //if the vector is empty, throw "no tokens" 
        	throw ("No tokens");
  	else
        	return *token;	//retrieve string input 
}




