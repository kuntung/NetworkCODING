[TOC]



# 第一章：理解网络编程和套接字

## 理解网络编程和套接字

<img src="C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210424162751261.png" alt="image-20210424162751261" style="zoom:50%;" />

![image-20210424163157067](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210424163157067.png)

> 服务器端创建的套接字又称为`服务器端套接字或监听套接字`
>
> 客户端程序只有：
>
> - 调用socket函数创建套接字
> - 调用connect函数向服务器端发送链接请求两个步骤

![image-20210424163443193](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210424163443193.png)

## linux文件操作

![image-20210426092218282](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426092218282.png)

 

![image-20210425210706620](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210425210706620.png)

> 1. 套接字是网络数据传输用的软件设备，为了与远程计算机进行数据传输，需要连接到因特网，而编程中的“套接字”就是用来连接该网络的工具。本身就具有连接的意义
> 2. listen：将套接字转化成可接收连接的状态，accept：接受处理连接请求
> 3. 

# 第二章：套接字类型与协议设置

## 套接字协议及其数据传输特性

**创建套接字：**

> 套接字中实际采用的最终协议信息是通过`socket`函数的第三个参数传递的，在指定的协议族范围内通过第一个参数决定第三个参数

```c
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
//domain: 套接字中使用的协议族信息
//type：套接字中数据传输类型信息
//Protocol: 计算机间通信中使用的协议信息
```

### 协议族

![image-20210426093552220](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426093552220.png)

### 套接字类型Type

套接字类型指的是套接字的数据传输方式，通过socket的第二个参数传递。只有这样才能决定创建的套接字的数据传输方式。

因为socket的第一个参数`PF_INET`协议族中也存在多种数据传输方式

#### 套接字类型1：面向连接的套接字（SOCK_STREAM)`TCP`

如果向socket函数的第二个参数传递SOCK_STREAM，将创建面向连接的套接字。

<div align="left">
    <img src="C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426094348766.png" alt="image-20210426094348766" style="zoom:50%;" />
</div>

![image-20210426095528698](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426095528698.png)

> 面向连接的套接字特点：
>
> 1. 套接字必须一一对应
> 2. 可靠的、按序传递的、基于字节的面向连接的数据传输方式的套接字
> 3. 传输的数据不存在数据边界

#### 面向消息的套接字(SOCK_DGRAM)`UDP`

![image-20210426100014663](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426100014663.png)

> **总结：**不可靠的，不按顺序传递的，以数据的高速传输为目的的套接字

### 协议的最终选择

> socket的创建取决于三个参数：协议族，数据传输类型，计算机通信协议
>
> 通常情况下，只需要前两个参数就可以创建所需的套接字，所以大部分情况下第三个参数可以传值`0`
>
> 当"同一协议族中存在多个数据传输方式相同的协议"时，即数据传输方式相同，但`协议不同，此时需要通过第三个参数具体指定协议信息`

![image-20210426100630475](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426100630475.png)

![image-20210426104817070](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426104817070.png)

# 第三章：地址族与数据序列

> 套接字的创建相当于只安装了电话机，而通过地址族等才是给套接字分配IP地址和端口号
>
> **数据传输的目的地址应同时包含：1. IP地址2. 端口号**

## 分配给套接字的IP地址和端口号

1. IP(Internet Protocol)网络协议：为`了收发网络数据而分配给计算机的值`
2. 端口号：并非赋予计算机的值，而是为了`区分程序中创建的套接字`而分配给套接字的`序号`

### 网络地址

为了使计算机连接到网络并收发数据，必须向其分配IP地址。

- IPv4，4字节地址族
- IPv6，16字节地址族

![image-20210426105630978](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426105630978.png)

### 网络地址区分方法

![image-20210426105943577](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426105943577.png)

### 用于区分套接字的端口号

