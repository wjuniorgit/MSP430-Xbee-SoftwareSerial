/*
 * softUart.h
 *
 *  Created on: 27/05/2014
 *      Author: Wellington
 */

#ifndef SOFTUART_H_
#define SOFTUART_H_

#include "ringbuffer.h"


//#define UART1RXBUFSIZE    10
//template<typename T_STORAGE>
class SoftwareSerial {
public:
	SoftwareSerial();
	virtual ~SoftwareSerial();
	bool IsEmpty();
	int Receive();
	void Transmit(unsigned char);
	void Transmit(const char *);

private:
	static ringbuffer<char,16> ring_buffer_;
	static __interrupt void Timer_A1_TX(void);
	static __interrupt void Timer_A0_RX(void);

	static unsigned int tx_char_buffer;                 // UART internal variable for TX
	static unsigned char rx_char_buffer;                    // Received UART character
	#define SOFT_UART_TXD   BIT1
	#define SOFT_UART_RXD   BIT0
	#define BIT_TIME_DIV_2     (( 16000000 / (9600*2) ) )
	#define BIT_TIME           ( 16000000 / 9600 )
	//#define BIT_TIME  1667
	//#define BIT_TIME_DIV_2  833


};



#endif /* SOFTUART_H_ */
