# computerStream_Test, a program for testing streaming video from a raspberry pi to a computer.
# This program is for THE COMPUTER
# To use, be sure the IP Address is the same, and both devices are connected to the same network.
# Written by Tyler Widener, tylerwidenerlm@gmail.com
# YouTube tutorial used: https://www.youtube.com/watch?v=bWwZF_zVf00

# Libraries
import io # Input and output
import socket # For server stuff
import struct 
from PIL import Image # For image processing
import matplotlib.pyplot as pl # For displaying the image

# Initialization
serverSocket = socket.socket()
serverSocket.bind(('172.17.1.82', 8000))
serverSocket.listen(3)

# Main
connection = serverSocket.accept()[0].makefile('rb') # Accept a connection, and set the mode to read bytes.
try: # Have all of the code in a try statement in case of errors.
    img = None # Create an image variable and set it to none.
    while True: # While loop for entire program.
        image_len = struct.unpack('<L', connection.read(struct.calcsize('<L')))[0] # Acquire the length of the image
        if not image_len: # If the image length cannot be acquired, break the loop and end the program
            break
        image_stream = io.BytesIO() # Create an image stream variable and set it to Bytes.
        image_stream.write(connection.read(image_len)) # Translate from bytes to the image, and put it in image_stream
        image_stream.seek(0) # Rewind to the beginning of the image data
        image = Image.open(image_stream) # Open the image
        if img is None: # Prep the image for display
            img = pl.imshow(image)
        else:
            img.set_data(image)
        pl.pause(0.01) # Display the image
        pl.draw()
        print('Image is %dx%d' % image.size) # Report the image to output
        image.verify()
        print('Image is verified')
finally: # Once the program ends, close the connection and socket
    connection.close()
    serverSocket.close()