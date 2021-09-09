## ESPAsync_WiFiManager_Lite (Light Weight Credentials / WiFiManager for ESP32/ESP8266)

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESPAsync_WiFiManager_Lite.svg?)](https://www.ardu-badge.com/ESPAsync_WiFiManager_Lite)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESPAsync_WiFiManager_Lite.svg)](https://github.com/khoih-prog/ESPAsync_WiFiManager_Lite/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESPAsync_WiFiManager_Lite/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESPAsync_WiFiManager_Lite.svg)](http://github.com/khoih-prog/ESPAsync_WiFiManager_Lite/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Major Release v1.5.0](#major-release-v150)
  * [Release v1.4.0](#release-v140)
  * [Release v1.3.0](#release-v130)
  * [Release v1.2.0](#release-v120)
  * [Release v1.1.0](#release-v110)
  * [Release v1.0.0](#release-v100)

---
---


## Changelog

### Major Release v1.5.0

1. Enable scan of WiFi networks for selection in Configuration Portal. Check [PR for v1.3.0 - Enable scan of WiFi networks #10](https://github.com/khoih-prog/WiFiManager_NINA_Lite/pull/10). Now you can select optional **SCAN_WIFI_NETWORKS**, **MANUAL_SSID_INPUT_ALLOWED** to be able to manually input SSID, not only from a scanned SSID lists and **MAX_SSID_IN_LIST** (from 2-15)
2. Minor enhancement to not display garbage when data is invalid

### Release v1.4.0

1. Add **LittleFS and SPIFFS** support to new **ESP32-S2** boards (**Arduino ESP32C3_DEV**). Check [HOWTO Install esp32 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) and ESP32-C3 boards into Arduino IDE](#howto-install-esp32-core-for-esp32-s2-saola-ai-thinker-esp-12k-and-esp32-c3-boards-into-arduino-ide).
2. Add **EEPROM and SPIFFS** support to new **ESP32-C3** boards (**Arduino ESP32C3_DEV**). Check [HOWTO Install esp32 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) and ESP32-C3 boards into Arduino IDE](#howto-install-esp32-core-for-esp32-s2-saola-ai-thinker-esp-12k-and-esp32-c3-boards-into-arduino-ide).

### Release v1.3.0

1. Fix invalid "blank" Config Data treated as Valid.
2. Permit optionally inputting one set of WiFi SSID/PWD by using `REQUIRE_ONE_SET_SSID_PW == true`
3. Enforce WiFi PWD minimum length of 8 chars
4. Fix bug where EEPROM_SIZE truncated by DRD/MRD to 512, resulting lost and corrupted data.

### Release v1.2.0

1. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header.
2. Fix Config Portal Bug. 
3. Update examples

### Release v1.1.0

1. Add support to **ESP32-S2 (ESP32-S2 Saola and AI-Thinker ESP-12K)**
2. Add [**Instructions to install ESP32-S2 core**](#howto-install-esp32-s2-core-for-esp32-s2-saola-ai-thinker-esp-12k-boards-into-arduino-ide)

### Release v1.0.0

1. Initial release to support ESP32 and ESP8266 to use the better **asynchronous** [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer).



