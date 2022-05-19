#ifndef __TIME_STRUCT_HPP__
#define __TIME_STRUCT_HPP__

#include <string>
#include <sstream>

using namespace std;

struct timeStruct {
	int hour = 0;
	int minute = 0;
	int second = 0;

	timeStruct(void) {};

	timeStruct(stringstream& time) {
		string value;
		getline(time,value,':');
		hour = stoi(value);
		getline(time,value,':');
		minute = stoi(value);
		getline(time,value,':');
		second = stoi(value);
	};

	bool operator==(const timeStruct &t) const {
		return hour == t.hour && minute == t.minute && second == t.second;
	}

	bool operator!=(const timeStruct &t) const {
		return !(*this == t);
	}
};

#endif //__TIME_STRUCT_HPP__