#include "airport.hpp"
#include <iostream>

using namespace std;

void initialize(int &end_time, int &queue_limit, double &arrival_rate, double &departure_rate) {
    cout << "This program simulates an airport with only one runway." << endl << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land " << "or take off at any time? " << flush;
    cin >> queue_limit;
    cout << "How many units of time will the simulation run? " << flush;
    cin >> end_time;
    bool acceptable;
    do {
        cout << "Expected number of arrivals per unit time? " << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time? " << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 or departure_rate < 0.0)
            cerr << "These rates must be nonnegative." << endl;
        else
            acceptable = true;
        if (acceptable and arrival_rate + departure_rate > 1.0)
            cerr << "Safety Warning: This airport will become saturated." << endl;
    } while(!acceptable);
}

void run_idle(int time) {
    cout << time << ": Runway is idle." << endl;
}

int main() {            // 机场模拟程序
	int runway_count;
	int runway_limit;
	cout << "please input the number of runway:";
	cin >> runway_count;
	cout << endl;
	int end_time;
	double arrival_rate;
	double departure_rate;
	int flight_number = 0;
	int fuel_start;
	cout << "please input the fuel of every plane: ";
	cin >> fuel_start;
	cout << endl;
	CommunicationProtocal *port;
	initialize(end_time, runway_limit, arrival_rate, departure_rate);
	//Runway test(runway_limit);
	Airport test(runway_count, runway_limit);
	for (int current_time = 0; current_time < end_time; current_time++) {//  loop over time intervals
		 //  current arrival requests
		int number_arrivals;
		cout << "please input the arrival requests: ";
			cin >> number_arrivals;
		for (int i = 0; i < number_arrivals; i++) {
			Plane current_plane(flight_number++, current_time, arriving ,port ,fuel_start);
			if (test.runways[0].try_land_queue(current_plane) != true)
				current_plane.refuse();
		}
		 //  current departure requests
		int number_departures;
		cout << "please input the number of the departures: ";
		cin >> number_departures;
		cout << endl;
		for (int j = 0; j < number_departures; j++) {
			Plane current_plane(flight_number++, current_time, departing,port,fuel_start);
			if (current_plane.isMayday()) {
				test.runways[2].mayday.push(current_plane);
			}
			if (test.runways[1].try_depart_queue(current_plane) != true)
				current_plane.refuse();
		}
		for (int i = 0; i < runway_count; i++) {
			test.runways[0].activity(current_time);
			test.runways[1].activity(current_time);
			test.runways[2].activity(current_time);
		}
	}
	test.printSummary();
}
