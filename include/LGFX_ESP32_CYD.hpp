#pragma once
#include <LovyanGFX.hpp>

class LGFX_ESP32_CYD : public lgfx::LGFX_Device {
    lgfx::Panel_ILI9341 _panel_instance;
    lgfx::Bus_SPI       _bus_instance;
    lgfx::Light_PWM     _light_instance;

public:

    LGFX_ESP32_CYD(void)
    {
        {
            auto cfg = _bus_instance.config();

            cfg.spi_host   = VSPI_HOST;
            cfg.spi_mode   = 0;

            cfg.freq_write = 40000000;
            cfg.freq_read  = 16000000;

            cfg.spi_3wire  = false;
            cfg.use_lock   = true;
            cfg.dma_channel = SPI_DMA_CH_AUTO;

            cfg.pin_sclk = 14;
            cfg.pin_mosi = 13;
            cfg.pin_miso = 12;
            cfg.pin_dc   = 2;

            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();

            cfg.pin_cs  = 15;
            cfg.pin_rst = -1;
            cfg.pin_busy = -1;

            cfg.panel_width  = 320;
            cfg.panel_height = 240;

            cfg.memory_width  = 320;
            cfg.memory_height = 240;

            cfg.offset_x = 0;
            cfg.offset_y = 0;
            cfg.offset_rotation = 0;

            cfg.dummy_read_pixel = 8;
            cfg.dummy_read_bits  = 1;

            cfg.readable = true;
            cfg.rgb_order = true;
            cfg.invert = true;
            cfg.dlen_16bit = false;
            cfg.bus_shared = false;
            _panel_instance.config(cfg);
        }
        {
            auto cfg = _light_instance.config();

            cfg.pin_bl = 21;
            cfg.invert = true;

            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance);
        }

        setPanel(&_panel_instance);
    }
};