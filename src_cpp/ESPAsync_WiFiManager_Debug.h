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
  Version: 1.4.3

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
 *****************************************************************************************************************************/

#pragma once

#ifdef ESPASYNC_WIFIMGR_DEBUG_PORT
  #define DBG_PORT      ESPASYNC_WIFIMGR_DEBUG_PORT
#else
  #define DBG_PORT      Serial
#endif

// Change _ESPASYNC_WIFIMGR_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _ESPASYNC_WIFIMGR_LOGLEVEL_
  #define _ESPASYNC_WIFIMGR_LOGLEVEL_       0
#endif

#define LOGERROR(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { DBG_PORT.print("[WM] "); DBG_PORT.println(x); }
#define LOGERROR0(x)        if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { DBG_PORT.print(x); }
#define LOGERROR1(x,y)      if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.println(y); }
#define LOGERROR2(x,y,z)    if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.println(z); }
#define LOGERROR3(x,y,z,w)  if(_ESPASYNC_WIFIMGR_LOGLEVEL_>0) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.print(z); DBG_PORT.print(" "); DBG_PORT.println(w); }

#define LOGWARN(x)          if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { DBG_PORT.print("[WM] "); DBG_PORT.println(x); }
#define LOGWARN0(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { DBG_PORT.print(x); }
#define LOGWARN1(x,y)       if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.println(y); }
#define LOGWARN2(x,y,z)     if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.println(z); }
#define LOGWARN3(x,y,z,w)   if(_ESPASYNC_WIFIMGR_LOGLEVEL_>1) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.print(z); DBG_PORT.print(" "); DBG_PORT.println(w); }

#define LOGINFO(x)          if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { DBG_PORT.print("[WM] "); DBG_PORT.println(x); }
#define LOGINFO0(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { DBG_PORT.print(x); }
#define LOGINFO1(x,y)       if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.println(y); }
#define LOGINFO2(x,y,z)     if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.println(z); }
#define LOGINFO3(x,y,z,w)   if(_ESPASYNC_WIFIMGR_LOGLEVEL_>2) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.print(z); DBG_PORT.print(" "); DBG_PORT.println(w); }

#define LOGDEBUG(x)         if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { DBG_PORT.print("[WM] "); DBG_PORT.println(x); }
#define LOGDEBUG0(x)        if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { DBG_PORT.print(x); }
#define LOGDEBUG1(x,y)      if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.println(y); }
#define LOGDEBUG2(x,y,z)    if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.println(z); }
#define LOGDEBUG3(x,y,z,w)  if(_ESPASYNC_WIFIMGR_LOGLEVEL_>3) { DBG_PORT.print("[WM] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.print(z); DBG_PORT.print(" "); DBG_PORT.println(w); }

