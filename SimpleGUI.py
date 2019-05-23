import os
import sys
import os
import binascii
import base64
import hashlib
from Crypto.Cipher import *

def toBytes(data) :
	return str(data).encode()

def SHA256(SID) :
	my_bytes = toBytes(SID)
	return str(hashlib.sha256(my_bytes).hexdigest().upper())

# Smart Wallet UI
from tkinter import *

# key down function
def click():
	entered_text=textentry.get() #this will collect the text from the text entry box
	output.delete(0.0, END) # clear box
	hash = SHA256(entered_text)
	output.insert(END, hash)


#### main:
window = Tk()
window.title("My Smart Wallet UI")
window.configure(background="black")

# create label
Label (window, text=" Enter your SID: ", bg="black", fg="white", font="none 12 bold") .grid(row=1, column=0, stick=W)

# create text entry box
textentry = Entry(window, width=20, bg="white")
textentry.grid(row=2, column=0, sticky=W)

# add a submit button
Button(window, text="Generate Hash", width=12, command=click) .grid(row=3, column=0, sticky=W)

# create another label
Label(window, text="\nSHA-256 Hash:", bg="black", fg="white", font="none 12 bold") .grid(row=4, column=0, sticky=W)

# create text box
output = Text(window, width=75, height=3, background="white")
output.grid(row=5, column=0, columnspan=2, sticky=W)

##### run the main loop
window.mainloop()