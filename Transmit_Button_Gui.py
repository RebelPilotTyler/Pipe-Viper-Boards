import serial
import time
import serial.tools.list_ports
import tkinter as tk
from tkinter import scrolledtext

# Function to find the Arduino's COM port
def find_arduino_port():
    arduino_ports = [p.device for p in serial.tools.list_ports.comports() if 'USB Serial Port' in p.description]
    if arduino_ports:
        return arduino_ports[0]  # Assume the first Arduino found is the one to connect to
    else:
        return None


# Function to send a command to the Arduino
def send_command(command):
    ser.write(command.encode())
    log_message(f"Sent command: {command}")

# Function to log messages to the terminal
def log_message(message):
    terminal.insert(tk.END, message + "\n")
    terminal.see(tk.END)

# Function to handle the button click event
def execute_command():
    user_input = command_entry.get().strip()
    if user_input.lower() == 'q':
        root.quit()
    else:
        send_command(user_input)

# Create the main application window
root = tk.Tk()
root.title("Arduino Control GUI")

# Create a text widget for the terminal-like display
terminal = scrolledtext.ScrolledText(root, wrap=tk.WORD, width=40, height=20)
terminal.pack()

# Create an entry widget for entering commands
command_entry = tk.Entry(root, width=40)
command_entry.pack()

# Create a button to execute commands
execute_button = tk.Button(root, text="Execute Command", command=execute_command)
execute_button.pack()

# Find the Arduino's COM port
arduino_port = find_arduino_port()

if arduino_port is None:
    log_message("Arduino not found. Please make sure it's connected.")
else:
    # Initialize the serial connection
    ser = serial.Serial(arduino_port, 115200)  # 9600 is the default baud rate, change if needed (changed to 115200)
    time.sleep(2)  # Allow time for the serial connection to initialize
    log_message(f"Connected to Arduino on {arduino_port}")

# Start the GUI main loop
root.mainloop()

# Close the serial connection when done
if arduino_port is not None:
    ser.close()
