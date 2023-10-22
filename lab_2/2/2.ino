const int LIGHT_SENSOR_PIN = 36;

hw_timer_t *my_timer0 = NULL;
hw_timer_t *my_timer1 = NULL;
hw_timer_t *my_timer2 = NULL;
hw_timer_t *my_timer3 = NULL;

bool bool_timer0 = false;
bool bool_timer1 = false;
bool bool_timer2 = false;
bool bool_timer3 = false;

void IRAM_ATTR OnTimer0();
void IRAM_ATTR OnTimer1();
void IRAM_ATTR OnTimer2();
void IRAM_ATTR OnTimer3();

void SetupTimer0();
void SetupTimer1();
void SetupTimer2();
void SetupTimer3();

void SetupMultipleTimer();

void HandleTimer0();
void HandleTimer1();
void HandleTimer2();
void HandleTimer3();

void HandleMultipleTimer();

void setup()
{
  Serial.begin(115200);
  SetupMultipleTimer();
}

void loop()
{
  HandleMultipleTimer();
}

void IRAM_ATTR OnTimer0()
{
  bool_timer0 = true;
}

void IRAM_ATTR OnTimer1()
{
  bool_timer1 = true;
}

void IRAM_ATTR OnTimer2()
{
  bool_timer2 = true;
}

void IRAM_ATTR OnTimer3()
{
  bool_timer3 = true;
}

void SetupTimer0()
{
  my_timer0 = timerBegin(0, 80, true);
  timerAttachInterrupt(my_timer0, &OnTimer0, true);
  timerAlarmWrite(my_timer0, 1000000, true);
  timerAlarmEnable(my_timer0);
}

void SetupTimer1()
{
  my_timer1 = timerBegin(1, 80, true);
  timerAttachInterrupt(my_timer1, &OnTimer1, true);
  timerAlarmWrite(my_timer1, 2000000, true);
  timerAlarmEnable(my_timer1);
}

void SetupTimer2()
{
  my_timer2 = timerBegin(2, 80, true);
  timerAttachInterrupt(my_timer2, &OnTimer2, true);
  timerAlarmWrite(my_timer2, 3000000, true);
  timerAlarmEnable(my_timer2);
}

void SetupTimer3()
{
  my_timer3 = timerBegin(3, 80, true);
  timerAttachInterrupt(my_timer3, &OnTimer3, true);
  timerAlarmWrite(my_timer3, 4000000, true);
  timerAlarmEnable(my_timer3);
}

void SetupMultipleTimer()
{
  SetupTimer0();
  SetupTimer1();
  SetupTimer2();
  SetupTimer3();
}

void HandleTimer0()
{
  if(bool_timer0)
  {
    int analog_value = analogRead(LIGHT_SENSOR_PIN);
    Serial.print("Analog Value0 = ");
    Serial.println(analog_value);

    bool_timer0 = false;
  }
}

void HandleTimer1()
{
  if(bool_timer1)
  {
    int analog_value = analogRead(LIGHT_SENSOR_PIN);
    Serial.print("Analog Value1 = ");
    Serial.println(analog_value);

    bool_timer1 = false;
  }
}

void HandleTimer2()
{
  if(bool_timer2)
  {
    int analog_value = analogRead(LIGHT_SENSOR_PIN);
    Serial.print("Analog Value2 = ");
    Serial.println(analog_value);

    bool_timer2 = false;
  }
}

void HandleTimer3()
{
  if(bool_timer3)
  {
    int analog_value = analogRead(LIGHT_SENSOR_PIN);
    Serial.print("Analog Value3 = ");
    Serial.println(analog_value);

    bool_timer3 = false;
  }
}

void HandleMultipleTimer()
{
  HandleTimer0();
  HandleTimer1();
  HandleTimer2();
  HandleTimer3();
}
