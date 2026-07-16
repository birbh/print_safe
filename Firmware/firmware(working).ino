#include <Servo.h>
#include <Adafruit_Fingerprint.h>
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- OLED Screen Configuration ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Verified Pin Allocations ---
const int greenBtnPin = 4;    // Green Button: Manual Lock / Admin Combo
const int redBtnPin = 5;      // Red Button: Hidden Alarm Reset / Admin Combo
const int greenLedPin = 6;
const int redLedPin = 7;
const int buzzerAPin = 8;     
const int servoupPin = 9;     
const int buzzerBPin = 10;    
const int servodownPin = 11;   

// --- Object Initializations ---
Servo servoup;
Servo servodown;
RTC_DS3231 rtc;

// Fingerprint Sensor Serial Configuration
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// --- Global System State Variables ---
int failedAttempts = 0;
const int maxFailedAttempts = 3;
const int stepDelay = 15; 

bool isLocked = true;          // Tracks the physical lock status of the vault
bool systemBlock = false;       // Hardlock flag when tamper alarm is tripped
unsigned long unlockTime = 0;  // Tracks auto-relock window countdowns
const unsigned long autoLockDelay = 30000; // 30 seconds lock window

void setup() {
  Serial.begin(9600);
  delay(500); 
  Serial.println(F("\n============================================="));
  Serial.println(F("         PRINTSAFE PRO STANDALONE FIRMWARE    "));
  Serial.println(F("============================================="));

  // Configure Button Pins with Internal Pull-Ups
  pinMode(greenBtnPin, INPUT_PULLUP);
  pinMode(redBtnPin, INPUT_PULLUP);
  
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerAPin, OUTPUT);
  pinMode(buzzerBPin, OUTPUT);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    errorBlink(3); 
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 25);
  display.setTextSize(2);
  display.println(F("PRINTSAFE"));
  display.display();
  delay(1500);

  // Initial Servo Alignment (Locked State at 0 Degrees)
  servoup.attach(servoupPin);
  servodown.attach(servodownPin);
  servoup.write(0);
  servodown.write(0); 
  delay(200);
  servoup.detach(); // Cut power to prevent inrush brownouts during setup
  servodown.detach();
  isLocked = true;

  // Initialize Clock
  if (!rtc.begin()) {
    updateOLEDStatus(F("RTC ERROR"), F("Check Wiring"));
    errorBlink(1); 
  }

  // Initialize Fingerprint Sensor
  mySerial.begin(57600);
  finger.begin(57600);
  delay(500); 
  if (!finger.verifyPassword()) {
    updateOLEDStatus(F("AS608 ERROR"), F("Scanner Missing"));
    errorBlink(2); 
  }

  // System Armed Beep
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(buzzerAPin, HIGH); delay(100);
  digitalWrite(buzzerAPin, LOW);
  digitalWrite(greenLedPin, LOW);
}

void loop() {
  // --- BUTTON ROUTINE 1: HIDDEN RED RESET BUTTON ---
  if (digitalRead(redBtnPin) == LOW) {
    if (systemBlock) {
      resetTamperSystem();
    }
  }

  // --- SECURITY CHECK: IF SYSTEM IS BLOCKED, FREEZE UNTIL RED RESET ---
  if (systemBlock) {
    displayRapidTamperFlash();
    return; 
  }

  // --- BUTTON ROUTINE 2: GREEN MANUAL LOCK BUTTON ---
  if (digitalRead(greenBtnPin) == LOW && !isLocked) {
    executeManualRelock();
  }

  // --- BUTTON ROUTINE 3: ADMIN MODE COMBINATION TRIGGER ---
  if (digitalRead(greenBtnPin) == LOW && digitalRead(redBtnPin) == LOW) {
    unsigned long holdStart = millis();
    bool holdSuccess = true;
    
    while (millis() - holdStart < 5000) {
      if (digitalRead(greenBtnPin) == HIGH || digitalRead(redBtnPin) == HIGH) {
        holdSuccess = false;
        break;
      }
      updateOLEDStatus(F("ENTERING ADMIN"), "Hold: " + String((5000 - (millis() - holdStart)) / 1000) + "s");
      delay(100);
    }
    
    if (holdSuccess) {
      runAdminRegistrationMode();
    }
  }

  // --- AUTOMATIC RELOCK ENGINE ---
  if (!isLocked && (millis() - unlockTime >= autoLockDelay)) {
    executeAutomaticRelock();
  }

  // --- REFRESH ARMED STANDBY DISPLAY ---
  refreshStandbyScreen();

  // --- SCAN BIOMETRIC MATRIX ---
  getFingerprintID();
  delay(50); 
}

