import numpy as np
import argparse
import imutils
import cv2

import matplotlib.pyplot as plt
import matplotlib.image as mpimg

def rotate_image(image, angle):
  angles_map = {
    90: cv2.ROTATE_90_COUNTERCLOCKWISE,
    180: cv2.ROTATE_180,
    270: cv2.ROTATE_90_CLOCKWISE
  }

  if (angle % 90 == 0):
    if (angle % 360 == 0):
      result = image
    else:
      result = cv2.rotate(image, angles_map[angle % 360])
  else:
    # image_center = tuple(np.array(image.shape[1::-1]) / 2)
    # rot_mat = cv2.getRotationMatrix2D(image_center, angle, 1.0)
    # result = cv2.warpAffine(image, rot_mat, image.shape[1::-1], flags=cv2.INTER_LINEAR)
    result = imutils.rotate_bound(image, angle)
  return result