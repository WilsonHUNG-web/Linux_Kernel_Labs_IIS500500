# Linux_kernel_labs
Dedicated for Linux Kernel 2.6.39.4
<br>
### mychrdev.c
This linux kernel function creates a character storage device at ```/dev/mychrdev``` which stores 100kB characters plus a null char ```\0``` at the end. Excessive characters in ```echo``` will be omitted.
<br>
Example commands,
```
$ echo 'ABCD' > /dev/mychrdev
$ cat /dev/mychrdev
```
