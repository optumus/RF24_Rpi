#include <iostream>
//#include <RF24/nRF24L01.h>
#include <RF24/RF24.h> // SPI and work with GPIO (BCM numbering) are already implemented in the library
#include "L2Interface.h"

using namespace std;

#define PIN_CE 17 // (chip enable)
#define PIN_CSN 0 // (chip select not)

uint8_t pipeNumber;
uint8_t payloadSize;
uint64_t TXaddress = 0x7878787878LL;

RF24_Init_S sRFInitData =
{
	.channel = 5,
	.PALevel = RF24_PA_HIGH,
	.dataRate = RF24_1MBPS,
	.child = 0,
	.address = 0x7878787878LL,
	.enableAutoACK = true,
	.TXretryDelay = 15, /*15 x 250us = 4000 us*/
	.TXretryCount = 15 /*retry for 15 times*/
};

void L2_Initialise(RF24 *radioObj, RF24_Init_S *sRFInitData)
{
	radioObj->begin();
	// data transmission channel (from 0 to 125), 5 - at a frequency of 2.405 GHz
	radioObj->setChannel(sRFInitData->channel);
	// signal gain level (RF24_PA_MIN = -18dBm, RF24_PA_LOW = -12dBm, RF24_PA_HIGH = -6dBm, RF24_PA_MAX = 0dBm)
	radioObj->setPALevel(sRFInitData->PALevel);
	// data transfer rate (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Mbps
	radioObj->setDataRate(sRFInitData->dataRate);
	// open the pipe with the address 0x7878787878LL to receive data (there can be pipes 0 - 5 in total)
	radioObj->openReadingPipe(sRFInitData->child, sRFInitData->address);

	// we allow to place user data in the acknowledgment packet
	radioObj->enableAckPayload();

	// we allow sending to the transmitter a packet of acknowledgment of its data reception on all pipes (by default, true)
	radioObj->setAutoAck(sRFInitData->enableAutoACK);

	// allow dynamically re-sizable payload size on all pipes (max 32 bytes)
	radioObj->enableDynamicPayloads();
}

void L2_printRFDetails(RF24 *radioObj)
{
	radioObj->printDetails();
}

void L2_ReceiveMode(RF24 *radioObj)
{
	radioObj->startListening();
}

bool L2_DataAvailable(RF24 *radioObj, uint8_t* pipe_num)
{
	return(radioObj->available(pipe_num));
}

uint8_t L2_payLoadSize(RF24 *radioObj)
{
	return(radioObj->getDynamicPayloadSize());
}

void L2_readData(RF24 *radioObj, void* buf, uint8_t len)
{
	radioObj->read(buf, len);
}

void L2_writeACKpayLoad(RF24 *radioObj, uint8_t pipe, const void* buf, uint8_t len)
{
	radioObj->writeAckPayload(pipe, buf, len);
}

void L2_setRetries(RF24 *radioObj, uint8_t delay, uint8_t count)
{
	radioObj->setRetries(delay, count);
}

void L2_openWritingPipe(RF24 *radioObj, uint64_t address)
{
	radioObj->openWritingPipe(address);
}

bool L2_writeData(RF24 *radioObj, const void* buf, uint8_t len)
{
	return(radioObj->write(buf, len));
}

bool L2_isACKPayloadAvailable(RF24 *radioObj)
{
	return(radioObj->isAckPayloadAvailable());
}

bool L2_isRXFifoFull(RF24 *radioObj)
{
	return(radioObj->rxFifoFull());
}

uint8_t L2_flushRXBuffer(RF24 *radioObj)
{
	return(radioObj->flush_rx());
}

//int main() {
//	RF24 radio(PIN_CE, PIN_CSN); // create a radio object
//
//	L2_Initialise(&radio, &sRFInitData);
//
//	// module configuration output
//	L2_printRFDetails(&radio);
//
//	// turn on the receiver, start listening to open pipes
//	L2_ReceiveMode(&radio);
//
//	cout << "Start listening..." << endl;
//
//  while (true) {
//
//    // If there is received data in the buffer, then we transfer the address of the variable (must be of the uint8_t type)
//	// where you want to put the pipe number on which the data was received
//    if (L2_DataAvailable(&radio, &pipeNumber)) {
//
//      payloadSize = L2_payLoadSize(&radio); // get the size of the received payload
//
//      char payload[payloadSize];
//      string receivedData;
//
//      // We read the received data into the payload array specifying the size of this array in bytes
//      L2_readData(&radio, &payload, payloadSize);
//
//      for (uint8_t i = 0; i < payloadSize; i++) {
//        receivedData += payload[i];
//      }
//
//      cout << "Pipe number : " << (int) pipeNumber << " ";
//      cout << "Payload size : " << (int) payloadSize << " ";
//      cout << "Data: " << receivedData << endl;
//
//      char ackData[] = "Data from buffer";
//
//      // We put the data into the FIFO buffer. As soon as the packet is received, the data from the buffer
//      // will be sent to this transmitter along with an acknowledgment packet of its data
//      L2_writeACKpayLoad(&radio, pipeNumber, &ackData, sizeof(ackData));
//    }
//  }
//  return 0;
//}

int main() {

  RF24 radio(PIN_CE, PIN_CSN); // create a radio object

  // If the transmitter has not received a response from the receiver, then it will retry sending data.
  // Wait between each retry, in multiples of 250,
  // the maximum is 15.0 means 250 μs, (15 * 250) +250 = 4000 μs,
  // and the number of attempts before surrender, maximum 15
  // the method is only available for the transmitter
  L2_setRetries(&radio, sRFInitData.TXretryDelay, sRFInitData.TXretryCount);

  // open a pipe with a unique ID (only one pipe can be opened at a time for data transfer)
  L2_openWritingPipe(&radio, TXaddress);
  // payload block can be up to 32 bytes
  char text[] = "Hello world!";
  char ackData[24];

  while (true) {

    // By default, the transmitter asks the receiver for confirmation of receipt of data,
    // and the receiver, having received the data and checking the CRC, returns an acknowledgment packet to the sender.

    // Pass the address of the variable and its size in bytes, the value of which will be used as payload
    // And check for a returned data receipt packet
    if (L2_writeData(&radio, &text, sizeof(text)))
    {
      cout << "Delivered " << (int) sizeof(text) << " byte" << endl;
    }
    else
    {
      cout << "Data not delivered" << endl; // transmitter data was not received or received with a CRC error
    }

    // If the buffer contains received data from the acknowledgment packet
    if (L2_isACKPayloadAvailable(&radio))
    {
		// read data from the buffer into the ackData array indicating how many bytes can fit into the array
		L2_readData(&radio, &ackData, sizeof(ackData));
		string FIFO;
		for (uint8_t i = 0; i < sizeof(ackData); i++)
		{
			FIFO += ackData[i];
		}
		//Serial.println(FIFO);

		// If all three FIFO buffers are full then clear
		if (L2_isRXFifoFull(&radio)) {
			cout << "Buffer full" << endl;
			L2_flushRXBuffer(&radio); // clear buffer
		}
    }

    delay(1000);
  }

}
