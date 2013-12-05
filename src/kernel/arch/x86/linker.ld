OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
ENTRY (_start)

SECTIONS{
    . = 0x00100000;

    .text :{
        *(.text)
    }

	.data ALIGN (0x1000) : {
	   start_ctors = .;
	   *(.ctor*)
	   end_ctors = .;
	   start_dtors = .;
	   *(.dtor*)
	   end_dtors = .;
	   *(.data)
	}


    .rodata ALIGN (0x1000) : {
        *(.rodata)
    }

    .data ALIGN (0x1000) : {
        *(.data)
    }

    .bss : {
        sbss = .;
        *(COMMON)
        *(.bss)
        ebss = .;
    }
}
