#include "runway.hpp"
#include <iostream>

// this is a git test 

using namespace std;

Runway::Runway(int limit) {
    queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
}
void Runway::resetStatistics() {
	num_land_requests = num_takeoff_requests = 0;
	num_landings = num_takeoffs = 0;
	num_land_refused = num_takeoff_refused = 0;
	num_land_accepted = num_takeoff_accepted = 0;
	land_wait = takeoff_wait = idle_time = 0;
}
Error_code Runway::can_land(const Plane &current) {
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

Runway_activity Runway::activity(int time) {
    /*
    TODO：加入对于Mayday队列的逻辑
     */
    Runway_activity in_progress;
    Plane moving;
    if (!landing.empty()) {
        // 取降落队列的头，赋值moving，然后对moving进行操作
        landing.retrive(moving);
        // 更新统计数据
        land_wait += time - moving.started();
        num_landings++;
        // 更新状态
        in_progress = land;
        // 将降落队列的头pop掉
        landing.serve();
        moving.land();
    } else if (!takeoff.empty()) {
        // 代码思路类似
        takeoff.retrive(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = Runway_activity::takeoff;
        takeoff.serve();
        moving.depart();
    } else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}
void Runway::removePlane_takeoff(int flt_no) {
	Plane temp[1000];
	int size = takeoff.size();
	for (int i = 0; i < size; i++) {
		temp[i] = takeoff.q.front();//将队列清空，并转移到一个数组里面，便于检索
		takeoff.q.pop();
	}
	int pos;
	for (int i = 0; i < size; i++) {
		if (temp[i].flt_num == flt_no) {//找到所要清除的元素
			pos = i;//标记位置
			for (int j = pos; j < size; j++) {
				temp[j] = temp[j + 1];//覆盖
			}
		}
	}
	for (int i = 0; i < size - 1; i++) {
		takeoff.q.push(temp[i]);//队列复原
	}
}
void Runway::removePlane_landing(int flt_no) {
	Plane temp[1000];
	int size = landing.size();
	for (int i = 0; i < size; i++) {
		temp[i] = landing.q.front();//将队列清空，并转移到一个数组里面，便于检索
		landing.q.pop();
	}
	int pos;
	for (int i = 0; i < size; i++) {
		if (temp[i].flt_num == flt_no) {//找到所要清除的元素
			pos = i;//标记位置
			for (int j = pos; j < size; j++) {
				temp[j] = temp[j + 1];//覆盖
			}
		}
	}
	for (int i = 0; i < size - 1; i++) {
		landing.q.push(temp[i]);//队列复原
	}
}
void Runway::removePlane_mayday(int flt_no) {
	Plane temp[1000];
	int size = mayday.size();
	for (int i = 0; i < size; i++) {
		temp[i] = mayday.q.front();//将队列清空，并转移到一个数组里面，便于检索
		mayday.q.pop();
	}
	int pos;
	for (int i = 0; i < size; i++) {
		if (temp[i].flt_num == flt_no) {//找到所要清除的元素
			pos = i;//标记位置
			for (int j = pos; j < size; j++) {
				temp[j] = temp[j + 1];//覆盖
			}
		}
	}
	for (int i = 0; i < size - 1; i++) {
		mayday.q.push(temp[i]);//队列复原
	}
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
