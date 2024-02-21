#include <asm-generic/param.h>
#include <asm/param.h>
#include <linux/gcd.h>
#include <linux/hash.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>

int simple_init(void) {
  printk(KERN_INFO "Loading Kernel Module\n");
  printk(KERN_INFO "Golden Ratio is %llu\n", GOLDEN_RATIO_PRIME);
  printk(KERN_INFO "Frequency of Timer interrupts %d\n", HZ);
  return 0;
}

void simple_exit(void) {
  printk(KERN_INFO "GCD of 4 and 6 is %lu\n", gcd(4, 6));
  printk(KERN_INFO "Number of timer interrupts since system boot %lu\n",
         jiffies);
  printk(KERN_INFO "Removing Kernel Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("l3002");
