#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kernel.h>

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

/* open and close */
int scull_open(struct inode* inode, struct file* flip)
{
	struct scull_dev *dev;					/* device information */
}

/* set up char_dev structure */
static void scull_setup_cdev(struct scull_dev *dev, int index)
{
	int err, devno = MKDEV(scull_major, scull_minor + index);

	cdev_init(&dev->cdev, &scull_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &scull_fops;
	err = cdev.add(&dev->cdev, devno, 1);
	/* fail gracefully if need be */
	if (err) 
		printk(KERN_NOTICE "Error %d adding scull%d", err, index);
}

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
