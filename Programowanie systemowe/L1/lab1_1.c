#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>


int main(void) {
	long ID;
	ID = fork();
	printf("id=%ld\n", ID);
	
	if(ID==0){
		printf ( "Child, Child PID: %d\n", getpid());
		printf ( "Child, Parent PID: %d\n", getppid());
	}
	else{
		printf ( "Parent, Parent PID: %d\n", getpid());
		printf ( "Parent, Child PID: %ld\n", ID);
	}
	return(0);
}

