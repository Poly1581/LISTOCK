#ifndef __DATE_STRUCT_HPP__
#define __DATE_STRUCT_HPP__

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct dateStruct {
	int year = 0;
	int month = 0;
	int day = 0;

	dateStruct(void) {};

	dateStruct(stringstream& date) {
		string value;
		getline(date,value,'-');
		year = stoi(value);
		getline(date,value,'-');
		month = stoi(value);
		getline(date,value,'-');
		day = stoi(value);
	};

	bool operator==(const dateStruct &d) const {
		return year == d.year && month == d.month && day == d.day;
	}

	bool operator!=(const dateStruct &d) const {
		return !(*this==d);
	}
};

#endif //__DATE_STRUCT_HPP__