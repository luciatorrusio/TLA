import numpy as np
import cv2
from matplotlib import pyplot as plt
from PIL import Image, ImageFilter

def image_filter(image_path):
    image = cv2.imread(image_path) # reads the image
    image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV) # convert to HSV
    figure_size = 9 # the dimension of the x and y axis of the kernal.
    new_image = cv2.blur(image,(figure_size, figure_size))
    return new_image
    # plt.figure(figsize=(11,6))
    # plt.subplot(121), plt.imshow(cv2.cvtColor(image, cv2.COLOR_HSV2RGB)),plt.title('Original')
    # plt.xticks([]), plt.yticks([])
    # plt.subplot(122), plt.imshow(cv2.cvtColor(new_image, cv2.COLOR_HSV2RGB)),plt.title('Mean filter')
    # plt.xticks([]), plt.yticks([])
    # plt.show()