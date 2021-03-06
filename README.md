# Linux_kernel_labs
Dedicated for **Linux Kernel 2.6.39.4 (CentOS 6 64-bit)**. 
<br>
These labs are the practice cases from the course **Linux Kernel (IIS500500)** delivered in **National Tsing Hua University**. A guideline from scratch for those who are not familiar with Linux.
<br>
## I. `mychrdev`
This kernel function creates a character storage device at `/dev/mychrdev` which stores 100kB characters, i.e. 100 ```char```, plus a null char ```\0``` at the end. Excessive characters (```char``` index larger than 100) following ```echo``` command will be omitted.
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
## II. ```myfs```
This kernel function creates a filesystem of files and directories that provide add/sub functions and store numbers in the range [0, 255] in the files a/b. For example,<br>
* ```$ echo 23 > /fs/output/a ``` stores 23 in a.<br>
* ```$ echo 256 > /fs/output/b ``` prints invalid argument error by returning ```-EINVAL``` in the ```.write``` function.<br>
* ```$ cat /fs/output/sub ``` prints a-b.<br>
* ```$ cat /fs/output/add ``` prints a+b.<br>
* ```$ echo 256 > /fs/output/add ``` prints invalid argument error by returning ```-EINVAL``` in order to suspend users from writing values into add/sub.<br>
The filesystem tree structure looks like, <br>
/fs<br>
├── input<br>
│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── a<br>
│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── b<br>
└── output<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── add<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── sub<br>

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
Note:
* ```loop0``` could be ```loop1```, ```loop2```, etc.
* ```/fs``` is the mounting directory. Changeable as desired. Do not mount the filesystem to a non-empty directory.
* Before removing the myfs module, user must firstly unmount the filesystem.
## III. ```mycall```
This custom system call, ```sys_mycall(char* str, int count)``` defined in ```mycall.c``` and ```syscalls.h```, takes a ```char*``` within 100 ```char``` and ```printk``` it into ```dmesg```. If ```char*``` has more than 100 ```char```, excessive ```char``` will be ignored.<br>
Some header files shall be editted in order to implement a custom system call.<br>

* ```mycall.c```: The implementation detail of ```sys_mycall(char* str, int count)```. Should be placed in the kernel image folder, e.g., ```/usr/src/kernels/[kernel_image_version]/mycall/mycall.c```.

* ```syscalls.h```: Locates at ```/usr/src/kernels/[kernel_image_version]/include/linux/syscalls.h```<br>
This header file formally defines ```sys_mycall(char* str, int count)```. Add it to the last lines. 
```
asmlinkage long sys_mycall(char* ch, int count);
```

* ```unistd_64.h```: Locates at ```/usr/src/kernels/[kernel_image_version]/arch/x86/include/asm/unistd_64.h```. It defines the representative number of the system call. It is recommmended to add it after the last existing system call and give it the last system call's number plus 1, e.g., 302+1 = 303.
```
#define __NR_mycall                             303
__SYSCALL(__NR_mycall, sys_mycall)
```

* ```Makefile```: The makefile for ```mycall.c``` can be simplified as shown below.
```
obj-y:=mycall.o
core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ mycall/
```

* ```/kernel/Makefile```: The makefile of the kernel image shall be editted in order to include our custom system call. It is located at ```/usr/src/[kernel_image_version]/Makefile```. Add ```mycall/``` after ```core-y +=``` at line 684, e.g., 
```
core-y		+= kernel/ mm/ fs/ ipc/ security/ crypto/ block/ mycall/
```

### 1. How to install the system call
After completing all the files mentioned above, we need to reconfigure the kernel image, reinstall it and reboot the system by the commands below.
```
$ cd /usr/src/[kernel_image_version]
$ make menuconfig
$ make -j[#processor], e.g., make -j1
$ make modules_install
$ make install
$ reboot
```
### 2. How to check if the OS is successfully updated
Use the command below to check if the timestamp of the kernel image is updated to the moment of using command ```$ make -j1```
```
$ uname -a
```
### 3. How to call our custom system call
We make a test C program, ```test_mycall.c```, to call sys_mycall by ```syscall(__NR_mycall, ch, 104);```, where ```ch``` is the ```char*``` and ```104``` is the number of ```char``` wanted to be ```printk```ed. (But as mentioned, ```char``` more than 100 will be ignored.)
### 4. How to check the ```printk``` messages.
The results can be found by the command below.
```
$ dmesg
```

## IV. ```myproc```
This kernel function is used to print some information about a specific process's data in ```struct_task``` and ```struct_mm```.
<br>
### 1. How to compile and install (```Makefile``` shall be editted accordingly based on different kernel function filenames.)
```
$ make clean
$ make
$ insmod myproc.ko
```
### 2. How to run (Write and Read)
We need to give a process PID to this device by ```echo``` and it will print the information of:
* Parent PID
* Start and end address of its code in hexadecimal format
* Start and end address of its data and in hexadecimal format
* Start and end address of its heap in hexadecimal format
* Kernel Version (nothing to do with this proces PID)
* Number of children process
```
$ echo 1122 > /proc/myproc
$ cat /proc/myproc
```
To get a process PID, we may use ```ps a``` command or use ```getpid()``` function defined in ```<unistd.h>``` in C to get the PID of a specific process. An example is provided in ```./myproc/test.c```. To compile it simply use command line ```gcc -o test.out test.c```, run it by ```./test.out``` command and use another terminal to lookup the PID by the ```echo``` and ```cat``` commands mentioned above.
