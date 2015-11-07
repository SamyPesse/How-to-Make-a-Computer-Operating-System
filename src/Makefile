SDKDIR=./sdk

help:
	@echo "Makefile for Building Dev Operating System."
	@echo "Usage: make [ all | clean | help | build | run] " 
	@echo ""
	@echo

all: 
	@echo "Building Kernel"
	make -C ./kernel
	@echo "Building SDK"
	make -C ./sdk
	@echo "Building Userland"
	make -C ./userland
	if [ "$(grep -Ei 'debian|buntu|mint' /etc/*release)" ]; then
	@echo "Update/Upgrade system. Install basic software"
	sudo apt-get update
	sudo apt-get upgrade
	sudo apt-get install make
	sudo apt-get install nasm
	sudo apt-get install g++
	sudo apt-get install grub
	sudo apt-get install qemu
	fi

build:
	zip -r devos-$(VERSION).zip ./


run:
	@echo "Running Dev Operating System."
	cd ./sdk && sudo bash ./diskimage.sh
	cd ./sdk && ./qemu.sh

clean:
	make -C ./kernel clean
	make -C ./userland clean
