/* the tutorial code for 3x4 Matrix Keypad with Arduino is as
This code prints the key pressed on the keypad to the serial port*/

#include <Keypad.h>
#include <Wire.h>

#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR_LCD3.h>

#include <LCD.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal.h>
LiquidCrystal_SR lcd(12, 13, 8);

const byte Rows= 4; //number of rows on the keypad i.e. 4
const byte Cols= 4; //number of columns on the keypad i,e, 3

//we will definne the key map as on the key pad:

char keymap[Rows][Cols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//  a char array is defined as it can be seen on the above


//keypad connections to the arduino terminals is given as:

byte rPins[Rows]= {0,1,2,3}; //Rows 0 to 3
byte cPins[Cols]= {4,5,6,7}; //Columns 0 to 2
int flag = 0, flag1 =1;

Keypad kpd= Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);
//LiquidCrystal lcd(12,13,8,9,10,11);

void setup()
{
  Serial.begin(9600);  // initializing serail monitor
  //lcd.begin(16,2);
  
lcd.begin(20, 4);
  //lcd.print("lock\n"); 
}

void loop()
{
  char enter = 'A', ch;
  int count = 0;
  char pass[10],cpass[10];
  if(flag1 == 1 ){
    //Serial.println("Unlocked");
    lcd.println("Unlocked");
  }
  delay(3000);
  lcd.clear();
  while(1){
     ch = kpd.getKey();
    if( ch != NO_KEY ){
      pass[count]=ch;
      count++;
      //Serial.print(ch);
      lcd.print(ch);
     }
     if( count == 4 )
       break;
    }
    pass[count] = '\0';
    //Serial.println();
    //lcd.print("\n");
    while(1){
      char ch = kpd.getKey();
      if( ch == enter ){
          flag = 1;
          flag1 =0;
          //Serial.println("Locked");
          lcd.clear();
          lcd.print("Locked");
          break;
        }
      }
      //count=0;
      while(1){
        char ch;
      count = 0;  
      lcd.setCursor(0,1);
      while(1){
        ch = kpd.getKey();
        if( ch == enter )
          break;
        if( ch != NO_KEY ){
          cpass[count]=ch;
          count++;
          //Serial.print(ch);
          lcd.print(ch);
        }
        }
        cpass[count] = '\0';
        //Serial.println();
        //lcd.print("\n");
        if(flag==1){
        if( strcmp(pass,cpass) == 0){
          //Serial.println("Unlocked");
          //lcd.setCursor(0,0);
          lcd.clear();
          lcd.print("Unlocked");
          flag = 0;
          }
        else{
         //Serial.println("Access denied");
         lcd.setCursor(0,1);
         lcd.print("Access denied");
        }
        }

         else{
        if( count == 0 && ch == enter ){
            //Serial.println("Locked");
            //lcd.setCursor(0,0);
            lcd.clear();
            lcd.print("Locked");
            flag=1;
            
          }
        else if( count == 4){
            strcpy(pass,cpass);
            //Serial.println("Locked");
            //lcd.setCursor(0,0);
            lcd.clear();
            lcd.print("Locked");
            flag=1;
          }
          else if(count<4){
            //Serial.println("Enter Password");
            //lcd.setCursor(0,0);
            lcd.clear();
            lcd.print("Enter Password");
          }
         }    
    }      
}
