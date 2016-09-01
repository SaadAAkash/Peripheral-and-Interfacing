
#define MotorA_IN1 10
#define MotorA_IN2 11
#define MotorPWM 9

void setup() {
  // put your setup code here, to run once:

pinMode (MotorA_IN1, OUTPUT);
pinMode (MotorA_IN2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
Motorclk();
Motoraclk();
}

void Motorclk()
{
  digitalWrite(MotorA_IN1, LOW);
  digitalWrite(MotorA_IN2, HIGH);
  analogWrite(MotorPWM,200);
  delay(500);
}
  
void Motoraclk()
{
  digitalWrite(MotorA_IN1, HIGH);
  digitalWrite(MotorA_IN2, LOW);
  analogWrite(MotorPWM,200);
  delay(500);
}
