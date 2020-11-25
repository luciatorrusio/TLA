import matplotlib.pyplot as plt
import matplotlib.image as mpimg

# show image
def show_image(image, cmap=None):
  plt.imshow(image, cmap)
  plt.show()