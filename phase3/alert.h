#ifndef _ALERT_H
#define _ALERT_H

int trig = 0; // global variable for trigger
byte filename;
int m_sample = 0;


void filename_value (byte filename)
{
  switch (filename)
  {
    case 2:
      m_sample = open("/sdcard/chinAlert.wav", O_RDONLY);
      break;

    case 4:
      m_sample = open("/sdcard/imperial.wav", O_RDONLY);
      break;

    case 6:
      m_sample = open("/sdcard/initTest.wav", O_RDONLY);
      break;

    default:
      break;
  }

  filename = 0;
  Serial.println(m_sample);
  if (m_sample < 0) {
    Serial.println("Failed to load file");
  }


}



void play_audio (char* filename_pl)
{
  // Use POSIX and C standard library functions to work with files.
  // First create a file.

  ESP_LOGI(TAG, "Opening file");
  uint8_t ch;
  FILE *fp;

  fp = fopen(filename_pl, "r");
  do
  {
    if (feof(fp))
    {
      break;
    }

    dacWrite(25, fgetc(fp));
    delay(0.5);
  }
  while (1);
  dacWrite(25, 0);

  delay (500);
  // Close file 
  fclose(fp);

}




void case_statement_audio_files (char val)
{
  char filename_phonecall[25];
  
  int delay_val;
  delay_val = 200;

  switch (val) {
    
    case '0':
      {
        Serial.println ("0\n");
        strcpy(filename_phonecall,"/sdcard/0.wav");
        delay (delay_val);
        break;
      }

    case '1':
      {
        Serial.println ("1\n");
        strcpy(filename_phonecall,"/sdcard/1.wav");
        delay(delay_val);
        break;
      }

    case '2':
      {
        Serial.println ("2\n");
        strcpy(filename_phonecall,"/sdcard/2.wav");
        delay(delay_val);
        break;
      }

    case '3':
      {
        Serial.println ("3\n");
        strcpy(filename_phonecall,"/sdcard/3.wav");
        delay(delay_val);
        break;
      }

    case '4':
      {
        Serial.println ("4\n");
        strcpy(filename_phonecall,"/sdcard/4.wav");
        delay(delay_val);
        break;
      }

    case '5':
      {
        Serial.println ("5\n");
        strcpy(filename_phonecall,"/sdcard/5.wav");
        delay(delay_val);
        break;
      }

    case '6':
      {
        Serial.println ("6\n");
        strcpy(filename_phonecall,"/sdcard/6.wav");
        delay(delay_val);
        break;
      }

    case '7':
      {
        Serial.println ("7\n");
        strcpy(filename_phonecall,"/sdcard/7.wav");
        delay(delay_val);
        break;
      }

    case '8':
      {
        Serial.println ("8\n");
        strcpy(filename_phonecall,"/sdcard/8.wav");
        delay(delay_val);
        break;
      }

    case '9':
      {
        Serial.println ("9\n");
        strcpy(filename_phonecall,"/sdcard/9.wav");
        delay(delay_val);
        break;
      }
    case '-':
      {
        Serial.println ("-\n");
        strcpy(filename_phonecall,"/sdcard/neg.wav");
        delay(delay_val);
        break;
      }

    case '.':
      {
        Serial.println (".\n");
        strcpy(filename_phonecall,"/sdcard/point.wav");
        delay(delay_val);
        break;
      }

    default: /* Optional */
      Serial.println ("Can't read this shit");
      
  }// switch statement
  
  delay (200);
  play_audio (filename_phonecall);
  delay(200);
}




void easy_alert () {
  Serial.println(F("Entering Easy Alert"));
  delay (1000);
  
  Serial.println("----------------------------------------------------");
  trig = 1;
  delay (10000);
  trig = 0;
  delay (10000);
  
  // Close file 
  close(m_sample);
}


void hard_alert () {

  int i;
  Serial.println(F("Entering Hard Alert"));
  delay (1000);
  Serial.println("----------------------------------------------------");
  //sendto = "4167169452";
  sendto = "6477162554";
  headphone_jack ();
  phonecall (sendto);

  Serial.println("---------------------After the phone call 1-------------------------------");
  
  delay (12000); // Wait 10 seconds for phone call pick up
  char filename_phonecall1[27] = "/sdcard/file-8-bit.wav"; // Initial Announcement
  
  Serial.println("---------------------Playing Tien's File ------------------------------");
  play_audio (filename_phonecall1);
  delay (5000); // Wait 5 seconds before outputting the coordinates
  Serial.println("---------------------After the phone call 2-------------------------------");

  

  Serial.println ("Reading out Latitude");
  Serial.println (lat);
  for (i = 0; i < 6; i++)
  {
    case_statement_audio_files (lat[i]);
  }

  Serial.println ("Reading out Longitude");
  Serial.println (lon);
  for (i = 0; i < 6; i++)
  {
    case_statement_audio_files (lon[i]);
  }

  delay (10000);
  
}



void medium_alert () {

  while (1) {
    Serial.println(F("Entering Medium Alert"));
    delay (1000);
    Serial.println("----------------------------------------------------");
    //sendto = "4167169452";
    sendto = "6477162554";
    message = "This is a medium alert - Please reset system";
    text_message (sendto, message);
    count += 1;
    Serial.println(count);
    delay (10000);

    if (count == 1)
    {
      hard_alert();

    }

  }// while loop

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

