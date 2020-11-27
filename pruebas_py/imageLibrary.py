import numpy as np
import cv2
import imutils
import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import sys

# TODO: se pueden declarar funciones privadas?

# =========================== COLLAGE ===========================
def vconcat_resize_min(im_list, interpolation=cv2.INTER_CUBIC):
    w_min = min(im.shape[1] for im in im_list)
    im_list_resize = [cv2.resize(im, (w_min, int(im.shape[0] * w_min / im.shape[1])), interpolation=interpolation)
                      for im in im_list]
    return cv2.vconcat(im_list_resize)

def hconcat_resize_min(im_list, interpolation=cv2.INTER_CUBIC):
    h_min = min(im.shape[0] for im in im_list)
    im_list_resize = [cv2.resize(im, (int(im.shape[1] * h_min / im.shape[0]), h_min), interpolation=interpolation)
                      for im in im_list]
    return cv2.hconcat(im_list_resize)

def concat_tile_resize(im_list_2d, interpolation=cv2.INTER_CUBIC):
    im_list_v = [hconcat_resize_min(im_list_h, interpolation=cv2.INTER_CUBIC) for im_list_h in im_list_2d]
    return vconcat_resize_min(im_list_v, interpolation=cv2.INTER_CUBIC)

def collage(*images_arrays):
    return concat_tile_resize(images_arrays)

# =========================== GRAY SCALE IMAGE ===========================
def gray_scale_image(image):
    return cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# =========================== IMAGE MIRROR ===========================
def image_mirror(image, axis):
    new_img = image

    if(axis == "x"):
        new_img = cv2.flip(image, 1)
    elif(axis == "y"):
        new_img = cv2.flip(image, 0)
    elif(axis == "xy" or axis == "yx"):
        new_img = cv2.flip(image, -1)
        
    return new_img

# =========================== INVERT COLORS ===========================
def invert_colors(image):
    return cv2.bitwise_not(image)

# =========================== LOAD IMAGE ===========================
def load_image(image_path):
  img = mpimg.imread(image_path)
  return img

# =========================== RESIZE IMAGE ===========================
def resize_image(image, percentage):

    #calculate the percent of original dimensions
    width = int(image.shape[1] * percentage)
    height = int(image.shape[0] * percentage)

    # dsize
    dsize = (width, height)

    # resize image
    return cv2.resize(image, dsize)

# =========================== ROTATE IMAGE ===========================
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

# =========================== WRITE ON IMAGE ===========================
def write_on_image(img, text, cords, font, fontScale, color, thickness, orientation):
  org = (cords[0], cords[1])
  available_fonts = {
    "HERSHEY SIMPLEX": cv2.FONT_HERSHEY_SIMPLEX,
    "HERSHEY PLAIN": cv2.FONT_HERSHEY_PLAIN,
    "HERSHEY DUPLEX": cv2.FONT_HERSHEY_DUPLEX,
    "HERSHEY COMPLEX": cv2.FONT_HERSHEY_COMPLEX,
    "HERSHEY TRIPLEX": cv2.FONT_HERSHEY_TRIPLEX,
    "HERSHEY COMPLEX SMALL": cv2.FONT_HERSHEY_COMPLEX_SMALL,
    "HERSHEY SCRIPT SIMPLEX": cv2.FONT_HERSHEY_SCRIPT_SIMPLEX,
    "HERSHEY SCRIPT COMPLEX": cv2.FONT_HERSHEY_SCRIPT_COMPLEX
  }
  try:
    choosed_font = available_fonts[font]
  except:
    print("Font", font, "not found: applying HERSHEY SIMPLEX", file=sys.stderr)
    choosed_font = available_fonts["HERSHEY SIMPLEX"]
  
  color_bgr = (color[0], color[1], color[2])

  orient = False
  if(orientation < 0):
    orient = True

  return cv2.putText(img, text, org, choosed_font, fontScale, color_bgr, thickness, cv2.LINE_AA, orient)

# =========================== CROP IMAGE ===========================
def crop_image(img, x1, x2, y1, y2):
  return img[y1:y2, x1:x2]

# =========================== SAVE IMAGE ===========================
def save_image(image_path, img):
  mpimg.imsave(image_path, img)
  return

def save_image_cmap(image_path, img, cmap):
  mpimg.imsave(image_path, img, cmap=cmap)
  return

# =========================== SHOW IMAGE ===========================
def show_image(image):
  plt.imshow(image)
  plt.show()

def show_image_cmap(image, cmap):
  plt.imshow(image, cmap=cmap)
  plt.show() 

# =========================== SUBSTRING ===========================
def substring(str, start, end):
    length = len(str)
    if(start < 0):
        start = 0
    if(end > length):
        end = length
    if(start > length or start > end):
        return ""
    return str[start:end+1]