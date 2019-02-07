/*
Open up the serial console on the Arduino at 115200 baud to interact with FONA

Note that if you need to set a GPRS APN, username, and password scroll down to
the commented section below at the end of the setup() function.
*/
#include "Adafruit_FONA.h"
#include <string.h>
#include <stdio.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define FONA_RX 15
#define FONA_TX 16
#define FONA_RST 4

// this is a large buffer for replies
char replybuffer[255];

// Hardware serial is also possible!
HardwareSerial *fonaSerial = &Serial2;

// Use this for FONA 800 and 808s
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);


class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

uint8_t type;

void setup() {
  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  
  while (!Serial);

  Serial.begin(115200);
  Serial.println(F("FONA basic test"));
  Serial.println(F("Initializing....(May take 3 seconds)"));

  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  
  type = fona.type();
  Serial.println(F("FONA is OK"));
  Serial.print(F("Found "));
  
  switch (type) {
    case FONA800L:
      Serial.println(F("FONA 800L")); break;
    case FONA800H:
      Serial.println(F("FONA 800H")); break;
    case FONA808_V1:
      Serial.println(F("FONA 808 (v1)")); break;
    case FONA808_V2:
      Serial.println(F("FONA 808 (v2)")); break;
    default: 
      Serial.println(F("???")); break;
  }
  
  // Print module IMEI number.
  char imei[16] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
    Serial.print("Module IMEI: "); Serial.println(imei);
  }
  
}







void loop() {
  Serial.print(F("FONA> "));




    /*********************************** GPS (SIM808 only) */

    
        // turn GPS off
        /*
        if (!fona.enableGPS(false))
          Serial.println(F("Failed to turn off"));
        break;
        */
    
        // turn GPS on
        if (!fona.enableGPS(true))
          Serial.println(F("Failed to turn on"));


        delay (3000);
      
        while (1){
          int8_t stat;
          
          // check GPS fix
          Serial.println(F("----------------------------------------------------"));
          Serial.println(F("Fix Status:"));
          Serial.println(F(""));
          stat = fona.GPSstatus();
          if (stat < 0)
            Serial.println(F("Failed to query"));
          if (stat == 0) Serial.println(F("GPS off"));
          if (stat == 1) Serial.println(F("No fix"));
          if (stat == 2) Serial.println(F("2D fix"));
          if (stat == 3) Serial.println(F("3D fix"));

          delay (3000);
          
          // check for GPS location
          Serial.println(F("----------------------------------------------------"));
          Serial.println(F("GPS Location:"));
          Serial.println(F(""));
          char gpsdata[120];
          fona.getGPS(0, gpsdata, 120);
          if (type == FONA808_V1)
              Serial.println(F("Format: mode,longitude,latitude,altitude,utctime(yyyymmddHHMMSS),ttff,satellites,speed,course"));
          else 
              Serial.println(F("Format: mode,fixstatus,utctime(yyyymmddHHMMSS),latitude,longitude,altitude,speed,course,fixmode,reserved1,HDOP,PDOP,VDOP,reserved2,view_satellites,used_satellites,reserved3,C/N0max,HPA,VPA"));
          Serial.println(gpsdata);
          Serial.println(F("----------------------------------------------------"));
          
          delay (2000);
          
          char *token;
          char *lat;
          char *lon;
          int i=0;
          
          /* get the first token */
          token = strtok(gpsdata, ",");
          
          /* walk through other tokens */
          
          while( token != NULL ) {
                   
              if (i==3){
                la212q  `````1  `   `1  `1  pt = token;
              }
          
              if(i==4){
                lon = token;
              }
              i +=1;
              token = strtok(NULL, ",");
           }

          Serial.println(F("Latitude"));
          Serial.println(lat);
          Serial.println(F("Longitude"));
          Serial.println(lon);
          Serial.println("----------------------------------------------------");
          
          delay (2000);
          
        }

}








// Functions to be called





uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout) {
  uint16_t buffidx = 0;
  boolean timeoutvalid = true;
  if (timeout == 0) timeoutvalid = false;

  while (true) {
    if (buffidx > maxbuff) {
      //Serial.println(F("SPACE"));
      break;
    }

    while (Serial.available()) {
      char c =  Serial.read();

      //Serial.print(c, HEX); Serial.print("#"); Serial.println(c);

      if (c == '\r') continue;
      if (c == 0xA) {
        if (buffidx == 0)   // the first 0x0A is ignored
          continue;

        timeout = 0;         // the second 0x0A is the end of the line
        timeoutvalid = true;
        break;
      }
      buff[buffidx] = c;
      buffidx++;
    }

    if (timeoutvalid && timeout == 0) {
      //Serial.println(F("TIMEOUT"));
      break;
    }
    delay(1);
  }
  buff[buffidx] = 0;  // null term
  return buffidx;
}
