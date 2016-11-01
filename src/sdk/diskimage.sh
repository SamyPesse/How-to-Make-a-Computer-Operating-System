#!/bin/bash
rm c.img
qemu-img create c.img 2M
fdisk ./c.img  << EOF
x
c
16
h
16
s
16
n
p
1
1
4095
a
1
w
EOF
fdisk -l -u ./c.img
losetup -o 512 /dev/loop1 ./c.img

mke2fs -t ext2 /dev/loop1
mount  /dev/loop1 /mnt/
cp -R bootdisk/* /mnt/
umount /mnt/
grub --device-map=/dev/null << EOF
device (hd0) ./c.img
geometry (hd0) 4 16 63
root (hd0,0)
setup (hd0)
quit
EOF

losetup -d /dev/loop1
