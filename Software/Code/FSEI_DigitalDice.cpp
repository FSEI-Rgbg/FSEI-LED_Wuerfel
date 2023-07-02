/*
Fachschaft Elektro- & Informationstechnik, OTH Regensburg, ©2023

Digitaler Würfel - Lötübung
ATtiny13A oder ATtiny85V

Inputs:    
    Taster mit PullDown und LowPassFilter an PB4 (Pin 3) - Interrupt PCINT4

Outputs:   
    LED Gruppen:
        LED1 = PB1 (Pin 6)
        LED2 = PB2 (Pin 7)
        LED3 = PB3 (Pin 2)
        LED4 = PB0 (Pin 5)
    ┌───┐   ┌───┐
    │ 3 │   │ 1 │
    ├───┼───┼───┤
    │ 2 │ 4 │ 2 │
    ├───┼───┼───┤
    │ 1 │   │ 3 │
    └───┘   └───┘

Funktionsprinzip:
    uC geht direkt in Tiefschlafmodus um Strom zu sparen.
    Sobald der Taster gedrückt wird, aktiviert sich der Timer (der mit 9,6MHz zählt), 
    und zählt endlos nach oben und läuft über. Die CPU ist dabei Idle.
    Sobald der Taster losgelassen wird, wird per XOR und Modulo aus dem Wert des Timers die anzuzeigende Zahl bestimmt.
    Dann wird der Interrupt des Timers aktiviert, welcher den TIMER_COUNTER solange hochzählt, 
    bis etwa 7s vergangen sind. Dann wird alles deaktiviert und wieder in den Tiefschlafmodus versetzt.

Stromaufnahme bei 3V:
    Tiefschlafmodus:    0,088 uA
    0 LEDs, CPU Idle:     0,9 mA
    1 LED, CPU Idle:    1,808 mA
    6 LEDs, CPU Idle:    10,8 mA
*/

// Einbinden aller benötigten Bibliotheken (Zusatzfunktionen)
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// Timer Modus für das Warten auf Abschaltung, dadurch hat er einen hohen Prescaler und wenig Interrupts.
#define TMODE_IDLE 0
// Timer Modus für das Ermitteln einer Zufallszahl, dafür wird die höchste Auflösung und kein Prescaler benötigt.
#define TMODE_TRNG 1


// Zusätzlicher Zähler, um den Timer auf 24-Bit zu erweitern.
volatile unsigned short TIMER_COUNTER = 0;
// Timer Modus Variable, die den derzeitigen Zustand speichert.
volatile unsigned char TIMER_USAGE_MODE = 0;
// Zähler für das Durchlaufen aller Würfelzustände
volatile unsigned char DICE_ANIM_COUNTER = 0;
// Speicher für den vorherigen Würfel-Wurf.
volatile unsigned char PREV_DICE_ROLL = 0;


// Ausgabe der gewürfelten Augenzahl auf LEDs. Rest von PORTB bleibt unverändert.
void DisplayAugenzahl(unsigned char Zahl)     
{
    // Alle LEDs deaktivieren
    PORTB &= ~((1 << PORTB3) | (1 << PORTB2) | (1 << PORTB1) | (1 << PORTB0));

    switch (Zahl)
    {
        case 1: //LED4
            PORTB |= (1 << PORTB0);
        break;

        case 2: // LED1
            PORTB |= (1 << PORTB1);
            break;

        case 3: // LED1 & LED4
            PORTB |= ((1 << PORTB1) | (1 << PORTB0));
            break;

        case 4: // LED1 & LED3
            PORTB |= ((1 << PORTB1) | (1 << PORTB3));
            break;

        case 5: // LED1 & LED3 & LED4
            PORTB |= ((1 << PORTB1) | (1 << PORTB3) | (1 << PORTB0));
            break;

        case 6: // LED1 & LED2 & LED3
            PORTB |= ((1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3));
            break;

        default: 
            break;
    }
}


// Timer im jeweiligen Modus aktivieren und mit einem festgelegten Wert starten.
void activate_timer(unsigned char timer_mode, unsigned char timer_value)
{
    TCCR0B = 0x00;                              // Timer stoppen falls er schon läuft.
    TIMER_USAGE_MODE = timer_mode;              // Timer Modus für Interrupt Routine speichern.
    TIMER_COUNTER = 0;                          // Zusätzlichen Timer Counter zurücksetzen.
    TCNT0 = timer_value;                        // Timer Wert setzen.

    TIMSK0 = (1 << TOIE0);                      // Timer-Interrupt anschalten.

    switch (timer_mode)
    {
        case TMODE_IDLE:
            TCCR0B = ((1 << CS02) | (1 << CS00));// Timer anschalten mit Prescaler 1024.
            break;
        case TMODE_TRNG:
            TCCR0B = (1 << CS00);               // Timer ohne Prescaler anschalten.
            break;
        default:                                // etwas ist falsch, timer nicht starten.
            break;
    }
}


