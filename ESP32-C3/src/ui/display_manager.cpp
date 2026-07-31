#include "display_manager.h"
#include <LovyanGFX.hpp>

extern float threshold;

class Display : public lgfx::LGFX_Device {
  lgfx::Panel_GC9A01 panel;
  lgfx::Bus_SPI bus;

public:
  Display() {
    auto bus_cfg = bus.config();
    bus_cfg.spi_host = SPI2_HOST;
    bus_cfg.spi_mode = 0;
    bus_cfg.freq_write = 10000000;
    bus_cfg.freq_read = 8000000;
    bus_cfg.spi_3wire = false;
    bus_cfg.use_lock = true;
    bus_cfg.dma_channel = SPI_DMA_CH_AUTO;
    bus_cfg.pin_sclk = 4;
    bus_cfg.pin_mosi = 3;
    bus_cfg.pin_miso = -1;
    bus_cfg.pin_dc = 10;
    bus.config(bus_cfg);
    panel.setBus(&bus);

    auto panel_cfg = panel.config();
    panel_cfg.pin_cs = 1;
    panel_cfg.pin_rst = 0;
    panel_cfg.pin_busy = -1;
    panel_cfg.panel_width = 240;
    panel_cfg.panel_height = 240;
    panel_cfg.memory_width = 240;
    panel_cfg.memory_height = 240;
    panel_cfg.offset_x = 0;
    panel_cfg.offset_y = 0;
    panel_cfg.offset_rotation = 0;
    panel_cfg.dummy_read_pixel = 8;
    panel_cfg.dummy_read_bits = 1;
    panel_cfg.readable = false;
    panel_cfg.invert = true;
    panel_cfg.rgb_order = false;
    panel_cfg.dlen_16bit = false;
    panel_cfg.bus_shared = false;
    panel.config(panel_cfg);

    setPanel(&panel);
  }
};

static Display lcd;

void setupDisplay() {
  lcd.init();
  lcd.setRotation(0);
  lcd.setBrightness(180);
}

uint16_t priceColor(float price) {
  return price > threshold ? TFT_RED : TFT_GREEN;
}

void drawCenteredPrice(float price) {
  lcd.fillScreen(TFT_BLACK);
  lcd.setFont(&fonts::Font8);
  lcd.setTextColor(priceColor(price), TFT_BLACK);

  String text = String(price, 2);
  int w = lcd.textWidth(text);
  int x = (lcd.width() - w) / 2;
  int y = 95;

  lcd.setCursor(x, y);
  lcd.print(text);
}

void drawCenteredMessage(const String& text) {
  lcd.fillScreen(TFT_BLACK);
  lcd.setFont(&fonts::Font4);
  lcd.setTextColor(TFT_WHITE, TFT_BLACK);

  int w = lcd.textWidth(text);
  int x = (lcd.width() - w) / 2;
  int y = 110;

  lcd.setCursor(x, y);
  lcd.print(text);
}

void drawConnectedMessage(const String& text) {
  lcd.fillScreen(TFT_BLACK);
  lcd.setFont(&fonts::Font4);
  lcd.setTextColor(TFT_GREEN, TFT_BLACK);

  int w = lcd.textWidth(text);
  int x = (lcd.width() - w) / 2;
  int y = 110;

  lcd.setCursor(x, y);
  lcd.print(text);
}