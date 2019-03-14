# Testing Python Functionality
# By Jeffrey Murray WI19 CSS 337
import sys
import os
import binascii
import base64
import hashlib
from Crypto.Cipher import *

## Start of Helper Functions

def removePad(string) :
	newstring = string.replace("0","")
	if(newstring == ''):
		return 0
	return newstring

def resizeByte(length, val) :
	result = str(val).zfill(length)
	return result

def toBytes(data) :
	return str(data).encode()

def toHex(bytes) :
	return binascii.hexlify(bytes)

def formatString(data) :
	string = str(data)
	newstring = string.replace("b", "")
	newstring = newstring.replace("'", "")
	return newstring.upper()

def printByte(byte) :
	print(byteToString(byte))

## End of Helper functions ##

## Py Enviornment: Hashlib
## SHA256(INT) - > prints hexadecimal hash
## input: SID (input: ASCII)
## into byte format with string.encode
## call SHA256 digest program with hashlib
## Output: HexaDecimal UPPERCASE
def SHA256(SID) :
	my_bytes = toBytes(SID)
	return str(hashlib.sha256(my_bytes).hexdigest().upper())

from Crypto.Cipher import AES

## Py Enviornment: Cryptodome
## encrypt(int amount, string kWallet)
## input: amount  - $$$ you want to encrypt
## input: kWallet - key for AES encryption with MODE: Electronic Cook Book
## Output: HexaDecimal UPPERCASE
def encrypt(amount, kWallet) :
	money = base64.b16decode(resizeByte(32, amount))
	key = base64.b16decode(toBytes(kWallet))
	cipher = AES.new(key, AES.MODE_ECB)
	ctext = base64.b16encode(cipher.encrypt(money))
	return ctext.decode('utf-8')

## Py Enviornment: Cryptodome
## encrypt(string EMD, string kWallet) -> int 
## input: EMD  - encrypted value
## input: kWallet - key for AES encryption with MODE: Electronic Cook Book
## Output: amount of money to be added to the account (int)
def decrypt(EMD, kWallet) :
	cipherText = base64.b16decode(toBytes(EMD))
	key = base64.b16decode(toBytes(kWallet))
	cipher = AES.new(key, AES.MODE_ECB)
	ptext = base64.b16encode(cipher.decrypt(cipherText))
	return ptext.decode('utf-8')

#kWallet = SHA256(1876007)
#print("Current key: " + kWallet)
#emd = encrypt(119, kWallet)
#print("After encrypt(amount, kWallet): " + emd)

#decrypted = decrypt(emd, kWallet)
#print("After decrypt(EMD, kWallet)   : " + removePad(decrypted))

def UI_start() : # options for user
	print()
	print("What would you like to do?")
	print("0 : Quit")
	print("1 : New Wallet ID")
	print("2 : View Wallet")
	print("3 : Sync Wallets")
	print("4 : Send Encrypted Token")
	print("5 : Receive Encrypted Token")
	print("6 : Print Ledger")
	c = input()
	return int(c)

## Helper Functions
def newToken(WIDa, WIDb, amount, counter):
	tokenlist = [resizeByte(8,WIDa), resizeByte(8, WIDb), resizeByte(8, amount), resizeByte(8,counter)]
	token = ''.join(str(i) for i in tokenlist)
	return str(token)

StoredTokens = [] ### STORAGE OF WALLET TOKENS

def generateToken(WIDa, WIDb, amount, counter) :
	token = newToken(WIDa, WIDb, amount, counter)
	StoredTokens.append((removePad(WIDa), removePad(WIDb), int(amount), int(counter)))
	x = encrypt(token, kBank)
	return x 

def decryptToken(encryptToken, key) :
	token = decrypt(encryptToken, key)
	if(len(str(token)) < 32):
		print("Invalid Token Length!")
		return -1;
	WIDA, WIDB, AMOUNT, COUNT = token[:9], token[10:17], token[17:24], token[-2:]
	synced = True
	return removePad(WIDA), removePad(WIDB), int(AMOUNT), int(COUNT)
	
def enterEMD(key) : # admin function "-1" hidden option use SID(chrisSID or timSID)
	print("Enter the EMD :")
	EMD = input()
	decryption = decrypt(EMD, key)
	return int(decryption)
## End of helper functions
## Initial Data
m_count = -1
kBank = "F25D58A0E3E4436EC646B58B1C194C6B505AB1CB6B9DE66C894599222F07B893" # key used in token generation
def isValid(encryptedToken):
	token = decryptToken(encryptedToken, kBank)
	for t in StoredTokens:
		if(str(t) == str(token)):
			return False
	StoredTokens.append(token)
	m_count = len(StoredTokens)
	return True
