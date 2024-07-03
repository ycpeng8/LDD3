#ifndef _SCULL_H_
#define _SCULL_H_

#ifndef SCULL_MAJOR
#define SCULL_MAJOR 0			/* dynamiclly assign major number */
#endif // !SCULL_MAJOR

#ifndef SCULL_MINOR
#define SCULL_MINOR 0           /* assign minor number */
#endif

#ifndef SCULL_NR_DEVS
#define SCULL_NR_DEVS 4         /* scull0 ~ scull3 */
#endif

/*
 * configurable parameters
 */
extern int scull_major;
extern int scull_minor;
extern int scull_nr_devs;

/*
 * device registration
 */
struct scull_dev {
    struct scull_qset *data;        /* pointer to first quantum set */
    int quantum;                    /* the current quantum size */
    int qset;                       /* the current array size */
    unsigned long size;             /* amount of data stored here */
    unsigned int access_key;        /* used by sculluid and scullpriv */
    struct semaphore sem;           /* mutual exclusion semaphore */
    struct cdev cdev;               /* char device structure */
}

/*
 * file operations functions
 */
loff_t scull_llseek(struct file* filp, loff_t off, int whence);
ssize_t scull_read(struct file* flip, char __user* buf, size_t count,
                    loff_t* f_pos);
ssize_t scull_write(struct file* flip, const char __user* buf, size_t count,
                    loff_t* f_pos);
int scull_ioctl(struct inode* inode, struct file* flip, unsigned int cmd,
                unsigned long arg);
int scull_open(struct inode* inode, struct file* flip);
int scull_release(struct inode* inode, struct file* flip);

#endif // !_SCULL_H_
