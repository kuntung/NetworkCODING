#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int status;
	pid_t pid = fork(); //创建子进程
	if(pid == 0)
	{
		sleep(15);
		return 24;
	}
	else{

	while(!waitpid(-1, &status, WNOHANG))
	{sleep(3); puts("sleep 3sec.");}//在没有子进程终止的时候，每隔3s扫描一次

	if(WIFEXITED(status)) printf("child send %d \n", WEXITSTATUS(status));
	
	}	
	
	return 0;
}
