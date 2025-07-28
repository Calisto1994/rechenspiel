# Makefile für rechenspiel.c

.PHONY: all linux windows clean install
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

linux: rechenspiel.c setlocale_unices.c
	@echo "Building for Linux x86_64..."
	@mkdir -p ./bin/
	@gcc -o ./bin/rechenspiel.bin rechenspiel.c setlocale_unices.c
	@strip --strip-unneeded ./bin/rechenspiel.bin
windows: rechenspiel.c setlocale_win.c
	@echo "Building for Windows x86_64..."
	@mkdir -p ./bin/
	@x86_64-w64-mingw32-gcc -o ./bin/rechenspiel.exe rechenspiel.c setlocale_win.c
	@strip --strip-unneeded ./bin/rechenspiel.exe