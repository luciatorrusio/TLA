# upload image

import numpy as np
import imutils
import cv2

import matplotlib.pyplot as plt
import matplotlib.image as mpimg

def load_image(image_path):
  img = mpimg.imread(image_path)
  return img