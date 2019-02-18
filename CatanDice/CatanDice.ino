//EEPROM memory storage
#include <EEPROM.h>
int eeAddress = 0;

//Liquid crystal
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
const int lcdX = 16; //To help center the messages

//Button
#define buttonPin 2
bool buttonDown = false;
long lastTime = 0;

//Piezo passive buzzer
#define tonePin 3
bool soundOn = true;



// User inferface states
int mainState = 0;
int gameStatsState = 0;
int globalStatsState = 0;

// Statistics management
struct stats {
  long numRolls = 0;
  long numSevens = 0;
  long diceStats[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

stats gameStats;// This info is lost after an Arduino reset.
stats globalStats;// This info is kept even after an Arduino reset.


void setup() {
  //Serial debugging.
  Serial.begin(9600);

  //LCD configuration.
  lcd.begin(16, 2);

  //Pseudo random number generator seeding.
  randomSeed(analogRead(0));

  //Retries the globalStats from the EEPROM memory
  EEPROM.get(eeAddress, globalStats);

  //Button configuration
  pinMode(buttonPin, INPUT_PULLUP);

  //To reset the global stats, one needs to reset the arduino an keep the button pressed
  //for more than 3 seconds.
  if (digitalRead(buttonPin) == LOW) {
    delay(3000);
    if (digitalRead(buttonPin) == LOW) {
      resetStats();
    }
  }

  //Greetings :)
  lcdPrintCenter("Dice ready !", 0, true);
  lcdPrintCenter("Happy Catan :)", 1, false);
  delay(100);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonIsDown, FALLING);
  buttonDown = false; //prevents a dice roll at startup.
}

//A small function to center the printed text on the LCD
void lcdPrintCenter(String string, int line, bool doClear) {
  if (doClear) {
    lcd.clear();
  }

  int lenght = string.length();
  lcd.setCursor(8 - lenght / 2, line);
  lcd.print(string);
}

void rollDices() {//Generate the dice output with some suspence sound
  lcd.clear();
  int increment = 0;// for the animated output on the LCD
  int line = 0;// for the animated output on the LCD
  if (soundOn) {
    int soundInterval = 150;
    while (soundInterval > 5) {// Makes a progressive sound
      soundInterval = soundInterval - 10;
      tone(tonePin, 600 - soundInterval);
      delay(soundInterval);
      noTone(tonePin);
      delay(soundInterval);

      if (increment > 15) {//Change line if greater than 15 so theres a string overflow
        line ++;
        lcd.setCursor(0, line);
        increment = 0;
      }
      if (line < 2) {
        lcd.print(String(random(1, 7)) + " " + String(random(1, 7)) + " ");
        increment = increment + 4;
      }
    }
  }

  int value1, value2;

  value1 = random(1, 7);//The random values of each dices
  value2 = random(1, 7);

  //Formatting the output for the LCD
  String result1 = "D1: " + String(value1) + "  D2: " + String(value2);
  String result2 = "Value: " + String(value1 + value2);

  //Check if the robbers have been drawn. If not, normal procedure. 
  if (value1 + value2 != 7) {
    lcdPrintCenter(result1, 0, true);
    lcdPrintCenter(result2, 1, false);

    for (int j = 0; j < 3; j++) { //A small blink animation
      delay(300);
      lcd.noDisplay();
      delay(300);
      lcd.display();
    }

  }
  else {//The draw is a seven!!! 
    lcdPrintCenter("ROBBER", 0, true);
    lcdPrintCenter(" :( :( :( ", 1, false);

    int freq[] =  {1000, 500, 300}; //The sad music of the robber. 
    int del[] = {200, 200, 600}; //delay between each notes. 

    for ( int j = 0; j < 3; j++) {
      lcd.noDisplay();
      tone(tonePin, freq[j]);
      delay(del[j]);
      lcd.display();
      noTone(tonePin);
      delay(del[j]);

    }
    lcdPrintCenter(result1, 0, true); 
    lcdPrintCenter(result2 + " (Robber)", 1, false);
  }
 
  storeValue(value1 + value2);

  //Print stats on the serial monitor (mainly for debugging)
  Serial.println("Dice 1: "+String(value1)); 
  Serial.println("Dice 2: "+String(value2)); 
  
  Serial.println("GameStats");
  for (int j = 0; j < 11; j++) {
    Serial.print(gameStats.diceStats[j]);
    Serial.print(",");

  }
  Serial.println("");
  Serial.println("GlobalStats");
  for (int j = 0; j < 11; j++) {
    Serial.print(globalStats.diceStats[j]);
    Serial.print(",");
  }
  Serial.println("");
  
}

void loop() {
  //Serial.println(digitalRead(buttonPin));
  if (buttonDown) {
    delay(50);
    long timerStart = millis();

    //User input management. If the button is kept down for more than 1 second, it 
    //will change the menu state. If it's down for less than a second, the operation will 
    //depends on the menu state.
    while (digitalRead(buttonPin) == LOW) {
        if (millis()  > timerStart + 1000) {
        mainStateChange();
        if (mainState == 0) {//Dice roll state
          lcdPrintCenter("Ready to roll!", 0, true);
          delay(500);
          buttonDown = false;
          return; // To avoid a roll when we change main state.
        }
        if (mainState == 1) {//Game stats state
          lcdPrintCenter("Game Stats", 0, true);
          delay(500);
          gameStatsState = -1;
        }
        if (mainState == 2) {//Global stats state
          lcdPrintCenter("Global Stats", 0, true);
          delay(500);
          globalStatsState = -1;
        }
        break;
      }
    }
    //Operation to perform depending on the state
    if (mainState == 0) {//
      rollDices();
    }
    // ################# GAMESTATS FORMATTING ####################
    // This part of the code is ugly and should be shortened by the use of functions... 
    if (mainState == 1) {
      gameStatsState ++;
      gameStatsState = gameStatsState % 5;
      if (gameStatsState == 0) {
        lcdPrintCenter("Game Stats", 0, true);
      }
      else if (gameStatsState == 1) {
        lcdPrintCenter("Num rolls : " + String(gameStats.numRolls), 0, true) ;
        lcdPrintCenter("Num sevens : " + String(gameStats.numSevens), 1, false);
      }
      else if (gameStatsState == 2) {
        String statsToShow;
        for (int j = 2; j < 4; j++) {
          statsToShow = statsToShow +  String(j) + "=" +
                        String((float) gameStats.diceStats[j - 2] / (float) gameStats.numRolls * 100 , 0)+ "% ";
        }

        lcdPrintCenter(statsToShow, 0, true);
        statsToShow = "";
        for (int j = 4; j < 6; j++) {
          statsToShow = statsToShow +   String(j) + "=" +
                        String((float) gameStats.diceStats[j - 2] / (float) gameStats.numRolls * 100, 0)+ "% ";
        }
        lcdPrintCenter(statsToShow, 1, false);
      }
      else if (gameStatsState == 3) {
        String statsToShow;
        for (int j = 6; j < 8; j++) {
          statsToShow = statsToShow +  String(j) + "=" +
                        String((float) gameStats.diceStats[j - 2] / (float) gameStats.numRolls * 100, 0)+ "% ";
        }

        lcdPrintCenter(statsToShow, 0, true);
        statsToShow = "";
        for (int j = 8; j < 10; j++) {
          statsToShow = statsToShow +  String(j) + "=" +
                        String((float) gameStats.diceStats[j - 2] / (float) gameStats.numRolls * 100, 0)+ "% ";
        }
        lcdPrintCenter(statsToShow, 1, false);
      }
      else if (gameStatsState == 4) {
        String statsToShow;
        for (int j = 10; j < 12; j++) {
          statsToShow = statsToShow +   String(j) + "=" +
                        String((float) gameStats.diceStats[j - 2] / (float) gameStats.numRolls * 100, 0)+ "% ";
        }

        lcdPrintCenter(statsToShow, 0, true);
        statsToShow = "";
        for (int j = 12; j < 13; j++) {
          statsToShow = statsToShow +   String(j) + "=" +
                        String((float) gameStats.diceStats[j - 2] / (float)gameStats.numRolls * 100, 0)+ "% ";
        }
        lcdPrintCenter(statsToShow, 1, false);
      }
 




    }// ################# END OF GAMESTATS FORMATTING ####################
    
    // ################# GLOBAL STATS FORMATTING ####################
    
    if (mainState == 2) {
      globalStatsState ++;
      globalStatsState = globalStatsState % 5;
      if (globalStatsState == 0) {
        lcdPrintCenter("Global Stats", 0, true);
      }
      else if (globalStatsState == 1) {
        lcdPrintCenter("Num rolls: " + String(globalStats.numRolls), 0, true) ;
        lcdPrintCenter("Num sevens: " + String(globalStats.numSevens), 1, false);
      }
      else if (globalStatsState == 2) {
        String statsToShow;
        for (int j = 2; j < 4; j++) {
          statsToShow = statsToShow +  String(j) + "=" +
                        String((float) globalStats.diceStats[j - 2] / (float) globalStats.numRolls * 100, 0)+ "% ";
        }

        lcdPrintCenter(statsToShow, 0, true);
        statsToShow = "";
        for (int j = 4; j < 6; j++) {
          statsToShow = statsToShow + String(j) + "=" +
                        String((float) globalStats.diceStats[j - 2] / (float) globalStats.numRolls * 100, 0)+ "% ";
        }
        lcdPrintCenter(statsToShow, 1, false);
      }
      else if (globalStatsState == 3) {
        String statsToShow;
        for (int j = 6; j < 8; j++) {
          statsToShow = statsToShow +   String(j) + "=" +
                        String((float) globalStats.diceStats[j - 2] / (float) globalStats.numRolls * 100, 0)+ "% ";
        }

        lcdPrintCenter(statsToShow, 0, true);
        statsToShow = "";
        for (int j = 8; j < 10; j++) {
          statsToShow = statsToShow +   String(j) + "=" +
                        String((float) globalStats.diceStats[j - 2] / (float) globalStats.numRolls * 100, 0)+ "% ";
        }
        lcdPrintCenter(statsToShow, 1, false);
      }
      else if (globalStatsState == 4) {
        String statsToShow;
        for (int j = 10; j < 12; j++) {
          statsToShow = statsToShow +  String(j) + "=" +
                        String((float) globalStats.diceStats[j - 2] / (float) globalStats.numRolls * 100, 0)+ "% ";
        }

        lcdPrintCenter(statsToShow, 0, true);
        statsToShow = "";
        for (int j = 12; j < 13; j++) {
          statsToShow = statsToShow +   String(j) + "=" +
                        String((float) globalStats.diceStats[j - 2] / (float)globalStats.numRolls * 100, 0)+ "% ";
        }
        lcdPrintCenter(statsToShow, 1, false);
      }

    }
  }
 // ################# END OFGLOBAL STATS FORMATTING ####################

  buttonDown = false;
}


void mainStateChange() {
  mainState++;
  mainState = mainState % 3;// this number must be changed if there is more states. 
}
void resetStats () {//To reset the global stated, the Arduino must be resetted and the button kept down for more than 3 seconds. 
  globalStats.numRolls = 0;
  globalStats.numSevens = 0;
  for (int j = 0; j < 11; j++) {
    globalStats.diceStats[j] = 0;
  }

  EEPROM.put(eeAddress, globalStats);
  Serial.println("Global stats have been reseted.");
  lcdPrintCenter("Reset of", 0, true);
  lcdPrintCenter("Global stats", 1, false);
  delay(500);
}
void buttonIsDown() {//This function is called via the interrupt attached to the buttonPin
  buttonDown = true;
}

void storeValue(int value) {//This function uptates the stats and store the global stats into the EEPROM
  gameStats.numRolls = gameStats.numRolls + 1;
  globalStats.numRolls = globalStats.numRolls + 1;
  if (value == 7) {
    gameStats.numSevens ++;
    globalStats.numSevens ++;
  }

  gameStats.diceStats[value - 2] =   gameStats.diceStats[value - 2] + 1;
  globalStats.diceStats[value - 2] =   globalStats.diceStats[value - 2] + 1;
  EEPROM.put(eeAddress, globalStats) ;

}

