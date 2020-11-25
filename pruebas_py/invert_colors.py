import cv2

def invert_colors(image):
    return cv2.bitwise_not(image)