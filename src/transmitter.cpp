#include <iostream>
//#include <RF24/nRF24L01.h>
#include <RF24/RF24.h> // SPI and work with GPIO (BCM numbering) are already implemented in the library

using namespace std;

#define PIN_CE 17 // (chip enable)
#define PIN_CSN 0 // (chip select not)

int main() {
  
  RF24 radio(PIN_CE, PIN_CSN); // create a radio object
  radio.begin();
  // data transmission channel (from 0 to 125), 5 - at a frequency of 2.405 GHz
  radio.setChannel(5);
  // transmitter gain level (RF24_PA_MIN = -18dBm, RF24_PA_LOW = -12dBm, RF24_PA_HIGH = -6dBm, RF24_PA_MAX = 0dBm)
  radio.setPALevel(RF24_PA_HIGH);
  // data transfer rate (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Mbps
  radio.setDataRate(RF24_1MBPS);
  // enable the receipt of the acknowledgment packet (true by default)
  radio.setAutoAck(true);
  // enable dynamically resizable payload block size
  radio.enableDynamicPayloads();
  
  // If the transmitter has not received a response from the receiver, then it will retry sending data.
  // Wait between each retry, in multiples of 250,
  // the maximum is 15.0 means 250 μs, (15 * 250) +250 = 4000 μs,
  // and the number of attempts before surrender, maximum 15
  radio.setRetries(15, 15); // the method is only available for the transmitter

  // open a pipe with a unique ID (only one pipe can be opened at a time for data transfer)
  radio.openWritingPipe(0x7878787878LL);

  // payload block can be up to 32 bytes
  char text[] = "Hello world!";
  char ackData[24];

  while (true) {

    // By default, the transmitter asks the receiver for confirmation of receipt of data,
    // and the receiver, having received the data and checking the CRC, returns an acknowledgment packet to the sender.
    
    // Pass the address of the variable and its size in bytes, the value of which will be used as payload
    // And check for a returned data receipt packet
    if (radio.write(&text, sizeof(text))) {
      cout << "Delivered " << (int) sizeof(text) << " byte" << endl;
    }
    else {
      cout << "Data not delivered" << endl; // transmitter data was not received or received with a CRC error
    }

    // If the buffer contains received data from the acknowledgment packet
    if (radio.isAckPayloadAvailable()) {
      // read data from the buffer into the ackData array indicating how many bytes can fit into the array
      radio.read(&ackData, sizeof(ackData));
      string FIFO;
      for (uint8_t i = 0; i < sizeof(ackData); i++) {
        FIFO += ackData[i];
      }
      //Serial.println(FIFO);

      // If all three FIFO buffers are full then clear
      if (radio.rxFifoFull()) {
        cout << "Buffer full" << endl;
        radio.flush_rx(); // clear buffer
      }
    }  

    delay(1000);
  }

}

