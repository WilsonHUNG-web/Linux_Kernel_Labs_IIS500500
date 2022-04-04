
###For 64-bit: arch/x86/include/asm/unistd_64.h
```
#define __NR_mycall                             307
__SYSCALL(__NR_mycall, sys_mycall)
```
###For 32-bit: arch/x86/kernel/syscall_table_32.S
```
        .long sys_mycall
```     
###For 32-bit: arch/x86/include/asm/unistd_32.h
```
#define __NR_mycall             346
```
###include/linux/syscalls.h
```
asmlinkage long sys_mycall(void);
```
###mycall/mycall.c
```
#include <linux/kernel.h>

asmlinkage long sys_mycall(void)
{
  printk("mycall..\n");
  return 0;
}
```
###mycall/Makefile
```
obj-y:=mycall.o
```
###Makefile
```
core-y          += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ mycall/
```
###test_call.c
```
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#define __NR_mycall 307
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv)
{
 
  long int ret;
  ret = syscall(__NR_mycall);
 
  return 0;
 
}
```
