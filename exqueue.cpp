#include "exqueue.hpp"
#include <queue>

using namespace std;

Error_code Extended_queue::append(const Plane &n) {
    q.push(n);
    return success;
}

Error_code Extended_queue::serve(void) {
    /* Pop unless underflow */
    if (empty())
        return underflow;
    else {
        q.pop();
        return success;
    }
}

Error_code Extended_queue::retrive(Plane &n) const {
    /* Front unless underflow */
    if (empty())
        return underflow;
    else {
        n = q.front();
        return success;
    }
}

size_t Extended_queue::size(void) const {
    return q.size();
}

bool Extended_queue::empty(void) const {
    return q.empty();
}