// --- Biometric Authentication Processing Core ---

int getFingerprintID() {
  while(mySerial.available() > 0) { mySerial.read(); }

  uint8_t p = finger.getImage();
  if (p == FINGERPRINT_NOFINGER) return -1; 
  if (p != FINGERPRINT_OK) return -1; 

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1; 

  updateOLEDStatus(F("PROCESSING..."), F("Matching Print"));

  p = finger.fingerFastSearch();

  if (p == FINGERPRINT_OK) {
    failedAttempts = 0; 
    executeUnlockRoutine();
    return finger.fingerID;
  } 
  else if (p == FINGERPRINT_NOTFOUND) {
    failedAttempts++;
    executeAccessDenied();
    return -1;
  } else {
    return -1;
  }
}

// --- Daily Operations UI Routines ---

void refreshStandbyScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(isLocked ? F("SYSTEM: LOCKED") : F("SYSTEM: UNLOCKED"));
  display.drawFastHLine(0, 10, 128, SSD1306_WHITE);
  
  DateTime now = rtc.now();
  display.setCursor(0, 20);
  display.print(F("Time: ")); 
  if(now.hour() < 10) display.print('0'); display.print(now.hour()); display.print(F(":"));
  if(now.minute() < 10) display.print('0'); display.print(now.minute()); display.print(F(":"));
  if(now.second() < 10) display.print('0'); display.print(now.second());

  display.setCursor(0, 48);
  display.println(isLocked ? F("[ PLACE FINGER ]") : F("[ GREEN TO LOCK ]"));
  display.display();
}

void executeUnlockRoutine() {
  if (!isLocked) return; 
  
  display.clearDisplay();
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  display.setCursor(20, 15);
  display.print(F("ACCESS GRANTED"));
  
  DateTime now = rtc.now();
  display.setCursor(20, 40);
  if(now.hour() < 10) display.print('0'); display.print(now.hour()); display.print(F(":"));
  if(now.minute() < 10) display.print('0'); display.print(now.minute()); display.print(F(":"));
  display.display();

  digitalWrite(greenLedPin, HIGH);
  digitalWrite(buzzerAPin, HIGH); delay(250); 
  digitalWrite(buzzerAPin, LOW);

  // Drive Servos to Unlock (Smooth sweep from 0 to 50 degrees)
  moveServos(0, 50);
  
  digitalWrite(greenLedPin, LOW);
  isLocked = false;
  unlockTime = millis(); 
}

void executeAccessDenied() {
  updateOLEDStatus(F("ACCESS DENIED"), "Attempts: " + String(failedAttempts) + "/3");
  digitalWrite(redLedPin, HIGH);
  digitalWrite(buzzerAPin, HIGH); delay(1000); 
  digitalWrite(buzzerAPin, LOW);
  digitalWrite(redLedPin, LOW);

  if (failedAttempts >= maxFailedAttempts) {
    systemBlock = true; 
  }
}

void executeManualRelock() {
  updateOLEDStatus(F("DOOR LOCKED"), F("Manual Lock Pin"));
  digitalWrite(redLedPin, HIGH); delay(200); digitalWrite(redLedPin, LOW);
  
  // Reverse sweep from 50 degrees back down to 0
  moveServos(50, 0);
  isLocked = true;
}

void executeAutomaticRelock() {
  updateOLEDStatus(F("RELOCKING..."), F("Auto Time Timeout"));
  
  // Reverse sweep from 50 degrees back down to 0
  moveServos(50, 0);
  isLocked = true;
}

// --- Power-Optimized Unified Servo Drive Block ---

void moveServos(int startPos, int endPos) {
  // Power up the motor lines right before rotation begins
  servoup.attach(servoupPin);
  servodown.attach(servodownPin);
  delay(30); 

  if (startPos < endPos) {
    for (int pos = startPos; pos <= endPos; pos++) {
      servoup.write(pos);   
      servodown.write(pos); 
      delay(stepDelay);     
    }
  } else {
    for (int pos = startPos; pos >= endPos; pos--) {
      servoup.write(pos);   
      servodown.write(pos); 
      delay(stepDelay);     
    }
  }
  
  delay(150); // Allow physical momentum to finish settling at endpoints
  
  // Cut holding current completely to prevent internal brownout resets
  servoup.detach();
  servodown.detach();
}

