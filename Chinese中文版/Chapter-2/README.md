## 第二章: 建立開發環境

開發一個作業系統的第一步便是建立一個好的且可行的開發環境。為了能夠在所有現行作業系統上編譯還有測試你做出來的作業系統，我們要使用 Vagrant 還有 VirtualBox。

### 安裝 Vagrant

> Vagrant 是一個免費且開源的軟體，用來產生或是設定虛擬開發環境，可以把它視為 VirtualBox 的包裝。

我們會用 Vagrant 來產生一個純粹的虛擬開發環境，不論你目前使用的是什麼作業系統都能夠使用這個開發環境。
第一步就是下載並安裝 Vagrant 在你的作業系統 ： http://www.vagrantup.com/

### 安裝 Virtualbox

> Oracle VM VirtualBox 是一個在 x86 以及 AMD64/Intel64-based 電腦上運作的虛擬化的軟體

Vagrant 的運行需要 Virtauslbox 從這裡：https://www.virtualbox.org/wiki/Downloads 下載並安裝到你的電腦

### 開啟並測試你的開發環境

當 Vargrant 和 Virtualbox 安裝完成之後，你需要下載 Ubuntu lucid32 的 Vagrant 映像檔

```
vagrant box add lucid32 http://files.vagrantup.com/lucid32.box
```

當 lucid32 映像檔下載好之後，我們需要用一個 *Vagrantfile* 來定義我們的開發環境。參考 ： [create a file named *Vagrantfile*](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/Vagrantfile)
這個檔案定義了我們的開發環境所需要的預載工具 : nasm, make, build-essential, grub 還有 qemu

開啟的的虛擬機器:

```
vagrant up
```

你現在可以透過用 ssh 來連線進你的虛擬機器以存取你的機器 : 

```
vagrant ssh
```

包含 *Vagrantfile* 的目錄會被自動掛載在虛擬機器的 */vagrant* 目錄 (在我們的例子中，是Ubuntu Lucid32)

```
cd /vagrant
```

#### 建構並測試我們的作業系統

[**Makefile**](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/Makefile)這個檔案定義了一些基本的建構核心的規則，user libc 還有一些使用者端的程式。

建構:

```
make all
```

用 qemu 測試我們的作業系統:

```
make run
```

The documentation for qemu is available at [QEMU Emulator Documentation](http://wiki.qemu.org/download/qemu-doc.html).
qemu 的使用手冊的可以在 [QEMU Emulator Documentation](http://wiki.qemu.org/download/qemu-doc.html) 找到。

你可以用 Ctrl-a 來離開模擬器。
