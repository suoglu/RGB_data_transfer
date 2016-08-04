# RGB_data_transfer






CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Troubleshooting
 * FAQ
 * Maintainers
 
INTRODUCTION
------------

This project is about VLC (Visible Light Communication). We use arduino uno boards and Adafruit TCS34725 RGB color sensors.
We use RGB leds, each represents one bit of information. Thus at single cycle we will send 3 bits of information.

 * To submit bug reports and feature suggestions, or to track changes:
   yigitsuoglu@sabanciuniv.edu

EQUIPMENTS
------------

This module requires the following equipments:

 * Arduino Board x2
 * Jumpers
 * RGB LEDs (power LEDs are highly recommended) x2
 * RGB light sensor (TCS34725) x2
 * Tape
 * Breadboard x2
 

REQUIREMENTS
------------

* Not very bright environment
* Undisturbed line of sight between the LEDs and RGB sensor.
 

INSTALLATION
------------
* All libraries in the repository should be added to Arduino IDE.
 
* Connect the power LEDs to corresponding pins (default values are 2,3,4 for rgb respectively) on the Arduino Board. Also, the color sensor (TCS34725) should be connected as specified here (https://cdn-shop.adafruit.com/datasheets/TCS34725.pdf). You can disable the LEDs on the light sensor by grounding the LED pin.

* Repeat same process to other board.

* Connect the Arduino boards to the computers.

* Upload master.ino using Arduino IDE to the board.

* Open serial monitors.

* Start calibration sequence with reserved word (default is MODE_sync).
 
* Do the same processes for the other board.

* Then enjoy slow chatting by the RGB LEDs with Arduino.
 




CONFIGURATION
-------------

Modes and default keywords:

MODE_sync: Sends calibration sequence.
MODE_recal: Listens for calibration sequence.
MODE_ledC: Enters LED opening mode. Input decimal equivalent of binary number formed as RGB. Input "quit" for quitting.
MODE_party: Randomly turns on/off LEDs. Change period with integers from 0 to 9. Input "quit" for quitting.
MODE_credits: Prints the team members in alphabetical order.



TROUBLESHOOTING
---------------

* If any LEDs or sensor does not work check your connections.

* If calibration fails at mid-process, reset the Arduino.

* If calibration values are not suitable for current environment do recalibration process. 

*  If the system locks in mid-transmission reset transmitting Arduino.

FAQ
---

Q: I want to disable the LED on the sensor. Is there way to do this?

A: Yes, this is possible. Simply by connecting the "LED" pin to ground will short-circuit it. 

Q: What is the bit rate of the system?

A: 40 bits/sec.

Q: Is there any way enchance the bit rate?

A: It is not possible with current hardware without a more complex algorithm.








MAINTAINERS
-----------

Current maintainers:
 * Yiğit Suoğlu  - https://github.com/suoglu
 * Baran Dereli  - https://github.com/BaranDer
 * Özgün Şensoy  - https://github.com/osensoy
 * Musab Çevik  - https://github.com/musabc
 * Onur Çalık  - https://github.com/calikonur

This project has been sponsored by:
 * AirTies Wireless Networks
      AirTies was established in 2004 by an executive and technical equip who has returned to Turkey from the Silicon Valley with the aim of being the market leaders in Wireless Network Technologies. With its expert R&D team the company designs the hardware and software of their own products. Their products provide wireless high-definition data and media transfer on multiple TVs, notebooks, PC and game consoles. Their product portfolio includes wideband internet devices, local area network products, accesories and set top boxes. In total, AirTies has over 8 million products worldwide. Visit http://www.airties.com.tr for more information.
   

















More information will be avaible soon.
