#include <stdint.h>
#include <util/crc16.h>
#include <FastCRC.h>
#include "RelayPinMap.h"

FastCRC8 CRC8;
uint8_t crc = 0x0;
const uint8_t SYNC = 0xD0;
uint64_t RelayStatus = 0xDEADBEEFDEADBEAF;
uint8_t* p; 
long lastTime = 0;
void setup()
{
	initRelay();
	Serial.begin(115200);
	p = (uint8_t*) &RelayStatus;

}

void loop()
{
	if (RecieveStatus());
	else
	{
		ReadRelayStatus();	
	}
	applyStaus();
	sendStatus();
	delay(500);

	

}

void applyStaus()
{
	uint64_t temp = RelayStatus;
	for(int i=0;i<64;i++)
	{
		
		if((temp & 0x01)==1)
		{
			RelayOn(i);
		}
		else
			RelayOff(i);
		temp = (temp >> 1);
	}
}
void sendStatus()
{
	uint8_t buffer[10];
	buffer[0] = 'a' ;
	uint8_t* p = (uint8_t*) &RelayStatus;
		for(int i =0;i<8;i++)
		{
			buffer[8-i] = *(p+i);
		}
	buffer[9] = crc ;
	Serial.write(buffer, 10);
}
bool RecieveStatus()
{
	char ch ;
	char r =0 ;
	int tries = 0 ;
	uint8_t TempCRC ;
	uint8_t buffer[10] ={0,0,0,0,0,0,0,0,0,0} ;	
	uint8_t* p = (uint8_t*) &RelayStatus ;
	do{
		if(Serial.available())
			ch = Serial.read();
		tries++;
	}while((ch != 'a') && (tries <11));
	if (ch == 'a')
	{
		buffer[r] = ch ;
		r++;
		do{
			if(Serial.available())
			{
				buffer[r]= Serial.read();
				r++;
			}
			tries++;
		}while((r <10) && (tries <100));
		if(tries >= 100);
		else
		{
			uint8_t* p = (uint8_t*) &RelayStatus;
			TempCRC = CRC8.smbus(buffer,9);
			if (TempCRC = buffer[9])
			{
				crc = TempCRC ;
				for(int i =0;i<8;i++)
				{
					*(p+i) = buffer[8-i];
				}
			  return true;
			}
		}
	}
	return false;
}
void ReadRelayStatus()
{
	uint64_t temp ;

		temp =(((uint64_t)ReadRelay(0)) << 0) | (((uint64_t)ReadRelay(10)) << 10) | (((uint64_t)ReadRelay(20)) << 20) | (((uint64_t)ReadRelay(30)) << 30) |
			((ReadRelay(1)) << 1) | ((ReadRelay(11)) << 11) | ((ReadRelay(21)) << 21) | ((ReadRelay(31)) << 31) |
			((ReadRelay(2)) << 2) | ((ReadRelay(12)) << 12) | ((ReadRelay(22)) << 22) | ((ReadRelay(32)) << 32) |
			((ReadRelay(3)) << 3) | ((ReadRelay(13)) << 13) | ((ReadRelay(23)) << 23) | ((ReadRelay(33)) << 33) |
			((ReadRelay(4)) << 4) | ((ReadRelay(14)) << 14) | ((ReadRelay(24)) << 24) | ((ReadRelay(34)) << 34) |
			((ReadRelay(5)) << 5) | ((ReadRelay(15)) << 15) | ((ReadRelay(25)) << 25) | ((ReadRelay(35)) << 35) |
			((ReadRelay(6)) << 6) | ((ReadRelay(16)) << 16) | ((ReadRelay(26)) << 26) | ((ReadRelay(36)) << 36) |
			((ReadRelay(7)) << 7) | ((ReadRelay(17)) << 17) | ((ReadRelay(27)) << 27) | ((ReadRelay(37)) << 37) |
			((ReadRelay(8)) << 8) | ((ReadRelay(18)) << 18) | ((ReadRelay(28)) << 28) | ((ReadRelay(38)) << 38) |
			((ReadRelay(9)) << 9) | ((ReadRelay(19)) << 19) | ((ReadRelay(29)) << 29) | ((ReadRelay(39)) << 39) |
			
			((ReadRelay(40)) << 40) | ((ReadRelay(50)) << 50) | ((ReadRelay(60)) << 60) |
			((ReadRelay(41)) << 41) | ((ReadRelay(51)) << 51) | ((ReadRelay(61)) << 61) |
			((ReadRelay(42)) << 42) | ((ReadRelay(52)) << 52) | ((ReadRelay(62)) << 62) |
			((ReadRelay(43)) << 43) | ((ReadRelay(53)) << 53) | ((ReadRelay(63)) << 63) |
			((ReadRelay(44)) << 44) | ((ReadRelay(54)) << 54) | 
			((ReadRelay(45)) << 45) | ((ReadRelay(55)) << 55) | 
			((ReadRelay(46)) << 46) | ((ReadRelay(56)) << 56) | 
			((ReadRelay(47)) << 47) | ((ReadRelay(57)) << 57) | 
			((ReadRelay(48)) << 48) | ((ReadRelay(58)) << 58) | 
			((ReadRelay(49)) << 49) | ((ReadRelay(59)) << 59) ;
			
	RelayStatus = temp;
	CalculateCRC();
}
void CalculateCRC()
{
	uint8_t  packet[9] ;
	uint8_t* p = (uint8_t*) &RelayStatus;
	packet[0] = 'a' ;
	for(int i =0 ;i< 8 ;i++)
	{
		packet[8-i] = *(p+i);
	}
	crc = CRC8.smbus(packet, 9);
}
void initRelay()
{
	setupRelays(0);setupRelays(10);setupRelays(20);setupRelays(30);setupRelays(40);setupRelays(50);setupRelays(60);
	setupRelays(1);setupRelays(11);setupRelays(21);setupRelays(31);setupRelays(41);setupRelays(51);setupRelays(61);
	setupRelays(2);setupRelays(12);setupRelays(22);setupRelays(32);setupRelays(42);setupRelays(52);setupRelays(62);
	setupRelays(3);setupRelays(13);setupRelays(23);setupRelays(33);setupRelays(43);setupRelays(53);setupRelays(63);
	setupRelays(4);setupRelays(14);setupRelays(24);setupRelays(34);setupRelays(44);setupRelays(54);
	setupRelays(5);setupRelays(15);setupRelays(25);setupRelays(35);setupRelays(45);setupRelays(55);
	setupRelays(6);setupRelays(16);setupRelays(26);setupRelays(36);setupRelays(46);setupRelays(56);
	setupRelays(7);setupRelays(17);setupRelays(27);setupRelays(37);setupRelays(47);setupRelays(57);
	setupRelays(8);setupRelays(18);setupRelays(28);setupRelays(38);setupRelays(48);setupRelays(58);
	setupRelays(9);setupRelays(19);setupRelays(29);setupRelays(39);setupRelays(49);setupRelays(59);
	
}
void RelayOn(int relay)
{
	switch(relay)
	{
		case 0 :switchOn(0);break;case 10 :switchOn(10);break;case 20 :switchOn(20);break;case 30 :switchOn(30);break;
		case 1 :switchOn(1);break;case 11 :switchOn(11);break;case 21 :switchOn(21);break;case 31 :switchOn(31);break;
		case 2 :switchOn(2);break;case 12 :switchOn(12);break;case 22 :switchOn(22);break;case 32 :switchOn(32);break;
		case 3 :switchOn(3);break;case 13 :switchOn(13);break;case 23 :switchOn(23);break;case 33 :switchOn(33);break;
		case 4 :switchOn(4);break;case 14 :switchOn(14);break;case 24 :switchOn(24);break;case 34 :switchOn(34);break;
		case 5 :switchOn(5);break;case 15 :switchOn(15);break;case 25 :switchOn(25);break;case 35 :switchOn(35);break;
		case 6 :switchOn(6);break;case 16 :switchOn(16);break;case 26 :switchOn(26);break;case 36 :switchOn(36);break;
		case 7 :switchOn(7);break;case 17 :switchOn(17);break;case 27 :switchOn(27);break;case 37 :switchOn(37);break;
		case 8 :switchOn(8);break;case 18 :switchOn(18);break;case 28 :switchOn(28);break;case 38 :switchOn(38);break;
		case 9 :switchOn(9);break;case 19 :switchOn(19);break;case 29 :switchOn(29);break;case 39 :switchOn(39);break;
		
		case 40 :switchOn(40);break;case 50 :switchOn(50);break;case 60 :switchOn(60);break;
		case 41 :switchOn(41);break;case 51 :switchOn(51);break;case 61 :switchOn(61);break;
		case 42 :switchOn(42);break;case 52 :switchOn(52);break;case 62 :switchOn(62);break;
		case 43 :switchOn(43);break;case 53 :switchOn(53);break;case 63 :switchOn(63);break;
		case 44 :switchOn(44);break;case 54 :switchOn(54);break;
		case 45 :switchOn(45);break;case 55 :switchOn(55);break;
		case 46 :switchOn(46);break;case 56 :switchOn(56);break;
		case 47 :switchOn(47);break;case 57 :switchOn(57);break;
		case 48 :switchOn(48);break;case 58 :switchOn(58);break;
		case 49 :switchOn(49);break;case 59 :switchOn(59);break;
		
	}
}
void RelayOff(int relay)
{
	switch(relay)
	{
		case 0 :switchOff(0);break;case 10 :switchOff(10);break;case 20 :switchOff(20);break;case 30 :switchOff(30);break;
		case 1 :switchOff(1);break;case 11 :switchOff(11);break;case 21 :switchOff(21);break;case 31 :switchOff(31);break;
		case 2 :switchOff(2);break;case 12 :switchOff(12);break;case 22 :switchOff(22);break;case 32 :switchOff(32);break;
		case 3 :switchOff(3);break;case 13 :switchOff(13);break;case 23 :switchOff(23);break;case 33 :switchOff(33);break;
		case 4 :switchOff(4);break;case 14 :switchOff(14);break;case 24 :switchOff(24);break;case 34 :switchOff(34);break;
		case 5 :switchOff(5);break;case 15 :switchOff(15);break;case 25 :switchOff(25);break;case 35 :switchOff(35);break;
		case 6 :switchOff(6);break;case 16 :switchOff(16);break;case 26 :switchOff(26);break;case 36 :switchOff(36);break;
		case 7 :switchOff(7);break;case 17 :switchOff(17);break;case 27 :switchOff(27);break;case 37 :switchOff(37);break;
		case 8 :switchOff(8);break;case 18 :switchOff(18);break;case 28 :switchOff(28);break;case 38 :switchOff(38);break;
		case 9 :switchOff(9);break;case 19 :switchOff(19);break;case 29 :switchOff(29);break;case 39 :switchOff(39);break;
		
		case 40 :switchOff(40);break;case 50 :switchOff(50);break;case 60 :switchOff(60);break;
		case 41 :switchOff(41);break;case 51 :switchOff(51);break;case 61 :switchOff(61);break;
		case 42 :switchOff(42);break;case 52 :switchOff(52);break;case 62 :switchOff(62);break;
		case 43 :switchOff(43);break;case 53 :switchOff(53);break;case 63 :switchOff(63);break;
		case 44 :switchOff(44);break;case 54 :switchOff(54);break;
		case 45 :switchOff(45);break;case 55 :switchOff(55);break;
		case 46 :switchOff(46);break;case 56 :switchOff(56);break;
		case 47 :switchOff(47);break;case 57 :switchOff(57);break;
		case 48 :switchOff(48);break;case 58 :switchOff(58);break;
		case 49 :switchOff(49);break;case 59 :switchOff(59);break;
	}

}

///////////////////////////TEST AREA//////////////////////////////////////
void BlinkAll()
{
	for(int i=0;i<64;i++)
	{
		RelayOff(i);
	}
	delay(1000);
	for(int i=0;i<64;i++)
	{
		RelayOn(i);
	}
	delay(1000);	
}
void SequenceAll()
{
	for(int i=0;i<64;i++)
	{
	 RelayOn(i);
	 delay(500);
	}
	for(int i=0;i<64;i++)
	{
		RelayOff(i);
		delay(500);
	}
}
void RandomStatus()
{
  int r ;
  	for(int i=0;i<64;i++)
	{
                r = random(0,63);
		RelayOn(r);
	}
}
