from load_image import load_image
from save_image import save_image
from rotate_image import rotate_image
from show_image import show_image
from resize_image import resize_image
from image_filter import image_filter
from image_mirror import image_mirror
from collage import collage

img = load_image("image.png")
img2 = load_image("image2.jpeg")
img3 = load_image("image3.jpg")
img4 = load_image("my_img.png")

aux = collage([[img3], [img2]])
# print(img4)
# print("\n\n")
# print(aux)
aux1 = collage([[aux, img]])
show_image(aux1)