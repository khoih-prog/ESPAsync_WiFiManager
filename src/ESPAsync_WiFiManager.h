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
  
  Version: 1.12.2

  Version Modified By  Date      Comments
  ------- -----------  ---------- -----------
  1.0.11  K Hoang      21/08/2020 Initial coding to use (ESP)AsyncWebServer instead of (ESP8266)WebServer. Bump up to v1.0.11
                                  to sync with ESP_WiFiManager v1.0.11
  ...
  1.10.0  K Hoang      29/12/2021 Fix `multiple-definitions` linker error and weird bug related to src_cpp
  1.11.0  K Hoang      17/01/2022 Enable compatibility with old code to include only ESP_WiFiManager.h
  1.12.0  K Hoang      10/02/2022 Add support to new ESP32-S3
  1.12.1  K Hoang      11/02/2022 Add LittleFS support to ESP32-C3. Use core LittleFS instead of Lorol's LITTLEFS for v2.0.0+
  1.12.2  K Hoang      13/03/2022 Optimize code by using passing by `reference` instead of by `value`
 *****************************************************************************************************************************/

#pragma once

#ifndef ESPAsync_WiFiManager_h
#define ESPAsync_WiFiManager_h

#include <ESPAsync_WiFiManager.hpp>              //https://github.com/khoih-prog/ESPAsync_WiFiManager
#include <ESPAsync_WiFiManager-Impl.h>           //https://github.com/khoih-prog/ESPAsync_WiFiManager

#endif    // ESPAsync_WiFiManager_h

