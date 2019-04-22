# Capstone Project 2019
## Microcontroller - Adafruit ESP32 Feather
## Module - FONA 808

This project is to be able to create a Smart Pad GPS for babies. 
These files are in charge of the wireless communications of the project - using the FONA 808

# Introduction and Reason
Infant/Toddler car seats and strollers are essential part of mobility and safety requirements for children when traveling. On long drives, it is important to continuously monitor the infant/toddler to make sure they are safe, comfortable, and securely fastened to the car seats. This is especially true  during sleep when infant/toddler alter their posture, possibly leading to unsafe neck or spine positions. Furthermore, changes in temperature, abnormal carbon monoxide levels or wet diapers can result discomfort, irritation and even danger for the child.  There have also been cases where babies were left unattended inside a vehicle, some have even resulted in tragedies. Currently, there exists only one similar product on the market it is called the “Tippy Pad”; however, it does not address the many issues of safety and comfort it simply functions to alert parents if a child was left behind in the vehicle.  

# Objective
This project aims to design a portable smart pad mountable to standard car seats and strollers, which can detect  multi-channel information on baby posture, wetness, temperature, Carbon Monoxide content in the vehicle and GPS location. The information is fed to an intelligent system able to send alarms or warnings on car audio or parents cell phones. In cases where a child is left unattended for an extended period of time, the smart pad is able to contact emergency staff and leave a voice recording explaining the situation and a GPS location. 


# Documents<br/>
### Final
Final folder contains the final files used for the capstone. <br/>
### Demo 
Attached are videos of our demos: <br/>
Demo 1: https://www.youtube.com/watch?v=FvuG59Sc1oY <br/>
Demo 2: https://www.youtube.com/watch?v=KJ0yU8TvkYo

### Phase 3
This will be the file in which the will be continuously worked on. Currently, Bluetooth can be initially connected to a phone, and Bluetooth speakers, simulatensouly. The initiation of the GSM and GPS networks are done at the beginning. These steps are done so the phone and speakers can connect to the microcontroller before entering an infinite loop to check connections. Furthermore, the hardware components are attached. The hardware component includes sensors to detect positioning of the baby. If at any moment, certain sensors are activated, a in-built algorithm activates and causes a soft alert. 

Theorectically, the user would have to connect their devices before the device could start operating. In the operating phase, there are various conditions to be check to make sure the saftey of the baby is prioritized. This is all done simultaneously receiving and saving GPS locations every few moments. 

There are three alerts created: Easy, Medium and Hard.

#### Easy Alert
Bluetooth speakers will output a specific warning to check baby if the conditions are satisfied below:
If the position of the baby is awkward
If the baby wet itself

#### Medium Alert
Text messages will be sent to parents' phones during medium alert due to the various conditions listed below:
If the Bluetooth connection is disconnected
If the head of the baby is leaned forward (causing danger to the baby to the its disproptionate body)

#### Hard Alert 
Phone call to emergency personel conducted. An emergency audio will play, alongside with the last known GPS location.


### GPS_and_GSM_Location
In this file, I am constantly working on this to be able to feed a location.
The location is derived from the GPS of the FONA 808. If the GPS is not able to retrieve a fix (due to being indoors or bad signal), the GSM module will use triangulation to be able to identify the location.

### GPS BLE
A file to use GPS while also connecting to the Bluetooth of the microcontroller

### FONA test 2
Similar to the FONA test in the library, adds more seperation between the different headers

### Write notify
This program is done to connect Bluetooth Devices. The serial monitor will identify and notify the user if it is connected or not. Additionally, the Bluetooth device can communicate by writing stuff to one another. Example image is in the folder

### Initial Connect 
This program was the previously worked on code that combined Bluetooth, GSM and GPS
