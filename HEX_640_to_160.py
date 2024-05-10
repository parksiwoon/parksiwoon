#!/usr/bin/env python
# coding: utf-8
#

# In[20]:


pip install intelhex


# In[22]:


pip install pillow


# In[29]:


import binascii
import re

def update_image_size_in_ihdr(image_hex_data, new_width, new_height):
    # Convert width and height to hex, 4 bytes each
    width_hex = f'{new_width:08X}'
    height_hex = f'{new_height:08X}'
    # Find the IHDR position (assuming it starts after the first ':')
    ihdr_pos = image_hex_data.find('49484452')  # 'IHDR' in hex
    if ihdr_pos != -1:
        # Replace the width and height in the IHDR chunk
        new_ihdr_data = (
            image_hex_data[:ihdr_pos+8] + # IHDR start
            width_hex + height_hex + # New width and height
            image_hex_data[ihdr_pos+24:] # Rest of the data
        )
        return new_ihdr_data
    else:
        return image_hex_data

def crop_hex_image(input_hex_path, output_hex_path, width, original_height, new_height):
    # Open the original hex file to read
    with open(input_hex_path, 'r') as file:
        hex_lines = file.readlines()
    
    # Extract all the hex data
    hex_data = ''.join(re.findall(r':[0-9A-F]{2}([0-9A-F]+)', ''.join(hex_lines)))

    # Update the IHDR with the new image size
    updated_hex_data = update_image_size_in_ihdr(hex_data, width, new_height)

    # Decode the hex to bytes
    image_bytes = binascii.unhexlify(updated_hex_data)

    # Assuming PNG RGBA (4 bytes per pixel), calculate the number of bytes per row
    bytes_per_row = width * 4
    # Select only the bytes for the top `new_height` rows
    cropped_bytes = image_bytes[:bytes_per_row * new_height]

    # Convert bytes back to hex
    cropped_hex = binascii.hexlify(cropped_bytes).upper().decode('utf-8')

    # Write to new hex file
    with open(output_hex_path, 'w') as out_file:
        # Split the long hex string into lines for readability (optional)
        for i in range(0, len(cropped_hex), 32):  # 32 characters per line
            out_file.write(':20' + cropped_hex[i:i+32] + '\n')

# Define paths and parameters
input_hex_path = "C:\\a.jobdongsani\\image_rgba.hex"
output_hex_path = "C:\\a.jobdongsani\\cropped_image_rgba.hex"
width = 960
original_height = 640
new_height = 160

# Crop the image
crop_hex_image(input_hex_path, output_hex_path, width, original_height, new_height)


# In[ ]:




