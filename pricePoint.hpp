#ifndef __PRICE_POINT_HPP__
#define __PRICE_POINT_HPP__

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "dateStruct.hpp"
#include "timeStruct.hpp"

using namespace std;

struct pricePoint {
	string datetime;
	dateStruct date;
	timeStruct time;


	double open;
	double close;
	double adjClose;
	double high;
	double low;

	int volume;

	int increasing = 0;
	int decreasing = 0;
	int sentiment = 0;

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
		
		datetime = dateString+" "+timeString;

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

	void writeToCSV(ofstream& stockCSV) {
		stockCSV << datetime << ",";
		stockCSV << open << ",";
		stockCSV << high << ",";
		stockCSV << low << ",";
		stockCSV << close << ",";
		stockCSV << adjClose << ",";
		stockCSV << volume << ",";
		stockCSV << increasing << ",";
		stockCSV << decreasing << ",";
		stockCSV << sentiment << endl;
	}
};

#endif //__PRICE_POINT_HPP__