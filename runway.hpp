#ifndef RUNWAY_HPP
#define RUNWAY_HPP

#include "plane.hpp"
#include "exqueue.hpp"

enum Runway_activity {idle, land, takeoff};

class Runway {
private:
    // 三个队列：降落队列、起飞队列和Mayday队列。
    Extended_queue landing;
    Extended_queue takeoff;
    Extended_queue mayday;
    int queue_limit;

public:
    // 构造函数
    Runway(int limit);
    // 重置所有统计数据
    void resetStatistics();
    // 判定给定的飞机是否能插入这个跑道的降落或起飞队列
    Error_code can_land(const Plane &current);
    Error_code can_depart(const Plane &current);
    // 进行跑道操作
    Runway_activity activity(int time);
    // 从跑道的队列中移除指定编号的飞机
	void Runway::removePlane_takeoff(int flt_no);
	void Runway::removePlane_landing(int flt_no);
	void Runway::removePlane_mayday(int flt_no);

    // 信息方法。
    int getRunwayLimit() const;
    int getLandingLength() const;
    int getTakeoffLength() const;
    int getMaydayLength() const;

};

#endif
