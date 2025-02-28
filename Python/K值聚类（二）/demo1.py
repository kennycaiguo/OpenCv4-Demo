# OpenCv版本：opencv-python 4.6.0.66
# 内容：K值聚类（二）
# 博客：http://www.bilibili996.com/Course?id=fcd7745b72f4493f81683b2e3e80f911
# 作者：高仁宝
# 时间：2023.11

import numpy as np
import cv2

img = cv2.imread('../images/fruits.jpg')
# img = cv2.imread('../data/opencv_logo.png')
Z = img.reshape((-1, 3))
# convert to np.float32
Z = np.float32(Z)


# define criteria, number of clusters(K) and apply kmeans()
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)
# K = 8
# K = 3
K = 14
ret, label, center = cv2.kmeans(Z, K, None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)


# Now convert back into uint8, and make original image
center = np.uint8(center)
res = center[label.flatten()]
res2 = res.reshape((img.shape))

cv2.imshow('res2', res2)
cv2.waitKey(0)
cv2.destroyAllWindows()
