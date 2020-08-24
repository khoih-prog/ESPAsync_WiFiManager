/****************************************************************************************************************************
  Async_ESP32_FSWebServer_DRD - Example WebServer with SPIFFS backend for ESP32
  For ESP32 boards

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
/*****************************************************************************************************************************
   Compare this efficient Async_ESP32_FSWebServer_DRD example with the so complicated twin ESP32_FSWebServer 
   in (https://github.com/khoih-prog/ESP_WiFiManager) to appreciate the powerful AsynWebServer.

   How To Upload Files:
   1) Go to http://async-esp32fs.local/edit, then "Choose file" -> "Upload"
   2) or Upload the contents of the data folder with MkSPIFFS Tool ("ESP8266 Sketch Data Upload" in Tools menu in Arduino IDE)
   3) or you can upload the contents of a folder if you CD in that folder and run the following command:
      for file in `\ls -A1`; do curl -F "file=@$PWD/$file" esp8266fs.local/edit; done
   
   How To Use:
   1) access the sample web page at http://async-esp32fs.local
   2) edit the page by going to http://async-esp32fs.local/edit
   3. Use configurable user/password to login. Default is admin/admin
*****************************************************************************************************************************/

#if !defined(ESP32)
#error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
#endif

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ESPASYNC_WIFIMGR_LOGLEVEL_    3

// Default is 30s, using 20s now
#define TIME_BETWEEN_MODAL_SCANS          20000

// Default is 60s, using 30s now
#define TIME_BETWEEN_MODELESS_SCANS       30000

#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

// You only need to format the filesystem once
//#define FORMAT_FILESYSTEM true
#define FORMAT_FILESYSTEM false

#define USE_SPIFFS            true

#if USE_SPIFFS
#include <SPIFFS.h>
FS* filesystem = &SPIFFS;
#define FILESYSTEM              SPIFFS
#define ESP_DRD_USE_SPIFFS      true
#else
// Use FFat
#include <FFat.h>
FS* filesystem = &FFat;
#define FILESYSTEM              FFat
//#define ESP_DRD_USE_EEPROM      true
#define ESP_DRD_USE_SPIFFS      true
#endif

#include <SPIFFSEditor.h>

#define DOUBLERESETDETECTOR_DEBUG       true  //false

#include <ESP_DoubleResetDetector.h>      //https://github.com/khoih-prog/ESP_DoubleResetDetector

// Number of seconds after reset during which a
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

//DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);
DoubleResetDetector* drd = NULL;
//////

// Indicates whether ESP has WiFi credentials saved from previous session, or double reset detected
bool initialConfig = false;

// SSID and PW for Config Portal
String ssid = "ESP_" + String((uint32_t)ESP.getEfuseMac(), HEX);
const char* password = "your_password";

// SSID and PW for your Router
String Router_SSID;
String Router_Pass;

// Use false if you don't like to display Available Pages in Information Page of Config Portal
// Comment out or use true to display Available Pages in Information Page of Config Portal
// Must be placed before #include <ESP_WiFiManager.h>
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

#define HTTP_PORT     80

#include <ESPAsync_WiFiManager.h>              //https://github.com/khoih-prog/ESPAsync_WiFiManager

AsyncWebServer server(HTTP_PORT);
DNSServer dnsServer;

AsyncEventSource events("/events");

String host = "async-esp32fs";

String http_username = "admin";
String http_password = "admin";

String separatorLine = "===============================================================";


