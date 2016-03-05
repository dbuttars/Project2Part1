#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/init.h>		
#include <linux/sched.h>		
#include <linux/signal.h>
#include <linux/delay.h>
#include <linux/list.h>
#include <linux/kthread.h>

struct task_struct *task;

// thread function from pdf slide
int my_kthread_function(void* data){
	while(!kthread_should_stop()){
		struct list_head *p; // part od sched.h
		struct task_struct tsk;

		msleep(1000);	// most of the time the thread sleeps
				// check every second
		// read_lock(&tasklist_lock); // Take tasklist_lock before you iterate each process.
		rcu_read_lock();
		for_each_process(task){
			list_for_each(p, &(task->children)){ 	
				tsk = *list_entry(p, struct task_struct, sibling); //check each child
				//** do 
			}
		}
		//read_unlock(&tasklist_lock);//Release tasklist_lock after you are done.
		rcu_read_unlock();

		oom_kill_process(p);
	}
	return 0;
}

void oom_kill_process (){
	// find vitim process
	// ...
	send_sig_info(SIGKILL, SEND_SIG_FORCED, this_task); // kill the victim
	// ...
	for_each_process(task) {
		if (!process_shares_mm(task, mm))
			continue;
		else
			send_sig_info(SIGKILL, SEND_SIG_FORCED, task);
	}
}

// ************* module stats here
static int __init forkbomb(void){
	int data = 20;
	// create and wake a thread: run in background
	task = kthread_run(&my_kthread_function,(void*)data,"my_kthread");

	return 0;
}
// ************* module end here
static void __exit forkbomb_exit(void){
	// stop thread in the end
	// int kthread_stop(task);
}

module_init(forkbomb);
module_exit(forkbomb_exit);
