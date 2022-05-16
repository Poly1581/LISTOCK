import sys
import numpy as np
import pandas as pd
import yfinance as yf
from datetime import datetime as dt

t = "UBER"
p = "5d"
i = "5m"
if len(sys.argv) == 4 :
	t = sys.argv[1]
	p = sys.argv[2]
	i = sys.argv[3]

data = yf.download(tickers=t, period=p, interval=i)
data.to_csv(t+"|"+p+"|"+i+".csv")