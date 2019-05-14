#Time; nameofdevice; macaddress; SSID

import numpy as np
import pandas as pd

reader = pd.read_csv(filepath_or_buffer = "smallData.csv",
				 names = ['Garbage', 'Garbage2', 'Time', 'Protocol', 'Result'],
				 sep = ";",
				 keep_date_col = True,
				 na_values=['N/A']);

df = pd.DataFrame(reader, columns=['Protocol', 'Result'])

for i in df['Protocol']:
   if(i[0] == 'w' & i[int(len(i)-1)] == 'd'):
	 print(i)

df.loc[df['Protocol'] == 'w']

# Looking for 
# 	"phone|sim|serial"
#	"wifi|scan| MAC ADDRESS |ssid"
# find "wifi" (constant number of characters until 1000, 10000, etc.)
# then throw out the preceeding data 

