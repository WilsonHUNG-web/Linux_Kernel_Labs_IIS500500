#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/device.h>
MODULE_LICENSE("GPL");
#define DRIVER_NAME "mychrdev"
dev_t device_number;
char text[101];

static struct class *mychrdev_class = NULL;
 
static struct cdev my_cdev;
 
static int mydevice_open(struct inode *inode, struct file *file)
{
        pr_info("%s\n", __func__);
        return 0;
}
 
static int mydevice_release(struct inode *inode, struct file *file)
{
        pr_info("%s\n", __func__);
        return 0;
}
 
ssize_t mydevice_read(struct file *file, char __user *user_buffer,
                      size_t count, loff_t *offset)
{
       	pr_info("%s\n", __func__);
	//printk("before: *offset: %d, count: %d\n",  (int)*offset, (int)count);
      	if(*offset > 100)
	 	return 0;
       	if(*offset + count > 100)
		count = 100 - *offset;
       	if(copy_to_user(user_buffer, text, count))
	 	return -EFAULT;

      	*offset+=count;
	pr_info("read return %d\n", (int)count);
	//printk("after: *offset: %d, count: %d\n",  (int)*offset, (int)count);
      	return count;
}
 
ssize_t mydevice_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	int ret;
        pr_info("%s\n", __func__);
	
	if(count < 100)
		{
		ret = copy_from_user(text, user_buffer, count);
		text[count]='\0';
		}
	else
		{
		ret = copy_from_user(text, user_buffer, 100);
		text[100]='\0';
		}

	//printk("before: *offset: %d, count: %d\n",  (int)*offset, (int)count);	

    	pr_info("kernel text content:%s\n", text);
	*offset+= count;
	//printk("after: *offset: %d, count: %d\n",  (int)*offset, (int)count);
    	return count;
}
 
struct file_operations fops = {
        .owner = THIS_MODULE,
        .open = mydevice_open,
        .release = mydevice_release,
        .read = mydevice_read,
        .write = mydevice_write
};
 
 
static int mynull_device_init(void)
{
    int retval;
    pr_info("%s: In init\n", __func__);
    retval = alloc_chrdev_region(&device_number, 0, 1, DRIVER_NAME);
    if (!retval) {
        pr_info("%s: Major Number:%d\t Minor Number:%d\n",
                __func__, MAJOR(device_number), MINOR(device_number));
        cdev_init(&my_cdev, &fops);
        retval = cdev_add(&my_cdev, device_number, 1);
        if (retval)
            pr_info("%s: Failed in adding cdev to subsystem "
                            "retval:%d\n", __func__, retval);
//create device
	mychrdev_class = class_create(THIS_MODULE, DRIVER_NAME);
 	//if (IS_ERR(mychrdev_class))
  	 // goto error;

 	device_create(mychrdev_class,
                      NULL,
                      MKDEV(MAJOR(device_number), 0),
                      NULL,
                      "mychrdev");
    }
    else
        pr_err("%s: Failed in allocating device number "
                "Error:%d\n", __func__, retval);
//
 //  error:
    //if (cdev_ret == 0)
    //  cdev_del(&test_chrdev_alloc_cdev);
   // if (alloc_ret == 0)
    //  unregister_chrdev_region(dev, num_of_dev);
    return retval;
}
 
static void mynull_device_exit(void)
{
    cdev_del(&my_cdev);
    unregister_chrdev_region(device_number, 1);
    pr_info("%s: In exit\n", __func__);
}
 
module_init(mynull_device_init);
module_exit(mynull_device_exit);
