#ifndef SERVER_H
#define SERVER_H

#include <queue>
#include <iostream>
#include <fstream>
#include "Request.h"

using namespace std;

class Server {
private:
    int serverID;
    queue<Request> requestQueue;          // Queue to store incoming requests
    bool active;                          // Indicates if the server is active

public:
    Server(int id);
    void addRequest(const Request& request);
    void processRequests(int totCycles);
    bool isActive() const;
    void setActive(bool isActive);
    int getServerID() const;
};

#endif // SERVER_H
