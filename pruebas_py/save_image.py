import numpy as np
import imutils
import cv2

import matplotlib.pyplot as plt
import matplotlib.image as mpimg

def save_image(image_path, img):
  mpimg.imsave(image_path, img)
  return

def save_image_cmap(image_path, img, cmap):
  mpimg.imsave(image_path, img, cmap=cmap)
  return