// --- For Admin Use: Registration Mode Engine ---

void runAdminRegistrationMode() {
  digitalWrite(buzzerAPin, HIGH); delay(80); digitalWrite(buzzerAPin, LOW); delay(80);
  digitalWrite(buzzerAPin, HIGH); delay(80); digitalWrite(buzzerAPin, LOW);
  
  updateOLEDStatus(F("ADMIN MODE"), F("Booting Profiles"));
  delay(1500);
  
  int id = 1;
  while (id < 128) {
    if (finger.loadModel(id) != FINGERPRINT_OK) {
      break; 
    }
    id++;
  }

  // --- PASS 1: SCAN FIRST PRINT ---
  while (true) {
    updateOLEDStatus(F("ADMIN ACTIVE"), F("Place new finger"));
    int p = finger.getImage();
    if (p == FINGERPRINT_OK) break;
  }

  if (finger.image2Tz(1) != FINGERPRINT_OK) {
    updateOLEDStatus(F("REG FAILED"), F("Image Bad. Aborting"));
    delay(2000); return;
  }
  
  updateOLEDStatus(F("REMOVE FINGER"), F("Lift off glass"));
  digitalWrite(buzzerAPin, HIGH); delay(100); digitalWrite(buzzerAPin, LOW);
  
  while (finger.getImage() != FINGERPRINT_NOFINGER) { delay(100); }

  // --- PASS 2: CONFIRM SAME PRINT ---
  while (true) {
    updateOLEDStatus(F("CONFIRMATION"), F("Place same again"));
    int p = finger.getImage();
    if (p == FINGERPRINT_OK) break;
  }

  if (finger.image2Tz(2) != FINGERPRINT_OK) {
    updateOLEDStatus(F("REG FAILED"), F("Matrix Mismatch"));
    delay(2000); return;
  }

  if (finger.createModel() != FINGERPRINT_OK) {
    updateOLEDStatus(F("REG FAILED"), F("Model Error"));
    delay(2000); return;
  }

  if (finger.storeModel(id) == FINGERPRINT_OK) {
    updateOLEDStatus(F("SUCCESS!"), F("Finger Registered"));
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(buzzerAPin, HIGH); delay(100); digitalWrite(buzzerAPin, LOW); delay(50);
    digitalWrite(buzzerAPin, HIGH); delay(300); digitalWrite(buzzerAPin, LOW);
    digitalWrite(greenLedPin, LOW);
  } else {
    updateOLEDStatus(F("REG FAILED"), F("Storage Write Err"));
  }
  delay(2000);
}

// --- Security, Alerts, and Hard Resets ---

void displayRapidTamperFlash() {
  updateOLEDStatus(F("🚨 LOCKOUT 🚨"), F("SYSTEM COMPROMISED"));
  
  digitalWrite(redLedPin, HIGH);
  digitalWrite(buzzerAPin, HIGH);
  delay(60);
  digitalWrite(buzzerAPin, LOW);
  
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerBPin, HIGH);
  delay(60);
  digitalWrite(buzzerBPin, LOW);
}

void resetTamperSystem() {
  digitalWrite(buzzerAPin, LOW);
  digitalWrite(buzzerBPin, LOW);
  digitalWrite(redLedPin, LOW);
  
  failedAttempts = 0;   
  systemBlock = false;  
  
  updateOLEDStatus(F("ALARM CLEARED"), F("System Ready"));
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(buzzerAPin, HIGH); delay(400); digitalWrite(buzzerAPin, LOW);
  digitalWrite(greenLedPin, LOW);
  delay(1000);
}

void updateOLEDStatus(String header, String subtext) {
  display.clearDisplay();
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE); 
  display.setTextSize(1);
  display.setCursor(10, 15);
  display.println(header);
  display.setCursor(10, 40);
  display.println(subtext);
  display.display();
}

void errorBlink(int blinks) {
  while(1) {
    for(int i=0; i<blinks; i++) {
      digitalWrite(redLedPin, HIGH);
      digitalWrite(buzzerAPin, HIGH); delay(100);
      digitalWrite(buzzerAPin, LOW);
      digitalWrite(redLedPin, LOW);  delay(150);
    }
    delay(1000); 
  }
}