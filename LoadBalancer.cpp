#include "LoadBalancer.h"

LoadBalancer::LoadBalancer(const vector<Server>& serverVec, Counter& counter) {
      servers = serverVec;
      clockCounter = counter;
}

void LoadBalancer::addRequest(const Request& request) {
    requestQueue.push(request);
}

void LoadBalancer::balanceLoad() {
    // least connections algorithm: find server with smallest queue size
    int minQueueSize = numeric_limits<int>::max();
    Server* selectedServer = nullptr;

    for (auto& server : servers) {
        if (!server.isActive()) {
            continue; // Skip inactive servers
        }
        int queueSize = server.getRequestQueueSize();
        if (queueSize < minQueueSize) {
            minQueueSize = queueSize;
            selectedServer = &server;
        }
    }

    if (selectedServer) {
        selectedServer->addRequest(requestQueue.front());
        selectedServer->processRequests();
        requestQueue.pop();
    }

    clockCounter.incrementCycle();
}

int LoadBalancer::getClockCycles() const {
    return clockCounter.getCycles();
}
