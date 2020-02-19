import numpy as np
import scipy
import matplotlib.pyplot as plt
import tensorflow as tf
from util import func_confusion_matrix
import time
# import data_helpers
import func_two_layer_fc
import os.path
from datetime import datetime

import os
import tempfile

import keras
from keras import backend as K
from keras import layers
from keras.datasets import mnist


# load (downloaded if needed) the MNIST dataset
(x_train, y_train), (x_test, y_test) = mnist.load_data()


# transform each image from 28 by28 to a 784 pixel vector
pixel_count = x_train.shape[1] * x_train.shape[2]
x_train = x_train.reshape(x_train.shape[0], pixel_count).astype('float32')
x_test = x_test.reshape(x_test.shape[0], pixel_count).astype('float32')

# normalize inputs from gray scale of 0-255 to values between 0-1
x_train = x_train / 255
x_test = x_test / 255

# Please write your own codes in responses to the homework assignment 4

# QUESTION 1
# Please further split the 60,000 training images (and labels) into two subsets: 50,000 images, and 10,000 images. 
# Use these two subsets for training models and validation purposes.  
# In particular, you will train your FNN model using the 50,000 images and labels, 
# and apply the trained model over the rest 10,000 images for evaluation purposes. 
#
# Please specify at least three sets of hyper-parameters (see the above). 
# For each set, call the third-party functions or tensorflow to train a FNN model on the training samples 
# (50,000 images in this case), and apply the learned model over the validation set (10,000 images in this case). 
# For each model and its results, please compute its confusion matrix, average accuracy, per-class Precision and Recall. 
# Report the model that achieves the top accuracy. 
#
# A sample function for calculating confusion matrix is provided in ‘util.py’

# QUESTION 2
# Apply the top ranked model over the testing samples (10,000 images). 
# Call the above function to compute the confusion matrix, average accuracy, per-class precision/recall rate.  
# In addition, select and visualize TEN testing images for which your mode made wrong predications. 
# Try to analyze the reasons of these failure cases. 

####################################################################
############## step-0: setting parameters       ####################
####################################################################

batch_size = 128
buffer_size = 10000
steps_per_epoch = int(np.ceil(60000 / float(batch_size)))  # = 469
epochs = 5
num_classes = 10


x_train = np.expand_dims(x_train, -1)
y_train = tf.one_hot(y_train, num_classes)

# Create the dataset and its associated one-shot iterator.
dataset = tf.data.Dataset.from_tensor_slices((x_train, y_train))
dataset = dataset.repeat()
dataset = dataset.shuffle(buffer_size)
dataset = dataset.batch(batch_size)
iterator = dataset.make_one_shot_iterator()

# Model creation using tensors from the get_next() graph node.
inputs, targets = iterator.get_next()
model_input = layers.Input(tensor=inputs)
model_output = cnn_layers(model_input)
train_model = keras.models.Model(inputs=model_input, outputs=model_output)

train_model.compile(optimizer=keras.optimizers.RMSprop(lr=2e-3, decay=1e-5),
                    loss='categorical_crossentropy',
                    metrics=['accuracy'],
                    target_tensors=[targets])
train_model.summary()

train_model.fit(epochs=epochs,
                steps_per_epoch=steps_per_epoch)

# Save the model weights.
weight_path = os.path.join(tempfile.gettempdir(), 'saved_wt.h5')
train_model.save_weights(weight_path)

# Clean up the TF session.
K.clear_session()

# Second session to test loading trained model without tensors.
x_test = x_test.astype(np.float32)
x_test = np.expand_dims(x_test, -1)

x_test_inp = layers.Input(shape=x_test.shape[1:])
test_out = cnn_layers(x_test_inp)
test_model = keras.models.Model(inputs=x_test_inp, outputs=test_out)

test_model.load_weights(weight_path)
test_model.compile(optimizer='rmsprop',
                   loss='sparse_categorical_crossentropy',
                   metrics=['accuracy'])
test_model.summary()

loss, acc = test_model.evaluate(x_test, y_test, num_classes)
print('\nTest accuracy: {0}'.format(acc))

y_pred = model.predict(X_test)
conf_matrix, accuracy, recall_array, precision_array = are(y_test, y_pred)
print("Confusion Matrix: ")
print(conf_matrix)
print("Average Accuracy: {}".format(accuracy))
print("Per-Class Precision: {}".format(precision_array))
print("Per-Class Recall: {}\n".format(recall_array))

