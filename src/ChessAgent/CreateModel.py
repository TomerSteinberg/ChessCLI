import tensorflow as tf
from tensorflow import keras
from keras import layers

model = keras.Sequential([
    layers.Input(shape=(8,8,14)),
    layers.Conv2D(32, kernel_size=(3, 3), activation="relu"),
    layers.Conv2D(64, kernel_size=(3, 3), activation="relu"),
    layers.Flatten(),
    layers.Dense(128, activation="relu"),
    layers.Dense(64, activation="relu"),
    layers.Dense(1, activation="tanh"),
])

model.compile(loss='mean_absolute_error', optimizer=tf.keras.optimizers.Adam(learning_rate=0.001))
model.save('agent.h5')