#include <linux/unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define __NR_my_syscall 359
#define __NR_process_count 360 

struct buff_struct {
 	int pid;
	char comm[16];
	char tty[10];
 	unsigned long time;
};

int main () {
		
	int tasks_num;
	int size;
	tasks_num = syscall(__NR_process_count);
	printf("Number of tasks is: %d\n", tasks_num);	
	size = sizeof(struct buff_struct) * tasks_num;
	struct buff_struct buff[tasks_num];

//	buff = (struct buff_struct *) malloc(size);
	tasks_num = syscall(__NR_my_syscall, sizeof(buff), buff);
	printf("taks_num = %d\n", tasks_num);
	
	int i;
	printf("%5s %-5s  %s %-10s\n", "PID", "TTY", "TIME", "CMD");
	
	for (i = 0; i < tasks_num; i++) {
		printf("i = %d\n", i);
		printf("%5d %-5s\t%lu %-10s\n", buff[i].pid, buff[i].tty, buff[i].time, buff[i].comm);			
	}
//	free (buff); //Make sure to do garbage collection after done	
	
	
	printf("Sieof buffstruct: %d\n", sizeof(struct buff_struct));
	printf("Size of buff: %d\n", sizeof(*buff));
	return 0;
}
