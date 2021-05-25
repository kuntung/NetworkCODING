#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <iostream>


int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int rt = bind(sock,(sockaddr*)& addr, sizeof(addr));
    assert(rt != -1);

    rt = listen(sock, 10);
    assert(rt != -1);
    bool state = false;
    sleep(10);
    sockaddr_in client;
    socklen_t client_len = sizeof(client);
    while (!state) {
        int sock_new = accept(sock, (sockaddr*)& client, &client_len);
        if(sock_new != -1) {
            state = true;
        }          
    }
    std::cout << "net" << client.sin_port << "host:" << ntohs(client.sin_port) << "ip" << 
        client.sin_addr.s_addr;
    return 0;
}

