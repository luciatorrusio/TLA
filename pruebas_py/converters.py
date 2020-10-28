import cv2
import numpy as np
from PIL import Image

def CV2toPIL(cv2_image):
  # convert from openCV2 to PIL. Notice the COLOR_BGR2RGB which means that 
  # the color is converted from BGR to RGB
  cv2_image = cv2.cvtColor(cv2_image, cv2.COLOR_BGR2RGB)
  print(cv2_image.shape)
  # Doing this is grayscaling the image. TODO: Fix this
  cv2_image = cv2_image[:, :, 0] 
  print(cv2_image.shape)
  pil_image = Image.fromarray(cv2_image)
  return pil_image

def PILtoCV2(pil_image):
  # use numpy to convert the pil_image into a numpy array
  numpy_image=np.array(pil_image)  
  # convert to a openCV2 image, notice the COLOR_RGB2BGR which means that 
  # the color is converted from RGB to BGR format
  opencv_image=cv2.cvtColor(numpy_image, cv2.COLOR_RGB2BGR)
  return opencv_image
