#pragma once
#include <LovyanGFX.hpp>


class LGFX_ESP32_GC9A01 : public lgfx::LGFX_Device {
  lgfx::Panel_GC9A01 panel;
  lgfx::Bus_SPI bus;

public:
  LGFX_ESP32_GC9A01() {
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