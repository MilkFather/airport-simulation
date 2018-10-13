#include "runway.hpp"
#include <iostream>

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

bool Runway::try_depart_queue(const Plane &current) {
    if (takeoff.size() < queue_limit) {
        takeoff.push(current);
        return true;
    } else
        return false;
}

/*Runway_activity*/void Runway::activity(int time) {
    /*
    TODO：加入对于Mayday队列的逻辑
     */
    //Runway_activity in_progress;
    Plane moving;
    if (!landing.empty()) {
        // 取降落队列的头，赋值moving，然后对moving进行操作
        moving = landing.front();
        // 更新状态
        //in_progress = land;
        // 将降落队列的头pop掉
        landing.pop();
        moving.land(time);
    } else if (!takeoff.empty()) {
        // 代码思路类似
        moving = takeoff.front();
        //in_progress = Runway_activity::takeoff;
        takeoff.pop();
        moving.fly(time);
    } else {
        //in_progress = idle;
    }
    //return in_progress;
	int size = landing.size();
	queue<Plane>temp;
	//landing fuel -1
	for (int i = 0; i < size; i++) {
		Plane front = landing.front();
		front.usefuel();
		landing.pop();
		temp.push(front);
	}
	for (int i = 0; i < size; i++) {
		Plane front = temp.front();
		landing.push(front);
		temp.pop();
	}
	//takeoff fuel -1
	size = takeoff.size();
	for (int i = 0; i < size; i++) {
		Plane front = takeoff.front();
		front.usefuel();
		takeoff.pop();
		temp.push(front);
	}
	for (int i = 0; i < size; i++) {
		Plane front = temp.front();
		takeoff.push(front);
		temp.pop();
	}
	//mayday fuel -1
	size = mayday.size();
	for (int i = 0; i < size; i++) {
		Plane front = mayday.front();
		front.usefuel();
		mayday.pop();
		temp.push(front);
	}
	for (int i = 0; i < size; i++) {
		Plane front = temp.front();
		mayday.push(front);
		temp.pop();
	}
}

void Runway::removePlane_takeoff(int flt_no, Plane &pl) {
	vector<Plane> temp;
	int size = takeoff.size();
	for (int i = 0; i < size; i++) {
		temp.push_back(takeoff.front());//将队列清空，并转移到一个数组里面，便于检索
		takeoff.pop();
	}

	int pos;
	for (int i = 0; i < size; i++) {
		if (temp[i].flt_num == flt_no) {//找到所要清除的元素
			pos = i;//标记位置
            pl = temp[i];
		}
	}

	for (int i = 0; i < size - 1; i++) {
        if (i != pos)
		    takeoff.push(temp[i]);//队列复原
	}
}

void Runway::removePlane_landing(int flt_no, Plane &pl) {
	vector<Plane> temp;
	int size = landing.size();
	for (int i = 0; i < size; i++) {
		temp.push_back(landing.front());//将队列清空，并转移到一个数组里面，便于检索
		landing.pop();
	}

	int pos;
	for (int i = 0; i < size; i++) {
		if (temp[i].flt_num == flt_no) {//找到所要清除的元素
			pos = i;//标记位置
            pl = temp[i];
		}
	}

	for (int i = 0; i < size - 1; i++) {
		if (i != pos)
            landing.push(temp[i]);//队列复原
	}
}

void Runway::removePlane_mayday(int flt_no, Plane &pl) {
	vector<Plane> temp;
	int size = mayday.size();
	for (int i = 0; i < size; i++) {
		temp.push_back(mayday.front()); //将队列清空，并转移到一个数组里面，便于检索
		mayday.pop();
	}

	int pos;
	for (int i = 0; i < size; i++) {
		if (temp[i].flt_num == flt_no) {//找到所要清除的元素
			pos = i;//标记位置
            pl = temp[i];
		}
	}

	for (int i = 0; i < size - 1; i++) {
        if (i != pos)
		    mayday.push(temp[i]);//队列复原
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

void Runway::add_Mayday(Plane pl) {
    mayday.push(pl);
}
