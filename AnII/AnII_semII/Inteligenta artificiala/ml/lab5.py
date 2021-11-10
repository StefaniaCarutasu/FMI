import numpy as np
from sklearn.model_selection import KFold
from sklearn.utils import shuffle
from sklearn import preprocessing
from sklearn.metrics import mean_squared_error, mean_absolute_error
from sklearn.linear_model import LinearRegression, Ridge, Lasso

# load training data
training_data = np.load('data_lab6/data/training_data.npy')
prices = np.load('data_lab6/data/prices.npy')

# print the first 4 samples
print('The first 4 samples are:\n ', training_data[:4])
print('The first 4 prices are:\n ', prices[:4])

# shuffle
training_data, prices = shuffle(training_data, prices, random_state=0)

#1
def normalize_data(train_data, test_data):
    scaler = preprocessing.StandardScaler()
    scaler.fit(train_data)
    return scaler.transform(train_data), scaler.transform(test_data)

#2
def train_test(model, train_data, train_labels, test_data, test_labels):
    model.fit(train_data, train_labels)
    predictions = model.predict(test_data)

    mse = mean_squared_error(test_labels, predictions)
    mae = mean_absolute_error(test_labels, predictions)

    return mse, mae
"""
model = LinearRegression()
kf = KFold(n_splits = 3)
mse = 0
mae = 0
for tr, te in kf.split(training_data):
    test_data, test_prices = training_data[te], prices[te]
    train_data, train_prices = training_data[tr], prices[tr]
    mse1, mae1 = train_test(model, train_data, train_prices, test_data, test_prices)
    mse += mse1
    mae += mae1

print(mse / 3, mae / 3)
"""
#3
alpha = 1
kf = KFold(n_splits = 3)
maev = []
msev = []
vals = [1, 10, 100, 1000]
for alfa in vals:
    modelRidge = Ridge(alpha)
    for tr, te in kf.split(training_data):
        test_data, test_prices = training_data[te], prices[te]
        train_data, train_prices = training_data[tr], prices[tr]
        train_data, test_data = normalize_data(train_data, test_data)
        mse, mae = train_test(modelRidge, train_data, train_prices, test_data, test_prices)
        maev.append(mae)
        msev.append(mse)
best_alpha = print(vals[np.argmax(msev)])
print(vals[np.argmax(maev)])

#4
train_data, ceva = normalize_data(training_data, training_data)
model_best_ridge = Ridge(alpha=best_alpha)
model_best_ridge.fit(train_data, prices)
print(model_best_ridge.coef_)
print(model_best_ridge.intercept_)

indices = (abs(-model_best_ridge.coef_)).argsort()
print("cel mai semnificativ: " + str(indices[-1]))
print("al doilea cel mai semnificativ: " + str(indices[-2]))
print("cel mai putin semnificativ: "+ str(indices[0]))
