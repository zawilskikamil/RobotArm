import serial_service
from tkinter import *

OPTIONS = serial_service.serial_ports()

master = Tk()

variable = StringVar(master)
variable.set(OPTIONS[0]) # default value

w = OptionMenu(master, variable, *OPTIONS)
w.pack()
x = Scale(master, from_=0, to=360, orient=HORIZONTAL)
x.pack()
y = Scale(master, from_=0, to=200, orient=HORIZONTAL)
y.pack()
z = Scale(master, from_=0, to=200, orient=HORIZONTAL)
z.pack()

def ok():
    print ("value is:" + variable.get())
    print (x.get(), y.get(), z.get())
    serial_service.lisen(variable.get(), print)

button = Button(master, text="OK", command=ok)
button.pack()

mainloop()

