#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <stdio.h>
#include <sys/types.h>

#define BUFFER 128
#define PROC_NAME "hello"

ssize_t proc_read(struct file *file, char __user *usrbuf, size_t count,
                  loff_t *offp);

static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

int proc_init() {
  printk(KERN_INFO "Loading module for proc creation\n");
  proc_create(PROC_NAME, 0666, NULL, &proc_ops);
  printk(KERN_INFO "Created proc entry for %s\n", PROC_NAME);
  return 0;
}

void proc_exit() {
  printk(KERN_INFO "Removing proc entry for %s\n", PROC_NAME);
  remove_proc_entry(PROC_NAME, NULL);
  printk(KERN_INFO "Proc Entry %s removed successfully\n", PROC_NAME);
}
