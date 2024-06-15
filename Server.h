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
    queue<Request> requestQueue;          // Queue to store incoming requests
    bool active;                          // Indicates if the server is active
    Counter& clockCounter;

public:
    Server(int id, Counter& counter);
    void addRequest(const Request& request);
    void processRequests();
    bool isActive() const;
    void setActive(bool isActive);
    int getServerID() const;
    int getRequestQueueSize();
};

#endif // SERVER_H
