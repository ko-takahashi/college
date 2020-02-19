global exception
exception = False
		
def isNumber(s): 
	try:
		int(s)
		return True
	except ValueError:
		return False
		
def Tokenize(str):
	_validTokens = ['push','pop','add','sub','mul','div','mod','skip','save','get']
	tokens = []
	#if the x character/element is not a valid token or number 
	invalidTokens = [x for x in str.split() if not (x in _validTokens or isNumber(x))]
	if len(invalidTokens) != 0:
		raise ValueError("Unexpected token: " + invalidTokens[0])
	tokens = str.split() #delimiter splits into single characters
	
	return tokens
	
def Parse(tokens):
	 singleTokens = ['pop','add','sub','mul','div','mod','skip']
	 doubleTokens = ['push','save','get']
	 
	 if tokens[0] in singleTokens and len(tokens) != 1:
	 	exception = True
	 	raise ValueError("Parse error: " + ' '.join(str(x) for x in tokens))
	 elif tokens[0] in doubleTokens:
	 	if len(tokens) != 2 or not isNumber(tokens[1]):
	 		raise ValueError("Parse error: " + ' '.join(str(x) for x in tokens))
	 return (True)
