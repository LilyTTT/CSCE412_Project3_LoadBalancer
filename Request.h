#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Request {
private:
    string ipIn;    
    string ipOut;   
    int processTime;          

    std::string generateIPAddress();

public:
    Request();
    string getIpIn() const;
    string getIpOut() const;
    int getProcessTime() const;
};

#endif // REQUEST_H
