
#ifndef KERNEL_H
#define KERNEL_H

#include <runtime/alloc.h>
#include <runtime/libc.h>
#include <runtime/string.h>


#include <core/file.h>
#include <core/filesystem.h>
#include <core/elf_loader.h>
#include <core/syscalls.h>
#include <core/env.h>
#include <core/user.h>
#include <core/modulelink.h>
#include <core/device.h>
#include <core/socket.h>
#include <core/system.h>


#include <module.h>


#include <io.h>
#include <architecture.h>
#include <vmm.h>
#include <process.h>

#endif
