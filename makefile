# Makefile für rechenspiel.c

.PHONY: all linux windows clean install linuxportable
all: linux windows		# Default target to build for Linux and Windows

clean:
	@echo "Cleaning up..."
	@rm -rf ./bin/ # remove the bin directory

install:	# Install the binary to /usr/local/bin (Linux only)
	@echo "Installing rechenspiel..."
	@mkdir -p /usr/local/bin
	@sudo cp ./bin/rechenspiel.bin /usr/local/bin/rechenspiel
	@sudo chmod +x /usr/local/bin/rechenspiel
	@make clean # Clean up after installation

uninstall:	# Uninstall the binary from /usr/local/bin (Linux only)
	@echo "Uninstalling rechenspiel..."
	@sudo rm -f /usr/local/bin/rechenspiel

linux: *.c
	@echo "Building for Linux x86_64..."
	@mkdir -p ./bin/
	@gcc -o ./bin/rechenspiel.bin *.c -luserInput
	@strip --strip-unneeded ./bin/rechenspiel.bin
linuxportable: libuserInput.so *.c
	@echo "Building for Linux x86_64 as portable binary..."
	@mkdir -p ./bin/
	@gcc -o ./bin/rechenspiel_portable.bin *.c -ldl -D PORTABLE
	@strip --strip-unneeded ./bin/rechenspiel_portable.bin
	@cp ./libuserInput.so ./bin/
windows: *.c
	@echo "Building for Windows x86_64..."
	@mkdir -p ./bin/
	@x86_64-w64-mingw32-gcc -o ./bin/rechenspiel.exe *.c -luserInput -L./
	@strip --strip-unneeded ./bin/rechenspiel.exe
	@cp ./libuserInput.dll ./bin/