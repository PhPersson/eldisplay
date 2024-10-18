# Eldisplay


Eldisplay is a small display  powered by and ESP8266 that shows the current electricity prices in sweden. The software pulls the data from [elprisetjustnu.se](https://www.elprisetjustnu.se)


The hardware consists of an ESP8266 and an 2.8" ILI9341 display.

## Wiring of the ILI9341 display:

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

