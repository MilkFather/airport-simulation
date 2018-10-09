#ifndef EXQUEUE_HPP
#define EXQUEUE_HPP

#include "plane.hpp"
#include <queue>

using namespace std;

enum Error_code {success, fail, overflow, underflow};

class Extended_queue {
    queue<Plane> q;
    
public:
    Error_code append(const Plane &n);
    Error_code serve();
    Error_code retrive(Plane &n) const;
    size_t size() const;
    bool empty() const;
};

#endif
