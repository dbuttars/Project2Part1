/*---Start of my_syscall.c---*/

#include<linux/syscalls.h>
#include<linux/sched.h>
#include<linux/jiffies.h>

struct task_struct *task;

asmlinkage long sys_my_syscall(int i)
{
	printk(KERN_INFO "This is the new system call Daniel Grant Burningham Buttars implemented.\n");

	for_each_process(task) {
		printk("Task %s (pid = %d)\n", task->comm, task_pid_nr(task));
	}
	return 0;
}

/*---End of my_syscall.c---*/
