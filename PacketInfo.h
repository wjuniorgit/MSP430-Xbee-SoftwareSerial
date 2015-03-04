/*
 * PacketInfo.h
 *
 *  Created on: 15/06/2014
 *      Author: Wellington
 */

#ifndef PACKETINFO_H_
#define PACKETINFO_H_


class PacketInfo {
public:
	PacketInfo();
	virtual ~PacketInfo();
	unsigned char addr;
	unsigned char rssi;
	unsigned char msMsb;
	unsigned char msLsb;
	unsigned char secMsb;
	unsigned char secLsb;
	unsigned char packNum;
	unsigned char oriAddr;
	unsigned char tries;
};


#endif /* PACKETINFO_H_ */