> 计算机中一般配有NIC（network interface card，网络接口卡）数据传输设备，通过NIC像计算机内部传输数据
>
> 端口号是由16位构成，可分配的端口号范围是0-65535,但是0-1023是知名端口，一般分配给特定的应用程序。
>
> **虽然端口号不能重复，但是TCP套接字和UDP套接字不会共用端口号。所以允许重复。**
>
> 即：如果某tcp套接字使用9190端口号，则其他TCP套接字就无法使用该端口号，但UDP套接字可以使用

### 构建结构体来表示IPv4地址

<div align="left">
    <img src="C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426111130676.png" alt="image-20210426111130676" style="zoom:50%;" />
</div>

<div >

```c
struct sockaddr_in
{
   sa_family_t sin_family; //地址族
   uint16_t sin_pot; //16位TCP/UDP端口号
    struct in_addr sin_addr; //32位IP地址
    char sin_zero[8]; //为了使结构体sockaddr_in的大小与sockaddr结构体保持一致插入的成员，必须填充为0
};

struct in_addr{
    In_addr_t s_addr; //32位IPv4地址
};

//struct sockaddr定义
struct sockaddr
{
	sa_family_t sin_family; //地址族
    char sa_data[14]; //地址信息
};
/*
此结构体成员sa_data保存的地址信息中，需要包含IP地址和端口号。剩余部分应该填充为0
在这也是bind函数要求的，但这对于包含地址信息来讲非常麻烦，因此有了新的结构体sockaddr_in
通过将sockaddr_in的地址再转换为sockaddr型的结构体变量，传入bind
*/

//bind示例
if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    error_handling("bind() error");
```

![image-20210426111805100](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426111805100.png)

#### 结构体`sockaddr_in`的成员分析

![image-20210426112231732](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426112231732.png)

![image-20210426112830083](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426112830083.png)



## 网络字节序与地址变换

### 字节序与网络字节序

**CPU向内存保存数据的方式有两种：**

- 大端序：高位字节存放到低位地址
- 小端序：高位字节存放到高位地址
- 目前主流的CPU以小段序方式保存数据

![image-20210426113327909](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426113327909.png)

**网络字节序：为了解决接受方和发送方可能存在的字节序不同导致的数据传输问题（统一为大端序）**

![image-20210426145457351](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426145457351.png)

![image-20210426145917309](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426145917309.png)

```c
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;
    
    net_port = htons(host_port);
    net_addr = htonl(host_addr);
    
    printf("Host ordered port: %#x \n", host_port); //0x1234
    printf("Network ordered prot: %#x \n", net_port); 
    printf("Host ordered address: %#lx \n", host_addr);
    printf("Network ordered address: %#lx \n", net_addr);
    
    return 0;
}
```

![image-20210426150541937](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426150541937.png)

## 网络地址的初始化与分配

### 将字符串信息转换为网络字节序的整数型

`sockaddr_in`中保存地址信息的成员是32位整型，为了帮助我们将字符串形式的ip地址转换为32位整数型数据，因此需要通过`inet_addr`函数在转换类型的同时进行网络字节序转换

```c
#include <arpa/inet.h>

in_addr_t inet_addr(const char* string); //成功时返回32位大端序整数型值，失败时返回INADDR_NON

int inet_aton(const char* string, struct in_addr *addr); //成功时返回1，失败时返回0
//string:含有需要转换的IP地址信息的字符串地址
//addr：将保存转换结果的in_addr结构体变量的地址值

//测试代码
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
        char *addr1 = "1.2.3.4"; //小端为0x01020304
        char *addr2 = "1.2.3.256";

        unsigned long conv_addr = inet_addr(addr1);

        if(conv_addr == INADDR_NONE) printf("Error occured!\n");
        else printf("Network ordered integer addr: %#lx \n", conv_addr);

        conv_addr = inet_addr(addr2);
        if(conv_addr == INADDR_NONE) printf("Error occured!\n");
        else printf("Network ordered integer addr: %#lx \n", conv_addr);

        return 0;
}
//显示结果为
```

