/*
 * Server.cpp
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */

#include <iostream>
#include <unistd.h>
#include "Server.h"

using namespace std;

Server::Server(int port)throw (const char*) {
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->fd < 0) {
        throw "socket failed";
    }

    // socket - initialize server struct
    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = INADDR_ANY;
    this->server.sin_port = htons(port);

    // bind
    if (bind(fd, (struct sockaddr*)&server, sizeof(server))<0) {
        throw "bind failure";
    }

    // listen
    if (listen(fd, 3) < 0) {
        throw "listen failure";
    }
}

void Server::start(ClientHandler& ch)throw(const char*){
    t = new thread([&ch, this](){
        while (!this->stopThread) {
            // accept
            socklen_t  clientSize = sizeof(client);
            int aClient = accept(fd, (struct sockaddr*)&client, &clientSize);
            if (aClient < 0) {
                throw "accept failure";
            }
            ch.handle(aClient);
            close(aClient);
        }
        close(fd);
    });
}

void Server::stop(){
    this->stopThread = true;
	t->join(); // do not delete this!
}

Server::~Server() {
    delete t;
}



