/* Capstone project */

char* sendto;
char* message;
int count = 0;

#include "SD_card.h"
#include "GPS_and_GSM_Location.h"
#include "alert.h"
#include "hardware_functions.h"
#include "setup_ble.h"

TaskHandle_t ReadSens;
TaskHandle_t BlinkLED;


void setup() {
  // put your setup code here, to run once:

  delay (250);
  bluetooth_startup();

  delay(2000);
  init_SD();

  delay (2000);
  Fona808_intial();

  delay (2000);
  Fona808_connect ();

  delay (2000);
  sensor_act_begin ();

  delay (250);

}



void loop() {

  int t_hold;
  int t_present;
  int alert_level = 0;
  int i;

  initial_connections ();
  delay (500);

  // Gets current time before entering normal loop
  t_hold = millis ();
  Serial.println(t_hold);

  if (deviceConnected) //(bl_speaker && deviceConnected)
  {

    while (1)
    {

      t_present = millis (); // Gets current time
      delay (500);

      // Hardware Component
      //Remove comments
      sensor_act_main_obtain ();
      delay(500);
      ReadSensCode();

      delay (500);
      Serial.println("Connection successful - move into while loop");
      delay (500);
      alert_level = alert (alert_level);



      // Find the GPS every 20 Seconds
      if (t_present >= t_hold + 70000)
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




      // Easy Alert
      if (bl_message)
      {
        bl_message = false; // Goes into loop and then cancels to avoid infinite loop
        Serial.println("*************Entering Bluetooth disconnection test*************");
        delay (500);
        filename_value (2);
        alert_level = 1;
        delay (500);
      }



      /*
          // Easy Alert
          if (bl_message)
          {
            bl_message = false; // Goes into loop and then cancels to avoid infinite loop
            Serial.println("*************Entering Bluetooth  disconnection test*************");
            delay (500);

            lat = "43.710268";
            for (i = 0; i < 6; i++)
            {
              case_statement_audio_files (lat[i]);
            }
            delay (500);

            char filename_phonecall1[27] = "/sdcard/initTest.wav"; // Initial Announcement
            play_audio (filename_phonecall1);

            delay (500);
            Serial.println("Post Audio File Play"); //  test to see when this gets outputted
          }
      */


      // Medium Alert
      // Bluetooth becomes disconnected

      ble_phone_connection_status();
      if (!deviceConnected)
      {
        Serial.println("Entering Bluetooth Phone disconnection test");
        delay (500);
        alert_level = 2;
      }



      delay (1);
      yield ();

    } // while loop
  }// if statement


}// main fct






void  initial_connections ()
{


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
  
    if (!gsmnetwork)
    {
    Serial.println("GSM connection confirmed");
    delay (1000);
    }
  
}





