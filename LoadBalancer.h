#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
#include <thread>
#include <fstream>
#include <algorithm>
#include "Server.h"
#include "Request.h"
#include "Counter.h"

/**
 * @brief Load balancer class for distributing incoming requests among servers.
 */
class LoadBalancer {
private:
    std::queue<Request> requestQueue; ///< Queue of incoming requests
    std::vector<Server> servers;      ///< Vector of servers available for load balancing
    Counter& clockCounter;            ///< Reference to a Counter object for clock cycles

public:
    /**
     * @brief Constructor for LoadBalancer class.
     * @param servers Vector of Server objects representing available servers.
     * @param counter Reference to a Counter object for clock cycles.
     */
    LoadBalancer(const std::vector<Server>& servers, Counter& counter);

    /**
     * @brief Adds a request to the load balancer's request queue.
     * @param request The Request object to add.
     */
    void addRequest(const Request& request);

    /**
     * @brief Balances load among servers using the least connections algorithm.
     * @param numClockCycles Number of clock cycles to run the load balancing.
     * @details The function selects servers with the smallest queue size and distributes
     * incoming requests accordingly. It also logs actions to 'log.txt'.
     */
    void balanceLoad(int numClockCycles);

    /**
     * @brief Retrieves the current clock cycles count.
     * @return Current clock cycles count.
     */
    int getClockCycles() const;

    /**
     * @brief Retrieves the size of the request queue.
     * @return Size of the request queue.
     */
    int getRequestQueueSize() const;
};

#endif // LOADBALANCER_H
