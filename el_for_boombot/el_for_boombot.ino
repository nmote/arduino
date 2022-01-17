#define NUM_LIGHTS 3
#define START_PIN 4
#define ALWAYS_ON 3

#define MIN_STATE 'a'
#define MAX_STATE 'd'
#define START_STATE MIN_STATE

#define DELAY_TIME 300

void setup() {
  for (int i = 0; i < NUM_LIGHTS; i++) {
    pinMode(START_PIN + i, OUTPUT);
  }
  pinMode(ALWAYS_ON, OUTPUT);
  digitalWrite(ALWAYS_ON, HIGH);
  Serial.begin(9600);
}

void loop() {
  static int state = START_STATE;
  int result = Serial.read();
  if (result >= MIN_STATE && result <= MAX_STATE) {
    state = result;
  }
  
  switch (state) {
    case 'a':
      // do nothing
      break;
    case 'b':
      blinkPins(0b111);
      delay(DELAY_TIME);
      break;
    case 'c':
      blinkPins(0b001);
      blinkPins(0b010);
      blinkPins(0b100);
      break;
    case 'd':
      setPins(0b111, HIGH);
      break;
    default:
      // do nothing
      break;
  }
}

void blinkPins(int pins) {
  setPins(pins, HIGH);
  delay(DELAY_TIME);
  setPins(pins, LOW);
}

void setPins(int pins, int setting) {
  for (int i = 0; i < NUM_LIGHTS; i++) {
    if (hasOneBitAt(pins, i)) {
      digitalWrite(i + START_PIN, setting);
    }
  }
}

int hasOneBitAt(int n, int pos) {
  return n >> pos & 1;
}
