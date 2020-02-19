CurrentLine = 1
stack = []
savedVal = {}

class StackMachine:

	def __init__(self):
		return None
		
	def Execute(tokens):
		global CurrentLine
		
		if tokens[0] == 'push':
			stack.append(int(tokens[1]))
			
		elif tokens[0] == 'pop':
			if len(stack) == 0: #nothing to pop
				raise IndexError("Invalid Memory Access")
			CurrentLine += 1
			x = stack.pop()
			print(x)
			return x
			
		elif tokens[0] == 'add':
			try:
				stack.append(stack.pop() + stack.pop())
			except IndexError:
				raise IndexError("Invalid Memory Access")
		
		elif tokens[0] == 'sub':
			try: 
				stack.append(stack.pop() - stack.pop())
			except IndexError:
				raise IndexError("Invalid Memory Access")
				
		elif tokens[0] == 'mul':
			try:
				stack.append(stack.pop() * stack.pop())
			except IndexError:
				raise IndexError("Invalid Memory Access")
				
		elif tokens[0] == 'div':
			try:
				stack.append(stack.pop() / stack.pop())
			except IndexError:
				raise IndexError("Invalid Memory Access")
				
		elif tokens[0] == 'mod': #divides left by right and returns remainder
			try:
				stack.append(stack.pop() % stack.pop())
			except IndexError:
				raise IndexError("Invalid Memory Access")
				
		elif tokens[0] == 'skip':
			try: 
				x = stack.pop()
				y = stack.pop()
				if x == 0:
					CurrentLine += y
			except IndexError:
				raise IndexError("Invalid Memory Access")
		
		elif tokens[0] == 'save':
			try:
				savedVal[tokens[1]] = stack.pop()
			except IndexError:
				raise IndexError("Invalid Memory Access")
				
		elif tokens[0] == 'get':
			try:
				stack.append(savedVal[tokens[1]])
			except IndexError:
				raise IndexError("Invalid Memory Access")
				
		CurrentLine += 1 
