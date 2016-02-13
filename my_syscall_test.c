#include <linux/unistd.h>
#include <stdio.h>
#define __NR_my_syscall 359

int main()
{
//	printf("%5s %-5s\t%8s %-10s\n", "PID", "TTY", "TIME", "CMD");
	printf("%d\n", syscall(__NR_my_syscall));
//	printf("%5s %-5s\t%8s %-10s\n", "1", "?", "00:00:31", "init");
	return 0;
}
