## Linux_kernel_labs

# mychrdev.c
Create a character storage device '/dev/mychrdev' which stores 100kB characters plus '\0' at the end. Excessive characters in 'echo' will be omitted.
```
$ echo 'ABC' > /dev/mychrdev
$ cat /dev/mychrdev
