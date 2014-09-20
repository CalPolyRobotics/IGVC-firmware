all : libcaddyControl.a main.o
	g++ main.o -o main -lcaddyControl
rs232.o : rs232.c
	g++ -c -o $@ $< -g
SerialComms.o : SerialComms.cpp
	g++ -c -o $@ $< -g
main.o : main.cpp
	g++ -c -o $@ $< -g
CaddyBoardControl.o : CaddyBoardControl.cpp
	g++ -c -o $@ $< -g

libcaddyControl.a : SerialComms.o rs232.o CaddyBoardControl.o
	ar rcs libcaddyControl.a SerialComms.o rs232.o CaddyBoardControl.o

lib : libcaddyControl.a

install:
	cp libcaddyControl.a /usr/lib/libcaddyControl.a
	cp CaddyBoardControl.h /usr/include/CaddyBoardControl.h

clean:
	rm *.o
	rm *.a
