#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

static char* who;
static int times;
module_param(who, charp, 0644);
module_param(times, int, 0644);


static int __init param_init(void)
{
    int i = 0;
    for(i = 0; i <= times; i++){
        printk("%d    %s", i, who);
    }
    return 0;
}

static void __init param_exit(void)
{
    printk(KERN_ALERT"goodbye%s\n", who);
    return 0;
}
module_init(param_init);
module_exit(param_exit);

MODULE_LICENSE("GPL");
