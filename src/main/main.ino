// FLEX_PAVUK 4825

#include <SoftwareSerial.h>
SoftwareSerial bluetooth(A1, A0); // RX, TX

#include <AFMotor.h>

#define TEST bluetooth

// RGB
#define LED_R 5
#define LED_G 10
#define LED_B 9
long int RGB_counter = 0;
#define RGB_one_krug 10000
#define RGB_1_3_krug int(RGB_one_krug/3)
bool RGB_flag = false;

#define DNO_LED A2
#define ZUMMER 2

int M = 100;
bool not_go = true;

AF_DCMotor motor_left(1);
AF_DCMotor motor_right(2);

void setup(){       
  delay(500); 
  Serial.begin(9600);
  bluetooth.begin(9600);
  motor_left.run(RELEASE);
  motor_right.run(RELEASE);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);
  pinMode(DNO_LED,OUTPUT);
  pinMode(ZUMMER,OUTPUT);
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
    else if (t=='W') RGB_flag = true;
    else if (t=='w') RGB_flag = false;
    else if (t=='U') dno(1);
    else if (t=='u') dno(0);
    else if (t=='X') dno(1); // переделать на мигалку (аварийка)
    else if (t=='x') dno(0);
    else if (t=='V') zum(1);
    else if (t=='v') zum(0);
    else if (t=='D') {
      motor(0,0);
      zum(0);
      dno(0);
    }
  }
  
  if (RGB_flag) {
    if (not_go) RGB_counter++;
    else RGB_counter = RGB_1_3_krug+M*(RGB_1_3_krug*2/100.0);
    RGB_koleso();
  }
  else RGB(0,0,0);
}

void zum(bool s) {
  digitalWrite(ZUMMER,s);
}

void dno(bool s) {
  digitalWrite(DNO_LED,s);
}


void RGB_koleso() {
  if (RGB_counter>=RGB_one_krug) RGB_counter = 0;
  RGB(RGB_func(RGB_counter),RGB_func(RGB_counter+RGB_1_3_krug),RGB_func(RGB_counter+RGB_1_3_krug*2));
}

int RGB_func(int r) {
  if (r>RGB_one_krug) r-=RGB_one_krug;
  return constrain( (abs(r-RGB_1_3_krug)*(-1)+RGB_1_3_krug)*200.0/RGB_1_3_krug ,0,100);
}

void RGB(int r, int g, int b) {
  analogWrite(LED_R,translate(r));
  analogWrite(LED_G,translate(g));
  analogWrite(LED_B,translate(b));
}

void motor(int a, int b) {
  if (a==0 && b==0) not_go = true;
  else not_go = false;
  
  if      (a==0) motor_left.run(RELEASE);
  else if (a>0)  motor_left.run(FORWARD);
  else           motor_left.run(BACKWARD);
  motor_left.setSpeed( translate(a) );
  
  if      (b==0) motor_right.run(RELEASE);
  else if (b>0)  motor_right.run(FORWARD);
  else           motor_right.run(BACKWARD);
  motor_right.setSpeed( translate(b) );
}

int translate(int a) {
  return map(constrain(abs(a),0,100),0,100,0,255);
}
