/*
 * XbeeS1.cpp
 *
 *  Created on: 14/06/2014
 *      Author: Wellington
 */

#include "XbeeS1.h"

PacketInfo XbeeS1::packet;
softUart XbeeS1::su;
volatile char XbeeS1::dataIndex;
volatile bool XbeeS1::isEscaped;
volatile uint8_t XbeeS1::rxChecksum;
volatile uint8_t XbeeS1::txChecksum;
int XbeeS1::msgsize;
volatile char XbeeS1::msb;
volatile char XbeeS1::lsb;
unsigned char XbeeS1::rxApiFrame;
unsigned char XbeeS1::txStatus;
//char XbeeS1::recievedMessage_[MAXMSGSIZE];
bool XbeeS1::txOk;
//ringbuffer<PacketInfo,8> XbeeS1::packetBuffer;
//ringbuffer<PacketInfo,2> XbeeS1::packetBuffer;
ringbuffer<char,16> XbeeS1::packetBuffer;


XbeeS1::XbeeS1() {

	//TA0CCTL0 = CCIE;
	TA0CCR0 = 60;
	TA0CCTL0 = CCIE;
	TA0CTL = TASSEL_2 + MC_2 + ID_0;

	dataIndex = 0;
	isEscaped = false;
	rxChecksum = 0x0;
	txChecksum = 0x0;
	msgsize = 255;
	msb = 0;
	lsb = 0;
	txOk = false;
	rxApiFrame = 0x0;
	txStatus = 0x0;
	// TODO Auto-generated constructor stub

}

XbeeS1::~XbeeS1() {
	// TODO Auto-generated destructor stub
}

int XbeeS1::strlen(const char* word){

	int word_lenght=0;

	unsigned char index=0;
	while(word[index]!=0){
		word_lenght++;
		index++;
	}

return word_lenght;
}

void XbeeS1::txPacket64(Xbee64addr addr, const char *payload) {

	int payloadsize = strlen(payload);

		while (!txOk ) {

		unsigned char byte = 0;
		txChecksum = 0x0;
		//START DELIMITER
		xbeeSendByte(START_BYTE, false);
		//LENGTH
		xbeeSendByte((((3 + payloadsize + 2) >> 8) & 0xff), true);
		xbeeSendByte(((3+ payloadsize + 2) & 0xff), true);
		//API IDENTIFIER
		xbeeSendByte(0x00, true);
		txChecksum += 0x00;
		//FRAME ID
		xbeeSendByte(0x01, true);
		txChecksum += 0x01;
		//DESTINATION ADRESS
		byte = addr.get_addr_sb(1);
		xbeeSendByte(byte, true);
		txChecksum += byte;
		byte = addr.get_addr_sb(2);
		xbeeSendByte(byte, true);
		txChecksum += byte;
	    byte = addr.get_addr_sb(3);
		xbeeSendByte(byte, true);
		txChecksum += byte;
	    byte = addr.get_addr_sb(4);
		xbeeSendByte(byte, true);
		txChecksum += byte;
		byte = addr.get_addr_sb(5);
		xbeeSendByte(byte, true);
		txChecksum += byte;
		byte = addr.get_addr_sb(6);
		xbeeSendByte(byte, true);
		txChecksum += byte;
		byte = addr.get_addr_sb(7);
		xbeeSendByte(byte, true);
		txChecksum += byte;
		byte = addr.get_addr_sb(8);
		xbeeSendByte(byte, true);
		txChecksum += byte;



		//OPTIONS
		xbeeSendByte(0x00, true);
		txChecksum += 0x00;
		//RF DATA

		while (*payload) {
			byte = ((unsigned char) *payload);
			xbeeSendByte(byte, true);
			txChecksum += byte;
			++payload;
		}

		txChecksum = 0xff - txChecksum;
		//CHECKSUM
		xbeeSendByte(txChecksum, true);
		quaterMsElapsed(400);
	}
	txOk = false;
}


