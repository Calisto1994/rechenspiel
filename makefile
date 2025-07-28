# Makefile für rechenspiel.c

.PHONY: all linux windows clean install
all: linux windows		# Default target to build for Linux and Windows

clean:
	rm -rf ./bin/ # remove the bin directory

install:	# Install the binary to /usr/local/bin (Linux only)
	mkdir -p /usr/local/bin
	cp ./bin/rechenspiel.bin /usr/local/bin/rechenspiel
	chmod +x /usr/local/bin/rechenspiel
	make clean # Clean up after installation

uninstall:	# Uninstall the binary from /usr/local/bin (Linux only)
	rm -f /usr/local/bin/rechenspiel

linux: rechenspiel.c
	mkdir -p ./bin/
	gcc -o ./bin/rechenspiel.bin rechenspiel.c
win64: rechenspiel.c
	mkdir -p ./bin/
	x86_64-w64-mingw32-gcc -o ./bin/rechenspiel.exe rechenspiel.c