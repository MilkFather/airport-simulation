#include "airport.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

// 请在这里完成Airport类的全部函数。

/*
关于模拟。
如果是通过没有参数的step函数进行的模拟，则通过泊松分布函数生成降落和起飞的飞机。
每个生成的飞机都应该设置好管辖它的机场的指针(Plane的host变量，在生成函数中设置)供之后联系。
生成入场飞机，入场飞机在生成过程中有万分之一的概率带有Mayday标记。
不带有标记的入场飞机在这里分配给各个跑道，现阶段分配原则定为尽量平均分配。无法分配的普通入场飞机被拒绝，之后不再考虑它们。
生成离场飞机，这些飞机不会有Mayday标记。它们被分配到各个跑道，原则也是平均。无法分配的也被拒绝，不再考虑。

飞机被分配跑道之后设置其跑道编号。

对所有跑道一次进行模拟降落或起飞。

更新统计数据。
*/

Airport::Airport(int runway_count, int runway_limit) {
	runways.clear()
	for (int i = 0; i < runway_count; i++) {
		Runway new_runway = new Runway(runway_limit);
		runways.push_back(new_runway);
	}
}

void Airport::initialize() {
	// TODO
}

void Airport::step(int newlanding, int newdeparture) {
	for (int p = 0; p < newlanding; p++) {
		Plane pl(totalPlanes, time_elapsed, arriving, this);

		int minused = runways[0].getLandingLength();
		int minidx = 0;
		for (int i = 0; i < runway_count; i++) {
			if (runways[i].getLandingLength() < minused) {
				minused = runways[i].getLandingLength();
				minidx = i;
			}
		}

		if (runways[i].try_land_queue(pl)) {
			pl.setRunwayNo(i);

		}
	}

	for (int p = 0; p < newdeparture; p++) {
		Plane pl(totalPlanes, time_elapsed, takeoff, this);

		int minused = runways[0].getTakeoffLength();
		int minidx = 0;
		for (int i = 0; i < runway_count; i++) {
			if (runways[i].getTakeoffLength() < minused) {
				minused = runways[i].getTakeoffLength();
				minidx = i;
			}
		}

		if (runways[i].try_depart_queue(pl)) {
			pl.setRunwayNo(i);
		}
	}

	for (int i = 0; i < runway_count; p++) {
		runways[i].activity(time_elapsed);
	}
}

int Poisson(double mean) {
	srand(time(NULL));
	double limit = exp(-mean);
    double product = rand() / RAND_MAX;
    int count = 0;
    while (product > limit) {
        count++;
        product *= rand() / RAND_MAX;
    }
    return count;
}

void Airport::step() {
	step(Poisson(arrival_rate), Poisson(departure_rate));
}

void Airport::reportMayday(int runway_no, int flt_no) {
	// Mayday 只会出现在landing飞机当中
	Plane pl;
	runways[runway_no].removePlane_landing(flt_no, &pl);

	int minused = runways[0].getMaydayLength();
	int minidx = 0;
	for (int i = 0; i < runway_count; i++) {
		if (runways[i].getMaydayLength() < minused) {
			minused = runways[i].getMaydayLength();
			minidx = i;
		}
	}

	pl.setRunwayNo(minidx);

	runways[minidx].add_Mayday(pl);
}

void Airport::reportCrash(int runway_no, int flt_no) {
	// Crash 只会出现在Mayday飞机当中
	Plane pl;
	runways[runway_no].removePlane_mayday(flt_no, &pl);
}

void Airport::printSummary() {
	cout << "截至第" << time_elapsed << "分钟的机场模拟报告如下:" << endl;
	cout << "一共处理飞机" << totalPlanes << "架" << endl;
	cout << "\t-- 降落" << landingRequestPlanes << "架" << endl;
	cout << "\t-- 起飞" << departureRequestPlanes << "架" << endl;
	cout << "在这些飞机中，本场一共接受了" << acceptedPlanes << "架，拒绝了" << rejectedPlanes << "架" << endl;
	cout << "目前为止，一共有" << landedPlanes + departuredPlanes << "架飞机完成了任务" << endl;
	cout << "\t-- 降落完成" << landedPlanes << "架" << endl;
	cout << "\t-- 起飞完成" << departuredPlanes << "架" << endl;
}
