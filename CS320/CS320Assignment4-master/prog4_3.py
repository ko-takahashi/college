import prog4_1
import prog4_2
import sys #system-specific parameters and functions 

print('Assignment #4-3, Bryan Phan, bryan.th.phan@gmail.com')

inFile = sys.argv[1] 
lines = [] 
tokenizedLines = []
parsedLines = [] 

lines = [line.rstrip('\n') for line in open(inFile)] 

for x in lines: 
	tokenizedLines.append(prog4_1.Tokenize(x))
	
for x in tokenizedLines:
	parsedLines.append(prog4_1.Parse(x))
	
while prog4_2.CurrentLine <= len(tokenizedLines):
	prog4_2.StackMachine.Execute(tokenizedLines[prog4_2.CurrentLine-1])

print("Program terminated correctly")

