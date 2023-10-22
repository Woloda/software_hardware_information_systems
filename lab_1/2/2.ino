const int LIGHT_SENSOR_PIN = 36;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  int analog_value = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Analog Value = ");
  Serial.print(analog_value);

  if (analog_value < 40)
  {
    Serial.println(" => Dark");
  } else if (analog_value < 800)
  {
    Serial.println(" => Dim");
  } else if (analog_value < 2000)
  {
    Serial.println(" => Light");
  } else if (analog_value < 3200)
  {
    Serial.println(" => Bright");
  } else
  {
    Serial.println(" => Very bright");
  }

  delay(500);
}
