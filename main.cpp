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
	auto start = chrono::high_resolution_clock::now();
	stockPortfolio portfolio(stocks, timescale, resolution, windowSize);
	portfolio.initData();
	portfolio.plot();
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
	double seconds = duration.count()/1000000.0;
	cout << "FINISHED TEST" << endl;
	cout << "EXECUTION TOOK " << seconds << " SECONDS" << endl;
	clearAllStockData();
}