#include <iostream>
// #include <nRF24L01.h>
#include <RF24.h>

using namespace std;

#define PIN_CE 17
#define PIN_CSN 0

int main() {

	RF24 radio(PIN_CE, PIN_CSN);
	radio.begin();

	// Checking for module support by the RF24 library (if connected correctly)
	if (radio.isPVariant()) {
		cout << "The module is supported" << endl;
		radio.printDetails(); 
	}
	else {
		cout << "Unknown module" << endl;
	}
}
