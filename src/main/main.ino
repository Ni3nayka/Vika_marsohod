// FLEX_PAVUK 4825

#include <SoftwareSerial.h>
SoftwareSerial bluetooth(A1, A0); // RX, TX

#include <AFMotor.h>

#define TEST bluetooth

int M = 100;

AF_DCMotor motor_left(1);
AF_DCMotor motor_right(2);

void setup(){       
  delay(500); 
  Serial.begin(9600);
  bluetooth.begin(9600);
  motor_left.run(RELEASE);
  motor_right.run(RELEASE);
}

void loop(){ 
  if (TEST.available()) {
    char t = TEST.read();
    if (t=='F') motor(M,M);
    else if (t=='S') motor(0,0);
    else if (t=='B') motor(-M,-M);
    else if (t=='L') motor(-M,M);
    else if (t=='R') motor(M,-M);
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

void motor(int a, int b) {
  if      (a==0) motor_left.run(RELEASE);
  else if (a>0)  motor_left.run(FORWARD);
  else           motor_left.run(BACKWARD);
  motor_left.setSpeed( map(constrain(abs(a),0,100),0,100,0,255) );
  
  if      (b==0) motor_right.run(RELEASE);
  else if (b>0)  motor_right.run(FORWARD);
  else           motor_right.run(BACKWARD);
  motor_right.setSpeed( map(constrain(abs(b),0,100),0,100,0,255) );
}
