/*
 * softUart.c
 *
 *  Created on: 27/05/2014
 *      Author: Wellington
 */

#include "msp430g2553.h"
#include "software_serial.h"
#include "pins.h"
#include "timer.h"

ringbuffer<char,16> SoftwareSerial::ring_buffer_;
unsigned int SoftwareSerial::tx_char_buffer;
unsigned char SoftwareSerial::rx_char_buffer;

SoftwareSerial::SoftwareSerial() {
	P2OUT = 0x00;
	P2SEL = SOFT_UART_TXD + SOFT_UART_RXD;            //  uart TX/RX pinos
	P2DIR = 0xFF & ~SOFT_UART_RXD;               //
	P2OUT = 0XFF;

	// Configures Timer_A for full-duplex UART operation
	TA1CCTL1 = OUT;                          // Set TXD Idle as Mark = '1'
	TA1CCTL0 = SCS + CM1 + CAP + CCIE;       // Sync, Neg Edge, Capture, Int
	TA1CTL = TASSEL_2 + MC_2 + TAIE;  // SMCLK, start in continuous mode
}

SoftwareSerial::~SoftwareSerial() {
	// TODO Auto-generated destructor stub
}

bool SoftwareSerial::IsEmpty() {

	return ring_buffer_.empty();

}

int SoftwareSerial::Receive() {
	return ring_buffer_.pop_front();

}

//template<typename T_STORAGE>
void SoftwareSerial::Transmit(unsigned char c) {
	while (TACCTL1 & CCIE){
		;        }                      // Ensure last char got TX'd

	TA1CCR1 = TA1R;                               // Current state of TA counter
	TA1CCR1 += BIT_TIME;                         // One bit time till first bit
	TA1CCTL1 = OUTMOD0 + CCIE;                           // Set TXD on EQU0, Int
	tx_char_buffer = c;                                       // Load global variable
	tx_char_buffer |= 0x100;                              // Add mark stop bit to TXData
	tx_char_buffer <<= 1;                                        // Add space start bit
	//__delay_cycles(800);
	QuaterMillisElapsed(5);
}

//template<typename T_STORAGE>
void SoftwareSerial::Transmit(const char *s) {

	unsigned char c;

	while (*s) {
		c = (unsigned char) *s++;
		//if (c == '\n') {
		if (c == '\0') {
			return;
		} else {
			Transmit(c);
		}

	}

}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void SoftwareSerial::Timer_A1_TX(void) {

	static unsigned char txBitCnt = 10;

	switch (__even_in_range(TA1IV, TA1IV_TAIFG)) // Efficient switch-implementation
	//switch (__even_in_range(TA1IV, TA1IV_TAIFG)) // Efficient switch-implementation
	{
	case 2:
		if (txBitCnt == 0) {                    // All bits TXed?
			TA1CCTL1 &= ~CCIE;           // All bits TXed, disable interrupt
			txBitCnt = 10;                      // Re-load bit counter
		} else {
			TA1CCR1 += BIT_TIME;                     // Add Offset to CCRx

			if (tx_char_buffer & 0x01) {
				TA1CCTL1 &= ~OUTMOD2;              // TX Mark '1' //set
			} else {
				TA1CCTL1 |= OUTMOD2;               // TX Space '0' //reset
			}
			tx_char_buffer >>= 1;
			txBitCnt--;
		}
	}

}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void SoftwareSerial::Timer_A0_RX(void) {

	static unsigned char rxBitCnt = 8;
	static unsigned char rxData = 0;

	TA1CCR0 += BIT_TIME;                 // Add Offset to CCRx

	if (TA1CCTL0 & CAP) {                 // Capture mode = start bit edge
		TA1CCTL0 &= ~CAP;                 // Switch capture to compare mode
		TA1CCR0 += BIT_TIME_DIV_2;                 // Point CCRx to middle of D0

	} else {
		rxData >>= 1;
		if (TA1CCTL0 & SCCI) {            // Get bit waiting in receive latch
			rxData |= 0x80;
		}
		rxBitCnt--;
		if (rxBitCnt == 0) {             // All bits RXed?

			//rxBuffer = rxData;             // Store in global variable
			ring_buffer_.push_back(rxData);

			rxBitCnt = 8;             // Re-load bit counter
			TA1CCTL0 |= CAP;             // Switch compare to capture mode

		}
	}
}
