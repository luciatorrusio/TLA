from PIL import Image
import cv2
import numpy as np
def resize_image(image, pixels):
    basewidth = pixels
    img = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    im_pil = Image.fromarray(img)
    wpercent = (basewidth/float(img_pil.size[0]))
    hsize = int((float(img_pil.size[1])*float(wpercent)))
    img_pil = img_pil.resize((basewidth,hsize), Image.ANTIALIAS) 
    numpy_image=numpy.array(img_pil)  
    opencv_image=cv2.cvtColor(numpy_image, cv2.COLOR_RGB2BGR)
    return opencv_image


    # https://stackoverflow.com/questions/43232813/convert-opencv-image-format-to-pil-image-format