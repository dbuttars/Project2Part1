/*---Start of my_syscall.c---*/

#include<linux/syscalls.h> //We're a syscall
#include<linux/sched.h> //Needed for the for_each_process() macro
#include<linux/jiffies.h> //Needed to manage the time
#include<asm/uaccess.h> //Needed to use copy_to_user
#include<linux/slab.h> //Needed to use kmalloc

struct task_struct *task; //To use the for_each_process macro

asmlinkage long sys_my_syscall(int cap, int *to)
{
//	printk(KERN_INFO "This is the new system call Daniel Grant Burningham Buttars implemented.\n");
	int buff[1024];
	int len = 0;
	for_each_process(task) {
		printk("Task %s (pid = %d)\n", task->comm, task_pid_nr(task));
		buff[len] = task_pid_nr(task);
		printk("Task saved in array as: %u\n", buff[len]); 
		len++;
	}	

	if (len > cap) len = cap;
	printk("Len is %d\n", len);
	int size;
	size = len * 4;	
	return copy_to_user(to, buff, size); 
}

/*---End of my_syscall.c---*/
