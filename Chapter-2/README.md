## Chapter 2: Set Up the Development Environment

The first step is to setup an effective development environment. Using Vagrant and VirtualBox, you'll be able to compile and test your OS from any platform.

### Install Vagrant

> Vagrant is free and open-source software for creating and configuring virtual development environments. It can be considered a wrapper around VirtualBox.

Vagrant will help us create a clean virtual environment on whatever system you are using. To get started, download and install Vagrant for your system [here](http://www.vagrantup.com).

### Install VirtualBox

> Oracle VM VirtualBox is a virtualization software package for x86 and AMD64/Intel64-based computers.

As a prerequisite, Vagrant needs VirtualBox to function properly. Download and install the VirtualBox package from [here](https://www.virtualbox.org/wiki/Downloads).

### Start and test your development environment

Once Vagrant and VirtualBox have been installed, you need to download the Ubuntu `lucid32` image for Vagrant:

```
vagrant box add lucid32 http://files.vagrantup.com/lucid32.box
```

Once the lucid32 image is ready, we need to define our development environment using a *Vagrantfile*. [Create a file named *Vagrantfile*](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/Vagrantfile). This file defines what prerequisites our environment needs: nasm, make, build-essential, grub and qemu.

Now, spin up your box using:

```
vagrant up
```

You can now access your environment by using ssh. Connect to the virtual box using:

```
vagrant ssh
```

The directory containing the *Vagrantfile* will be mounted by default in the */vagrant* directory of the guest VM (in this case, Ubuntu Lucid32):

```
cd /vagrant
```

#### Build and test our operating system

The [**Makefile**](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/Makefile) defines some basic rules for building the kernel, the user libc and some userland programs.

To build, run:

```
make all
```

We can test our operating system with qemu:

```
make run
```

The documentation for qemu is available at [QEMU Emulator Documentation](http://wiki.qemu.org/download/qemu-doc.html). You can exit the emulator using: Ctrl-a.
