import numpy as np
import imutils
import cv2

import matplotlib.pyplot as plt
import matplotlib.image as mpimg

def save_image(image_path, img, cmap=None):
  mpimg.imsave(image_path, img, cmap=cmap)
  return