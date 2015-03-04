/*
 * Xbee16addr.h
 *
 *  Created on: 16/06/2014
 *      Author: Wellington
 */

#ifndef XBEE64ADDR_H_
#define XBEE64ADDR_H_

class Xbee64addr {
public:
	Xbee64addr(unsigned char msb_, unsigned char secsb_, unsigned char tirsb_, unsigned char forsb_,  unsigned char fivsb_, unsigned char sixsb_, unsigned char sevsb_, unsigned char lsb_){

		msb = msb_;
		secsb = secsb_;
		tirsb = tirsb_;
		forsb = forsb_;
		fivsb = fivsb_;
		sixsb = sixsb_;
		sevsb = sevsb_;
		lsb = lsb_;
	}
	virtual ~Xbee64addr(){}

	unsigned char get_addr_sb(unsigned char index){

		if(index==1){
	     return msb;
		}
		if(index==2){
			     return secsb;
				}
		if(index==3){
			     return tirsb;
				}
		if(index==4){
			     return forsb;
				}
		if(index==5){
			     return fivsb;
				}
		if(index==6){
			     return sixsb;
				}
		if(index==7){
			     return sevsb;
				}
		if(index==8){
			     return lsb;
				}

		return msb;
	}

private:
	unsigned char msb;
	unsigned char secsb;
	unsigned char tirsb;
	unsigned char forsb;
	unsigned char fivsb;
	unsigned char sixsb;
	unsigned char sevsb;
	unsigned char lsb;


};



#endif /* XBEE16ADDR_H_ */
