#include <stdio.h>
#include <fcntl.h>

#define BUF_SIZE 3

int main(int argc, char* argv[])
{
	int fd1, fd2; //保存在fd1和fd2的是文件描述符
	int len;
	char buf[BUF_SIZE];
	
	fd1 = open("news.txt", O_RDONLY); //以只读的方式打开news.txt
	fd2 = open("cpy.txt", O_WRONLY | O_CREAT | O_TRUNC); //对cpy.txt如果有内容则销毁重建
	
	while(len = read(fd1, buf, sizeof(buf))>0)
		write(fd2, buf, len);
	
	close(fd1);
	close(fd2);

	return 0;
}
