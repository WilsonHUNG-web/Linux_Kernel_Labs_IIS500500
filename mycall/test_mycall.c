#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#define __NR_mycall 303
#include <string.h>
#include <stdlib.h>

int main(int argc,char **argv)
{

  long int ret;
  char* ch = malloc(150);
  strcpy(ch, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
  
  ret = syscall(__NR_mycall, ch, 104);
  ret = syscall(__NR_mycall, ch, 2);
  ret = syscall(__NR_mycall, ch, 3);

  ret = syscall(__NR_mycall, ch, 100);
  ret = syscall(__NR_mycall, ch, 0);

  printf("end of test_call.c, ret=%d\n", ret);

  return 0;
 
}
