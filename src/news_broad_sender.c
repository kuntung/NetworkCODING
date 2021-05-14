#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TTL 64 //因为没有经过理由转发就不需要TTL
#define BUF_SIZE 30

void error_handling(char* message);

int main(int argc, char* argv[])
{
	int send_sock;
	struct sockaddr_in broad_adr;
    int brd_tag = 1;
	int time_live = TTL;
	FILE* fp;
	char buf[BUF_SIZE];
	
	if(argc != 3) //接受三个参数。因为不像服务端可以指定IP地址为INADDR_ANY
	{
		printf("Usage: %s <GroupIP> <PORT>\n", argv[0]);
		exit(1);
	}
	
	send_sock = socket(PF_INET, SOCK_DGRAM, 0); //使用UDP协议
	memset(&broad_adr, 0, sizeof(broad_adr));
	broad_adr.sin_family = AF_INET;
	broad_adr.sin_addr.s_addr = inet_addr(argv[1]); //broadcast IP
	broad_adr.sin_port = htons(atoi(argv[2])); //Port
    
    setsockopt(send_sock, SOL_SOCKET, SO_BROADCAST, (void*)&brd_tag, sizeof(brd_tag));//但是需要打开广播
	//setsockopt(send_sock, IPPROTO_IP, IP_MULTICAST_TTL, (void*)&time_live, sizeof(time_live)); //不需要设置TTL
	
	if((fp = fopen("news.txt", "r")) == NULL) 
		error_handling("fopen() error");
	while(!feof(fp)) //Broadcasting
	{
		fgets(buf, BUF_SIZE, fp);
		sendto(send_sock, buf, strlen(buf), 0, (struct sockaddr*)&broad_adr, sizeof(broad_adr)); //因为是通过UDP套接字传输数据，因此使用sendto函数。
        //send(clnt_sock, buf, sizeof(buf));
        //write(clnt_sock, buf, str_len ); tcp的write不需要提供IP地址等
		sleep(2);
	}	
	fclose(fp); //关闭打开的文件
	close(send_sock);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}