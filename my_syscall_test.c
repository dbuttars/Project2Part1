#include <linux/unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define __NR_my_syscall 359
#define __NR_process_count 360 

struct buff_struct {
 	int pid;
	char comm[16];
	char tty[10];
	char time[9];
} *buff;

int main () {		
	long tasks_num;
	tasks_num = syscall(__NR_process_count);
	printf("Number of tasks is: %ld\n", tasks_num);	
	buff = malloc(sizeof(struct buff_struct) * tasks_num);
	tasks_num = syscall(__NR_my_syscall, sizeof(buff), buff);	
	int i;
	for (i = 0; i < tasks_num; i++) {
		printf("%5d %-5s %s %-10s\n",buff[i].pid, buff[i].tty,buff[i].time,buff[i].comm);			
	}	
	return 0;
}