![image-20210426153212104](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426153212104.png)

![image-20210426153429818](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426153429818.png)

![image-20210426153746203](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426153746203.png)

**总结：三种字符串和网络字节序转换的函数**

```c
#include <arpa/inet.h>

in_addr_t inet_addr(const char* string); //成功时返回32位大端序整数型值，失败时返回INADDR_NON

int inet_aton(const char* string, struct in_addr *addr); //成功时返回1，失败时返回0
//string:含有需要转换的IP地址信息的字符串地址
//addr：将保存转换结果的in_addr结构体变量的地址值

char* inet_ntoa(struct in_addr adr); //将网络字节序整数型IP地址转换成我们熟悉的字符串形式
//成功时返回转换的字符串地址值，失败返回-1
```

![image-20210426154846175](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426154846175.png)

### 网络地址初始化

![image-20210426155206031](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426155206031.png)

![image-20210426155232848](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426155232848.png)

### 客户端地址信息初始化

在`3.3.2`节中的**网络地址信息初始化过程**主要针对服务器端而非客户端，给套接字分配IP地址和端口号主要是为了让服务器进入`listen并accept的状态`

![image-20210426155520306](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426155520306.png)

### INADDR_ANY

在3.3.2节中，每次创建服务器端套接字都要输入IP地址，因此可以通过如下方式初始化地址信息

```c
struct sockaddr_in addr;
char * serv_port = "9190";

memset(&addr, 0, sizeof(addr));
addr.sin_family = AF_INET; //协议族
addr.sin_addr.s_addr = htol(INADDR_ANY); //利用常数INADDR_ANY分配服务器端的IP地址
addr.sin_port = htons(atoi(serv_port)); //基于字符串的网络端口初始化
```

![image-20210426160022800](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426160022800.png)

![image-20210426160201861](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426160201861.png)

### 向套接字分配网络地址

在完成`sockaddr_in`结构体的初始化方法后，需要通过`bind函数`负责将初始化的地址信息分配给套接字

```c
#include <sys/socket.h>

int bind(int sockfd, struct sockaddr * myaddr, sockelent_t addrlen);
//sockfd: 要分配地址信息（IP地址和端口号）的套接字文件描述符
//myaddr：存有地址信息的结构体变量地址值
//addrlen：第二个结构体变量的长度
```

![image-20210426160836523](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426160836523.png)

## 问题探讨

### IP地址族IPv4和IPv6有何区别？在何种背景下诞生了IPv6？

> IPv4和IPv6都是IP地址族，只是长度不一样。分别是四个字节和16个字节。
>
> 为了解决IP地址消耗的问题

### 套接字地址分为IP地址和端口号，为什么需要IP地址和端口号?

> IP地址可以用来区分网络上计算机，而端口号可以在一台计算上用来区分不同套接字而设置的。
>
> 知名端口是：0-1023

### 请是大端序、小端序、网络字节序，并说明为何需要网络字节序

1. 大端序：计算机cpu向内存写入数据时，高位数据放在低位地址
2. 小端序：
3. 网络字节序：为了解决通信双方因为端序不一致而导致的数据传输问题

### 怎样表示回送地址？其含义是什么？如果向会送地址传输数据会发生什么情况？

回送地址（127.x.x.x）是本机回送地址（Loopback Address）,即`主机IP堆栈内部的IP地址，主要用于网络软件测试以及本地机进程间通信，无论什么程序，一旦使用回送地址发送数据，协议软件立即返回之，不进行任何网络传输。` 属于保留测试地址,不能用，同时网络ID的第一个6位组也不能全置为“0”，全“0”表示本地网络。 

# 第四章：基于TCP的服务器端客户端（1）

> 根据数据传输方式的不同，基于网络协议的套接字一般分为`TCP套接字`和`UDP套接字`，因为TCP套接字是面向连接的，因此又称`基于流的套接字`（字节流）

