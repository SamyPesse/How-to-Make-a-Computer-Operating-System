## Chapter 2: Setup the development environment

The first step is to setup a good and viable development environment. Using Vagrant and Virtualbox, you'll be able to compile and test your OS from all the OSs (Linux, Windows or Mac).

### Install Vagrant

> Vagrant is free and open-source software for creating and configuring virtual development environments. It can be considered a wrapper around VirtualBox.

Vagrant will help us create a clean virtual development environment on whatever system you are using.
The first step is to download and install Vagrant for your system at http://www.vagrantup.com/.

### Install Virtualbox

> Oracle VM VirtualBox is a virtualization software package for x86 and AMD64/Intel64-based computers.

Vagrant needs Virtualbox to work, Download and install for your system at https://www.virtualbox.org/wiki/Downloads.

### Start and test your development environment

Once Vagrant and Virtualbox are installed, you need to download the ubuntu lucid32 image for Vagrant:

```
vagrant box add lucid32 http://files.vagrantup.com/lucid32.box
```

Once the lucid32 image is ready, we need to define our development environment using a *Vagrantfile*, [create a file named *Vagrantfile*](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/Vagrantfile). This file defines what prerequisites our environment needs: nasm, make, build-essential, grub and qemu.

Start your box using:

```
vagrant up
```

You can now access your box by using ssh to connect to the virtual box using:

```
vagrant ssh
```

The directory containing the *Vagrantfile* will be mounted by default in the */vagrant* directory of the guest VM (in this case, Ubuntu Lucid32):

```
cd /vagrant
```

#### Build and test our operating system

The file [**Makefile**](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/Makefile) defines some basics rules for building the kernel, the user libc and some userland programs.

Build:

```
make all
```

Test our operating system with qemu:

```
make run
```

The documentation for qemu is available at [QEMU Emulator Documentation](http://wiki.qemu.org/download/qemu-doc.html).

You can exit the emulator using: Ctrl-a.
