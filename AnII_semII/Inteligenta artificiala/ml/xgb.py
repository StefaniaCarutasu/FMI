import imageio
import numpy as np
import pandas as pd
import seaborn as sn
import matplotlib.pyplot as plt
from xgboost import XGBClassifier
from sklearn.metrics import confusion_matrix


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
val_im = []
for i in range(30001, 35001):
    validation_imgs[i - 30001] = imageio.imread(f'./ai-unibuc-24-22-2021/validation/0{i}.png')
    val_im.append(f'0{i}')
validation_imgs = validation_imgs.reshape(5000, 1024)

#TEST
#citire imagini test
test_imgs = np.zeros((5000, 32, 32), 'int')
test_im = []
for i in range(35001, 40001):
    test_imgs[i - 35001] = imageio.imread(f'./ai-unibuc-24-22-2021/test/0{i}.png')
    test_im.append(f'0{i}.png')
test_imgs = test_imgs.reshape(5000, 1024)

modelXGB = XGBClassifier()
modelXGB.fit(train_imgs, train_labels)
predictions_test = modelXGB.predict(test_imgs)  #fac predictiile pe imaginile de test
#scriu in fisierul csv predictiile facute
file = pd.DataFrame({'id':test_im, 'label': predictions_test})
file.to_csv('test_predictions_xgb.csv', index=False)

#matricea de confuzie
validation_predict = modelXGB.predict(validation_imgs)  #fac predictii pe imaginile de validare
matrice_confuzie = confusion_matrix(validation_labels, validation_predict, labels=None, sample_weight=None, normalize=None)

#plotez matricea de confuzie
# plotting
df_cm = pd.DataFrame(matrice_confuzie, index=[i for i in range(9)], columns=[i for i in range(9)])
sn.set(font_scale=1.2)
sn.heatmap(df_cm, annot=True, annot_kws={"size": 10})
plt.title("Confusion Matrix")
plt.show()



