#include "plane.hpp"
#include <iostream>

using namespace std;

// Plane类的实现。可以考虑在现有代码基础上进行更改。

Plane::Plane(int flt, int time, Plane_status status) {
    /*
     */
    flt_num = flt;
    clock_start = time;
    state = status;
    cout << "Plane number " << flt << " ready to ";
    if (status == arriving)
        cout << "land." << endl;
    else
        cout << "take off." << endl;
}

Plane::Plane() {
    /*
     */
    flt_num = -1;
    clock_start = -1;
    state = null;
}

void Plane::refuse() const {
    cout << "Plane number " << flt_num;
    if (state == arriving)
        cout << " directed to another airport" << endl;
    else
        cout << " told to try to takeoff again later" << endl;
}

void Plane::land(int time) const {
    int wait = time - clock_start;
    cout << time << ": Plane number " << flt_num << " landed after " << wait << " time unit" << ((wait == 1) ? "" : "s") << " in landing queue." << endl;
}

void Plane::fly(int time) const {
    int wait = time - clock_start;
    cout << time << ": Plane number " << flt_num << " took off after " << wait << " time unit" << ((wait == 1) ? "" : "s") << " in takeoff queue." << endl;
}

int Plane::started() const {
    return clock_start;
}

bool Plane::isMayday() const {
    return Mayday;
}
