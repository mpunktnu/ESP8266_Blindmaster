# ESP8266_Blindmaster

This is server software which is installed on a ESP8266 (preferrably Feather HUZZAH) and which controls a motorized blind (or other bi-directional motor) over WiFi.
As I used a *Feather HUZZAH* with a *DC Motor FeatherWing*, this code uses the corresponding Adafruit library (see below). It is of course possible to use some other motor controller.

## Software
This firmware is flashed using the Arduino Core for ESP8266.

###Prerequisites
The following software is absolutely necessary in order to compile this firmware in its current form.
The _WiFiManager_ could be excluded, but in that case WiFi credentials would have to be hardcoded.

* _**Arduino IDE 1.6.2 or higher**_
* _**ESP8266 Arduino Core**_ (I suggest installing with *Tools > Board > Boards manager*: https://github.com/esp8266/Arduino )
* _**[Adafruit Motor Shield V2 Library](https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library)**_ - Download and install in your Arduino/libraries folder (remove .github folder inside to suppress warning)
* _**[WiFiManager](https://github.com/tzapu/WiFiManager)**_ - Great tool. If the ESP8266 is flashed with this and can't find a network to login to, it will enable WiFi-AP mode. It is then possible to connect to it and specify network/password. It is also possible to save other settings, see examples on their Github.

## Hardware
This is all the hardware I used for the PoC. PSU, UBEC and motor may be exchanged for other items.

* _**Adafruit Feather HUZZAH with ESP8266** (PID: 2821)_ - No introduction required, I expect. This lovely little device is the magic brain WiFi thingy.
* _**Adafruit DC Motor FeatherWing** (PID: 2927)_ - Will work for any _4.5-13.5 VDC_ bi-directional DC motor, and probably up to 4 motors (code only controls one)
* _**UBEC DC/DC Step-Down Converter - 5V**_ - This little circuit can be used to transform 5-23 VDC into 5 VDC. I used one of these to provide power to the Feather HUZZAH, since it can not be powered from the FeatherWing.
* _**12 VDC PSU**_ - I used a 12V/1A power supply. It is connected directly to the FeatherWing, and also to the UBEC which in turn provides 5VDC to the Feather HUZZAH (over the USB/GND pins).
* _**Blind motor**_ - Bofu ES1612 is suitable. But as long as you have the correct PSU, any _4.5-13.5 VDC_ motor will do.

## Plans for the future

* _Better UI_ - I'm not a web designer. The current design works (NEW! It scales!), but the UI could probably look better and scale better on mobiles.
* _Sensor control_ - Automate the motor controller based on input from sensors, HTTP etc.
* _???_ - Profit?
