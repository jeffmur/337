#Time; nameofdevice; macaddress; SSID

import numpy as np
import pandas as pd

df = pd.read_csv(filepath_or_buffer = "nexusOne.csv",
				 names = ['Date', 'Protocol', 'Result'],
				 sep = ";",
				 usecols = [2, 3, 4]);

print(df)

# find "wifi" (constant number of characters until 1000, 10000, etc.)
# then throw out the preceeding data 

