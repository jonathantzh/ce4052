// modIO.c
// Demonstarting how to enable access from a user program
// To compile:
// - command to create a Makefile:   	echo "obj-m := mod_IO.o" > Makefile
// - execute the compilation:		make  -C /usr/src/linux-headers-`uname -r` M=`pwd` modules

// To load the module:  			sudo insmod ./mod_IO.ko
// To check loading:				lsmod | grep mod_IO
// To check loading/unloading messasges: 	dmesg | tail
// To unload later:				sudo rmmod mod_IO.ko

// After loading the module
// - first create the node with major number 101:		sudo mknod /dev/ce4052 c 101 22
// - to check that the device is created successfully:		ls -al /dev/ce4052
// - to write to the file:					echo "hello" > /dev/ce4052
// - to read from the file:  					cat /dev/ce4052

// Can also be accessed using a user space program
// - see testmodIO.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h> /* for put_use and get_user */

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = { .read = device_read,
  				       .write = device_write,
  				       .open = device_open,
  				       .release = device_release
				     };

char msg, ctr=0;  //  for read/write control - initialize to 0

static int __init ce4052_init(void)
{	printk(KERN_ALERT "Loading modIO\n");
	register_chrdev(101, "ce4052", &fops);      // registered as "ce4052" device node
	return 0;
}

static void __exit ce4052_cleanup(void)
{	unregister_chrdev(101, "ce4052");
	printk(KERN_ALERT "Unloading modIO\n");
}


module_init(ce4052_init); /*macro to execute module's initialize routine */
module_exit(ce4052_cleanup); /*macro to execute module's exit routine */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CE4052-modIO");
MODULE_DESCRIPTION("I/O module");




static int device_open(struct inode *inode, struct file *file)
{  printk(KERN_ALERT "Someone opened modIO\n");
   return 0;
}

static int device_release(struct inode *inode, struct file *file)
{  printk(KERN_ALERT "Someone closed modIO\n");
   return 0;
}

static ssize_t device_write(struct file *filp, const char *buf, size_t len, loff_t *off)
// write by user space program
{   printk(KERN_ALERT "writing to device\n");
    if (ctr>0)
       return 0;	    /* no space to accept another char */
    get_user(msg, buf++);  /* retrieve the value from user space */
    ctr=1;
    return 1;       	  /* 1 byte/char read from buf & stored */
}

static ssize_t device_read(struct file *filp, char *buf, size_t len, loff_t *off)
// read by user space program
{  printk(KERN_ALERT "reading the device\n");
   if (ctr==0)
      return 0;	          /* nothing to return to userland*/
   put_user(msg, buf++);  /* put the value into buf of user space */
   ctr=0;
   return 1;   		  /* 1 byte/char was put into buf in userland */
}



