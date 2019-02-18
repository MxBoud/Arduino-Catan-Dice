# Arduino Catan Dice

I really love playing Settles of Catan with my friends! After a game, we always end up discussing about the outcome of the game, commenting on how some numbers did not appear as ofen than what we should statistically expect. I decided to create an electronic dice that can add a little bit of exictement to the game and keeps track of the statistics about the dices outcome. 
![Picture](https://github.com/MxBoud/Arduino-Catan-Dice/blob/master/Ressources/Images/01.jpg)

## Statistics 

### Game statistics
Every time the dice is rolled, the alrogithm records the outcome. From this data, it is possible to display the number of rolls of the game, the number of times the seven (robber) was rolled and the relative percentage of outcome of all the numbers. The game statistics are erased when the Arduino is reseted. 

### Global statistics
In addition to the game statistics, this project uses the non-volatile EEPROM memory of the Arduino to keep tracks of the global outcome of the dice. At anytime (even after a power off), it can shows the total number of rolls, the total number of game and the relative percentage of roll of every numbers. 

## How to use it
After a power up, every time you momentarily push the button, the dice will be rolled. To access the game statistics and the global statitistics, the button must be pressed for more than one second. To reset the global statistics, the Arduino must be reseted and the button pressed down for more than 3 seconds after the power up. 

## How to build it 

### Parts list
https://www.digikey.ca/product-detail/en/e-switch/PS1024ARED/EG2015-ND/44577

### Electronic schematics
![Schematics](https://github.com/MxBoud/Arduino-Catan-Dice/blob/master/Ressources/Images/Schematics.png)

### Ressources used and acknowledgement
The idea came by discussing with my friend Alexandre. However, after googling it, it was of course already made (here and her), but I did not found one that was keeping tracks of the statistics and was using a 3D printed cover. 





https://www.adafruit.com/product/181
button
https://www.adafruit.com/product/917
pot :
https://www.adafruit.com/product/1831
pbb
https://www.amazon.ca/ELEGOO-Prototype-Soldering-Compatible-Arduino/dp/B073173QL5/ref=sr_1_1?ie=UTF8&qid=1550519033&sr=8-1&keywords=pcb
nano :
https://www.amazon.ca/Arduino-ELEGOO-ATmega328P-Compatible-Without/dp/B071NMD14Y/ref=sr_1_1?ie=UTF8&qid=1550519119&sr=8-1&keywords=arduino+nano
9v connector
https://www.amazon.ca/abcGoodefg-Battery-Button-Connector-Leather/dp/B07B9W4CPT/ref=sr_1_3?ie=UTF8&qid=1550519150&sr=8-3&keywords=9v+battery+connector
buzzer
https://www.amazon.ca/Cylewet-Terminals-Electronic-Electromagnetic-Impedance/dp/B07DDG9HD9/ref=sr_1_2?ie=UTF8&qid=1550519198&sr=8-2&keywords=arduino+buzzer
pbc header
https://www.amazon.ca/Seloky-Straight-Connector-Assortment-Prototype/dp/B07F74QRYH/ref=sr_1_4?ie=UTF8&qid=1550519222&sr=8-4&keywords=pcb+header



STL :
https://a360.co/2SIfUmJ
FUSION 360 
https://a360.co/2SIfUmJ

Acknolwedgement
https://www.instructables.com/id/Arduino-Display-Messages-Using-Hardware-Interrupts/
