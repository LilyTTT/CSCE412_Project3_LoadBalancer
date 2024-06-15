#include "Server.h"

Server::Server(int id, Counter& counter) {
    clockCounter = counter;
    serverID = id;
    active = false; // Server starts inactive
}

void Server::addRequest(const Request& request) {
    requestQueue.push(request);
    if (!active) {
        active = true; // Activate the server if it was inactive
        ofstream logFile("log.txt", ios::app); // Open file for logging
        logFile << "Server ID " << serverID << "deactivated \n";
        logFile.close();
    }
}

void Server::processRequests() {
    ofstream logFile("log.txt", ios::app); // Open file for logging
    Request currentRequest;
    int processTime = 0;
    int cycles = 0;

    if (!requestQueue.empty()) {
        currentRequest = requestQueue.front();
        requestQueue.pop();
        processTime = currentRequest.getProcessTime();
        logFile << "Server ID " << serverID << " is processing request with inAddress: " << currentRequest.getIpIn() << ", outAddress: " << currentRequest.getIpOut() << ", processTime: " << processTime << " clock cycles \n";
    }

    while (true) {
        if (clockCounter.getCycles() == 10000) {
            logFile << "10000 clock cycles reached, end of log";
            logFile.close();
        }

        if (cycles <= processTime) {
            cycles++;
        }
        else if (cycles > processTime) {
            // if the last request has been processed
            if (requestQueue.empty()) {
                break;
            }

            currentRequest = requestQueue.front();
            requestQueue.pop();
            processTime = currentRequest.getProcessTime();

            if (logFile.is_open()) {
                logFile << "Server ID " << serverID << " is processing request with inAddress: " << currentRequest.getIpIn() << ", outAddress: " << currentRequest.getIpOut() << ", processTime: " << processTime << " clock cycles \n";
            }
        }
    }

    active = false;
    if (logFile.is_open()) {
        logFile << "Server ID " << serverID << "deactivated \n";
        logFile.close();
    }
}

bool Server::isActive() const {
    return active;
}

void Server::setActive(bool isActive) {
    active = isActive;
}

int Server::getServerID() const {
    return serverID;
}

int Server::getRequestQueueSize() {
    return requestQueue.size();
}
