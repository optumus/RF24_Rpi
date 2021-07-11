/*
 * L2Msg.cpp
 *
 *  Created on: Jul 11, 2021
 *      Author: Ravi
 */

#include <string.h>
#include "L2Interface.h"
#include "L2Msg.h"

uint8_t L2TXMsgBuffer[L2_TX_MSG_BUFFER_SIZE] = {0};
uint8_t L2RXMsgBuffer[L2_RX_MSG_BUFFER_SIZE] = {0};

uint64_t TXAddress = 0x7878787878LL;
/**
 * @Description Construct heartbeat message which is to be sent periodically
 * @Returns the total bytes written in TX buffers
 **/
uint16_t ConstructL2Msg_HeartbeatStatus(void)
{
    uint16_t returnSize = 0;
    S_TIMESTAMP currentTimeStamp = {
        .YY = 63,
        .MO = 12,
        .DD = 31,
        .HH = 23,
        .MM = 59,
        .SS = 59
    };
    RTC_TMR_STRUCT currentTime;
	currentTimeStamp.YY = 2021;
	currentTimeStamp.MO = 07;
	currentTimeStamp.DD = 06;
	currentTimeStamp.HH = 05;
	currentTimeStamp.MM = 04;
	currentTimeStamp.SS = 03;
    returnSize = constructL2SendMessage(L2_MSG_HEARTBEAT,
    		(reinterpret_cast <uint8_t *> (&currentTimeStamp)),
            sizeof(S_TIMESTAMP));
    return returnSize;
}

/*
 * Construct L2 Send message
 * Returns the total bytes written in TX buffers
 */
uint16_t constructL2SendMessage(L2_MESSAGE_ID msgId, uint8_t *data, uint8_t dataSize)
{
    uint16_t dataByteCntr = 0;
    L2TXMsgBuffer[dataByteCntr] = msgId;
    dataByteCntr++;
    memcpy(&L2TXMsgBuffer[dataByteCntr], &TXAddress,
            sizeof(TXAddress));
    dataByteCntr += sizeof(TXAddress);
    memcpy(&L2TXMsgBuffer[dataByteCntr], data, dataSize);
    dataByteCntr += dataSize;

    return dataByteCntr;
}

//Send message
//receive message




