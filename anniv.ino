#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "RTClib.h"

Adafruit_AlphaNum4 top = Adafruit_AlphaNum4();
Adafruit_AlphaNum4 mid1 = Adafruit_AlphaNum4();
Adafruit_AlphaNum4 mid2 = Adafruit_AlphaNum4();
Adafruit_AlphaNum4 bot = Adafruit_AlphaNum4();
RTC_PCF8523 rtc;

void setup() {
  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
  top.begin(0x70);  // pass in the address
  mid1.begin(0x71);  // pass in the address
  mid2.begin(0x72);  // pass in the address
  bot.begin(0x74);  // pass in the address

  
}

char numDays[4] = {'1', ' ', ' ', ' '};
char temp;
int annivDays;
int curYear;
char yrsTogC[4];
char annivDaysC[4];

void loop() {
  DateTime now = rtc.now();
  //unixtime is seconds since Jan 1st, 1970. Nov 16th 2017 is 17,486 days later
  annivDays = (now.unixtime()/86400) - 17486;
  String numDays = String(annivDays);
  numDays.toCharArray(annivDaysC,4);
  //if (int(annivDaysC[3]) == 0){annivDaysC[3] =' ';}
  
  if (now.month() == 11 && now.day() == 16){
    curYear = now.year();
    int yearsTog = curYear - 2017;
    String yrsTogS = String(yearsTog);
    yrsTogS.toCharArray(yrsTogC,4);
    
    top.writeDigitAscii(0, ' ');
    top.writeDigitAscii(1, ' ');
    top.writeDigitAscii(2, ' ');
    top.writeDigitAscii(3, 'I');

    mid1.writeDigitAscii(0, 'L');
    mid1.writeDigitAscii(1, 'O');
    mid1.writeDigitAscii(2, 'V');
    mid1.writeDigitAscii(3, 'E');

    mid2.writeDigitAscii(0, ' ');
    mid2.writeDigitAscii(1, 'Y');
    mid2.writeDigitAscii(2, 'O');
    mid2.writeDigitAscii(3, 'U');

    bot.writeDigitAscii(0, yrsTogC[0]);
    bot.writeDigitAscii(1, 'Y');
    bot.writeDigitAscii(2, 'R');
    bot.writeDigitAscii(3, 'S');
    
    top.writeDisplay();
    mid1.writeDisplay();
    mid2.writeDisplay();
    bot.writeDisplay();
  }
  else{
    top.writeDigitAscii(0, 'D');
    top.writeDigitAscii(1, 'A');
    top.writeDigitAscii(2, 'Y');
    top.writeDigitAscii(3, 'S');

    mid1.writeDigitAscii(0, 'T');
    mid1.writeDigitAscii(1, 'O');
    mid1.writeDigitAscii(2, 'G');
    mid1.writeDigitAscii(3, 'E');

    mid2.writeDigitAscii(0, 'T');
    mid2.writeDigitAscii(1, 'H');
    mid2.writeDigitAscii(2, 'E');
    mid2.writeDigitAscii(3, 'R');
   
    bot.writeDigitAscii(0, numDays[0]);
    bot.writeDigitAscii(1, numDays[1]);
    bot.writeDigitAscii(2, numDays[2]);
    bot.writeDigitAscii(3, numDays[3]);
    
    top.writeDisplay();
    mid1.writeDisplay();
    mid2.writeDisplay();
    bot.writeDisplay();
    
   /*
    temp = numDays[0];
    numDays[0] = numDays[1];
    numDays[1] = numDays[2];
    numDays[2] = numDays[3];
    numDays[3] = temp;
    */
  }
  
    delay(300);
}
