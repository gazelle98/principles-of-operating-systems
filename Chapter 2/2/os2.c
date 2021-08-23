#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/jiffies.h>
#include <linux/param.h>

#define BUFFER_SIZE 128
#define PROC_NAME "seconds"

unsigned long int volatile start_time;
const int hz = HZ;

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

int proc_init(void)
{
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    start_time = jiffies;

    return 0;
}


void proc_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
}

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;
    if(completed){
        completed = 0;
        
        return 0;
    }
        completed = 1;
        rv = sprintf(buffer, "The running time is %ld seconds.\n", ((jiffies - start_time)/hz));
        copy_to_user(usr_buf, buffer, rv);
        return rv;
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Report of elapsed seconds since the kernel module was loaded.");
MODULE_AUTHOR("Ghazaleh Kharadpoor");