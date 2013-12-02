## Chapter 6: GDT

Thanks to GRUB, your kernel is no more in real-mode, but already in [protected mode](http://en.wikipedia.org/wiki/Protected_mode), this mode allows us to use all the possibilities of the microprocessor such as virtual memory management, paging and safe multi-tasking.

#### What is the GDT?

The [GDT](http://en.wikipedia.org/wiki/Global_Descriptor_Table) ("Global Descriptor Table") is a data structure used to define the different memory area: the base address, the size and access privileges like executability and writability.

These memory areas are called "segments".
