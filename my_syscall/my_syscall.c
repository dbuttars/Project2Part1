/*---Start of my_syscall.c---*/

#include<linux/syscalls.h> //We're a syscall
#include<linux/sched.h> //Needed for the for_each_process() macro
#include<linux/jiffies.h> //Needed to manage the time
#include<asm/uaccess.h> //Needed to use copy_to_user


struct task_struct *task; //To use the for_each_process macro

int pid_array [1000];
int counter;

asmlinkage long sys_my_syscall(int i, unsigned long *to)
{
//	printk(KERN_INFO "This is the new system call Daniel Grant Burningham Buttars implemented.\n");
	counter = 0;
	for_each_process(task) {
		printk("Task %s (pid = %d)\n", task->comm, task_pid_nr(task));
		pid_array[counter] = task_pid_nr(task);
		printk("Task saved in array as: %d\n", pid_array[counter]);
		counter++;
	}	


	return copy_to_user(to, pid_array, (sizeof(int)*1000));	
}

/*---End of my_syscall.c---*/
