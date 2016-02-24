/*---Start of process_count.c---*/

#include<linux/syscalls.h> //We're a syscall
#include<linux/sched.h> //Needed for the for_each_process() macro

asmlinkage long sys_process_count (void) {
	struct task_struct *task; 	//To use the for_each_process macro
	long counter;  
	counter = 0;
	// getting total number of tasks	
	for_each_process(task) {	 	
		counter++;				
	}
	return counter;
}