## TCP/IP协议

1. 数据链路层
2. 网络层
3. 传输层
4. 应用层：将数据传输路径，数据确认过程都隐藏到套接字内部。这也是网络编程称为套接字编程的原因

### TCP服务器端的默认函数调用顺序

1. socket()创建套接字
2. bind()分配套接字地址
3. listen()等待连接请求状态
4. accept()允许连接
5. read()/write() 数据交换传输
6. close()断开链接

![image-20210426164413400](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426164413400.png)

> **等待连接请求状态：**指客户端请求连接时，受理连接前一直处于等待状态
>
> **连接请求等待队列：**允许的等待序队列的长度
>
> 准备好服务器端套接字和连接请求等待队列后，这种可接受连接请求的状态称为`等待连接请求状态`

![image-20210426165122875](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426165122875.png)

### TCP客户端的默认函数调用顺序

1. socket() 创建套接字
2. connect()请求连接
3. read() / write() 交换数据
4. close() 断开连接

> 与服务器端相比，区别就在于“请求连接”，在客户端创建套接字后向服务器端发起的连接请求。但必须在服务器端调用`listen函数后创建请求等待队列`,之后客户端才可请求连接
>
> ```c
> #include <sys/socket.h>
> 
> int connect(int sock, struct sockaddr * servaddr, socklen_t addrlen);
> //sock:客户端套接字文件描述符
> //servaddr：保存目标服务器端地址信息的变量地址值
> //addrlen：以字节为单位传递的地址变量长度
> ```
>
> 客户端在调用connect函数后，发生以下情况之一才会返回：
>
> 1. 服务器端接受连接请求（并不意味着服务器端调用accept函数，可以是进入到等待队列）**因此，connect函数返回后，并不立即进行数据交换**
> 2. 发生断网等异常情况而中断连接请求

![image-20210426170544668](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426170544668.png)

### 基于TCP的服务器端、客户端的函数调用关系

![image-20210426170917636](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426170917636.png)

![image-20210426171003838](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426171003838.png)

## 实现迭代服务器端/客户端

本节编写回声服务器端/客户端，即服务器端将客户端传输的字符串数据原封不动地传回给客户端

### 实现迭代服务器端

![image-20210426171252179](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426171252179.png)

> 门卫还在，但是换了一批面试官

![image-20210426171352752](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426171352752.png)

#### 迭代回声服务器端、客户端

![image-20210426171458563](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210426171458563.png)

> **存在的问题：**
>
> 每次调用write函数都会传递一个字符串，因此这种假设在某种程度上合理。
>
> 但是`TCP不存在数据边界`，而上述客户端是基于TCP的，因此多次调用write函数传递的字符串有可能一次性传递到服务端，此时客户端有可能从服务端收到多个字符串。
>
> 因此，还需要考虑服务器端的如下情况：字符串太长则分成两个数据包发送
>
> **解决办法：**可以提前确定接受数据的大小
>
> ****

![image-20210427154222788](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427154222788.png)

![image-20210427154358211](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427154358211.png)

![image-20210427154538803](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427154538803.png)

![image-20210427154614526](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427154614526.png)

![image-20210427154713366](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427154713366.png)



## 问题探讨

1. 客户端调用connect函数向服务器端发送连接请求，服务器端调用哪个函数后，客户端可以调用connect函数

   > 服务器端必须在socket(), bind(), listen()之后才能够接受connect()请求

2. 什么时候创建请求等待队列？它有何作用？与accept有什么关系？

   > 在服务器端套接字繁忙的时候，会创建一个请求等待序列，对于新的连接请求，按序处理
   >
   > 因此，客户端的connect成功，不一定就真正被服务器端accept，可能只是被listen的
   >
   > accept函数内部自动产生用于数据I/O的套接字，并自动与发起连接请求的客户端建立连接

