# print_safe
Print safe is a smart biometric storage system designed for students and teachers to securely store their personal belongings.
This project combines fingerprint based access controls,breach detection and activity logging which helps in preventing the unauthorized access.

<img width="1587" height="2245" alt="Print Safe" src="https://github.com/user-attachments/assets/f5c46e3e-c9f5-4db0-9d83-85bec6d800bc" />


## What is this project??
Print safe is an intelligent locker system that allows only authorized person to access stored items using their fingerprint.

Unlike basic locks; it doesnt just opens or closes it but::
- Verifies the identity using fingerprint sensor
- Detects forced access or tampering
- Logs all the access attempts(all including successful and failed one) 

This thing makes it suitable for places like schools,hostels and even a shared living spaces.

## How do you use it? 

1. For Daily Use:
    - Place your registered finger on the sensor:

    1. If fingerprint matches:
        - Servo rotates to unlock the storage
        - Green LED will turn on indicating success
        - A success beep will sound from the buzzer
        - Oled display will show "Access Granted" along with clock
        - The safe will automatically lock after 5 secs(initially)
    2. If fingerprint does not match:
        - Red LED will turn on indicating failure
        - A failure beep will sound from the buzzer
        - Oled display will show "Access Denied" 
    - To lock manually:
        - Press the green push button switch to lock the safe immediately
        - Oled display will show "Door Locked"

2. For Admin Use:
    - To enter admin mode:
        - Press and hold both the green and red push button switch for 5 seconds 
        - The safe will play double beep and oled will show "Admin Mode" and then "Place finger to register"
        1. To register a new fingerprint:
            - Place the new finger on the sensor
            - The system will capture first scan and prompt 'Remove finger'
            - Lift the finger from the sensor
        2. When screen prompts 'Place same finger again':
            - Place the same finger again on the sensor to confirm
        - If successfull, buzzer will play a success tone and oled will show "Fingerprint Registered"

3. Security and resets:
    - Tamper alarm:
        - If an unregistered finger is scanned 3 times in a row, the system will trigger a tamper alarm:
            - Buzzer will sound continuously with loud beeps
            - Red LED will flash rapidly
            - The biometric system will be locked to prevent further attempts
    - To reset the system:
        - Press the red push button which is hidden in the side of the safe
        - This will reset the siren
        - Clear the failed attempt count
        - Allow users to try accessing again
        - Again ready to scan fingerprints



## Story behind this:

### Why am i making this? 
I lived in my school's hostel in my school life. The main problem of hostel life was that my belongings never stayed in my place. Someone always came to my place and misplace my personal belongings, which would frustate me and I used to be very angry as:
- my items were not always where i left them
- there was no way to know who accessed them
- privacy was very hard to maintain

To solve this problem for hostel students, I thought of creating a system to:
- protect belongings
- ensure authorized access
- let user know if system was tampered or not


### How the idea came in my mind?
The idea actually came from my own room at home. One day while i was sitting in my bed, I thought that I don't have privacy maintained in my room. While i was sleeping i thought of keeping a fingerprint scanning device in my room's entrance that would only unlock the room if the fingerprint would match to me. I thought,'Why not make my own custom device at home buying all the parts from the market🤔'. But I never made it 😭.

**print_safe** is my attempt to bring these ideas to life, solving real world problem I personally faced.

## Project preparation instructions:

Printsafe is designed to be fully robust, utilizing mechanical fastners and 3d-printed components.

### Component fastening instructions:
1. Dev boards(Arduino,rtc,boost conv.,charging module,etc): 

    They are mounted to the floor of enclosure using screws through its screw mounting holes.
2. Locking Servos:

    They are slid into custon 3D-printed mounting cages(as in the 3D model) and secure tightly with screws to prevent torsion during locking sequences.
3. Enclosure Door:

    Attached to the main body via dual screw mechanical hinge layout.
4. Door alignment and security:

    A high strength magnetic latch is alighed on the interior frame to provide tactile door retention, ensuring the door remains fixed to the frame so the servo deadbolts can smoothly engage and lock the system.

### Step by step assembly:
1. Prepare the shell:

    3D print the main enclosure body and door panel using the provided 'CAD' files in the repo(recommended: PLA/PETG).
2. Mount the core electronics:

    Secure the Arduino and other similar electronic componects directly into the 3Dprinted mounts given in CAD files as in Onshape.
    Similarly using the dedicated heaavy duty double sided tape of breadboards mount it into the wall as in CAD.Many breadboards already come with a peel-and-stick adhesive backing. Clean both the back of the breadboard and the wall thoroughly before applying.
3. Install servo mounts:

    Screw the 3D printed servo brackets into the interior left wall as in CAD. Slide the servos into the brackets and secure them easily.
4. Hinge and latch attachment:

    Screw the physical hinge to both the interior side wall and the door panel.Mount the magnetic latch components to ensure the tight, aligned seal when the door swings shut.
5. Calibrate the lock position:

    Power the electronics so the servos rotate to their default locked positions, then attach the locking arms to perfectly block door path when closed.
(NOTE: the 3d models are available in fully assembled and parts form in the repo itself. they are refecenced mostly from grabcad and other 3d model libraries.)


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
<img width="906" height="621" alt="Screenshot 2026-05-28 at 10 41 38 PM" src="https://github.com/user-attachments/assets/623817b1-e86f-4192-96c9-de92e608676b" />
<img width="574" height="434" alt="Screenshot_2026-05-28_at_5 22 28_PM-removebg-preview" src="https://github.com/user-attachments/assets/49e4ef9b-bb4d-4d58-a02b-1e6e49e96c5a" />
<img width="839" height="624" alt="Screenshot 2026-05-28 at 10 45 32 PM" src="https://github.com/user-attachments/assets/424cce52-7fbf-4e7c-9578-baf0c80d444c" />
<img width="870" height="624" alt="Screenshot 2026-05-28 at 10 47 16 PM" src="https://github.com/user-attachments/assets/7327bde4-9f53-498f-bb37-7edc9213c99e" />
<img width="844" height="483" alt="Screenshot 2026-05-28 at 10 47 41 PM" src="https://github.com/user-attachments/assets/1523f70a-24d3-4339-916d-27264110f57a" />
<img width="499" height="469" alt="Screenshot 2026-05-28 at 10 48 26 PM" src="https://github.com/user-attachments/assets/164011d0-d3e5-40dc-9395-31f41455383b" />


For those who want to see full design, here's the like to the Onshape CAD model:

[Onshape Model](https://cad.onshape.com/documents/6a9e66424898c3a5d22b5a59/w/668f054415e8574befa880c0/e/08491907242ab19b0f76189a)

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
- Battery to DC barrel jack(for arduino)
- 3D CAD models as stated above.




