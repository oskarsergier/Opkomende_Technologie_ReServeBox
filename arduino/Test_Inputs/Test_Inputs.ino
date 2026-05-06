#include "SoftwareSerial.h"

#if defined(ARDUINO_ARCH_AVR)
#define SERIAL Serial
SoftwareSerial mySerial(2,3);
#define TRANS_SERIAL  mySerial
#elif defined(ARDUINO_ARCH_SAMD)
#define SERIAL SerialUSB
#define TRANS_SERIAL  Serial
#else

#endif


//RX=2,TX=3(D2) Software Serial Port

void setup() {
 TRANS_SERIAL.begin(9600); 

    SERIAL.begin(9600);  // start serial for output
    SERIAL.println("Version:v1.0");
}

void loop() {
    printData();
}

/*
* data mapping:E1---1；E2---2；E3---3；E4---4；E5---5；E6---6；
*              E7---7；E8---8；E9---9；EA---*；EB---0；EC---#；
*/
void printData() {
    while(TRANS_SERIAL.available()) {
        uint8_t data = TRANS_SERIAL.read();
        switch(data) {
                case 0xE1 :
                    SERIAL.println("1");
                    break;
                case 0xE2 :
                    SERIAL.println("2");
                    break;
                case 0xE3 :
                    SERIAL.println("3");
                    break;
                case 0xE4 :
                    SERIAL.println("4");
                    break;
                case 0xE5 :
                    SERIAL.println("5");
                    break;
                case 0xE6 :
                    SERIAL.println("6");
                    break;
                case 0xE7 :
                    SERIAL.println("7");
                    break;
                case 0xE8 :
                    SERIAL.println("8");
                    break;
                case 0xE9 :
                    SERIAL.println("9");
                    break;
                case 0xEA :
                    SERIAL.println("*");
                    break;
                case 0xEB :
                    SERIAL.println("0");
                    break;
                case 0xEC :
                    SERIAL.println("#");
                    break;
                default:
                    break;
            }
    }

}