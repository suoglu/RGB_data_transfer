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
 
 * Install as you would normally install a contributed Drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.

 * You may want to disable Toolbar module, since its output clashes with
   Administration Menu.
 




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

Q: I enabled "Aggregate and compress CSS files", but admin_menu.css is still
   there. Is this normal?

A: Yes, this is the intended behavior. the administration menu module only loads
   its stylesheet as needed (i.e., on page requests by logged-on, administrative
   users).





MAINTAINERS
-----------

Current maintainers:
 * Yiğit Suoğlu  - https://github.com/suoglu
 * Baran Dereli  - https://github.com/BaranDer
 * Özgün Şensoy  - https://github.com/osensoy
 * Musab Çevik  - https://github.com/musabc
 * Onur Çalık  - https://github.com/calikonur

This project has been sponsored by:
 * AirTies A.Ş.
   AirTies was established in 2004 by an executive and technical equip who has returned to Turkey from the Silicon Valley with the aim of being the market leaders in Wireless Network Technologies. With its expert R&D team the company designs the hardware and software of their own products. Their products provide wireless high-definition data and media transfer on multiple TVs, notebooks, PC and game consoles. Their product portfolio includes wideband internet devices, local area network products, accesories and set top boxes. In total, AirTies has over 8 million products worldwide. Visit http://www.airties.com.tr for more information.
   

















More information will be avaible soon.
