# Linux_kernel_labs
Dedicated for Linux Kernel 2.6.39.4
<br>
## I. mychrdev.c
This linux kernel function creates a character storage device at ```/dev/mychrdev``` which stores 100kB characters plus a null char ```\0``` at the end. Excessive characters in ```echo``` will be omitted.
<br>
### 1. How to compile and install (Makefile shall be editted accordingly based on different kernel function filenames.)
```
$ make clean
$ make
$ insmod mychrdev.ko
```
### 2. How to run
```
$ echo 'ABCD' > /dev/mychrdev
$ cat /dev/mychrdev
```
### 3. How to remove
```
$ rmmod mychrdev.ko
```
