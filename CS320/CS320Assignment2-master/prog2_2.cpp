#include <string> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> 
#include <cstdlib>
#include "prog2_1.hpp"

using namespace std; 

int main(int argc,char** argv) {
	cout << "Assignment #2-2, Bryan Phan, bryan.th.phan@gmail.com" << endl;
	if(argc!=2) { 
		exit(EXIT_FAILURE);//zero or more than one command line 
	}
	else { 
		int i = 0; //keeps track of line
		try {	
			Tokenizer t; //tokenizer class
			string infile = argv[1], line;			
			ifstream ifs(infile.c_str()); //input stream class to operate on files 
			//.c_str used to contain c-string copy of infile 
			while(getline(ifs, line)){ //extract characters from ifs and store into line	
				i++; //move to the next line 
				t.Tokenize(line); //call Tokenizer and use tokenize function 				
			
			}
			vector<string> token = t.GetTokens(); //call Tokenize and use GetTokens function
			for (int j=0; j<token.size(); j++) { //loops through the vector<string> token 
				stringstream ss(token[j]); 
				int k = 0; 
				string character; 
				while(getline(ss,character,' ')) { //delimiter 
					k++;
					//checks to see if the first character that does not match the digits 
					if(k>1) {//more than one token (i.e. push 3 -> push, )
							cout<<","<<character;
					}
					else {
						if(character.find_first_not_of("1234567890")==string::npos) {
							stringstream ssin(character);
							int digit;
							ssin>>digit;//extraction (can't use getline since we are looking for int
							cout<<","<<digit; 
							}
						else    //one token left (i.e. 3 -> 3) (k<1) 
							cout<<character;
					}
				}
				cout<<endl;
			} 
		}
		catch(string invalid) { //catches the invalid string and outputs the tokenization error on line #
			cout << "Error on line " << i << ": " << invalid << endl; 
			return 1; //return 1 because we want to end the program after the error
		}
	}
	return 0; //end program 
}
