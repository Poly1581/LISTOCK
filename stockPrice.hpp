#ifndef __STOCK_PRICE_HPP__
#define __STOCK_PRICE_HPP__

#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "timeStruct.hpp"
#include "dateStruct.hpp"
#include "pricePoint.hpp"

using namespace std;

struct stockPrice {
	string ticker;
	string timescale;
	string resolution;
	int windowSize;
	int left;
	int right;

	string updateFileName;
	string updateCommand;
	string initFileName;
	string initCommand;
	string deleteCommand;

	vector<pricePoint*> pricePoints;

	stockPrice(string t, string ts, string res, int ws) : ticker(t), timescale(ts), resolution(res), windowSize(ws), left(0), right(-1){
		updateFileName = ticker+"|5m|5m.csv";
		updateCommand = "python3 PYLISTOCK.py " + ticker + " 5m 5m";
		initFileName = ticker+"|"+timescale+"|"+resolution+".csv";
		initCommand = "python3 PYLISTOCK.py " + ticker + " " + timescale + " " + resolution;
		deleteCommand = "rm "+updateFileName+" && "+"rm "+initFileName;
	};
	
	~stockPrice() {
		for(int i = 0; i < pricePoints.size(); i++) {
			delete pricePoints.at(i);
		}
	}

	void deleteData(void) {
		system(deleteCommand.c_str());
	};

	void calcLIS(void) {
		pricePoint* rightPricePoint = pricePoints.at(right);
		for(int i = left; i < right; i++) {
			pricePoint* leftPricePoint = pricePoints.at(left);
			if(leftPricePoint->close < rightPricePoint->close) {
				cout << "INCREASING" << endl;
				cout << "PREVIOUS LENGTH: " << rightPricePoint->length << endl;
				rightPricePoint->length = max(rightPricePoint->length, leftPricePoint->length+1);
				cout << "NEW LENGTH: " << rightPricePoint->length << endl;
			}
		}
	};
	
	void addSinglePricePoint(pricePoint* point) {
		pricePoints.push_back(point);
		right++;
		if((right - left) > windowSize) {
			left++;
		}
		cout << "ADDED POINT" << endl;
		cout << "\tLEFT: " << left << endl;
		cout << "\tRIGHT: " << right << endl;
		cout << "\tWINDOWSIZE: " << windowSize << endl;
		cout << "\tVECTORSIZE: " << pricePoints.size() << endl;
		calcLIS();
	};

	void initData(void) {
		system(initCommand.c_str());
		ifstream stockCSV;
		stockCSV.open(initFileName);
		if(!stockCSV.is_open()) {
			cout << "ERORR OPENING " << initFileName << endl;
			return;
		}
		string lineString;
		getline(stockCSV, lineString);
		while(getline(stockCSV, lineString)) {
			stringstream lineStream(lineString);
			pricePoint* currPricePoint = new pricePoint(lineStream);
			addSinglePricePoint(currPricePoint);
			calcLIS();
		}
	};

	void updateData(void) {
		system(updateCommand.c_str());
		ifstream stockCSV;
		stockCSV.open(updateFileName);
		if(!stockCSV.is_open()) {
			cout << "ERROR OPENING " << updateFileName << endl;
			return;
		}
		string lineString;
		getline(stockCSV,lineString);
		getline(stockCSV,lineString);
		stringstream lineStream(lineString);
		pricePoint* currPricePoint = new pricePoint(lineStream);
		pricePoint* lastPricePoint = pricePoints.back();
		if( (currPricePoint->date != lastPricePoint->date) || (currPricePoint->time != lastPricePoint->time)) {
			addSinglePricePoint(currPricePoint);
		} else {
			delete currPricePoint;
		}
	};
};

#endif //__STOCK_PRICE_HPP__