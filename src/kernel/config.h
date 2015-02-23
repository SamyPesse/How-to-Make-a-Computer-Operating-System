#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_NAME		"devos"		/* kernel name */
#define KERNEL_VERSION	"1"		/* kernel version */
#define KERNEL_DATE		__DATE__
#define KERNEL_TIME		__TIME__
#define KERNEL_LICENCE	"Apache License"	/* license */
#define KERNEL_COMPUTERNAME	"test-pc"	/* default name for the machine */

/* identifiant du processeur */
#ifdef __x86__
#define KERNEL_PROCESSOR_IDENTIFIER "x86"
#else
#define KERNEL_PROCESSOR_IDENTIFIER "(null)"
#endif

/* max open file */
#define CONFIG_MAX_FILE	32

#endif
