/*
 * PacketInfo.cpp
 *
 *  Created on: 15/06/2014
 *      Author: Wellington
 */



#include "PacketInfo.h"

PacketInfo::PacketInfo() {
	addr = 0;
	rssi = 0;
	msMsb = 0;
	msLsb = 0;
	secMsb = 0;
	secLsb = 0;
	packNum = 0;
	oriAddr = 0;
	tries = 0;
}
PacketInfo::~PacketInfo() {

}
