# FSEI - LED Würfel - Lötübung

Dieses Projekt wurde als Lötübung ins Leben gerufen. Es handelt sich um eine kleine Platine mit 7 LEDs und einem Taster. Beim Drücken des Tasters wird eine Zahl zwischen 1 und 6 gewürfelt, wie bei einem echten Würfel auch.



## Wie sieht denn der Würfel eigentlich aus?
Bei einem solchen Projekt darf natürlich der FSEIgel nicht fehlen. Er hat selbstverständlich seinen ganz eigenen Platz auf der Platine bekommen.<p>
![Wuerfel Version v1.0](/Bilder/v1.0/Animation_highQuality.gif)<p>
![Wuerfel Version v2.0](/Bilder/v2.0/Render_KiCAD_v2.0_FrontAndBack.png)<p>
![Wuerfel Version v2.0 Back](/Bilder/v2.0/Render_JLCPCB-Gerber_FrontAndBack.png)<p>
Eine [interaktive BOM](https://htmlpreview.github.io/?https://github.com/FSEI-Rgbg/FSEI-LED_Wuerfel/blob/main/Hardware%20-%20KiCAD/KiCAD-Project/bom/FSEI_WuerfelPlatine_v2.0.html) zur einfachen Komponentenplatzierung gibt's natürlich auch.


 
## Projekt Status
Der Würfel ist voll funktionsfähig und als Lötübung in der Fachschaft Elektro- und Informationstechnik als Kit mit allen benötigten Komponenten sowie bereits installierter Software erhältlich.

Still ToDo:
- Version 2.0 ist (Stand 02.07.2023) noch UNTESTED!
- Dokumentation
- Bilder von KIT hinzufügen

 
## Zielgruppe / Dauer
<p> Diese Lötübung zielt auf alle Elektro- und Lötbegeisterten, oder die die es noch werden möchten, ab einem Alter von etwa 12-14 Jahren ab.
<p>Mit ein wenig handwerklichem Geschick kann nach etwa 30-45 Minuten losgewürfelt werden.


 
## Kit
**TODO** - _Bild folgt!_
<br>
<p>Der Würfel wird mit allen benötigten Bauteilen in einer kleinen Box herausgegeben. Enthalten ist alles, von der Platine, über die Batterie bis hin zu den LEDs.
<p>Wenn es für dich möglich ist, würden wir dich bitten, die Box nach erfolgreichem Zusammenbau wieder bei uns abzugeben.
<p>Danke für deine Mithilfe.


## Dokumentation
**TODO**
<br>
Eine Dokumentation wie alles funktioniert, zusammengebaut werden muss inkl. einer kurzen Erklärung für alles Weitere findest du [hier](/Doku/Dokumentation-FSEI-LED_Wuerfel_v2.0.pdf).<p>
Der interaktive Bestückungsplan ist [hier](https://htmlpreview.github.io/?https://github.com/FSEI-Rgbg/FSEI-LED_Wuerfel/blob/main/Hardware%20-%20KiCAD/KiCAD-Project/bom/FSEI_WuerfelPlatine_v2.0.html) zu finden. Damit kannst du einfach der Reihe nach alle Komponenten einbauen und Stück für Stück abhaken, was du schon erledigt hast.

 
## Support
Bei Problemen, Fragen oder Anregungen bitte einfach bei der Fachschaft Elektro- und Informationstechnik (S060) melden.


 
## Software
**TODO**
<br>
Beim Drücken des Tasters wird ein Timer gestartet, außerdem startet eine Würfelanimation. Beim Loslassen des Tasters wird eine Zufallszahl gewürfelt, dargestellt und nach etwa 7 Sekunden wieder ausgeschalten. Durch die gedrückte Zeit des Tasters ergibt sich hierbei die Zufälligkeit. <p>
Weitere Details findest du in der [Dokumentation](#Dokumentation) oder im [Programmcode](/Software/Code/).


 
## Hardware
<p>Die Version 1.0 des Würfels wurde mit Hilfe von EasyEDA erstellt. Die Version 2.0 der Platine enthält einige Verbesserungen des ursprünglichen Designs und wurde in KiCAD realisiert.
<p>Im Mittelpunkt der Platine steht neben unserem FSEIgel natürlich ein kleiner Computer, ein sogenannter Mikroprozessor. Wir haben uns hierbei für den ATtiny13A von Atmel entschieden.


 
## Technische Daten / Stromverbrauch
- Stromaufnahme bei 3V: <p>
Modus  &  Stromaufnahme <p>
0,088 uA  @  Tiefschlafmodus <p>
0,9 mA  @  0 LEDs, CPU Idle <p>
1,808 mA  @  1 LED, CPU Idle <p>
10,8 mA  @  6 LEDs, CPU Idle

- Maße: 60 x 35 x ~10 mm

- Verwendungszweck: Würfel für Spieleabende


 
## Ich habe einen Bug gefunden oder eine Verbesserung
[Siehe Support](#Support)


 
## Wir sind ein Verein oder Gruppe von Studenten und wollen mehrere Bausätze kaufen
Es ist toll, dass du anderen Zeigen möchtest wie einfach Löten oder Elektrotechnik sein kann. Melde dich bei uns.



## Autoren
- Leo Scherer
- Patrick Lermer

 
## Inspired by
BlinkyParts
- https://github.com/Binary-Kitchen/SolderingTutorial
- https://binary-kitchen.github.io/SolderingTutorial/
- https://shop.blinkyparts.com/de/Bausaetze/

 
## Copyright and Authorship
[CC-BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) - Fachschaft Elektro- und Informationstechnik der OTH Regensburg

© [FSEI OTH Regensburg](fsei-regensburg.de)