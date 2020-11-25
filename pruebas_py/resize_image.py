import cv2

def resize_image(image, percentage):

    #calculate the 50 percent of original dimensions
    width = int(image.shape[1] * percentage)
    height = int(image.shape[0] * percentage)

    # dsize
    dsize = (width, height)

    # resize image
    return cv2.resize(image, dsize)