#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_ _SIZE 1024
void error_ handling(char *message);
int main(int argc, char *argv[])
{

	int sock;
	char message[BUF_ SIZE];
	int str_ _len;
	struct sockaddr_ in serv_ adr;
	if(argc!=3) {
	printf("Usage : %s <IP> <port>\n", argv[0]);
	exit(1);
	}
	sock=socket(PF_ INET, SOCK_ _STREAM, 0);
	if(sock==-1)
	error_ handling(" socket() error");
	memset(&serv_ adr, 0, sizeof(serv_ adr));
	serv_ adr .sin_ family=AF _INET;
	serv_ adr. sin_ addr.s_ addr=inet _addr(argv[1]);
	serv_ _adr. sin_ port=htons (atoi (argv[2]));
	if(connect(sock, (struct sockaddr*)&serv_ adr, sizeof(serv_ adr))==-1)
	error_ handling("connect() error!");
	else
	puts("Connecte..........");
	while(1){
	
	fputs("Input message(Q to quit): "£¬stdout);
	fgets(message, BUF_ SIZE, stdin);
	if(!strcmp(message, "q\n") II !strcmp(message , "Q\n"))
	break;£¬
	write(sock, message, strlen(message));
	str_ len=read(sock, message, BUF_ SIZE-1);
	message[str_ 1en]=0;
	printf( "Message from server: %s"£¬message);
	}
	close(sock);
	return 0;
	
}
	void error_ handling( char *message)
	{
		fputs(message, stderr);
		fputc('\n', stderr);
		exit(1);
	}
