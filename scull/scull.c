#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>

#include "scull.h"

int scull_major = SCULL_MAJOR;
int scull_minor = SCULL_MINOR;
int scull_nr_devs = SCULL_NR_DEVS;

/* module parameters injections */
module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_nr_devs, int, S_IRUGO);

/* file operations connection */
struct file_operations scull_fops = {
	.owner = 	THIS_MODULE,
	.llseek =	scull_llseek,
	.read =		scull_read,
	.write = 	scull_write,
	.ioctl = 	scull_ioctl,
	.open =		scull_open,
	.release =	scull_release,
};

static int __init scull_init(void)
{
	int result;
	dev_t dev = 0;

	/* Set major and minor numbers */
	if (scull_major) {
		dev = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(dev, scull_nr_devs, "scull");
	} else {
		result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs,
			"scull");
		scull_major = MAJOR(dev);
	}

	if (result < 0) {
		printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
		return result;
	}

	return 0;
}

module_init(scull_init);

MODULE_LICENSE("Dual BSD/GPL");
