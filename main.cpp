#include "stockPrice.hpp"
#include "pricePoint.hpp"
#include "dateStruct.hpp"
#include "timeStruct.hpp"
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
	vector<stockPrice> prices;
	string timescale = "7d";
	string resolution = "1m";
	int windowSize = 180;
	auto start = chrono::high_resolution_clock::now();
	for(int i = 0; i < stocks.size(); i++) {
		stockPrice temp(stocks.at(i), timescale, resolution, windowSize);
		temp.initData();
		temp.writeToCSV();
		temp.plot();
		prices.push_back(temp);
	}
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
	double seconds = duration.count()/1000000.0;
	cout << "EXECUTION TOOK " << seconds << " SECONDS" << endl;
	cout << "FINISHED TEST" << endl;
	// clearAllStockData();
	return 0;
}