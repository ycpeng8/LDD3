#include <linux/init.h>
#include <linux/module.h>

#include "scull.h"

int scull_major = 0;

module_param(scull_major, int, S_IRUGO);

static int __init scull_init(void)
{
	return 0;
}

module_init(scull_init);

MODULE_LICENSE("Dual BSD/GPL");