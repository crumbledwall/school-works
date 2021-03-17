#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/init_task.h>
#include <linux/kernel.h>


MODULE_LICENSE("GPL");

static const char *task_state_array[] = {
        "R (running)",          /*  0 */
        "S (sleeping)",         /*  1 */
        "D (disk sleep)",       /*  2 */
        "T (stopped)",          /*  4 */
        "T (tracing stop)",     /*  8 */
        "Z (zombie)",           /* 16 */
        "X (dead)"              /* 32 */
};

static inline const char *get_task_state(struct task_struct *tsk)
{
        unsigned int state = (tsk->state & TASK_REPORT) | tsk->exit_state;
        const char **p = &task_state_array[0];

        while (state) {
                p++;
                state >>= 1;
        }
        return *p;
}

static int __init listall_init(void)
{
    struct task_struct *task;

    for_each_process(task) {
        if(task->mm == NULL){
            printk(KERN_INFO"%-25s%-7d%-25s%-7d%-7d\n",
                task->comm,
                task->pid,
                get_task_state(task),
                task->prio,
                task->parent->pid
                );
        }
    }
    return 0;
}

static void __exit listall_exit(void)
{
    printk(KERN_ALERT"goodbye\n");
    return 0;
}
module_init(listall_init);
module_exit(listall_exit);