# Linux_kernel_labs
Dedicated for **Linux Kernel 2.6.39.4 (CentOS 6)**.
<br>
These labs are the practice cases from the course **Linux Kernel (IIS500500)** delivered in **National Tsing Hua University**.
<br>
## I. ```mychrdev.c```
This kernel function creates a character storage device at ```/dev/mychrdev``` which stores 100kB characters, i.e. 100 ```char```, plus a null char ```\0``` at the end. Excessive characters (```char``` index larger than 100) following ```echo``` command will be omitted.
<br>
### 1. How to compile and install (```Makefile``` shall be editted accordingly based on different kernel function filenames.)
```
$ make clean
$ make
$ insmod mychrdev.ko
```
### 2. How to run (Write and Read)
```
$ echo 'ABCD' > /dev/mychrdev
$ cat /dev/mychrdev
```
### 3. How to remove
```
$ rmmod mychrdev.ko
```
### 4. How to check whether a device exists
```
$  lsmod |grep mychrdev
```
Note:<br>
* 'mychrdev' is just an example for the device name's keywords. It could be 'my', 'mychr', 'chr', 'chrdev', etc.
## II. ```myfs.c```
This kernel function creates a filesystem of files and directories that provide add/sub functions and store numbers in the range [0, 255] in the files a/b. For example,<br>
```$ echo 23 > /fs/output/a ``` stores 23 in a.<br>
```$ echo 256 > /fs/output/b ``` prints invalid argument error by returning ```-EINVAL``` in the ```.write``` function.<br>
```$ cat /fs/output/sub ``` prints a-b.<br>
```$ cat /fs/output/add ``` prints a+b.<br>
```$ echo 256 > /fs/output/add ``` prints invalid argument error by returning ```-EINVAL``` in order to suspend users from writing values into add/sub.<br>
The filesystem tree structure looks like, <br><br>
/fs<br>
├── input<br>
│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── a<br>
│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── b<br>
└── output<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── add<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── sub<br>
<br>
### 1. How to compile and install (```Makefile``` shall be editted accordingly based on different kernel function filenames.)
```
$ make clean
$ make
$ insmod myfs.ko
```
### 2. How to mount and unmount the file system
```
$ mount -t myfs /dev/loop0 /fs
$ umount -t myfs /dev/loop0 /fs
```
Note:<br>
* ```loop0``` could be ```loop1```, ```loop2```, etc.
* ```/fs``` is the mounting directory. Changeable as desired. Do not mount the filesystem to a non-empty directory.
* Before removing the myfs module, user must firstly unmount the filesystem.
## III. ```mycall.c```+```unistd_65.h```+```syscalls.h```+```/usr/src/[kernel_image]/Makefile```
This custom system call, ```mycall.c```, takes a ```char*``` within 100 ```char``` and ```printk``` it into ```dmesg```. If ```char*``` has more than 100 ```char```, excessive ```char``` will be ignored.

