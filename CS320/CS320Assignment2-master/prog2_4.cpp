#include <string> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> 
#include <cstdlib>
#include "prog2_1.hpp"
#include "prog2_3.hpp"

using namespace std;

int main(int argc,char** argv) {
    cout << "Assignment #2-4, Bryan Phan, bryan.th.phan@gmail.com" << endl;
  	if(argc!=2) { 
        	exit(EXIT_FAILURE); //zero or more than one command line
  	}
  	else { //single command line
  		vector<string> token;
  		Tokenizer t; //calls Tokenizer class
        	Parser p; //calls Parser class 
        	int i=0; //keeps track of line 
        	bool parser = false; //used to see if the parser has passed or failed (invalid or not) 
        	string infile=argv[1], line;
        	try { //tokenization portion
              		ifstream ifs(infile.c_str());//input stream class to operate on files 
			//.c_str used to contain c-string copy of infile 
              		while(getline(ifs,line)) { ////input stream class to operate on files 
			//.c_str used to contain c-string copy of infile    						
                    		i++; //read the next line
                    		t.Tokenize(line); //tokenize the line 
              		}
              		token=t.GetTokens(); //GetTokens from the vector<string> token
              		parser=true; //tokenization passed, move on to parser 
        	}
        	catch(string invalid) { //tokenization failed (invalid token) 
              		parser=false;
              		cout<<"Error on line "<< i <<": "<<invalid<<endl; //error like that of prog2_2
        	}

        	if(parser) { //parser portion 
              		if(p.Parse(token)) {              	
                    		for(int i=0;i<token.size();i++) { //loops through the tokens 
                          		stringstream ss(token[i]);                          	
                          		int k=0;
                          		string character;
                          		while(getline(ss,character,' ')) { //delimiter 
                                		k++;                
                                		if(k>1) {//more than one token (i.e. push 3 -> push, )
                                            			cout<<","<<character;
                                		}
                                		else { 
                                			//checks to see if the first character that does not match the digits                 	
                                            		if(character.find_first_not_of("1234567890")==string::npos) {
                                      				stringstream ssin(character);
                                      				int digit;
                                      				ssin>>digit;
                                      				cout<<","<<digit;
                                      			}
                                      			else 	//one token left(i.e. 3 -> 3) (k<1) 
                                      				cout<<character;
                                		}
                    	  		}
                          		cout<<endl;
                    		}
              		}
              		else { 
                    		cout<<"Parse error on line "<<p.tokenLineError+1<<": "<<token[p.tokenLineError];
                    		//if parsing failed, parser error is printed telling what line it's on and the single or double token error (i.e pop 3 or push) 
              		}
        	}
  	}
  	return 0; //end program
}




