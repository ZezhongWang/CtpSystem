//
// Created by w2w on 18-3-8.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>

using std::cout;
using std::endl;

#define PORT1 8887
#define PORT2 8886

#define BUFFER_SIZE 1024

void helpInfo(){
    cout<<"************************"<<endl;
    cout<<"Help Info"<<endl;
    cout<<"\tsubscribe\t"<<"Subscribe MarketData"<<endl;
    cout<<"\tshutdown\t"<<"End the system"<<endl;
    cout<<"\texit\t"<<"Exit the client"<<endl;
    cout<<"\thelp\t"<<"Print help information"<<endl;
    cout<<"************************"<<endl;
}

void startClient(int port)
{
    ///定义sockfd
    int sock_cli = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);

    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///服务器ip

    ///连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    else{
        cout<<"Connect to MdServer Success"<<endl;
        cout<<"Type 'help' for more information";
    }
    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];

    cout<<"\n>>>";
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {
        send(sock_cli, sendbuf, strlen(sendbuf),0); ///发送
        if(strcmp(sendbuf,"exit\n")==0)
            break;
        else if(strcmp(sendbuf,"help\n")==0){
            helpInfo();
        }
        recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///接收

        fputs(recvbuf, stdout);
        cout<<"\n>>>";
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }

    close(sock_cli);

}

int main(int argc, char* argv[]){
    if (argc <= 1){
        cout<<"Please input the target tcp port"<<endl;
    }
    else{
        int port = std::atoi(argv[1]);
        cout<<"Connect to port "<<port<<endl;
        startClient(port);
    }
    return 0;
}