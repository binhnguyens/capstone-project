# capstone-project
Microcontroller - Adafruit ESP32 Feather
Module - FONA 808

This project is to be able to create a Smart Pad GPS for babies. 
These files are in charge of the wireless communications of the project - using the FONA 808

# Introduction and Reason
Infant/Toddler car seats and strollers are essential part of mobility and safety requirements for children when traveling. On long drives, it is important to continuously monitor the infant/toddler to make sure they are safe, comfortable, and securely fastened to the car seats. This is especially true  during sleep when infant/toddler alter their posture, possibly leading to unsafe neck or spine positions. Furthermore, changes in temperature, abnormal carbon monoxide levels or wet diapers can result discomfort, irritation and even danger for the child.  There have also been cases where babies were left unattended inside a vehicle, some have even resulted in tragedies. Currently, there exists only one similar product on the market it is called the “Tippy Pad”; however, it does not address the many issues of safety and comfort it simply functions to alert parents if a child was left behind in the vehicle.  

# Objective
This project aims to design a portable smart pad mountable to standard car seats and strollers, which can detect  multi-channel information on baby posture, wetness, temperature, Carbon Monoxide content in the vehicle and GPS location. The information is fed to an intelligent system able to send alarms or warnings on car audio or parents cell phones. In cases where a child is left unattended for an extended period of time, the smart pad is able to contact emergency staff and leave a voice recording explaining the situation and a GPS location. 


# Files
### GPS_and_GSM_Location
In this file, I am constantly working on this to be able to feed a location.
The location is derived from the GPS of the FONA 808. If the GPS is not able to retrieve a fix (due to being indoors or bad signal), the GSM module will use triangulation to be able to identify the location.

### GPS BLE
A file to use GPS while also connecting to the Bluetooth of the microcontroller

### FONA test 2
Similar to the FONA test in the library, adds more seperation between the different headers
