//
// Created by w2w on 18-3-7.
//


#include <ctime>
#include <md/ctpmdengine.h>
#include <util/iniparser.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <zconf.h>
#include <thread>

using std::cout;
using std::endl;
using std::vector;

#define PORT1 8887
#define PORT2 8886
#define QUEUE_SIZE 20
#define BUFFER_SIZE 1024

Config* config;
CTPMdEngine* md;
void initMd(const Config* config){
    md = new CTPMdEngine();
    md->load(config);
    md->Connect();
    md->Login();
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
    if (params[0] == "subscribe"){
        string rtnStr = "Subscribe ";
        vector<string> tickers;
        for (int tickerIndex = 1; tickerIndex < params.size(); ++tickerIndex) {
            tickers.push_back(params[tickerIndex]);
            rtnStr.insert(rtnStr.length(), tickers[tickerIndex-1]);
            rtnStr.insert(rtnStr.length(), ";");
        }
        vector<string> markets;
        markets.push_back("CTP");
        md->subscribeMarketData(tickers, markets);
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

void startServer(int port){
    // 创建socket
    int server_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 将socket与IP、端口绑定
    sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET; //使用IPv4地址
    server_sockaddr.sin_port = htons(port); // 端口号
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); //任何IP地址都可以访问

    //bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }


    //listen，成功返回0，出错返回-1
    //QUEUE_SIZE connection requests will be queued before further requests are refused.
    if(listen(server_sockfd,QUEUE_SIZE) == -1)
    {
        perror("listen");
        exit(1);
    }

    ///客户端套接字
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    ///成功返回非负描述字，出错返回-1
    // 接收客户端请求, 当client端调用connect的时候继续往下
    int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    if(conn<0)
    {
        perror("connect");
        exit(1);
    }

    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer),0);
//        if(buffer[len-1] == '\n'){
//            buffer[len] = '\0';
//            cout<<"buffer[len-1] == '\\n'"<<endl;
//        } else{
//            cout<<buffer[len]<<endl;
//            cout<<"buffer[len-1] != '\\n'"<<endl;
//        }
        if(strcmp(buffer,"exit\n")==0)
            break;
        fputs("[Client]", stdout);
        fputs(buffer, stdout);
        string rtnInfo = loadCmd(buffer);
        memset(buffer,0,sizeof(buffer));
        strcpy(buffer, rtnInfo.c_str());
        // 向Client端发送数据
        send(conn, buffer, sizeof(buffer), 0);
    }
    close(conn);
    close(server_sockfd);
}

int main(int argc, char* argv[]){

    config = loadConfig("../MyConfig.ini");
    if (config != NULL){
        initMd(config);
        std::thread t1(startServer, PORT1);
        std::thread t2(startServer, PORT2);
        t1.join();
        t2.join();
//        startServer(MYPORT);
        md->Block();
    }
    return 0;
}
