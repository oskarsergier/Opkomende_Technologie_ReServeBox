#include "SoftwareSerial.h"

#if defined(ARDUINO_ARCH_AVR)
#define SERIAL Serial
SoftwareSerial mySerial(2,3);
#define TRANS_SERIAL  mySerial
#elif defined(ARDUINO_ARCH_SAMD)
#define SERIAL SerialUSB
#define TRANS_SERIAL  Serial
#endif

// ====== INSTELLINGEN ======
String inputCode = "";
const int codeLength = 6;

// Voorbeeldcodes (later kan je dit dynamisch maken via app)
String locker1Code = "123456";
String locker2Code = "654321";

// Pins voor lockers (relais of servo)
const int locker1Pin = 8;
const int locker2Pin = 9;

void setup() {

  pinMode(locker1Pin, OUTPUT);
  pinMode(locker2Pin, OUTPUT);
  digitalWrite(locker1Pin, LOW);
  digitalWrite(locker2Pin, LOW);

  TRANS_SERIAL.begin(9600);
  SERIAL.begin(9600);
  SERIAL.println("ReServeBox systeem gestart");
}

void loop() {
  readKeypad();
}

void readKeypad() {
  while(TRANS_SERIAL.available()) {
    uint8_t data = TRANS_SERIAL.read();
    char key = mapKey(data);

    if(key != '\0') {
      SERIAL.print("Toets: ");
      SERIAL.println(key);

      if(key == '#') {
        checkCode();
      }
      else if(key == '*') {
        inputCode = "";  // reset bij *
        SERIAL.println("Invoer gewist");
      }
      else {
        if(inputCode.length() < codeLength) {
          inputCode += key;
        }
      }
    }
  }
}

char mapKey(uint8_t data) {
  switch(data) {
    case 0xE1: return '1';
    case 0xE2: return '2';
    case 0xE3: return '3';
    case 0xE4: return '4';
    case 0xE5: return '5';
    case 0xE6: return '6';
    case 0xE7: return '7';
    case 0xE8: return '8';
    case 0xE9: return '9';
    case 0xEA: return '*';
    case 0xEB: return '0';
    case 0xEC: return '#';
    default: return '\0';
  }
}

void checkCode() {

  SERIAL.print("Ingevoerde code: ");
  SERIAL.println(inputCode);

  if(inputCode.length() != codeLength) {
    SERIAL.println("Code moet 6 cijfers zijn!");
  }
  else if(inputCode == locker1Code) {
    openLocker(locker1Pin);
  }
  else if(inputCode == locker2Code) {
    openLocker(locker2Pin);
  }
  else {
    SERIAL.println("FOUTE CODE");
  }

  inputCode = ""; // reset na controle
}

void openLocker(int lockerPin) {

  SERIAL.println("Locker x opent!");
  digitalWrite(lockerPin, HIGH);
  delay(3000);                // 3 seconden open
  digitalWrite(lockerPin, LOW);
  SERIAL.println("Locker x gesloten");
}