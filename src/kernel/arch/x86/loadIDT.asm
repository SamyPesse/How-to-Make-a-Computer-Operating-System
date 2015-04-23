section .text

global load_idt;

load_idt:
    cli                 ;turn off Interrupts
	mov edx, [esp + 4]
    lidt [edx]          ;load IDT
	sti 				;turn on interrupts
	ret