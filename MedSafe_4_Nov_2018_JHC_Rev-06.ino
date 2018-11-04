#include <Servo.h>
#include <Time.h>
int servoPin = 5;
 
Servo servo;  

int green = 9;
int red = 7;
int blue = 6;
int white = 8;
int RedLED = 4;
int GreenLED = 3;

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
  servo.write(180);
  Serial.begin(9600);  
  pinMode(green, INPUT);
  pinMode(red, INPUT);
  pinMode(blue, INPUT);
  pinMode(white, INPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
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
    digitalWrite(GreenLED, HIGH);
    delay(1000);
    digitalWrite(GreenLED, LOW);
  }
  else if (br == HIGH and BNum == 1){
    BNum++;
    digitalWrite(GreenLED, HIGH);
    delay(1000);
    digitalWrite(GreenLED, LOW);    
  }
  else if (bb == HIGH and BNum == 2){
    BNum++;
    delay(500);
    servo.write(90); 
    Error = 0;
    digitalWrite(GreenLED, HIGH);
    delay(4000);
    digitalWrite(GreenLED, LOW);  
  }
  else if (bw == HIGH){
    BNum=0;
    servo.write(180);     
  }
  else if (br == HIGH and BNum != 1 || bb == HIGH and BNum != 2 || bg == HIGH and BNum != 0){
    Error++;
    digitalWrite(RedLED, HIGH);
    delay(4000);
    digitalWrite(RedLED, LOW);  
    if (Error >= 3){
      delay(10000);
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
