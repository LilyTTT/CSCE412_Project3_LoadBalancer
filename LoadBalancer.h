#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
#include <thread>
#include <fstream>
#include "Server.h"
#include "Request.h"
#include "Counter.h"

class LoadBalancer {
private:
    std::queue<Request> requestQueue; // Queue of incoming requests
    std::vector<Server> servers;
    Counter& clockCounter;

public:
    LoadBalancer(const std::vector<Server>& servers, Counter& counter);
    void addRequest(const Request& request);
    void balanceLoad(int numClockCycles); // Least connections
    int getClockCycles() const;
    int getRequestQueueSize() const;
};

#endif // LOADBALANCER_H
