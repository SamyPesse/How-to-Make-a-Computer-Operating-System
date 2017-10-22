#!/bin/bash
qemu-img create c.img 16M
fdisk ./c.img  << EOF
n
p
1
2048
32767
a
w
EOF
kpartx -a ./c.img
echo ----------------------------------
echo Detected loop partitions:
lsblk /dev/loop0
mkfs.ext4 /dev/mapper/loop0p1
mount /dev/mapper/loop0p1 /mnt
cp -R bootdisk/* /mnt
# TODO: Install grub2
# As of now, nothing I've tried works.
# Still, the kernel sould be bootable, just not this image.
umount /mnt
kpartx -d /dev/loop0
