import numpy as np
from sklearn import preprocessing, metrics
from sklearn import svm

train_data = np.load('./data/training_sentences.npy', allow_pickle=True)
train_labels = np.load('./data/training_labels.npy', allow_pickle=True)
test_data = np.load('./data/test_sentences.npy', allow_pickle=True)
test_labels = np.load('./data/test_labels.npy', allow_pickle=True)


# 2
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
        return scaler.transform(train_data), scaler.transform(test_data)


# 3
class BagOfWords:
    def __init__(self):
        self.dictionary = {}
        self.all_words = []

    def build_vocabulary(self, data):
        index = 0
        for list in data:
            for word in list:
                if word not in self.dictionary:
                    self.all_words.append(word)
                    self.dictionary[word] = index
                    index += 1

    # 4
    def get_features(self, data):
        features = np.zeros((len(data), len(self.dictionary)))
        for index in range(len(data)):
            for word in data[index]:
                if word in self.dictionary.keys():
                    features[index, self.dictionary[word]] += 1
        return features


bow = BagOfWords()
bow.build_vocabulary(train_data)
# print(len(bow.dictionary))

# 5
train_data = bow.get_features(train_data)
test_data = bow.get_features(test_data)
scaled_train, scaled_test = normalize_data(train_data, test_data, "l2")
# print(train_data, test_data)

# 6
svm_linear = svm.SVC(C=1.0, kernel="linear")
svm_linear.fit(scaled_train, train_labels)
predictions = svm_linear.predict(scaled_test)
accuracy = metrics.accuracy_score(test_labels, predictions)
f1_score = metrics.f1_score(test_labels, predictions)
# print(accuracy, f1_score)

# TEMA - afisare primele 10 cuv negative + 10 cuv pozitive
print(train_labels)
spam = train_data[train_labels == 1]
not_spam = train_data[train_labels == 0]
words = np.sum(spam, axis=0)
indices = (-words).argsort()[:11]
negative_words = []
for i in indices:
    negative_words.append(bow.all_words[i])
print(negative_words)

words = np.sum(not_spam, axis=0)
indices = (-words).argsort()[:11]
positive_words = []
for i in indices:
    positive_words.append(bow.all_words[i])
print(positive_words)