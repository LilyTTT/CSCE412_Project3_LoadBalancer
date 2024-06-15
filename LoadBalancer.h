#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
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
    void balanceLoad(); // least connections
    int getClockCycles() const;
};

#endif // LOADBALANCER_H
