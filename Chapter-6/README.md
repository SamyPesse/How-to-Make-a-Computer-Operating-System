## Chapter 6: GDT

Thanks to GRUB, your kernel is no more in real-mode, but already in [protected mode](http://en.wikipedia.org/wiki/Protected_mode), this mode allows us to use all the possibilities of the microprocessor such as virtual memory management, paging and safe multi-tasking.

#### What is the GDT?

The [GDT](http://en.wikipedia.org/wiki/Global_Descriptor_Table) ("Global Descriptor Table") is a data structure used to define the different memory area: the base address, the size and access privileges like executability and writability.

These memory areas are called "segments".

We are going to use the GDT to define differents memory segments:

* *"code"*: kernel code, used to stored the executable binary code
* *"data"*: kernel data
* *"stack"*: kernel stack, used to stored the call stack during kernel execution
* *"ucode"*: user code, used to stored the executable binary code for user program
* *"udata"*: user program data
* *"ustack"*: user stack, used to stored the call stack during execution in userland

#### How to load our GDT?

The GDT is loaded using the LGDT assembly instruction. It expects the location of a GDT description structure:

![test](http://wiki.osdev.org/images/7/77/Gdtr.png)

And the C structure:

```cpp
struct gdtr {
	u16 limite;
	u32 base;
} __attribute__ ((packed));
```

**Caution:** the directive ```__attribute__ ((packed))``` signal to gcc that the structure should use the less memory possible. Without this directive, gcc include some bytes to optimize the memory alignment and the access during execution.

So we need to define our GDT and load it using LGDT.




