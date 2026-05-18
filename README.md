# print_safe
Print safe is a smart biometric storage system designed for students and teachers to securely store their personal belongings.
This project combines fingerprint based access controls,breach detection and activity logging which helps in preventing the unauthorized access.

<img width="1587" height="2245" alt="Print Safe" src="https://github.com/user-attachments/assets/9cf2ec7c-eda1-4488-8dcb-d4821535aaf3" />


## What is this project??
Print safe is an intelligent locker system that allows only authorized person to access stored items using their fingerprint.

Unlike basic locks; it doesnt just opens or closes it but::
- Verifies the identity using fingerprint sensor
- Detects forced access or tampering
- Logs all the access attempts(all including successful and failed one) 

This thing makes it suitable for places like schools,hostels and even a shared living spaces.

## How do you use it? 
1. first user places finger on the sensor
2. the system then scans and compares fingerprint with a stored data
3. if fingerprint matches; 
    - access is granted, 
    - servo unlocks storage, 
    - led indicates success 
    - logs the successful access attempt
4. But if the fingerprint doesnt match; 
    - access is denied 
    - failed attempt is recorded.
5. then if multiple failed attempts i.e tampering is detected:
    - Buzzer alert is triggered
    - system enters a temporary lock state
6. all activities are recorded for monitoring.


## Story behind this:

- Why am i making this? 
I lived in my school's hostel in my school life. The main problem of hostel life was that my belongings never stayed in my place. Someone always came to my place and misplace my personal belongings, which would frustate me and I used to be very angry as:
    - my items were not always where i left them
    - there was no way to know who accessed them
    - privacy was very hard to maintain

To solve this problem for hostel students, I thought of creating a system to:
    - protect belongings
    - ensure authorized access
    - let user know if system was tampered or not


- How the idea came in my mind?
The idea actually came from my own room at home. One day while i was sitting in my bed, I thought that I don't have privacy maintained in my room. While i was sleeping i thought of keeping a fingerprint scanning device in my room's entrance that would only unlock the room if the fingerprint would match to me. I thought,'Why not make my own custom device at home buying all the parts from the market🤔'. But I never made it 😭.

**print_safe** is my attempt to bring these ideas to life, solving real world problem I personally faced.

## why this and why is it unique?
- its not just a lock but decision based security system
- combines verification + intrusion + logging
- designed for real world student problems

## where can it be used ??
- hostel lockers
- school storage system
- personal drawers and cabinets
- shared living spaces

## CAD:
<img width="777" height="581" alt="Screenshot 2026-05-18 at 3 55 42 PM" src="https://github.com/user-attachments/assets/51cdbec7-775d-4732-9777-3da56444da0f" />
<img width="735" height="649" alt="Screenshot 2026-05-18 at 3 56 14 PM" src="https://github.com/user-attachments/assets/82066022-4a11-45aa-a771-0e0a8e584d13" />
<img width="840" height="627" alt="Screenshot 2026-05-18 at 3 56 57 PM" src="https://github.com/user-attachments/assets/b4a2e382-11dd-45cd-bc53-f95e467d3019" />


For those who want to see full design, here's the like to the Onshape CAD model:

[Onshape Model](https://cad.onshape.com/documents/6a9e66424898c3a5d22b5a59/w/668f054415e8574befa880c0/e/ee66468a29e6d836aa232004?renderMode=0&uiState=6a0ae9338172e23688a599eb)

## Circuit Diagram:
I made the circuit diagram for my project using tikercad. Due to absence of required components i have used Breadboard to complete the circuit diagram and used the notes feature in tinkercad😅.

   ### SS:
   <img width="1004" height="682" alt="Main circuit" src="https://github.com/user-attachments/assets/42735b55-d0d9-42fe-81e2-2fabd818c774" />
<img width="1095" height="577" alt="battery,charging,boost circuit" src="https://github.com/user-attachments/assets/dc8122c6-6fb9-4a21-8e57-e009ccbc5883" />

   ### Links to tinkercad:
   
   [Main circuit](https://www.tinkercad.com/things/bx13RGkoUNs-printsafe-cc/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=D09gbGRxw1kjS-in_ok5X9PMID51vPCvei0ZnDljU3c)
   
   [Battery and charging circuit](https://www.tinkercad.com/things/15RenR3HXBn-charging-and-boost/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=QZZ-2SHpT_xSTQirN5RwBh1pLtKrvM8x8ejTbw8yr-w)




## Components required(planned):

- Arduino uno with cable
- AS608 Fingerprint Module
- Servo motor
- Leds
- Active Electronic Buzzer
- Resistors (10k Ω)
- Resistors (220 Ω)
- WIRES
- Breadboard
- Push Button Switch
- 18650 Battery Holder
- 18650 Lithium-Ion Battery
- TP4056 Charging Module
- MT3608 Boost Converter
- I2C OLED Display 0.96 inch
- DS3231 RTC Module
- ESP8266 NodeMCU(optional)
- 1000μF (Polarized)(greater than 5V)
- Switch (on/off)





