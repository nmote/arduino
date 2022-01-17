#define LED_COUNT 8

// digital/PWM
#define START_LED 5
#define BUZZER 3

// analog in
#define POT 0

// anything below this value is considered to not be a button press
#define MIN_POT_VALUE 15

const short MAX_STATE = 1 << LED_COUNT;
const short MIN_STATE = 0;

const int frequencyCount = 8;
const int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

int getIndex(int sensorValue)
{
  return constrain(map(sensorValue, MIN_POT_VALUE, 1023, 0, frequencyCount), 0, frequencyCount - 1);
}

void setup()
{
  pinMode(BUZZER, OUTPUT);

  for (int i = START_LED; i < START_LED + LED_COUNT; i++)
    pinMode(i, OUTPUT);
}

void writeLEDs(short state)
{
  for (short i = 0; i < LED_COUNT; i++)
  {
    if ((state >> i) & 1)
      digitalWrite(i + START_LED, HIGH);
    else
      digitalWrite(i + START_LED, LOW);
  }
}

void loop()
{
  int pot = analogRead(POT);

  if (pot > MIN_POT_VALUE)
  {
    int count = getIndex(pot);
    int hz = frequencies[count];

    int LEDState = 1 << count;

    tone(BUZZER, hz);
    writeLEDs(LEDState);
  }
  else
  {
    noTone(BUZZER);
    writeLEDs(0);
  }

  delay(20);
}
