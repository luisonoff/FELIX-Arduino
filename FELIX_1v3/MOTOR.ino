const int motor1Pin = 20;
const int motor2Pin = 21;
const int motor3PinF = 6;
const int motor3PinR = 5;

float gyro = 1.1; // Para compensar Z drift, positivo lo hace girar horario
float yawU2 = 1;

int gas2 = -1000;
int pwm1 = 0;
int pwm2 = 0;

int gas3 = 0;
int pwm3 = 0;

int yawU = 0;

void setupMotor(){
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(motor3PinF, OUTPUT);
  pinMode(motor3PinR, OUTPUT);
}

void loopMotor(){
  //Gyro manual adjusting
//  if( yawU < -500 ) gyro -= 0.001;
//  if( yawU > 500 ) gyro += 0.001;
  yawU2 = 0.15*yawU/1000 + 1;
  if (abs(yawU)<100) yawU2 = 1;
  
  pwm1 = yawU2*gyro*255*(gas2+1000)/2000;
  pwm2 = (2-yawU2)*(2-gyro)*255*(gas2+1000)/2000;  // Valido si gyro [0,2]
  
  if( gas2 < -700 ){
    pwm1 = 0;
    pwm2 = 0;
  }
  if( pwm1 > 255 ) pwm1 = 255;
  if( pwm2 > 255 ) pwm2 = 255;
  
  analogWrite(motor1Pin, pwm1);
  analogWrite(motor2Pin, pwm2);

  pwm3 = gas3*255/1000;
  if (abs(gas3)<200) pwm3 = 0;
  if( pwm3 > 255 ) pwm3 = 255;
  
  if ( pwm3 >= 0){
    analogWrite(motor3PinF, pwm3);
    analogWrite(motor3PinR, 0);
  }
  else{
    analogWrite(motor3PinF, 0);
    analogWrite(motor3PinR, abs(pwm3));
  }
}

void setgas2(int temp1){
  gas2 = temp1;
}

void setgas3(int temp1){
  gas3 = temp1;
}

void setYaw(int temp1){
  yawU = temp1;
}

void sendpwm2(){
  Serial1.print("#M");
  Serial1.print(pwm2);
  Serial1.println(';');
}

void sendpwm3(){
  Serial1.print("#C");
  Serial1.print(pwm3);
  Serial1.println(';');
}

void sendGyro(){
  Serial1.print("#Y");
  Serial1.print(gyro,2);
  Serial1.println(';');
}

