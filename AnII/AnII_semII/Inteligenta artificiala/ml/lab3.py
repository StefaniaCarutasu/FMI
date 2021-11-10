import numpy as np
import matplotlib.pyplot as plt

train_images = np.loadtxt('./data/train_images.txt')
train_labels = np.loadtxt('./data/train_labels.txt', 'int')
test_images = np.loadtxt('./data/test_images.txt')
test_labels = np.loadtxt('./data/test_labels.txt', 'int')

# 1
class KnnClassifier:
    def __init__(self, train_images, train_labels):
        self.train_images = train_images
        self.train_labels = train_labels

    # 2
    def l1(self, img, images):
        return np.sum(np.abs(images - img), axis=1)

    def l2(self, img, images):
        return np.sqrt(np.sum((images - img) ** 2, axis=1))

    def classify_image(self, test_image, num_neighbors=3, metric='l2'):
        #determinare distante fata de img data
        if metric == "l1":
            dist = self.l1(test_image, self.train_images)
        else:
            dist = self.l2(test_image, self.train_images)

        #determinare cei mai apropriati vecini
        nearest_images = np.argsort(dist)[:num_neighbors]
        nearest_labels = self.train_labels[nearest_images]
        pred = np.argmax(np.bincount(nearest_labels))
        return pred

    def classify_images(self, test_images, num_neighbors, metric):
        pred = np.zeros(test_images.shape[0])
        for i in range(len(test_images)):
            pred[i] = knn.classify_image(test_images[i], num_neighbors, metric)
        return pred

# 3
knn = KnnClassifier(train_images, train_labels)
pred = knn.classify_images(test_images, 3, "l2")
np.savetxt('predictii_3nn_l2_mnist.txt', pred)
accuracy = (pred == test_labels).mean()
print(accuracy)

# 4 a
vec = [1, 3, 5, 7, 9]
accuracyL2 = np.zeros(5)
for i in range(len(vec)):
    accuracyL2[i] = (knn.classify_images(test_images, vec[i], "l2") == test_labels).mean()

np.savetxt('acuratete_l2.txt', accuracyL2)
plt.plot(vec, accuracyL2)
plt.xlabel("number of neighbors")
plt.ylabel("accuracy")
plt.show()

# 4 b
accuracyL1 = np.zeros(5)
for i in range(len(vec)):
    accuracyL1[i] = (knn.classify_images(test_images, vec[i], "l1") == test_labels).mean()

plt.plot(vec, accuracyL2)
plt.plot(vec, accuracyL1)
plt.xlabel("number of neighbors")
plt.ylabel("accuracy")
plt.show()