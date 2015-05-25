unsigned long temp, temp2, temp3,adc,inicio;

void setup()
{
  analogReadResolution(12);
  analogReadAveraging(1);
  Serial.begin(115200);
  delay(250);

}

void loop()
{
  if(Serial.available()>0){
    if(Serial.read()=='a'){
      Serial.println("Empieza medida");
      inicio=millis();
      temp=millis();
      while(millis()-inicio<3000){
        temp2 = millis()-temp;
        delay(5-temp2);
        temp3 = millis()-temp;
        temp = millis();
        adc=analogRead(14);

        Serial.println(adc);
      }
      Serial.println("Fin medida");
    }
    while(Serial.available()>0) Serial.read();
  }
}



