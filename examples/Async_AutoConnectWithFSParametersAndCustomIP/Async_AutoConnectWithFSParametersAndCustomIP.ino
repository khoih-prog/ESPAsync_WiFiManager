/****************************************************************************************************************************
  Async_AutoConnectWithFSParametersAndCustomIPr.ino
  For ESP8266 / ESP32 boards

  ESPAsync_WiFiManager is a library for the ESP8266/Arduino platform, using (ESP)AsyncWebServer to enable easy
  configuration and reconfiguration of WiFi credentials using a Captive Portal.

  Modified from 
  1. Tzapu               (https://github.com/tzapu/WiFiManager)
  2. Ken Taylor          (https://github.com/kentaylor)
  3. Alan Steremberg     (https://github.com/alanswx/ESPAsyncWiFiManager)
  4. Khoi Hoang          (https://github.com/khoih-prog/ESP_WiFiManager)

  Built by Khoi Hoang https://github.com/khoih-prog/ESPAsync_WiFiManager
  Licensed under MIT license
  Version: 1.0.11

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.11   K Hoang      21/08/2020 Initial coding to use (ESP)AsyncWebServer instead of (ESP8266)WebServer. Bump up to v1.0.11
                                   to sync with ESP_WiFiManager v1.0.11
 *****************************************************************************************************************************/
 
#if !( defined(ESP8266) ||  defined(ESP32) )
#error This code is intended to run on the ESP8266 or ESP32 platform! Please check your Tools->Board setting.
#endif

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ESPASYNC_WIFIMGR_LOGLEVEL_       3

// Default is 30s, using 20s now
#define TIME_BETWEEN_MODAL_SCANS          20000

// Default is 60s, using 30s now
#define TIME_BETWEEN_MODELESS_SCANS       30000

#include <FS.h>                   //this needs to be first, or it all crashes and burns...

//Ported to ESP32
//For ESP32, To use ESP32 Dev Module, QIO, Flash 4MB/80MHz, Upload 921600
#if ESP32
#include "SPIFFS.h"
#include <esp_wifi.h>
#include <WiFi.h>
#include <WiFiClient.h>

#define ESP_getChipId()   ((uint32_t)ESP.getEfuseMac())

#define LED_ON      HIGH
#define LED_OFF     LOW

#define FileFS      SPIFFS

#else

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>

#define ESP_getChipId()   (ESP.getChipId())

#define LED_ON      LOW
#define LED_OFF     HIGH

#define USE_LITTLEFS      true

#if USE_LITTLEFS
#define FileFS    LittleFS
#else
#define FileFS    SPIFFS
#endif

#include <LittleFS.h>

#endif

// For Config Portal
// SSID and PW for Config Portal
String ssid           = "ESP_" + String(ESP_getChipId(), HEX);
const char* password  = "your_password";

// SSID and PW for your Router
String Router_SSID;
String Router_Pass;

// Use false if you don't like to display Available Pages in Information Page of Config Portal
// Comment out or use true to display Available Pages in Information Page of Config Portal
// Must be placed before #include <ESPAsync_WiFiManager.h>
#define USE_AVAILABLE_PAGES     false

// From v1.0.10 to permit disable/enable StaticIP configuration in Config Portal from sketch. Valid only if DHCP is used.
// You'll loose the feature of dynamically changing from DHCP to static IP, or vice versa
// You have to explicitly specify false to disable the feature.
//#define USE_STATIC_IP_CONFIG_IN_CP          false

// Use false to disable NTP config. Advisable when using Cellphone, Tablet to access Config Portal.
// See Issue 23: On Android phone ConfigPortal is unresponsive (https://github.com/khoih-prog/ESP_WiFiManager/issues/23)
#define USE_ESP_WIFIMANAGER_NTP     false

// Use true to enable CloudFlare NTP service. System can hang if you don't have Internet access while accessing CloudFlare
// See Issue #21: CloudFlare link in the default portal (https://github.com/khoih-prog/ESP_WiFiManager/issues/21)
#define USE_CLOUDFLARE_NTP          false

// New in v1.0.11
#define USING_CORS_FEATURE          true
//////

