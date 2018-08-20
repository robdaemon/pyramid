.PHONY: all clean

all: pyramid.prg

clean:
	del pyramid.prg

pyramid.prg: pyramid.c
	vc +tos pyramid.c -o pyramid.prg -lm