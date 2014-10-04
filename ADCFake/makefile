F_CPU = 16000000

default:
	avr-gcc -fdiagnostics-color=always -mmcu=atmega2560 -DF_CPU=$(F_CPU) -o test.elf main.c SPI.c ADC.c usart.c
	avr-objcopy -O ihex test.elf test.hex
	avr-size test.elf

clean:
	rm -rf *.elf *.o *.hex

download_mac:
	#may need to change /dev/tty to correct port on your computer
	avrdude -p m328p -P /dev/tty.usbmodem1411 -c arduino -F -u -U flash:w:test.hex

d:
	#may need to change /dev/tty to correct port on your computer
	avrdude -p atmega2560 -P /dev/ttyACM0 -c avrispv2 -F -u -U flash:w:test.hex

download_windows:
	#may need to change COM port to correct one on your computer
	avrdude -p m328p -P com14 -c arduino -F -u -U flash:w:test.hex 
