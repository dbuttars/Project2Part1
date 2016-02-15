/*---Start of my_syscall.c---*/

#include<linux/syscalls.h> //We're a syscall
#include<linux/sched.h> //Needed for the for_each_process() macro
#include<linux/jiffies.h> //Needed to manage the time
#include<asm/uaccess.h> //Needed to use copy_to_user

struct task_struct *task; //To use the for_each_process macro

asmlinkage long sys_my_syscall(int cap, int *to)
{

	int buff[1024]; 	// Our kernel space buffer, put data in here to be transferred to userspace
	int len = 0; 		//Simple length int to keep track of how many procs we have


	for_each_process(task) {	 	//Iterates through each process curently running (the current iteration is saved in the task
						//struct and used for printing/saving 

		printk("Task %s (pid = %d)\n", task->comm, task_pid_nr(task)); 	//Print out the task info to the kern.log (TO BE REMOVED)

		buff[len] = task_pid_nr(task);					//Save the task PID into the buffer

		printk("Task saved in array as: %u\n", buff[len]); 		//Print out the saved num, for debugging purposes (TO BE REMOVED) 

		len++; 								//Iterate our length int
	}	

	//If our length is bigger than the cap set by the user
	//program then reduce the length
	if (len > cap) len = cap;

	printk("Len is %d\n", len);		//Print out the len, for debugging purposes (TO BE REMOVED)
	int size; 				//Easy way to calc the size for the copy_to_user function
	size = len * 4; 			//Each int takes up 4 bytes of memory	
	return copy_to_user(to, buff, size); 	//Copy the (size) number of bytes from (buff) to (to) 
}

/*---End of my_syscall.c---*/
