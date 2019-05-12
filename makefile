# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

all: client server

client:
	$(CC) $(CFLAGS) -o client main.cpp

server:
	$(CC) $(CFLAGS) -o server server.cpp

clean:
	$(RM) client server