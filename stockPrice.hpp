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

	//		DE-POINTERIZED
	vector<pricePoint> pricePoints;

	stockPrice(string t, string ts, string res, int ws) : ticker(t), timescale(ts), resolution(res), windowSize(ws), left(0), right(-1){
		updateFileName = ticker+"-1m-1m.csv";
		updateCommand = "python3 PYLISTOCK.py " + ticker + " 1m 1m";
		initFileName = ticker+"-"+timescale+"-"+resolution+".csv";
		initCommand = "python3 PYLISTOCK.py " + ticker + " " + timescale + " " + resolution;
		LISFileName = ticker+"-LIS.csv";
		LISPlotCommand = "python3 PLOT.py "+LISFileName;
		deleteCommand = "rm "+updateFileName+" && rm "+initFileName+" && rm "+LISFileName;
	};

	void deleteData(void) {
		system(deleteCommand.c_str());
	};

	//		DE-POINTERIZED
	void calcLIS(void) {
		//			FULL LIS
		// for(int i = 0; i < pricePoints.size(); i++) {
		// 	pricePoint currPricePoint = pricePoints.at(i);
		// 	if(currPricePoint.close < pricePoints.back().close) {
		// 		pricePoints.back().increasing = max(pricePoints.back().increasing, currPricePoint.increasing+1);
		// 	} else if(currPricePoint.close > pricePoints.back().close) {
		// 		pricePoints.back().decreasing = max(pricePoints.back().decreasing, currPricePoint.decreasing+1);
		// 	}
		// }
		// pricePoints.back().sentiment = pricePoints.back().increasing - pricePoints.back().decreasing;


		//			WINDOWED LIS
		pricePoint& rightPricePoint = pricePoints.at(right);
		for(int i = left; i < right; i++) {
			pricePoint& currPricePoint = pricePoints.at(i);
			if(currPricePoint.close < rightPricePoint.close) {
				rightPricePoint.increasing = max(rightPricePoint.increasing, currPricePoint.increasing+1);
			} else if(currPricePoint.close > rightPricePoint.close) {
				rightPricePoint.decreasing = max(rightPricePoint.decreasing, currPricePoint.decreasing+1);
			}
		}
		rightPricePoint.sentiment = rightPricePoint.increasing - rightPricePoint.decreasing;
	};
	

	//		DE-POINTERIZED
	void addSinglePricePoint(pricePoint& currPricePoint) {
		if(pricePoints.size() != 0) {
			pricePoint& lastPricePoint = pricePoints.back();
			if( (currPricePoint.date == lastPricePoint.date) && (currPricePoint.time == lastPricePoint.time)) {
				cout << "\t\tMATCHING DATE AND TIME:" << endl;
				cout << "\t" << currPricePoint.date.year << "/" << currPricePoint.date.month << "/" << currPricePoint.date.day << endl;
				cout << "\t" << currPricePoint.time.hour << ":" << currPricePoint.time.minute << ":" << currPricePoint.time.second << endl;
				return;
			}
		}
		pricePoints.push_back(currPricePoint);
		right++;
		if((right - left) > windowSize) {
			left++;
		}
		calcLIS();
	};


	//		DE-POINTERIZED
	void initData(void) {
		cout << "Initializing data for " << ticker << endl;
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
			pricePoint newPricePoint(lineStream);
			addSinglePricePoint(newPricePoint);
		}
	};


	//		DE-POINTERIZED
	void updateData(void) {
		system(updateCommand.c_str());
		ifstream stockCSV;
		stockCSV.open(updateFileName);
		if(!stockCSV.is_open()) {
			cout << "ERROR OPENING " << updateFileName << endl;
			return;
		}
		string lineString;
		getline(stockCSV,lineString);		//		REMOVE HEADER
		getline(stockCSV,lineString);
		stringstream lineStream(lineString);
		pricePoint newPricePoint(lineStream);
		addSinglePricePoint(newPricePoint);
		stockCSV.close();
	};

	//		DE-POINTERIZED
	void writeToCSV(void) {
		string header = "Datetime,Open,High,Low,Close,Adj Close,Volume,LIS,LDS,Sentiment";
		ofstream stockCSV;
		stockCSV.open(LISFileName);
		if(!stockCSV.is_open()) {
			cout << "ERROR OPENING " << LISFileName << endl;
			return;
		}
		stockCSV << header << endl;
		for(int i = 0; i < pricePoints.size(); i++) {
			pricePoints.at(i).writeToCSV(stockCSV);
		}
		stockCSV.close();
	};

	void readFromCSV(void) {

	};

	void plot(void) {
		writeToCSV();
		system(LISPlotCommand.c_str());
	}
};

#endif //__STOCK_PRICE_HPP__