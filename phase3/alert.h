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
  
  filename =0;
  Serial.println(m_sample);
  if (m_sample < 0) {
    Serial.println("Failed to load file");
  }


}



void play_audio (char* filename)
{
  // Use POSIX and C standard library functions to work with files.
  // First create a file.

  ESP_LOGI(TAG, "Opening file");
  uint8_t ch;
  FILE *fp;

  fp = fopen(filename, "r");
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
}




void case_statement_audio_files (char val)
{

  int delay_val;
  delay_val = 1000;
  
  switch (val) {
    case '0':
      {
        Serial.println ("0\n");
        char filename_phonecall[27] = "/sdcard/0.wav";
        play_audio (filename_phonecall);
        delay (2000);
        break;
      }

    case '1':
      {
        Serial.println ("1\n");
        char filename_phonecall[27] = "/sdcard/1.wav";
        play_audio (filename_phonecall);
        delay(2000);
        break;
      }

    case '2':
      {
        Serial.println ("2\n");
        char filename_phonecall[27] = "/sdcard/2.wav";
        play_audio (filename_phonecall);
        delay(2000);
        break;
      }

    case '3':
      {
        Serial.println ("3\n");
        char filename_phonecall[27] = "/sdcard/3.wav";
        play_audio (filename_phonecall);
        delay(2000);
        break;
      }

    case '4':
      {
        Serial.println ("4\n");
        char filename_phonecall[27] = "/sdcard/4.wav";
        play_audio (filename_phonecall);
        delay(2000);
        break;
      }

    case '5':
      {
        Serial.println ("5\n");
        char filename_phonecall[27] = "/sdcard/5.wav";
        play_audio (filename_phonecall);
        delay(2000);
        break;
      }

    case '6':
      {
        Serial.println ("6\n");
        char filename_phonecall[27] = "/sdcard/6.wav";
        play_audio (filename_phonecall);
        delay(2000);
        break; 
      }

    case '7':
      {
        Serial.println ("7\n");
        char filename_phonecall[27] = "/sdcard/7.wav";
        play_audio (filename_phonecall);
        delay(2000);
        break;
      }

    case '8':
      {
        Serial.println ("8\n");
        char filename_phonecall[27] = "/sdcard/8.wav";
        play_audio (filename_phonecall);
        delay(2000);
        break;
      }

    case '9':
      {
        Serial.println ("9\n");
        char filename_phonecall[27] = "/sdcard/9.wav";
        play_audio (filename_phonecall);
        delay(2000);
        break;
      }
    case '-':
      {
        Serial.println ("-\n");
        char filename_phonecall[27] = "/sdcard/-.wav";
        play_audio (filename_phonecall);
        delay(2000);
        break;
      }

    case '.':
      {
        Serial.println (".\n");
        char filename_phonecall[27] = "/sdcard/point.wav";
        play_audio (filename_phonecall);
        delay(2000);
        break;
      }

    default: /* Optional */
      Serial.println ("Can't read this shit");
  }// switch statement

  yield();
  delay(1);
}







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

  int i;

  Serial.println(F("Entering Hard Alert"));
  delay (1000);
  Serial.println("----------------------------------------------------");
  sendto = "4167169452";
  headphone_jack ();
  phonecall (sendto);

  delay (10000); // Wait 10 seconds for phone call pick up
  char filename_phonecall1[27] = "/sdcard/initTest.wav"; // Initial Announcement
  play_audio (filename_phonecall1);
  
  Serial.println("---------------------After the phone call-------------------------------");
  
  delay (5000); // Wait 10 seconds before outputting the coordinates
  Serial.println ("Reading out Latitude");
  for (i = 0; i < 6; i++)
  {
    case_statement_audio_files (lat[i]);
    delay (100);
  }

  Serial.println ("Reading out Latitude");
  for (i = 0; i < 6; i++)
  {
    case_statement_audio_files (lon[i]);
    delay (100);
  }

  delay (10000);
  yield ();
  delay(1);
}



void medium_alert () {

  while (1) {
    Serial.println(F("Entering Medium Alert"));
    delay (1000);
    Serial.println("----------------------------------------------------");
    sendto = "4167169452";
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

