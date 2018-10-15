#ifndef DELEGATE_HPP
#define DELEGATE_HPP

#include <string>

using namespace std;

class CommunicationProtocal {
public:
    virtual void report(string msg, int flt_no, ...) = 0;
};

#endif
