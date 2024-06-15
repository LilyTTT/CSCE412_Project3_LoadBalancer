#include "Request.h"
using namespace std;

// Constructor
Request::Request() {
    ipIn = generateIPAddress();
    ipOut = generateIPAddress();
    processTime = rand() % 5 + 1;  // in units of clock cycle
}

// Private method to generate random IP address
string Request::generateIPAddress() {
    return to_string(rand() % 256) + "." +
           to_string(rand() % 256) + "." +
           to_string(rand() % 256) + "." +
           to_string(rand() % 256);
}

// Getter methods
string Request::getIpIn() const {
    return ipIn;
}

string Request::getIpOut() const {
    return ipOut;
}

int Request::getProcessTime() const {
    return processTime;
}
