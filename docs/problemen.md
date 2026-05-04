## Arduino tests
Via de app van ReServeBox wordt er een code ontvangen die je nadien kunt ingeven op een keypad aan de lockers. Om dit principe te testen wordt er gebruik gemaakt van een arduino uno, de 12-Channel Capacitive Touch Keypad (ATtiny1616) en wat verbindingsdraden. 

### Voorbeeld code keypad
Vooralleer er begonnen werd met programmeren werd er informatie opgezocht over de keypad die gebruikt wordt. ([Info](https://wiki.seeedstudio.com/Grove-12-Channel-Capacitive-Touch-Keypad-ATtiny1616-/#features)) Bij deze pagina werd er ook een voorbeeldcode meegegeven om te testen indien de keypad werkt. Tijdens het testen werden er enkele problemen vastgesteld:
* Indien de informatie gevolgd werd over de keypad, dan werd er geen info ingelezen in de seriële monitor (er kwam altijd een error op).
Dit kwam omdat de TX pin van de keypad aangesloten was op de TX pin van de arduino en idem voor de RX pin. Dit kwam omdat de twee pinnen die informatie (TX) versturen aan elkaar geschakeld waren en kreeg de keypad geen informatie binnen, idem voor de RX pinnen. Dus werd de conclusie gemaakt dat de draden verwisseld moesten worden. 
We kregen telkens volgende error:
![alt text](/imgs/Error.png)

<p align="center">
</p>

* Tijdens het testen verkregen we enkel hokjes te zien op de seriële monitor. 
Dit probleem was er omdat de draden geschakeld waren op de pinnen TX en RX. Deze twee poorten zorgen ervoor dat er data van de keypad naar de arduino gestuurd kan worden en omgekeerd. Dit zorgde er voor dat de arduino zegmaar twee seriële monitoren had en deze werkten elkaar tegen. Na enkele testen werd er vastgesteld dat de TX en RX pinnen moesten gewijzigd worden door de pinnen 2 en 3 op de arduino.
![alt text](/imgs/hok.png)

<p align="center">
</p>

![alt text](/imgs/OP1.jpg)

<p align="center">
</p>

* [Voorbeeld code](/arduino/Voorbeeld%20code/Vb_code_touch_pad/Vb_code_touch_pad.ino)

### Code lockers
Om de lockers te kunnen openen met de keypad werd de voorbeeldcode aangepast naar een code die gebruikt kan worden om lockers open te doen die na een bepaalde tijd weer sluit. De code is ook voorzien van een knop die controleert indien de code correct is (Dit is de "#" op de keypad). Ook is deze voorzien van een knop om de code te wissen indien de foute code ingegeven werd. (Dit is het "*" op de keypad)
* Om te controleren als de code effectief werkt werd er gebruik gemaakt van een led die zal oplichten indien de locker opent. 
* Het enige probleem waar we nog nog mee zitten is om de code binnen te lezen rechtstreeks van de app. Nu werkt het enkel met cijfercode die voorgeprogrameerd is.

![alt text](/imgs/OP2.jpg)

<p align="center">
</p>

* [Voorlopige code](/arduino/Code%20lockers/code_touchpad/code_touchpad.ino)

### Voorbeeld code display

[info](https://wiki.seeedstudio.com/Grove-16x2_LCD_Series/)

* [Voorbeeld code display](/arduino/HelloWorld_LCD_GROVE/HelloWorld_LCD_GROVE.ino)

### Eind code

max 3 fouten + 3min timer
6 codes hardcoded

* [Code laatste versie](/arduino/Code_laatste_versie/Code_laatste_versie.ino)