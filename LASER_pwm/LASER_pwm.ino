

void setup()   {                
  pinMode(23, OUTPUT);
  analogWriteFrequency(23, 48);
  analogWrite(23, 127);
}

void loop()                     
{
  delay(500);
}

