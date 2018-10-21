#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif
#include "fauxmoESP.h"


#define WIFI_SSID "..your wifi name.."
#define WIFI_PASS "..your wifi password.."

#define SERIAL_BAUDRATE                 115200
#define LED                             2

/* Set Relay Pins */
#define RELAY_1 D5
#define RELAY_2 D6
#define RELAY_3 D7
#define RELAY_4 D8


fauxmoESP fauxmo;
// -----------------------------------------------------------------------------
// Wifi
// -----------------------------------------------------------------------------

void wifiSetup() {

    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

}

void setup() {

     Serial.begin(SERIAL_BAUDRATE);
   //setup and wifi connection
   wifiSetup();
 
   //Set relay pins to outputs
   pinMode(RELAY_1, OUTPUT);
   pinMode(RELAY_2, OUTPUT);
   pinMode(RELAY_3, OUTPUT);
   pinMode(RELAY_4, OUTPUT);

   //Set each relay pin to HIGH ====== NOTE THAT THE RELAYS USE INVERSE LOGIC =====
   digitalWrite(RELAY_1, HIGH);   
   delay(500);
   digitalWrite(RELAY_2, HIGH);  
   delay(500);
   digitalWrite(RELAY_3, HIGH);  
   delay(500);
   digitalWrite(RELAY_4, HIGH);   
   delay(500);
    
 

    // You have to call enable(true) once you have a WiFi connection
    // You can enable or disable the library at any moment
    // Disabling it will prevent the devices from being discovered and switched
    fauxmo.enable(true);
    fauxmo.enable(false);
    fauxmo.enable(true);

   // Device Names for Simulated Wemo switches
   fauxmo.addDevice("Light One");
   fauxmo.addDevice("Light Two");
   fauxmo.addDevice("Outlet One");
   fauxmo.addDevice("Outlet Two");
   fauxmo.addDevice("Bed Room");
   fauxmo.addDevice("Living Room");
   fauxmo.addDevice("All Devices");


    // fauxmoESP 2.0.0 has changed the callback signature to add the device_id,
    // this way it's easier to match devices to action without having to compare strings.
    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
        digitalWrite(LED, !state);

         //Switching action on detection of device name
  
        if ( (strcmp(device_name, "Light One") == 0) ) 
        {
          if (!state) 
          {
            digitalWrite(RELAY_1, HIGH);
          } 
          else 
          {
            digitalWrite(RELAY_1, LOW);
          }
        }

         if ( (strcmp(device_name, "Light Two") == 0) ) 
        {
          if (!state) 
          {
            digitalWrite(RELAY_3, HIGH);
          } 
          else 
          {
            digitalWrite(RELAY_3, LOW);
          }
        }
        
        if ( (strcmp(device_name, "Outlet One") == 0) ) 
        {
          if (!state) 
          {
            digitalWrite(RELAY_2, HIGH);
          } 
          else 
          {
            digitalWrite(RELAY_2, LOW);
          }
        }
        
        if ( (strcmp(device_name, "Outlet Two") == 0) ) 
        {
          if (!state) 
          {
            digitalWrite(RELAY_4, HIGH);
          } 
          else 
          {
            digitalWrite(RELAY_4, LOW);
          }
        }
        
        if ( (strcmp(device_name, "Bed Room") == 0) ) 
        {
          if (!state) 
          {
            digitalWrite(RELAY_3, HIGH);
            digitalWrite(RELAY_4, HIGH);
          } 
          else 
          {
            digitalWrite(RELAY_3, LOW);
            digitalWrite(RELAY_4, LOW);
          }
        }
        
        if ( (strcmp(device_name, "Living Room") == 0) ) 
        {
          if (!state) 
          {
            digitalWrite(RELAY_1, HIGH);
            digitalWrite(RELAY_2, HIGH);
          } 
          else 
          {
            digitalWrite(RELAY_1, LOW);
            digitalWrite(RELAY_2, LOW);
          }
        }
       
        if ( (strcmp(device_name, "All Devices") == 0) ) 
        {
          if (!state) 
          {
            digitalWrite(RELAY_1, HIGH);
            digitalWrite(RELAY_2, HIGH);
            digitalWrite(RELAY_3, HIGH);
            digitalWrite(RELAY_4, HIGH);
          } 
          else 
          {
            digitalWrite(RELAY_1, LOW);
            digitalWrite(RELAY_2, LOW);
            digitalWrite(RELAY_3, LOW);
            digitalWrite(RELAY_4, LOW);
          }
        }

  
    });

}

void loop() {

    // Since fauxmoESP 2.0 the library uses the "compatibility" mode by
    // default, this means that it uses WiFiUdp class instead of AsyncUDP.
    // The later requires the Arduino Core for ESP8266 staging version
    // whilst the former works fine with current stable 2.3.0 version.
    // But, since it's not "async" anymore we have to manually poll for UDP
    // packets
    fauxmo.handle();

    static unsigned long last = millis();
    if (millis() - last > 5000) {
        last = millis();
        Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
    }

}