/****************************************************************************************************************************
  ESPAsync_WiFiManager.h
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
  
  Version: 1.11.0

  Version Modified By  Date      Comments
  ------- -----------  ---------- -----------
  1.0.11  K Hoang      21/08/2020 Initial coding to use (ESP)AsyncWebServer instead of (ESP8266)WebServer. Bump up to v1.0.11
                                  to sync with ESP_WiFiManager v1.0.11
  1.1.1   K Hoang      29/08/2020 Add MultiWiFi feature to autoconnect to best WiFi at runtime to sync with
                                  ESP_WiFiManager v1.1.1. Add setCORSHeader function to allow flexible CORS
  1.1.2   K Hoang      17/09/2020 Fix bug in examples.
  1.2.0   K Hoang      15/10/2020 Restore cpp code besides Impl.h code to use if linker error. Fix bug.
  1.3.0   K Hoang      04/12/2020 Add LittleFS support to ESP32 using LITTLEFS Library
  1.4.0   K Hoang      18/12/2020 Fix staticIP not saved. Add functions. Add complex examples.
  1.4.1   K Hoang      21/12/2020 Fix bug and compiler warnings.
  1.4.2   K Hoang      21/12/2020 Fix examples' bug not using saved WiFi Credentials after losing all WiFi connections.
  1.4.3   K Hoang      23/12/2020 Fix examples' bug not saving Static IP in certain cases.
  1.5.0   K Hoang      13/02/2021 Add support to new ESP32-S2. Optimize code.
  1.6.0   K Hoang      25/02/2021 Fix WiFi Scanning bug.
  1.6.1   K Hoang      26/03/2021 Modify multiWiFi-related timings to work better with latest esp32 core v1.0.6
  1.6.2   K Hoang      08/04/2021 Fix example misleading messages.
  1.6.3   K Hoang      13/04/2021 Allow captive portal to run more than once by closing dnsServer.
  1.7.0   K Hoang      20/04/2021 Add support to new ESP32-C3 using SPIFFS or EEPROM
  1.7.1   K Hoang      25/04/2021 Fix MultiWiFi bug. Fix captive-portal bug if CP AP address is not default 192.168.4.1
  1.8.0   K Hoang      30/04/2021 Set _timezoneName. Add support to new ESP32-S2 (METRO_ESP32S2, FUNHOUSE_ESP32S2, etc.)
  1.8.1   K Hoang      06/05/2021 Fix bug. Don't display invalid time when not synch yet.
  1.9.0   K Hoang      08/05/2021 Add WiFi /scan page. Fix timezoneName not displayed in Info page. Clean up.
  1.9.1   K Hoang      18/05/2021 Fix warnings with ESP8266 core v3.0.0
  1.9.2   K Hoang      02/08/2021 Fix Mbed TLS compile error and MultiWiFi connection issue with ESP32 core v2.0.0-rc1+
  1.9.3   K Hoang      13/08/2021 Add WiFi scanning of hidden SSIDs
  1.9.4   K Hoang      10/10/2021 Update `platform.ini` and `library.json`
  1.9.5   K Hoang      26/11/2021 Auto detect ESP32 core and use either built-in LittleFS or LITTLEFS library
  1.9.6   K Hoang      26/11/2021 Fix compile error for ESP32 core v1.0.5-
  1.9.7   K Hoang      30/11/2021 Fix bug to permit using HTTP port different from 80
  1.9.8   K Hoang      01/12/2021 Fix bug returning IP `255.255.255.255` in core v2.0.0+ when using `hostname`
  1.10.0  K Hoang      29/12/2021 Fix `multiple-definitions` linker error and weird bug related to src_cpp
  1.11.0  K Hoang      17/01/2022 Enable compatibility with old code to include only ESP_WiFiManager.h
 *****************************************************************************************************************************/

#pragma once

#ifndef ESPAsync_WiFiManager_h
#define ESPAsync_WiFiManager_h

#include <ESPAsync_WiFiManager.hpp>              //https://github.com/khoih-prog/ESPAsync_WiFiManager
#include <ESPAsync_WiFiManager-Impl.h>           //https://github.com/khoih-prog/ESPAsync_WiFiManager

#endif    // ESPAsync_WiFiManager_h

