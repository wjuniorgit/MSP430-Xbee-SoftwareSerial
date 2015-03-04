/*
 * pins.cpp
 *
 *  Created on: 18/06/2014
 *      Author: Wellington
 */

#include  "pins.h"

void initPins() {
	P1DIR = GREEN_LED | RED_LED;
	//pushbtn
	P1SEL &= ~BUTTON_S2;
	P1DIR &= ~BUTTON_S2;
	P1REN |= BUTTON_S2;
	P1IE |= BUTTON_S2;
	P1IFG &= ~BUTTON_S2;
}

