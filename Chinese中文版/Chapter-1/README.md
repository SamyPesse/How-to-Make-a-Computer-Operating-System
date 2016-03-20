## Chapter 1: 介紹x86架構以及我們要做的作業系統

### x86架構是什麼?

> x86一詞代表的意思是一系列基於Intel 8086 CPU的向後兼容的指令集架構

x86架構自從IBM電腦公司在1981年發表後一直佔有最廣泛被使用的指令集架構的地位。很多的軟體，包含作業系統如DOs,Windows,Linux,BSD, Solaris,還有Mac OS X，都是用x86-based的硬體

在這個課程裡，我們設計的作業系統是符合x86 32bits的架構，而不是x86 64 bits的架構。由於向後兼容的特性，我們的作業系統能夠與我們新的電腦相容(但如果你要在實體的機器上測試的話要小心)

### 我們的作業系統

目標是用C++建立一個簡單的基於UNIX的作業系統，但不僅只是建立一個用來實證觀念的作業系統。我們建立出來的作業系統必須要能夠開機，啟動一個應用程序還有能夠被擴充。

這個作業系統是用x86架構建立而成的，用32 bits來執行，並且與IBM的PC相容。

**規格:**

* Code in C++
* x86, 32 bit architecture
* Boot with Grub
* Kind of modular system for drivers
* Kind of UNIX style
* Multitasking
* ELF executable in userland
* Modules (accessible in userland using /dev/...) :
    * IDE disks
    * DOS partitions
    * Clock
    * EXT2 (read only)
    * Boch VBE
* Userland :
    * API Posix
    * LibC
    * "Can" run a shell or some executables (e.g., lua)
