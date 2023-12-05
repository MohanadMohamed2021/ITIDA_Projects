#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h> 

char str[50]="work";

dev_t dev = MKDEV(300,0);

int dev_open(struct inode *inode,struct file *filp)
{
    printk(KERN_INFO "Hello from open device...\n");
    return 0;
}
int dev_release(struct inode *inode,struct file *filp)
{
    printk(KERN_INFO "Hello from release device...\n");
    return 0;
}
ssize_t dev_write(struct file *filp, const char __user *buffer, size_t count, loff_t *offp)
{
    int i=0,flag=0;
    printk(KERN_INFO "Hello from write device...\n");
    copy_from_user(str,buffer,count);
    while(str[i] != '\n')
    {
        if(buffer[i]!=str[i])
        {
            flag=1;
            break;
        }
        i++;
    }
    if(flag==0)
    {
        printk(KERN_INFO "LED ON...\n");
    }
    else
    {
        printk(KERN_INFO "LED OFF...\n");
    }
    return count;
}
ssize_t dev_read(struct file *filp,char __user *buffer, size_t count, loff_t *offp)
{
    printk(KERN_INFO "Hello from read device...\n");
    copy_from_user(buffer,str,sizeof(str));
    return count;
}
struct file_operations opera = {
                                .owner = THIS_MODULE,
                                .open  = dev_open,
                                .release = dev_release,
                                .write = dev_write, 
                                .read = dev_read    };
struct cdev char_device;
int x=5;
module_param(x, int, S_IRUSR | S_IWUSR);
char str2[] = "mohanad";
module_param_string(str2, str2, sizeof(str2), S_IRUSR | S_IWUSR);
int __init Module_Init_Funct(void)
{
    int ret = register_chrdev_region(dev,1,"print_name");
    if(ret < 0)
    {
        printk(KERN_INFO "can't create device...\n");
        return ret;
    }
    printk(KERN_INFO "Starting module function...\n");
    for (int i = 0; i < x ; i++)
    {
        printk(KERN_INFO "%s\n",str2);
    }
    cdev_init(&char_device,&opera);
    cdev_add(&char_device,dev,1);
    return 0;
}

void __exit Module_exit_Funct(void)
{
    unregister_chrdev_region(dev, 1);
    cdev_del(&char_device);
    printk(KERN_INFO "Exiting module function...\n");
}

module_init(Module_Init_Funct);
module_exit(Module_exit_Funct);

MODULE_LICENSE("GPL");
