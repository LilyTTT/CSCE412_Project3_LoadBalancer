#ifndef SERVER_H
#define SERVER_H

#include <queue>
#include <iostream>
#include <fstream>
#include "Request.h"
#include "Counter.h"

using namespace std;

class Server {
private:
    int serverID;
    bool active;                          // Indicates if the server is active
    queue<Request> requestQueue;          // Queue to store incoming requests
    Counter& clockCounter;
    bool stop;

public:
    Server(int id, Counter& counter);
    Server(const Server& other); // Copy constructor
    Server& operator=(const Server& other); // Copy Assignment constructor
    void Stop();
    void addRequest(const Request& request);
    void processRequests(int limit);
    bool isActive() const;
    void setActive(bool isActive);
    int getServerID() const;
    int getRequestQueueSize();
};

#endif // SERVER_H
