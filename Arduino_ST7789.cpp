/*
 * start rewrite from:
 * https://github.com/adafruit/Adafruit-GFX-Library.git
 * https://github.com/ananevilya/Arduino-ST7789-Library.git
 */
#include "Arduino_ST7789.h"

Arduino_ST7789::Arduino_ST7789(Arduino_DataBus *bus, int8_t rst, uint8_t r,
                               int16_t w, int16_t h, uint8_t col_offset, uint8_t row_offset, bool ips)
    : Arduino_TFT(bus, rst, r, w, h, col_offset, row_offset)
{
  _ips = ips;
}

// Companion code to the above tables.  Reads and issues
// a series of LCD commands stored in PROGMEM byte array.
void Arduino_ST7789::tftInit()
{
  //  if (_rst < 0)
  //  {
  _bus->writeCommand(ST7789_SWRESET); // 1: Software reset
  delay(ST7789_RST_DELAY);
  //  }

  _bus->writeCommand(ST7789_SLPOUT); // 2: Out of sleep mode, no args, w/delay
  delay(ST7789_SLPOUT_DELAY);
  _bus->writeCommand(ST7789_COLMOD); // 3: Set color mode, 1 arg + delay:
  _bus->writeData(0x55);             // 16-bit color
  if (_ips)
  {
    _bus->writeCommand(ST7789_INVON);
  }
  _bus->writeCommand(ST7789_NORON); // 4: Normal display on, no args, w/delay
  delay(10);
  _bus->writeCommand(ST7789_DISPON); // 5: Main screen turn on, no args, w/delay
  delay(500);
}

void Arduino_ST7789::writeAddrColumn(uint16_t x, uint16_t w)
{
#ifdef ESP32
  uint32_t x_range = ((uint32_t)(x + _xStart) << 16) | (x + w - 1 + _xStart);

  _bus->writeCommandCore(ST7789_CASET); // Column addr set
  _bus->write32(x_range);
#else
  uint16_t x_start = x + _xStart, x_end = x + w - 1 + _xStart;

  _bus->writeCommandCore(ST7789_CASET); // Column addr set
  _bus->write(x_start >> 8);
  _bus->write(x_start & 0xFF); // XSTART
  _bus->write(x_end >> 8);
  _bus->write(x_end & 0xFF); // XEND
#endif
}

void Arduino_ST7789::writeAddrRow(uint16_t y, uint16_t h)
{
#ifdef ESP32
  uint32_t y_range = ((uint32_t)(y + _yStart) << 16) | (y + h - 1 + _yStart);

  _bus->writeCommandCore(ST7789_RASET); // Row addr set
  _bus->write32(y_range);
#else
  uint16_t y_start = y + _yStart, y_end = y + h - 1 + _yStart;

  _bus->writeCommandCore(ST7789_RASET); // Row addr set
  _bus->write(y_start >> 8);
  _bus->write(y_start & 0xFF); // YSTART
  _bus->write(y_end >> 8);
  _bus->write(y_end & 0xFF); // YEND
#endif
}

void Arduino_ST7789::writeAddrMemWrite()
{
  _bus->writeCommandCore(ST7789_RAMWR); // write to RAM
}

/**************************************************************************/
/*!
    @brief   Set origin of (0,0) and orientation of TFT display
    @param   m  The index for rotation, from 0-3 inclusive
*/
/**************************************************************************/
void Arduino_ST7789::setRotation(uint8_t m)
{
  rotation = m % 4; // can't be higher than 3
  switch (rotation)
  {
  case 0:
    m = ST7789_MADCTL_MX | ST7789_MADCTL_MY | ST7789_MADCTL_RGB;

    _width = WIDTH;
    _height = HEIGHT;
    _max_x = _width - 1;  ///< x zero base bound
    _max_y = _height - 1; ///< y zero base bound
    _xStart = COL_OFFSET;
    _yStart = ROW_OFFSET;
    break;
  case 1:
    m = ST7789_MADCTL_MY | ST7789_MADCTL_MV | ST7789_MADCTL_RGB;

    _width = HEIGHT;
    _height = WIDTH;
    _max_x = _width - 1;  ///< x zero base bound
    _max_y = _height - 1; ///< y zero base bound
    _xStart = ROW_OFFSET;
    _yStart = COL_OFFSET;
    break;
  case 2:
    m = ST7789_MADCTL_RGB;

    _width = WIDTH;
    _height = HEIGHT;
    _max_x = _width - 1;  ///< x zero base bound
    _max_y = _height - 1; ///< y zero base bound
    _xStart = ST7789_TFTWIDTH - WIDTH - COL_OFFSET;
    _yStart = ST7789_TFTHEIGHT - HEIGHT - ROW_OFFSET;
    break;

  case 3:
    m = ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_RGB;

    _width = HEIGHT;
    _height = WIDTH;
    _max_x = _width - 1;  ///< x zero base bound
    _max_y = _height - 1; ///< y zero base bound
    _xStart = ST7789_TFTHEIGHT - HEIGHT - ROW_OFFSET;
    _yStart = ST7789_TFTWIDTH - WIDTH - COL_OFFSET;
    break;
  }

  _bus->beginWrite();
  _bus->writeCommandCore(ST7789_MADCTL);
  _bus->write(m);
  _bus->endWrite();
}

void Arduino_ST7789::invertDisplay(bool i)
{
  _bus->writeCommand(_ips ? (i ? ST7789_INVOFF : ST7789_INVON) : (i ? ST7789_INVON : ST7789_INVOFF));
}

void Arduino_ST7789::displayOn(void)
{
  _bus->writeCommand(ST7789_SLPOUT);
  delay(ST7789_SLPOUT_DELAY);
}

void Arduino_ST7789::displayOff(void)
{
  _bus->writeCommand(ST7789_SLPIN);
  delay(ST7789_SLPIN_DELAY);
}
