#include <iostream>
#include <vector>
#include <thread>
#include <chrono> 
#include <fstream>
#include "LoadBalancer.h"
#include "Server.h"
#include "Counter.h"

/**
 * @brief Main function to demonstrate load balancing simulation.
 * @details This function sets up servers, creates a load balancer instance,
 *          generates requests, runs the load balancer, and logs results.
 * @return Exit status.
 */
int main() {
    // Prep log file
    std::ofstream logFile("log.txt");
    logFile.clear();
    logFile << "----------------------Start logging----------------------\n\n";
    logFile << "Tasks process time range from 1-5 clock cycles\n";

    // Get number of servers from user input
    int numServers;
    std::cout << "Enter the number of servers: ";
    std::cin >> numServers;

    // Create vector of Server instances
    Counter clockCounter;
    std::vector<Server> servers;
    for (int i = 0; i < numServers; ++i) {
        Server newServer(i+1, clockCounter);
        servers.push_back(newServer);
    }

    // Create LoadBalancer instance with the servers
    LoadBalancer loadBalancer(servers, clockCounter);

    // Generate a full queue of requests (servers * 100)
    int numRequests = numServers * 800;
    for (int i = 0; i < numRequests; ++i) {
        Request newRequest;
        loadBalancer.addRequest(newRequest);
    }

    logFile << "Initial queue size: " << loadBalancer.getRequestQueueSize() << "\n";
    logFile.close();

    // Get time to run the load balancer from user input (in clock cycles)
    int numClockCycles;
    std::cout << "Enter the time to run the load balancer (in clock cycles): ";
    std::cin >> numClockCycles;

    // Run the load balancer for the specified time
    loadBalancer.balanceLoad(numClockCycles);

    // Print the total clock cycles after running the load balancer
    std::ofstream appendFile("log.txt", std::ios::app);
    appendFile << "Final queue size: " << loadBalancer.getRequestQueueSize() << "\n\n";
    appendFile.close();
    std::cout << "Total clock cycles: " << clockCounter.getCycles() << std::endl;

    return 0;
}
