from PIL import Image
def resize_image(image, pixels):
    basewidth = pixels
    img = Image.open(image)
    wpercent = (basewidth/float(img.size[0]))
    hsize = int((float(img.size[1])*float(wpercent)))
    img = img.resize((basewidth,hsize), Image.ANTIALIAS)
    img.save(image) 
    return img