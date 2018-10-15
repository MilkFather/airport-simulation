#include "runway.hpp"
#include <iostream>
#include <cassert>

using namespace std;

Runway::Runway(int limit) {
    queue_limit = limit;
}

bool Runway::try_land_queue(const Plane &current) {
    if (landing.size() < queue_limit) {
        landing.push(current);
        return true;
    } else
        return false;
}

void Runway::force_land_queue(const Plane &current) {
    landing.push(current);
}

bool Runway::try_depart_queue(const Plane &current) {
    if (takeoff.size() < queue_limit) {
        takeoff.push(current);
        return true;
    } else
        return false;
}

void Runway::activity(int time) {
    Plane moving;
    if (!mayday.empty()) {
        moving = mayday.front();
        mayday.pop();
        moving.land(time);
    } else if (!landing.empty()) {
        moving = landing.front();
        landing.pop();
        moving.land(time);
    } else if (!takeoff.empty()) {
        moving = takeoff.front();
        takeoff.pop();
        moving.fly(time);
    }
    use_fuel_plane();
}

void Runway::use_fuel_plane() {
    for (int i = landing.size() - 1; i >= 0; i--) {
        assert(landing[i].getfuel() >= 6);
        landing[i].usefuel();
    }
    for (int i = mayday.size() - 1; i >= 0; i--) {
        assert(landing[i].getfuel() >= 0);
        mayday[i].usefuel();
    }
}

void Runway::removePlane_takeoff(int flt_no, Plane &pl) {
    for (int i = 0; i < takeoff.size(); i++) {
        if (takeoff[i].flt_num == flt_no) {
            pl = takeoff[i];
            takeoff.del(i);
        }
    }
    /*debug*/
    for (int i = 0; i < takeoff.size(); i++) {
        assert(takeoff[i].flt_num != flt_no);
    }
    /*end of debug*/
}

void Runway::removePlane_landing(int flt_no, Plane &pl) {
    for (int i = 0; i < landing.size(); i++) {
        if (landing[i].flt_num == flt_no) {
            pl = landing[i];
            landing.del(i);
        }
    }
    /*debug*/
    for (int i = 0; i < landing.size(); i++) {
        assert(landing[i].flt_num != flt_no);
    }
    /*end of debug*/
}

void Runway::removePlane_mayday(int flt_no, Plane &pl) {
    for (int i = 0; i < mayday.size(); i++) {
        if (mayday[i].flt_num == flt_no) {
            pl = mayday[i];
            mayday.del(i);
        }
    }
    /*debug*/
    for (int i = 0; i < mayday.size(); i++) {
        assert(mayday[i].flt_num != flt_no);
    }
    /*end of debug*/
}

int Runway::getRunwayLimit() const {
	return this->queue_limit;
}

int Runway::getLandingLength() const {
	return this->landing.size();
}

int Runway::getTakeoffLength() const {
	return this->takeoff.size();
}

int Runway::getMaydayLength() const {
	return this->mayday.size();
}

void Runway::add_Mayday(Plane pl) {
    mayday.push(pl);
}
