#include "runway.hpp"
#include <iostream>

using namespace std;

Runway::Runway(int limit) {
    /*
     */
    queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
}

Error_code Runway::can_land(const Plane &current) {
    /*
     */
    Error_code result;
    if (landing.size() < queue_limit)
        result = landing.append(current);
    else
        result = fail;
    num_land_requests++;
    if (result != success)
        num_land_refused++;
    else
        num_land_accepted++;
    return result;
}

Error_code Runway::can_depart(const Plane &current) {
    /*
     */
    Error_code result;
    if (takeoff.size() < queue_limit)
        result = takeoff.append(current);
    else
        result = fail;
    num_takeoff_requests++;
    if (result != success)
        num_takeoff_refused++;
    else
        num_takeoff_accepted++;
    return result;
}

Runway_activity Runway::activity(int time, Plane &moving) {
    /*
    moving是交还给调用者的，返回值是Runway_activity。这一个函数同时返回了两个值，不要误解了。
    TODO：加入对于Mayday队列的逻辑
     */
    Runway_activity in_progress;
    if (!landing.empty()) {
        // 取降落队列的头，赋值给实参moving，这样调用者就可以得到它
        landing.retrive(moving);
        // 更新统计数据
        land_wait += time - moving.started();
        num_landings++;
        // 更新状态
        in_progress = land;
        // 将降落队列的头pop掉
        landing.serve();
    } else if (!takeoff.empty()) {
        // 代码思路类似
        takeoff.retrive(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = Runway_activity::takeoff;
        takeoff.serve();
    } else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}

void Runway::shut_down(int time) const {
    cout << "Simulation has concluded after " << time << " time units." << endl;
    cout << "Total number of planes processed " << (num_land_requests + num_takeoff_requests) << endl;
    cout << "Total number of planes asking to land " << num_land_requests << endl;
    cout << "Total number of planes asking to take off " << num_takeoff_requests << endl;
    cout << "Total number of planes accepted for landing " << num_land_accepted << endl;
    cout << "Total number of planes accepted for takeoff " << num_takeoff_accepted << endl;
    cout << "Total number of planes refused for landing " << num_land_refused << endl;
    cout << "Total number of planes refused for takeoff " << num_takeoff_refused << endl;
    cout << "Total number of planes that landed " << num_landings << endl;
    cout << "Total number of planes that took off " << num_takeoffs << endl;
    cout << "Total number of planes left in the landing queue " << landing.size() << endl;
    cout << "Total number of planes left in the tookoff queue " << takeoff.size() << endl;
    cout << "Percentage of time runway idle " << 100.0 * ((float) idle_time) / ((float) time) << "%" << endl;
    cout << "Average wait in landing queue " << ((float) land_wait) / ((float) num_landings) << " time units" << endl;
    cout << "Average wait in takeoff queue " << ((float) takeoff_wait) / ((float) num_takeoffs) << " time units" << endl;
    cout << "Average observed rate of planes wanting to land " << ((float) num_land_requests) / ((float) time) << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to takeoff " << ((float) num_takeoff_requests) / ((float) time) << " per time unit" << endl;
}
