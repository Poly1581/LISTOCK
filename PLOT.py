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

fig = make_subplots(rows=4, cols=1, shared_xaxes=True, vertical_spacing=0.02)

stockdata = fig.add_trace(go.Candlestick(
	x=data.index,
	open=data["Open"],
	high=data["High"],
	low=data["Low"],
	close=data["Close"],
	name="Price History"),
	row=4,
	col=1)

LIS = fig.add_trace(go.Scatter(
	x=data.index,
	y=data["LIS"],
	name="LIS Data",
	line_color="green"),
	row=1,
	col=1)

LDS = fig.add_trace(go.Scatter(
	x=data.index,
	y=data["LDS"],
	name="LDS Data",
	line_color="red"),
	row=2,
	col=1)

Sentiment = fig.add_trace(go.Scatter(
	x=data.index,
	y=data["Sentiment"],
	name="Stock Sentiment",
	line_color="grey"),
	row=3,
	col=1)

fig.show()