choice = -1
balance = 0
mySID = '1876007'
chrisSID = '1941191'
timSID = '1941193'
kWallet = SHA256(mySID)
senderID = -1
syncToken = newToken(chrisSID[-3:], mySID[-3:], 0, '0')
syncEncrypt = encrypt(syncToken, kBank)
moneyToken = newToken(chrisSID[-3:], mySID[-3:], 200, 1)
moneyEncrypt = encrypt(moneyToken, kBank)
print("Chris has sent you a sync request! : " + str(syncEncrypt))
print("    WID: " + str(chrisSID)[-3:])
print("Encrypted Token with $200: " + str(moneyEncrypt))
synced = False
while(choice != 0) :
	choice = UI_start()
	if(choice == 1) : # NEW SID
		print("Enter your SID :")
		sid = input()
		mySID = (sid)
		kWallet = SHA256(sid)
		print("Thank you! That will be a secret...")
		synced = False;
		balance = 0
		m_count = 0
		StoredTokens = []

	if(choice == 2) : # Display Wallet
		print()
		print("---StartOFWallet---")
		print("Balance: $" + str(balance))
		print("    SID: " + str(mySID))
		print("kWallet: " + str(kWallet))
		if(synced == True) :
			print("Synced Wallet: " + str(senderID))
			print("Current Count: " + str(m_count))
		else :
			print("You must sync your wallet!")
		print("----EndOfWallet----")
		print()

	if(choice == -1) : ## Testing Decrypt EMD
		print("Welcome you have entered the EMD Tester function!")
		print("This is for admins only!")
		print("SID: " + str(mySID))
		amount = enterEMD(kWallet)
		balance += amount
		print("Success! Balance has been updated")
		print("Updated Balance: $" + str(balance))

	if(choice == 3) : #Sync Wallets
		print("Sync in progress...")
		print("What wallet are we syncing with?")
		senderID = input()
		cryptToken = generateToken(mySID[-3:], senderID, 0, 0)
		print("Sending token to..." + senderID + "..." + cryptToken)
		m_count += 1
		synced = True;
		choice = 5

	if(choice == 4): # Send Encrypted Token
		if(synced == True):
			print("Amount to send? :")
			amount = input()
			if(int(amount) > 999) :
				amount = 999
				print("Exception Thrown: The max amount of money to send is $999")
			elif(int(amount) < 0) :
				amount = 0
				print("Exception Thrown: You can not request money at this time!")
			token = generateToken(mySID[-3:], senderID, amount, ++m_count)
			balance -= int(amount)
			print("Updated Balance: $" + str(balance))
			print("Encrypted token: " + str(token))
		else:
			print("You can't do that without syncing!")

	if(choice == 5) : # Recieve Encrypted Token
		if(synced == True):
			print("Decryption in progress...")
			print("Please input Encrypted Token")
			cryptToken = input()

			if(isValid(cryptToken)):
				senderID, receiverID, amount, counter = decryptToken(cryptToken, kBank)
				token = newToken(senderID, receiverID, amount, ++counter)
				print(token)
				print("senderID  : " + str(senderID))
				print("receiverID: " + str(receiverID))
				print("amount    : " + str(amount))
				print("counter   : " + str(counter))
				if(int(mySID[-3:]) != int(receiverID)):
					print("Bad Token -- issue with ReceiverID! {Expected WIDB=" + str(int(mySID[-3:])) + "}")
					continue;
				if(counter == m_count):
					m_count += 1
				balance += int(amount)
				synced = True;
			else:			
				 print("Relay attack denied!")							
				 continue;
		else:
			print("You can't do that without syncing!")

	if(choice == 6):
		print("Printing all transactions (including syncs)")
		for t in StoredTokens:
			print(t)
print("Thank you for using Smart Wallet")
print("by Jeffrey Murray")

## Start of encryption testing
# Results:
# EMD = DFF663AFB11C4E8450033D1E90DC8F18
# Amount = 119 w/ Chris SID : 1941191

# EMD = 9DC4B037A1772850022EBA2C45648F2F
# Amount = 119 w/ Tim SID : 1941193
## End of encryption testing

## AES-256(00000444000003330000002100000001 ,
## F25D58A0E3E4436EC646B58B1C194C6B505AB1CB6B9DE66C894599222F07B893) =
## 965390DFD8B18BCD419CA0583896218A