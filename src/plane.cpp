#include "plane.hpp"
#include <iostream>
#include <random>
#include <cassert>

using namespace std;

// Plane类的实现。可以考虑在现有代码基础上进行更改。

Plane::Plane(int flt, int time, Plane_status status, CommunicationProtocal *port, int fuel_start) {
    this->flt_num = flt;
    this->clock_start = time;
    this->state = status;
	this->fuel = fuel_start;
    this->host = port; 
    /*cout << "Plane number " << flt << " ready to ";
    if (status == arriving)
        cout << "land." << endl;
    else
        cout << "take off." << endl;*/
    this->Mayday = false;
    if (status == arriving) {
        random_device r;
        mt19937 gen(r());
    	uniform_int_distribution<> dis(1, 10000);
        if (dis(gen) == 9999) {
            this->Mayday = true;
        }
    }
}

Plane::Plane() {
    this->flt_num = -1;
    this->clock_start = -1;
    this->state = null;
}

void Plane::refuse() const {
    cout << "Plane number " << this->flt_num;
    if (this->state == arriving)
        cout << " directed to another airport" << endl;
    else
        cout << " told to try to takeoff again later" << endl;
}

void Plane::land(int time) const {
    int wait = time - this->clock_start;
    //cout << time << ": Plane number " << flt_num << " landed after " << wait << " time unit" << ((wait == 1) ? "" : "s") << " in landing queue." << endl;
    this->host->report("LAND_SUCCESS", this->runway_no, this->flt_num, wait);
}

void Plane::fly(int time) const {
    int wait = time - clock_start;
    //cout << time << ": Plane number " << flt_num << " took off after " << wait << " time unit" << ((wait == 1) ? "" : "s") << " in takeoff queue." << endl;
    this->host->report("TAKEOFF_SUCCESS", this->runway_no, this->flt_num, wait);
}

int Plane::started() const {
    return this->clock_start;
}

bool Plane::isMayday() const {
    return this->Mayday;
}

void Plane::setMayday(bool s) {
    this->Mayday = s;
}

void Plane::setRunwayNo(int no) {
    this->runway_no = no;
}

int Plane::getfuel() {
	return this->fuel;
}
void Plane::usefuel() {
	this->fuel--;
    assert(this->fuel >= 0);
    if (this->fuel <= 5 and !this->Mayday) {
        this->Mayday = true;
        this->host->report("MAYDAY_FUEL", this->flt_num, this->runway_no);
    }
    if (fuel <= 0) {
        this->host->report("CRASH", this->flt_num, this->runway_no);
    }
}

Plane& Plane::operator= (const Plane &rhs) noexcept {
    this->flt_num = rhs.flt_num;
    this->clock_start = rhs.clock_start;
    this->state = rhs.state;
    this->Mayday = rhs.Mayday;
    this->fuel = rhs.fuel;
    this->runway_no = rhs.runway_no;
    this->host = rhs.host;
    
    return *this;
}
