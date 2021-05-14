#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char* message);

int main(int argc, char* argv[])
{
	int recv_sock;
	int str_len;
	char buf[BUF_SIZE];
	struct sockaddr_in adr;
	
	if(argc != 2 )
	{
		printf("Usage: %s <PORT>\n", argv[0]);
		exit(1);
	}
	
	recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
	memset(&adr, 0, sizeof(adr));
	adr.sin_family = AF_INET; //IPv4地址
	adr.sin_addr.s_addr = htonl(INADDR_ANY); //设定主机的任一IP都可以接受
	adr.sin_port = htons(atoi(argv[1])); //设置主机的端口号
	
	if(bind(recv_sock, (struct sockaddr*)&adr, sizeof(adr)) == -1)
		error_handling("bind() error"); //创建有链接的UDP
		
	//setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&join_adr, sizeof(join_adr)); //不需要加入多播组
	while(1)
	{
		str_len = recvfrom(recv_sock, buf, BUF_SIZE - 1, 0, NULL, 0);
		if(str_len < 0) break;
		buf[str_len] = 0;
		fputs(buf, stdout);
	}	
	
	close(recv_sock);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}