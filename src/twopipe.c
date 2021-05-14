#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char* argv[])
{
	int fds1[2], fds2[2];
    char str1[] = "who are you?";
    char str2[] = "I am the parent proc！";
    char buf[BUF_SIZE];
    pid_t pid;
    
    pipe(fds1); //调用pipe函数创建管道，fds数组中保存用于I/O的文件描述符

    pipe(fds2); //调用pipe函数创建管道，fds数组中保存用于I/O的文件描述符
    pid = fork();
    if(pid == 0)
    {
		write(fds1[1], str1, sizeof(str1)); //管道入口，发送数据
        read(fds2[0], buf, BUF_SIZE);
        printf("Child proc output: %s \n", buf);
    }
    else
    {
		read(fds1[0], buf, BUF_SIZE);  //管道出口，接收数据
        printf("Parent proc output: %s \n", buf);
        write(fds2[1], str2, sizeof(str2)); //管道入口，发送数据
   	sleep(3); 
	}
    return 0;
}
