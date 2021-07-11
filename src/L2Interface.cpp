#include <iostream>
//#include <RF24/nRF24L01.h>
#include <RF24/RF24.h> // SPI and work with GPIO (BCM numbering) are already implemented in the library
#include "L2Interface.h"

using namespace std;

#define PIN_CE 17 // (chip enable)
#define PIN_CSN 0 // (chip select not)

uint8_t pipeNumber;
uint8_t payloadSize;

RF24_Init_S sRFInitData =
{
	.channel = 5,
	.PALevel = RF24_PA_HIGH,
	.dataRate = RF24_1MBPS,
	.child = 0,
	.address = 0x7878787878LL,
	.enableAutoACK = true
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

int main() {
	RF24 radio(PIN_CE, PIN_CSN); // create a radio object

	L2_Initialise(&radio, &sRFInitData);

	// module configuration output
	L2_printRFDetails(&radio);

	// turn on the receiver, start listening to open pipes
	L2_ReceiveMode(&radio);

	cout << "Start listening..." << endl;

  while (true) {

    // If there is received data in the buffer, then we transfer the address of the variable (must be of the uint8_t type)
	// where you want to put the pipe number on which the data was received
    if (L2_DataAvailable(&radio, &pipeNumber)) {

      payloadSize = L2_payLoadSize(&radio); // get the size of the received payload

      char payload[payloadSize];
      string receivedData;

      // We read the received data into the payload array specifying the size of this array in bytes
      L2_readData(&radio, &payload, payloadSize);

      for (uint8_t i = 0; i < payloadSize; i++) {
        receivedData += payload[i];
      }

      cout << "Pipe number : " << (int) pipeNumber << " ";
      cout << "Payload size : " << (int) payloadSize << " ";
      cout << "Data: " << receivedData << endl;

      char ackData[] = "Data from buffer";

      // We put the data into the FIFO buffer. As soon as the packet is received, the data from the buffer
      // will be sent to this transmitter along with an acknowledgment packet of its data
      L2_writeACKpayLoad(&radio, pipeNumber, &ackData, sizeof(ackData));
    }
  }
  return 0;
}
