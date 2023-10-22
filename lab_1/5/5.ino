#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp;

void setup()
{
  Serial.begin(115200);

  while(not Serial)
  {
    delay(100);
  }

  const unsigned status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  if(not status)
  {
    Serial.println("Could not find a valid BMP280 sensor, check wiring or try a different address!");

  while(true)
  {
    Serial.println("No BMP280 sensor found!");
    delay(1000);
  }
  }
  else
  {
    Serial.println("BMP280 sensor found!");
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
}

void loop()
{
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

  Serial.println();

    delay(2000);
}
