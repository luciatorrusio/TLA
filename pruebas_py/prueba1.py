# upload image

from standardLibrary import collage, gray_scale_image, image_mirror, invert_colors, load_image, resize_image, rotate_image, write_on_image, crop_image, save_image, save_image_cmap, show_image, show_image_cmap, substring, to_int, defaultlist

img = load_image("image.jpg")
img2 = load_image("image2.jpeg")
img3 = load_image("image3.jpg")
img4 = load_image("my_img.jpg")

show_image(np.zeros((1, 1, 3)))