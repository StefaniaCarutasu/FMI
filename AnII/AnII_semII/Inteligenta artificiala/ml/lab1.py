import numpy as np
from skimage import io

# a
img = np.zeros((9, 400, 600))
for i in range(0, 9):
    img[i] = np.load(f'masini/car_{i}.npy')
"""
print(img)

# b
print(np.sum(img))
"""
# c
sum_img = np.sum(img, axis=(1, 2))
#print(sum_img)

"""
# d
#print(np.argmax(sum_img))
"""
# e
mean_img = np.mean(img, axis=0)
# petru a putea fi afisata imaginea trebuie sa aiba tipul unsigned int
io.imshow(mean_img.astype(np.uint8))
io.show()


# f
std_img = np.std(img)
print(std_img)

# g
n_img = (img - mean_img) / std_img
print(n_img)

# h
slice_img = np.copy(img[:, 200:300, 280:400])
io.imshow(slice_img[0].astype(np.uint8))
io.show()

