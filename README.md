# print_safe
Print safe is a smart biometric storage system designed for students and teachers to securely store their personal belongings.
This project combines fingerprint based access controls,breach detection and activity logging which helps in preventing the unauthorized access.

![Uploading Screenshot 2026-08-05 at 10.52.33 PM Large.png…]()


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

### What was challenging and things to be noted??(overall)
There were many challenges making this project. Here i am listing some important things to be noted to make this project on the basis of what i faced in irl build.
- First, it was challenging to make this project fully eco-friendly by using only cardboards and papers. Every small to big things for the project were made from cardboard but for anyone making this I would recommend using a 3d printed case and components which would help a lot in saving time and efficiency.(I couldnt use 3d printed parts cause it takes 3-4 months and huge tax to deliver from abroad and there are not trusted 3d printing platform in my country.
- The logic behind the door opening and closing seems easy in CAD but its a bit complicated as, in my case, servo didnt directly attach to the door so I was forced to use a cardboard extension which attaches to servo head and the door too. But doing this made the cardboard extension move left and right along the door when the servo started to work. So to tackle this I applied the hot glue to the other end of extension and attached it to door and instantly turned and run the device 4 to 5 times which made the glue flexible and the problem was somehow solved but i found that the door dosnt fully close due to the flexible glue. so for this prototype version this issue was not solves and i managed to close it with my hand for the remaining part which then would attach to the magnets inside and holds the door in fixed position. Hence, the 3d printed fixed parts could have solved it.
- Also keep in mind that you dont join the boost converter in opposite direction as it would burn the internal components and you'll have to buy a new one as i did.
- Make sure the batteries are connected in parallel as i. did which would provide a good balanced voltage to the boost converter. 
- This time when i tried to attach the oled, fingerprint sensor and leds to the cardboard door, they were so heavy for the cardboard to handle so i had to change the whole design if my door only letting the oled display attach to the door while moving.
- Last challenge was to provide the essential torque to the door through servos to overcome the magnetic forse between the magnets attached to the end of the door and inner wall of door. So to match the torque of servos I taped the magnet's outer parts and then attached to the door which eventually reduced the magnetic force between the magnets and it was easier for servos to overcome the force. So i recommend using more powerful servos than the standard blue SG90 servos.

That's it!!! If you keep these challenges in mind and work for project, you'd definitely make this project easily in most efficient way.

## why this and why is it unique?
- its not just a lock but decision based security system
- combines verification + intrusion + logging
- designed for real world student problems

## where can it be used ??
- hostel lockers
- school storage system
- personal drawers and cabinets
- shared living spaces

## IRL Build:
### Pictures:
<img width="3024" height="4032" alt="tempImageHhVQ3i" src="https://github.com/user-attachments/assets/679ac7d0-95e1-4fda-b48c-8c3792310a84" />
<img width="3024" height="4032" alt="tempImage1bL4IE" src="https://github.com/user-attachments/assets/3fc62e49-c693-49f1-8d8a-30dd4d9ce204" />
<img width="3024" height="4032" alt="tempImageRyGA7T" src="https://github.com/user-attachments/assets/e19e0992-8614-457a-b1be-6b6758894daa" />
<img width="3024" height="4032" alt="tempImageo10fXb" src="https://github.com/user-attachments/assets/ad17c2fe-1fbe-4fe1-966b-43b3408a2b6a" />
<img width="3024" height="4032" alt="tempImage0Veda7" src="https://github.com/user-attachments/assets/02d16692-3f6a-4513-ab15-03e640c7da5c" />
<img width="4032" height="3024" alt="tempImageZshb4o" src="https://github.com/user-attachments/assets/b8d38bb1-fc13-44eb-a6fe-4f2ea89056ba" />
<img width="4032" height="3024" alt="tempImagegbeKXF" src="https://github.com/user-attachments/assets/0e32452f-2b99-4079-9634-7fb65941eb94" />
<img width="3024" height="4032" alt="tempImagegSR62w" src="https://github.com/user-attachments/assets/8a5633c5-937b-4931-b874-1986c7bff06e" />

### Demo Video:
Youtube: [Demo Video](https://www.youtube.com/watch?v=nzNCS3ORe8U)






## CAD:
<img width="726" height="530" alt="Screenshot 2026-08-04 at 6 19 32 PM" src="https://github.com/user-attachments/assets/7b34b0f6-35bc-44b9-97d9-c8afb4491a52" />
<img width="979" height="646" alt="Screenshot 2026-08-04 at 6 20 45 PM" src="https://github.com/user-attachments/assets/39362980-543b-4d38-bfd9-2a5dcdef6201" />
<img width="642" height="512" alt="Screenshot 2026-08-04 at 6 21 53 PM" src="https://github.com/user-attachments/assets/7aa7b96e-a41c-41cd-b748-1d85a6800257" />
<img width="909" height="534" alt="Screenshot 2026-08-04 at 6 22 24 PM" src="https://github.com/user-attachments/assets/44274b46-5b3e-43dc-9086-27cbd8e07b50" />
<img width="808" height="655" alt="Screenshot 2026-08-04 at 6 29 24 PM" src="https://github.com/user-attachments/assets/03dbcb3d-555e-4d8b-b60e-06a1ced35abc" />
<img width="782" height="647" alt="Screenshot 2026-08-04 at 6 30 27 PM" src="https://github.com/user-attachments/assets/e9f0f293-2527-4e33-862b-a14aae9f25a2" />





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
- Push Button Switches
- 18650 Battery Holder
- 18650 Lithium-Ion Battery
- TP4056 Charging Module
- MT3608 Boost Converter(or equivalent)
- I2C OLED Display 0.96 inch
- DS3231 RTC Module
- ESP8266 NodeMCU(optional)
- 1000μF (Polarized)(greater than 5V)
- Switch (on/off)
- Battery to DC barrel jack(for arduino)
- 3D models as stated above.




