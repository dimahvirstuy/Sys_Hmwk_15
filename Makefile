all: control.c
	gcc -g -o control control.c

run: all
	./control -c 5
	./control -v
	./control -c 4
	./control -v
	./control -r
