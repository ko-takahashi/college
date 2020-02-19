#include <vector> 
#include <iostream> 
#include <sstream>
#include <string> 
#include <fstream>
#include <ctype.h>
#include <cstddef>
#include "prog2_1.hpp" 
#include "prog2_3.hpp" 

Parser::Parser() {
  	tokenLineError=-1; //-1 because since this is the constructor we should have no line errors 
}
Parser::~Parser(){
}

bool Parser::Parse(vector<string> token) {
  	for(int i=0;i<token.size();i++) { //loops through the vector<string> token
        	if(token[i].substr(0,3)=="pop" || token[i].substr(0,3)=="add") { //substr(0,3) means the token contains three characters (i.e. pop and add) 
        		if(token[i].length()>3) { //if it has more than 3 characters (should be alone) 
                    		tokenLineError=i; //store line error # into i 
                    		return false; //return false 
  	        	}
        	}
        	else if(token[i].substr(0,3)=="sub" || token[i].substr(0,3)=="mul") {
        		if(token[i].length()>3) { //if it has more than 3 characters (should be alone)
                    		tokenLineError=i; //store line error # into i
                    		return false; //return false 
  	        	}
        	}
        	else if(token[i].substr(0,3)=="div" || token[i].substr(0,3)=="mod") {
        		if(token[i].length()>3) { //if it has more than 3 characters (should be alone) 
                    		tokenLineError=i; //store line error # into i
                    		return false; //return false 
  	        	}
        	}
        	else if(token[i].substr(0,4)=="skip") { //substr(0,4) means the token contains 4 characters(i.e. skip)
              		if(token[i].length()>4) { //if it has more than 4 characters 
                    		tokenLineError=i; //store line error # into i
                    		return false; 
              		}
        	}
        	else if(token[i].substr(0,4)=="push" || token[i].substr(0,4)=="save") { //push & save, must appear with an arg after (i.e. push 7)
              		if(token[i].length()<=5) { //less than 5 characters 
                    		tokenLineError=i;
                    		return false;
              		} //not a digit 
              		if(token[i].substr(5).find_first_not_of("1234567890")!=string::npos) {
                    		tokenLineError=i;
                    		return false;
              		}
        	}
        	else if(token[i].substr(0,3)=="get") { //must appear with an arg after
              		if(token[i].length()<=4) { //less than 4 characters 
                    		tokenLineError=i;
  	              		return false;
              		} //not a digit 
              		if(token[i].substr(4).find_first_not_of("1234567890")!=string::npos) {
                    		tokenLineError=i;
                    		return false;
              		}
        	}
  	}
  	return true; //no parsing errors 
}



