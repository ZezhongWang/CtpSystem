//
// Created by w2w on 18-3-12.
//

#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include <ctime>
#include <ctime>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <stdio.h>

class Server{
public:
    Server(int max_size=1024, int epoll_events_size=100, int fd_size=100);
    ~Server();
    int socketBind(const char *ip = NULL, int port = 8888);
    int doEpoll();
    int handleEvents(struct epoll_event *events, int num);
    void acceptConnect();
    int readFd(int fd);
    void writeFd(int fd, char *buf);
    void addEvent(int fd, int state);
    void modifyEvent(int fd, int state);
    void deleteEvent(int fd, int state);

    virtual int handleClientInput(int fd, char *buf);
private:
    char* address_;
    int port_;
    int fd_size_;
    int max_size_;
    int epoll_events_size_;
    int listen_fd_;
    int epoll_fd_;

    bool hasBound;
    bool isEpolling;
};


#endif //NETWORK_SERVER_H
