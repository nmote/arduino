#define START_LED 8
#define LED_COUNT 5


const short MAX_STATE = 1 << LED_COUNT;
const short MIN_STATE = 0;

volatile short state = 0;

volatile int on = false;

volatile unsigned long lastButtonPress = 0l;

void setup()
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  
  for (int i = START_LED; i < START_LED + LED_COUNT; i++)
    pinMode(i, OUTPUT);
  
  attachInterrupt(0, down, FALLING);
  attachInterrupt(1, up, FALLING);
}

void up()
{
  add(1);
}

void down()
{
  add(-1);
}

void add(short i)
{
  unsigned long currentTime = millis();
  if (currentTime - lastButtonPress < 300)
    return;
  
  lastButtonPress = currentTime;
  
  state += i;
  state = state % MAX_STATE;
  
  if(on)
    writeLEDs(state);
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
  int sensorValue = analogRead(0);
  
  writeLEDs(state);
  on = true;
  delay(sensorValue);
  writeLEDs(0);
  on = false;
  delay(sensorValue);
}
