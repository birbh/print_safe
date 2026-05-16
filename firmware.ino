// printsafe initial firmware

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Fingerprint.h>
#include <RTClib.h>
#include <Servo.h>


//oled set.
#define width 128
#define height 64

Adafruit_SSD1306 display(
    width,height,&Wire,-1
);

//rtc set.
RTC_DS3231 rtc;

//SERVO set.

Servo servoup;
Servo servodown;


//PINS.  
//leds pins.
const int ledgreen = 6;
const int ledred = 7;

//buzzers pins.
const int buzznormal = 8;
const int buzzalarm = 10;

//servos pins.
const int servoupPin = 9;
const int servodownPin = 11;

//pushbutton pins.
const int greenbtn = 2;
const int redbtn = 3;

//fingerprint set.
const int fingerTX = 4;
const int fingerRX = 5;




//SETUP
voit setup(){
    Serial.begin(9600);

    // pins
    pinMode(ledgreen, OUTPUT);
    pinMode(ledred, OUTPUT);

    pinMode(greenbtn, INPUT_PULLUP);
    pinMode(redbtn, INPUT_PULLUP);

    pinMode(buzznormal, OUTPUT);
    pinMode(buzzalarm, OUTPUT);

    // servos
    servoup.attach(servoupPin);
    servodown.attach(servodownPin);
//
    //oled
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
        {
             Serial.println(F("oled failed"));
             while(1);
        }
    //rtc
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }

    //start..
    


}