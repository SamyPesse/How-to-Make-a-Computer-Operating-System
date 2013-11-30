

#ifndef _SYS_MOUNT_H_
#define _SYS_MOUNT_H_

#define MOUNT_NONE      0
#define MOUNT_RO        1
#define MOUNT_NOATIME   2

int mount(
    const char* source,
    const char* target,
    const char* filesystemtype,
    unsigned long mountflags,
    const void* data
);

int umount(
    const char* dir
);

#endif /* _SYS_MOUNT_H_ */
