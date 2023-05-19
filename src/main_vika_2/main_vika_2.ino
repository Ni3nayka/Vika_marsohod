#include <SoftwareSerial.h>
SoftwareSerial bluetooth(A1, A0); // RX, TX

#define TEST bluetooth

#define PWM_FORWARD 10
#define PWM_BACKWARD 9
#define EN_PIN 11

#include <Servo.h>
Servo myservo;

int M = 100;

void setup(){       
  delay(500); 
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(PWM_FORWARD,OUTPUT);
  pinMode(PWM_BACKWARD,OUTPUT);
  pinMode(EN_PIN,OUTPUT);
  digitalWrite(EN_PIN,1);
  myservo.attach(8);
  //motor(M,0);
}

void loop(){ 
  if (TEST.available()) {
    char t = TEST.read();
    if      (t=='F') motor(M,0);
    else if (t=='S') motor(0,0);
    else if (t=='B') motor(-M,0);
    else if (t=='L') motor(0,1);
    else if (t=='R') motor(0,-1);
    else if (t=='G') motor(M,1);
    else if (t=='I') motor(M,-1);
    else if (t=='H') motor(-M,1);
    else if (t=='J') motor(-M,-1);
    else if (t=='0') M = 0;
    else if (t=='1') M = 10;
    else if (t=='2') M = 20;
    else if (t=='3') M = 30;
    else if (t=='4') M = 40;
    else if (t=='5') M = 50;
    else if (t=='6') M = 60;
    else if (t=='7') M = 70;
    else if (t=='8') M = 80;
    else if (t=='9') M = 90;
    else if (t=='q') M = 100;
  }
}


void motor(int speed, int angle) {
  if (angle==0) myservo.write(90);
  if (angle==1) myservo.write(130); // L
  if (angle==-1) myservo.write(60); // R
  //else if

  //speed = map(constrain(abs(speed),0,100),0,100,0,255);

  if (speed>0) {
    digitalWrite(PWM_FORWARD,1);
    digitalWrite(PWM_BACKWARD,0);
  }
  else if (speed<0) {
    digitalWrite(PWM_FORWARD,0);
    digitalWrite(PWM_BACKWARD,1);
  }
  else {
    digitalWrite(PWM_FORWARD,0);
    digitalWrite(PWM_BACKWARD,0);
  }
}
