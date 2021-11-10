import imageio
import numpy as np
import pandas as pd
import seaborn as sn
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.naive_bayes import MultinomialNB

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

#TEST
#citire imagini test
test_imgs = np.zeros((5000, 32, 32), 'int')
test_im = []
for i in range(35001, 40001):
    test_imgs[i - 35001] = imageio.imread(f'./ai-unibuc-24-22-2021/test/0{i}.png')
    test_im.append(f'0{i}.png')
test_imgs = test_imgs.reshape(5000, 1024)

#MODELUL NAIV BAYES
naive_bayes_model = MultinomialNB()

def values_to_bins(train, bins):
    index = np.digitize(train, bins) - 1  #pentru fiecare valoare returneaza in ce bin se afla
    return index

def test_naive_bayes(num_bins, train_images, validation_images, train_labels, validation_labels, test_images):
    bins = np.linspace(start=0, stop=255, num=num_bins)  #returneaza intervalele

    train = values_to_bins(train_images, bins)
    validation = values_to_bins(validation_images, bins)
    test = values_to_bins(test_images, bins)

    naive_bayes_model.fit(train, train_labels)  #antrenarea modelului
    validation_predictions = naive_bayes_model.predict(validation)  #fac predictii pe datele de validare
    test_predictions = naive_bayes_model.predict(test)  #fac predictiile pe datele de test
    return naive_bayes_model.score(validation, validation_labels) * 100, test_predictions, validation_predictions  #returnez acuratetea obtinuta pe datele de validare

max_accuracy = (0, 0)
for num_bins in range(1, 50, 2):
    accuracy, test_pred, val_pred = test_naive_bayes(num_bins, train_imgs, validation_imgs, train_labels, validation_labels, test_imgs)
    if accuracy > max_accuracy[0]:
        max_accuracy = (accuracy, num_bins) #pastrez acuratetea maxima obtinuta si pentru cate bins uri am obtinut-o

print("Acuratete Naive Bayes:", max_accuracy)

bins = np.linspace(start=0, stop=255, num=max_accuracy[1])  #returneaza intervalele
train = values_to_bins(train_imgs, bins)
validation = values_to_bins(validation_imgs, bins)
test = values_to_bins(test_imgs, bins)

naive_bayes_model.fit(train, train_labels)  #antrenarea modelului
validation_predictions = naive_bayes_model.predict(validation)  #fac predictii pe datele de validare
test_predictions = naive_bayes_model.predict(test)  #fac predictiile pe datele de test

#matricea de confuzie
matrice_confuzie = confusion_matrix(validation_labels, validation_predictions, labels=None, sample_weight=None, normalize=None)

#plotez matricea de confuzie
# plotting
df_cm = pd.DataFrame(matrice_confuzie, index=[i for i in range(9)], columns=[i for i in range(9)])
sn.set(font_scale=1.2)
sn.heatmap(df_cm, annot=True, annot_kws={"size": 10})
plt.title("Confusion Matrix")
plt.show()
