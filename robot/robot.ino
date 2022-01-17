// digital/PWM
#define MOTOR 9
#define LED 7
#define SERVO 5
#define BUZZER 11

const int songLength = 18;
const char notes[] = "cdfda ag cdfdg gf ";

const int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};

const int tempo = 150;

// analog:
#define LIGHT_SENSOR 0

#include <Servo.h>

volatile int left = 0;
volatile int right = 1023;

boolean songPlayed = false;

Servo steering;

void setup()
{
  Serial.begin(9600);
  
  pinMode(MOTOR, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  steering.attach(SERVO);
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(0, calLeft, FALLING);
  attachInterrupt(1, calRight, FALLING);
  
  // give some time to calibrate
  digitalWrite(LED, HIGH);
  delay(6000);
  digitalWrite(LED, LOW);
  detachInterrupt(0);
  detachInterrupt(1);
  
  go();
}

void calLeft()
{
  int sensorValue = analogRead(LIGHT_SENSOR);
  left = sensorValue;
}

void calRight()
{
  int sensorValue = analogRead(LIGHT_SENSOR);
  right = sensorValue;
}

void straight()
{
  steering.write(90);
}

void turn(int deg)
{
  deg = 90 - deg;
  deg = constrain(deg, 30, 150);
  steering.write(deg);
}

void go()
{
  digitalWrite(MOTOR, HIGH);
}

void stop()
{
  digitalWrite(MOTOR, LOW);
}

void updateDirection()
{
  int sensorValue = analogRead(LIGHT_SENSOR);
  int deg = map(sensorValue, left, right, -60, 60);
  turn(deg);
}

void song()
{
  for (int i = 0; i < songLength; i++)
  {
    int duration = beats[i] * tempo;
    
    if (notes[i] == ' ')
      delay(duration);
    else
    {
      tone(BUZZER, frequency(notes[i]), duration);
      delay(duration);
    }
    delay(tempo/10);
  }
}

int frequency(char note)
{
   int numNotes = 8;
   char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
   int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};
   for (int i = 0; i < numNotes; i++)
   {
     if (names[i] == note)
       return frequencies[i];
   }
   return 0;
}

void loop()
{
  if (songPlayed)
    return;
  if (millis() > 30000l)
  {
    stop();
    song();
    songPlayed = true;
  }
  else
    updateDirection();
  delay(200);
}
