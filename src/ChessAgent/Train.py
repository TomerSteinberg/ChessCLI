from TrainLib import train_loop
import tensorflow as tf

model = tf.keras.models.load_model('agent.h5')
print("Started training")
train_loop(model, 1) # starting training 
model.save('agent.h5')