3. 客户端中为何不需要调用bind函数分配地址？如果不调用bind函数，那么何时、如何向套接字分配IP地址和端口号？

   > 客户端也需要为套接字分配IP和端口，只是在调用connect函数的时候自动分配。无需调用标记的bind函数进行分配
   >
   > 何时？调用connect函数时
   >
   > 何地？系统内核中
   >
   > 如何？IP用计算机主机IP，端口随机

# 第五章：基于TCP的服务器端客户端（2）

## 回声客户端的完美实现

> **在第四章分析得到的回声客户端存在的问题：**
>
> 每次调用write函数都会传递一个字符串，因此这种假设在某种程度上合理。
>
> 但是`TCP不存在数据边界`，而上述客户端是基于TCP的，因此多次调用write函数传递的字符串有可能一次性传递到服务端，此时客户端有可能从服务端收到多个字符串。
>
> 因此，还需要考虑服务器端的如下情况：字符串太长则分成两个数据包发送

![image-20210427155112968](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427155112968.png)

![image-20210427155739156](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427155739156.png)

## 如果问题不在于回声客户端：定义应用层协议

> 回声客户端可以提前知道要接收的数据长度，但是在大多数情况下，这不太可能。
>
> 因此，需要通过`定义应用层协议:在收发数据过程中需要定好规则以表示数据的边界，或提前告知收发数据的大小`

### 计算器服务端、客户端

![image-20210427160510077](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427160510077.png)

## TCP原理

### TCP套接字中的I/O缓冲

![image-20210427164317480](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427164317480.png)

![image-20210427164452438](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427164452438.png)

![image-20210427164616412](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427164616412.png)

## 问题探讨

1. 请说明TCP套接字连接设置的三次握手过程，尤其是3次数据交换过程每次收发的数据内容

   > 首先：client向服务器端发送SEQ，并要求server返回一定格式的ACK
   >
   > Server：SEQ：告诉客户端应该以什么样的形式ACK，并且附加一个ACK对client的SEQ确认
   >
   > Client：发送server需要的SEQ，并对server的SEQ进行ACK

2. TCP是可靠的数据传输协议，但在通过网络通信的过程中可能丢失数据，请通过ACK和SEQ说明TCP通过何种机制保证丢失数据的可靠传输

3. 对方主机的输入缓冲剩余50字节空间时，若本方主机通过write函数请求传输70字节，请问tcp如何处理这种情况？

   > 通过流量控制

![image-20210428150456525](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210428150456525.png)

# 第六章：基于UDP的服务端、客户端

> TCP在不可靠的IP层进行流控制，进而实现提供可靠的数据传输服务
>
> 流控制是区分UDP和TCP的最重要标志

## UDP协议的有效性

![image-20210428151155332](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210428151155332.png)

## 实现基于UDP的服务器端、客户端

> UDP服务器端、客户端不像TCP那样在连接状态下交换数据，因此与TCP不同，无需经过连接过程。
>
> 也就是不需要调用TCP连接过程中的`listen函数`和`accept函数`

**UDP服务器端和客户端均只需一个套接字，而TCP中服务器端需要N+1个套接字，其中N为相连客户端个数**

### 基于UDP的数据I/O函数

1. 创建好TCP套接字后，传输数据时无需再添加地址信息。因为TCP套接字将保持与对方套接字的连接。因此，`TCP套接字总是知道目的地址信息`
2. UDP套接字不会保持连接状态，因此每次传递数据都要添加目标地址信息。

