#define button1 2
#define button2 3

// escape
#define key1 177
// ctrl
#define key2 128

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  Keyboard.begin();
}

bool is_pressed(int key) {
  return !digitalRead(key);
}

bool press_key(int pin, int key) {
  if (is_pressed(pin)) {
    Keyboard.press(key);
  } else {
    Keyboard.release(key);
  }
}

void loop() {
  press_key(button1, key1);
  press_key(button2, key2);
}
