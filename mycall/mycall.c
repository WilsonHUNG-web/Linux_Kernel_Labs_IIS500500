#include <linux/kernel.h>
#include <asm/uaccess.h>

char text[101];

asmlinkage long sys_mycall(char* str, int count)
{
  int i = 0;

  //check memory access violaion of READ, memory not in user space -> return non-zero -> return -efault
  if(!(access_ok(VERIFY_READ, str, count)))
	return -EFAULT;

  if(count<100)
	{
  	text[count] = '\0';
	while(i<count)
		{	
		text[i] = str[i];
		i+=1;
		}
	}
  else{
  	text[100] = '\0';
	while(i<100)
		{
		text[i]=str[i];
		i+=1;	
		}
      }
	printk("%s\n", text);
  return 0;
}
