//
// Created by w2w on 18-3-7.
//
/*
 * @Author: w2w
 * @Date: 2018-02-28 22:10:38
 * @Last Modified by: w2w
 * @Last Modified time: 2018-03-01 12:31:08
 */


#define M_TICKER "rb1801"

#include <ctime>
#include <td/ctptdengine.h>
#include <util/iniparser.h>
#include <ctime>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <vector>
#include <thread>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <net/server.h>

Config* config;
using std::cout;
using std::endl;
using std::vector;

#define PORT1 8877
#define PORT2 8876
#define QUEUE_SIZE 20
#define BUFFER_SIZE 1024
#define FDSIZE 50
#define EPOLLEVENTS 50

CTPTdEngine* td;


void initTd(Config *config){
    td = new CTPTdEngine();
    td->load(config);
    td->Connect();
    td->Login();
}


std::vector<std::string> split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;

    str+=pattern;//扩展字符串以方便操作
    int length=str.length();

    for(int i=0; i<length; i++)
    {
        pos=str.find(pattern,i);
        if(pos<length)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}



string loadCmd(char *inputstr){
    /*
     * 字符串分割，分割成 argsc, args[]
     * -t 合约号 -f 输出文件路径
     */
    string input = inputstr;
    // 去除/n
    input.erase(input.length() -1 );
    vector<string> params = split(input, " ");
    if (params[0] == "io"){
        if (params.size() < 5){
            return "No Enough Parameters";
        }
        string rtnStr = "Insert Order";
        string instrument_id = params[1];
        string direction = params[2];
        string price = params[3];
        string volume = params[4];
        td->req_limit_order_insert(instrument_id, direction, price, volume);
        rtnStr.insert(rtnStr.length(), " Success");
        return rtnStr;
    }
    else if(params[0] == "help"){
        return "";
    }
    else{
        string errorInfo = "Incorrect command";
        return errorInfo;
    }
}


//void startServer(int port){
//    // 创建socket
//    int server_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//    // 将socket与IP、端口绑定
//    sockaddr_in server_sockaddr;
//    server_sockaddr.sin_family = AF_INET; //使用IPv4地址
//    server_sockaddr.sin_port = htons(port); // 端口号
//    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); //任何IP地址都可以访问
//
//    //bind，成功返回0，出错返回-1
//    if(bind(server_sockfd,(sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
//    {
//        perror("bind");
//        exit(1);
//    }
//
//
//    //listen，成功返回0，出错返回-1
//    //QUEUE_SIZE connection requests will be queued before further requests are refused.
//    if(listen(server_sockfd,QUEUE_SIZE) == -1)
//    {
//        perror("listen");
//        exit(1);
//    }
//
//    ///客户端套接字
//    char buffer[BUFFER_SIZE];
//    struct sockaddr_in client_addr;
//    socklen_t length = sizeof(client_addr);
//
//    ///成功返回非负描述字，出错返回-1
//    // 接收客户端请求, 当client端调用connect的时候继续往下
//    int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
//    if(conn<0)
//    {
//        perror("connect");
//        exit(1);
//    }
//
//    while(1)
//    {
//        memset(buffer,0,sizeof(buffer));
//        int len = recv(conn, buffer, sizeof(buffer),0);
////        if(buffer[len-1] == '\n'){
////            buffer[len] = '\0';
////            cout<<"buffer[len-1] == '\\n'"<<endl;
////        } else{
////            cout<<buffer[len]<<endl;
////            cout<<"buffer[len-1] != '\\n'"<<endl;
////        }
//        if(strcmp(buffer,"exit\n")==0)
//            break;
//        fputs("[Client]", stdout);
//        fputs(buffer, stdout);
//        string rtnInfo = loadCmd(buffer);
//        memset(buffer,0,sizeof(buffer));
//        strcpy(buffer, rtnInfo.c_str());
//        // 向Client端发送数据
//        send(conn, buffer, sizeof(buffer), 0);
//    }
//    close(conn);
//    close(server_sockfd);
//}

int main(int argc, char* argv[]){
    config = loadConfig("../MyConfig.ini");
    if (config != NULL){
        initTd(config);
        Server tdServer = Server();
        tdServer.socketBind("0.0.0.0", PORT1);
        tdServer.doEpoll();
        td->Block();
    }
    return 0;
}


//int main(int argc, char* argv[]){
//    config = loadConfig("../MyConfig.ini");
//    if (config != NULL){
//        initTd(config);
//        std::thread t1(startServer, PORT1);
//        std::thread t2(startServer, PORT2);
//        t1.join();
//        t2.join();
//        td->Block();
//    }
//    return 0;
//}