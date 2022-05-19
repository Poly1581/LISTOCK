# LISTOCK
Uses windowed longest increasing subsequence for stock applications.  Uses python yfinance api to pull stock data.
Initializes with 7 days of 1 minute data and appends any successive data point by point.  Also runs windowed longest
decreasing subsequence algorithm and calculates the difference of LIS and LDS as crude sentiment. Testing windowed vs
full lis and lds showed ~10x speed increase with window size of 180 on 5 stocks with 7 days of 1 minute data each
(~13000 data points).
