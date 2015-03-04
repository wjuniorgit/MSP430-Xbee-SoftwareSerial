/*
 * Xbee16addr.h
 *
 *  Created on: 16/06/2014
 *      Author: Wellington
 */

#ifndef XBEE16ADDR_H_
#define XBEE16ADDR_H_

class Xbee16addr {
public:
	Xbee16addr(unsigned char msb_, unsigned char lsb_){
		msb = msb_;
		lsb = lsb_;
	}
	virtual ~Xbee16addr(){}
	unsigned char get_msb(){
		return msb;
	}
	unsigned char get_lsb(){
		return lsb;
	}
private:
	unsigned char msb;
	unsigned char lsb;


};



#endif /* XBEE16ADDR_H_ */
