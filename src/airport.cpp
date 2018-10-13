#include "airport.hpp"
#include "plane.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstdarg>
#include <random>

using namespace std;

Airport::Airport(int runway_count, int runway_limit) {
	runways.clear();
	for (int i = 0; i < runway_count; i++) {
		Runway new_runway(runway_limit);
		runways.push_back(new_runway);
	}
}

void Airport::initialize() {
	time_elapsed = 0;
	totalPlanes = landingRequestPlanes = departureRequestPlanes = 0;
	acceptedPlanes = rejectedPlanes = 0;
	landedPlanes = departuredPlanes = 0;
	Plane_fuel = 15;
}

void Airport::step(int newlanding, int newdeparture) {
	int runway_count = runways.size();

	landingRequestPlanes += newlanding;
	for (int p = 0; p < newlanding; p++) {
		Plane pl(totalPlanes, time_elapsed, arriving, this,Plane_fuel);
		totalPlanes++;

		int minused = runways[0].getLandingLength();
		int minidx = 0;
		for (int i = 0; i < runway_count; i++) {
			if (runways[i].getLandingLength() < minused) {
				minused = runways[i].getLandingLength();
				minidx = i;
			}
		}

		if (runways[minidx].try_land_queue(pl)) {
			pl.setRunwayNo(minidx);
			acceptedPlanes++;
		} else {
			rejectedPlanes++;
		}
	}
	departureRequestPlanes += newdeparture;
	for (int p = 0; p < newdeparture; p++) {
		Plane pl(totalPlanes, time_elapsed, departing, this,Plane_fuel);
		totalPlanes++;

		int minused = runways[0].getTakeoffLength();
		int minidx = 0;
		for (int i = 0; i < runway_count; i++) {
			if (runways[i].getTakeoffLength() < minused) {
				minused = runways[i].getTakeoffLength();
				minidx = i;
			}
		}

		if (runways[minidx].try_depart_queue(pl)) {
			pl.setRunwayNo(minidx);
			acceptedPlanes++;
		} else {
			rejectedPlanes++;
		}
	}

	for (int i = 0; i < runway_count; i++) {
		runways[i].activity(time_elapsed);
	}
	time_elapsed++;
}

int Poisson(double mean) {
	double limit = exp(-mean);
    //double product = (double)rand() / RAND_MAX;
	random_device r;
	mt19937 gen(r());
	uniform_real_distribution<> dis(0.0, 1.0);
	double product = dis(gen);
    int count = 0;
    while (product > limit) {
        count++;
        product *= dis(gen) / RAND_MAX;
    }
    return count;
}

void Airport::step() {
	step(Poisson(arrival_rate), Poisson(departure_rate));
}

void Airport::report(string msg, int flt_no, ...) {
	va_list args;
	va_start(args, flt_no);
	if (msg == "MAYDAY_FUEL") {
		Plane pl;
		int runway_no = va_arg(args, int);
		runways[runway_no].removePlane_landing(flt_no, pl);

		int minused = runways[0].getMaydayLength();
		int minidx = 0;
		for (int i = 0; i < runways.size(); i++) {
			if (runways[i].getMaydayLength() < minused) {
				minused = runways[i].getMaydayLength();
				minidx = i;
			}
		}

		pl.setRunwayNo(minidx);
		runways[minidx].add_Mayday(pl);
		cout << "航班" << flt_no << ": MAYDAY, MAYDAY, MAYDAY" << endl;
	} else if (msg == "MAYDAY") {

	} else if (msg == "CRASH") {
		// Crash 只会出现在Mayday飞机当中
		Plane pl;
		int runway_no = va_arg(args, int);
		runways[runway_no].removePlane_mayday(flt_no, pl);
		cout << "很遗憾，航班" << flt_no << "已经坠毁……" << endl;
	} else if (msg == "LAND_SUCCESS") {
		int runway_no = va_arg(args, int);
		int times = va_arg(args, int);
		landedPlanes++;
	} else if (msg == "TAKEOFF_SUCCESS") {
		int runway_no = va_arg(args, int);
		int times = va_arg(args, int);
		departuredPlanes++;
	}
	va_end(args);
}

void Airport::printSummary() {
	cout << "截至第" << time_elapsed << "分钟的机场模拟报告如下:" << endl;
	cout << "一共处理飞机" << totalPlanes << "架" << endl;
	cout << "\t降落" << landingRequestPlanes << "架" << endl;
	cout << "\t起飞" << departureRequestPlanes << "架" << endl;
	cout << "在这些飞机中，本场一共接受了" << acceptedPlanes << "架，拒绝了" << rejectedPlanes << "架" << endl;
	cout << "目前为止，一共有" << landedPlanes + departuredPlanes << "架飞机完成了任务" << endl;
	cout << "\t降落完成" << landedPlanes << "架" << endl;
	cout << "\t起飞完成" << departuredPlanes << "架" << endl;
}
