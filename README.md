# IPASS Sogyrolib & MatrixEngine

IPASS Project
Hoge School Utrecht 
HBO ICT-TI

Library for the L3G4200D gryoscope and the MH7219 Led Matrix including a Game making toolset.

By Peter Schenkels 2019.


#Description Sogyrolib:
Interface for the L3G4200D with a twist. The Chip is connected to a seperate Arudino Nano. This Arduino Nano 
is used for getting the Axis. The Slave Arduino Nano is connected via a SPI bus with a Master Arduino. The Slave 
Arduino Nano focusses on getting the DPS (Degrees Per Second) values from the chip and keeping track of it's 
own axis. The Master Arudino can acces these values by sending command bytes to the Arduino Nano

#How to use it:
Hwlib is needed for this project, consult this page for more information: 
https://github.com/wovo/installers

The Arduino Nano needs to be connected to a Master Arduino Due via SPI.
Flash the slave code in the /src/Slave_Gyroscope Directory on to the Slave Arduino Nano.
I have profided some tests in the "tests" directory. 

pin connections between the Slave and the Master

For the Slave you need to connect these pins:
Pin d4 on the slave is for the clock
Pin d5 is for the mosi
Pin d6 is for the miso
and pin d7 is for the cs

For the Master you can choose whatever you want.

Run this command in the root directory of this project:
Doxygen

See the doxygen documentation for more information.


#What you need:

Arduino Due (Master)
Arduino Nano (Slave)
L3G4200(D) Gyroscope


#Description MatrixEngine:
Interface and game making toolset for the MH7219 Led Matrix chip and other Hwlib Window peripherals. 
This toolset includes a physics engine a render engine collision detection camera movement and more. 
Connect multiple MH7219 chips via SPI with the Arduino. The toolset can also be used to run games
inside the terminal.

#How to use it:
Hwlib is needed for this project, consult this page for more information: 
https://github.com/wovo/installers

this library comes with a demo file that is also connected to Sogyro lib. 
But it can also be run without gyroscope (if you remove the gyroscope you wont be able to move the character).

See the Doxygen documentation for more information.


#What you need:

Arduino Due (Master)
MH7219 Led Matrix Chip(s)

optional:
Hwlib Window Peripherals such as an oled.


