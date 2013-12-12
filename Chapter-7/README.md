## Chapter 7: IDT and interrupts

An interrupt is a signal to the processor emitted by hardware or software indicating an event that needs immediate attention.

There are 3 types of interruptions:

- **Hardware interrupts:** are sent to the processor from an external device (keyboard, mouse, hard disk, ...). Hardware interrupts were introduced as a way to reduce wasting the processor's valuable time in polling loops, waiting for external events.
- **Software interrupts:** are initiated voluntarily by the software. It's used to manage system calls.
- **Exceptions:**  are used for errors or events occurring during program execution that are exceptional enough that they cannot be handled within the program itself (division by zero, page fault, ...)

#### The keyboard example:

When the user pressed a key on the keyboard, the keyboard controller will signal an interrupt to the Interrupt Controller. If the interrupt is not masked, the controller signal the interrupt to the processor, the processor will execute a routine to manage the interrupt (key pressed or key released), this routine could for example get the pressed key from the keyboard controller and print the key to the screen. Once the character processing routine is completed, the interrupted job can be resumed.

#### What is the PIC?

The [PIC](http://en.wikipedia.org/wiki/Programmable_Interrupt_Controller) (Programmable interrupt controller)is a device that is used to combine several sources of interrupt onto one or more CPU lines, while allowing priority levels to be assigned to its interrupt outputs. When the device has multiple interrupt outputs to assert, it asserts them in the order of their relative priority.

The best known PIC is the 8259A, each 8259A can handle 8 devices but most computers have two controllers: one master and one slave, it's allow the computer to manager interrupts from 14 devices.

In this chapter, we will need to program this controller to initialize it and mask interrupts.

#### What is the IDT?

> The Interrupt Descriptor Table (IDT) is a data structure used by the x86 architecture to implement an interrupt vector table. The IDT is used by the processor to determine the correct response to interrupts and exceptions.

Our kernel is going to use the IDT to define the different functions to be executed when an interrupt occurred.

Like the GDT, the IDT is loaded using the LIDTL assembly instruction. It expects the location of a IDT description structure:

```cpp
struct idtr {
	u16 limite;
	u32 base;
} __attribute__ ((packed));
```

The IDT table is composed of IDT segments with the following structure:

```cpp
struct idtdesc {
	u16 offset0_15;
	u16 select;
	u16 type;
	u16 offset16_31;
} __attribute__ ((packed));
```

**Caution:** the directive ```__attribute__ ((packed))``` signal to gcc that the structure should use as little memory as possible. Without this directive, gcc include some bytes to optimize the memory alignment and the access during execution.

Now we need to define our IDT table and then load it using LIDTL. The IDT table can be stored wherever we want in memory, its address should just be signaled to the process using the IDTR registry.

Here is a table of common interrupts (Maskable hardware interrupt are called IRQ):


| IRQ   |         Description        |
|:-----:| -------------------------- |
| 0 | Programmable Interrupt Timer Interrupt | 
| 1 | Keyboard Interrupt | 
| 2 | Cascade (used internally by the two PICs. never raised) | 
| 3 | COM2 (if enabled) | 
| 4 | COM1 (if enabled) | 
| 5 | LPT2 (if enabled) | 
| 6 | Floppy Disk | 
| 7 | LPT1 | 
| 8 | CMOS real-time clock (if enabled) | 
| 9 | Free for peripherals / legacy SCSI / NIC | 
| 10 | Free for peripherals / SCSI / NIC | 
| 11 | Free for peripherals / SCSI / NIC | 
| 12 | PS2 Mouse | 
| 13 | FPU / Coprocessor / Inter-processor | 
| 14 | Primary ATA Hard Disk | 
| 15 | Secondary ATA Hard Disk | 


<table><tr><td><a href="../Chapter-6/README.md" >&larr; Previous</a></td><td>Next &rarr;</td></tr></table>