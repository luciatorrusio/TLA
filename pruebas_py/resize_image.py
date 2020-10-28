from PIL import Image
import cv2
import numpy as np
from converters import PILtoCV2, CV2toPIL

def resize_image(image, pixels):
    basewidth = pixels
    img_pil = CV2toPIL(image)
    wpercent = (basewidth/float(img_pil.size[0]))
    hsize = int((float(img_pil.size[1])*float(wpercent)))
    img_pil = img_pil.resize((basewidth,hsize), Image.ANTIALIAS) 
    return PILtoCV2(img_pil)


    # https://stackoverflow.com/questions/43232813/convert-opencv-image-format-to-pil-image-format