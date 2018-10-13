#include "plane.hpp"
#include <iostream>
#include <random>

using namespace std;

// Plane类的实现。可以考虑在现有代码基础上进行更改。

Plane::Plane(int flt, int time, Plane_status status, CommunicationProtocal *port) {
    flt_num = flt;
    clock_start = time;
    state = status;
    host = port; /*
    cout << "Plane number " << flt << " ready to ";
    if (status == arriving)
        cout << "land." << endl;
    else
        cout << "take off." << endl;*/
    if (status == arriving) {
        random_device r;
        mt19937 gen(r());
    	uniform_int_distribution<> dis(1, 10000);
        if (dis(gen) == 9999) {
            Mayday = true;
        }
    }

    if (isMayday())
        host->report("MAYDAY", flt);
}

Plane::Plane() {
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
    //cout << time << ": Plane number " << flt_num << " landed after " << wait << " time unit" << ((wait == 1) ? "" : "s") << " in landing queue." << endl;
    host->report("LAND_SUCCESS", runway_no, flt_num, wait);
}

void Plane::fly(int time) const {
    int wait = time - clock_start;
    //cout << time << ": Plane number " << flt_num << " took off after " << wait << " time unit" << ((wait == 1) ? "" : "s") << " in takeoff queue." << endl;
    host->report("TAKEOFF_SUCCESS", runway_no, flt_num, wait);
}

int Plane::started() const {
    return clock_start;
}

bool Plane::isMayday() const {
    return Mayday;
}

void Plane::setRunwayNo(int no) {
    runway_no = no;
}
