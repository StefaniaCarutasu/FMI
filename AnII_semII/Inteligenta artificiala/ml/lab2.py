import numpy as np
import matplotlib.pyplot as plt
from sklearn.naive_bayes import MultinomialNB

#2
train_images = np.loadtxt('./data/train_images.txt') # incarcam imaginile
train_labels = np.loadtxt('./data/train_labels.txt', 'int')  # incarcam etichetele

num_bins = 10
bins = np.linspace(start=0, stop=255, num=num_bins)  # returneaza intervalele

def values_to_bins(train, bins):
    index = np.digitize(train, bins) - 1  # pt fiecare valoare returneaza in ce bin se afla
    return index

x = values_to_bins(train_images, bins)
print(np.shape(x))

#3
test_images = np.loadtxt('./data/test_images.txt') # incarcam imaginile
test_labels = np.loadtxt('./data/test_labels.txt', 'int')  # incarcam etichetele avand  							   # tipul de date int
naive_bayes_model = MultinomialNB()  # declarare model Naive Bayes

num_bins = 5

def test_naive_bayes(num_bins):
    bins = np.linspace(start=0, stop=255, num=num_bins)  # returneaza intervalele

    train = values_to_bins(train_images, bins)
    test = values_to_bins(test_images, bins)

    naive_bayes_model.fit(train, train_labels)  # antrenare model
    naive_bayes_model.predict(test)  # predictii pe datele de testare
    print(naive_bayes_model.score(test, test_labels) * 100)  # scorul (cate predicitii a facut corect)

#4
for num_bins in range(3, 12, 2):
    print(num_bins, end = ": ")
    test_naive_bayes(num_bins)

#5
num_bins = 11
bins = np.linspace(start=0, stop=255, num=num_bins)  # returneaza intervalele

train = values_to_bins(train_images, bins)
test = values_to_bins(test_images, bins)

naive_bayes_model.fit(train, train_labels)  # antrenare model
nb_predicts = naive_bayes_model.predict(test) # predictii pe datele de testare

count = 0
for i in range(len(nb_predicts)):
    if count == 10:
        break

    if nb_predicts[i] != train_labels[i]:
        count += 1
        image = train_images[i, :]
        image = np.reshape(image, (28, 28))
        plt.imshow(image.astype(np.uint8), cmap='gray')
        plt.title('Aceasta imagine a fost clasificata ca ' + str(nb_predicts[i]))
        plt.show()

#6
def confusion_matrix(y_true, y_pred):
    conf_matr = np.zeros((10, 10))
    for i in range(len(y_true)):
        conf_matr[y_true[i], y_pred[i]] += 1
    print(conf_matr)

confusion_matrix(test_labels, nb_predicts)