void XbeeS1::txPacket(Xbee16addr addr, const char *payload) {

	int payloadsize = strlen(payload);

		while (!txOk ) {

		unsigned char byte = 0;
		txChecksum = 0x0;
		//START DELIMITER
		xbeeSendByte(START_BYTE, false);
		//LENGTH
		xbeeSendByte((((3 + payloadsize + 2) >> 8) & 0xff), true);
		xbeeSendByte(((3+ payloadsize + 2) & 0xff), true);
		//API IDENTIFIER
		xbeeSendByte(0x01, true);
		txChecksum += 0x01;
		//FRAME ID
		xbeeSendByte(0x01, true);
		txChecksum += 0x01;
		//DESTINATION ADRESS
		byte = addr.get_msb();
		xbeeSendByte(byte, true);
		txChecksum += byte;
		byte = addr.get_lsb();
		xbeeSendByte(byte, true);
		txChecksum += byte;
		//OPTIONS
		xbeeSendByte(0x00, true);
		txChecksum += 0x00;
		//RF DATA

		while (*payload) {
			byte = ((unsigned char) *payload);
			xbeeSendByte(byte, true);
			txChecksum += byte;
			++payload;
		}

		txChecksum = 0xff - txChecksum;
		//CHECKSUM
		xbeeSendByte(txChecksum, true);
		quaterMsElapsed(400);
	}
	txOk = false;
}


void XbeeS1::xbeeSendByte(char byte, bool escape) {

	if (escape
			&& (byte == START_BYTE || byte == ESCAPE || byte == XON
					|| byte == XOFF)) {
		su.xmit(ESCAPE);
		su.xmit(byte ^ 0x20);
	} else {
		su.xmit(byte);
	}

}

bool XbeeS1::getTxOk(void) {
	return false;
}
void XbeeS1::setTxOk(bool param) {

	//txOK = param;
}

bool XbeeS1::isEmpty() {

	return packetBuffer.empty();

}
char  XbeeS1::getPacket() {

	return packetBuffer.pop_front();
}

void XbeeS1::getRXPacket() {

	unsigned char ch;


	while (!su.empty()) {
		ch = su.recv();

		if (ch == ESCAPE) {
			isEscaped = true;
		}
		if (isEscaped) {
			ch = ch - 0x20;
			isEscaped = false;
		}
		if (ch == START_BYTE) {
			rxChecksum = 0x0;
			dataIndex = 0;
			msgsize = 0;
			msb = 0;
			lsb = 0;
			//recievedMessage_[dataIndex] = ch;
			dataIndex++;
		} else {

			if (dataIndex == 1) {
				msb = ch;
				//recievedMessage_[dataIndex] = ch;
			} else if (dataIndex == 2) {
				lsb = ch;

				msgsize = (msb << 8) | lsb;
				msgsize = msgsize + 0x04;

				//recievedMessage_[dataIndex] = ch;

			} else if (dataIndex < msgsize - 1 && dataIndex > 2) {

				//recievedMessage_[dataIndex] = ch;
				if (dataIndex == 3) {
					rxApiFrame = ch;
				}
				if (rxApiFrame != 0x89) {

					packetBuffer.push_back(ch);
					RED_LED_TOGGLE();
				} else if (rxApiFrame == 0x89) {
					if (dataIndex == 5) {
						txStatus = ch;
					}
				}

				rxChecksum = rxChecksum + ch;

				//} else if (dataIndex < msgsize && dataIndex > 2) {
			} else if (dataIndex == (msgsize - 1)) {

				//recievedMessage_[dataIndex] = ch;		//ultimo char
				rxChecksum = rxChecksum + ch;

				//RED_LED_TOGGLE();

				if (rxChecksum == 0xFF) {
					//RED_LED_TOGGLE();
					if (rxApiFrame != 0x89) {
						//packetBuffer.push_back(packet);

					} else if (rxApiFrame == 0x89 && txStatus == 0x0) {
						txOk = true;
					}

					//hardUARTSendArray("Correct Checksum ", 17);
					//interpretPackage(recievedMessage_, msgsize);
				} else {
					//hardUARTSendArray("Incorrect Checksum ", 19);
				}

			}

			dataIndex++;
		}
	}
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void XbeeS1::Timer0_A0(void) {
	XbeeS1::getRXPacket();
}

