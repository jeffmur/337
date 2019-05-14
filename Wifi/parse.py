#Time; nameofdevice; macaddress; SSID

import numpy as np
import pandas as pd
#/home/jeffmur/nexusOne.csv
reader = pd.read_csv(filepath_or_buffer = "smallData.csv",
				 names = ['Garbage', 'Garbage2', 'time', 'protocol', 'result'],
				 sep = ";",
				 keep_date_col = True,
				 na_values=['N/A']);

df = pd.DataFrame(reader, columns=['protocol', 'result'])

# found serial number
def printSerialNumber():
   j = -1
   for i in df['protocol']:
      j+=1
      if(i == 'phone|sim|serial'):
         print(df['result'][j])

# found macaddress SHA
def printMacSSID() :
   j = -1
   for i in df['protocol']:
      j+=1
      if((i[0:4] == 'wifi') & (i[(len(i)-1)] == 'd')):
	 # macAddress
	 print("macAddress: " + i[10:(len(i)-5)])
	 # ssid
	 print("SSID: " + df['result'][j])

printSerialNumber()
printMacSSID()


# Looking for 
# 	"phone|sim|serial"
#	"wifi|scan| MAC ADDRESS |ssid"
# find "wifi" (constant number of characters until 1000, 10000, etc.)
# then throw out the preceeding data 

