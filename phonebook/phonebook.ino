#include <LiquidCrystal.h>
#include <Keypad.h>
#include <string.h>
const byte numrows = 4;
const byte numcols = 4;


char keymap[numrows][numcols] = { {1,2,3,'F'},
                                  {4,5,6,'B'},
                                  {7,8,9,'*'},
                                  {'C','0','E','/'}};
byte rowpins[numrows] = {0,7,2,3};
byte colpins[numcols] = {4,5,6,1};

Keypad mykeypad = Keypad(makeKeymap(keymap),rowpins,colpins,numrows,numcols);

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

char charSel[10][4] = { {0,0,0,0}, 
                        {0,0,0,0},
                        {'a','b','c' , 0} ,
                        {'d','e','f' , 0 } , 
                        {'g','h','i' , 0 } , 
                        {'j','k','l' , 0} , 
                        {'m','n','o',0} , 
                        {'p','q','r','s'} , 
                        {'t','u','v', 0} , 
                        {'w','x','y','z'} };

char Number[100];
char Store[100];
int numberOfContent = 0;

struct value{
  char Name[15];
  char Num[15];
} storedValue[10];

void setup() {
  Serial.begin(9600);
  while(!Serial);
  UCSR0B=0;
  lcd.begin(16, 2);
}

void loop() 
{
  showMenu();
  selection();
}
void showMenu(){
  lcd.clear();
  lcd.print("1. Save 2. Del");
  lcd.setCursor(0,1);
  lcd.print("3. Search");
}
void selection(){
  char keypressed = mykeypad.waitForKey();
  if(keypressed != NO_KEY){
    if(keypressed == 1){
      save();
    }
    else if(keypressed == 2){
      del();
    }
    else if(keypressed == 3){
      search();
    }
    else{
      lcd.clear();
      lcd.print("Wrong input");
      delay(500);
    }
  }
}
void save(){
 
  inputName();
  strcpy(storedValue[numberOfContent].Name,Store);
  inputNumber();
  strcpy(storedValue[numberOfContent].Num,Number);
  numberOfContent++;
}

void inputName(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Name:");
  lcd.setCursor(0,1);
  int index = 0;
  char temp;
  char tempChar;
  char Key = mykeypad.waitForKey();  
  while(true){
    if(Key == 'E'){
      Store[index] = 0;
      break;
    }
    int j = 0;
    tempChar = charSel[Key][j];
    unsigned long start = millis();
    while(true){
      lcd.setCursor(index,1);
      if(Key){
        lcd.print(tempChar);
        Store[index] = tempChar;  
      }
      
      unsigned long end = millis();
      if(end - start > 1000){
        Key = 0;
        break;  
      }
      temp = mykeypad.getKey();
      if(temp == NO_KEY) continue;
      if(temp == 'C'){
        if(index) index--;
        lcd.print(' ');
        continue;
      }
      if(temp == Key){
        if(temp != 7 && temp != 9){
          j = (j+1)%3;
          tempChar = charSel[Key][j];
        }
        else{
          j = (j+1)%4;
          tempChar = charSel[Key][j];
        }
      }
      else{
        Key = temp;
        j = 0;
        tempChar = charSel[Key][j];
        index++;
        break;
      }
    }
  }
}
void inputNumber(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Number:");
  
  
  int index = 0 ;
  while(true){
    lcd.setCursor(index,1);
    char temp = mykeypad.waitForKey();
    if(temp == 'E'){
      Number[index] = 0 ;
      break;
    }
    if(temp == 'C'){
      if(index) index--;
      lcd.setCursor(index,1);
      lcd.print(' ');
      continue;
    }
    if(temp != '0')
      Number[index] = temp + '0';
    else
      Number[index] = temp;
    lcd.print(Number[index]);
    index++;
  }
}

void search(){
  inputName();
  int showValue[10];
  int numberOfHits = 0;
  bool found = false;
  for(int i = 0 ; i < numberOfContent; i++){
    if(!strncmp(storedValue[i].Name, Store, strlen(Store))){
      showValue[numberOfHits++] = i;
      found = true;
    }
  }
  
  int curPos = 0;
  lcd.clear();
  if(!found){
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("No Contact Found");
    delay(1000);
  }
  else
  while(true){
    
    lcd.setCursor(0,0);
    lcd.print(storedValue[showValue[curPos]].Name);
    lcd.setCursor(0,1);
    lcd.print(storedValue[showValue[curPos]].Num);  
    char temp = mykeypad.waitForKey();
    if(temp == 'F'){
      if(curPos != 0){
        lcd.clear();
        curPos--;
      }
    }else if(temp == 'B'){
      if(curPos != numberOfHits - 1){
        lcd.clear();
        curPos++;
      }
    }else if(temp == 'C'){
      lcd.clear();
      break;
    }
  }
}
void del(){
 inputName();
  char Searching[15];
  for(int i = 0 ; i < numberOfContent; i++){
    if(!strcmp(storedValue[i].Name,Store)){
      for(int j = 0 ; j < numberOfContent - 1; j++){
        strcpy(storedValue[j].Name, storedValue[j+1].Name);
        strcpy(storedValue[j].Num, storedValue[j+1].Num);
      }
      numberOfContent--;
      break;
    }
  } 
}

