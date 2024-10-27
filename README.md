<h1 align="center">
  <br>
  <a href=""><img src="https://github.com/PhPersson/eldisplay/blob/main/images/logo.png" alt="logo height="300" width="300"></a>
</h1>

<h4 align="center">Eldisplay är en liten display som drivs av en ESP8266 och visar de aktuella elpriserna i Sverige.</h4>
<p align="center">
  <a href="#vad-ar-eldisplay">•Vad är Eldisplay?</a> •
  <a href="#hur-man-installera">Hur man installerar</a> •
  <a href="#hårdvara">Hårdvara</a>
</p>

<p align="left"></p>
[here](README-en.md)

## Vad är Eldisplay?

Eldisplay föddes ur en enkel insikt: det kändes onödigt att behöva plocka upp mobiltelefonen för att kolla elpriser innan man använde apparater som tvättmaskiner eller diskmaskiner. Jag insåg att det borde finnas ett enklare sätt att hålla koll på priserna.

Därför skapades Eldisplay – en lösning som syftar till att förenkla processen för att övervaka elpriser. Genom att erbjuda omedelbar åtkomst till aktuella elpriser för den nuvarande timmen och de följande två timmarna, gör Eldisplay det möjligt för användare att fatta informerade beslut om sin energiförbrukning. Det eliminerar behovet av att öppna en mobilapplikation varje gång, vilket inte bara sparar tid utan också bidrar till att spara på elräkningarna.


Funktioner i Eldisplay:

* **Realtidspriser:** Visar aktuella elpriser för den aktuella timmen och de kommande två timmarna.
* **Regionsval:** Gör det möjligt för användare att konfigurera inställningar baserat på sitt geografiska område, vilket säkerställer korrekt prisinformation.
* **Webbgränssnitt:** Ett gränssnitt för enkel konfiguration.

<a href=""><img src="https://github.com/PhPersson/eldisplay/raw/main/images/eldisplay.jpeg" alt="" height="40%" width="40%"></a>

## Hur man installerar

1. **Ladda ner .bin:**
   - Gå till [release-sidan](https://github.com/PhPersson/eldisplay/releases) och ladda ner den senaste `.bin`-filen för Eldisplay.

2. **Installera .bin:**
   - Använd [ESPHome Web](https://web.esphome.io/) för att ladda upp `.bin`-filen till din ESP8266.
   - Följ verktygets instruktioner för att välja rätt COM-port och ladda upp.

3. **Åtkomst till webbgränssnittet:**
   - När uppladdningen är klar, anslut till Eldisplays AP.
   - När du är ansluten till WiFi, gå till __eldisplay.local__ för att konfigurera enheten.

<img src="https://github.com/PhPersson/eldisplay/blob/main/images/setup_error.jpeg" width=40% height=40% >

## Hårdvara
<a href=""><img src="https://github.com/PhPersson/eldisplay/raw/main/images/eldisplay_below.jpeg" alt="" height="40%" width="40%"></a>

1. **Hårdvara:**
   - ESP8266 mikrokontroller.
   - ILI9341 display.
   - Strömförsörjning för ESP8266 och displayen.
   - Jumperkablar för anslutningar.

