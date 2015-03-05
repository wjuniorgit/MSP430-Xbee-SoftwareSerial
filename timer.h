/*
 * timer.h
 *
 *  Created on: 27/05/2014
 *      Author: Wellington
 */

#ifndef TIMER_H_
#define TIMER_H_


void SecondsElapsed(int);
void InitializeClockTime(void);
void BeginTest(void);
void QuaterMillisElapsed(int);
void StartTxTimeout(int);
int get_millis();
int get_sec();


#endif /* TIMER_H_ */
