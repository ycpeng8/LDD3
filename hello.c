//
// Created by ycpeng on 6/6/2024.
//
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

/* Export symbols for other modules to use
 * (The _GPL version makes the symbol available
 * to GPL-licensed modules only)
 */
// EXPORT_SYMBOL(name);
// EXPORT_SYMBOL_GPL(name);

static void print_process_id(void) 
{
    printk(KERN_INFO "The process is \"%s\" (pid %i)\n",
            current->comm, current->pid);
}

/*
 * __init means this function is used only
 * at initialization time.
 * __initdata has the same behavior.
 */
static int __init hello_init(void)
{
    printk(KERN_ALERT "Hello, world\n");
    print_process_id();
    return 0;
}

/*
 * __exit means this function is being 
 * for module unload only
 */
static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

// MODULE_ declarations
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("ycpeng");
