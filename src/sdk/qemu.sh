#!/bin/bash
qemu-system-i386 -m 1024 -hda ./c.img  -curses -serial /dev/tty -redir tcp:2323::23 -gdb tcp::1234
