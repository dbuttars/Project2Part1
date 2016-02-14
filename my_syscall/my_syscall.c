/*---Start of my_syscall.c---*/

#include<linux/syscalls.h> //We're a syscall
#include<linux/sched.h> //Needed for the for_each_process() macro
#include<linux/proc_fs.h> //Needed for the proc_fs management
#include<linux/jiffies.h> //Needed to manage the time

#define procfs_name "processlist"

struct proc_dir_entry *Proc_file; //Holds proc_file info

struct task_struct *task; //To use the for_each_process macro

int pid_array [1000];
int counter;

asmlinkage long sys_my_syscall(int i, unsigned long *to)
{
//	printk(KERN_INFO "This is the new system call Daniel Grant Burningham Buttars implemented.\n");
//	for_each_process(task) {
//		printk("Task %s (pid = %d)\n", task->comm, task_pid_nr(task));
//	}
	counter = 0;
	for_each_process(task) {
		pid_array[counter] = task_pid_nr(task);
		counter++;
	}	

	copy_to_user(to, pid_array, (sizeof(int)*1000));	

	return 0;
}

/*---End of my_syscall.c---*/
