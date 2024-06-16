#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <ctime>
#include <cstdlib>

/**
 * @file Request.h
 * @brief Header file for the Request class.
 */

/**
 * @brief Request class represents a network request with IP addresses and processing time.
 */
class Request {
private:
    std::string ipIn;     ///< Incoming IP address
    std::string ipOut;    ///< Outgoing IP address
    int processTime;      ///< Processing time in clock cycles

    /**
     * @brief Private method to generate a random IP address.
     * @return Randomly generated IP address as a string.
     */
    std::string generateIPAddress();

public:
    /**
     * @brief Constructor for the Request class.
     * @details Initializes the IP addresses and process time of the request.
     */
    Request();

    /**
     * @brief Getter method to retrieve the incoming IP address.
     * @return Incoming IP address as a string.
     */
    std::string getIpIn() const;

    /**
     * @brief Getter method to retrieve the outgoing IP address.
     * @return Outgoing IP address as a string.
     */
    std::string getIpOut() const;

    /**
     * @brief Getter method to retrieve the processing time of the request.
     * @return Processing time of the request in clock cycles.
     */
    int getProcessTime() const;
};

#endif // REQUEST_H
