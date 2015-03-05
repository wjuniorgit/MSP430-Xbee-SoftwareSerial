/*
 * Xbee16addr.h
 *
 *  Created on: 16/06/2014
 *      Author: Wellington
 */

#ifndef XBEE64ADDR_H_
#define XBEE64ADDR_H_

class Xbee64Addr {
public:
	Xbee64Addr(){}
	Xbee64Addr(unsigned char msb, unsigned char secsb, unsigned char tirsb, unsigned char forsb,  unsigned char fivsb, unsigned char sixsb, unsigned char sevsb, unsigned char lsb){

		msb_ = msb;
		secsb_ = secsb;
		tirsb_ = tirsb;
		forsb_ = forsb;
		fivsb_ = fivsb;
		sixsb_ = sixsb;
		sevsb_ = sevsb;
		lsb_ = lsb;
	}
	virtual ~Xbee64Addr(){}

	unsigned char get_addr_sb(unsigned char index){

		if(index==1){
	     return msb_;
		}
		if(index==2){
			     return secsb_;
				}
		if(index==3){
			     return tirsb_;
				}
		if(index==4){
			     return forsb_;
				}
		if(index==5){
			     return fivsb_;
				}
		if(index==6){
			     return sixsb_;
				}
		if(index==7){
			     return sevsb_;
				}
		if(index==8){
			     return lsb_;
				}

		return msb_;
	}

private:
	unsigned char msb_;
	unsigned char secsb_;
	unsigned char tirsb_;
	unsigned char forsb_;
	unsigned char fivsb_;
	unsigned char sixsb_;
	unsigned char sevsb_;
	unsigned char lsb_;


};



#endif /* XBEE64ADDR_H_ */
