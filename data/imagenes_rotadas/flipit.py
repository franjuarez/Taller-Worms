from PIL import Image, ImageDraw
import math

# Function to rotate and save the image with a transparent or solid white background
def rotate_and_save_with_transparent_background(image, angle, output_path):
    rotated_image = image.rotate(math.degrees(angle), expand=True)

    # Create a new image with a transparent or white background
    new_image = Image.new("RGBA", rotated_image.size, (255, 255, 0))

# from PIL import Image

# image = Image.open("your_image.png")
# image = image.convert("RGBA")


    # Paste the rotated image onto the new image
    new_image.paste(rotated_image, (0, 0), rotated_image)

    new_image.save(output_path)

# Load the input PNG image
input_image_path = '../bloque_poc.png'
image = Image.open(input_image_path)
image = image.convert("RGBA")

# Define the rotation angles (0 to 2*pi in steps of 1 degree)
rotation_angles = [i* math.pi / 180 for i in range(101)]  # 0 to 2*pi in radians with 1-degree steps

# Rotate and save the images
for i, angle in enumerate(rotation_angles):
    output_path = f'output_{i}.png'
    rotate_and_save_with_transparent_background(image, angle, output_path)
