#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

void hello2print(void);

static int __init myhello_init(void)
{
    printk(KERN_ALERT"Hello World\n");
    hello2print();
    return 0;
}

static void __exit myhello_exit(void)
{
    printk(KERN_ALERT"goodbye\n");
    return 0;
}
module_init(myhello_init);
module_exit(myhello_exit);

MODULE_LICENSE("GPL");
