#include <linux/unistd.h>
#include <stdio.h>
#define __NR_my_syscall_num 359
#define __NR_my_syscall 360
struct buff_struct {
 	int pid;
	char comm[64];
};

int main(){
//	Saved for formatting, as it is similar to the formatting used by
//	the ps -e call
//	printf("%5s %-5s\t%8s %-10s\n", "PID", "TTY", "TIME", "CMD");
//	printf("%d\n", syscall(__NR_my_syscall));
//	printf("%5s %-5s\t%8s %-10s\n", "1", "?", "00:00:31", "init");
	
	// 1.step get total number of taks
	int tasks_num;
	tasks_num = syscall(__NR_my_syscall_num);
	printf("Task_num:%u\n",tasks_num ); 	
			
	// 2.getting data-fields from kernel-space
	struct buff_struct buff[2000];
	syscall(__NR_my_syscall, tasks_num, sizeof(buff), buff);
	int i;
	for (i = 0; i < tasks_num; i++){ 
		printf("PID: %u\n", buff[i].pid ); 	
		printf("NAME: %s\n", buff[i].comm ); 				
	}
	return 0;
}
