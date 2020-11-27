# upload image

from imageLibrary import *

img = load_image("image.jpg")
img2 = load_image("image2.jpeg")
img3 = load_image("image3.jpg")
img4 = load_image("my_img.jpg")

aux = crop_image(img, 100, 500, 400, 600)
show_image(aux)