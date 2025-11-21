| Supported Targets | ESP32-P4 |
| ----------------- | -------- |

# MIPI DSI LCD Panel Example

> [Firebeetle 2 Board ESP32-P4 Microcontroller Wiki - DFRobot](https://wiki.dfrobot.com/SKU_DFR1172_FireBeetle_2_Board_ESP32_P4): 16MB QIO FLASH
> 
> Wi-Fi (ESP32-C6) + NTP + RTC [系统时间 - ESP32](https://docs.espressif.com/projects/esp-idf/zh_CN/v5.5.1/esp32/api-reference/system/system_time.html#sntp)
> 
> LVGL + MIPI-DSI ST7701(S) ([ESP Component Registry](https://components.espressif.com/components/espressif/esp_lcd_st7701/versions/1.1.5/readme))

[esp_lcd](https://docs.espressif.com/projects/esp-idf/en/latest/esp32p4/api-reference/peripherals/lcd/dsi_lcd.html) supports MIPI DSI interfaced LCD panel, with frame buffer(s) managed by the driver itself.

This example shows the general process of installing a MIPI DSI LCD driver, and displays a LVGL widget on the screen.

