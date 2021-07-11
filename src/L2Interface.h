
#include <RF24/RF24.h> // SPI and work with GPIO (BCM numbering) are already implemented in the library

typedef struct
{
	uint8_t channel; // data transmission channel (from 0 to 125)
	rf24_pa_dbm_e PALevel; //signal gain level (RF24_PA_MIN = -18dBm, RF24_PA_LOW = -12dBm, RF24_PA_HIGH = -6dBm, RF24_PA_MAX = 0dBm)
	rf24_datarate_e dataRate; // data transfer rate (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Mbps
	uint8_t child; // there can be pipes 0 - 5 in total
	uint64_t RXaddress; //The pipe with the address
	bool enableAutoACK;
	uint8_t TXretryDelay;
	uint8_t TXretryCount;
	uint64_t TXaddress; //The pipe with the address
}RF24_Init_S;

class L2Interface
{
	//Attributes
	public:

	private:
		RF24 *L2radioObj;
		RF24_Init_S sRFInitData;
	protected:


	//Methods
	public:

		//Constructor
		L2Interface(RF24 *radioObj);

		//Distructor
		~L2Interface(void);

		void L2_Initialise(void);

		void L2_printRFDetails(void);

		void L2_ReceiveMode(void);

		bool L2_DataAvailable(uint8_t* pipe_num);

		uint8_t L2_payLoadSize(void);

		void L2_readData(void* buf, uint8_t len);

		void L2_writeACKpayLoad(uint8_t pipe, const void* buf, uint8_t len);

		void L2_setRetries(void);

		void L2_openWritingPipe(void);

		bool L2_writeData(const void* buf, uint8_t len);

		bool L2_isACKPayloadAvailable(void);

		bool L2_isRXFifoFull(void);

		uint8_t L2_flushRXBuffer(void);

	private:

	protected:

};
