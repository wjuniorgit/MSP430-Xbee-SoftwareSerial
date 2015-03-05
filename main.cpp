#include "msp430g2553.h"
#include "globals.h"
#include "timer.h"
#include "pins.h"
#include "XbeeS1.h"

#define BUTTON BIT3

void startTest(void);

bool startT;

char btnpress;
unsigned char check;
char value;

/*
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	if (CALDCO_16MHZ == 0xFF)				// If calibration constant erased
			{
		while (1)
			;                               // do not load, trap CPU!!
	}

	DCOCTL = 0;                          // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_16MHZ;                    // Set DCO
	DCOCTL = CALBC1_16MHZ;

	initClockTime();
	initPins();

	//endbtn
	btnpress = 0;

	XbeeS1 xbee;

	_BIS_SR(GIE);                            // Enable CPU interrupts


	Xbee16Addr adr(0x00,0x01);


	Xbee64Addr adr64(0x00,0x13,0xA2,0x00,0x40,0x92,0xBA,0xEF);

	unsigned char counter=0;

	while (1) {

		// TXNODE EX1

		if (startT && counter < 1) {


			//xbee.txPacket(adr, teste, 150, strlen(teste));
			//xbee.txPacket(adr, teste);
			xbee.TxRequest64(adr64, "teste");
			//xbee.TxRemoteATCommand(adr64,'C','H');

			counter++;
			quaterMsElapsed(100);

			//RED_LED_TOGGLE();
		}else{
			startT = false;
			counter = 0;
		}


		while (!xbee.IsEmpty()) {
			//RED_LED_TOGGLE();
			//rxPacket = xbee.get_packet();
			//RED_LED_TOGGLE();
		}

		//ENDTXNODE


		if (btnpress == 1) {

			//RED_LED_TOGGLE();
			startTest();


			secondsElapsed(1);
			btnpress = 0;
		}



	}
}



void startTest() {
	startT = true;
	initTest();

}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
	btnpress++;
	P1IFG &= ~BUTTON;
	//P1IES ^= BUTTON;
}
