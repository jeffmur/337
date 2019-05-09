#Time; nameofdevice; macaddress; SSID

import numpy as np
import pandas as pd

reader = pd.read_csv(filepath_or_buffer = "/home/jeffmur/nexusOne.csv",
				 names = ['Protocol', 'Result'],
				 sep = ";",
				 chunksize = 1,
                                 iterator = True,
				 keep_date_col = True,
				 na_values=['N/A'],
				 usecols = [3, 4]);
for chunk in reader:
     print(chunk)

# Looking for 
# 	"phone|sim|serial"
#	"wifi|scan| MAC ADDRESS |ssid"
# find "wifi" (constant number of characters until 1000, 10000, etc.)
# then throw out the preceeding data 

