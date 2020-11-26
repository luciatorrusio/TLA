import matplotlib.pyplot as plt
import matplotlib.image as mpimg

# show image
def show_image(image):
  plt.imshow(image)
  plt.show()

def show_image_cmap(image, cmap):
  plt.imshow(image, cmap=cmap)
  plt.show()