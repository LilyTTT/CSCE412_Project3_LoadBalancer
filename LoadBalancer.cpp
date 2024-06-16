#include "LoadBalancer.h"

/**
 * @brief Constructor for LoadBalancer class.
 * @param serverVec Vector of Server objects.
 * @param counter Reference to a Counter object for clock cycles.
 */
LoadBalancer::LoadBalancer(const vector<Server>& serverVec, Counter& counter): clockCounter(counter) {
    servers = serverVec;
}

/**
 * @brief Adds a request to the request queue.
 * @param request The Request object to add.
 */
void LoadBalancer::addRequest(const Request& request) {
    requestQueue.push(request);
}

/**
 * @brief Balances load among servers using the least connections algorithm.
 * @param numClockCycles Number of clock cycles to run the load balancing.
 */
void LoadBalancer::balanceLoad(int numClockCycles) {
    // Least connections algorithm: find server with smallest queue size
    vector<thread> serverThreads;
    vector<int> serverSize;
    int minQueueSize = INT_MAX;
    Server* selectedServer = nullptr;
    ofstream logFile("log.txt", ios::app); // Open file for logging

    while (clockCounter.getCycles() < numClockCycles && !requestQueue.empty()) {
        // Randomly add new requests
        if (rand() % 5 == 1){
            Request newRequest;
            requestQueue.push(newRequest);
        }

        serverSize.clear();

        for (auto& server : servers) {
            int queueSize = server.getRequestQueueSize();
            serverSize.push_back(queueSize);
        }

        minQueueSize = *(min_element(serverSize.begin(), serverSize.end()));

        for (auto& server : servers) {
            int queueSize = server.getRequestQueueSize();
            if (queueSize == minQueueSize) {
                selectedServer = &server;
                break;
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
            cout << "Reached maximum clock cycles." << endl;
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

/**
 * @brief Retrieves the current clock cycles count.
 * @return Current clock cycles count.
 */
int LoadBalancer::getClockCycles() const {
    return clockCounter.getCycles();
}

/**
 * @brief Retrieves the size of the request queue.
 * @return Size of the request queue.
 */
int LoadBalancer::getRequestQueueSize() const {
    return requestQueue.size();
}
