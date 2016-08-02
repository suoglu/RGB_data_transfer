# RGB_data_transfer






CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Recommended modules
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

This module requires the following modules:

 * Module1 (https://module1.com)
 * 
 
RECOMMENDED MODULES
-------------------

 * Markdown filter (https://www.drupal.org/project/markdown):
   When enabled, display of the project's README.md help will be rendered
   with markdown.




INSTALLATION
------------
 
 * 
 
* Connect the power LEDs to corresponding pins (red, green and blue to pin 2, 4 and 7 respectively) on the Arduino Board and to ground. Also, the color sensor (TCS34725) should be connected as specified here (https://cdn-shop.adafruit.com/datasheets/TCS34725.pdf). You should disable the LEDs on the light sensor by grounding the LED pin.
 
* First step should be done with the other Arduino.
 
* After connecting the Arduino Boards to two seperate PCs and power supplies, ... should be uploaded to the Arduino Boards.

* Text can be written into the console by opening the serial monitor
 




CONFIGURATION
-------------
 
 
 
 * Configure user permissions in Administration » People » Permissions:

   - Use the administration pages and help (System module)

     The top-level administration categories require this permission to be
     accessible. The administration menu will be empty unless this permission
     is granted.

   - Access administration menu

     Users in roles with the "Access administration menu" permission will see
     the administration menu at the top of each page.

   - Display Drupal links

     Users in roles with the "Display drupal links" permission will receive
     links to drupal.org issue queues for all enabled contributed modules. The
     issue queue links appear under the administration menu icon.

 * Customize the menu settings in Administration » Configuration and modules »
   Administration » Administration menu.

 * To prevent administrative menu items from appearing twice, you may hide the
   "Management" menu block.





TROUBLESHOOTING
---------------

 * If the menu does not display, check the following:

   - Are the "Access administration menu" and "Use the administration pages
     and help" permissions enabled for the appropriate roles?

   - Does html.tpl.php of your theme output the $page_bottom variable?

FAQ
---

Q: I want to disable the LED on the sensor. Is there way to do this?

A: Yes, this is possible. Simply by connecting the "LED" pin to ground will short-circuit it. 






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
