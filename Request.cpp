#include "Request.h"
using namespace std;

/**
 * @file Request.cpp
 * @brief Implementation file for the Request class.
 */

/**
 * @brief Constructor for the Request class.
 * @details Initializes the IP addresses and process time of the request.
 */
Request::Request() {
    ipIn = generateIPAddress();
    ipOut = generateIPAddress();
    processTime = rand() % 5 + 1;  // in units of clock cycle
}

/**
 * @brief Private method to generate a random IP address.
 * @return Randomly generated IP address as a string.
 */
string Request::generateIPAddress() {
    return to_string(rand() % 256) + "." +
           to_string(rand() % 256) + "." +
           to_string(rand() % 256) + "." +
           to_string(rand() % 256);
}

/**
 * @brief Getter method to retrieve the incoming IP address.
 * @return Incoming IP address as a string.
 */
string Request::getIpIn() const {
    return ipIn;
}

/**
 * @brief Getter method to retrieve the outgoing IP address.
 * @return Outgoing IP address as a string.
 */
string Request::getIpOut() const {
    return ipOut;
}

/**
 * @brief Getter method to retrieve the processing time of the request.
 * @return Processing time of the request in clock cycles.
 */
int Request::getProcessTime() const {
    return processTime;
}
