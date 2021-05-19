#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    FILE *fp;
    int fd = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC); //创建文件描述符
    if(fd == -1)
    {
        fputs("file open error", stdout);
        return -1;
    }
  	fp = fdopen(fd, "w"); //将文件描述符fd通过fdopen转换为FILE*,并且打开模式为w
    fputs("Network C progamming \n", fp); //通过标准I/O的fputs写入字符串"Network C programming"
    	
    fclose(fp);
    
    return 0;
}
