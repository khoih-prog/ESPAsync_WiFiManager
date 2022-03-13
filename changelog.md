# ESPAsync_WiFiManager

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESPAsync_WiFiManager.svg?)](https://www.ardu-badge.com/ESPAsync_WiFiManager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESPAsync_WiFiManager.svg)](https://github.com/khoih-prog/ESPAsync_WiFiManager/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESPAsync_WiFiManager/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESPAsync_WiFiManager.svg)](http://github.com/khoih-prog/ESPAsync_WiFiManager/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.12.2](#releases-v1122)
  * [Releases v1.12.1](#releases-v1121)
  * [Releases v1.12.0](#releases-v1120)
  * [Releases v1.11.0](#releases-v1110)
  * [Releases v1.10.0](#releases-v1100)
  * [Releases v1.9.8](#releases-v198)
  * [Releases v1.9.7](#releases-v197)
  * [Releases v1.9.6](#releases-v196)
  * [Releases v1.9.5](#releases-v195)
  * [Releases v1.9.4](#releases-v194)
  * [Releases v1.9.3](#releases-v193)
  * [Releases v1.9.2](#releases-v192)
  * [Releases v1.9.1](#releases-v191)
  * [Releases v1.9.0](#releases-v190)
  * [Releases v1.8.1](#releases-v181)
  * [Major Releases v1.8.0](#major-releases-v180)
  * [Releases v1.7.1](#releases-v171)
  * [Releases v1.7.0](#releases-v170)
  * [Releases v1.6.3](#releases-v163)
  * [Releases v1.6.2](#releases-v162)
  * [Releases v1.6.1](#releases-v161)
  * [Releases v1.6.0](#releases-v160)
  * [Major Releases v1.5.0](#major-releases-v150)
  * [Releases v1.4.3](#releases-v143)
  * [Releases v1.4.2](#releases-v142)
  * [Releases v1.4.1](#releases-v141)
  * [Major Releases v1.4.0](#major-releases-v140)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.2](#releases-v112)
  * [Major Releases v1.1.1](#major-releases-v111)
  * [Releases v1.0.11](#releases-v1011)
 
---
---

## Changelog

### Releases v1.12.2

1. Optimize code by using passing by `reference` instead of by `value`
2. Delete all confusing, function-lacking `minimal` examples
3. Delete all `Modeless` examples
4. Display informational warnings only when `_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3`

### Releases v1.12.1

1. Add LittleFS support to `ESP32-C3`.
2. Use ESP32-core's LittleFS library instead of Lorol's LITTLEFS library for v2.0.0+

### Releases v1.12.0

1. Add support to `ESP32-S3` (`ESP32S3_DEV, ESP32_S3_BOX, UM TINYS3, UM PROS3, UM FEATHERS3`, etc.) using [ESP32 core, esp32-s3-support branch, v2.0.2+](https://github.com/espressif/arduino-esp32/tree/esp32-s3-support)

### Releases v1.11.0

1. Reduce the breaking effect of v1.10.0 by enabling compatibility with old code to include only `ESPAsync_WiFiManager.h`. Check [Important Breaking Change from v1.10.0](https://github.com/khoih-prog/ESPAsync_WiFiManager#Important-Breaking-Change-from-v1100)

### Releases v1.10.0

1. Fix `multiple-definitions` linker error and weird bug related to `src_cpp`. Check [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)
2. Optimize library code by using `reference-passing` instead of `value-passing`

### Releases v1.9.8

1. Fix bug returning IP `255.255.255.255` in core v2.0.0+ when using `hostname`

### Releases v1.9.7

1. Fix bug to permit using HTTP port different from 80. Check [WiFiManager works only on port 80 #75](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/75)

### Releases v1.9.6

1. Fix compile error for ESP32 core v1.0.5-

### Releases v1.9.5

1. Auto detect ESP32 core and use either built-in LittleFS or [LITTLEFS](https://github.com/lorol/LITTLEFS) library
2. Update `library.json` to use new `headers` for PIO


### Releases v1.9.4

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix

### Releases v1.9.3

1. Add WiFi scanning of hidden SSIDs. Check [Add support for Wifi hidden SSID scanning. #66](https://github.com/khoih-prog/ESP_WiFiManager/pull/66)

### Releases v1.9.2

1. Fix MultiWiFi connection issue with ESP32 core v2.0.0-rc1+
2. Fix AsyncWebServer library compile error with ESP32 core v2.0.0-rc1+. Check [Fix compiler error for ESP32-C3 and mbed TLS v2.7.0+ #970](https://github.com/me-no-dev/ESPAsyncWebServer/pull/970)
3. Verify compatibility with new ESP32 core v2.0.0-rc1+
4. Verify compatibility with new ESP8266 core v3.0.2

### Releases v1.9.1

1. Fix warnings and verify compatibility with new ESP8266 core v3.0.0 
2. Autodetect ESP8266 core v1.7.4- or new ESP8266 core v3.0.0 to use the new breaking features

### Releases v1.9.0

1. Add WiFi `/scan` page. 
2. Fix timezoneName not displayed in Info page. 
3. Clean up.

### Releases v1.8.1

1. Fix bug.
2. Don't display invalid time when not synch yet.

### Major Releases v1.8.0

1. Add auto-Timezone feature with variable `_timezoneName` (e.g. `America/New_York`) and function to retrieve TZ (e.g. `EST5EDT,M3.2.0,M11.1.0`) to use directly to configure ESP32/ESP8266 timezone. Check [How to retrieve timezone? #51](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/51)
2. Store those `_timezoneName` and `TZ` in LittleFS or SPIFFS config file.
3. Using these new timezone feature is optional.
4. Add checksum in config file to validate data read from LittleFS or SPIFFS config file.
5. Update examples to show how to use the new TZ feature.

### Releases v1.7.1

1. Fix captive-portal bug if Config Portal AP address is not default 192.168.4.1. Check [In AP, DNS server always redirects to 192.168.4.1 no mater what APStaticIP is set to. #58](https://github.com/khoih-prog/ESP_WiFiManager/issues/58)
2. Fix MultiWiFi bug.

### Releases v1.7.0

1. Add **LittleFS and SPIFFS** support to new **ESP32-S2** boards (**Arduino ESP32C3_DEV**). Check [HOWTO Install esp32 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) and ESP32-C3 boards into Arduino IDE](#howto-install-esp32-core-for-esp32-s2-saola-ai-thinker-esp-12k-and-esp32-c3-boards-into-arduino-ide).
2. Add **EEPROM and SPIFFS** support to new **ESP32-C3** boards (**Arduino ESP32C3_DEV**). Check [HOWTO Install esp32 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) and ESP32-C3 boards into Arduino IDE](#howto-install-esp32-core-for-esp32-s2-saola-ai-thinker-esp-12k-and-esp32-c3-boards-into-arduino-ide).

### Releases v1.6.3

1. Fix dnsServer not closed to free up DNS port 53. Check [**Allow captive portal to run more than once by closing dnsServer cleanly.** #49](https://github.com/khoih-prog/ESPAsync_WiFiManager/pull/49)
2. Add `dnsServer can't start` error message.

### Releases v1.6.2

1. Fix example misleading messages. Check [**Minor: examples/Async_ESP32_FSWebServer/ wrongly uses FileFS.begin(true)** #47](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/47)

### Releases v1.6.1

1. Modify multiWiFi-related timings to work better with latest esp32 core v1.0.6

### Releases v1.6.0

1. Fix WiFi Scanning bug.

### Major Releases v1.5.0

1. Add support to **ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, ESP32S2 Dev Module, UM FeatherS2, UM ProS2, microS2, etc.)**
2. Add [**Instructions to install ESP32-S2 core**](#howto-install-esp32-s2-core-for-esp32-s2-saola-ai-thinker-esp-12k-boards-into-arduino-ide)
3. Rewrite library code to be more efficient and multitask friendly

### Releases v1.4.3

1. Fix examples' bug not saving Static IP in certain cases.
2. Add feature to warn if using examples with old library versions

### Releases v1.4.2

1. Fix examples' bug not using saved WiFi Credentials after losing all WiFi connections.
2. Fix compiler warnings.

### Releases v1.4.1

1. Fix bug.
2. Fix compiler warnings.

### Major Releases v1.4.0

1. Fix staticIP not saved in examples. See [ESP32 static IP not saved after restarting the device](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/19)
2. Add structures and functions to handle AP and STA IPs.
3. Add complex examples 
  * [Async_ConfigOnDRD_FS_MQTT_Ptr_Complex](examples/Async_ConfigOnDRD_FS_MQTT_Ptr_Complex) to demo usage of std::map
  * [Async_ConfigOnDRD_FS_MQTT_Ptr_Medium](examples/Async_ConfigOnDRD_FS_MQTT_Ptr_Medium).
4. Add simple minimal examples 
  * [Async_ConfigOnDRD_ESP32_minimal](examples/Async_ConfigOnDRD_ESP32_minimal)
  * [Async_ConfigOnDRD_ESP8266_minimal](examples/Async_ConfigOnDRD_ESP8266_minimal)
  * [Async_AutoConnect_ESP32_minimal](examples/Async_AutoConnect_ESP32_minimal)
  * [Async_AutoConnect_ESP8266_minimal](examples/Async_AutoConnect_ESP8266_minimal)
5. Modify Version String
6. Add Table of Contents

### Releases v1.3.0

1. Add LittleFS support to ESP32-related examples to use [**LittleFS_esp32 Library**](https://github.com/lorol/LITTLEFS)
2. Add Version String

### Releases v1.2.0

1. Restore cpp code besides Impl.h code to use in case of `multiple definition` linker error. See [`Change Implementation to seperate *.h and *.cpp file instead of *.h and *-Impl.h`](https://github.com/khoih-prog/ESP_WiFiManager/issues/38) and [`Support building in PlatformIO PR`](https://github.com/khoih-prog/ESP_WiFiManager/pull/20). Also have a look at [**HOWTO Fix Multiple Definitions Linker Error**](https://github.com/khoih-prog/ESPAsync_WiFiManager#HOWTO-Fix-Multiple-Definitions-Linker-Error)
2. Fix bug [/close does not close the config portal](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/16).

### Releases v1.1.2

1. Fix bug in examples.

### Major Releases v1.1.1

1. Add **MultiWiFi feature to auto(Re)connect to the best WiFi at runtime**
2. Fix bug, typo and minor improvement.
3. Completely enhanced examples to use new MultiWiFi feature.
4. Add setCORSHeader function to allow **configurable CORS Header**. See [Using CORS feature](https://github.com/khoih-prog/ESPAsync_WiFiManager#15-using-cors-cross-origin-resource-sharing-feature)
5. Bump up to v1.1.1 to sync with [ESP_WiFiManager v1.1.1](https://github.com/khoih-prog/ESP_WiFiManager/releases/tag/v1.1.1).

### Releases 1.0.11

1. Initial coding to use ESPAsyncWebServer instead of (ESP8266)WebServer.
2. Add more features and error checking to many examples.
3. Add example [Async_ConfigOnDRD_FS_MQTT_Ptr](examples/Async_ConfigOnDRD_FS_MQTT_Ptr)
4. Bump up to v1.0.11 to sync with ESP_WiFiManager v1.0.11.


