#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

	pid_t pid = fork();
	if(pid == 0) puts("hi, I am a child process");
	else{
		
		 printf("Child process Id: %d \n", pid);
		 sleep(30);
	}

	if(pid == 0) puts("End child process");
	else puts("End parent process");

	return 0;

}
