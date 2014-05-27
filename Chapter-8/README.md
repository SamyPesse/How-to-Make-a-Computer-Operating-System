## Chapter 8: Memory management: physical and virtual

In the chapter related to the GDT, we saw that using segmentation a physical memory address is calculated using a segment selector and an offset.

In this chapter, we are going to implement paging, paging will translate a linear address from segmentation into a physical address.

#### Why do we need paging?

Paging will allow our kernel to:

* use the hard-drive as a memory and not be limited by the machine ram memory limit
* to have a unique memory space for each process
* to allow and unallow memory space in a dynamic way

In a paged system, each process may execute in its own 4gb area of memory, without any chance of effecting any other process's memory, or the kernel's. It simplifies multitasking.

![Processes memories](./processes.png)

#### How does it work?

The translation of a linear address to a physical address is done in multiple steps:

1. The processor use the registry `CR3` to know the physical address of the pages directory.
2. The first 10 bytes of the linear address represent an offset (between 0 and 1023), pointing to an entry in the pages directory. This entry contains the physical address of a pages table.
3. the next 10 bytes of the linear address represent an offset, pointing to an entry in the pages table. This entry is pointing to a 4ko page.
4. The last 12 bytes of the linear address represent an offset (between 0 and 4095), which indicates the position in the 4ko page.

![Address translation](./paging_memory.png)

#### Format for pages table and directory

The two types of entries (table and directory) look like the same. Only the field in gray will be used in our OS.

![Page directory entry](./page_directory_entry.png)

![Page table entry](./page_table_entry.png)

* `P`: indicate if the page or table is in physical memory
* `R/W`: indicate if the page or table is accessible in writting (equals 1)
* `U/S`: equals 1 to allow access to non-preferred tasks
* `A`: indicate if the page or table was accessed
* `D`: (only for pages table) indicate if the page was written
* `PS` (only for pages directory) indicate the size of pages:
    * 0 = 4ko
    * 1 = 4mo


