#include <LiquidCrystal.h> 
LiquidCrystal lcd(12,11,10,9,8,7);


int kp = 50;int ki=30;int kd = 1200;
int PID_p = 0; int PID_i = 0;int PID_d = 0;
float last_kp=0;
float last_ki=0;
float last_kd=0;
float PID_error=0;
float previous_error=0;
float elapsedTime,Time,timePrev;
float PID_value = 0;

int istenenSicaklik = 0;
int anlikSicaklik = 0;
int pwmSicaklik = 0;
int apwmSicaklik = 0; // anlık pwm değeri.

float istenenDeger = 0;
float anlikDeger = 0;


void setup(){
  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(13,OUTPUT);

  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);

  lcd.begin(16,2);
  lcd.display();
  Serial.begin(9600);
  }

void loop(){
   istenenSicaklik = analogRead(A1);
   pwmSicaklik = map(istenenSicaklik,0,1023,0,100);

   float anlikSicaklik = analogRead(A0);
   apwmSicaklik = map(anlikSicaklik,0,1023,0,100);

   istenenDeger = ((istenenSicaklik/1023.0)*5000)/10;
   anlikDeger = ((anlikSicaklik/1023.0)*5000)/10;


  PID_error = pwmSicaklik - apwmSicaklik+2;
  PID_p = 0.01*kp*PID_error;
  PID_i = 0.01*PID_i + (ki * PID_error);
  timePrev = Time;
  Time = millis();
  elapsedTime = (Time - timePrev)/1000;
  PID_d = 0.01*kd*((PID_error-previous_error)/elapsedTime);
  PID_value = PID_p + PID_i + PID_d;

  if(PID_value < 0)
  {PID_value = 0;}
  if(PID_value > 255)
  {PID_value = 250;}


  lcd.setCursor(0,0);
  lcd.print("anlik    istenen");
  lcd.setCursor(0,1);
  lcd.print(anlikDeger);
  lcd.setCursor(10,1);
  lcd.print(istenenDeger);
  delay(1000);


  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  analogWrite(3,PID_value);



  previous_error = PID_error;
  
  }
