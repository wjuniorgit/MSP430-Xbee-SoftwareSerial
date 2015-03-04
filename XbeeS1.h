/*
 * XbeeS1.h
 *
 *  Created on: 14/06/2014
 *      Author: Wellington
 */
#include <inttypes.h>
#include "softUart.h"
#include "pins.h"
#include "PacketInfo.h"
#include "Xbee16addr.h"
#include "Xbee64addr.h"
#include "timer.h"

#ifndef XBEES1_H_
#define XBEES1_H_

class XbeeS1 {
public:
	XbeeS1();
	virtual ~XbeeS1();
	void xbeeSendByte(char, bool);
	static void getRXPacket(void);
	bool getTxOk(void);
	void setTxOk(bool);
	bool isEmpty();
	char getPacket();
	void txPacket(Xbee16addr addr, const char *payload);
	void txPacket64(Xbee64addr addr, const char *payload);
	//void txPacket(Xbee16addr, PacketInfo, int);



private:
#define START_BYTE          0x7e
#define ESCAPE              0x7d
#define XON                 0x11
#define XOFF                0x13
#define MAXMSGSIZE 6

	static int strlen(const char* word);
	static void Timer0_A0(void);
	static softUart su;
	static volatile char dataIndex;
	static volatile bool isEscaped;
	static volatile uint8_t rxChecksum;
	static volatile uint8_t txChecksum;
	static int msgsize;
	static volatile char msb;
	static volatile char lsb;
	static bool txOk;
	//static char recievedMessage_[MAXMSGSIZE];
	static PacketInfo packet;
	//static ringbuffer<PacketInfo,8> packetBuffer;
	//static ringbuffer<PacketInfo,2> packetBuffer;
	static ringbuffer<char,16> packetBuffer;
	static unsigned char rxApiFrame;
	static unsigned char txStatus;


};

#endif /* XBEES1_H_ */
