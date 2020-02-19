function InfixToPostfix(infix)
  infix = string.gsub(infix, "%s+", "")--.gsub -> Global Substitution 
  length = string.len(infix) --.len --> length of string
  newString = ""
  for n=1,length do
	letter = string.sub(infix,n,n)--extracts a piece of string from string infix, from the n-th to the n-th character
	if(letter== "+" or letter== "-" or letter== "*" or letter== "/" or letter== "%") then
        	newString = newString.. " ".. letter.. " "
	else
    		newString = newString.. letter
	end
  end
 
 function opOrdering(stack,char)--checks the precedence of the characters (%, /, *, +, -)
	s = 0
	c = 0
	if(stack=="%" or stack=="/" or stack=="*") then
    		s = 2
	elseif(stack=="+" or stack=="-") then
    		s = 1
	end
	if(char=="%" or char=="/" or char=="*") then
    		c = 2
	elseif(char=="+" or char=="-") then
    		c = 1
	end
	if (s==c and s~=0 and c~=0) then
		return 3  
	elseif(s<c) then
    		return 2
	elseif(s>c) then
    		return 1
	else
    		return 0
	end
end
 
  opstack = {} 
  opCount = 0
  pString = ""
 
  for i in (newString):gmatch(".") do
   --checks the operand 
	if(i== "+" or i== "-" or i== "*" or i== "/" or i== "%") then
    	--checks their priority 
    	while(opCount ~= 0 and opstack[1] and opOrdering(opstack[opCount],i)==1) do
            pString = pString.. table.remove(opstack,opCount).. " " 
        	opCount = opCount - 1	
    	end
    	--checks to see if the given characters are the same 
    	if(opCount ~= 0 and opOrdering(opstack[opCount],i)==3) then
        	pString = pString.. table.remove(opstack,opCount).. " "
            table.insert(opstack,opCount,i)
    	elseif(opOrdering(opstack[opCount],i)==0) then
        	print("Error")
            return
    	else
        	opCount = opCount + 1
        	table.insert(opstack,i)
    	end
	elseif(i==" ") then    
    		pString = pString.. " " 
	else
    		pString = pString.. i
	end
  end
  --puts the rest of the characters from stack into output
  while(opCount ~=0) do
    if(opstack[opCount] == "(") then
        	print("Error: Missing ( or )" )
        	return
	end
    pString = pString .. " ".. table.remove(opstack,opCount)
    opCount = opCount - 1
  end
  --prints header and  returns output to be used for prog3_3 
  print("Assignment #3-2, Bryan Phan, bryan.th.phan@gmail.com")
  pString = string.gsub(pString, "%s+%s+", " ")
  return(pString)
end