// Interrupt Service Routine (ISR) für Flankenwechsel des Tasters. Pin 4 ist High wenn dieser gedrückt wird.
ISR(PCINT0_vect)
{
    if (PINB & (1 << PINB4))                    // Eingang PIN4 abfragen: Taster gedrückt -> Steigende Flanke
    {
        DICE_ANIM_COUNTER = 0;                  // Animations-Zähler für Zwischenanimation zurücksetzen

        activate_timer(TMODE_TRNG, PREV_DICE_ROLL); // Aktiviere den Timer im Zufallszahlen-Modus

        set_sleep_mode(SLEEP_MODE_IDLE);        // Sleep Mode zu nur Idle ändern, damit die Oszillatoren an bleiben und der Timer zählen kann.
    }
    else                                        // Taster nicht gedrückt -> Fallende Flanke
    {
        PREV_DICE_ROLL ^= TCNT0;                // Alten Timer Wert mit neuem Wert XORen für eine bessere Gleichverteilung der Werte und speichern.

        DisplayAugenzahl((PREV_DICE_ROLL % 6) + 1);  // Zufallsgenerierte Zahl aus Timer Wert berechnen und anzeigen.

        activate_timer(TMODE_IDLE, 0);          // Aktiviere den Timer für die Idle-Abschaltung
    }
}

// Interrupt Service Routine (ISR) für den Overflow des Timers. Wird alle 1 / 9,6 MHz * Prescaler * 255 Sekunden aufgerufen.
// Der Prescaler ist 1 im TMODE_TRNG und 1024 im TMODE_IDLE.
ISR(TIM0_OVF_vect)                              
{                                               

    TIMER_COUNTER += 1;                         // TIMER_COUNTER hochzählen. Dient als Erweiterung für den 8-Bit Counter.

    if (TIMER_USAGE_MODE == TMODE_IDLE)         // Wenn der Timer für die Idle-Abschaltung nach zu langer Zeit verwendet wird:
    {
        if (TIMER_COUNTER >= 255)               // Überprüfe ob etwa 7 Sekunden vergangen sind. Falls ja, System für den Tiefschlaf vorbereiten:
        {            
            TCCR0B = 0x00;                      // Timer stoppen.
            TIMSK0 = 0x00;                      // Timer-Interrupt ausschalten.
            DisplayAugenzahl(0);                // Alle LEDs ausschalten.
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);// Sleep Mode zu kompletten Tiefschalf ändern. nach der ISR wird durch die while Schleife in main der Schlaf gestartet.
        }
    }
    else if (TIMER_USAGE_MODE == TMODE_TRNG)    // Wenn der Timer für die Zufallszahlengenerierung verwendet wird:
    {
        if (TIMER_COUNTER >= 6300)              // Überprüfe ob etwa 1/6 einer Sekunde vergangen ist.
        {
            DICE_ANIM_COUNTER += 1;             // Animations-Counter zum Anzeigen eines "hochzählenden" Würfels zurücksetzen.
            DisplayAugenzahl(DICE_ANIM_COUNTER % 6 + 1);    // Zahl anzeigen.
            TIMER_COUNTER = 0;                  // Timer zurücksetzen.
        }
    }
}


int main() 
{ 
    // Interrupts deaktivieren & initialisieren
    cli();   

    // Definieren der PB0-PB3 Outputs, PB4 Input, PB5 Input
    DDRB = ((1 << DDB3) | (1 << DDB2) | (1 << DDB1) | (1 << DDB0));

    // Vorrübergehend: Pull-Up auf Reset Pin aktivieren. Eigentlich ist PB5 durch R10 auf High gezogen.
    PORTB |= (1 << PORTB5);

    // Timer auf Normal Mode stellen (ist normalerweise default)
    TCCR0A = 0x00;

    // Setzen aller Register für Pin Change Interrupt PCINT4
    PCMSK = (1 << PCINT4);  // Pin Change Interrupt für Pin 4 demaskieren
    GIMSK |= (1 << PCIE);   // Pin Change Interrupt aktivieren
    
    // ADC Modul deaktiveren um Strom zu sparen.
    PRR = (1 << PRADC);

    // Tiefschalfmodus als Schlafmodus setzen. 
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
    
    // Interrupts aktivieren
    sei();          

    // Endlos schlafen gehen sobald er wieder aufwacht.
    do
    {
        sleep_mode();
    } while(1);
}