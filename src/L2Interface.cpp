#include <iostream>
//#include <RF24/nRF24L01.h>
#include <RF24/RF24.h> // SPI and work with GPIO (BCM numbering) are already implemented in the library
#include "L2Interface.h"

using namespace std;

#define PIN_CE 	17 // (chip enable)
#define PIN_CSN 0  // (chip select not)

uint8_t pipeNumber;
uint8_t payloadSize;

L2Interface::L2Interface(RF24 *radioObj)
{
	L2radioObj = radioObj;

	sRFInitData.channel = 5;// 5 - at a frequency of 2.405 GHz
	sRFInitData.PALevel = RF24_PA_HIGH;
	sRFInitData.dataRate = RF24_1MBPS;
	sRFInitData.child = 0;
	sRFInitData.RXaddress = 0x7878787878LL;
	sRFInitData.enableAutoACK = true;
	sRFInitData.TXretryDelay = 15; /*15 x 250us = 4000 us*/
	sRFInitData.TXretryCount = 15; /*retry for 15 times*/
	sRFInitData.TXaddress = 0x7878787878LL;
}

void L2Interface::L2_Initialise(void)
{
	L2radioObj->begin();
	L2radioObj->setChannel(sRFInitData.channel);
	L2radioObj->setPALevel(sRFInitData.PALevel);
	L2radioObj->setDataRate(sRFInitData.dataRate);
	L2radioObj->openReadingPipe(sRFInitData.child, sRFInitData.RXaddress);

	// we allow to place user data in the acknowledgment packet
	L2radioObj->enableAckPayload();

	// we allow sending to the transmitter a packet of acknowledgment of its data reception on all pipes (by default, true)
	L2radioObj->setAutoAck(sRFInitData.enableAutoACK);

	// allow dynamically re-sizable payload size on all pipes (max 32 bytes)
	L2radioObj->enableDynamicPayloads();
}

void L2Interface::L2_printRFDetails(void)
{
	L2radioObj->printDetails();
}

void L2Interface::L2_ReceiveMode(void)
{
	L2radioObj->startListening();
}

bool L2Interface::L2_DataAvailable(uint8_t* pipe_num)
{
	return(L2radioObj->available(pipe_num));
}

uint8_t L2Interface::L2_payLoadSize(void)
{
	return(L2radioObj->getDynamicPayloadSize());
}

void L2Interface::L2_readData(void* buf, uint8_t len)
{
	L2radioObj->read(buf, len);
}

void L2Interface::L2_writeACKpayLoad(uint8_t pipe, const void* buf, uint8_t len)
{
	L2radioObj->writeAckPayload(pipe, buf, len);
}

void L2Interface::L2_setRetries(void)
{
	L2radioObj->setRetries(sRFInitData.TXretryDelay, sRFInitData.TXretryCount);
}

void L2Interface::L2_openWritingPipe(void)
{
	L2radioObj->openWritingPipe(sRFInitData.TXaddress);
}

bool L2Interface::L2_writeData(const void* buf, uint8_t len)
{
	return(L2radioObj->write(buf, len));
}

bool L2Interface::L2_isACKPayloadAvailable(void)
{
	return(L2radioObj->isAckPayloadAvailable());
}

bool L2Interface::L2_isRXFifoFull(void)
{
	return(L2radioObj->rxFifoFull());
}

uint8_t L2Interface::L2_flushRXBuffer(void)
{
	return(L2radioObj->flush_rx());
}

int RX_Task() {
	RF24 radio(PIN_CE, PIN_CSN); // create a radio object

	L2Interface L2Comm(&radio);

	L2Comm.L2_Initialise();

	// module configuration output
	L2Comm.L2_printRFDetails();

	// turn on the receiver, start listening to open pipes
	L2Comm.L2_ReceiveMode();

	cout << "Start listening..." << endl;

  while (true) {

    // If there is received data in the buffer, then we transfer the address of the variable (must be of the uint8_t type)
	// where you want to put the pipe number on which the data was received
    if (L2Comm.L2_DataAvailable(&pipeNumber)) {

      payloadSize = L2Comm.L2_payLoadSize(); // get the size of the received payload

      char payload[payloadSize];
      string receivedData;

      // We read the received data into the payload array specifying the size of this array in bytes
      L2Comm.L2_readData(&payload, payloadSize);

      for (uint8_t i = 0; i < payloadSize; i++) {
        receivedData += payload[i];
      }

      cout << "Pipe number : " << (int) pipeNumber << " ";
      cout << "Payload size : " << (int) payloadSize << " ";
      cout << "Data: " << receivedData << endl;

      char ackData[] = "Data from buffer";

      // We put the data into the FIFO buffer. As soon as the packet is received, the data from the buffer
      // will be sent to this transmitter along with an acknowledgment packet of its data
      L2Comm.L2_writeACKpayLoad(pipeNumber, &ackData, sizeof(ackData));
    }
  }
  return 0;
}

int TX_Task() {

  RF24 radio(PIN_CE, PIN_CSN); // create a radio object

  L2Interface L2Comm(&radio);

  L2Comm.L2_Initialise();

  	// module configuration output
  L2Comm.L2_printRFDetails();

  // If the transmitter has not received a response from the receiver, then it will retry sending data.
  // Wait between each retry, in multiples of 250,
  // the maximum is 15.0 means 250 μs, (15 * 250) +250 = 4000 μs,
  // and the number of attempts before surrender, maximum 15
  // the method is only available for the transmitter
  L2Comm.L2_setRetries();

  // open a pipe with a unique ID (only one pipe can be opened at a time for data transfer)
  L2Comm.L2_openWritingPipe();

  // payload block can be up to 32 bytes
  char text[] = "Hello world!";
  char ackData[24];

  while (true)
  {

    // By default, the transmitter asks the receiver for confirmation of receipt of data,
    // and the receiver, having received the data and checking the CRC, returns an acknowledgment packet to the sender.

    // Pass the address of the variable and its size in bytes, the value of which will be used as payload
    // And check for a returned data receipt packet
    if (L2Comm.L2_writeData(&text, sizeof(text)))
    {
      cout << "Delivered " << (int) sizeof(text) << " byte" << endl;
    }
    else
    {
      cout << "Data not delivered" << endl; // transmitter data was not received or received with a CRC error
    }

    // If the buffer contains received data from the acknowledgment packet
    if (L2Comm.L2_isACKPayloadAvailable())
    {
		// read data from the buffer into the ackData array indicating how many bytes can fit into the array
    	L2Comm.L2_readData(&ackData, sizeof(ackData));
		string FIFO;
		for (uint8_t i = 0; i < sizeof(ackData); i++)
		{
			FIFO += ackData[i];
		}

		// If all three FIFO buffers are full then clear
		if (L2Comm.L2_isRXFifoFull()) {
			cout << "Buffer full" << endl;
			L2Comm.L2_flushRXBuffer(); // clear buffer
		}
    }

    delay(1000);
  }

  return 0;
}

int main()
{
	TX_Task();
	RX_Task();

	return 0;
}
