int hitState = 0;
unsigned long millisHit = 0;

void loopweapon(){
  if( millis() - millisHit > 3000 ) hitState = 0;
}

void hit(){
  hitState = 1;
  millisHit = millis();
}

void sendHit(){
  if( hitState == 1){
    Serial1.print("#A");
    Serial1.print(1);
    Serial1.println(';');
  }
  else{
    Serial1.print("#A");
    Serial1.print(0);
    Serial1.println(';');
  }
}

