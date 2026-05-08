## Arduino tests
Via de app van ReServeBox wordt er een code ontvangen die je nadien kunt ingeven op een keypad aan de lockers. Om dit principe te testen wordt er gebruik gemaakt van een arduino uno, de 12-Channel Capacitive Touch Keypad (ATtiny1616) en wat verbindingsdraden. 

### Voorbeeld code keypad
Vooralleer er begonnen werd met programmeren werd er informatie opgezocht over de keypad die gebruikt wordt. ([Info](https://wiki.seeedstudio.com/Grove-12-Channel-Capacitive-Touch-Keypad-ATtiny1616-/#features)) Bij deze pagina werd er ook een voorbeeldcode meegegeven om te testen indien de keypad werkt. Tijdens het testen werden er enkele problemen vastgesteld:
* Indien de informatie gevolgd werd over de keypad, dan werd er geen info ingelezen in de seriële monitor (er kwam altijd een error op).
Dit kwam omdat de TX pin van de keypad aangesloten was op de TX pin van de arduino en idem voor de RX pin. Dit kwam omdat de twee pinnen die informatie (TX) versturen aan elkaar geschakeld waren en kreeg de keypad geen informatie binnen, idem voor de RX pinnen. Dus werd de conclusie gemaakt dat de draden verwisseld moesten worden. 
We kregen telkens volgende error:
![Error TX en RX](/imgs/Error.png)

<p align="center">
</p>

* Tijdens het validatieproces trad er een defect op waarbij de seriële monitor uitsluitend onleesbare karakters (weergave als blokjes) vertoonde. Dit fenomeen werd veroorzaakt door een conflict op de hardwarematige seriële communicatiepoorten.

De keypad was aanvankelijk aangesloten op de **TX (Transmit)** en **RX (Receive)** pinnen van de Arduino. Deze specifieke pinnen zijn gereserveerd voor de seriële communicatie tussen de microcontroller en de computer. Door externe hardware op deze poorten aan te sluiten, ontstond er een interferentie tussen de datastroom van de keypad en de communicatie met de seriële monitor. In feite trachtten twee verschillende processen gelijktijdig gebruik te maken van hetzelfde communicatiekanaal, wat resulteerde in corrupte data-overdracht.

Om dit conflict op te lossen, is de hardwareconfiguratie aangepast. De keypad is verplaatst naar digitale pinnen **2 en 3**. Door gebruik te maken van softwarematige seriële communicatie op deze alternatieve pinnen, bleven de hardwarematige TX/RX-poorten vrij voor de verbinding met de seriële monitor, waarna de dataoverdracht correct kon worden voltooid.
![Fout hokjes](/imgs/hok.png)

<p align="center">
</p>

![Opstelling Keypad](/imgs/OP1.jpg)

<p align="center">
</p>

* [Voorbeeld code](/arduino/Voorbeeld%20code/Vb_code_touch_pad/Vb_code_touch_pad.ino)

### Code lockers
Om de lockers te kunnen openen met de keypad werd de voorbeeldcode aangepast naar een code die gebruikt kan worden om lockers open te doen die na een bepaalde tijd weer sluit. De code is ook voorzien van een knop die controleert indien de code correct is (Dit is de "#" op de keypad). Ook is deze voorzien van een knop om de code te wissen indien de foute code ingegeven werd. (Dit is het "*" op de keypad)
* Om te controleren als de code effectief werkt werd er gebruik gemaakt van een led die zal oplichten indien de locker opent. 
* Het enige probleem waar we nog nog mee zitten is om de code binnen te lezen rechtstreeks van de app. Nu werkt het enkel met cijfercode die voorgeprogrameerd is.

![Opstelling Locker](/imgs/OP2.jpg)

<p align="center">
</p>

* [Voorlopige code](/arduino/Code%20lockers/code_touchpad/code_touchpad.ino)

### Voorbeeld code display

Tijdens de ontwikkeling van de Arduino-code voor het ReServeBox-project traden er fouten op bij het integreren van de code voor de LCD-Display in de bestaande code. Deze foutmeldingen verschenen pas wanneer de LCD-code werd toegevoegd aan de reeds werkende code.

Om de oorzaak te achterhalen, werden alle componenten opnieuw afzonderlijk getest. In deze fase functioneerde elk onderdeel, inclusief de LCD en keypad, correct met hun voorbeeld code.

Bij het opnieuw samenvoegen van de verschillende codes ontstonden echter weer problemen. Later bleek dat er twee regels code ontbraken. Na het corrigeren hiervan bleef de compiler foutmeldingen geven. Er werd specifiek aangegeven dat er in het begin van de code een puntkomma ontbrak.

Wanneer deze puntkomma op de aangeduide plaats werd toegevoegd, resulteerde dit in meerdere bijkomende foutmeldingen. Eén van deze fouten verwees naar een regel binnen de keypad-code, hoewel deze code afzonderlijk wel correct werkte.

Na verdere analyse (met ondersteuning van AI) werd vastgesteld dat de werkelijke oorzaak zich onderaan de code bevond, waar effectief een puntkomma ontbrak. Na het toevoegen van deze ontbrekende puntkomma verdwenen alle foutmeldingen en functioneerde de geïntegreerde code correct.

Tot slot werd bijkomende feedback toegepast om de code te optimaliseren en de leesbaarheid te verbeteren.

![Opstelling display](/imgs/OPD_LCD1.jpg)


[info](https://wiki.seeedstudio.com/Grove-16x2_LCD_Series/)

* [Voorbeeld code display](/arduino/HelloWorld_LCD_GROVE/HelloWorld_LCD_GROVE.ino)

### Eind code

Na het oplossen van alle initiële fouten werd de code verder verfijnd volgens de wensen van de gebruiker. Zo werd er gevraagd om een beveiliging in te bouwen waarbij het aantal foutief ingevoerde codes beperkt wordt tot maximaal drie pogingen. Wanneer drie keer een verkeerde code wordt ingevoerd, wordt het systeem gedurende drie minuten geblokkeerd voordat er opnieuw een poging kan worden gedaan.

Tijdens de implementatie van deze functionaliteit trad er opnieuw een fout op. Deze bleek veroorzaakt te zijn door het gebruik van een int-datatype voor tijdsregistratie, terwijl hiervoor een unsigned long vereist is (int waarden tot ongeveer 32.000). Na het aanpassen van het datatype werd dit probleem opgelost.

Na deze aanpassing traden er nog enkele bijkomende foutmeldingen op, die veroorzaakt werden door ontbrekende puntkomma’s. Na het corrigeren van deze kleine fouten functioneerde de code opnieuw correct.


![Schakeling](/imgs/OPE.jpg)

![3D-print](/imgs/OPP.jpg)

* [Code laatste versie](/arduino/Code_laatste_versie/Code_laatste_versie.ino)
