#ifndef RELAY_PIN_MAP_H__
#define RELAY_PIN_MAP_H__
#include <Arduino.h>
#define R0	2
#define R1 	3
#define R2 	4
#define R3	5
#define R4	6
#define R5	7
#define R6	8
#define R7	9
#define R8	10
#define R9	11
#define R10 12
#define R11 13
#define R12 14
#define R13 15
#define R14 16
#define R15 17
#define R16 18
#define R17 19
#define R18	20
#define R19 21
#define R20 22
#define R21 23
#define R22 24
#define R23 25
#define R24 26
#define R25 27
#define R26 28
#define R27 29
#define R28	30
#define R29 31
#define R30 32
#define R31 33
#define R32 34
#define R33 35
#define R34 36
#define R35 37
#define R36 38
#define R37 39
#define R38	40
#define R39 41
#define R40 42
#define R41 43
#define R42 44
#define R43 45
#define R44 46
#define R45 47
#define R46 48
#define R47 49
#define R48	50
#define R49 51
#define R50 52
#define R51 53
#define R52	A0
#define R53 A1
#define R54 A2
#define R55 A3
#define R56 A4
#define R57 A5
#define R58 A6
#define R59 A7
#define R60 A8
#define R61 A9
#define R62 A10
#define R63 A11


#define switchOn(relay)digitalWrite(R##relay,HIGH)
#define ReadRelay(relay) (digitalRead(R##relay)== HIGH)?(uint64_t)1:(uint64_t)0
#define switchOff(relay)digitalWrite(R##relay,LOW)
#define setupRelays(relay) pinMode(R##relay,OUTPUT)

#endif 
