#ifndef SERVER_H
#define SERVER_H

#include <queue>
#include <iostream>
#include <fstream>
#include "Request.h"
#include "Counter.h"

/**
 * @file Server.h
 * @brief Header file for the Server class.
 */

using namespace std;

/**
 * @brief Server class represents a server handling incoming requests.
 */
class Server {
private:
    int serverID;                     ///< Unique ID of the server
    bool active;                      ///< Indicates if the server is active
    queue<Request> requestQueue;      ///< Queue to store incoming requests
    Counter& clockCounter;            ///< Reference to a Counter object for tracking clock cycles
    bool stop = false;                ///< Flag to stop processing requests

public:
    /**
     * @brief Constructor for the Server class.
     * @param id The ID of the server.
     * @param counter Reference to a Counter object for tracking clock cycles.
     */
    Server(int id, Counter& counter);

    /**
     * @brief Copy constructor for the Server class.
     * @param other The Server object to copy from.
     */
    Server(const Server& other);

    /**
     * @brief Assignment operator overload for the Server class.
     * @param other The Server object to assign from.
     * @return Reference to this Server object after assignment.
     */
    Server& operator=(const Server& other);

    /**
     * @brief Stops the server from processing further requests.
     */
    void Stop();

    /**
     * @brief Adds a request to the server's request queue.
     * @param request The Request object to add.
     */
    void addRequest(const Request& request);

    /**
     * @brief Processes requests from the server's queue until a limit is reached.
     * @param limit The maximum number of clock cycles to run processing.
     */
    void processRequests(int limit);

    /**
     * @brief Checks if the server is currently active.
     * @return true if the server is active, false otherwise.
     */
    bool isActive() const;

    /**
     * @brief Retrieves the ID of the server.
     * @return The ID of the server.
     */
    int getServerID() const;

    /**
     * @brief Retrieves the size of the request queue.
     * @return The number of requests in the server's queue.
     */
    int getRequestQueueSize();
};

#endif // SERVER_H
