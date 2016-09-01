#include <Wire.h>
#include <Keypad.h>
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
char key;
const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
/*
char keymap[numRows][numCols]=
{
{'3', '2', '1'},
{'6', '5', '4'},
{'9', '8', '7'},
{'E', '0', 'F'}
};
*/
char keymap[numRows][numCols] = { {'1','2','3','A'},
                                  {'4','5','6','B'},
                                  {'7','8','9','C'},
                                  {'E','0','F','D'}};

char a,b,c,d,e,f,g,h;

/////////////////
boolean state=false;
boolean lock=false;
int dl=0;

char arr[4];

int i=0,pin,password=0,login;
////////////////////////////////


//Code that shows the the keypad connections to the arduino terminals
//byte rowPins[numRows] = {4,5,6,7}; //Rows 0 to 3 // 0 13 6 7
//byte colPins[numCols]= {1,2,3}; //Columns 0 to 3

byte rowPins[numRows] = {0,1,2,3}; //Rows 0 to 3 // 0 13 6 7
byte colPins[numCols]= {4,5,6,7}; //Columns 0 to 3


//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
long int prev=0;
void setup()
{

Serial.begin(9600);
lcd.begin(20, 4);
lcd.clear();
//prev = millis();

}
/////////////
int sec=0,min=0;
int pos=0;
//////////////
void loop() 
{
  //long int prev = millis();

  long int cur;
  key = NO_KEY;
  for (cur =0; cur <500; cur++ )
  {
    //getInput();
    
      if (key == NO_KEY) key = myKeypad.getKey();
       
      //lcd.print(k);
    delay(1);
  }
  /////////////////////////////////
  if (key!=NO_KEY)
  {
  lcd.setCursor(pos,1);
  lcd.print(key);
  arr[pos] = key;
  pos++;
  }


  if (pos == 4)
  {
    lcd.setCursor(0,1);
    lcd.print("Alarm Set");    
    delay (1000);
    
    lcd.setCursor(9,1);
    char chhh = arr[0];
    int zzz = (int)chhh-48;
    lcd.print(zzz);
    char chhh1 = arr[1];
    int zzz1 = (int)chhh1-48;
    lcd.print(zzz1);
    char chhh2 = arr[2];
    int zzz2 = (int)chhh2-48;
    lcd.print(zzz2);
    char chhh3 = arr[3];
    int zzz3 = (int)chhh3-48;
    lcd.print(zzz3);

    int min2 = zzz*10 + zzz1;
    int sec2 = zzz2*10 + zzz3;

    if (min == min2 && sec == sec2)
    {
      lcd.clear();
      lcd.print("Alarm triggered!");
      delay(3000);
      lcd.clear();
      pos = 0;
      
    }
    
  }
  ///////////////
  sec++;
  prev = cur;

  if (sec==60)
  {
    min++;
    sec=0;
  }
  lcd.setCursor(0,0);
  lcd.print(min);
  lcd.print(":");
  lcd.print(sec);
  //delay(1200);
  //lcd.clear();
  
 
}
//////loop ends///////////
void getInput()
{
  lcd.setCursor(0,1);
  key = myKeypad.getKey();
  if (key == NO_KEY)
  {
    //delay(100);
    key = myKeypad.getKey();
    //lcd.print("not");
  }
/*  else
    key = 't';*/
    
  lcd.print(key);
}

