#include "LoadBalancer.h"

LoadBalancer::LoadBalancer(const vector<Server>& serverVec, Counter& counter): clockCounter(counter) {
      servers = serverVec;
}

void LoadBalancer::addRequest(const Request& request) {
    requestQueue.push(request);
}

void LoadBalancer::balanceLoad(int numClockCycles) {
    // Least connections algorithm: find server with smallest queue size
    vector<thread> serverThreads;
    int minQueueSize = INT_MAX;
    Server* selectedServer = nullptr;
    ofstream logFile("log.txt", ios::app); // Open file for logging

    while (clockCounter.getCycles() < numClockCycles && !requestQueue.empty()) {
        // Ramdomly add new requests
        if (rand() % 5 == 1){
            Request newRequest;
            requestQueue.push(newRequest);
        }

        for (auto& server : servers) {
            int queueSize = server.getRequestQueueSize();
            if (queueSize <= minQueueSize) {
                minQueueSize = queueSize;
                selectedServer = &server;
            }
        }
        if (selectedServer) {
            selectedServer->addRequest(requestQueue.front());
            if (!selectedServer->isActive()){
                try{
                    serverThreads.emplace_back(&Server::processRequests, selectedServer, numClockCycles);
                } catch (const std::exception& e) {
                    cout << e.what() << endl;
                }
            }
            requestQueue.pop();
        }
        clockCounter.incrementCycle();

        if (clockCounter.getCycles() == numClockCycles){
            cout << "leave" << endl;
            break;
        }
    }

    for (auto& thread : serverThreads) {
        for (auto& server : servers) {
            server.Stop();
        }

        if (thread.joinable()) {
            thread.join();
        }
    } 
}

int LoadBalancer::getClockCycles() const {
    return clockCounter.getCycles();
}

int LoadBalancer::getRequestQueueSize() const {
    return requestQueue.size();
}