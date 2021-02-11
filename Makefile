cc = gcc
cflags = -ansi -Wpedantic -Os


buildDir = bin


all: client-bin

client-bin:
	gcc src/*.c $(cflags) -Iinclude -o $(buildDir)/ezonic
