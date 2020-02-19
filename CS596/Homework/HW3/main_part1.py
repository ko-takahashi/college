import math
import numpy as np
import matplotlib.pyplot as plt
from getDataset import getDataSet
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report

# Starting codes

# Fill in the codes between "%PLACEHOLDER#start" and "PLACEHOLDER#end"

# step 1: generate dataset that includes both positive and negative samples,
# where each sample is described with two features.
# 250 samples in total.

[X, y] = getDataSet()  # note that y contains only 1s and 0s,

# create figure for all charts to be placed on so can be viewed together
fig = plt.figure()


def func_DisplayData(dataSamplesX, dataSamplesY, chartNum, titleMessage):
    idx1 = (dataSamplesY == 0).nonzero()  # object indices for the 1st class
    idx2 = (dataSamplesY == 1).nonzero()
    ax = fig.add_subplot(1, 3, chartNum)
    # no more variables are needed
    plt.plot(dataSamplesX[idx1, 0], dataSamplesX[idx1, 1], 'r*')
    plt.plot(dataSamplesX[idx2, 0], dataSamplesX[idx2, 1], 'b*')
    # axis tight
    ax.set_xlabel('x_1')
    ax.set_ylabel('x_2')
    ax.set_title(titleMessage)

# implementation of sigmoid function
def Sigmoid(x):
	g = float(1.0 / float((1.0 + math.exp(-1.0*x))))
	return g

# Prediction function
def Prediction(theta, x):
	z = 0
	for i in range(len(theta)):
		z += x[i]*theta[i]
	return Sigmoid(z)

# execute gradient updates over thetas
def Gradient_Descent(X,Y,theta,m,alpha):
	new_theta = []
	constant = alpha/m
	for j in range(len(theta)):
		deltaF = Cost_Function_Derivative(X,Y,theta,j,m,alpha)
		new_theta_value = theta[j] - deltaF
		new_theta.append(new_theta_value)
	return new_theta

# implementation of cost functions
def Cost_Function(X,Y,theta,m):
	sumOfErrors = 0
	for i in range(m):
		xi = X[i]
		est_yi = Prediction(theta,xi)
		if Y[i] == 1:
			error = Y[i] * math.log(est_yi)
		elif Y[i] == 0:
			error = (1-Y[i]) * math.log(1-est_yi)
		sumOfErrors += error
	const = -1/m
	J = const * sumOfErrors
	#print 'cost is ', J 
	return J

# gradient components called by Gradient_Descent()
def Cost_Function_Derivative(X,Y,theta,j,m,alpha):
	sumErrors = 0
	for i in range(m):
		xi = X[i]
		xij = xi[j]
		hi = Prediction(theta,X[i])
		error = (hi - Y[i])*xij
		sumErrors += error
	m = len(Y)
	constant = float(alpha)/float(m)
	J = constant * sumErrors
	return J

#############
# Problem 3 #
#############
from sklearn.metrics import confusion_matrix
def func_calConfusionMatrix(predY, trueY):
	result = confusion_matrix(trueY, predY)
	print(result)

#In [11]: y = arange(5); (y==2).nonzero()[0]
#Out[11]: array([2])

# plotting all samples
func_DisplayData(X, y, 1, 'All samples')

# number of training samples
nTrain = 120

######################PLACEHOLDER 1#start#########################
# write you own code to randomly pick up nTrain number of samples for training and use the rest for testing.
maxIndex = len(X)
randomTrainingSamples = np.random.choice(maxIndex, nTrain, replace=False)

trainX =  X[randomTrainingSamples]   #  training samples
trainY =  y[randomTrainingSamples] # labels of training samples    nTrain X 1

testX =   X[~randomTrainingSamples]# testing samples               
testY =   y[~randomTrainingSamples]# labels of testing samples     nTest X 1
####################PLACEHOLDER 1#end#########################

# plot the samples you have pickup for training, check to confirm that both negative
# and positive samples are included.
func_DisplayData(trainX, trainY, 2, 'training samples')
func_DisplayData(testX, testY, 3, 'testing samples')

# show all charts
plt.show()

#  step 2: train logistic regression models

######################PLACEHOLDER2 #start#########################
# in this placefolder you will need to train a logistic model using the training data: trainX, and trainY.

#####################
# use sklearn class #
#####################
clf = LogisticRegression()
# call the function fit() to train the class instance
clf.fit(trainX,trainY)

###############################
# use Gradient_Descent method #
###############################
theta = [0,0] #initial model parameters
alpha = 0.05 # learning rates
max_iteration = 1000 # maximal iterations
m = len(y) # number of samples
for x in range(max_iteration):
	# call the functions for gradient descent method
	new_theta = Gradient_Descent(X,y,theta,m,alpha)
	theta = new_theta
	if x % 200 == 0:
		# calculate the cost function with the present theta
		Cost_Function(X,y,theta,m)

######################PLACEHOLDER2 #end #########################

# step 3: Use the model to get class labels of testing samples.
 
######################PLACEHOLDER3 #start#########################
# codes for making prediction, 
# with the learned model, apply the logistic model over testing samples
# hatProb is the probability of belonging to the class 1.
# y = 1/(1+exp(-Xb))
# yHat = 1./(1+exp( -[ones( size(X,1),1 ), X] * bHat )); ));            

predictions = []
for i in range(0, len(testX)):
    predictions.append(round(Prediction(theta , testX[i])))
yHat = np.array(predictions)

sk_prediction = clf.predict(testX)
gd_prediction = yHat
######################PLACEHOLDER 3 #end #########################

# step 4: evaluation
# compare predictions yHat and and true labels testy to calculate average error and standard deviation
gd_YDiff = np.abs(gd_prediction - testY)
gd_avgErr = np.mean(gd_YDiff)
gd_stdErr = np.std(gd_YDiff)
print("\nGradient Descent: \n")
print(classification_report(testY,gd_prediction))
print('Gradient Descent Average Error: {} ({})\n'.format(gd_avgErr, gd_stdErr))
print("Gradient Descent Confustion Matrix\n")
func_calConfusionMatrix(gd_prediction, testY)

sk_YDiff = np.abs(sk_prediction - testY)
sk_avgErr = np.mean(sk_YDiff)
sk_stdErr = np.std(sk_YDiff)
print("\nsklearn: \n")
print(classification_report(testY,sk_prediction))
print('sklearn Average Error: {} ({})\n'.format(sk_avgErr, sk_stdErr))
print("sklearn Confusion Matrix\n)
func_calConfusionMatrix(sk_prediction, testY)


