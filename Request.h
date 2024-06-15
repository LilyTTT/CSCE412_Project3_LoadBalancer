#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <ctime>
#include <cstdlib>

class Request {
private:
    std::string ipIn;    
    std::string ipOut;   
    int processTime;          

    std::string generateIPAddress();

public:
    Request();
    std::string getIpIn() const;
    std::string getIpOut() const;
    int getProcessTime() const;
};

#endif // REQUEST_H
