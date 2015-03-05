/*
 * XbeeS1.cpp
 *
 *  Created on: 14/06/2014
 *      Author: Wellington
 */

#include "xbee_s1.h"

SoftwareSerial XbeeS1::software_serial_;
volatile char XbeeS1::data_index_;
volatile bool XbeeS1::is_escaped_;
volatile uint8_t XbeeS1::rx_checksum_;
volatile uint8_t XbeeS1::tx_checksum_;
int XbeeS1::message_size_;
volatile char XbeeS1::msb_;
volatile char XbeeS1::lsb_;
unsigned char XbeeS1::rx_api_frame_;
unsigned char XbeeS1::tx_status_;
bool XbeeS1::tx_ok_;
ringbuffer<char,16> XbeeS1::packet_buffer_;


XbeeS1::XbeeS1() {
    //TA0CCTL0 = CCIE;
    TA0CCR0 = 60;
    TA0CCTL0 = CCIE;
    TA0CTL = TASSEL_2 + MC_2 + ID_0;

    data_index_ = 0;
    is_escaped_ = false;
    rx_checksum_ = 0x0;
    tx_checksum_ = 0x0;
    message_size_ = 255;
    msb_ = 0;
    lsb_ = 0;
    tx_ok_ = false;
    rx_api_frame_ = 0x0;
    tx_status_ = 0x0;
    // TODO Auto-generated constructor stub
}

XbeeS1::~XbeeS1() {
    // TODO Auto-generated destructor stub
}

int XbeeS1::strlen(const char* word) {

    int word_lenght=0;

    unsigned char index=0;
    while(word[index]!=0) {
        word_lenght++;
        index++;
    }

    return word_lenght;
}





void XbeeS1::TxRequest64(Xbee64Addr addr, const char *payload) {

    int payloadsize = strlen(payload);

    while (!tx_ok_ ) {

        unsigned char byte = 0;
        tx_checksum_ = 0x0;
        //START DELIMITER
        XbeeSendByte(START_BYTE, false);
        //LENGTH
        XbeeSendByte((((3 + payloadsize + 8) >> 8) & 0xff), true);
        XbeeSendByte(((3+ payloadsize + 8) & 0xff), true);
        //API IDENTIFIER
        XbeeSendByte(TX_REQUEST_64, true);
        tx_checksum_ += TX_REQUEST_64;
        //FRAME ID
        XbeeSendByte(0x01, true);
        tx_checksum_ += 0x01;
        //DESTINATION ADRESS
        byte = addr.get_addr_sb(1);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(2);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(3);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(4);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(5);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(6);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(7);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(8);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;


        //OPTIONS
        XbeeSendByte(0x00, true);
        tx_checksum_ += 0x00;
        //RF DATA

        while (*payload) {
            byte = ((unsigned char) *payload);
            XbeeSendByte(byte, true);
            tx_checksum_ += byte;
            ++payload;
        }

        tx_checksum_ = 0xff - tx_checksum_;
        //CHECKSUM
        XbeeSendByte(tx_checksum_, true);
        QuaterMillisElapsed(400);
    }
    tx_ok_ = false;
}


void XbeeS1::TxATCommand(const char first_char, const char second_char) {

    int payloadsize = 2;

    while (!tx_ok_ ) {

        unsigned char byte = 0;
        tx_checksum_ = 0x0;
        //START DELIMITER
        XbeeSendByte(START_BYTE, false);
        //LENGTH
        XbeeSendByte((((3 + payloadsize ) >> 8) & 0xff), true);
        XbeeSendByte(((3+ payloadsize ) & 0xff), true);
        //API IDENTIFIER
        XbeeSendByte(AT_COMMAND, true);
        tx_checksum_ += AT_COMMAND;
        //FRAME ID
        XbeeSendByte(0x01, true);
        tx_checksum_ += 0x01;
        //AT COMMAND
        byte = first_char;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = second_char;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        tx_checksum_ = 0xff - tx_checksum_;
        //CHECKSUM
        XbeeSendByte(tx_checksum_, true);
        QuaterMillisElapsed(400);
    }
    tx_ok_ = false;
}

void XbeeS1::TxATCommand(const char first_char, const char second_char, const char* parameter) {

    int payloadsize = strlen(parameter) + 2;

    while (!tx_ok_ ) {

        unsigned char byte = 0;
        tx_checksum_ = 0x0;
        //START DELIMITER
        XbeeSendByte(START_BYTE, false);
        //LENGTH
        XbeeSendByte((((3 + payloadsize ) >> 8) & 0xff), true);
        XbeeSendByte(((3+ payloadsize ) & 0xff), true);
        //API IDENTIFIER
        XbeeSendByte(AT_COMMAND, true);
        tx_checksum_ += AT_COMMAND;
        //FRAME ID
        XbeeSendByte(0x01, true);
        tx_checksum_ += 0x01;
        //AT COMMAND
        byte = first_char;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = second_char;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;

        while (*parameter) {
            byte = ((unsigned char) *parameter);
            XbeeSendByte(byte, true);
            tx_checksum_ += byte;
            ++parameter;
        }

        tx_checksum_ = 0xff - tx_checksum_;
        //CHECKSUM
        XbeeSendByte(tx_checksum_, true);
        QuaterMillisElapsed(400);
    }
    tx_ok_ = false;
}

