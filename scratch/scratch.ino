#define STARTPIN 2
#define ENDPIN 11
#define NUMLEDS (ENDPIN - STARTPIN + 1)

void setup() {
  Serial.begin(9600);
  for (int i = STARTPIN; i <= ENDPIN; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  int num = getnum();
  int pin = num + STARTPIN;
  for (int i = STARTPIN; i <= ENDPIN; i++) {
    if (pin == i) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
}

int getnum() {
  int raw = analogRead(0);
  Serial.println(raw);

  if (raw > 600)
    return -1;
  return constrain(map(raw, 0, 425, 0, NUMLEDS - 1), 0, NUMLEDS - 1);
}
