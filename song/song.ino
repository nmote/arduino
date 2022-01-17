#define buzzerPin 11

const int songLength = 18;
const char notes[] = "cdfda ag cdfdg gf ";

const int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};

const int tempo = 150;

void setup()
{
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  for (int i = 0; i < songLength; i++)
  {
    int duration = beats[i] * tempo;
    
    if (notes[i] == ' ')
      delay(duration);
    else
    {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);
    }
    delay(tempo/10);
  }
  
  while (true) { }
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
