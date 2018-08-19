.PHONY: all

all: pyramid.prg

pyramid.prg: pyramid.c
	vc +tos pyramid.c -o pyramid.prg -lm