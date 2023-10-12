#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <nRF24L01RT.h>

// CONNOR W

class nRF24L01Transmitter{
    public:
    int CSN = 8;
    int CE = 7;
    int SCK = 52;
    int MOSI = 51;
    int MISO = 50;
    RF24 radio(CE,CSN);
    const byte address = "00001";
    void write(char text[]){
        radio.write(&text, sizeof(text));
    }
};
class nRF24L01Receiver{
    public:
    int CSN = 8;
    int CE = 7;
    int SCK = 52;
    int MOSI = 51;
    int MISO = 50;
    RF24 radio(CE,CSN);
    const byte address = "00001";
    void read(){
        char text[32] = "";
        radio.read(&text, sizeof(text));
        return text
    }
};
nRF24L01Transmitter Transmitter1;
nRF24L01Receiver Receiver1;
void setup(){
    Serial.begin(9600);
    Transmitter1.radio.begin();
    Transmitter1.radio.openWritingPipe(Transmitter1.address);
    Transmitter1.radio.setPALevel(RF24_PA_MIN);
    Transmitter1.radio.stopListening();
    Receiver1.radio.begin();
    Receiver1.radio.openReadingPipe(0,Receiver1.address);
    Receiver1.radio.setPALevel(RF24_PA_MIN);
    Receiver1.radio.startListening();
};
void loop(){
    Transmitter1.write("Hello");
    if (Receiver1.radio.available()){
        char text[32] = Receiver1.read();
        Serial.write(text);

    }
    delay(1000);
};
