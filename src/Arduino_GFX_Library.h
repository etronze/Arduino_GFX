#ifndef _ARDUINO_GFX_LIBRARIES_H_
#define _ARDUINO_GFX_LIBRARIES_H_

#include "Arduino_DataBus.h"
#include "databus/Arduino_SWSPI.h"
#include "databus/Arduino_HWSPI.h"
#include "databus/Arduino_ESP32SPI.h"
#include "databus/Arduino_ESP32SPI_DMA.h"
#include "databus/Arduino_ESP32PAR8.h"
#include "databus/Arduino_ESP32PAR16.h"
#include "databus/Arduino_ESP8266SPI.h"
#include "databus/Arduino_mbedSPI.h"
#include "databus/Arduino_NRFXSPI.h"

#include "Arduino_GFX.h"                     // Core graphics library
#include "canvas/Arduino_Canvas.h"           // Canvas (framebuffer) library
#include "canvas/Arduino_Canvas_Indexed.h"   // Indexed Color Canvas (framebuffer) library
#include "canvas/Arduino_Canvas_3bit.h"      // 3-bit Color Canvas (framebuffer) library
#include "canvas/Arduino_Canvas_Mono.h"      // Mono Color Canvas (framebuffer) library
#include "display/Arduino_GC9A01.h"          // Hardware-specific library for GC9A01
#include "display/Arduino_HX8347C.h"         // Hardware-specific library for HX8347C
#include "display/Arduino_HX8347D.h"         // Hardware-specific library for HX8347D
#include "display/Arduino_HX8352C.h"         // Hardware-specific library for HX8352C
#include "display/Arduino_HX8357B.h"         // Hardware-specific library for HX8357B
#include "display/Arduino_ILI9225.h"         // Hardware-specific library for ILI9225
#include "display/Arduino_ILI9341.h"         // Hardware-specific library for ILI9341
#include "display/Arduino_ILI9341_M5STACK.h" // Hardware-specific library for M5STACK
#include "display/Arduino_ILI9481_18bit.h"   // Hardware-specific library for ILI9481
#include "display/Arduino_ILI9486_18bit.h"   // Hardware-specific library for ILI9486
#include "display/Arduino_ILI9488_18bit.h"   // Hardware-specific library for ILI9488
#include "display/Arduino_JBT6K71.h"         // Hardware-specific library for JBT6K71
#include "display/Arduino_R61529.h"          // Hardware-specific library for R61529
#include "display/Arduino_SEPS525.h"         // Hardware-specific library for SEPS525
#include "display/Arduino_SSD1283A.h"        // Hardware-specific library for SSD1283A
#include "display/Arduino_SSD1331.h"         // Hardware-specific library for SSD1331
#include "display/Arduino_SSD1351.h"         // Hardware-specific library for SSD1351
#include "display/Arduino_ST7735.h"          // Hardware-specific library for ST7735
#include "display/Arduino_ST7789.h"          // Hardware-specific library for ST7789
#include "display/Arduino_ST7796.h"          // Hardware-specific library for ST7796

