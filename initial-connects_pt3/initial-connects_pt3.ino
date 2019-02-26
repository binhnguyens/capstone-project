/* Capstone project */


char* sendto;
char* message;
int count = 0;

#include "SD_card.h"
#include "setup_ble.h"
//#include "GPS_and_GSM_Location.h"
#include "alert.h"

void setup() {
  // put your setup code here, to run once:

  delay (250);
  bluetooth_startup();
  delay(2500);
  init_SD();
  /* REMOVE
    delay (2500);
    Fona808_intial();
    delay (2500);
    Fona808_connect ();
    delay (500);
  */

}



void loop() {
  int t_hold;
  int t_present;
  int gps_counter = 1;
  int alert_level = 0;
  char filename[27] = "/sdcard/imperial_8_bit.wav";


  /****** Begin Initial Connections ******/
  ble_phone_connection_status();
  if (deviceConnected)
  {
    Serial.println("Bluetooth Phone connect");
    delay (1000);
  }

  /****** Bluetooth to Speakers connection ******/
  if (bl_speaker)
  {
    Serial.println("Bluetooth speaker connect");
    delay (1000);
  }

  /****** GPS and GSM connections ******/
  /*REMOVE
    if (gsmnetwork)
    {
    Serial.println("GSM connection confirmed");
    delay (1000);
    }
  */

  delay (500);

  t_hold = millis ();


  // Gets current time before entering normal loop
  Serial.println(t_hold);

  if (bl_speaker && deviceConnected)
  {

    while (1)
    {


      t_present = millis (); // Gets current time

      Serial.println("Connection successful - move into while loop");
      delay (1000);
      alert_level = alert (alert_level);



      /*REMOVE
        // Find the GPS every 20 Seconds
        if (t_present >=t_hold+20000)
        {
        Serial.println("Entering gps loop");
        gps_location ();
        retrieve_lat_lon ();
        t_hold = t_present;
        Serial.println("Latitude");
        Serial.println(lat);
        Serial.println("Latitude");
        Serial.println(lon);

        }
      */

      // Easy Alert
      if (bl_message) // Testing with input from iPhone
      {
        bl_message = false;
        Serial.println("Entering Bluetooth Speaker disconnection test");
        delay (500);
        alert_level = 1;
        //play_audio (filename);
      }


      // Medium Alert
      // Bluetooth becomes disconnected
      /* FROG - REMOVE THIS COMMENT
        ble_phone_connection_status();
        if (!deviceConnected)
        {
        Serial.println("Entering Bluetooth Phone disconnection test");
        delay (500);
        alert_level =2;
        }
      */

      delay (1);
      yield ();

    } // while loop
  }// if statement


}// main fct




