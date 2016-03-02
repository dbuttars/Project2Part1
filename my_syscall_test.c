#include <linux/unistd.h>
#include <stdio.h>
#define __NR_my_syscall 359
struct buff_struct {
 	int pid;
	char comm[16];
	char tty[10];
 	unsigned long time;
};
int main(){
//	printf("%5s %-5s\t%8s %-10s\n", "1", "?", "00:00:31", "init");
	
	int tasks_num ;
	int i;
	// getting data-fields from kernel-space
	struct buff_struct buff[500];
	tasks_num = syscall(__NR_my_syscall, sizeof(buff), buff);
	// iterate through struct array and display
	printf("%5s %-5s\t%6s %-10s\n", "PID", "TTY", "TIME", "CMD");
	for (i = 0; i < tasks_num; i++){
	//printf("%5d %-5s\t%7s %-10s\n",buff[i].pid, "?","00:00:31", buff[i].comm);	
	//printf("%5d %-5s\t%7s %-10s\n",buff[i].pid, buff[i].tty,"00:00:31", buff[i].comm);
printf("%5d %-5s\t%8lu %-10s\n",buff[i].pid, buff[i].tty,buff[i].time,buff[i].comm);			
	}
	return 0;
}
