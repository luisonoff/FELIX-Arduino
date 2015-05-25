const int ledPinR = 11;
const int ledPinG = 8;
const int ledPinB = 7;

int ledRGBState = 0;

void setupLedRGB(){
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
}

void loopLedRGB(){
  if(ledRGBState == 0) {
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinB, LOW);
  }  
  else if(ledRGBState == 1){
    digitalWrite(ledPinR, HIGH);
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinB, LOW);
  }  
  else if(ledRGBState == 2){
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, HIGH);
    digitalWrite(ledPinB, LOW);
  } 
  else if(ledRGBState == 3){
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinB, HIGH);
  } 
  else if(ledRGBState == 4){
    digitalWrite(ledPinR, HIGH);
    digitalWrite(ledPinG, HIGH);
    digitalWrite(ledPinB, LOW);
  } 
  else if(ledRGBState == 5){
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, HIGH);
    digitalWrite(ledPinB, HIGH);
  } 
  else if(ledRGBState == 6){
    digitalWrite(ledPinR, HIGH);
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinB, HIGH);
  } 
  else if(ledRGBState == 7){
    digitalWrite(ledPinR, HIGH);
    digitalWrite(ledPinG, HIGH);
    digitalWrite(ledPinB, HIGH);
  } 
}

void setLedRGBState(int temp1){
  ledRGBState = temp1;
}