void XbeeS1::TxRemoteATCommand(Xbee64Addr addr, const char first_char, const char second_char) {

    int payloadsize = 2;

    while (!tx_ok_ ) {

        unsigned char byte = 0;
        tx_checksum_ = 0x0;
        //START DELIMITER
        XbeeSendByte(START_BYTE, false);
        //LENGTH
        XbeeSendByte((((3 + payloadsize + 10) >> 8) & 0xff), true);
        XbeeSendByte(((3+ payloadsize + 10) & 0xff), true);
        //API IDENTIFIER
        XbeeSendByte(REMOTE_AT_REQUEST, true);
        tx_checksum_ += REMOTE_AT_REQUEST;
        //FRAME ID
        XbeeSendByte(0x01, true);
        tx_checksum_ += 0x01;

        //64 DESTINATION ADRESS
        byte = addr.get_addr_sb(1);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(2);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(3);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(4);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(5);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(6);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(7);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(8);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;

        //16DESTINATION ADRESS
        byte = 0xFF;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte =0xFE;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;

        //OPTIONS
        XbeeSendByte(0x02, true);
        tx_checksum_ += 0x02;

        //AT COMMAND
        byte = first_char;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;

        byte = second_char;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;


        tx_checksum_ = 0xff - tx_checksum_;
        //CHECKSUM
        XbeeSendByte(tx_checksum_, true);
        QuaterMillisElapsed(400);
    }
    tx_ok_ = false;
}

void XbeeS1::TxRemoteATCommand(Xbee64Addr addr, const char first_char, const char second_char, const char* parameter) {

    int payloadsize = strlen(parameter) + 2;

    while (!tx_ok_ ) {

        unsigned char byte = 0;
        tx_checksum_ = 0x0;
        //START DELIMITER
        XbeeSendByte(START_BYTE, false);
        //LENGTH
        XbeeSendByte((((3 + payloadsize + 10) >> 8) & 0xff), true);
        XbeeSendByte(((3+ payloadsize + 10) & 0xff), true);
        //API IDENTIFIER
        XbeeSendByte(REMOTE_AT_REQUEST, true);
        tx_checksum_ += REMOTE_AT_REQUEST;
        //FRAME ID
        XbeeSendByte(0x01, true);
        tx_checksum_ += 0x01;

        //64 DESTINATION ADRESS
        byte = addr.get_addr_sb(1);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(2);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(3);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(4);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(5);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(6);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(7);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_addr_sb(8);
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;

        //16DESTINATION ADRESS
        byte = 0xFF;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte =0xFE;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;

        //OPTIONS
        XbeeSendByte(0x00, true);
        tx_checksum_ += 0x00;

        //AT COMMAND
        byte = first_char;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = second_char;
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;

        while (*parameter) {
            byte = ((unsigned char) *parameter);
            XbeeSendByte(byte, true);
            tx_checksum_ += byte;
            ++parameter;
        }


        tx_checksum_ = 0xff - tx_checksum_;
        //CHECKSUM
        XbeeSendByte(tx_checksum_, true);
        QuaterMillisElapsed(400);
    }
    tx_ok_ = false;
}

void XbeeS1::TxRequest16(Xbee16Addr addr, const char *payload) {

    int payloadsize = strlen(payload);

    while (!tx_ok_ ) {

        unsigned char byte = 0;
        tx_checksum_ = 0x0;
        //START DELIMITER
        XbeeSendByte(START_BYTE, false);
        //LENGTH
        XbeeSendByte((((3 + payloadsize + 2) >> 8) & 0xff), true);
        XbeeSendByte(((3+ payloadsize + 2) & 0xff), true);
        //API IDENTIFIER
        XbeeSendByte(TX_REQUEST_16, true);
        tx_checksum_ += TX_REQUEST_16;
        //FRAME ID
        XbeeSendByte(0x01, true);
        tx_checksum_ += 0x01;
        //DESTINATION ADRESS
        byte = addr.get_msb();
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        byte = addr.get_lsb();
        XbeeSendByte(byte, true);
        tx_checksum_ += byte;
        //OPTIONS
        XbeeSendByte(0x00, true);
        tx_checksum_ += 0x00;
        //RF DATA

        while (*payload) {
            byte = ((unsigned char) *payload);
            XbeeSendByte(byte, true);
            tx_checksum_ += byte;
            ++payload;
        }

        tx_checksum_ = 0xff - tx_checksum_;
        //CHECKSUM
        XbeeSendByte(tx_checksum_, true);
        QuaterMillisElapsed(400);
    }
    tx_ok_ = false;
}


