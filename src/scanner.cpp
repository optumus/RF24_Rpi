// ISM frequency range scanner (2400 MHz to 2527 MHz)
#include <iostream>
// #include <RF24/nRF24L01.h>
#include <RF24/RF24.h>
 
using namespace std;

#define PIN_CE 17
#define PIN_CSN 0
#define NUM_CHANNELS 126
 
uint8_t values[NUM_CHANNELS];
const int num_reps = 100;
 
int main() {

  RF24 radio(PIN_CE, PIN_CSN);
  radio.begin();
  radio.setAutoAck(false); // prohibiting automatic sending of acknowledgment packets for all pipes
 
  radio.startListening(); // enter in receiver mode
  radio.stopListening();
 
  radio.printDetails(); // config output
 
  // Top header output
  for (int i = 0; i < NUM_CHANNELS; ++i) {
    cout << hex << (i >> 4);
  }

  cout << endl;

  // Bottom header output
  for (int i = 0; i < NUM_CHANNELS; ++i) {
    cout << hex << (i & 0xf);
  }

  cout << endl;
 
  while (true) {

    memset(values, 0, sizeof(values)); // all channel values ​​are set to zero
 
    // Scan all channels num_reps
    for (int k = 0; k < num_reps; ++k) {
      for (int i = 0; i < NUM_CHANNELS; ++i) {

        radio.setChannel(i);
 
        radio.startListening();
        delayMicroseconds(130); // since the switching time between the module and the channels is 130 μs
        radio.stopListening();
 
        // Checking the presence of a carrier frequency on the selected channel (frequency)
        if (radio.testCarrier()) { 
          ++values[i];
        }
      }
    }
  
    // Printout of channel measurement in one hexadecimal digit
    for (int i = 0; i < NUM_CHANNELS; ++i) {
      cout << hex << min(0xf, (values[i] & 0xf));
    }
    cout << endl;
  }
  return 0;
}
