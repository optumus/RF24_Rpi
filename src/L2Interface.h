
#include <RF24/RF24.h> // SPI and work with GPIO (BCM numbering) are already implemented in the library

typedef struct
{
	uint8_t channel;
	rf24_pa_dbm_e PALevel;
	rf24_datarate_e dataRate;
	uint8_t child;
	uint64_t address;
	bool enableAutoACK;
}RF24_Init_S;

void L2_Initialise(RF24 *radioObj, RF24_Init_S *sRFInitData);

void L2_printRFDetails(RF24 *radioObj);

void L2_ReceiveMode(RF24 *radioObj);

bool L2_DataAvailable(RF24 *radioObj, uint8_t* pipe_num);

uint8_t L2_payLoadSize(RF24 *radioObj);

void L2_readData(RF24 *radioObj, void* buf, uint8_t len);

void L2_writeACKpayLoad(RF24 *radioObj, uint8_t pipe, const void* buf, uint8_t len);
