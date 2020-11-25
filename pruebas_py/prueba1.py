# upload image

from load_image import load_image
from save_image import save_image
from rotate_image import rotate_image
from show_image import show_image
from resize_image import resize_image
from image_filter import image_filter
from image_mirror import image_mirror
from collage import collage
from invert_colors import invert_colors
from gray_scale_image import gray_scale_image

img = load_image("image.jpg")
img2 = load_image("image2.jpeg")
img3 = load_image("image3.jpg")
img4 = load_image("my_img.jpg")

aux = resize_image(img, 1.5)
aux = gray_scale_image(aux)
show_image(aux, 'gray')
save_image("gray.jpg", aux, 'gray')