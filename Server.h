/*
 * Server.h
 *
 * Author: 209215490 Bar Tawil
 *         208478453 Anastasiya Khizgiyaev
 *
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <thread>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "CLI.h"

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file
class SocketIO : public DefaultIO {
    int fd;
public:
    SocketIO(int clientID) {
        this->fd = clientID;
    }

    string read() {
        string buffer = "";
        char c;
        recv(this->fd, &c, sizeof(char), 0);
        while (c != '\n') {
            buffer += c;
            recv(this->fd, &c, sizeof(char), 0);
        }
        return buffer;
    }

    void write(string text) {
        send(this->fd, text.c_str(), text.size(), 0);
    }

    void write(float f) {
        stringstream ss;
        ss << f;
        string s = ss.str();
        const char *buffer = s.c_str();
        send(this->fd, buffer, s.size(), 0);
    }

    void read(float *f) {
        string buffer = "";
        char c;
        recv(this->fd, &c, sizeof(char), 0);
        while (c != '\n') {
            buffer += c;
            recv(this->fd, &c, sizeof(char), 0);
        }
        *f = stof(buffer);
    }

    ~SocketIO() {}
};

// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	public:
    virtual void handle(int clientID){
        SocketIO socketIo(clientID);
        CLI cli(&socketIo);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
    int fd;
    sockaddr_in server;
    sockaddr_in client;
    // the thread to run the start() method in
    thread* t;
    bool stopThread = false;
public:
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */
