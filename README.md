# Home Automation with NodeMCU and Alexa using fauxmoESP

This is a library for ESP8266/ESP32-based devices that emulates Philips Hue lights and thus allows you to control them using this protocol, in particular from Alexa-powered devices like the Amazon Echo or the Dot.
The library can be found on Xose Perez's BitBucket: fauxmoESP

The below video, shows how the project will look like at the end:


### Material 
1. NodeMCU ESP8266-12E 
2. Echo Dot (2nd Generation) 
3. 2 X Mini BreadBoard 
4. 4-Channel Relay Module 
5. Male-Female Dupont Cables
6. External 5V power Supply 

### Dependencies
1. [fauxmoESP Library ZIP](https://github.com/MamunHoque/fauxmoESP/blob/master/libraries/xoseperez-fauxmoesp-56183f1df105.zip?raw=true)
In order to run it in your code, you will also need 2 more libraries by Hristo Gochkov:
2. [ESPAsyncTCP](https://github.com/MamunHoque/fauxmoESP/blob/master/libraries/ESPAsyncTCP-master.zip?raw=true)
3. [ESPAsyncWebServer](https://github.com/MamunHoque/fauxmoESP/blob/master/libraries/ESPAsyncWebServer-master.zip?raw=true)
## Step One:
### Download or clone full source code from here: [Source Code](https://github.com/MamunHoque/fauxmoESP/archive/master.zip)

So, Unzip the files and Go to your Arduino IDE and install the 3 above libraries form libraries folder under your Arduino/Library directory or Install by zip option.

## Step Two:
Open the file NodeMCU_with_Alexa_Home_Automation.ino from my GitHub folder and change the dummy wifi credentials, with your own:

/* Network credentials */
#define WIFI_SSID "YOUR SSID HERE"
#define WIFI_PASS "YOUR PASSWORD HERE"

Select your board and upload to NodeMCU board. 

## Step Four: 

### Diagram
Let's connect a 4 Channel relay module to control 2 lamps and 2 outlets as shown in above diagram.

We will create 4 "single smart devices":
Light1 ==> Relay 1 ==> NodeMCU D5
Light2 ==> Relay 3 ==> NodeMCU D7
Outlet1 ==> Relay 2 ==> NodeMCU D6
Outlet2 ==> Relay 4 ==> NodeMCU D8
and 3 groups of combined devices:

All Devices (Light1, Light2, Outlet1 and Outlet2)
Living Room (Light1 and Outlet1)
Bed Room (Light2 and Outlet2)


### Credits:
Based on [ALEXA - NODEMCU: WEMO EMULATION MADE SIMPLE
By mjrovai](https://www.instructables.com/id/Alexa-NodeMCU-WeMo-Emulation-Made-Simple/)