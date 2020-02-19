import numpy as np
import download_data as dl
import matplotlib.pyplot as plt
import sklearn.svm as svm
from sklearn import metrics
from conf_matrix import func_confusion_matrix

#CS 596, machine learning

## step 1: load data from csv file. 
data = dl.download_data('crab.csv').values

n = 200
#split data 
S = np.random.permutation(n)
#100 training samples
Xtr = data[S[:100], :6]
Ytr = data[S[:100], 6:].ravel()
# 100 testing samples
X_test = data[S[100:], :6]
Y_test = data[S[100:], 6:].ravel()

## step 2 randomly split Xtr/Ytr into two even subsets: use one for training, another for validation.
#############placeholder: training/validation #######################
n2 = len(Xtr)
S2 = np.random.permutation(n2)

# subsets for training models
# has to be half of the 100 previous dataset
x_train= Xtr[S2[:50],:]
y_train= Ytr[S2[:50]]
# subsets for validation
x_validation= Xtr[S2[50:],:]
y_validation= Ytr[S2[50:]]
#############placeholder #######################

## step 3 Model selection over validation set
# consider the parameters C, kernel types (linear, RBF etc.) and kernel
# parameters if applicable. 


# 3.1 Plot the validation errors while using different values of C ( with other hyperparameters fixed) 
#  keeping kernel = "linear"
#############placeholder: Figure 1#######################
c_parameters = []
c_range =  np.arange(0.5,7.0,0.5)
svm_c_error = []
for c_value in c_range:
    model = svm.SVC(kernel='linear', C=c_value)
    model.fit(X=x_train, y=y_train)
    error = 1. - model.score(x_validation, y_validation)
    svm_c_error.append(error)
plt.plot(c_range, svm_c_error)
plt.title('Linear SVM')
plt.xlabel('c values')
plt.ylabel('error')
#plt.xticks(c_range)
plt.show()

# needs an index to keep track of the process
# c_parameters changes the data before going through the nest for loop
index = np.argmin(svm_c_error)
c_parameters.append(c_range[index])

svm_c_error = []
for c_value in c_range:
    model = svm.SVC(kernel='poly', C=c_value)
    model.fit(X=x_train, y=y_train)
    error = 1. - model.score(x_validation, y_validation)
    svm_c_error.append(error)
plt.plot(c_range, svm_c_error)
plt.title('Polynomial SVM')
plt.xlabel('c values')
plt.ylabel('error')
#plt.xticks(c_range)
plt.show()

index = np.argmin(svm_c_error)
c_parameters.append(c_range[index])

svm_c_error = []
for c_value in c_range:
    model = svm.SVC(kernel='rbf', C=c_value)
    model.fit(X=x_train, y=y_train)
    error = 1. - model.score(x_validation, y_validation)
    svm_c_error.append(error)
plt.plot(c_range, svm_c_error)
plt.title('RBF SVM')
plt.xlabel('c values')
plt.ylabel('error')
#plt.xticks(c_range)
plt.show()

index = np.argmin(svm_c_error)
c_parameters.append(c_range[index])
#############placeholder #######################


# 3.2 Plot the validation errors while using linear, RBF kernel, or Polynomial kernel ( with other hyperparameters fixed) 
#############placeholder: Figure 2#######################

kernel_types = ['linear', 'poly', 'rbf']
svm_kernel_error = []
x = 0
for kernel_value in kernel_types:
    # your own codes
    model = svm.SVC(kernel = kernel_value, C =c_parameters[x])
    model.fit(X=x_train, y=y_train)
    error =  1. - model.score(x_validation, y_validation)
    svm_kernel_error.append(error)
    x +=1
# similar to the for loop used for Figure 1 but x needs to be iterated
plt.plot(kernel_types, svm_kernel_error)
plt.title('SVM by Kernels')
plt.xlabel('Kernel')
plt.ylabel('error')
plt.xticks(kernel_types)
plt.show()

best = np.argmin(svm_kernel_error)

## step 4 Select the best model and apply it over the testing subset 
best_kernel = kernel_types[best]
best_c = c_parameters[best] # poly had many that were the "best"
model = svm.SVC(kernel=best_kernel, C=best_c)
model.fit(X=x_train, y=y_train)
## step 5 evaluate your results with the metrics you have developed in HA3,including accuracy, quantize your results. 


y_pred = model.predict(X_test)
conf_matrix, accuracy, recall_array, precision_array = func_confusion_matrix(Y_test, y_pred)
print("Best kernel: {}   c = {}".format(best_kernel,best_c))
print("Confusion Matrix: ")
print(conf_matrix)
print("Average Accuracy: {}".format(accuracy))
print("Per-Class Precision: {}".format(precision_array))
print("Per-Class Recall: {}\n".format(recall_array))

success = (y_pred == Y_test)
counter = 0
print("5 Failure Examples")
for x in range(len(success)):
   if(not(success[x])):
      counter+=1
      print("Prediction: {}    Ground-truth: {}".format(y_pred[x],Y_test[x]))
      print("Features: {}\n".format(X_test[x]))
   if (counter == 5):
      break
counter = 0
print("5 Successs Examples")
for x in range(len(success)):
   if(success[x]):
      counter+=1
      print("Correct Prediction: {}".format(y_pred[x]))
      print("Features: {}\n".format(X_test[x]))
   if (counter == 5):
      break