#if defined(ESP32_LCDKIT_SPI)
#define DISPLAY_DEV_KIT
#define TFT_SCK 22
#define TFT_MOSI 21
#define TFT_MISO 27
#define TFT_CS 5
#define TFT_DC 19
#define TFT_RST 18
#define TFT_BL 23
#elif defined(TTGO_T_DISPLAY)
#define DISPLAY_DEV_KIT
#define TFT_SCK 18
#define TFT_MOSI 19
#define TFT_MISO -1
#define TFT_CS 5
#define TFT_DC 16
#define TFT_RST 23
#define TFT_BL 4
#elif defined(WT32_SC01)
#define DISPLAY_DEV_KIT
#define TFT_SCK 14
#define TFT_MOSI 13
#define TFT_MISO -1
#define TFT_CS 15
#define TFT_DC 21
#define TFT_RST 22
#define TFT_BL 23
#elif defined(ARDUINO_ARCH_SAMD) && defined(SEEED_GROVE_UI_WIRELESS)
#define DISPLAY_DEV_KIT
#define WIO_TERMINAL
#define TFT_CS LCD_SS_PIN
#define TFT_DC LCD_DC
#define TFT_RST -1
#define TFT_BL LCD_BACKLIGHT
#elif defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
#define DISPLAY_DEV_KIT
#define M5STACK_CORE
#define TFT_SCK 18
#define TFT_MOSI 23
#define TFT_MISO 19
#define TFT_CS 14
#define TFT_DC 27
#define TFT_RST 33
#define TFT_BL 32
#elif defined(ARDUINO_ODROID_ESP32)
#define DISPLAY_DEV_KIT
#define ODROID_GO
#define TFT_SCK 18
#define TFT_MOSI 23
#define TFT_MISO 19
#define TFT_CS 5
#define TFT_DC 21
#define TFT_RST -1
#define TFT_BL 14
/* TTGO T-Watch */
#elif defined(ARDUINO_T) || defined(ARDUINO_TWATCH_BASE) || defined(ARDUINO_TWATCH_2020_V1) || defined(ARDUINO_TWATCH_2020_V2)
#define DISPLAY_DEV_KIT
#define TTGO_T_WATCH
#define TFT_SCK 18
#define TFT_MOSI 19
#define TFT_MISO -1
#define TFT_CS 5
#define TFT_DC 27
#define TFT_RST -1
#define TFT_BL 12
#elif defined(ARDUINO_ARCH_NRF52840)
#define TFT_SCK 13
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_CS 9
#define TFT_DC 8
#define TFT_RST 7
#define TFT_BL 6
#elif defined(ESP32)
#define TFT_SCK 18
#define TFT_MOSI 23
#define TFT_MISO -1
#define TFT_CS 5
#define TFT_DC 27
#define TFT_RST 33
#define TFT_BL 22
#elif defined(ESP8266)
#define TFT_CS 15
#define TFT_DC 5
#define TFT_RST 16
#define TFT_BL 4
#else // default pins for Arduino Nano, Mini, Micro and more
#define TFT_CS 9
#define TFT_DC 8
#define TFT_RST 7
#define TFT_BL 6
#endif

Arduino_DataBus *create_default_Arduino_DataBus()
{
#if defined(ARDUINO_ARCH_NRF52840)
    return new Arduino_NRFXSPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
#elif defined(ESP32)
    return new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
#elif defined(ESP8266)
    return new Arduino_ESP8266SPI(TFT_DC, TFT_CS);
#else
    return new Arduino_HWSPI(TFT_DC, TFT_CS);
#endif
}

Arduino_GFX *create_default_Arduino_GFX()
{
    Arduino_DataBus *bus = create_default_Arduino_DataBus();
#if defined(ESP32_LCDKIT_SPI)
    return new Arduino_ILI9341(bus, TFT_RST, 1 /* rotation */);
#elif defined(TTGO_T_DISPLAY)
    return new Arduino_ST7789(bus, TFT_RST, 2 /* rotation */, true /* IPS */, 135 /* width */, 240 /* height */, 53 /* col offset 1 */, 40 /* row offset 1 */, 52 /* col offset 2 */, 40 /* row offset 2 */);
#elif defined(WT32_SC01)
    return new Arduino_ST7796(bus, TFT_RST, 3 /* rotation */);
#elif defined(WIO_TERMINAL)
    return new Arduino_ILI9341(bus, TFT_RST, 3 /* rotation */);
#elif defined(M5STACK_CORE)
    return new Arduino_ILI9341_M5STACK(bus, TFT_RST, 1 /* rotation */);
#elif defined(ODROID_GO)
    return new Arduino_ILI9341(bus, TFT_RST, 3 /* rotation */);
#elif defined(TTGO_T_WATCH)
    return new Arduino_ST7789(bus, TFT_RST, 2 /* rotation */, true /* IPS */, 240, 240, 0, 80);
#else
    return new Arduino_ILI9341(bus, TFT_RST, 0 /* rotation */);
#endif
}

#endif // _ARDUINO_GFX_LIBRARIES_H_
