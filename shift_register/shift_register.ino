#define DATAPIN 2
#define CLOCKPIN 3
#define LATCHPIN 4

byte data = 0;

void setup()
{
  pinMode(DATAPIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(LATCHPIN, OUTPUT);
}

void loop()
{
  for (int i = 0; i < 4; i++)
  {
    int pin1 = i;
    int pin2 = 7 - i;
    shiftWrite(pin1, HIGH);
    shiftWrite(pin2, HIGH);
    delay(100);
    shiftWrite(pin1, LOW);
    shiftWrite(pin2, LOW);
  }
}

int getPin(int pinIn)
{
  if (pinIn < 4)
    return pinIn;
  else
    return map(pinIn, 4, 7, 7, 4);
}

void shiftWrite(int pin, boolean state)
{
  data &= ~(1 << pin);
  data |= (state << pin);
  
  //shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, data);
  
  
  for (int i = 7; i >= 0; i--)
  {
    int bit = (data >> i) & 1;
    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(DATAPIN, bit);
    digitalWrite(CLOCKPIN, HIGH);
    digitalWrite(CLOCKPIN, LOW);
  }
  
  digitalWrite(LATCHPIN, HIGH);
  digitalWrite(LATCHPIN, LOW);
}
