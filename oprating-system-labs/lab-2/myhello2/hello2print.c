#include <linux/kernel.h>

void hello2print(void) {
    printk(KERN_ALERT"this is hello2 print\n");
}
