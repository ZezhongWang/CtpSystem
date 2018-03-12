//
// Created by w2w on 18-3-12.
//

#include "net/server.h"

Server::Server(int max_size, int epoll_events_size, int fd_size): max_size_(max_size)
        , epoll_events_size_(epoll_events_size), fd_size_(fd_size){
    this->hasBound = false;
    this->isEpolling =false;
}

Server::~Server() {

}
/*
 * 创建socket，并且bind端口，成功返回0,失败返回-1,已经绑定过了返回1
 */
int Server::socketBind(const char *ip, int port){
    if(hasBound){
        return 1;
    }
    int server_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 将socket与IP、端口绑定
    sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET; //使用IPv4地址
    server_sockaddr.sin_port = htons(port); // 端口号
//    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); //任何IP地址都可以访问
    inet_pton(AF_INET,ip,&server_sockaddr.sin_addr);
    //bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        return -1;
    }
    //listen，成功返回0，出错返回-1
    //QUEUE_SIZE connection requests will be queued before further requests are refused.
    if(listen(server_sockfd,20) == -1)
    {
        perror("listen");
        return -1;
    }
    this->listen_fd_ = server_sockfd;
    this->hasBound = true;
    return 0;
}

/*
 * 开始epoll，成功返回0,失败返回-1
 */
int Server::doEpoll() {
    if (!hasBound){
        perror("Please create socket first");
        return -1;
    }
    if (isEpolling){
        perror("Epoll has started.");
        return -1;
    }
    epoll_fd_ = epoll_create(fd_size_);
    struct epoll_event events[epoll_events_size_];
    addEvent(this->listen_fd_, EPOLLIN);
    isEpolling = true;
    while(true){
        int events_num = epoll_wait(this->epoll_fd_, events, this->epoll_events_size_, -1);
        int rtn = handleEvents(events, events_num);
        if (rtn == -1) break;
    }
    return 0;
}


/*
 * 返回-1结束 epoll, 返回0继续epoll
 */
int Server::handleEvents(struct epoll_event *events, int num) {
    int rtn = 0;
    for (int i = 0; i < num; ++i) {
        int fd = events[i].data.fd;
        if ( (fd == listen_fd_) && (events[i].events & EPOLLIN)){
            acceptConnect();
        }
        else if (events[i].events & EPOLLIN){
            int read_rtn = readFd(fd);
            if (read_rtn == -1) rtn = -1;
        }
        else if (events[i].events & EPOLLOUT){
            perror("There are should not be writing events");
        }
    }
    if (rtn == -1){
        return -1;
    }
    return rtn;
}

/*
 * 返回-1结束 epoll, 返回0表示正常返回
 */
int Server::readFd(int fd) {
    char buf[max_size_];
    int rtn = 0;
    int read_rtn = read(fd, buf, max_size_);
    if (read_rtn== -1){
        perror("read error");
        close(fd);
        deleteEvent(fd, EPOLLIN);
    }
    else if (read_rtn == 0){
        fprintf(stderr, "client close.\n");
        close(fd);
        deleteEvent(fd, EPOLLIN);
    }
    else{
        rtn = handleClientInput(fd, buf);
    }
    return rtn;
}

void Server::writeFd(int fd, char *buf) {
    printf("Call writeFd function\n");
    int write_rtn = write(fd, buf, max_size_);
    if (write_rtn == -1){
        perror("write error:");
        close(fd);
        deleteEvent(fd, EPOLLOUT);
    }
}

void Server::acceptConnect() {
    struct sockaddr_in cliaddr;
    socklen_t length = sizeof(cliaddr);
    int clifd = accept(listen_fd_, (struct sockaddr*)&cliaddr, &length);
    if (clifd == -1)    perror("accept error:");
    else{
        printf("accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
        addEvent(clifd, EPOLLIN);
    }

}

void Server::addEvent(int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ev);
}

void Server::deleteEvent(int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &ev);
}

void Server::modifyEvent(int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &ev);
}

int Server::handleClientInput(int fd, char *buf) {
    printf("Call handle client Input function");
    printf("[Client] %s\n", buf);
    write(fd, buf, max_size_);
}


//int main(){
//    Server s = Server();
//    s.socketBind("0.0.0.0", 8888);
//    s.doEpoll();
//}