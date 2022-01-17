// digital/PWM
#define BUZZER 3


#define DELAY 1000
#define BUZZ_DURATION 30
#define HIGH_TONE 1000
#define LOW_TONE 900

void setup()
{
  pinMode(BUZZER, OUTPUT);
}

void loop()
{
  tone(BUZZER, HIGH_TONE, BUZZ_DURATION);
  delay(DELAY);
  tone(BUZZER, LOW_TONE, BUZZ_DURATION);
  delay(DELAY);
}
