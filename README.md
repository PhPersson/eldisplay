# Eldisplay


Eldisplay is a small display  powered by and ESP8266 that shows the current electricity prices in sweden. The software pulls the data from [elprisetjustnu.se](https://www.elprisetjustnu.se)


The hardware consists of an ESP8266 and an 2.8" ILI9341 display.

| ![Image 1](https://github.com/PhPersson/eldisplay/raw/main/images/eldisplay.jpeg) | ![Image 2](https://github.com/PhPersson/eldisplay/raw/main/images/eldisplay_below.jpeg) |
|---|---|

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


## Configuration Steps

1. **Locate the Configuration File**  
   Find the `user_config.template.h` file in your project directory. __Rename it to__ `user_config.h`.

2. **Set the API URL**  
   You need to specify the API URL to fetch the price data. Locate the following line in the file:

```cpp
// char api_url[45] = "";  // API-url to fetch the price
```
3. **Set your price area**  
   You need to specify wich electricity price area you are located in. Currently it only supports swedish areas, SE1, SE2, SE3 or SE4:
```cpp
// char electricityPriceArea[4] = ""; // Any of SE1, SE2, SE3 or SE4
```

4. **Set high electricyty price**  
   Set a defualt value when u want the price to be consider high.
```cpp
// float priceThreshold = 0.30; // The threshold when price should be considered high
```
5. **Add tax**  
   Set as true if u want to include tax in the displayed price (25%)
```cpp
// bool shouldAddTax = true; // false if not include tax
```

### UI
The above configuration is also available to setup using a simple ui. Go to __eldisplay.local__ to configure the device. 
![](https://github.com/PhPersson/eldisplay/blob/main/images/ui.png)
