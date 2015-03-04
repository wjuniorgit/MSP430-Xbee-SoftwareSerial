#include "msp430g2553.h"
#include "globals.h"
#include "timer.h"
#include "pins.h"
#include "XbeeS1.h"
#include "PacketInfo.h"

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


	char msbAddr;
	char lsbAddr;
	char thisLsbAddr;



	//Nodo solo - 5 - exp1
	msbAddr = 0x00;
	lsbAddr = 0x01;
	thisLsbAddr = 0x05;

	Xbee16addr adr(msbAddr,lsbAddr);
	//adr.msb = msbAddr;
	//adr.lsb = lsbAddr;
	char rxPacket;
	PacketInfo txPacket;

	startT = false;
	int packNumCounter = 0;
	int packTxCounter = 0;
	int sec = 0;
	int ms = 0;
	int j = 0;
	value = 0x45;

	while (1) {

		// TXNODE EX1

		if (startT && packTxCounter < 100) {
			ms = getMs();
			sec = getSec();

			txPacket.secMsb = sec >> 8;
			txPacket.secLsb = sec & 0xff;
			txPacket.packNum = packNumCounter;
			txPacket.oriAddr = thisLsbAddr;
			txPacket.msMsb = ms >> 8;
			txPacket.msLsb = ms & 0xff;

			char* stringa = "teste";
			char teste[4];
			teste[0]=0x45;
			teste[1]=0x67;
			teste[2]=0x65;
			teste[3]=0x67;
			teste[4]=0x22;



			//xbee.txPacket(adr, teste, 150, strlen(teste));
			xbee.txPacket(adr, teste);

			packTxCounter++;

			quaterMsElapsed(100);

			//RED_LED_TOGGLE();
		}

		while (!xbee.isEmpty()) {
			RED_LED_TOGGLE();
			rxPacket = xbee.getPacket();
			RED_LED_TOGGLE();

		}

		//ENDTXNODE





		/*
		 // TXNODE EX2
		 if (startT && packTxCounter < 100) {
		 ms = getMs();
		 sec = getSec();
		 txPacket.secMsb = sec >> 8;
		 txPacket.secLsb = sec & 0xff;
		 txPacket.packNum = packNumCounter;
		 txPacket.oriAddr = thisLsbAddr;
		 txPacket.msMsb = ms >> 8;
		 txPacket.msLsb = ms & 0xff;
		 xbee.txPacket(adr, txPacket, 150);
		 packTxCounter++;
		 quaterMsElapsed(400);
		 RED_LED_TOGGLE();
		 }

		 if (!xbee.isEmpty()) {
		 rxPacket = xbee.getPacket();
		 if (rxPacket.secLsb == 0xFF && rxPacket.secMsb == 0xFF) {

		 if (thisLsbAddr == 0x02) {
		 quaterMsElapsed(400);
		 }
		 if (thisLsbAddr == 0x03) {
		 quaterMsElapsed(700);
		 }
		 if (thisLsbAddr == 0x04) {
		 quaterMsElapsed(1000);
		 }
		 if (thisLsbAddr == 0x05) {
		 quaterMsElapsed(1300);

		 }

		 startTest();
		 } else {
		 rxPacket = xbee.getPacket();
		 txPacket.secMsb = rxPacket.secMsb;
		 txPacket.secLsb = rxPacket.secLsb;
		 txPacket.packNum = rxPacket.packNum;
		 txPacket.oriAddr = rxPacket.oriAddr;
		 txPacket.msMsb = rxPacket.msMsb;
		 txPacket.msLsb = rxPacket.msLsb;
		 xbee.txPacket(adr, txPacket, 150);
		 quaterMsElapsed(400);
		 RED_LED_TOGGLE();
		 }
		 }
		 */
		//ENDTXNODE





		/*
		 //UAV NODE
		 while (!xbee.isEmpty()) {
		 rxPacket = xbee.getPacket();


		 packNumCounter++;
		 // xbee.txPacket(adr,rxPacket,1000);
		 RED_LED_TOGGLE();
		 }

		 	*/
		//secondsElapsed(1);
		if (btnpress == 1) {

			RED_LED_TOGGLE();
			startTest();


			for (j = 0; j < packNumCounter; j++) {

			//for (j = 0; j < packNumCounter * 9; j++) {

			//	hu.xmit();

			}

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
