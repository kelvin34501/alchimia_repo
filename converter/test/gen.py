from keras.models import Sequential
import keras.layers as L
import keras
import numpy as np

model = Sequential()
model.add(L.Dense(64, input_shape=(5,)))

json_str = model.to_json()
with open('test_0.json', 'w') as outfile:
    outfile.write(json_str)

model.add(L.Dense(10))

model.add(L.Activation('sigmoid'))

json_str = model.to_json()
with open('test.json', 'w') as outfile:
    outfile.write(json_str)

model.compile(optimizer='rmsprop',
              loss='categorical_crossentropy',
              metrics=['accuracy'])

data = np.random.random((1000, 5))
labels = np.random.randint(10, size=(1000, 1))

one_hot_labels = keras.utils.to_categorical(labels, num_classes=10)

model.fit(data, one_hot_labels, epochs=10, batch_size=32)

model.save_weights('test.h5')
