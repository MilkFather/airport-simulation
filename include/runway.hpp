#ifndef RUNWAY_HPP
#define RUNWAY_HPP

#include "plane.hpp"
#include "exqueue.cpp"

using namespace std;

//enum Runway_activity {idle, land, takeoff};

class Runway {
private:
    // 三个队列：降落队列、起飞队列和Mayday队列。
    exqueue<Plane> landing;
    exqueue<Plane> takeoff;
    exqueue<Plane> mayday;
    int queue_limit;

public:
	  queue<Plane> landing;
	  queue<Plane> takeoff;
	  queue<Plane> mayday;
    // 构造函数
    Runway(int limit);
    // 判定给定的飞机是否能插入这个跑道的降落或起飞队列，如果能，顺便就插入了
    bool try_land_queue(const Plane &current);
    void force_land_queue(const Plane &current);
    bool try_depart_queue(const Plane &current);
    // 进行跑道操作
    /*Runway_activity*/void activity(int time);
    void use_fuel_plane();
    // 从跑道的队列中移除指定编号的飞机
	  void removePlane_takeoff(int flt_no, Plane &pl);
	  void removePlane_landing(int flt_no, Plane &pl);
	  void removePlane_mayday(int flt_no, Plane &pl);

    // 信息方法。
    int getRunwayLimit() const;
    int getLandingLength() const;
    int getTakeoffLength() const;
    int getMaydayLength() const;

    // 将飞机插入Mayday队列
    void add_Mayday(Plane pl);

};

#endif
