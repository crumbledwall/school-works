#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init_task.h>

#include <linux/moduleparam.h>

static int pid;

module_param(pid, int, 0644);

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

static int __init showpid_init(void)
{
    struct task_struct *p;
    struct list_head *pp;
    struct task_struct *psibling;

   p = pid_task(find_get_pid(pid), PIDTYPE_PID);
    if(p->parent == NULL) {
        printk("No Parent\n");
    }
    else {
        printk("Parent: %d %s %s\n", p->parent->pid, p->parent->comm, get_task_state(p));
    }

    // 兄弟进程
    list_for_each(pp, &p->parent->children)
    {
        psibling = list_entry(pp,struct task_struct, sibling);
        printk("sibling %d %s %s\n", psibling->pid, psibling->comm, get_task_state(p));
    }

    // 子进程
    list_for_each(pp, &p->children)
    {
        psibling = list_entry(pp, struct task_struct, sibling);
        printk("children %d %s %s\n", psibling->pid, psibling->comm, get_task_state(p));
    }
    return 0;
}

static void __init showpid_exit(void)
{
    printk(KERN_ALERT"goodbye\n");
    return 0;
}
module_init(showpid_init);
module_exit(showpid_exit);

MODULE_LICENSE("GPL");
