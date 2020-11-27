# upload image

from imageLibrary import *

img = load_image("image.jpg")
img2 = load_image("image2.jpeg")
img3 = load_image("image3.jpg")
img4 = load_image("my_img.jpg")

aux = collage([img2, img3, img4], [img4, img2])
aux = collage([aux, img])
aux = write_on_image(aux, "tremendo colageno", [500, 600], "HERSHEY DUPLEX", 5, [255, 0, 0], 2, 1)
show_image(aux)