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
	string command = "ls | grep \\| | xargs rm";
	cout << "command: " << command << endl;
	system(command.c_str());
}

int main() {
	vector<string> stocks = {"AAPL", "MSFT", "GOOG", "AMZN", "TSLA", "V"};
	vector<stockPrice> prices;
	string timescale = "5d";
	string resolution = "5m";
	int windowSize = 12;
	for(int i = 0; i < stocks.size(); i++) {
		stockPrice temp(stocks.at(i), timescale, resolution, windowSize);
		temp.deleteData();
		temp.initData();
		prices.push_back(temp);
	}
	for(int i = 0; i < prices.size(); i++) {
		cout << prices.at(i).ticker << endl;
		cout << "\tCURR PRICE: " << prices.at(i).pricePoints.back()->close << endl;
		cout << "\tCURR LIS: " << prices.at(i).pricePoints.back()->length << endl;
	}
	cout << "FINISHED TEST" << endl;
	clearAllStockData();
	return 0;
}