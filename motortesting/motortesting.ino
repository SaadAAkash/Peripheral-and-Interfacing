
#define MotorA_IN1 10
#define MotorA_IN2 11
#define MotorPWM 9


void setup() {
  // put your setup code here, to run once:
pinMode (MotorA_IN1, OUTPUT);
pinMode (MotorA_IN2, OUTPUT);
pinMode (13, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(10, HIGH);
digitalWrite(11, LOW);
digitalWrite(13, HIGH);

//analogWrite(10,120);
//analogWrite(11,120);

analogWrite(MotorPWM,50);
delay(10000);
digitalWrite(10, LOW);
digitalWrite(11, LOW);

analogWrite(MotorPWM,0);


}
