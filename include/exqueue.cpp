#ifndef EXQUEUE_HPP
#define EXQUEUE_HPP

#include <vector>

using namespace std;

template <typename T>
class exqueue {
    vector<T> v;
    int l;

public:
    int size() const {
        return this->l;
    }

    void push(T& t) {
        if (l < v.size()) {
            v[l] = t;
        } else
            this->v.push_back(t);
        l++;
    }

    void push(const T& t) {
        if (l < v.size()) {
            v[l] = t;
        } else
            this->v.push_back(t);
        l++;
    }

    T& front() {
        return this->v[0];
    }
    T& back() {
        return this->v[l - 1];
    }

    void pop() {
        v.erase(v.begin());
        l--;
    }

    void clear() {
        l = 0;
        this->v.clear();
    }

    void del(int idx) {
        if (idx < 0 or idx >= l) return;
        typename vector<T>::iterator it = v.begin();
        for (int i = 0; i < idx; i++) it++;
        v.erase(it);
        l--;
    }

    bool empty() {
        return l <= 0;
    }

    T& operator[](int idx) {
        return this->v[idx];
    }

    exqueue() {
        this->l = 0;
    }
};

#endif
