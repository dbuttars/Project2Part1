/*---Start of my_syscall.c---*/

#include<linux/syscalls.h> //We're a syscall
#include<linux/sched.h> //Needed for the for_each_process() macro
#include<linux/jiffies.h> //Needed to manage the time
#include<asm/uaccess.h> //Needed to use copy_to_user

struct buff_struct {		// struct to store informations
 	int pid;
	char comm[16];
	char tty[10];
 	unsigned long time;
};

asmlinkage long sys_my_syscall( int cap, int *to){
	struct task_struct *task; 	//To use the for_each_process macro
	int counter;  
	counter = 0;
	unsigned long jiff;
	unsigned long time_second;
	// getting total number of tasks	
	for_each_process(task) {	 	
		counter++;				
	}
	
	struct buff_struct buff[counter]; // create buffer with size counter
	int i = 0;			  // index-counter
	for_each_process(task) {	  // copy fields into buffer		
		cputime_t utime = 0;
	 	cputime_t stime = 0;
	 	thread_group_cputime_adjusted(task, &utime, &stime);
 		jiff = utime + stime;
		time_second = jiff/HZ;
		buff[i].time = time_second;
		// printk("Task %s (pid = %d)\n", task->comm, task_pid_nr(task)); 
		buff[i].pid = task_pid_nr(task);
		strncpy(buff[i].comm, task->comm, 16);	
		if(task->signal == NULL || task->signal->tty == NULL)
			snprintf(buff[i].tty, 64, "?");
		else	
			snprintf(buff[i].tty, 64, "xxxxxxx");
		//	strncpy(buff[i].tty,task->signal->tty->name, 64);
		// TESTING in kernel-level
		// printk("TEST::  Task %s (pid = %d)\n", buff[i].comm, buff[i].pid); 			
		i++; 						
	}	
	// printk("TOTAL TASKS: %d\n",counter);		
	copy_to_user(to, &buff, sizeof(buff));
	return counter;
}
