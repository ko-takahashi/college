
import numpy as np
# X          - single array/vector
# y          - single array/vector
# theta      - single array/vector
# alpha      - scalar
# iterations - scarlar

def gradientDescent(X, y, theta, alpha, numIterations):
    '''
    # This function returns a tuple (theta, Cost array)
    '''
    m = len(y)
    arrCost =[];
    transposedX = np.transpose(X) # transpose X into a vector  -> XColCount X m matrix
    for iteration in range(0, numIterations):
        ################PLACEHOLDER3 #start##########################
        #: write your codes to update theta, i.e., the parameters to estimate. 
	# Replace the following variables if needed
        
        # Sets residualError to the dot product of X and theta
        residualError = X.dot(theta)
        # Sets gradient to the dot prodcut of X and theta from np
        gradient =  np.dot(X,theta)
        # Sets theta into the formula that changes each iteration through the loop
        theta = theta - (1/m)*alpha*(X.T.dot((gradient - y)))
        ################PLACEHOLDER3 #end##########################

        ################PLACEHOLDER4 #start##########################
        # calculate the current cost with the new theta; 
        
        # calculates the cost with the new updated values from PLACEHOLDER3
        atmp =  (1/2*m) * np.sum(np.square(residualError-y)) 

        arrCost.append(atmp)
        arrCost[iteration] = atmp
    print(atmp)
        # cost = (1 / m) * np.sum(residualError ** 2)
        ################PLACEHOLDER4 #start##########################

    return theta, arrCost
