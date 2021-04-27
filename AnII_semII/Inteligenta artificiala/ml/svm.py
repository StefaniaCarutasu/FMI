import imageio
import numpy as np
from sklearn import svm
from sklearn import preprocessing, metrics

#TRAIN
#citire label-uri imagini de train
train_file = open('ai-unibuc-24-22-2021/train.txt')
train_labels = np.zeros(30001, 'int')
for i in range(30001):
    train_labels[i] = int(train_file.readline().split(',')[1])
train_file.close()

#citire imagini train
train_imgs = np.zeros((30001, 32, 32), 'int')
for i in range(30001):
    if i < 10:
        train_imgs[i] = imageio.imread(f'./ai-unibuc-24-22-2021/train/00000{i}.png')
    elif 10 <= i < 100:
        train_imgs[i] = imageio.imread(f'./ai-unibuc-24-22-2021/train/0000{i}.png')
    elif 100 <= i < 1000:
        train_imgs[i] = imageio.imread(f'./ai-unibuc-24-22-2021/train/000{i}.png')
    elif 1000 <= i < 10000:
        train_imgs[i] = imageio.imread(f'./ai-unibuc-24-22-2021/train/00{i}.png')
    else:
        train_imgs[i] = imageio.imread(f'./ai-unibuc-24-22-2021/train/0{i}.png')

train_imgs = train_imgs.reshape(30001, 1024)

#VALIDATION
#citire label-uri imagini de validation
validation_file = open('ai-unibuc-24-22-2021/validation.txt')
validation_labels = np.zeros(5000, 'int')
for i in range(30001, 35001):
    validation_labels[i - 30001] = int(validation_file.readline().split(',')[1])
validation_file.close()

#citire imagini validation
validation_imgs = np.zeros((5000, 32, 32), 'int')
for i in range(30001, 35001):
    validation_imgs[i - 30001] = imageio.imread(f'./ai-unibuc-24-22-2021/validation/0{i}.png')
validation_imgs = validation_imgs.reshape(5000, 1024)

def normalize_data(train_data, test_data, type=None):
    if type == None:
        return train_data, test_data
    else:
        if type == 'standard':
            scaler = preprocessing.StandardScaler()
            scaler.fit(train_data)
        elif type == "l1":
            scaler = preprocessing.Normalizer("l1")
            scaler.fit(train_data)
        elif type == "l2":
            scaler = preprocessing.Normalizer("l2")
            scaler.fit(train_data)
        elif type == "minmax":
            scaler = preprocessing.MinMaxScaler()
            scaler.fit(train_data)
        return scaler.transform(train_data), scaler.transform(test_data)

scaled_train, scaled_validation = normalize_data(train_imgs, validation_imgs, type="minmax")

max_acc = (0, 0)
for c in range(2, 6):
    print("Working on c =", c)
    svm_acc = svm.SVC(C = 10 ** c, kernel="linear")
    svm_acc.fit(scaled_train, train_labels)
    predictions = svm_acc.predict(scaled_validation)
    accuracy = metrics.accuracy_score(validation_labels, predictions) * 100
    if accuracy > max_acc[0]:
        max_acc = (accuracy, c)
    print("Accuracy: ", accuracy, "deviation: 10 ^", c)

print(max_acc)
