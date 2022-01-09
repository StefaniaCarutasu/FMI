import numpy as np
from matplotlib import image
from dictlearn import methods
from matplotlib import pyplot as plt
from dictlearn import DictionaryLearning
from sklearn.preprocessing import normalize
from sklearn.feature_extraction.image import extract_patches_2d
from sklearn.feature_extraction.image import reconstruct_from_patches_2d

p = 8
s = 6
N = 1000
n = 256
K = 50
sigma = 0.075


def rezolvare():
    # ex1
    # a
    I = image.imread('barbara.png')

    # b
    Inoisy = I + sigma * np.random.rand(I.shape[0], I.shape[1])

    # c
    Ynoisy = extract_patches_2d(Inoisy, (p, p))
    Ynoisy = Ynoisy.reshape(Ynoisy.shape[0], -1)

    means = np.mean(Ynoisy, axis=0)
    Ynoisy -= means
    Ynoisy = Ynoisy.transpose()

    # d
    Y = Ynoisy[:,np.random.choice(Ynoisy.shape[1], N, replace=False)]

    # ex 2
    # a
    D0 = np.random.randn(Ynoisy.shape[0], n)
    D0 = normalize(D0, axis=0, norm='max')

    # b
    dl = DictionaryLearning(
        n_components=n,
        max_iter=K,
        fit_algorithm='ksvd',
        n_nonzero_coefs=s,
        code_init=D0,
        params=None,
        data_sklearn_compat=False
    )

    dl.fit(Y)
    D = dl.D_

    # 3
    # a
    Xc, err = methods.omp(Y, D, n_nonzero_coefs=s)
    print(Xc.shape)
    print(D.shape)
    Yc += means

    Ic = reconstruct_from_patches_2d(Yc, (255, 255))
    plt.imshow(Ic)
    plt.show()

# 4
# b
def psnr(img1, img2):
    mse = np.mean((img1 - img2) ** 2)
    if (mse == 0):
        return 0
    max_pixel = 255
    psnr = 20 * np.log10(max_pixel / np.sqrt(mse))
    return psnr


if __name__ == '__main__':
    rezolvare()
