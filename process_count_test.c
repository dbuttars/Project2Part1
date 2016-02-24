#include <linux/unistd.h>
#include <stdio.h>
#define __NR_process_count 360 
int main () {
	
	long tasks_num;
	tasks_num = syscall(__NR_process_count);
	printf("Number of tasks is: %ld\n", tasks_num);	
	return 0;
}
