#include "Server.h"

Server::Server(int id, Counter& counter) : clockCounter(counter) {
    serverID = id;
    active = false; // Server starts inactive
    stop = false;
}

Server::Server(const Server& other)
    : serverID(other.serverID), requestQueue(other.requestQueue), active(other.active), clockCounter(other.clockCounter) {
}

Server& Server::operator=(const Server& other) {
    if (this != &other) { // Check for self-assignment
        serverID = other.serverID;
        requestQueue = other.requestQueue;
        clockCounter = other.clockCounter;

        active = false;
    }
    return *this;
}

void Server::addRequest(const Request& request) {
    requestQueue.push(request);
}

void Server::processRequests(int limit) {
    // cout << clockCounter.getCycles() << endl;

    ofstream logFile("log.txt", ios::app); // Open file for logging
    Request currentRequest;
    int processTime = 0;

    if (!active) {
        active = true; // Activate the server if it was inactive
        logFile << "Clock cycle: " << clockCounter.getCycles() << " | Server ID " << serverID << " activated \n";
    }

    if (!requestQueue.empty()) {
        currentRequest = requestQueue.front();
        requestQueue.pop();
        processTime = clockCounter.getCycles() + currentRequest.getProcessTime();
        logFile << "Clock cycle: " << clockCounter.getCycles() << " | Server ID " << serverID << " is processing request with inAddress: " << currentRequest.getIpIn() << ", outAddress: " << currentRequest.getIpOut() << ", processTime: " << currentRequest.getProcessTime() << " clock cycles \n";
    }

    while (!stop && clockCounter.getCycles() != limit) {
        if (clockCounter.getCycles() == 10000) {
            logFile << "10000 clock cycles reached, end of log";
            logFile.close();
        }
        else if (clockCounter.getCycles() == limit){
            break;
        }

        if (clockCounter.getCycles() < processTime) { 
            continue;
        }
        else if (clockCounter.getCycles() >= processTime) {
            // If the last request has been processed
            if (logFile.is_open()) {
                logFile << "Clock cycle: " << clockCounter.getCycles() << " | Server ID " << serverID << " finished processing request with inAddress: " << currentRequest.getIpIn() << ", outAddress: " << currentRequest.getIpOut() << ", processTime: " << currentRequest.getProcessTime() << " clock cycles \n";
            }

            if (requestQueue.empty()) {
                break;
            }

            currentRequest =requestQueue.front();
            requestQueue.pop();
            processTime =  clockCounter.getCycles() + currentRequest.getProcessTime();

            if (logFile.is_open()) {
                logFile << "Clock cycle: " << clockCounter.getCycles() << " | Server ID " << serverID << " is processing request with inAddress: " << currentRequest.getIpIn() << ", outAddress: " << currentRequest.getIpOut() << ", processTime: " << currentRequest.getProcessTime() << " clock cycles \n";
            }
        }
    }

    active = false;
    if (logFile.is_open()) {
        logFile << "Clock cycle: " << clockCounter.getCycles() << " | Server ID " << serverID << " deactivated \n";
    }

    logFile.close();
}

void Server::Stop() {
    stop = true;
}

bool Server::isActive() const {
    return active;
}

int Server::getServerID() const {
    return serverID;
}

int Server::getRequestQueueSize() {
    return requestQueue.size();
}