```c
#include <sys/socket.h>

ssize_t sendto(int sock, void *buff, size_t nbytes, int flags, struct sockaddr *to, socklen_t addrlen); //成功时返回传输的字节数，失败时返回-1
/*
1. sock: 用于传输数据的UDP套接字文件描述符
2. buff: 保存待传输数据的缓冲地址值
3. nbytes: 待传输的数据长度，以字节为单位
4. flags: 可选参数，若没有则传递0
5. to: 存有目标地址信息的sockaddr结构体变量的地址值
6. addrlen: 传递给参数to的地址值结构体变量长度
*/

ssize_t recvfrom(int sock, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen); //成功时返回接受的字节数，失败时返回-1
/*
1. sock: 用于接收数据的UDP套接字文件描述符
2. buff: 保存待接收数据的缓冲地址值
3. nbytes: 可接受的最大字节数，故无法超过参数buff所指的缓冲大小
4. flags: 可选参数，若没有则传递0
5. from: 存有发送端地址信息的sockaddr结构体变量的地址值
6. addrlen: 保存参数from的结构体变量长度的变量地址值
*/
```

## UDP客户端套接字的地址分配

在TCP客户端实现的时候，有一个通过connect同server相连接的过程。而在UDP客户端中则没有这一步骤。

![image-20210428173913259](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210428173913259.png)

## UDP的数据传输特性和调用connect函数

>  TCP传输的数据不存在数据边界，而UDP数据传输中存在数据边界
>
> UDP是具有数据边界的协议，传输中调用I/O函数的次数非常重要。因此，输入函数的调用次数应和输出函数的调用次数完全一致。这样才能保证接收全部已发送数据
>
> 例如：调用三次输出函数发送的数据必须通过调用三次输入函数才能接收完

![image-20210428174535572](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210428174535572.png)



### 已连接UDP套接字与未连接UDP套接字

![image-20210429100854001](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210429100854001.png)

### 创建已连接UDP套接字

> 创建已连接UDP套接字的过程：只需要针对UDP套接字调用connect函数
>
> `connect(sock, (struct sockaddr*)&adr, sizeof(adr));`
>
> 针对UDP套接字调用connect函数并不意味着要与对方UDP套接字连接，只是向UDP套接字注册`目标IP和端口信息`
>
> **对于已连接UDP套接字，不仅可以通过`sendto(), recvfrom()`还可以使用TCP套接字的`write和read`进行通信**

![image-20210429101607643](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210429101607643.png)

## 问题探讨

1. UDP为什么比TCP快？为什么TCP数据传输可靠而UDP数据传输不可靠？

   > UDP比TCP更快的原因是它不存在的确认支持连续的包流。由于TCP连接总是确认一组数据包(无论连接是否完全可靠)，当数据包丢失时，每一次否定确认都必须进行重传
   >
   > 这也是TCP比UDP数据传输可靠的依据。面向连接，重传，流量控制等

2. ![image-20210429102156721](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210429102156721.png)

3. 何种情况下，UDP的性能优于TCP

   > 网络带宽需求较小，而实时性要求高，大部分应用无需维持连接，需要低功耗

4. 客户端TCP套接字调用connect函数时自动分配IP和端口号，UDP不调用bind函数，而是在sendto的时候自动分配IP和端口号

5. UDP中调用connect函数的好处

   - 节省在sendto()的时候，总是会自动分配IP和端口号的时间
   - 对于经常进行数据传输的双方，UDP通过connect函数获取对方IP和端口号，可以通过`write和read`更加高效地完成数据传输工作

# 优雅地断开套接字连接

> 在前面的示例中，我们总是调用`close`或`closesocket`函数单方面断开连接，同时断开两个I/O流
>
> 本章讨论的**优雅地断开连接方式**只断开其中一个流，而非同时断开两个流

## 基于TCP的半关闭

### 套接字和流

> 将建立套接字后可交换数据的状态看作一种流
>
> 一旦两台主机间建立了套接字连接，每个主机就会拥有独立的输入流和输出流

### 针对优雅断开的shutdown函数

```c
#include <sys/socket.h>

int shutdown(int sock, int howto); //成功时返回0， 失败时返回-1
//sock:需要断开的套接字文件描述符
//howto：传递断开方式信息,SHUT_RD 断开输入流，SHUT_WR，断开输出流，SHUT_RDWR
```

