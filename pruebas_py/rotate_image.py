import imutils
import cv2

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
    result = imutils.rotate_bound(image, angle)
  return result