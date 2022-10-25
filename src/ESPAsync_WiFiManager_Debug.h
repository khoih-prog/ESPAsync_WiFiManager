/****************************************************************************************************************************
  ESPAsync_WiFiManager_Debug.h
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

  Version: 1.15.1

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
  1.13.0  K Hoang      18/08/2022 Using AsynsDNSServer instead of DNSServer
  1.14.0  K Hoang      09/09/2022 Fix ESP32 chipID and add ESP_getChipOUI()
  1.14.1  K Hoang      15/09/2022 Remove dependency on ESP_AsyncWebServer, ESPAsyncTCP and AsyncTCP in `library.properties`
  1.15.0  K Hoang      07/10/2022 Optional display Credentials (SSIDs, PWDs) in Config Portal
  1.15.1  K Hoang      25/10/2022 Using random channel for softAP without password. Add astyle using allman style
 *****************************************************************************************************************************/

#pragma once

#ifndef ESPAsync_WiFiManager_Debug_H
#define ESPAsync_WiFiManager_Debug_H

#ifdef ESPASYNC_WIFIMGR_DEBUG_PORT
  #define DBG_PORT_ESP_WM      ESPASYNC_WIFIMGR_DEBUG_PORT
#else
  #define DBG_PORT_ESP_WM      Serial
#endif

// Change _ESPASYNC_WIFIMGR_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _ESPASYNC_WIFIMGR_LOGLEVEL_
  #define _ESPASYNC_WIFIMGR_LOGLEVEL_       1
#endif

/////////////////////////////////////////////////////////

const char ESP_WM_MARK[] = "[WM] ";
const char ESP_WM_SP[]   = " ";

#define ESP_WM_PRINT        DBG_PORT_ESP_WM.print
#define ESP_WM_PRINTLN      DBG_PORT_ESP_WM.println

#define ESP_WM_PRINT_MARK   ESP_WM_PRINT(ESP_WM_MARK)
#define ESP_WM_PRINT_SP     ESP_WM_PRINT(ESP_WM_SP)

/////////////////////////////////////////////////////////

#define LOGERROR(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { ESP_WM_PRINT_MARK; ESP_WM_PRINTLN(x); }
#define LOGERROR0(x)        if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { ESP_WM_PRINT(x); }
#define LOGERROR1(x,y)      if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(y); }
#define LOGERROR2(x,y,z)    if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP;  ESP_WM_PRINTLN(z); }
#define LOGERROR3(x,y,z,w)  if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINT(z); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(w); }

/////////////////////////////////////////////////////////

#define LOGWARN(x)          if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { ESP_WM_PRINT_MARK; ESP_WM_PRINTLN(x); }
#define LOGWARN0(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { ESP_WM_PRINT(x); }
#define LOGWARN1(x,y)       if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(y); }
#define LOGWARN2(x,y,z)     if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP;  ESP_WM_PRINTLN(z); }
#define LOGWARN3(x,y,z,w)   if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINT(z); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(w); }

/////////////////////////////////////////////////////////

#define LOGINFO(x)          if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { ESP_WM_PRINT_MARK; ESP_WM_PRINTLN(x); }
#define LOGINFO0(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { ESP_WM_PRINT(x); }
#define LOGINFO1(x,y)       if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(y); }
#define LOGINFO2(x,y,z)     if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(z); }
#define LOGINFO3(x,y,z,w)   if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINT(z); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(w); }

/////////////////////////////////////////////////////////

#define LOGDEBUG(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { ESP_WM_PRINT_MARK; ESP_WM_PRINTLN(x); }
#define LOGDEBUG0(x)        if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { ESP_WM_PRINT(x); }
#define LOGDEBUG1(x,y)      if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(y); }
#define LOGDEBUG2(x,y,z)    if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(z); }
#define LOGDEBUG3(x,y,z,w)  if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { ESP_WM_PRINT_MARK; ESP_WM_PRINT(x); ESP_WM_PRINT_SP; ESP_WM_PRINT(y); ESP_WM_PRINT_SP; ESP_WM_PRINT(z); ESP_WM_PRINT_SP; ESP_WM_PRINTLN(w); }

/////////////////////////////////////////////////////////

#endif    // ESPAsync_WiFiManager_Debug_H

