// printsafe initial firmware

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Fingerprint.h>
#include <RTClib.h>
#include <Servo.h>
#include <SoftwareSerial.h>

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
SoftwareSerial fingerSerial(fingerTX, fingerRX);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);


//vars to be used for security
bool alarmactive=false;
bool fingerrec=false;
unsigned long dualpress=0;
bool dualpressactive=false;
int failedattempts=0;



//SETUP
void setup(){
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

    // fingerprint
    finger.begin(57600);
    if(finger.verifyPassword()){
        Serial.println("Found fingerprint sensor!");
    } else {
        Serial.println("Did not find fingerprint sensor :(");
        while (1)
        {delay(1);}
        
    }
    //start..
    initialmsg();
    readysnd();


}

void loop(){
    seethebuttonsfirst();
    //serial
    if (Serial.available()){
        char input=Serial.read();

        //authorized
        if(input=='1'){
            accessgranted();
        }
        // unauthorized
        else if(input=='0'){
            accessdenied();
        }

    } 
}

//button handler
void seethebuttonsfirst(){
      bool greenpressed= digitalRead(greenbtn)==LOW;
      bool redpressed= digitalRead(redbtn)==LOW;

      if(greenpressed && redpressed){
        if(!dualpressactive){
            dualpressactive=true;
            dualpress=millis();
      }
      //if pressed both for 5 secs fingerprint enroll active.
      if(dualpressactive && (millis()-dualpress>=5000)){
        dualpressactive=false;
        fingerenroll();
    }}
    else if(!greenpressed && !redpressed){
        dualpressactive=false;
    }

    // if only red pressed reset the alarm
    if(redpressed && alarmactive && !greenpressed){
        resetalarm();
    }
    // if only green pressed lock manually. 
    if(greenpressed && !redpressed && !dualpressactive){
        lockdoor();
        showmsg("DOOR LOCKED","MANUAL LOCK");
        delay(500);
    }
}






void accessgranted(){
    failedattempts=0;
    unlockdoor();

    digitalWrite(ledgreen, HIGH);
    digitalWrite(ledred, LOW);
    
    //beep success buzzer
    successbeep();

    //rtc set time
    DateTime now = rtc.now();

//oled display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(0,0);//changable
    display.println("ACCESS GRANTED");

    //show time and date
    display.setCursor(0,20);
    display.print(now.hour());
    display.print(":");
    display.print(now.minute());
    display.print(":");
    display.println(now.second());
    display.display();
    
    Serial.println("Access Granted for authorized person");

    delay(5000);
    digitalWrite(ledgreen, LOW);



}

void accessdenied(){
    failedattempts++;
    digitalWrite(ledred,HIGH);

    //BEEP WARNING BUZZER
    warningbeep();
    showmsg("ACCESS DENIED","UNAUTHORIZED");
    delay (1000);
    digitalWrite(ledred, LOW);

    //if failed attempts more than 3 activate emergency alarm
    if(failedattempts>=3){
        activatealarm();
    }
}

void fingerenroll(){
    fingerrec=true;
    
    // confirmation 2 beep
    digitalWrite(buzznormal, HIGH);
    delay(300);
    digitalWrite(buzznormal, LOW);
    delay(300);
    digitalWrite(buzznormal, HIGH);
    delay(300);
    digitalWrite(buzznormal, LOW);

    showmsg("ADMIN MODE","PLS PLACE FINGER");
    Serial.println("Place your finger on the sensor to enroll.");
    delay(3000);

    //enroll 
    fingerrec=false;

    showmsg("FINGERPRINT ENROLLED","SUCCESS");  

    successbeep();
}



void lockdoor(){
    // adjust servo angles accordingly
    servoup.write(0);
    servodown.write(0);

}
void unlockdoor(){
    // adjust servo angles accordingly
    servoup.write(90);
    servodown.write(90);
}


void successbeep(){
    digitalWrite(buzznormal,HIGH);
    delay(300);
    digitalWrite(buzznormal,LOW);
}
void warningbeep(){
    digitalWrite(buzzalarm,HIGH);
    delay(300);
    digitalWrite(buzzalarm,LOW);
}


void activatealarm(){
    alarmactive=true;
    showmsg("ALARM ACTIVATED","TAMPER ALERT!!");
    while(alarmactive){
        digitalWrite(ledred, HIGH);
        digitalWrite(buzzalarm, HIGH);
        delay(300);
        digitalWrite(ledred, LOW);
        digitalWrite(buzzalarm, LOW);
        delay(300);

        //reset thing
        if(digitalRead(redbtn)==LOW){
            resetalarm();
        }
    }
}
void resetalarm(){
    alarmactive=false;
    failedattempts=0;
    digitalWrite(ledred, LOW);
    digitalWrite(buzzalarm, LOW);

    showmsg("ALARM RESET","SYSTEM IS SAFE");

    successbeep();
    delay(1000);

}

void showmsg(String msg1, String msg2) {

  display.clearDisplay();    

  display.setTextSize(1); 
  display.setTextColor(WHITE);  
  display.setCursor(0, 15);      
  display.println(msg1);      

  display.setCursor(0, 35);
  display.println(msg2);

  display.display();            
}

void initialmsg(){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(5,10);
    display.println("PRINTSAFE");
    display.setTextSize(1);
    display.setCursor(5,40);
    display.println("Initializing...");
    display.display();
    delay(2000);
}

void readysnd()
{
    digitalWrite(buzznormal, HIGH);
    delay(150);
    digitalWrite(buzzalarm, HIGH);
    delay(150);
    digitalWrite(buzznormal, LOW);
    digitalWrite(buzzalarm, LOW);
}