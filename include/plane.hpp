#ifndef PLANE_HPP
#define PLANE_HPP

#include "delegate.hpp"

enum Plane_status {null, arriving, departing};

// 写在定义内的函数可能不全，我会时不时进行更新。

class Plane {
private:
    // 飞机的生成的时间点和其状态（降落 or 起飞）
    int clock_start;
    Plane_status state;

    // Mayday标记。一旦机场遇见了Mayday飞机，机场应当无条件安排其降落，即使降落队列已满也不能拒绝它。每个跑道都有单独针对Mayday飞机的降落队列。请将其安排到那里去。
    bool Mayday;

    // 飞机的燃料。初始时请设置一个合适的值（没有标准），每经过一个单位时间飞机的燃料都要减1，一旦剩余燃料数小于等于5，则宣布进入Mayday状态并从原来的等待队列中跳出，按照Mayday流程处理。
    // 燃料归零则宣布坠毁。
    int fuel;

    int runway_no;

    CommunicationProtocal *host;

public:
    // 飞机的航班号
    int flt_num;
    // Plane的生成函数。其中空的那个写出来是为了防止程序错误而设置的保护措施，但是正常运行中不应该调用它。
    Plane();
    Plane(int flt, int time, Plane_status status, CommunicationProtocal *port, int fuel_start);
    void refuse() const;
    void land(int time) const;
    void fly(int time) const;
    int started() const;

    bool isMayday() const;
    void setMayday(bool s);
    void setRunwayNo(int no);
	int getfuel();
	void usefuel();
};

#endif
