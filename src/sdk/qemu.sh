#!/bin/bash
qemu-system-i386 -m 512 -s -hda ./c.img  -curses -serial /dev/tty  -redir tcp:2323::23