// Use USE_DHCP_IP == true for dynamic DHCP IP, false to use static IP which you have to change accordingly to your network
#if (defined(USE_STATIC_IP_CONFIG_IN_CP) && !USE_STATIC_IP_CONFIG_IN_CP)
// Force DHCP to be true
#if defined(USE_DHCP_IP)
#undef USE_DHCP_IP
#endif
#define USE_DHCP_IP     true
#else
// You can select DHCP or Static IP here
//#define USE_DHCP_IP     true
#define USE_DHCP_IP     false
#endif

#if ( USE_DHCP_IP || ( defined(USE_STATIC_IP_CONFIG_IN_CP) && !USE_STATIC_IP_CONFIG_IN_CP ) )
// Use DHCP
#warning Using DHCP IP
IPAddress stationIP   = IPAddress(0, 0, 0, 0);
IPAddress gatewayIP   = IPAddress(192, 168, 2, 1);
IPAddress netMask     = IPAddress(255, 255, 255, 0);
#else
// Use static IP
#warning Using static IP
#ifdef ESP32
IPAddress stationIP   = IPAddress(192, 168, 2, 232);
#else
IPAddress stationIP   = IPAddress(192, 168, 2, 186);
#endif

IPAddress gatewayIP   = IPAddress(192, 168, 2, 1);
IPAddress netMask     = IPAddress(255, 255, 255, 0);
#endif

#define USE_CONFIGURABLE_DNS      true

IPAddress dns1IP      = gatewayIP;
IPAddress dns2IP      = IPAddress(8, 8, 8, 8);

#include <ESPAsync_WiFiManager.h>              //https://github.com/khoih-prog/ESPAsync_WiFiManager

AsyncWebServer webServer(80);
DNSServer dnsServer;

// Now support ArduinoJson 6.0.0+ ( tested with v6.15.2 to v6.16.1 )
#include <ArduinoJson.h>        // get it from https://arduinojson.org/ or install via Arduino library manager

const char* CONFIG_FILE = "/config.json";

//define your default values here, if there are different values in config.json, they are overwritten.
//length should be max size + 1
char mqtt_server  [40]  = "mqtt-server.ddns.net";
char mqtt_port    [6]   = "1883";
char blynk_token  [33]  = "YOUR_BLYNK_TOKEN";

//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback ()
{
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void setup()
{
  // Put your setup code here, to run once
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStarting Async_AutoConnectWithFSParametersAndCustomIP on " + String(ARDUINO_BOARD));

  //clean FS, for testing
  //FileFS.format();

  // Mount the filesystem
  bool result = FileFS.begin();

#if USE_LITTLEFS
  Serial.print("\nLittleFS opened: ");
#else
  Serial.print("\nSPIFFS opened: ");
#endif

  Serial.println(result ? "OK" : "Failed");

  //read configuration from FS json
  Serial.println("Mounting FS...");

  if (result) 
  {
    Serial.println("Mounted file system");
    
    if (FileFS.exists(CONFIG_FILE)) 
    {
      //file exists, reading and loading
      Serial.println("Reading config file");
      
      File configFile = FileFS.open(CONFIG_FILE, "r");
      
      if (configFile) 
      {
        Serial.println("Opened config file");
        
        size_t size = configFile.size();
        
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);

#if (ARDUINOJSON_VERSION_MAJOR >= 6)

        DynamicJsonDocument json(1024);
        auto deserializeError = deserializeJson(json, buf.get());

        serializeJson(json, Serial);
        
        if ( !deserializeError )    
#else
        DynamicJsonBuffer jsonBuffer;
        
        // Parse JSON string
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        
        json.printTo(Serial);

        // Test if parsing succeeds.
        if (json.success()) 
#endif        
        {
          Serial.println("\nParsed json");

          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_port,   json["mqtt_port"]);
          strcpy(blynk_token, json["blynk_token"]);
        }  
        else 
        {
          Serial.println("Failed to load json config");
        }
      }
    }
  } 
  else 
  {
    Serial.println("Failed to mount FS");
  }
  
  //end read
  Serial.println(String("MQTT Server = ") + mqtt_server);
  Serial.println(String("MQTT Port   = ") + mqtt_port);
  Serial.println(String("Blynk Token = ") + blynk_token);
  
  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length
  ESPAsync_WMParameter custom_mqtt_server ("server",  "mqtt server",  mqtt_server,  40);
  ESPAsync_WMParameter custom_mqtt_port   ("port",    "mqtt port",    mqtt_port,    5);
  ESPAsync_WMParameter custom_blynk_token ("blynk",   "blynk token",  blynk_token,  34);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  //ESPAsync_WiFiManager ESPAsync_wifiManager(&&webServer, &dnsServer,);
  //Here starts the WiFi Manager initialization
  //Local intialization. Once its business is done, there is no need to keep it around
  ESPAsync_WiFiManager ESPAsync_wifiManager(&webServer, &dnsServer, "AutoConnectFS");

  //set config save notify callback
  ESPAsync_wifiManager.setSaveConfigCallback(saveConfigCallback);

  //set custom ip for portal
  //ESPAsync_wifiManager.setAPStaticIPConfig(IPAddress(192, 168, 100, 1), IPAddress(192, 168, 100, 1), IPAddress(255, 255, 255, 0));
  
