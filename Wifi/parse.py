#Time; nameofdevice; macaddress; SSID
from timeit import default_timer as timer
import numpy as np
import pandas as pd
#/home/jeffmur/nexusOne.csv
reader = pd.read_csv(filepath_or_buffer = "/home/jeffmur/nexusOne.csv",
				 names = ['Garbage', 'Garbage2', 'time', 'protocol', 'result'],
				 sep = ";",
				 keep_date_col = True,
				 na_values=['N/A']);

# set up dataFrame for protocol and result
df = pd.DataFrame(reader, columns=['time', 'protocol', 'result'])

# remove any duplicates
df.drop_duplicates(keep='first')


# found serial number
def getData():
   start = timer()
   data = []
   j = -1
   for i in df['protocol']:
      j+=1
      # Assumption: name comes before data
      if(i == 'phone|sim|serial'):
	 name = df['result'][j]
      # check for w and i 
      if((i[0] == 'w') & (i[len(i)-2] == 'i')):
	 # check for connected wifi
	 if(i[5] == 'c'):
	    macAddress = i[16:(len(i)-5)]
	 else:
	    # macAddress
	    macAddress = i[10:(len(i)-5)]
	 # ssid
         if(len(macAddress) <= 40):
	    ssid = df['result'][j]
	    time = df['time'][j]
	    data.append({'time':time, 'serialNumber':name, 'macaddress':macAddress, 'ssid':ssid});
    
   parsedData = pd.DataFrame(data)
   end = timer()
   print("Time elapsed: " + str(end - start))
   return parsedData
	 

print(getData())



# Looking for 
# 	"phone|sim|serial"
#	"wifi|scan| MAC ADDRESS |ssid"
# find "wifi" (constant number of characters until 1000, 10000, etc.)
# then throw out the preceeding data 

