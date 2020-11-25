import cv2

def image_mirror(image, axis):
    new_img = image

    if(axis == "x"):
        new_img = cv2.flip(image, 1)
    elif(axis == "y"):
        new_img = cv2.flip(image, 0)
    elif(axis == "xy" or axis == "yx"):
        new_img = cv2.flip(image, -1)
        
    return new_img