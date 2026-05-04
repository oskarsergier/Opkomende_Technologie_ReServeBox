
// Library voor grove lcd
#include<Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

// library voor keypad
#include "SoftwareSerial.h"

#if defined(ARDUINO_ARCH_AVR)
#define SERIAL Serial
SoftwareSerial mySerial(2,3);
#define TRANS_SERIAL mySerial
#elif defined(ARDUINO_ARCH_SAMD)
#define SERIAL SerialUSB
#define TRANS_SERIAL  Serial
#endif

// INSTELLINGEN
String inputCode = "";
const int codeLength = 6;

// Voorbeeldcodes 
String locker1Code = "589647";
String locker2Code = "784265";
String locker3Code = "558211";
String locker4Code = "796146";
String locker5Code = "546281";
String locker6Code = "315849";

// Pins voor lockers 
const int locker1Pin = 4;
const int locker2Pin = 5;
const int locker3Pin = 6;
const int locker4Pin = 7;
const int locker5Pin = 8;
const int locker6Pin = 9;

// Blokkeer systeem
int fouten = 0;
bool blokkeer = false;
unsigned long startBlokkeer = 0;
const unsigned long blokkeerTijd = 180000; // 3 minuten wachten

void setup() {
// Lockerpin definiëren + laag zetten
  pinMode(locker1Pin, OUTPUT);
  pinMode(locker2Pin, OUTPUT);
  pinMode(locker3Pin, OUTPUT);
  pinMode(locker4Pin, OUTPUT);
  pinMode(locker5Pin, OUTPUT);
  pinMode(locker6Pin, OUTPUT);

  digitalWrite(locker1Pin, LOW);
  digitalWrite(locker2Pin, LOW);
  digitalWrite(locker3Pin, LOW);
  digitalWrite(locker4Pin, LOW);
  digitalWrite(locker5Pin, LOW);
  digitalWrite(locker6Pin, LOW);

// LCD starten 16x2
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.setCursor(0,0);
  lcd.print("Voer code in:");
  
// Seriële monitor starten
  TRANS_SERIAL.begin(9600);
  SERIAL.begin(9600);
  SERIAL.println("ReServeBox systeem gestart");

}

void loop() {
  // Controle indien geblokeerd
  if (blokkeer){
    unsigned long gelopenTijd = millis() - startBlokkeer;

    if (gelopenTijd >= blokkeerTijd){
      blokkeer = false;
      fouten = 0;

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Voer code in:");
    }
    else {
      // tijd weergeven
      unsigned long rest = (blokkeerTijd - gelopenTijd) / 1000;
      lcd.setCursor(0,1);
      lcd.print("Wacht: ");
      lcd.print(rest);
      lcd.print("s  ");

      return;
    }
  }

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
        // scherm resetten en weergeven "code gewist!"     
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Code gewist!");
        delay (2000);
        // scherm resetten om code nadien opnieuw in te voeren.
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Voer code in:");
      }
      else {
        if(inputCode.length() < codeLength) {
          inputCode += key;

          lcd.setCursor(0,1);
          lcd.print(inputCode);
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

  // code moet 6 cijfers zijn
  if(inputCode.length() != codeLength) {
    SERIAL.println("Code moet 6 cijfers zijn!");
  }
// Correcte locker openen
  else if(inputCode == locker1Code) {
    fouten = 0;
    openLocker(locker1Pin);
  }
  else if(inputCode == locker2Code) {
    fouten = 0;
    openLocker(locker2Pin);
  }
  else if(inputCode == locker3Code) {
    fouten = 0;
    openLocker(locker3Pin);
  }
  else if(inputCode == locker4Code) {
    fouten = 0;
    openLocker(locker4Pin);
  }
  else if(inputCode == locker5Code) {
    fouten = 0;
    openLocker(locker5Pin);
  }
  else if(inputCode == locker6Code) {
    fouten = 0;
    openLocker(locker6Pin);
  }

  else {
  // foute code
    SERIAL.println("FOUTE CODE");
    fouten++;
    // foute code projecteren op display
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Foute code!");
    delay(2000);

    if (fouten >= 3){
      blokkeer = true;
      startBlokkeer = millis();

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Geblokkeerd!");
      lcd.setCursor(0,1);
      lcd.print("3 min wachten");
    }
    else {
      // reset van display
     lcd.clear();
     lcd.setCursor(0,0);
      lcd.print("Voer code in:");      
    }
  }

  inputCode = ""; // reset na controle
}

void openLocker(int lockerPin) {
// locker openen
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Locker opent!");
  delay(3000);                // laat tekst 3 seconden staan
  digitalWrite(lockerPin, HIGH);
  delay(3000);                // 3 seconden open

// locker sluiten
  digitalWrite(lockerPin, LOW);
  
// display resetten
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Voer code in:");
}