//Importing Libraries
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Servo.h>

//setting the timer delay to 30 seconds 
int address = 0;
static unsigned long SaveTimer;
static unsigned long SaveDelay = (30 * 1000); 


char CODE[10] = "1234E"; //Unlock Code/Password 
char Str[10]; 
char CodeLength = 4; //Length of Passcode
int Pos = 0;
bool Unlocked;
static unsigned long DisplayTimer; 
static unsigned long DisplayDelay = 200; //Display Latency after clicking button

LiquidCrystal lcd(12, 11, 9, 8, 7, 6); //PinOuts used for lcd

//each button set to pin
int buttonPin1 = 2;   
int buttonPin2 = 3;
int buttonPin3 = 4;
int buttonPin4 = 5;

int enterbutton = 10; 
int clearlockbutton = 13;

Servo myServo;

void setup() {
//servo attached to analog 1 pinout
  myServo.attach(A1);
  
  int EEPROMCodeOK = true;
  for (Pos = 0; Pos <= (CodeLength); Pos++) {
    Str[Pos] =  EEPROM.read(Pos);
    if (!(strrchr("1123456789", Str[Pos]))) { 
      // not a valid code (will not work with letters"
      EEPROMCodeOK = false;
    }
  }
  Pos++;
  Str[Pos] =  EEPROM.read(Pos); 
  if (Str[CodeLength + 1] != 'E') EEPROMCodeOK = false; //if the last character in the codelength is not E, the code is invalid
  if (EEPROMCodeOK) {
    Str[CodeLength + 2] = '\0';
    strncpy(CODE, Str, CodeLength + 1);
  }
  ClearCode();
//pushbuttons must be set to low value
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  pinMode(enterbutton, INPUT_PULLUP);
  pinMode(clearlockbutton, INPUT_PULLUP);

  lcd.begin(16, 2); //introduction sequence
  lcd.setCursor(0, 0);
  lcd.print("Hello Mr.Gould");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Password:");

  DisplayTimer = millis() + 200; //erases code after 0.2 seconds
}


void loop() {
  
  Lock(); //makes sure the box is in the locked position
  
  Pos = constrain(Pos, 0, CodeLength); //constrain value of position to length of code(password)

  int buttonState1 = digitalRead(buttonPin1);  
  int buttonState2 = digitalRead(buttonPin2);
  int buttonState3 = digitalRead(buttonPin3);
  int buttonState4 = digitalRead(buttonPin4);

  int clButtonState = digitalRead(clearlockbutton);
  int enterButtonState = digitalRead(enterbutton);

  lcd.setCursor(9, 0); //loop checking for if button is pressed

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
    while (digitalRead(buttonPin1) == LOW); //checks if the entered digits match the set password
     if (strcmp (Str,CODE) == 0) {
      Unlocked = true;
      lcd.setCursor(0, 0);
      lcd.print(" Access Granted");
      delay(2000);
      lcd.clear();
      lcd.print("    Unlocked");
    } 
    else if (SaveTimer > millis() && (Pos + 1) == CodeLength) { 

      strcpy(CODE, Str);
      for (Pos = 0; Pos <= (CodeLength + 1); Pos++) { //command to store code 
        EEPROM.write(Pos, Str[Pos]);
      }
      lcd.setCursor(0, 0);
      lcd.print("Saving Code:");
      lcd.setCursor(0, 1);
      lcd.print(Str);

      Unlocked = true; //unlock if the password is correct
    }

    else { 

      lcd.clear();
      lcd.print(" Access Denied."); //access denied if password is incorrect
      delay(2000);
      lcd.clear();
      lcd.print("Password:");

    }

    while (Unlocked) {
      Unlock();
      if (digitalRead(clearlockbutton) == LOW) {
        delay(200);
        lcd.clear();

        //timer for closing the box again
        
        
        lcd.print("   20 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   19 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   18 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   17 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   16 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   15 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   14 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   13 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   12 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   11 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   10 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   9 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   8 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   7 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   6 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   5 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   4 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   3 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   2 Seconds");
        delay(1000);
        lcd.clear();
        lcd.print("   1 Second");
        delay(1000);
        lcd.clear();
        lcd.print("Door Locking!");
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

    while (clearlockbutton == LOW); //clear button held for 0.5 seconds clears the code and resets
    if ((millis() - SaveTimer) > 4500) {
      
    }
    
    ClearCode();
    
  }

  if ( (long)( millis() - DisplayTimer ) >= 0) {
    DisplayTimer += DisplayDelay;
    lcd.setCursor(9, 0); //resets
    lcd.print(Str);
    lcd.print("     ");

  }
}

void ClearCode() {
  
  Pos = 0;
  Str[Pos] = '\0';
  lcd.setCursor(0, 0);
  lcd.print("Password:");
  lcd.setCursor(0, 1);
  lcd.print("          "); //clear code call
  
}

void Unlock() {

  myServo.write(150-90); //servo angle change
  
}

void Lock() {

  myServo.write(50+90); //servo angle change

}
