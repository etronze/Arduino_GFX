#ifndef _ARDUINO_GC9106_H_
#define _ARDUINO_GC9106_H_

#include <Arduino.h>
#include <Print.h>
#include "./Arduino_GFX.h"
#include "../Arduino_TFT.h"

#define GC9106_TFTWIDTH 80
#define GC9106_TFTHEIGHT 160

#define GC9106_RST_DELAY 120    ///< delay ms wait for reset finish
#define GC9106_SLPIN_DELAY 120  ///< delay ms wait for sleep in finish
#define GC9106_SLPOUT_DELAY 120 ///< delay ms wait for sleep out finish

#define GC9106_NOP 0x00
#define GC9106_SWRESET 0x01
#define GC9106_RDDID 0x04
#define GC9106_RDDST 0x09

#define GC9106_SLPIN 0x10
#define GC9106_SLPOUT 0x11
#define GC9106_PTLON 0x12
#define GC9106_NORON 0x13

#define GC9106_INVOFF 0x20
#define GC9106_INVON 0x21
#define GC9106_DISPOFF 0x28
#define GC9106_DISPON 0x29

#define GC9106_CASET 0x2A
#define GC9106_RASET 0x2B
#define GC9106_RAMWR 0x2C
#define GC9106_RAMRD 0x2E

#define GC9106_PTLAR 0x30
#define GC9106_TELON 0x35
#define GC9106_MADCTL 0x36
#define GC9106_COLMOD 0x3A
#define GC9106_SCANLSET 0x44

#define GC9106_FRMCTR1 0xB1
#define GC9106_FRMCTR2 0xB2
#define GC9106_FRMCTR3 0xB3

#define GC9106_INVCTR 0xB4
#define GC9106_VREG1CTL 0xE6
#define GC9106_VREG2CTL 0xE7
#define GC9106_GAMMA1 0xF0
#define GC9106_GAMMA2 0xF1
#define GC9106_INTERRE1 0xFE
#define GC9106_INTERRE2 0xEF

#define GC9106_MADCTL_MY 0x80
#define GC9106_MADCTL_MX 0x40
#define GC9106_MADCTL_MV 0x20
#define GC9106_MADCTL_ML 0x10
#define GC9106_MADCTL_BGR 0x08
#define GC9106_MADCTL_MH 0x04
#define GC9106_MADCTL_RGB 0x00


class Arduino_GC9106 : public Arduino_TFT
{
public:
  Arduino_GC9106(
      Arduino_DataBus *bus, int8_t rst = -1, uint8_t r = 0,
      bool ips = false, int16_t w = GC9106_TFTWIDTH, int16_t h = GC9106_TFTHEIGHT,
      uint8_t col_offset1 = 24, uint8_t row_offset1 = 0, uint8_t col_offset2 = 24, uint8_t row_offset2 = 0);

  void begin(int32_t speed = 0) override;
  void writeAddrWindow(int16_t x, int16_t y, uint16_t w, uint16_t h) override;
  void setRotation(uint8_t r) override;
  void invertDisplay(bool) override;
  void displayOn() override;
  void displayOff() override;

protected:
  void tftInit() override;

private:
};

#endif
