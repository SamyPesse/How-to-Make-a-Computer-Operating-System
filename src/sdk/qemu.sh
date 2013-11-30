#!/bin/bash
qemu -m 1024 -s -hda ./c.img  -curses -serial /dev/tty  -redir tcp:2323::23
