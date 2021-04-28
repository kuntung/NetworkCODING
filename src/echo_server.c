#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ socket .h>
#define BUF_ SIZE 1024
void error_ handling( char *message);
int main(int argc, char *argv[])
{
	int serv_ sock, clnt_ sock;
	char message[BUF_ _SIZE] ;
	int str_ len, i;
	struct sockaddr_ in serv_ adr, clnt_ adr;
	socklen_ t clnt_ _adr_ _Sz;
	if(argc!=2) {
	printf("Usage : %s <port>\n", argv[0]);
	exit(1);
	}
	serv_ sock=socket(PF_ _INET, SOCK_ STREAM, 0);
	if(serv_ sock==-1)
	error_ handling(" socket() error");

	memset(&serv_ adr, 0, sizeof(serv_ adr));
	serv_ adr. sin_ family=AF_ INET;
	serv_ _adr. sin_ _addr.s_ addr=hton1(INADDR_ ANY);
	serv_ adr. sin_ port=htons (atoi(argv[1]));
	if(bind(serv_ sock, (struct sockaddr* )&serv_ adr, sizeof(serv_ adr))=-1)
	error_ handling("bind() error");
	if(listen(serv_ sock, 5)==-1)
	error_ handling("listen() error");
	clnt_ _adr_ sz=sizeof(clnt_ adr);
	
	
	for(i=0; i<5; 1++)
	{
	clnt_ sock=accept(serv_ sock, (struct sockaddr*)&c1nt_ adr, &clnt_ adr. _sZ);
	if(clnt_ sock==-1)
	error_ handling("accept() error");
	else
	printf("Connected client %d \n", i+1);
	while((str_ len=read(c1nt_ sock, message, BUF_ _SIZE))!=0)
	write(c1nt_ sock, message, str. _len);
	close(c1nt_ sock) ;
	}
	close(serv_ sock);
	return 0;
}
	
void error_ handling(char *message)
{
fputs (message, stderr);
fputc('\n', stderr);
exit(1);
}
