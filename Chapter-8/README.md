## Chapter 8: Memory management: physical and virtual

In the chapter related to the GDT, we saw that using segmentation a physical memory address is calculated using a segment selector and an offset.

In this chapter, we are going to implement paging, paging will translate a linear address from segmentation into a physical address.

#### Why do we need paging?

Paging will allow our kernel to:

* use the hard-drive as a memory and not be limited by the machine ram memory limit
* to have a unique memory space for each task
* to allow and unallow memory space in a dynamic way


<table><tr><td><a href="../Chapter-7/README.md" >&larr; Previous</a></td><td><a href="../Chapter-9/README.md" >Next &rarr;</a></td></tr></table>
