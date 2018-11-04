#include <Servo.h>
#include <Time.h>
int servoPin = 5;
 
Servo servo;  

int green = 9;
int red = 7;
int blue = 6;
int white = 8;

int bg = LOW;
int br = LOW;
int bb = LOW;
int bw = LOW;
int cur[10]={0,0,0,0,0,0,0,0,0,0};
int BNum = 0;
int LNum = 0;
double LTime = 0;
double TSSE = 0;
double TSSP = 0;
int Error = 0;

void setup() {
  servo.attach(5);
  servo.write(0);
  Serial.begin(9600);  
  pinMode(green, INPUT);
  pinMode(red, INPUT);
  pinMode(blue, INPUT);
  pinMode(white, INPUT);
}

void loop(){
  bg = digitalRead(green);
  br = digitalRead(red);
  bb = digitalRead(blue);
  bw = digitalRead(white);
  
  if (bg == HIGH and BNum == 0){
    BNum++;
    LNum = 0;
    TSSP = millis();
  }
  else if (br == HIGH and BNum == 1 || bb == HIGH and BNum == 2){
    BNum++;
  }
  else if (bw == HIGH and BNum == 3){
    BNum++;
    delay(500);
    servo.write(180); 
  }
  else if (br == HIGH and BNum != 1 || bb == HIGH and BNum != 2 || bg == HIGH and BNum != 0 || bw == HIGH and BNum != 3){
    Error++;
    if (Error >= 3){
      delay(10000)
    }
  }
  Serial.println(BNum);
  TSSE = millis();
  LTime = (TSSE-TSSP);
  Serial.println(LTime);
  if (BNum != 0 and LTime >= 10000){
    BNum = 0;
  }
}
