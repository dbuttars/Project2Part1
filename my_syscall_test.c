#include <linux/unistd.h>
#include <stdio.h>
#define __NR_my_syscall 359

int main()
{
//	printf("%5s %-5s\t%8s %-10s\n", "PID", "TTY", "TIME", "CMD");
//	printf("%d\n", syscall(__NR_my_syscall));
//	printf("%5s %-5s\t%8s %-10s\n", "1", "?", "00:00:31", "init");
	
	int array [1000];
	int i;		
	for (i = 0; i < 1000; i++) {
		array[i] = 0;
	}	
	printf("%d\n",	syscall(__NR_my_syscall, array));
	
//	for (i = 0; i < 1000; i++) {
//		printf("PID: %d\n", array[i]);
//	}	

	return 0;
}
