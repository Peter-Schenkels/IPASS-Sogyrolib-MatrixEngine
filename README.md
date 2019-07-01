# IPASS Sogyrolib & MatrixEngine

IPASS Project
Hoge School Utrecht 
HBO ICT-TI

Library for the **L3G4200D** gryoscope and the **MH7219 Led Matrix** including a Game making toolset.

By Peter Schenkels 2019

___
## Description Sogyrolib:
Interface for the **L3G4200D** with a twist. The Chip is connected to a seperate Arudino Nano. This Arduino Nano 
is used for getting the Axis. The **Slave Arduino Nano** is connected via a **SPI** bus to a **Master Arduino**. The Slave 
Arduino Nano focusses on getting the **DPS** (Degrees Per Second) values from the chip and keeping track of it's 
**own axis** in **degrees**. The Master Arudino can acces these values by sending **command bytes** to the Arduino Nano. 

### How to use it:
**Hwlib** is needed for this project, consult this page for more **information**: 
https://github.com/wovo/installers

The **Slave Arduino Nano** needs to be connected to a **Master Arduino Due** via **SPI**.
**Flash** the slave code in the */src/Slave_Gyroscope* Directory on to the Slave Arduino Nano.
I have profided a **test** in the "tests" directory. 

**Pin** connections between the **Slave** and the **Master**.

For the **Slave** you need to connect these **pins**:

* Pin **d4** is for the **clock** pin.
* Pin **d5** is for the **mosi** pin.
* Pin **d6** is for the **miso** pin.
* Pin **d7** is for the **cs** pin.


note: ~~these pins can be changed by manually modifying the class~~

For the **Master** you can choose whatever suits your mood.

Run this **command** in the **root** directory of this project for the Doxygen documentation:
*Doxygen*

See the Doxygen documentation for more information on how to use this library.


### What you need:

* Arduino Due (Master)
* Arduino Nano (Slave)
* L3G4200(D) Gyroscope


___

## Description MatrixEngine:
Interface and **game making toolset** for the **MH7219 Led Matrix chip** and other **Hwlib Window peripherals**. 
This toolset includes a **physics engine**, **render engine**, **collision detection**, **camera movement** and more. 
Connect **multiple MH7219 chips** via **SPI** on the **Arduino**. The toolset can also be used to run games
inside the **terminal**.
(linux only)

### How to use it:
**Hwlib** is needed for this project, consult this page for more **information**: 
https://github.com/wovo/installers

This library comes with a **demo** file that is also connected to **Sogyro lib**. 
But it can also be run without gyroscope (if you remove the gyroscope you wont be able to move the character).

See the Doxygen documentation for more information on how to use this library.

### What you need:

* Arduino Due (Master)
* MH7219 Led Matrix Chip(s)

optional:
Hwlib Window Peripherals such as an oled.




