import sys
from timeit import default_timer as timer
import numpy as np
import pandas as pd
#   /home/jeffmur/nexusOne.csv      smallData.csv

dataFile = "smallData.csv"

reader = pd.read_csv(filepath_or_buffer = dataFile,
				 names = ['Garbage', 'Garbage2', 'time', 'protocol', 'result'],
				 sep = ";",
				 keep_date_col = True,
				 
				 na_values=['N/A']);

# set up dataFrame for protocol and result
df = pd.DataFrame(reader, columns=['time', 'protocol', 'result'])

# remove any duplicates
df['result'].drop_duplicates(keep='first')

# locates phone|sim|serial number
def loc_serial(df):	
    name = df.iloc[np.where(df.protocol.values == 'phone|sim|serial')]
    return name['result'].drop_duplicates(keep='first')       
 
# mac, ssid, time to DataFrame
def loc_mac(df):
    base = df.iloc[np.where(df.protocol.str.contains('ssid'))]
    time = base['time']
    for v in loc_serial(df).values: device = v
    ssid = base['result']
    mac = base['protocol']
    mac = mac.map(lambda x: str(x)[16:-5] if(str(x)[5] == 'c')	
                             else str(x)[10:-5])
    data = ({'time':time.values, 'macaddress':mac.values, 'ssid':ssid.values});
    data['device'] = device
    return pd.DataFrame(data)

start = timer()
data = loc_mac(df)
data.to_csv(r'parsedData.csv',index=False, sep=";")
end = timer()
print("Time elapsed: " + str(end - start))

print(data)

# Found 
# 	"phone|sim|serial"
#	"wifi|scan| MAC ADDRESS |ssid"
#
# Into DataFrame
#	device; macaddress; SSID; Time


