from PIL import Image

def get_pixel_color(image_path):
    try:
        image = Image.open(image_path)
        if image.mode != 'RGB':
            image = image.convert('RGB')

        pixel_color = image.getpixel((1,1))

        return pixel_color

    except Exception as e:
        print(f'Error: {e}')
        return None

image_path = 'waccuse.png'

color = get_pixel_color(image_path)

if color:
    print(color)
else:
    print("el color es 0 o devolvio error?")



