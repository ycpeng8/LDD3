//
// Created by ycpeng on 6/6/2024.
//
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
MODULE_LICENSE("Dual BSD/GPL");

static void print_process_id(void) 
{
    printk(KERN_INFO "The process is \"%s\" (pid %i)\n",
            current->comm, current->pid);
}

static int hello_init(void)
{
    printk(KERN_ALERT "Hello, world\n");
    print_process_id();
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
