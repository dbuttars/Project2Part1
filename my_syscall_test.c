#include <linux/unistd.h>
#include <stdio.h>
#define __NR_my_syscall 359

int main()
{
//	Saved for formatting, as it is similar to the formatting used by
//	the ps -e call
//	printf("%5s %-5s\t%8s %-10s\n", "PID", "TTY", "TIME", "CMD");
//	printf("%d\n", syscall(__NR_my_syscall));
//	printf("%5s %-5s\t%8s %-10s\n", "1", "?", "00:00:31", "init");
	
	int buff[1024]; 				//Initialize our data buffer for the PID data
	syscall(__NR_my_syscall, sizeof(buff), buff);	//Call the syscall, which should copy over the
							//PID data to our buffer
	
	int i; //Simple iteration int
	for (i = 0; i < 1024; i++){ 	//There are a maximum of 1024 ints in the buffer so don't try to
					//read past that
						
		printf("PID: %d\n", buff[i]); 	//Print out the PID from the buffer 
		if (buff[(i+1)] == 0) i = 1024; 	//Stop the looping if the PID of the next value in the buff
						//is 0 (means the rest of the buffer is empty)
	}

	return 0;
}
