<h1 align="center">
  <br>
  <a href="http://www.amitmerchant.com/electron-markdownify"><img src="https://github.com/PhPersson/eldisplay/blob/main/images/logo.png" alt="logo height="300" width="300"></a>
</h1>

<h4 align="center">Eldisplay is a small display powered by and ESP8266 that shows the current electricity prices in sweden.</a>.</h4>
<p align="center">
   •
  <a href="#what-is-eldisplay">•What's Eldisplay?</a> •
  <a href="#how-to-setup">How To Setup</a> •
  <a href="#hardware">Hardware</a>
</p>

## What is eldisplay?
Eldisplay is an project designed to provide real-time electricity pricing information. The system connects to WiFi and offers a user-friendly web interface that allows users to select their specific price region, ensuring they receive accurate electricity prices.

The primary goal of Eldisplay is to simplify the process of monitoring electricity rates, eliminating the need for users to open a mobile application just to check prices before running appliances like washing machines or dishwashers. By providing instant access to the current electricity pricing for the hour and the next two hours, Eldisplay empowers users to make informed decisions about their energy consumption, ultimately helping them save on utility costs.

Key features of Eldisplay include:

* Real-Time Pricing: Displays live electricity prices for the current hour and the following two hours.
* Region Selection: Allows users to configure settings based on their geographical area, ensuring accurate pricing information.
* Web Interface: A straightforward interface for easy configuration.

With Eldisplay, users can optimize their energy usage, making it an essential tool for anyone looking to manage their electricity consumption efficiently.

<a href=""><img  src="https://github.com/PhPersson/eldisplay/raw/main/images/eldisplay.jpeg" alt="" height="40%" width="40%"></a>

## How To Setup

1. **Download the Binary:**
   - Go to the [release page](https://github.com/PhPersson/eldisplay/releases) and download the latest `.bin` file for Eldisplay.

2. **Install the Binary:**
   - Use [ESPHome Web](https://web.esphome.io/) to upload the `.bin` file to your ESP8266.
   - Follow the tool's instructions to select the correct COM port and upload the firmware.

3. **Access the Web Interface:**
   - Once the upload is complete connect to eldisplays AP
   - Once connected to WiFi, go to __eldisplay.local__ to configure the device.

<img src="https://github.com/PhPersson/eldisplay/blob/main/images/setup_error.jpeg" width=40% height=40% >

## Hardware
<a href=""><img src="https://github.com/PhPersson/eldisplay/raw/main/images/eldisplay_below.jpeg" alt="" height="40%" width="40%"></a>

1. **Hardware Requirements:**
   - ESP8266 microcontroller.
   - ILI9341 display module.
   - Power supply for the ESP8266 and display.
   - Jumper wires for connections.

```
ILI9341   -> ESP8266
VCC       -> 3.3V
GND       -> GND
CS        -> D2
RESET     -> D3
D/C       -> D4
SDI(MOSI) -> D7
SCK       -> D5
LED       -> 3.3V
```
