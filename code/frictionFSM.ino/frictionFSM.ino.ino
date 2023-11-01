#include <Servo.h>
#include<Streaming.h>
#include <NewPing.h>
#define TRIGGER_PIN1 PA0
#define ECHO_PIN1 PA1
#define MAX_DISTANCE1 50 //cm 
#define TRIGGER_PIN2 PA4
#define ECHO_PIN2 PA5
#define MAX_DISTANCE2 50 //cm
#define LDR PA6
#define laser PB10
#define Motor PA11
unsigned long previousMillis = 0;
int t, sec = 0;
int v, a, s, f;
Servo myservo;
NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE1); // NewPing setup of pins and
maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE2);
#define Step0 0
#define Step1 1
#define Step2 2
int Status = 0;
int Coin_Input();
void Func0();
void Func1();
void Func2();
void Func3();
void Func4();
void state1();
int S = 0;
char data;
struct State {
  void (*fn1)();
  //unsigned long Out;
  int Time;
  int Next[3]
  ;
};
typedef const struct State STyp;
STyp FSM[3] =
{
  { Func
    0, 500, {Step1, Step1}},
  { Func1, 5000, {Step2, Step2}},
  { Func
    2, 500, {
      Step
      0, Step
      0
    }
  }
};
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(LDR, INPUT);
  pinMode(laser, OUTPUT);
  pinMode(Motor, OUTPUT);
  myservo.attach(PA8);
  digitalWrite(laser, HIGH);
  digitalWrite(Motor, LOW);
  myservo.write(90);
}
void loop() {
  int i;
  if (Serial2.available() > 0)
  {
    data = Serial2.read();
    if (data == 'A') {
      Status =
        1;
      35

    }
    if (data == 'P') {
      Status =0;
}
    if (data == 'M') {
      myservo.write(90);
      digitalWrite(Motor, HIGH);
      delay(400);
      digitalWrite(Motor, LOW);
      v = 0;
      a = 0;
      f = 0;
    }
    if (data == 'W') {
      digitalWrite(Motor, LOW);

    }
    if (data == 'S') {
      int ser = myservo.read();
      if (ser == 0)
      {
        myservo.write(90);
      } else {
        myservo.write(0);
      }
    }
  }
  36
  if (Status == 1)
  {
    state1()
    ;
    Serial2.println(v);
    Serial2.println("");
    Serial2.println("");
    Serial2.println(a);
    Serial2.println("");
    Serial2.println("");
    Serial2.println(f);

  }
  if (Status == 0)
  {
    delay(300)
    ;

    if (sonar1.ping_cm() <= 9)
    {
      v = 0;
      a = 0;
      f = 0;
      t = 0;
    }
    if (sonar1.ping_cm() >= 10)
    {
      digitalWrite(laser, HIGH);
      timer();
      s = sonar1.ping_cm();
      v = 2 * s / t;
      a = s / t;
      f = 9.81 - (3 * a);
    }

  }

  Serial2.println(v);
  Serial2.println("");
  Serial2.println("");
  Serial2.println(a);
  Serial2.println("");
  Serial2.println("");
  Serial2.println(f);
}
void state1() {
  FSM[S].fn1(); // call output function
  delay(FSM[S].Time); // wait Time
  int Input = Coin_Input(); // input can be 0,1,2
  S = FSM[S].Next[Input]; // nextl State
  Serial << "" << endl;
  Serial << "Input : " << Input << endl;
  Serial << "State No : " << S << endl;
  delay(1000);
}

int Coin_Input() {
  int y;
  int s1 = sonar1.ping_cm();
  int s2 = sonar2.ping_cm();
  if (s1 >= 7) {
    y = 0;
  }
  if (s2 <= 3) {
    y = 1;
  }
  return y;
}
void Func0() {
  myservo.write(90);
  digitalWrite(Motor, LOW);
  digitalWrite(laser, HIGH);
  delay(5000);
}
void Func1() {
  s = sonar1.ping_cm();
  myservo.write(0);
  int sec = 0;
  unsigned long currentMillis = micros();
  if (currentMillis - previousMillis >= 1000000) {
    39
    sec++;
    if (sec >= 60)
    {
      sec = 0;
    }
    previousMillis = currentMillis;
  }
  t = sec;
  v = 2 * s / t;
  a = s / t;
  f = 9.81 - (3 * a);
  Serial2.println(v);
  Serial2.println("");
  Serial2.println("");
  Serial2.println(a);
  Serial2.println("");
  Serial2.println("");
  Serial2.println(f);
  delay(300);
}
void Func2()
{
  myservo.write(90);
  digitalWrite(Motor, HIGH);
  delay(400);
  digitalWrite(Motor, LOW);
  Serial2.println(v);
  Serial2.println("");
  Serial2.println("");
  Serial2.println(a);
  Serial2.println("");
  Serial2.println("");
  Serial2.println(f);
  delay(5000);
}
void timer() {
  t, sec = 0.00;
  unsigned long currentMillis = micros();
  if (currentMillis - previousMillis >= 1000000) {
    sec++;
    if (sec >= 60) {
      sec = 0;
    }
    previousMillis = currentMillis;
  }
  t = sec;
  // Serial.print(m); Serial.print(":"); Serial.print(sec);
}
