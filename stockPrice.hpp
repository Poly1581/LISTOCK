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
	string LISFileName;
	string LISPlotCommand;
	string deleteCommand;

	vector<pricePoint*> pricePoints;

	stockPrice(string t, string ts, string res, int ws) : ticker(t), timescale(ts), resolution(res), windowSize(ws), left(0), right(-1){
		updateFileName = ticker+"|1m|1m.csv";
		updateCommand = "python3 PYLISTOCK.py " + ticker + " 1m 1m";
		initFileName = ticker+"|"+timescale+"|"+resolution+".csv";
		initCommand = "python3 PYLISTOCK.py " + ticker + " " + timescale + " " + resolution;
		LISFileName = ticker+"|LIS.csv";
		LISPlotCommand = "python3 PLOT.py "+LISFileName;
		deleteCommand = "rm "+updateFileName+" && rm "+initFileName+" && rm "+LISFileName;
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
		//			FULL LIS
		// for(int i = 0; i < pricePoints.size(); i++) {
		// 	pricePoint* currPricePoint = pricePoints.at(i);
		// 	if(currPricePoint->close < pricePoints.back()->close) {
		// 		pricePoints.back()->length = max(pricePoints.back()->length, currPricePoint->length+1);
		// 	}
		// }


		//			WINDOWED LIS
		for(int i = left; i < right; i++) {
			pricePoint* currPricePoint = pricePoints.at(i);
			if(currPricePoint->close < rightPricePoint->close) {
				rightPricePoint->length = max(rightPricePoint->length, currPricePoint->length+1);
			}
		}
	};
	
	void addSinglePricePoint(pricePoint* point) {
		pricePoints.push_back(point);
		right++;
		if((right - left) > windowSize) {
			left++;
		}
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
			addSinglePricePoint(new pricePoint(lineStream));
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
		stockCSV.close();
	};

	void writeToCSV(void) {
		string header = "Datetime,Open,High,Low,Close,Adj Close,Volume,LIS";
		ofstream stockCSV;
		stockCSV.open(LISFileName);
		if(!stockCSV.is_open()) {
			cout << "ERROR OPENING " << LISFileName << endl;
			return;
		}
		stockCSV << header << endl;
		for(int i = 0; i < pricePoints.size(); i++) {
			pricePoints.at(i)->writeToCSV(stockCSV);
		}
		stockCSV.close();
	};

	void plot(void) {
		writeToCSV();
		system(LISPlotCommand.c_str());
	}
};

#endif //__STOCK_PRICE_HPP__