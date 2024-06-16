#include "Server.h"

/**
 * @file Server.cpp
 * @brief Implementation file for the Server class.
 */

/**
 * @brief Constructor for the Server class.
 * @details Initializes the server with an ID and a reference to a counter.
 *          The server starts inactive by default.
 * @param id The ID of the server.
 * @param counter Reference to a Counter object for tracking clock cycles.
 */
Server::Server(int id, Counter& counter) : clockCounter(counter) {
    serverID = id;
    active = false; // Server starts inactive
    stop = false;
}

/**
 * @brief Copy constructor for the Server class.
 * @details Copies the properties of another Server instance.
 * @param other The Server object to copy from.
 */
Server::Server(const Server& other)
    : serverID(other.serverID), requestQueue(other.requestQueue), active(other.active), clockCounter(other.clockCounter) {
}

/**
 * @brief Assignment operator overload for the Server class.
 * @details Assigns the properties of another Server instance to this instance.
 * @param other The Server object to assign from.
 * @return Reference to this Server object after assignment.
 */
Server& Server::operator=(const Server& other) {
    if (this != &other) { // Check for self-assignment
        serverID = other.serverID;
        requestQueue = other.requestQueue;
        clockCounter = other.clockCounter;
        active = false; // Reset the active state
    }
    return *this;
}

/**
 * @brief Adds a request to the server's request queue.
 * @param request The Request object to add.
 */
void Server::addRequest(const Request& request) {
    requestQueue.push(request);
}

/**
 * @brief Processes requests from the server's queue until a limit is reached.
 * @param limit The maximum number of clock cycles to run processing.
 */
void Server::processRequests(int limit) {
    std::ofstream logFile("log.txt", std::ios::app); // Open file for logging
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

            currentRequest = requestQueue.front();
            requestQueue.pop();
            processTime = clockCounter.getCycles() + currentRequest.getProcessTime();

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

/**
 * @brief Stops the server from processing further requests.
 */
void Server::Stop() {
    stop = true;
}

/**
 * @brief Checks if the server is currently active.
 * @return true if the server is active, false otherwise.
 */
bool Server::isActive() const {
    return active;
}

/**
 * @brief Retrieves the ID of the server.
 * @return The ID of the server.
 */
int Server::getServerID() const {
    return serverID;
}

/**
 * @brief Retrieves the size of the request queue.
 * @return The number of requests in the server's queue.
 */
int Server::getRequestQueueSize() {
    return requestQueue.size();
}