### 为什么要半关闭

**存在的问题：**对于数据传输的接收方，可能不知道要接收数据到何时。因此，只能无休止的调用输入函数，这有可能导致程序阻塞（调用的函数未返回）

**解决办法：**发送端在发送完数据以后传递一个EOF表示文件传输结束。

**服务器如何传递EOF：**

- 服务器端调用close函数可以同时关闭I/O流，但是有问题就是，这样可能无法再收到客户端想发送给服务器端的数据内容。
- 因此需要选择半关闭的`SHUT_WR`

# 总结

## 关于int main中的传入参数

```c++
int main( int argc, char** argv )
{ 
     //函数体内使用或不使用argc和argv都可
     ……
     return 0;
}
```

**一、argc、argv的具体含义** 
![image-20210427161037210](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427161037210.png)

```c++
#include <stdio.h>
using namespace std;

int main(int argc, char ** argv)
{
    int i;
    printf("Argc = %d", argc);
    for (i = 0; i < argc; i++)
        printf("Argument %d is %s\n", i, argv[i]);
    return 0;
}
```

![image-20210427161521599](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427161521599.png)

> 因为命令行中argument有五个，因此argc = 5

## socket的read和write

### write函数

一旦，我们建立好了tcp连接之后，我们就可以把得到的fd当作文件描述符来使用。
ssize_t **write**(int fd, const void*buf,size_t nbytes);
**write**函数将buf中的nbytes字节内容写入文件描述符fd.成功时返回写的字节数.失败时返回-1. 并设置errno变量. 在网络程序中,当我们向套接字文件描述符写时有两可能.
1)**write**的返回值大于0,表示写了部分或者是全部的数据. 这样我们用一个while循环来不停的写入，但是循环过程中的buf参数和nbyte参数得由我们来更新。也就是说，网络写函数是不负责将全部数据写完之后在返回的。
2)返回的值小于0,此时出现了错误.我们要根据错误类型来处理.
如果错误为EINTR表示在写的时候出现了中断错误.
如果为EPIPE表示网络连接出现了问题(对方已经关闭了连接).

> **从write函数返回的时间点：**
>
> write函数和windows的send函数`并不会在完成向对方主机的数据传输时返回，而是在数据移到输出缓冲时。`但TCP会保证对输出缓冲数据的传输，所以write函数在数据传输完成时返回。

### 读函数read

ssize_t read(int fd,void *buf,size_t nbyte)
read函数是负责从fd中读取内容.当读成功 时,read返回实际所读的字节数,如果返回的值是0 表示已经读到文件的结束了,小于0表示出现了错误.如果错误为EINTR说明读是由中断引起 的, 如果是ECONNREST表示网络连接出了问题.

### fread()和fwrite()

```c
FILE* fp;
char buf[BUF_SIZE];
fp = fopen("fileName.type", "rb");

read_cnt = fread((void *)buf, 1, BUF_SIZE, fp);
fwrite((void*)buf, 1, read_cnt, fp);

fclose(fp);
```

## TCP三次握手

![image-20210427165153364](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427165153364.png)

### ACK增量

> ACK号的增量为传输的数据字节数，假设每次ACK号不加传输的字节数，这样虽然可以确认数据包的传输，但是无法确定是否全部字节都正确传递，还是存在丢失情况
>
> 因此：ACK号 = SEQ号 + 传递的字节数 + 1；
>
> 最后加1是为了告知对方下次要传递的SEQ号

## TCP四次挥手：断开套接字的连接

![image-20210427165912649](C:\Users\唐昆\AppData\Roaming\Typora\typora-user-images\image-20210427165912649.png)

## 课后参考

https://blog.csdn.net/nail_candy/article/details/88957409

https://blog.csdn.net/nail_candy/article/details/88957438