//format bytes
String formatBytes(size_t bytes)
{
  if (bytes < 1024)
  {
    return String(bytes) + "B";
  }
  else if (bytes < (1024 * 1024))
  {
    return String(bytes / 1024.0) + "KB";
  }
  else if (bytes < (1024 * 1024 * 1024))
  {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  }
  else
  {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

void setup(void)
{
  Serial.begin(115200);
  while (!Serial);

  Serial.setDebugOutput(false);

  bool FileFSReady = true;

  if (FORMAT_FILESYSTEM)
    FILESYSTEM.format();

#if USE_SPIFFS 
  Serial.println("\nStarting Async_ESP32_FSWebServer_DRD using USE_SPIFFS on " + String(ARDUINO_BOARD));

  // Format SPIFFS if not yet
  if (!FILESYSTEM.begin(true))
  {
    Serial.println(F("SPIFFS failed! Formatting."));
    
    if (!FILESYSTEM.begin())
    {
      Serial.println(F("SPIFFS failed!"));
      FileFSReady = false;
    }
  }
#else
  Serial.println("\nStarting Async_ESP32_FSWebServer_DRD using FFat on " + String(ARDUINO_BOARD));
  
  FILESYSTEM.begin();
#endif
 
  if (FileFSReady)
  {
    File root = FILESYSTEM.open("/");
    File file = root.openNextFile();

    while (file)
    {
      String fileName = file.name();
      size_t fileSize = file.size();

      Serial.println("FS File: " + fileName + ", size: " + formatBytes(fileSize));

      file = root.openNextFile();
    }

    Serial.println();
  }

  drd = new DoubleResetDetector(DRD_TIMEOUT, DRD_ADDRESS);

  if (!drd)
    Serial.println(F("Can't instantiate. Disable DRD feature"));
    
  unsigned long startedAt = millis();

  //Local intialization. Once its business is done, there is no need to keep it around
  // Use this to default DHCP hostname to ESP8266-XXXXXX or ESP32-XXXXXX
  //ESPAsync_WiFiManager ESPAsync_wifiManager(&webServer, &dnsServer);
  // Use this to personalize DHCP hostname (RFC952 conformed)
  ESPAsync_WiFiManager ESPAsync_wifiManager(&server, &dnsServer, "Async_ESP32-FSWebServer");

  //set custom ip for portal
  ESPAsync_wifiManager.setAPStaticIPConfig(IPAddress(192, 168, 100, 1), IPAddress(192, 168, 100, 1), IPAddress(255, 255, 255, 0));

  ESPAsync_wifiManager.setMinimumSignalQuality(-1);

  // Set config portal channel, default = 1. Use 0 => random channel from 1-13
  ESPAsync_wifiManager.setConfigPortalChannel(0);
  //////

#if !USE_DHCP_IP
#if USE_CONFIGURABLE_DNS
  // Set static IP, Gateway, Subnetmask, DNS1 and DNS2.
  ESPAsync_wifiManager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask, dns1IP, dns2IP);
#else
  // Set static IP, Gateway, Subnetmask, Use auto DNS1 and DNS2.
  ESPAsync_wifiManager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask);
#endif
#endif

  // We can't use WiFi.SSID() in ESP32as it's only valid after connected.
  // SSID and Password stored in ESP32 wifi_ap_record_t and wifi_config_t are also cleared in reboot
  // Have to create a new function to store in EEPROM/SPIFFS for this purpose
  Router_SSID = ESPAsync_wifiManager.WiFi_SSID();
  Router_Pass = ESPAsync_wifiManager.WiFi_Pass();

  //Remove this line if you do not want to see WiFi password printed
  Serial.println("Stored: SSID = " + Router_SSID + ", Pass = " + Router_Pass);

  // SSID to uppercase
  ssid.toUpperCase();

  if (Router_SSID != "")
  {
    ESPAsync_wifiManager.setConfigPortalTimeout(60); //If no access point name has been previously entered disable timeout.
    Serial.println("Got stored Credentials. Timeout 60s for Config Portal");
  }
  else
  {
    Serial.println("Open Config Portal without Timeout: No stored Credentials.");
    initialConfig = true;
  }

  if (drd && drd->detectDoubleReset())
  {
    // DRD, disable timeout.
    ESPAsync_wifiManager.setConfigPortalTimeout(0);
    
    Serial.println("Open Config Portal without Timeout: Double Reset Detected");
    initialConfig = true;
  }

  if (initialConfig)
  {
    // Starts an access point
    if (!ESPAsync_wifiManager.startConfigPortal((const char *) ssid.c_str(), password))
      Serial.println("Not connected to WiFi but continuing anyway.");
    else
      Serial.println("WiFi connected...yeey :)");
  }

#define WIFI_CONNECT_TIMEOUT        30000L
#define WHILE_LOOP_DELAY            200L
#define WHILE_LOOP_STEPS            (WIFI_CONNECT_TIMEOUT / ( 3 * WHILE_LOOP_DELAY ))

  startedAt = millis();

  while ( (WiFi.status() != WL_CONNECTED) && (millis() - startedAt < WIFI_CONNECT_TIMEOUT ) )
  {
    WiFi.mode(WIFI_STA);
    WiFi.persistent (true);

    // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(Router_SSID);

    WiFi.config(stationIP, gatewayIP, netMask);
    //WiFi.config(stationIP, gatewayIP, netMask, dns1IP, dns2IP);

    WiFi.begin(Router_SSID.c_str(), Router_Pass.c_str());

    int i = 0;

    while ((!WiFi.status() || WiFi.status() >= WL_DISCONNECTED) && i++ < WHILE_LOOP_STEPS)
    {
      delay(WHILE_LOOP_DELAY);
    }
  }

  Serial.print("\nConnected! IP address: ");
  Serial.println(WiFi.localIP());

  if ( !MDNS.begin(host.c_str()) )
  {
    Serial.println("Error starting MDNS responder!");
  }
  
  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", HTTP_PORT);
  
  //SERVER INIT
  events.onConnect([](AsyncEventSourceClient * client)
  {
    client->send("hello!", NULL, millis(), 1000);
  });

  server.addHandler(&events);

  server.on("/heap", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send(200, "text/plain", String(ESP.getFreeHeap()));
  });

  if (FileFSReady)
  {
    server.addHandler(new SPIFFSEditor(SPIFFS, http_username, http_password));
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm");
  }

  server.onNotFound([](AsyncWebServerRequest * request)
  {
    Serial.print("NOT_FOUND: ");

    if (request->method() == HTTP_GET)
      Serial.print("GET");
    else if (request->method() == HTTP_POST)
      Serial.print("POST");
    else if (request->method() == HTTP_DELETE)
      Serial.print("DELETE");
    else if (request->method() == HTTP_PUT)
      Serial.print("PUT");
    else if (request->method() == HTTP_PATCH)
      Serial.print("PATCH");
    else if (request->method() == HTTP_HEAD)
      Serial.print("HEAD");
    else if (request->method() == HTTP_OPTIONS)
      Serial.print("OPTIONS");
    else
      Serial.print("UNKNOWN");
    Serial.println(" http://" + request->host() + request->url());

    if (request->contentLength())
    {
      Serial.println("_CONTENT_TYPE: " + request->contentType());
      Serial.println("_CONTENT_LENGTH: " + request->contentLength());
    }

    int headers = request->headers();
    int i;

    for (i = 0; i < headers; i++)
    {
      AsyncWebHeader* h = request->getHeader(i);
      Serial.println("_HEADER[" + h->name() + "]: " + h->value());
    }

    int params = request->params();

    for (i = 0; i < params; i++)
    {
      AsyncWebParameter* p = request->getParam(i);

      if (p->isFile())
      {
        Serial.println("_FILE[" + p->name() + "]: " + p->value() + ", size: " + p->size());
      }
      else if (p->isPost())
      {
        Serial.println("_POST[" + p->name() + "]: " + p->value());
      }
      else
      {
        Serial.println("_GET[" + p->name() + "]: " + p->value());
      }
    }

    request->send(404);
  });

  server.onFileUpload([](AsyncWebServerRequest * request, const String & filename, size_t index, uint8_t *data, size_t len, bool final)
  {
    if (!index)
      Serial.println("UploadStart: " + filename);

    Serial.print((const char*)data);

    if (final)
      Serial.println("UploadEnd: " + filename + "(" + String(index + len) + ")" );
  });

  server.onRequestBody([](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total)
  {
    if (!index)
      Serial.println("BodyStart: " + total);

    Serial.print((const char*)data);

    if (index + len == total)
      Serial.println("BodyEnd: " + total);
  });

  server.begin();

  //////

  Serial.print("HTTP server started @ ");
  Serial.println(WiFi.localIP());

  Serial.println(separatorLine);
  Serial.println("Open http://" + host + ".local/edit to see the file browser");
  Serial.println("Using username = " + http_username + " and password = " + http_password);
  Serial.println(separatorLine);
}

void loop(void)
{
  // Call the double reset detector loop method every so often,
  // so that it can recognise when the timeout expires.
  // You can also call drd.stop() when you wish to no longer
  // consider the next reset as a double reset.
  if (drd)
    drd->loop();
}
