#include<linux/syscalls.h> //We're a syscall
#include<linux/sched.h> //Needed for the for_each_process() macro
#include<linux/tty.h>
#include<linux/jiffies.h> //Needed to manage the time
#include<linux/slab.h> //Needed for kmalloc
#include<asm/uaccess.h> //Needed to use copy_to_user

struct buff_struct {		// struct to store informations
 	int pid;
	char comm[16];
	char tty[10];
 	unsigned long time;
};

asmlinkage long sys_my_syscall( int cap, int *to){

	struct buff_struct *buff;
	struct task_struct *task; 	//To use the for_each_process macro
	int counter;
	int i;
	unsigned long jiff;
	unsigned long time_second;


	counter = 0;
	for_each_process (task) { counter++; }
	// create buffer with size counter
	buff = kmalloc(sizeof(struct buff_struct) * counter, GFP_KERNEL);  
	i = 0;			  // index-counter
	printk("%5s %-5s  %s %-10s\n", "PID", "TTY", "TIME", "CMD");
	for_each_process (task) {	  // copy fields into buffer		
		cputime_t utime = 0;
	 	cputime_t stime = 0;
	 	thread_group_cputime_adjusted(task, &utime, &stime);
 		jiff = utime + stime;
		time_second = jiff/HZ;
		buff[i].time = time_second;
//		printk("Task %s (pid = %d)\n", task->comm, task_pid_nr(task)); 
		buff[i].pid = task_pid_nr(task);
		strncpy(buff[i].comm, task->comm, 16);	

		if (task->signal == NULL || task->signal->tty == NULL) {
			snprintf(buff[i].tty, 64, "?");
		}

		else {	
			snprintf(buff[i].tty, 64, task->signal->tty->name);
		}
		//	strncpy(buff[i].tty,task->signal->tty->name, 64);
		// TESTING in kernel-level
		// printk("TEST::  Task %s (pid = %d)\n", buff[i].comm, buff[i].pid); 			

		printk("%5d %-5s\t%lu %-10s\n", buff[i].pid, buff[i].tty, buff[i].time, buff[i].comm);			
		i++; 						

	}	

	printk("TOTAL TASKS: %d\n",counter);		
	
	if (sizeof(buff) > cap) {
		i = copy_to_user(to, buff, cap);
		printk("sizeof(buff) > cap, copied to user\n");
	}
	else {
		i = copy_to_user(to, buff, sizeof(buff));
		printk("sizeof(buff) < cap, copied to user\n");
	}

	printk("Result of copy: %d bytes left to copy\n", i);

	kfree(buff);

	return counter;
}
