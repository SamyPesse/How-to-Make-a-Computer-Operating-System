#!/bin/bash

# I added some delays and some root functions.
qemu-img create c.img 2M
sleep 1s
fdisk ./c.img  << EOF
x
c
4
h
16
s
63
r
n
p
1
1
4
a
1
w
EOF
sleep 1s
fdisk -l -u ./c.img
sleep 3s
sudo losetup -o 32256 /dev/loop1 ./c.img
sleep 3s
sudo mke2fs /dev/loop1
sleep 1s
sudo mount  /dev/loop1 /mnt/
sleep 1s
sudo cp -R bootdisk/* /mnt/
sleep 1s
sudo umount /mnt/
sleep 1s
sudo grub --device-map=/dev/null << EOF
device (hd0) ./c.img
geometry (hd0) 4 16 63
root (hd0,0)
setup (hd0)
quit
EOF
sleep 1s
sudo losetup -d /dev/loop1
