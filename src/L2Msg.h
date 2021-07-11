/*
 * L2Msg.h
 *
 *  Created on: Jul 11, 2021
 *      Author: Ravi
 */

#ifndef RF24_RPI_SRC_L2MSG_H_
#define RF24_RPI_SRC_L2MSG_H_

#include <iostream>



#define L2_TX_MSG_BUFFER_SIZE   32u
#define L2_RX_MSG_BUFFER_SIZE   32u

typedef struct
{
    uint8_t YY : 6; //    Year bits - 21 to 63 - 6 bits
    uint8_t MO : 4; //    Month - 1 to 12  - 4 bits
    uint8_t DD : 5; // - 1 to 31  - 5 bits
    uint8_t HH : 5; //- 0 to 24  - 5 bits
    uint8_t MM : 6; //- 0 to 59  - 6 bits
    uint8_t SS : 6; //- 0 to 59  - 6 bits
}S_TIMESTAMP;

typedef enum
{
    L2_MSG_HEARTBEAT = 0X351,
    L2_MSG_SET_DO = 0X352,
    L2_MSG_GET_DI = 0X353,
    L2_MSG_SET_DO_TMR = 0X00,

    L2_MSG_MAX

}L2_MESSAGE_ID;

typedef struct
	{	/* date and time components */
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	}RTC_TMR_STRUCT;

bool constructL2SendMessage(L2_MESSAGE_ID msgId, uint8_t *data, uint8_t dataSize);

uint8_t ConstructL2Msg_HeartbeatStatus(void);




#endif /* RF24_RPI_SRC_L2MSG_H_ */
