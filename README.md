# LISTOCK
Uses windowed longest increasing subsequence for stock applications.  Uses python yfinance api to pull stock data.
Initializes with 7 days of 1 minute data and appends any successive data point by point.  Also runs windowed longest
decreasing subsequence algorithm and calculates the difference of LIS and LDS as crude sentiment.
