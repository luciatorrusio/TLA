# upload image

from load_image import load_image
from rotate_image import rotate_image
from show_image import show_image

img = load_image("image.png")
rotated = rotate_image(img, 45)
show_image(rotated)