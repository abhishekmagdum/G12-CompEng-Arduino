#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Servo.h>

int address = 0;
static unsigned long SaveTimer;                
static unsigned long SaveDelay = (30 * 1000); 

char CODE[10] = "123E";                  
char Str[10]; 
char CodeLength = 3;
int Pos = 0;
bool Unlocked;
static unsigned long DisplayTimer; 
static unsigned long DisplayDelay = 200;

LiquidCrystal lcd(12, 11, 9, 8, 7, 6); 


int buttonPin1 = 2;   
int buttonPin2 = 3;
int buttonPin3 = 4;
int buttonPin4 = 5;

int enterbutton = 10; 
int clearlockbutton = 13;

Servo myServo;                    

void setup() {

  myServo.attach(A1);  

  Lock();
  
  int EEPROMCodeOK = true;
  for (Pos = 0; Pos <= (CodeLength); Pos++) {
    Str[Pos] =  EEPROM.read(Pos);
    if (!(strrchr("1123456789", Str[Pos]))) { 
      EEPROMCodeOK = false;
    }
  }
  Pos++;
  Str[Pos] =  EEPROM.read(Pos); 
  if (Str[CodeLength + 1] != 'E') EEPROMCodeOK = false; 
  if (EEPROMCodeOK) {
    Str[CodeLength + 2] = '\0';
    strncpy(CODE, Str, CodeLength + 1);
  }
  ClearCode();

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  pinMode(enterbutton, INPUT_PULLUP);
  pinMode(clearlockbutton, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Hello.");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Password:");

  DisplayTimer = millis() + 200;
}


void loop() {

 
  
  Pos = constrain(Pos, 0, CodeLength);

  int buttonState1 = digitalRead(buttonPin1);  
  int buttonState2 = digitalRead(buttonPin2);
  int buttonState3 = digitalRead(buttonPin3);
  int buttonState4 = digitalRead(buttonPin4);

  int clButtonState = digitalRead(clearlockbutton);
  int enterButtonState = digitalRead(enterbutton);

  lcd.setCursor(9, 0);

  if (buttonState1 == LOW) {
    Str[Pos] = '1';
    Pos++;
    Str[Pos] = '\0';
    delay(250); 
    while (digitalRead(buttonPin1) == LOW); 

  }

  else if (buttonState2 == LOW) {
    Str[Pos] = '2';
    Pos++;
    Str[Pos] = '\0';
    delay(250); 
    while (digitalRead(buttonPin2) == LOW);

  }

  else if (buttonState3 == LOW) {
    Str[Pos] = '3';
    Pos++;
    Str[Pos] = '\0';
    delay(250); 
    while (digitalRead(buttonPin3) == LOW);
  }

  else if (buttonState4 == LOW) {
    Str[Pos] = '4';
    Pos++;
    Str[Pos] = '\0';
    delay(250); 
    while (digitalRead(buttonPin4) == LOW); 

  }
  else if (enterButtonState == LOW) {
    Str[Pos] = 'E';
    Pos++;
    Str[Pos] = '\0';
    delay(250);

    lcd.setCursor(15, 0);
    lcd.print("E");
    delay(400);
    lcd.setCursor(15, 0);
    lcd.print(" ");
    
    while (digitalRead(buttonPin1) == LOW); 
     if (strcmp (Str,CODE) == 0) {
      Unlocked = true;
      lcd.setCursor(0, 0);
      lcd.print(" Access Granted");
      delay(2000);
      lcd.clear();
      lcd.print("    Unlocked");
      
    } 

    else { 

      lcd.clear();
      lcd.print(" Access Denied.");
      delay(2000);
      lcd.clear();
      lcd.print("Password:");

    }

    while (Unlocked) {
      Unlock();
      if (digitalRead(clearlockbutton) == LOW) {
        delay(200);
        lcd.clear();
        delay(3000);
        lcd.print("     Locked");
        delay(2000);
        lcd.clear();
        Unlocked = false;
        SaveTimer = millis() + 30000;
      }
    }
    
    ClearCode();

    
  }

  else if (clButtonState == LOW) {
    delay(500);

    while (clearlockbutton == LOW);
    if ((millis() - SaveTimer) > 4500) {
      
    }
    
    ClearCode();
    
  }

  if ( (long)( millis() - DisplayTimer ) >= 0) {
    DisplayTimer += DisplayDelay;
    lcd.setCursor(9, 0); 
    lcd.print(Str);
    lcd.setCursor(15, 0);
    lcd.print(" ");

    if (clButtonState == LOW) {

      lcd.clear();
      lcd.print("Password:");
      
    }


  }

}

void ClearCode() {
  
  Pos = 0;
  Str[Pos] = '\0';
  lcd.setCursor(0, 0);
  lcd.print("Password:");
  lcd.setCursor(0, 1);
  lcd.print("          ");
  
}

void Unlock() {

  myServo.write(117);
  
}
//delay(2000);

void Lock() {

  myServo.write(26);

}

