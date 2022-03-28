# Linux_kernel_labs
Dedicated for Linux Kernel 2.6.39.4 (CentOS 6)
<br>
The labs are the practice cases from the course Linux Kernel (IIS500500) delivered in National Tsing Hua University.
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
$  ls -l /dev/ |grep [device name's keyword]
```
