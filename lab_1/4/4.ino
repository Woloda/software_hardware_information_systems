const int ledPin = 32;

const int freq      = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup()
{
  Serial.begin(115200);
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
}

void loop()
{
  for(int dutyCycle = 0; dutyCycle <= 255; ++dutyCycle)
  {
    ledcWrite(ledChannel, dutyCycle);
    delay(5);
  }

  for(int dutyCycle = 255; dutyCycle >= 0; --dutyCycle)
  {
    ledcWrite(ledChannel, dutyCycle);
    delay(5);
  }
}
