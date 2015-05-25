const int batPin = A14;
int adc1 = 0;
float batV = 0;

// Teoricamente 1.3*Vadc = Vreal

void setupBat(){
  pinMode(batPin, INPUT);
}

void loopBat(){
  adc1 = analogRead(batPin);
  batV = 1.3*3.3*adc1/1023;
}

void sendBatLevel(){
  Serial1.print("#B");
  Serial1.print(batV,2);
  Serial1.println(';');
}