void XbeeS1::XbeeSendByte(char byte, bool escape) {

    if (escape
            && (byte == START_BYTE || byte == ESCAPE || byte == XON
                || byte == XOFF)) {
        software_serial_.Transmit(ESCAPE);
        software_serial_.Transmit(byte ^ 0x20);
    } else {
        software_serial_.Transmit(byte);
    }

}


bool XbeeS1::get_tx_ok(void) {
    return false;
}
void XbeeS1::set_tx_ok(bool param) {
    //txOK = param;
}

bool XbeeS1::IsEmpty() {
    return packet_buffer_.empty();
}


void XbeeS1::GetRXPacket() {

    char buffer_char;

    while (!software_serial_.IsEmpty()) {
        buffer_char = software_serial_.Receive();

        if (buffer_char == ESCAPE && data_index_ > 0) {
            is_escaped_ = true;
        }
        if (is_escaped_) {
            buffer_char = buffer_char - 0x20;
            is_escaped_ = false;
        }

        switch(data_index_) {
        case 0:
            if (buffer_char == START_BYTE) {
                rx_checksum_ = 0x0;
                data_index_ = 0;
                message_size_ = 0;
                msb_ = 0;
                lsb_ = 0;
                data_index_++;
            }
            break;
        case 1:
            msb_ = buffer_char;
            data_index_++;
            break;
        case 2:
            lsb_ = buffer_char;
            message_size_ = (msb_ << 8) | lsb_;
            message_size_ = message_size_ + 0x03;//?
            data_index_++;
        case 3:
            if(buffer_char==RX_PACKET_16) {

                RED_LED_TOGGLE();
            }
            if(buffer_char==RX_PACKET_64) {

                RED_LED_TOGGLE();
            }
            if(buffer_char==AT_COMMAND_RESPONSE) {

                RED_LED_TOGGLE();
            }
            if(buffer_char==REMOTE_AT_RESPONSE) {

                RED_LED_TOGGLE();
            }
            if(buffer_char==TX_STATUS) {

                RED_LED_TOGGLE();
            }
            data_index_++;
            break;
        default:

        	if(data_index_ == message_size_){
        		//end of packet
                RED_LED_TOGGLE();

                rx_checksum_ = 0x0;
                data_index_ = 0;
                message_size_ = 0;
                msb_ = 0;
                lsb_ = 0;
        	}else{
                data_index_++;

        	}

        }










    }
}

/*
void XbeeS1::GetRXPacket() {

	unsigned char buffer_char;

	while (!software_serial_.empty()) {

		buffer_char = software_serial_.recv();

		if (buffer_char == ESCAPE) {
			is_escaped_ = true;
		}
		if (is_escaped_) {
			buffer_char = buffer_char - 0x20;
			is_escaped_ = false;
		}
		if (buffer_char == START_BYTE) {
			rx_checksum_ = 0x0;
			data_index_ = 0;
			message_size_ = 0;
			msb_ = 0;
			lsb_ = 0;
			data_index_++;
		} else {

			if (data_index_ == 1) {
				msb_ = buffer_char;

				//recievedMessage_[dataIndex] = ch;
			} else if (data_index_ == 2) {

				lsb_ = buffer_char;

				message_size_ = (msb_ << 8) | lsb_;
				message_size_ = message_size_ + 0x04;//?

				//recievedMessage_[dataIndex] = ch;

			} else if (data_index_ < message_size_ - 1 && data_index_ > 2) {

				//recievedMessage_[dataIndex] = ch;
				if (data_index_ == 3) {
					rx_api_frame_ = buffer_char;
				}
				if (rx_api_frame_ != 0x89) {

					packet_buffer_.push_back(buffer_char);
					RED_LED_TOGGLE();
				} else if (rx_api_frame_ == 0x89) {
					if (data_index_ == 5) {
						tx_status_ = buffer_char;
					}
				}

				rx_checksum_ = rx_checksum_ + buffer_char;

				//} else if (dataIndex < msgsize && dataIndex > 2) {
			} else if (data_index_ == (message_size_ - 1)) {

				//recievedMessage_[dataIndex] = ch;		//ultimo char
				rx_checksum_ = rx_checksum_ + buffer_char;

				//RED_LED_TOGGLE();

				if (rx_checksum_ == 0xFF) {
					//RED_LED_TOGGLE();
					if (rx_api_frame_ != 0x89) {
						//packetBuffer.push_back(packet);

					} else if (rx_api_frame_ == 0x89 && tx_status_ == 0x0) {
						tx_ok_ = true;
					}

					//hardUARTSendArray("Correct Checksum ", 17);
					//interpretPackage(recievedMessage_, message_size);
				} else {
					//hardUARTSendArray("Incorrect Checksum ", 19);
				}

			}

			data_index_++;
		}
	}
}
*/

#pragma vector=TIMER0_A0_VECTOR
__interrupt void XbeeS1::Timer0_A0(void) {
    XbeeS1::GetRXPacket();
}

