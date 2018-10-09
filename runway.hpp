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

    // 以下这些都是统计数据
    int queue_limit;
    int num_land_requests;
    int num_takeoff_requests;
    int num_landings;
    int num_takeoffs;
    int num_land_accepted;
    int num_takeoff_accepted;
    int num_land_refused;
    int num_takeoff_refused;
    int land_wait;
    int takeoff_wait;
    int idle_time;
    
public:
    // 构造函数
    Runway(int limit);
    // 重置所有统计数据
    void resetStatistics();
    // 判定给定的飞机是否能插入这个跑道的降落或起飞队列
    Error_code can_land(const Plane &current);
    Error_code can_depart(const Plane &current);
    // 进行跑道操作
    Runway_activity activity(int time, Plane &moving);
    // 跑道的终止操作。目前这里是用来进行统计数据的输出的。
    void shut_down(int time) const;
    // 从跑道的队列中移除指定编号的飞机
    void removePlane(int flt_no);
};

#endif
