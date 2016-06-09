#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <thread>
#include <iostream>
#include <vector>
#include "clientecomando.h"

using namespace std;

class Socket : public QObject
{
    Q_OBJECT

public:
    int portnum;
    char* ip;
    bool ligado;
    bool pass;
    Comando comando;
    Socket(int, char*);
    ~Socket();
    void start();
    void run();
    void setIp(char*);
    void setPort(int);
    void changeStat(bool);

signals:
    void update();


private:
    void socketHandler(int, Comando);


    std::thread connect;

};

#endif // SERVIDOR_H
