#ifndef __PRICE_POINT_HPP__
#define __PRICE_POINT_HPP__

#include <string>
#include <sstream>
#include <iostream>
#include "dateStruct.hpp"
#include "timeStruct.hpp"

using namespace std;

struct pricePoint {
	dateStruct date;
	timeStruct time;

	double open;
	double close;
	double adjClose;
	double high;
	double low;

	int volume;

	int length;

	pricePoint(stringstream& line) {
		string dateString;
		string timeString;

		line >> dateString;
		stringstream dateStream(dateString);
		dateStruct d(dateStream);
		date = d;

		getline(line,timeString, ',');
		stringstream timeStream(timeString);
		timeStruct t(timeStream);
		time = t;
		
		string value;
		getline(line,value,',');
		open = stod(value);
		getline(line,value,',');
		high = stod(value);
		getline(line,value,',');
		low = stod(value);
		getline(line,value,',');
		close = stod(value);
		getline(line,value,',');
		adjClose = stod(value);
		getline(line,value,',');
		volume = stoi(value);
		length = 0;
	};

	void print(void) {
		cout << "pricePoint:" << endl;
		cout << "\tdate: " << endl;
		cout << "\t\tyear: " << date.year << endl;
		cout << "\t\tmonth: " << date.month << endl;
		cout << "\t\tday: " << date.day << endl;
		cout << "\ttime: " << endl;
		cout << "\t\thour: " << time.hour << endl;
		cout << "\t\tminute: " << time.minute << endl;
		cout << "\t\tsecond: " << time.second << endl;
		cout << "\topen: " << open << endl;
		cout << "\tclose: " << close << endl;
		cout << "\tadjClose: " << adjClose << endl;
		cout << "\thigh: " << high << endl;
		cout << "\tlow: " << low << endl;
		cout << "\tvolume: " << volume << endl;

	};
};

#endif //__PRICE_POINT_HPP__