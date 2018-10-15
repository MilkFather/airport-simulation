#include "airport.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <cstdlib>

using namespace std;

Airport *airport;
int runway_limit = 15;
int runway_count = 3;
double arrival_rate = 1.0;
double departure_rate = 1.0;
int Plane_fuel = 15;

void act_step(vector<string> arg) {
    if (arg.size() == 0) {
        airport->step();
    } else if (arg.size() == 2) {
        try {
            int land, fly;
            land = stoi(arg[0]);
            fly = stoi(arg[1]);
            airport->step(land, fly);
        } catch (exception e) {
            cout << "在使用step命令时使用了无效的语法" << endl;
        }
    } else {
        cout << "在使用step命令时使用了无效的语法" << endl;
    }
}

void act_set(vector<string> arg) {
    if (arg.size() == 2) {
        if (arg[0] == "runway-limit") {
            try {
                int lim = stoi(arg[1]);
                if (lim != runway_limit) {
                    airport->runway_limit = lim;
                    runway_limit = lim;
                }
            } catch (exception e) {
                cout << "无效的数值: 应当输入整数" << endl;
            }
        } else if (arg[0] == "runway-count") {
            try {
                int cnt = stoi(arg[1]);
                if (cnt != runway_count) {
                    delete airport;
                    airport = new Airport(cnt, runway_limit);
                    airport->Plane_fuel = Plane_fuel;
                    airport->arrival_rate = arrival_rate;
                    airport->departure_rate = departure_rate;
                    airport->initialize();
                    runway_count = cnt;
                    cout << "机场已经重置" << endl;
                }
            } catch (exception e) {
                cout << "无效的数值: 应当输入整数" << endl;
            }
        } else if (arg[0] == "arrival-rate") {
            try {
                int rate = stod(arg[1]);
                if (rate != arrival_rate) {
                    airport->arrival_rate = rate;
                    arrival_rate = rate;
                }
            } catch (exception e) {
                cout << "无效的数值: 应当输入浮点数" << endl;
            }
        } else if (arg[0] == "departure-rate") {
            try {
                int rate = stod(arg[1]);
                if (rate != departure_rate) {
                    airport->departure_rate = rate;
                    departure_rate = rate;
                }
            } catch (exception e) {
                cout << "无效的数值: 应当输入浮点数" << endl;
            }
        } else if (arg[0] == "plane-fuel") {
            try {
                int fuel = stoi(arg[1]);
                if (fuel != Plane_fuel) {
                    airport->Plane_fuel = fuel;
                    Plane_fuel = fuel;
                }
            } catch (exception e) {
                cout << "无效的数值: 应当输入整数" << endl;
            }
        } else {
            cout << "未知的set目标: " << arg[0] << endl;
            cout << "可以设置的参数有: runway-limit, runway-count, arrival-rate, departure-rate, plane-fuel"<< endl;
        }
    } else {
        cout << "在使用set命令时使用了无效的语法" << endl;
    }
}

void act_show(vector<string> args) {
    if (args.size() > 0) {
        cout << "警告: show命令后的参数已忽略" << endl << endl;
    }
    airport->printSummary();
}

void act_runfor(vector<string> args) {
    if (args.size() == 1) {
        try {
            int t = stoi(args[0]);
            for (int i = 0; i < t; i++) {
                airport->step();
            }
        } catch (exception e) {
            cout << "无效的数值: 应当输入整数" << endl;
        }
    } else {
        cout << "在使用runfor命令时使用了无效的语法" << endl;
    }
}

void act_reset(vector<string> args) {
    if (args.size() > 0) {
        cout << "警告: show命令后的参数已忽略" << endl << endl;
    }
    airport->initialize();
}

void act_exit(vector<string> args) {
    exit(0);
}

void act_help(vector<string> args) {
    cout << "可用指令: " << endl;
    cout << "\texit\t\t退出程序" << endl;
    cout << "\thelp\t\t显示本帮助" << endl;
    cout << "\treset\t\t重置模拟" << endl;
    cout << "\trunfor\t\t一次性模拟多个单位时间的运行" << endl;
    cout << "\tset\t\t设定机场模拟的参数" << endl;
    cout << "\tshow\t\t显示模拟统计数据" << endl;
    cout << "\tstep\t\t模拟一个单位时间的运行，可以指定降落和起飞的数量" << endl;
}

bool isblank(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ' and s[i] != '\t' and s[i] != '\0')
            return false;
    }
    return true;
}

vector<string> split(string s) {
    vector<string> tkn;
    string tmp;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            if (!isblank(tmp))
                tkn.push_back(tmp);
            tmp = "";
        } else {
            tmp += s[i];
        }
    }
    if (!isblank(tmp))
        tkn.push_back(tmp);
    tmp = "";
    return tkn;
}

void do_action(vector<string> cmds) {
    string cmd = cmds[0];
    vector<string> args;
    for (int i = 1; i < cmds.size(); i++) {
        args.push_back(cmds[i]);
    }
    
    if (cmd == "step") {
        act_step(args);
    } else if (cmd == "set") {
        act_set(args);
    } else if (cmd == "show") {
        act_show(args);
    } else if (cmd == "runfor") {
        act_runfor(args);
    } else if (cmd == "reset") {
        act_reset(args);
    } else if (cmd == "exit") {
        act_exit(args);
    } else if (cmd == "help") {
        act_help(args);
    } else {
        cout << "未知的指令: " << cmd << endl;
    }
}

int main(int argc, char *argv[]) {            // 机场模拟程序
    airport = new Airport(3, 15);
    airport->Plane_fuel = 15;
    airport->arrival_rate = arrival_rate;
    airport->departure_rate = departure_rate;
    airport->initialize();
    cout << "机场模拟准备就绪" << endl << "输入\"help\"查看帮助" << endl;
    while (true) {
        string str;
        vector<string> tokens;
        cout << "> ";
        getline(cin, str);
        tokens = split(str);
        if (tokens.size() > 0)
            do_action(tokens);
    }
    return 0;
}
