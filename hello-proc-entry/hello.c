#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#define BUFFER_SIZE 128
#define PROC_NAME "hello"

ssize_t proc_read(struct file *file, char __user *usrbuf, size_t count,
                  loff_t *offp);

static struct proc_ops proc_ops = {.proc_read = proc_read};

int proc_init(void) {
  printk(KERN_INFO "Loading module for proc creation\n");
  proc_create(PROC_NAME, 0666, NULL, &proc_ops);
  printk(KERN_INFO "Created proc entry for %s\n", PROC_NAME);
  return 0;
}

void proc_exit(void) {
  printk(KERN_INFO "Removing proc entry for %s\n", PROC_NAME);
  remove_proc_entry(PROC_NAME, NULL);
  printk(KERN_INFO "Proc Entry %s removed successfully\n", PROC_NAME);
}

ssize_t proc_read(struct file *file, char __user *usrbuf, size_t count,
                  loff_t *offp) {
  ssize_t rev = 0;
  char buffer[BUFFER_SIZE];
  static ssize_t completed = 0;

  if (completed) {
    completed = 0;
    return 0;
  }

  completed = 1;
  rev = sprintf(buffer, "Hello World! from proc/%s\n", PROC_NAME);
  copy_to_user(usrbuf, buffer, rev);

  return rev;
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Module to add proc entry for hello");
MODULE_AUTHOR("l3002");
