

#include "setup_ble.h"
#include "GPS_and_GSM_Location.h"

char* sendto;
char* message;
int count = 0;


bool ack_required = false;
int t_hold;
int t_present;
int gps_counter = 1;
int alert_level = 0;


void setup() {
  // put your setup code here, to run once:
  bluetooth_startup();
  delay (2500);
  Fona808_intial();
  delay (2500);
  Fona808_connect ();
}

void loop() {

    /****** Begin Initial Connections ******/

    ble_phone_connection_status();
    if (deviceConnected)
    {
      Serial.println("Bluetooth Phone connect");
    }

    /****** Bluetooth to Speakers connection ******/
    if (bl_speaker)
    {
      Serial.println("Bluetooth speaker connect");
      delay (1000);
    }

    /****** GPS and GSM connections ******/
    
    if (gsmnetwork)
    {
      Serial.println("GSM connection confirmed");
      delay (1000);
    }
    
    delay (500);
    t_hold = millis (); // Gets current time before entering normal loop
    Serial.println(t_hold);

            if(bl_speaker && deviceConnected)
            {
                  while (1)
                  {

                    
                      t_present = millis (); // Gets current time    
                      
                      Serial.println("Connection successful - move into while loop");    
                      delay (1000);
                      alert (alert_level);

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

                      
                      
                      // Bluetooth becomes disconnected
                      ble_phone_connection_status();
                      if (!deviceConnected) 
                      {
                        Serial.println("Entering Bluetooth disconnection test");   
                        delay (500);
                        alert_level =2;
                      }


                      
                      delay (1);
                      yield (); 
                      
                  } // while loop
            }// if statement

            
}// main fct








void alert (int alert_level){
    if (alert_level == 1) // easy alert -> Baby positioned weird, something that needs to be adjusted
    {
      delay  (1000);
      Serial.println("Entering Easy Alert");   
      easy_alert();
      delay (1000);
    }

    else if (alert_level == 2) // medium alert -> BL disconnected, Baby is not there, etc.
    {
      delay  (1000);
      Serial.println("Entering Medium Alert");  
      medium_alert();
      delay  (1000);
    }
    
    else if (alert_level == 3) // hard alert -> No response from parent 
    {
      delay  (1000);
      Serial.println("Entering Hard Alert");  
      hard_alert();
      delay  (1000);
    }
}

void easy_alert (){
  Serial.println(F("Entering Easy Alert"));
  delay (1000);
  Serial.println("----------------------------------------------------");
  //bt_app_av_media_proc(uint16_t event, void *param)
  
  delay (5000);
  
  /***** Include parameters to check condition*****/
    
}


void medium_alert (){
  while (1){
  Serial.println(F("Entering Medium Alert"));
  delay (1000);
  Serial.println("----------------------------------------------------");
  sendto = "6477162554";
  message = "This is a medium alert - Please reset system";
  text_message (sendto, message);
  count +=1;
  Serial.println(count);
  delay (10000);
  
  if (count == 3)
    {
        hard_alert();      
        
    }


    /***** Include parameters to check condition*****/
    
  }// while loop

}


void hard_alert (){
  Serial.println(F("Entering Hard Alert"));
  delay (1000);
  Serial.println("----------------------------------------------------");
  sendto = "6477162554";
  headphone_jack ();
  phonecall (sendto);
  delay (100000);

  
   
}

