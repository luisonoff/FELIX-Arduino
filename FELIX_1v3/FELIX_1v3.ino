const int buttonPin = 12;

long tick = 0;
int i1 = 0;

int isrFlag = 0;
int state = 0;

char recv_str[100];
char recv_str2[100];
int bleReady = 0;

void setup() 
{ 
  // LED RGB
  setupLedRGB();

  // MAIN MOTOR
  setupMotor();
  
  setupBat();

  pinMode(buttonPin, INPUT);
  // Dos lineas a continuacion para configurar PULL_DOWN, hasta que Teensyduino lo permita.
  *portConfigRegister(buttonPin) |= PORT_PCR_PE; //pull enable
  *portConfigRegister(buttonPin) &= ~PORT_PCR_PS; //pull down
  attachInterrupt(buttonPin, isrService, FALLING); //PCB v1, falling va mejor que rising.


  pinMode(2,OUTPUT);  //eSTE ES SYSTEM KEY DE BLE_1, SE PONE ALTO PARA QUE NO HAGA NADA, SI SE PONE BAJO DESCONECTA O FACTORY
  digitalWrite(2,HIGH);

  Serial.begin(115200);   //Serial port for debugging

  delay(2000); // PARA QUE ME DE TIEMPO A ABRIR CONSOLA

  Serial.println("\r\nPower on!!");

  if(setupBlueToothConnection() != 0) Serial.println("Setup failed");   //initialize Bluetooth

} 

void loop() 
{ 
  tick = micros();
  //  if(recvUSB()) sendBlueToothCommand(recv_str2);

  readBLE();

  loopMotor();
  
  loopweapon();
  
  loopBat();
  //  recvMsg(500);
  //  Serial.print("recv: ");
  //  Serial.print(recv_str);
  //  Serial.println("");
  //
  //  if(recv_str[0]=='1') state=3;
  //  else if(recv_str[0]=='2') state=5;
  //  else if(recv_str[0]=='3') state=4;
  //  else if(recv_str[0]=='4') state=7;
  //  memset(recv_str, 0, sizeof(recv_str));

  // PULSADOR
    if(isrFlag==1){
      hit();
      isrFlag = 0;
    }
  //  if(state>7) state = 0;
  //  setLedRGBState(state);
  if( i1 > 20 ){  // Divisor de 100Hz
//    sendpwm2();
//    sendpwm3();
    sendHit();
    sendBatLevel();
    sendGyro();
    i1 = 0;
  }
  i1++;

  //LED RGB
  loopLedRGB();

  delayMicroseconds(10000-(micros()-tick)); // Main loop 100Hz
}

void isrService(){
  isrFlag = 1;
}

//configure the Bluetooth through AT commands
int setupBlueToothConnection()
{
  Serial.print("Setting up Bluetooth link\r\n");

  //send command to module in different baud rate
  while(1)
  {
    delay(100);
    Serial1.begin(115200);
    delay(100);
    Serial.print("try 115200\r\n");
    if(sendBlueToothCommand("AT") == 0){
      bleReady = 1;
      break;
    }
    if(sendBlueToothCommand("AT") == 0){
      bleReady = 1;
      break;
    }  //lA PRIMERA VEZ PARECE QUE FALLA SIEMPRE

    delay(100);
    Serial1.begin(9600);
    delay(100);
    Serial.print("try 9600\r\n");
    if(sendBlueToothCommand("AT") == 0) break;
  }
  if(bleReady == 0){
    Serial.println("Configuro BLE");
    // falta comprobar que cada comando ha sido recibido y procesado, o repetir
    sendBlueToothCommand("AT+RENEW");//restore factory configurations, AFFECTS IMMEDIATELY
    sendBlueToothCommand("AT+BAUD4");//reset the module's baud rate, DOES NOT AFFECT UNTIL RESET
    sendBlueToothCommand("AT+RESET");//restart module to take effect
    Serial1.begin(115200);
    delay(1000); // necesario TRAS CAMBIO BAUD, 200MS NO ES SUFICIENTE

    sendBlueToothCommand("AT+NOTI1");//enable connect notifications
    //  sendBlueToothCommand("AT+IMME0");//DONT WORK UNTIL I TELL YOU

    sendBlueToothCommand("AT+NAMEFELIX1");//restart module to take effect

    sendBlueToothCommand("AT+RESET");//restart module to take effect
    delay(1000);//wait for module restart

    if(sendBlueToothCommand("AT") != 0) return -1;//detect if the module exists
    else{
      Serial.print("Setup complete\r\n\r\n");
      setLedRGBState(1);
    }
  }
  else{
    Serial.println("NO configuro BLE");
    setLedRGBState(1);
  }

  return 0;
}

//send command to Bluetooth and return if there is a response
int sendBlueToothCommand(char command[])
{
  Serial.print("send: ");
  Serial.print(command);
  Serial.println("");

  Serial1.print(command);
  delay(200);

  //  if(recvMsg(200) != 0) return -1;
  if(recvMsg(1000) != 0) return -1;

  Serial.print("recv: ");
  Serial.print(recv_str);
  Serial.println("");
  return 0;
}

//receive message from Bluetooth with time out
int recvMsg(unsigned int timeout)
{
  //wait for feedback
  unsigned int time = 0;
  unsigned char num;
  unsigned char i;

  //waiting for the first character with time out
  i = 0;
  while(1)
  {
    delay(50);
    if(Serial1.available())
    {
      recv_str[i] = char(Serial1.read());
      i++;
      break;
    }
    time++;
    if(time > (timeout / 50)){ 
      if (timeout>0)  Serial.println("timeout");
      return -1;
    }
  }

  //read other characters from uart buffer to string
  while(Serial1.available() && (i < 100))
  {                                              
    recv_str[i] = char(Serial1.read());
    i++;
  }
  recv_str[i] = '\0';

  return 0;
}

int recvUSB()
{
  unsigned char num;
  unsigned char i;

  //waiting for the first character with time out
  i = 0;
  if(Serial.available()){

    while(Serial.available())
    {
      recv_str2[i] = char(Serial.read());
      i++;
    }

    recv_str2[i] = '\0';

    return 1;
  }
  else return 0;
}










