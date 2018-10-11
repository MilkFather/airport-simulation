#include "airport.hpp"
#include "random.hpp"

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

		if (runways[i].can_land(pl) == success) {
			pl.setRunwayNo(i);

		}
	}

	for (int p = 0; p < newdeparture; p++) {
		Plane pl(totalPlanes, time_elapsed, takeoff, this);

		int minused = runways[0].getLandingLength();
		int minidx = 0;
		for (int i = 0; i < runway_count; i++) {
			if (runways[i].getLandingLength() < minused) {
				minused = runways[i].getLandingLength();
				minidx = i;
			}
		}

		if (runways[i].can_depart(pl) == success) {
			pl.setRunwayNo(i);
		}
	}

	for (int i = 0; i < runway_count; p++) {
		runways[i].activity(time_elapsed);
	}
}

void Airport::step() {
	// Poisson
}
