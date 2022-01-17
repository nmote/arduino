/*
 * hardware:
 *
 * MSGEQ7 audio equalizer chip, connected to an amplified electret microphone
 *
 * EL Escudo Dos, with EL wire
 *
 */

#define WIRE_COUNT 5

// digital
#define START_WIRE 3

#define STROBE 13
#define RESET 12

// analog in
#define AUDIO 0

void setup()
{
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);

  resetEq();

  for (int i = START_WIRE; i < START_WIRE + WIRE_COUNT; i++)
    pinMode(i, OUTPUT);
}

void loop()
{
  static int loops = 0;
  static int recentMax = 0;

  int volumeLevel = getSmoothedVolume();

  if (volumeLevel > recentMax)
  {
    recentMax = volumeLevel;
    loops = 0;
  }
  else
  {
    loops++;
  }

  int wires = constrain(map(recentMax, 2, 19, 0, 4), 0, 4);
  // always light the bottom wire
  int state = 1;
  for (int i = 1; i < wires + 1; i++)
  {
    state |= (1 << i);
  }
  writePins(state);

  if (loops >= 10)
  {
    recentMax--;
  }

  // note: if you use Serial for debugging, reduce this delay (serial takes a
  // long time)
  delay(15);
}

void writePins(short state)
{
  for (short i = 0; i < WIRE_COUNT; i++)
  {
    if ((state >> i) & 1)
      digitalWrite(i + START_WIRE, HIGH);
    else
      digitalWrite(i + START_WIRE, LOW);
  }
}

// returns volume level between 0 and 20.
//
// This is a sliding window, the top and bottom of which depend on the recent
// noise level
int getSmoothedVolume()
{
  // used to adjust the window every few loops
  static int loopCount = 0;
  // manipulated to approach the recent median sound level
  static int baseline = 0;
  // the recent max, declining slowly
  static int max = 0;

  // 0 to 1023
  int volume = getVolumeLevel();

  if (volume > max)
    max = volume;

  int retVal;

  if (max == 0)
    retVal = 0;
  else
    retVal = constrain(map(volume, baseline, max, 0, 20), 0, 20);

  loopCount++;
  if (loopCount >= 2)
  {
    max--;

    if (volume > baseline)
      baseline++;
    else
      baseline--;
    loopCount = 0;

    // keep the window at least 300 in width
    if (max - baseline < 300)
      max = baseline + 300;
  }

  return retVal;
}

// returns the volume level from 0 to 1023
int getVolumeLevel()
{
  int audio[7];

  getAudioData(audio);

  unsigned int sum = 0;
  byte divisor = 0;

  const byte min_light_weight = 3;

  // weight bass heavily
  for (int i = 0; i < min_light_weight; i++)
  {
    sum += 2*audio[i];
    divisor += 2;
  }
  for (int i = min_light_weight; i < 7; i++)
  {
    sum += audio[i];
    divisor++;
  }

  return sum / divisor;
}

// this resets the MSGEQ7, so that we can be sure it's output is the lowest
// channel
void resetEq()
{
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);
  delay(1);
}

/* gets audio intensity data and puts it in arr. arr's size must be at least 7
 * or bad shit will happen.
 *
 * gives 10 bit intensity data, with intensities measured at the following
 * frequencies (in order).
 *
 * 63 Hz, 160 Hz, 400 Hz, 1 kHz, 2.5 kHz, 6.25 kHz, 16 kHz */
void getAudioData(int *arr)
{
  for (int i = 0; i < 7; i++)
  {
    // average for greater accuracy
    arr[i] = (analogRead(AUDIO) + analogRead(AUDIO)) >> 1;
    // strobe to move to the next channel
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}
