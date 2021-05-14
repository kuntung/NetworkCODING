#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void mychild(int sig){
	int status;
	pid_t id = waitpid(-1, &status, WNOHANG);
	if(WIFEXITED(status))
	{
		printf("Removed proc id: %d \n", id);
		printf("Child send: %d \n", WEXITSTATUS(status));
	}

}

int main(int argc, char* argv[])
{
	pid_t pid;
	struct sigaction act;
	act.sa_handler = mychild;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	sigaction(SIGCHLD, &act, 0); //通过sigaction绑定的mychild

	pid = fork();
	if(pid == 0)
	{
		puts("Hi, I am a child process" );
		sleep(10);
		return 12;
	}
	else
	{
		printf("Child proc id: %d \n", pid);
		pid = fork();
		if(pid == 0) //另一个子进程执行区域
		{
		
			puts("Hi, I am a extra child process");
			sleep(10);
			exit(24);
		}
		else
		{
			int i;
			printf("Child proc id: %d \n", pid);
			for(i = 0; i < 5; i++)
			{
				puts("wait...");
				sleep(5);
			}
		}
	}
	return 0;
}
