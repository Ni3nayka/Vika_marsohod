// https://alexgyver.ru/lessons/arduino-rgb/

int RGB_counter = 0;
#define RGB_one_krug 500
#define RGB_1_3_krug int(RGB_one_krug/3)

void setup(){       
  delay(500); 
  Serial.begin(9600);
}

void loop(){ 
  RGB_koleso();
}

void RGB_koleso() {
  if (RGB_counter>=RGB_one_krug) RGB_counter = 0;
  RGB(RGB_func(RGB_counter),RGB_func(RGB_counter+RGB_1_3_krug),RGB_func(RGB_counter+RGB_1_3_krug*2));
  RGB_counter++;
}

int RGB_func(int r) {
  if (r>RGB_one_krug) r-=RGB_one_krug;
  return constrain( (abs(r-RGB_1_3_krug)*(-1)+RGB_1_3_krug)*200.0/RGB_1_3_krug ,0,100);
}

void RGB(int r, int g, int b) {
  Serial.print(b);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.print(r);
  Serial.println();
}
