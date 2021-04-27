import imageio
import numpy as np

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

#KNN Classifier
class KnnClassifier:
    def __init__(self, train_images, train_labels):
        self.train_images = train_images
        self.train_labels = train_labels
    def l1(self, img, images):
        return np.sum(np.abs(images - img), axis=1)

    def l2(self, img, images):
        return np.sqrt(np.sum((images - img) ** 2, axis=1))

    def classify_image(self, test_image, num_neighbors=3, metric='l2'):
        #determinare distante fata de imaginea data
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

knn = KnnClassifier(train_imgs, train_labels)
max_acc = (0, 0)
for i in range(3, 50, 2):
    print("Number of neighbors:", i, end= "    ")
    pred = knn.classify_images(validation_imgs, i, "l2")
    accuracy = (pred == validation_labels).mean()
    print("Accuracy: ", accuracy)
    if accuracy > max_acc[0]:
        max_acc = (accuracy, i)
print(max_acc)
