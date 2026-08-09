#pragma once

#include <LovyanGFX.hpp>

class LGFX_ESP32_S3_LCD_2 : public lgfx::LGFX_Device {
  lgfx::Panel_ST7789 panel;
  lgfx::Bus_SPI bus;
  lgfx::Light_PWM light;
  lgfx::Touch_CST816S touch;

public:
  LGFX_ESP32_S3_LCD_2 () {
    auto bus_cfg = bus.config();
    bus_cfg.spi_host = SPI2_HOST;
    bus_cfg.spi_mode = 0;
    bus_cfg.freq_write = 40000000;
    bus_cfg.freq_read = 16000000;
    bus_cfg.spi_3wire = false;
    bus_cfg.use_lock = true;
    bus_cfg.dma_channel = SPI_DMA_CH_AUTO;
    bus_cfg.pin_sclk = 39;
    bus_cfg.pin_mosi = 38;
    bus_cfg.pin_miso = 40;
    bus_cfg.pin_dc = 42;
    bus.config(bus_cfg);
    panel.setBus(&bus);

    auto panel_cfg = panel.config();
    panel_cfg.pin_cs = 45;
    panel_cfg.pin_rst = -1;
    panel_cfg.pin_busy = -1;
    panel_cfg.panel_width = 240;
    panel_cfg.panel_height = 320;
    panel_cfg.memory_width = 240;
    panel_cfg.memory_height = 320;
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

    auto light_cfg = light.config();
    light_cfg.pin_bl = 1;
    light_cfg.invert = false;
    light_cfg.freq = 44100;
    light_cfg.pwm_channel = 7;
    light.config(light_cfg);
    panel.setLight(&light);        // attach light to panel

    auto touch_cfg = touch.config();
    touch_cfg.pin_sda = 8;
    touch_cfg.pin_scl = 9;
    touch_cfg.pin_int = 4;
    touch_cfg.i2c_port = 1;
    touch_cfg.i2c_addr = 0x15;
    touch_cfg.freq = 400000;
    touch_cfg.x_min = 0;
    touch_cfg.x_max = 239;
    touch_cfg.y_min = 0;
    touch_cfg.y_max = 319;
    touch_cfg.bus_shared = false;
    touch.config(touch_cfg);
    panel.setTouch(&touch);        // attach touch to panel

    setPanel(&panel); 
  }
};