/*
 * timer.c
 *
 *  Created on: 27/05/2014
 *      Author: Wellington
 */

#include "msp430g2553.h"
#include "timer.h"
#include "pins.h"


volatile int millis_counter_;
volatile int millis_cronometer_;
volatile long seconds_counter_;
volatile bool start_cronometer_; //BOOL
volatile bool start_tx_cronometer_;
volatile int tx_cronometer_;
volatile int tx_timeout_;

void InitializeClockTime() {

	millis_counter_ = 0;
	seconds_counter_ = 0;
	millis_cronometer_ = 0;
	start_cronometer_ = false;
	start_tx_cronometer_ = false;

	WDTCTL = WDT_MDLY_0_5;              // WDT as interval timer (period 8 ms)
	IE1 |= WDTIE;

}

void StartTxTimeout(int timeout) {
	tx_cronometer_ = 0;
	start_tx_cronometer_ = true;
	tx_timeout_ = timeout *16;
}


void SecondsElapsed(int interval) {


	millis_cronometer_ = 0;
	int presentTime = 0;

	//activate cronometer
	start_cronometer_ = true;              //BOOL
	int intervalEnd = 32000 * interval;

	while (presentTime < intervalEnd) {

		presentTime = millis_cronometer_;
	}

	start_cronometer_ = false;              //BOOL
	millis_cronometer_ = 0;
}

void QuaterMillisElapsed(int interval) {

	millis_cronometer_ = 0;
	int presentTime = 0;

	//activate cronometer
	start_cronometer_ = true;              //BOOL
	int intervalEnd = 8 * interval;

	while (presentTime < intervalEnd) {

		presentTime = millis_cronometer_;
	}

	//de-activate cronometer
	start_cronometer_ = false;              //BOOL
	millis_cronometer_ = 0;

}

int get_millis() {

	int ms;
	ms = millis_counter_ / 16;
	return ms;

}

int get_sec() {

	return seconds_counter_;
}

void BeginTest(){
	seconds_counter_ = 0;
	millis_counter_ = 0;
}

#pragma vector=WDT_VECTOR
__interrupt void wdt_timer(void) {

	millis_counter_ = millis_counter_ + 1;

	if (millis_counter_ == 32000) {
		GREEN_LED_TOGGLE();
		seconds_counter_ = seconds_counter_ + 1;
		millis_counter_ = 0;
	}

	if (start_cronometer_ == true) {
		millis_cronometer_ = millis_cronometer_ + 1;
	}

	if (start_tx_cronometer_) {
		tx_cronometer_ = tx_cronometer_ + 1;
		if (tx_cronometer_ > tx_timeout_) {
			start_tx_cronometer_ = false;
		}
	}

}
