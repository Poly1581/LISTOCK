#include "stockPrice.hpp"
#include "pricePoint.hpp"
#include "dateStruct.hpp"
#include "timeStruct.hpp"
#include "stockPortfolio.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

void clearAllStockData(void) {
	string command = "ls | grep - | xargs rm";
	cout << "command: " << command << endl;
	system(command.c_str());
}

int main() {
	vector<string> stocks = {"AAPL", "MSFT", "GOOG", "AMZN", "TSLA", "V"};
	string timescale = "7d";
	string resolution = "1m";
	int windowSize = 180;
	stockPortfolio portfolio(stocks, timescale, resolution, windowSize);



	auto startInit = chrono::high_resolution_clock::now();
	portfolio.initData();
	auto stopInit = chrono::high_resolution_clock::now();
	auto Initduration = chrono::duration_cast<chrono::microseconds>(stopInit-startInit);
	double Initseconds = Initduration.count()/1000000.0;
	cout << "INIT TOOK " << Initseconds << " SECONDS" << endl;


	auto startUpdate = chrono::high_resolution_clock::now();
	portfolio.updateData();
	auto stopUpdate = chrono::high_resolution_clock::now();
	auto Updateduration = chrono::duration_cast<chrono::microseconds>(stopUpdate-startUpdate);
	double Updateseconds = Updateduration.count()/1000000.0;
	cout << "UPDATE TOOK " << Updateseconds << " SECONDS" << endl;


	auto startPlot = chrono::high_resolution_clock::now();
	portfolio.plot();
	auto stopPlot = chrono::high_resolution_clock::now();
	auto Plotduration = chrono::duration_cast<chrono::microseconds>(stopPlot-startPlot);
	double Plotseconds = Plotduration.count()/1000000.0;
	cout << "PlOT TOOK " << Plotseconds << " SECONDS" << endl;
	// clearAllStockData();
}