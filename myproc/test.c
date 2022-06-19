#include <stdio.h>
#include <unistd.h>
int main()
{
  printf("%d\n",getpid());
  while(1){
    printf("sleeping\n");
    sleep(5);
  }
  return 0;
}
