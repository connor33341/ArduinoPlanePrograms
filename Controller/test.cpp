// Connor Windish
// Project: Applied Tech, Rc Airplane
// Purpose: Wireless Communication Control

#include "nRF24L01RT.h"

using namespace nRF24L01RT

nRF24L01Receiver Receiver1;
nRF24L01Transmitter Transmitter1;

void setup(){
    Receiver1.init();
    Transmitter1.init();
}
void loop(){
    Transmitter1.write("Hello");
    if (Receiver1.radio.available()){
        char text[32] = Receiver1.read();
        Serial.write(text);

    }
    delay(1000);
}

