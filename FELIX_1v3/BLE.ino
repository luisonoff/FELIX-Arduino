char code;

void readBLE(){
  while( Serial1.available() >= 4 ){
    if( Serial1.read() == '#'){ // Detectamos mensaje
      code=Serial1.read();
      if( code == 'L'){ // Mensaje de LEDRGB
        setLedRGBState(Serial1.parseInt());
      }
      if( code == 'M'){ // Mensaje de LEDRGB
        setgas2(Serial1.parseInt()); // App envia siempre entre -1000 y 1000, todos los ejes joystick.
      }
      if( code == 'm'){ // Mensaje de LEDRGB
        setgas2(-1000);
      }
      if( code == 'C'){ // Mensaje de LEDRGB
        setgas3(Serial1.parseInt());
      }
      if( code == 'c'){ // Mensaje de LEDRGB
        setgas3(0);
        setYaw(0);
      }
      if( code == 'Y'){ // Mensaje de LEDRGB
        setYaw(Serial1.parseInt());
      }
    }
  }
  //  //wait for feedback
  //  unsigned int time = 0;
  //  unsigned char num;
  //  unsigned char i;
  //
  //  //waiting for the first character with time out
  //  i = 0;
  //  while(1)
  //  {
  //    delay(50);
  //    if(Serial1.available())
  //    {
  //      recv_str[i] = char(Serial1.read());
  //      i++;
  //      break;
  //    }
  //    time++;
  //    if(time > (timeout / 50)){ 
  //      if (timeout>0)  Serial.println("timeout");
  //      return -1;
  //    }
  //  }
  //
  //  //read other characters from uart buffer to string
  //  while(Serial1.available() && (i < 100))
  //  {                                              
  //    recv_str[i] = char(Serial1.read());
  //    i++;
  //  }
  //  recv_str[i] = '\0';
  //
  //  return 0;
}

