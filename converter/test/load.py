from keras.models import model_from_json
import numpy as np

# with open('test_0.json', 'r') as infile:
#     json_str = infile.readline()

with open('test.json', 'r') as infile:
    json_str = infile.readline()

model = model_from_json(json_str)
model.load_weights('test.h5')

data = np.random.random((1000, 5))
y = model.predict(data)
print(y)
