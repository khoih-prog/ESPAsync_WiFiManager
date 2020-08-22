/****************************************************************************************************************************
  ModelessWithInterrupts.ino
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

#if !defined(ESP8266)
  #error This code is intended to run on the ESP8266! Please check your Tools->Board setting.
#endif

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ESPASYNC_WIFIMGR_LOGLEVEL_       3

// Default is 30s, using 20s now
#define TIME_BETWEEN_MODAL_SCANS          20000

// Default is 60s, using 30s now
#define TIME_BETWEEN_MODELESS_SCANS       30000

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>

// Use false if you don't like to display Available Pages in Information Page of Config Portal
// Comment out or use true to display Available Pages in Information Page of Config Portal
// Must be placed before #include <ESPAsync_WiFiManager.h>
#define USE_AVAILABLE_PAGES     true

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
  
  IPAddress stationIP   = IPAddress(192, 168, 2, 186);
  IPAddress gatewayIP   = IPAddress(192, 168, 2, 1);
  IPAddress netMask     = IPAddress(255, 255, 255, 0);
#endif

#define USE_CONFIGURABLE_DNS      true

IPAddress dns1IP      = gatewayIP;
IPAddress dns2IP      = IPAddress(8, 8, 8, 8);

#include <ESPAsync_WiFiManager.h>              //https://github.com/khoih-prog/ESPAsync_WiFiManager

AsyncWebServer webServer(80);
DNSServer dnsServer;

ESPAsync_WiFiManager ESPAsync_wifiManager(&webServer, &dnsServer, "ModelessConnect");

void heartBeatPrint(void)
{
  static int num = 1;

  if (WiFi.status() == WL_CONNECTED)
    Serial.print("W");        // W means connected to WiFi
  else
    Serial.print("N");        // N means not connected to WiFi

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 5 == 0)
  {
    Serial.print(" ");
  }
}

void check_status()
{
  static ulong checkstatus_timeout = 0;

#define HEARTBEAT_INTERVAL    10000L
  // Print hearbeat every HEARTBEAT_INTERVAL (10) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
}

volatile boolean guard = true;
const uint32_t callCycleCount = ESP.getCpuFreqMHz() * 1024 / 8;

/*
   If some other code was in the process of calling a method in
   WiFi, ESP or EEPROM, and we do too, there is a very good chance
   a reset will happen.
*/
void ICACHE_RAM_ATTR interruptFunction()
{
  /*
     This is equivalent to:
     timer0_write(ESP.getCycleCount() + ESP.getCpuFreqMHz() * 1024 / 8)
     But that could clash with the main thread code.
  */
  uint32_t ccount;
  __asm__ __volatile__("esync; rsr %0,ccount":"=a" (ccount));

  timer0_write(ccount + callCycleCount);

  if (!guard)
  {
    // An example call that would cause a reset if it happens to be called while AsyncWiFiManager 
    // is also calling methods that modify flash. Uncomment to see it will cause crash.
    //ESP.getChipId();
  }
}

String helloString = "ModelessWithInterrupts on " + String(ARDUINO_BOARD);

void setup()
{
  // Put your setup code here, to run once
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStarting " + helloString);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  //reset saved settings
  //ESPAsync_wifiManager.resetSettings();

  ESPAsync_wifiManager.setMinimumSignalQuality(-1);

  // Set config portal channel, default = 1. Use 0 => random channel from 1-13
  ESPAsync_wifiManager.setConfigPortalChannel(0);

  //set custom ip for portal
  //ESPAsync_wifiManager.setAPStaticIPConfig(IPAddress(192, 168, 100, 1), IPAddress(192, 168, 100, 1), IPAddress(255, 255, 255, 0));
    
#if !USE_DHCP_IP    
  #if USE_CONFIGURABLE_DNS  
    // Set static IP, Gateway, Subnetmask, DNS1 and DNS2.
    ESPAsync_wifiManager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask, dns1IP, dns2IP);  
  #else
    // Set static IP, Gateway, Subnetmask, Use auto DNS1 and DNS2.
    ESPAsync_wifiManager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask);
  #endif 
#endif  

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an AP with the specified name "AutoConnectAP"/"password"
  //and goes into a blocking loop awaiting configuration
  //ESPAsync_wifiManager.autoConnect("AutoConnectAP", "password";
  //or use this for auto generated name ESP + ChipID
  //ESPAsync_wifiManager.autoConnect();
  ESPAsync_wifiManager.startConfigPortalModeless("ModelessAP", "Password");

  webServer.on("/", HTTP_GET, [](AsyncWebServerRequest * request) 
  {
    request->send(200, "text/plain", "Hello from " + helloString);
  });

  // Set up some code that could cause a reset.
  guard = true;
  timer0_isr_init();
  timer0_attachInterrupt(interruptFunction);
  timer0_write(ESP.getCycleCount() + ESP.getCpuFreqMHz() * 1024);	// Wait 2 seconds before displaying
}

void loop() 
{
  // put your main code here, to run repeatedly:
  // This can be called with guarding interrupt routines - so
  // interrupt routines can interrupt it!
  ESPAsync_wifiManager.safeLoop();

  // this is just for checking if we are connected to WiFi
  check_status();

  guard = true;
  // This call can not be interrupted without possibly causing a reset.
  ESPAsync_wifiManager.criticalLoop();
  guard = false;
}
