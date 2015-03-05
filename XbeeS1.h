/*
 * XbeeS1.h
 *
 *  Created on: 14/06/2014
 *      Author: Wellington
 */
#include <inttypes.h>
#include "softUart.h"
#include "pins.h"
#include "xbee_16_addr.h"
#include "xbee_64_addr.h"
#include "timer.h"

#ifndef XBEES1_H_
#define XBEES1_H_

class XbeeS1 {
public:
	XbeeS1();
	virtual ~XbeeS1();
	void XbeeSendByte(char, bool);
	static void GetRXPacket(void);
	bool get_tx_ok(void);
	void set_tx_ok(bool);
	bool IsEmpty();
	char get_packet();
	void TxRequest16(Xbee16Addr addr, const char *payload);
	void TxRequest64(Xbee64Addr addr, const char *payload);
	void TxATCommand(const char first_char, const char second_char);
	void TxATCommand(const char first_char, const char second_char, const char* parameter);
	void TxRemoteATCommand(Xbee64Addr addr, const char first_char, const char second_char);
    void TxRemoteATCommand(Xbee64Addr addr, const char first_char, const char second_char, const char* parameter);

private:
#define START_BYTE          0x7e
#define ESCAPE              0x7d
#define XON                 0x11
#define XOFF                0x13
#define MAXMSGSIZE 6

#define TX_REQUEST_64 0x00
#define TX_REQUEST_16 0X01
#define AT_COMMAND 0x08
#define REMOTE_AT_REQUEST 0x17
#define RX_PACKET_16 0x81
#define RX_PACKET_64 0x82
#define AT_COMMAND_RESPONSE 0x88
#define TX_STATUS 0x89
#define REMOTE_AT_RESPONSE 0x97


	static int strlen(const char* word);
	static void Timer0_A0(void);
	static softUart software_serial_;
	static volatile char data_index_;
	static volatile bool is_escaped_;
	static volatile uint8_t rx_checksum_;
	static volatile uint8_t tx_checksum_;
	static int message_size_;
	static volatile char msb_;
	static volatile char lsb_;
	static bool tx_ok_;
	static ringbuffer<char,16> packet_buffer_;
	static unsigned char rx_api_frame_;
	static unsigned char tx_status_;


};

#endif /* XBEES1_H_ */
