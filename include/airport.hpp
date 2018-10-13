#ifndef AIRPORT_HPP
#define AIRPORT_HPP

#include "runway.hpp"
#include "delegate.hpp"
#include <vector>
#include <string>

using namespace std;

// Airport 类
// 这里进行了定义与实现的分离，请在airport.cpp文件中实现该类的函数。
class Airport: public CommunicationProtocal {
private:
	// 虚拟的跑道和虚拟的时间
	vector<Runway> runways;
	int time_elapsed;

	int runway_limit;

	// 统计数据
	int totalPlanes, landingRequestPlanes, departureRequestPlanes;  // 全部生成的数量，其中有多少是降落，多少是起飞？
	int acceptedPlanes, rejectedPlanes;  // 全部生成的飞机当中，有多少被拒绝了，多少被接受了？
	/* 关于拒绝和接受：拒绝只发生在降落的飞机身上。一般而言，如果所有跑道的降落队列都满了，那么新的请求降落的飞机就会被拒绝。标记了Mayday的飞机除外，它们无条件被接受。 */
	int landedPlanes, departuredPlanes;  // 成功降落和起飞的飞机数量
	/* 关于成功：完成了降落或起飞动作的飞机即为成功。留在队列里的飞机和坠毁的飞机不算 */
	int Plane_fuel;
public:
	double arrival_rate, departure_rate;  // 产生降落飞机和离场飞机的频率
	// Airport 的生成函数，在这里定义包含的跑道的数量
	Airport(int runway_count, int runway_limit);
	// Airport 模拟前应当进行调用。在这里，所有跑道清空，统计数据全部清零，并且设定好一些参数。
	void initialize();
	// 两个模拟函数，都会模拟一个单位时间的情况。前者将使用Random类当中的泊松分布进行模拟，后者手动给定数据进行模拟。
	// 如果需要连续模拟n个单位时间，请使用循环，或者自行考虑新增一个函数。
	void step();
	void step(int newlanding, int newdeparture);
	// 在屏幕上显示到目前为止的所有统计情况。
	void printSummary();

	// 供飞机调用
	void report(string msg, int runway_no, int flt_no, ...);
};

#endif
