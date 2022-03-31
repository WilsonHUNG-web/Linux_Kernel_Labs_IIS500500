# Linux_kernel_labs
Dedicated for **Linux Kernel 2.6.39.4 (CentOS 6)**.
<br>
The labs are the practice cases from the course **Linux Kernel (IIS500500)** delivered in **National Tsing Hua University**.
<br>
## I. ```mychrdev.c```
This linux kernel function creates a character storage device at ```/dev/mychrdev``` which stores 100kB characters, i.e. 100 ```char```, plus a null char ```\0``` at the end. Excessive characters (```char``` index larger than 100) following ```echo``` command will be omitted.
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
$  lsmod |grep [device name's keyword]
```
## II. ```myfs.c```
This kernel function creates a filesystme of files and directories that provide specific functions and store numbers in the files.

### 1. How to compile and install (```Makefile``` shall be editted accordingly based on different kernel function filenames.)
```
$ make clean
$ make
$ insmod myfs.ko
```
### 2. How to mount the file system (Write and Read)
```
$ mount -t myfs /dev/loop0(could be loop1, loop2, etc.) [mounting directory]
```
