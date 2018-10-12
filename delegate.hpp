#ifndef DELEGATE_HPP
#define DELEGATE_HPP

class CommunicationProtocal {
    virtual void reportMayday(int runway_no, int flt_no) = 0;
    virtual void reportCrash(int runway_no, int flt_no) = 0;
};

#endif
