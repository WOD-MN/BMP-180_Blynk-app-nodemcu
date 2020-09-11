//BMP-180 IN BLYNK APPLICATION!!!!

#include <Adafruit_Sensor.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
#define I2C_SCL 12
#define I2C_SDA 13

float dst,bt,bp,ba;
char dstmp[20],btmp[20],bprs[20],balt[20];
bool bmp085_present=true;

char auth[]="********************************"; //Blynk Auth Code
char ssid[] = "********";                      // Wifi SSID
char pass[] = "*******";                      // WIFI PASSWORD
BlynkTimer timer;

void sendSensor()
{

  if (!bmp.begin()) 
  {
           Serial.println("Sensor Not Found !!");
              while (1) {}
        }

float bp =  bmp.readPressure()/100;
int ba =  bmp.readAltitude();
float bt =  bmp.readTemperature();
float dst = bmp.readSealevelPressure()/100;

Blynk.virtualWrite(V10, bp);
Blynk.virtualWrite(V11, ba);
Blynk.virtualWrite(V12, bt);
Blynk.virtualWrite(V13, dst);


}


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Wire.begin(I2C_SDA, I2C_SCL);
  delay(10);
  timer.setInterval(3000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
