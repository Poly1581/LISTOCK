import sys
import numpy as np
import pandas as pd
import yfinance as yf
import datetime as dt
import plotly.graph_objects as go
from plotly.subplots import make_subplots

if len(sys.argv) != 2 :
	exit()

fileName = sys.argv[1]

data = pd.read_csv(fileName)

minValue = min(data["Low"])
maxValue = max(data["High"])
maxLIS = max(data["LIS"])
diff = maxValue-minValue
scale = diff/maxLIS

fig = make_subplots(rows=2, cols=1, shared_xaxes=True)
a1 = fig.add_trace(go.Candlestick(
	x=data.index,
	open=data["Open"],
	high=data["High"],
	low=data["Low"],
	close=data["Close"],
	name="market data"),
	row=1,
	col=1)

a2 = fig.add_trace(go.Scatter(
	x=data.index,
	y=data["LIS"],
	name="LIS data"),
	row=2,
	col=1)
fig.show()