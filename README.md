# Arduino Catan Dice

[See the video on Youtube](https://youtu.be/gaEj32isIZw)

I really enjoy playing Settlers of Catan with my friends! After a game, we always end up discussing about the outcome of the game and dice rolls, commenting on how some numbers did not appear as often as we should statistically expect. I decided to build an electronic dice that can add a little bit of excitement to the game and keeps track of the statistics about the dices outcome. 
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
* [Arduino nano](https://www.amazon.ca/Arduino-ELEGOO-ATmega328P-Compatible-Without/dp/B071NMD14Y/ref=sr_1_1?ie=UTF8&qid=1550519119&sr=8-1&keywords=arduino+nano)
* [LCD Display (16x2)](https://www.adafruit.com/product/181)
* [Power switch](https://www.digikey.ca/product-detail/en/e-switch/PS1024ARED/EG2015-ND/44577)
* [100k potentiometer](https://www.adafruit.com/product/1831)
* [Metallic button](https://www.adafruit.com/product/917)
* [6cm x 4cm prototype board](https://www.amazon.ca/ELEGOO-Prototype-Soldering-Compatible-Arduino/dp/B073173QL5/ref=sr_1_1?ie=UTF8&qid=1550519033&sr=8-1&keywords=pcb)
* Assortment of electric wires
* 9V battery
* [9V battery connector](https://www.amazon.ca/abcGoodefg-Battery-Button-Connector-Leather/dp/B07B9W4CPT/ref=sr_1_3?ie=UTF8&qid=1550519150&sr=8-3&keywords=9v+battery+connector)
* [Piezo electric passive buzzer](https://www.amazon.ca/Cylewet-Terminals-Electronic-Electromagnetic-Impedance/dp/B07DDG9HD9/ref=sr_1_2?ie=UTF8&qid=1550519198&sr=8-2&keywords=arduino+buzzer)
* [Trough hole pcb termials](https://www.amazon.ca/Seloky-Straight-Connector-Assortment-Prototype/dp/B07F74QRYH/ref=sr_1_4?ie=UTF8&qid=1550519222&sr=8-4&keywords=pcb+header) (if you want to be able to remove the arduino from the board). 
* A solder iron, some soldering skills and patience :) 
* 3D printed hex case (click [here for the Fusion 360 file](https://a360.co/2SIfUmJ) and here for the .STL's files)
* Some M3 screws and nuts 
* Some M2 screws and nuts 
### Electronic schematics
![Schematics](https://github.com/MxBoud/Arduino-Catan-Dice/blob/master/Ressources/Images/Schematics.png)

### Ressources used and acknowledgement
* The idea came by discussing with my friend Alexandre. However, after googling it, it was of course already made ([here](https://create.arduino.cc/projecthub/joshi/settlers-of-catan-dice-d653f0) and [here](https://www.youtube.com/watch?v=biL6dSZkcWw)), but I did not found one that was keeping tracks of the statistics and was using a 3D printed cover. 

* Thanks Nicole, Lindsay and Alexandre for testing the device with me :). 
* The code from [this tutorial](https://www.instructables.com/id/Arduino-Display-Messages-Using-Hardware-Interrupts/) was very usefull! 





