const int LED_PIN       = 25;
const int PUSH_BUTTON_PIN = 18;

int counter = 0;


void IRAM_ATTR ToggleLed()
{
  ++counter;
  digitalWrite(LED_PIN, not digitalRead(LED_PIN));
}

void setup()
{
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(PUSH_BUTTON_PIN, ToggleLed, RISING);
}

void loop()
{
  Serial.print("Counter: ");
  Serial.println(counter);

  delay(2000);
}
