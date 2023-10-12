// CONNOR WINDISH
// Module Requirements:
// 1. Imported Modules
// 2. Serial Connection (Temporay, needed for quick connect code)

// Imports
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <random>
#include <string.h>
#include <cstring.h>

// Guards
#pragma once

// Global
const byte[] address = {"00001","00002"};

// C++ Main
namespace nRF24L01RT {

    // Class for radio key control
    class nRF24L01Keys{
        public:
        char cnHeader = "_CNH:";
        void read(char str){
            char *token = strtok(str,":");
            return token[1]
        }
    };

    // Transmitter Class
    class nRF24L01Transmitter{
        public:
        int CSN = 8;
        int CE = 7;
        int SCK = 52;
        int MOSI = 51;
        int MISO = 50;
        RF24 radio(CE,CSN);
        const byte address = "00001";
        bool setupConnection = true;
        void init(){
            radio.begin();
            if (setupConnection){
                radio.openWritingPipe(address);
                radio.setPALevel(RF24_PA_MIN);
                radio.stopListening();
            };
        };
        void write(char text[]){
            radio.write(&text, sizeof(text));
        };
    };

    // Receiver Class
    class nRF24L01Receiver{
        public:
        int CSN = 8;
        int CE = 7;
        int SCK = 52;
        int MOSI = 51;
        int MISO = 50;
        RF24 radio(CE,CSN);
        byte address = "00001";
        bool setupConnection = true;
        void init(){
            radio.begin();
            if (setupConnection){
                radio.openReadingPipe(address);
                radio.setPALevel(RF24_PA_MIN);
                radio.startListening();
            }
        };
        void read(){
            char text[32] = "";
            radio.read(&text, sizeof(text));
            return text;
        };
    };

    // Quick Connect
    // Use nRF24L01Adress.generate() to generate the code, use nRF24L01Adress.send(class:transmitter) to send
    // Use nRF24L01Adress.lookUp(connectionNuber) to search for the code, do this before the code is sent
    class nRF24L01Adress{
        private:
        void print(char *text[]){
            try{
                Serial.print(text);
            }
        }
        public:
        int connectionNumber = 0;
        nRF24L01Keys Keys
        String cnk = Keys.cnHeader;
        int addresSize = sizeof(address);
        int iterateDelay = 10;
        void generate(){
            connectionNumber = rand();
            print(to_string(connectionNumber).c_str());
        };
        void send(nRF24L01Transmitter Transmitter){
            String message = cnk+to_string(connectionNumber);
            Transmitter.send(message.c_str());
        };
        void lookUp(int cn){
            int *keys[] = [];
            nRF24L01Receiver Receiver
            Receiver.setupConnection = false;
            Receiver.init();
            bool found = false;
            while (found == false){
                for (int i=0; i<addresSize, i++){
                const byte localAddress = address[i]
                Receiver1.radio.openReadingPipe(0,localAddress);
                Receiver1.radio.setPALevel(RF24_PA_MIN);
                Receiver1.radio.startListening();
                if (Receiver.radio.available()){;
                    char text[] = Receiver.read();
                    text = Keys.read(text);
                    if (text == cn){
                        try{
                            Serial.write("Connection Established");
                        }
                        found = true;
                        return localAddress
                    }
                };
            }
            }
        };
    };
}