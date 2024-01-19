import tensorflow as tf
from tensorflow import keras
from keras import layers
from Loss import ternary_result_agent_loss

model = keras.Sequential([
    layers.Input(shape=(8,8,13)),
    layers.Reshape(target_shape=(8, 8, 13)),
    layers.Conv2D(32, kernel_size=(3, 3), activation="relu"),
    layers.Conv2D(64, kernel_size=(3, 3), activation="relu"),
    layers.Flatten(),
    layers.Dense(128, activation="relu"),
    layers.Dense(64, activation="relu"),
    layers.Dense(1, activation="tanh"),
])

model.compile(loss=ternary_result_agent_loss, optimizer=tf.keras.optimizers.Adam(learning_rate=0.001))
model.save('agent.h5')