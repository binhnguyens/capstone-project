#ifndef _ALERT_H
#define _ALERT_H


void easy_alert () {
  Serial.println(F("Entering Easy Alert"));
  delay (1000);
  Serial.println("----------------------------------------------------");
  trig = 1;
  delay (10000);
  trig = 0;
  /***** Include parameters to check condition*****/

}


void hard_alert () {
  /* REMOVE
    Serial.println(F("Entering Hard Alert"));
    delay (1000);
    Serial.println("----------------------------------------------------");
    sendto = "6477162554";
    headphone_jack ();
    phonecall (sendto);
    delay (10000);
    play_audio (filename);
    delay (10000);
  */
}



void medium_alert () {
  /* REMOVE
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

    }// while loop
  */
}



int alert (int alert_level) {
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

  return 0;
}


#endif //_ALERT_H

