#include <asm/param.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#define BUFFER_SIZE 128
#define PROC_NAME "seconds"

ssize_t proc_read(struct file *file, char __user *usr_buff, size_t count,
                  loff_t *pos);

static struct proc_ops proc_ops = {.proc_read = proc_read};

int seconds_init(void) {
  printk(KERN_INFO "Loading module for creating proc entry %s\n", PROC_NAME);
  proc_create(PROC_NAME, 0666, NULL, &proc_ops);
  printk(KERN_INFO "Successfully created proc entry %s\n", PROC_NAME);
  return 0;
}

void seconds_exit(void) {
  printk(KERN_INFO "Exiting module for creating proc entry %s\n", PROC_NAME);
  remove_proc_entry(PROC_NAME, NULL);
  printk(KERN_INFO "Successfully removed proc entry %s\n", PROC_NAME);
}

ssize_t proc_read(struct file *file, char __user *usr_buff, size_t count,
                  loff_t *pos) {
  ssize_t rv;
  char buffer[BUFFER_SIZE];
  static ssize_t completed = 0;

  if (completed) {
    completed = 0;
    return 0;
  }

  rv = sprintf(buffer, "%lu seconds have passed since boot\n", jiffies / HZ);
  copy_to_user(usr_buff, buffer, rv);
  completed = 1;

  return rv;
}

module_init(seconds_init);
module_exit(seconds_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(
    "creates a proc entry which reports number of seconds elapsed since boot");
MODULE_AUTHOR("l3002");
