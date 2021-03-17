
SYSCALL_DEFINE5(mysetnice,  pid_t, pid, int, flag, int, nicevalue, void __user*, prio, void __user*, nice)
{
	struct pid *id;    	    
	struct task_struct *pcb;    

	int new_nice, new_prio;

	id = find_get_pid(pid);     
	pcb = pid_task(id, PIDTYPE_PID);  
	
	
	new_nice = task_nice(pcb);    
	new_prio = task_prio(pcb);    

	if(flag == 0)      
	{
		copy_to_user(nice, &new_nice, sizeof(new_nice));
		copy_to_user(prio, &new_prio, sizeof(new_prio));
		
		return 0;
	}
	else if(flag == 1)       
	{
		set_user_nice(pcb, nicevalue);
		
		
		new_nice = task_nice(pcb);
		new_prio = task_prio(pcb);
 		
		
		copy_to_user(nice, &new_nice, sizeof(new_nice));
		copy_to_user(prio, &new_prio, sizeof(new_prio));
		return 0;	
	}
	return EFAULT;
}

struct mm_struct* my_get_task_mm(struct task_struct* task)
{
   struct mm_struct *mm;

   mm = task->mm;

return mm;
}

SYSCALL_DEFINE2(mytaskmm, pid_t, pid, void __user*, my_mm_struct)
{
    struct pid* cur_pid = find_get_pid(pid);
    struct task_struct* cur_task = NULL;
    struct mm_struct* cur_mm = NULL;

    cur_task = pid_task(cur_pid,PIDTYPE_PID);
	cur_mm = my_get_task_mm(cur_task);
	unsigned long mm_list[6] = {0};
	mm_list[0]  = cur_mm->start_code;
	mm_list[1]  = cur_mm->end_code;
	mm_list[2]  = cur_mm->start_data;
	mm_list[3]  = cur_mm->end_data;
	mm_list[4]  = cur_mm->start_brk;
	mm_list[5]  = cur_mm->start_stack;
	
	copy_to_user(my_mm_struct, mm_list, sizeof(mm_list));
	return 0;
}

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

SYSCALL_DEFINE5(mytaskinfo, int, pid, void __user *, task_name, void __user *, task_state, void __user *, task_uid, void __user *, task_euid) {
	struct pid* cur_pid = find_get_pid(pid);
    struct task_struct* cur_task = NULL;
	
    cur_task = pid_task(cur_pid,PIDTYPE_PID);
	char *state = get_task_state(cur_task);

	copy_to_user(task_name, &(cur_task->comm), sizeof(cur_task->comm));
	copy_to_user(task_state, state, strlen(state)+1);
	copy_to_user(task_uid, &(cur_task->cred->uid), sizeof(cur_task->cred->uid));
	copy_to_user(task_euid, &(cur_task->cred->euid), sizeof(cur_task->cred->euid));
	return 0;
}