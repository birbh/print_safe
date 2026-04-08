# print_safe
Print safe is a smart biometric storage system designed for students and teachers to securely store their personal belongings.
This project combines fingerprint based access controls,breach detection and activity logging which helps in preventing the unauthorized access.

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

## Components required(planned):

- arduino uno or nano
- AS608 finferprint sensor
- servo motor (for locking mechanism)
- leds(status indicators)
- Buzzer (alerts)
- resistors and wiring
- aluminium foil (tamper detection)