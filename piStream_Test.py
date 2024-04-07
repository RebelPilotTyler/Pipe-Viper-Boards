# piStream_Test, a program for testing streaming video from a raspberry pi to a computer.
# This program is for THE RASPBERRY PI
# To use, be sure the IP Address is the same, and both devices are connected to the same network.
# Written by Tyler Widener, tylerwidenerlm@gmail.com
# YouTube tutorial used: https://www.youtube.com/watch?v=bWwZF_zVf00

# Libraries
import io
import socket
import struct
import time
import picamera #FIXME Requires picamera library available through a Raspberry Pi

# Initializations
clientSocket = socket.socket()
clientSocket.connect(('IP ADDRESS HERE', 8000))

# Main
connection = clientSocket.makefile('wb')
try:
    camera = picamera.PiCamera()
    camera.vflip = True
    camera.resolution = (500, 480)
    camera.start_preview()
    time.sleep(2)

    start = time.time()
    stream = io.BytesIO()
    for foo in camera.capture_continuous(stream, 'jpeg'):
        connection.write(struct.pack('<L', stream.tell()))
        connection.flush()
        stream.seek(0)

        if time.time() - start > 60:
            break

        stream.seek(0)
        stream.truncate()
    connection.write(struct.pack('<L', 0))
finally:
    connection.close()
    clientSocket.close()