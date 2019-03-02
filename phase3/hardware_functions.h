#ifndef _HARDWARE_FUNCTIONS_H
#define _HARDWARE_FUNCTIONS_H

#include "DHT.h"
#define DHT1PIN 13
#define DHTPIN 32     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#include "driver/adc.h"



DHT dht1(DHT1PIN, DHTTYPE);
DHT dht2(DHTPIN, DHTTYPE);


void PostureAlert(int a, int b, int c, int d) {
  int alert_level = 0;
  
  if ((a > 2000) && (b > 2000) && ( c >= 0) && (d >= 0))
    Serial.println("Normal Posture");
  if ((a > 1.8 * b) || (a > 1.8 * b) && (c >= 0) && (d >= 0))
    {
      Serial.println ("Lean Right Posture");
      filename_value (4);
      alert_level = 1;
    }
      
  if ((b > 1.8 * a) || (b > 1.8 * a) && (c >= 0) && (d >= 0))
    Serial.println ("Lean Left Posture");
  if ((c >= 2500) && (a < 200) && (b < 200))
    {
      Serial.println("Chin to Chest Posture");

    }
  if ((d > 0) && (a < 200) && (b < 200) && (c < 200))
    {
      Serial.println ("Leaning Forward Posture");
    }

  alert_level = alert (alert_level);
  
}

void GasAlert (int e) {
  int alert_level = 0;
  if (e > 1000)
  {
    Serial.println ("CO levels above safety limit"); 
    //filename = 4;
    //alert_level = 1;
  } 
  if (e < 500)
    Serial.println ("CO levels are Normal");
  if ((e > 500) && (e < 1000))
    Serial.println ("CO levels are slightly elevated");

  alert_level = alert (alert_level);

}
void WetnessAlert (int g, int f) {
  if (g >= 15 + f)
    Serial.println ("Baby is wet");
  if (g <= 15 + f)
    Serial.println ("Baby is dry");
}


void sensor_act_begin ()
{
  pinMode(LED_BUILTIN, OUTPUT);
  dht1.begin();
  dht2.begin();
}


//Task1code: blinks an LED every 1000 ms
void ReadSensCode() {

  int sens1 = A2;
  int sens2 = A3;
  int sens3 = A9;
  int sens4 = A4;
  //int gasSen = A4;

  //pinMode(A5, INPUT);

  int sens1Value = 0;
  int sens2Value = 0;
  int sens3Value = 0;
  int sens4Value = 0;
  int gasSenVal = 0;
  
  int sensArr[5] = {sens1Value, sens2Value, sens3Value, sens4Value, gasSenVal};

  for (;;) {
    
    sens1Value = analogRead(sens1);    //A2
    sens2Value = analogRead(sens2);    //A3
    sens3Value = analogRead(sens3);    //A4
    sens4Value = analogRead(sens4);     //A5
    //gasSenVal = analogRead(gasSen);     //A7
    adc2_get_raw(ADC2_CHANNEL_7, ADC_WIDTH_12Bit, &gasSenVal);
    
    Serial.println ("This is the test to read values");
    Serial.println (sens1Value);
    Serial.println (sens2Value);
    Serial.println (sens3Value);
    Serial.println (sens4Value);
    Serial.println (gasSenVal);

    

    PostureAlert(sens1Value, sens3Value, sens4Value, sens2Value);
    GasAlert(gasSenVal);

    sensArr[0] = map(sens1Value, 0, 4095, 0, 4095);
    sensArr[1] = map(sens2Value, 0, 4095, 0, 4095);
    sensArr[2] = map(sens3Value, 0, 4095, 0, 4095);
    sensArr[3] = map(sens4Value, 0, 4095, 0, 4095);
    sensArr[4] = map(gasSenVal, 0, 4095, 0, 4095);

    Serial.println("FSR 1      FSR 2      FSR 3      FSR 4       Gas");

    for (int i = 0; i < 5; i++) {
      Serial.print(sensArr[i]);
      Serial.print("          ");
    }
    Serial.print("\n");
    delay(900);

  }
}

void sensor_act_main_obtain ()

{
  
// Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();

  WetnessAlert (h1,h2);
 
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t1) || isnan(h1)) {
    Serial.println("Failed to read from DHT #1");
  } else {
    Serial.print("Humidity 1: "); 
    Serial.print(h1);
    Serial.print(" %\t");
    Serial.print("Temperature 1: "); 
    Serial.print(t1);
    Serial.println(" *C");
  }
  if (isnan(t2) || isnan(h2)) {
    Serial.println("Failed to read from DHT #2");
  } else {
    Serial.print("Humidity 2: "); 
    Serial.print(h2);
    Serial.print(" %\t");
    Serial.print("Temperature 2: "); 
    Serial.print(t2);
    Serial.println(" *C");
  }
  Serial.println();
}




#endif //_HARDWARE_FUNCTIONS_H
