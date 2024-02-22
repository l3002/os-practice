#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#define BUFFER_SIZE 128
#define PROC_NAME "jiffies"

ssize_t proc_read(struct file *file, char __user *usr_buff, size_t count,
                  loff_t *pos);

static const struct proc_ops proc_ops = {.proc_read = proc_read};

int jiffies_init(void) {

  printk(KERN_INFO "Loading module for creating proc entry %s\n", PROC_NAME);
  proc_create(PROC_NAME, 0666, NULL, &proc_ops);
  printk(KERN_INFO "Successfully created proc entry %s\n", PROC_NAME);

  return 0;
}

void jiffies_exit(void) {

  printk(KERN_INFO "removing module for proc entry %s\n", PROC_NAME);
  remove_proc_entry(PROC_NAME, NULL);
  printk(KERN_INFO "successfully removed proc entry %s\n", PROC_NAME);
}

ssize_t proc_read(struct file *file, char __user *usr_buff, size_t count,
                  loff_t *pos) {

  ssize_t rv = 0;
  char buffer[BUFFER_SIZE];
  static int completed = 0;

  if (completed) {
    completed = 0;
    return 0;
  }

  rv = sprintf(buffer, "The current value of jiffies: %lu\n", jiffies);
  copy_to_user(usr_buff, buffer, rv);
  completed = 1;

  return rv;
}

module_init(jiffies_init);
module_exit(jiffies_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Returns current value of jiffies");
MODULE_AUTHOR("l3002");
