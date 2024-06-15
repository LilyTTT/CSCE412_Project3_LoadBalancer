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

    while (clockCounter.getCycles() < numClockCycles) {
        for (auto& server : servers) {
            cout << server.getServerID() << ": " << server.getRequestQueueSize() << endl;
            int queueSize = server.getRequestQueueSize();
            if (queueSize <= minQueueSize) {
                minQueueSize = queueSize;
                selectedServer = &server;
            }
        }
        if (selectedServer) {
            selectedServer->addRequest(requestQueue.front());
            logFile << "Clock cycle: " << clockCounter.getCycles() << " | new request added to " << selectedServer->getServerID() << "\n";
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
        cout<< clockCounter.getCycles() << endl;
        
        if (clockCounter.getCycles() == numClockCycles){
            break;
        }
    }

    cout << "end";

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