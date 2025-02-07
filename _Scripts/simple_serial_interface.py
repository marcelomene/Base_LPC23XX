#author: Marcelo Menezes
#Created: 22/12/2017

#Read and write from Serial port

import sys
import time
from serial import *

if __name__ == '__main__':
	comPort = None
	baudRate = None

	if len(sys.argv) < 2:
		print "Enter COM number:"
		com = raw_input()
		if com.isdigit():
			comPort = "COM" + com
		print "Enter baudRate:"
		baud = raw_input()
		if baud.isdigit():
			baudRate = int(baud)
	else:
		com = str(sys.argv[1])
		comPort = "COM" + com
		baudRate = str(sys.argv[2])
		
	ser = Serial( port = comPort, baudrate = baudRate, parity = PARITY_ODD, stopbits = STOPBITS_TWO, bytesize=SEVENBITS )
	
	#ser.open()
	
	if ser.isOpen():
		
		print "Reading data from port forever..."
		while True:
			data = ser.read()
			print data,			
			
		