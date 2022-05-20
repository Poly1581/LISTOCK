#ifndef __STOCK_PORTFOLIO_HPP__
#define __STOCK_PORTFOLIO_HPP__

#include <vector>
#include <string>
#include "stockPrice.hpp"

using namespace std;

struct stockPortfolio {
	vector<string> tickers;
	vector<stockPrice> stocks;

	string timescale;
	string resolution;

	int windowSize;

	stockPortfolio(vector<string> tickers, string ts, string res, int ws) : timescale(ts), resolution(res), windowSize(ws) {
		for(int i = 0; i < tickers.size(); i++) {
			stockPrice temp(tickers.at(i), ts, res, ws);
			stocks.push_back(temp);
		}
	};

	void deleteData(void) {
		for(int i = 0; i < stocks.size(); i++) {
			stocks.at(i).deleteData();
		}
	};

	void initData(void) {
		for(int i = 0; i < stocks.size(); i++) {
			stocks.at(i).initData();
		}
	};

	void updateData(void) {
		for(int i = 0; i < stocks.size(); i++) {
			stocks.at(i).updateData();
		}
	};

	void writeToCSV(void) {
		for(int i = 0; i < stocks.size(); i++) {
			stocks.at(i).writeToCSV();
		}
	};

	void plot(void) {
		for(int i = 0; i < stocks.size(); i++) {
			stocks.at(i).plot();
		}
	};
};

#endif //__STOCK_PORTFOLIO_HPP__