#if !USE_DHCP_IP    
  #if USE_CONFIGURABLE_DNS  
    // Set static IP, Gateway, Subnetmask, DNS1 and DNS2. New in v1.0.5
    ESPAsync_wifiManager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask, dns1IP, dns2IP);  
  #else
    // Set static IP, Gateway, Subnetmask, Use auto DNS1 and DNS2.
    ESPAsync_wifiManager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask);
  #endif 
#endif  

  //add all your parameters here
  ESPAsync_wifiManager.addParameter(&custom_mqtt_server);
  ESPAsync_wifiManager.addParameter(&custom_mqtt_port);
  ESPAsync_wifiManager.addParameter(&custom_blynk_token);

  //reset settings - for testing
  //ESPAsync_wifiManager.resetSettings();

  // Set config portal channel, default = 1. Use 0 => random channel from 1-13
  ESPAsync_wifiManager.setConfigPortalChannel(0);

  //set minimum quality of signal so it ignores AP's under that quality, defaults to 8%
  ESPAsync_wifiManager.setMinimumSignalQuality();
  //ESPAsync_wifiManager.setMinimumSignalQuality(-1);

  // Sets timeout in seconds until configuration portal gets turned off.
  // If not specified device will remain in configuration mode until
  // switched off via webserver or device is restarted.
  //ESPAsync_wifiManager.setConfigPortalTimeout(120);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an AP with the specified name "AutoConnectAP"/"password"
  //and goes into a blocking loop awaiting configuration
  if (!ESPAsync_wifiManager.autoConnect("AutoConnectAP", "password")) 
  {
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
#ifdef ESP8266
    ESP.reset();
#else    //ESP32
    ESP.restart();
#endif
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("Connected...yeey :)");

  //read updated parameters
  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(blynk_token, custom_blynk_token.getValue());

  //save the custom parameters to FS
  if (shouldSaveConfig) 
  {
    Serial.println("Saving config");

#if (ARDUINOJSON_VERSION_MAJOR >= 6)
    DynamicJsonDocument json(1024);
#else
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
#endif
    
    json["mqtt_server"] = mqtt_server;
    json["mqtt_port"]   = mqtt_port;
    json["blynk_token"] = blynk_token;

    File configFile     = FileFS.open(CONFIG_FILE, "w");
    
    if (!configFile) 
    {
      Serial.println("Failed to open config file for writing");
    }

#if (ARDUINOJSON_VERSION_MAJOR >= 6)
    serializeJsonPretty(json, Serial);
    // Write data to file and close it
    serializeJson(json, configFile);
#else
    json.prettyPrintTo(Serial);
    // Write data to file and close it
    json.printTo(configFile);
#endif
    
    configFile.close();
    //end save
  }

  Serial.print("Local IP = ");
  Serial.println(WiFi.localIP());
  Serial.print("GateWay IP = ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("SubnetMask = "); 
  Serial.println(WiFi.subnetMask());
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
