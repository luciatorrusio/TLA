# upload image

from load_image import load_image
from rotate_image import rotate_image
from show_image import show_image
from resize_image import resize_image

img = load_image("image.png")
resized = resize_image(img, 45)
show_image(resized)