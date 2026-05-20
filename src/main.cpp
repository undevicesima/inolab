#include <Arduino.h>
#include <Servo.h>
#include <./../hardware/pins.h>

#define DELAY_5S      delay(5000)
#define DELAY_1S      delay(1000)
#define DELAY_500MS   delay(500)
#define DELAY_50MS    delay(50)
#define DEBOUNCE_DELAY  50  /*50 Millisekunden Entprellzeit*/

Servo myServo;

// --- Volatile Variablen für die ISR (Interrupt Service Routinen) ---
// volatile ist zwingend nötig, da sich die Werte im Interrupt ändern!
volatile bool button1Pressed = false;
volatile bool button2Pressed = false;
volatile bool updateSerial = false;

// --- Entprellt-Variablen (Debouncing) ---
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;

// --- Interrupt Service Routine für Taster 1 ---
void rpsButton1ISR() {
    unsigned long currentTime = millis();
    if ((currentTime - lastDebounceTime1) > DEBOUNCE_DELAY) {
        // Taster zieht gegen GND (LOW = gedrückt, HIGH = losgelassen)
        button1Pressed = (digitalRead(BUTTON_1_PIN) == LOW);
        lastDebounceTime1 = currentTime;
        updateSerial = true;
    }
}

// --- Interrupt Service Routine für Taster 2 ---
void rpsButton2ISR() {
    unsigned long currentTime = millis();
    if ((currentTime - lastDebounceTime2) > DEBOUNCE_DELAY) {
        // Taster zieht gegen GND (LOW = gedrückt, HIGH = losgelassen)
        button2Pressed = (digitalRead(BUTTON_2_PIN) == LOW);
        lastDebounceTime2 = currentTime;
        updateSerial = true;
    }
}

void setup()
{
    // Serielle Konsole starten
    Serial.begin(9600);

    // Servo initialisieren
    myServo.attach(SERVO_PIN);

    // Taster-Pins mit internem Pull-up aktivieren (GND-Schaltung)
    pinMode(BUTTON_1_PIN, INPUT_PULLUP);
    pinMode(BUTTON_2_PIN, INPUT_PULLUP);

    // Interrupts anfügen: Reagiert auf jede Pegeländerung (RISING und FALLING)
    attachInterrupt(digitalPinToInterrupt(BUTTON_1_PIN), rpsButton1ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(BUTTON_2_PIN), rpsButton2ISR, CHANGE);

    Serial.println("System bereit. Warte auf Taster/Potentiometer...");
}

void loop()
{
    // 7.1 Textnachricht über die serielle Konsole ausgeben, wenn sich ein Status geändert hat
    if (updateSerial) {
        updateSerial = false; // Flag zurücksetzen

        Serial.print("Taster-status - Taster 1: ");
        Serial.print(button1Pressed ? "GEDRUECKT" : "LOSGELASSEN");
        Serial.print(" | Taster 2: ");
        Serial.println(button2Pressed ? "GEDRUECKT" : "LOSGELASSEN");
    }

    // Target-Winkel für den Servo bestimmen
    int targetAngle = 0;

    // 7.3 Logik für die Tatterprioritäten
    if (button1Pressed && button2Pressed) {
        // Beide Taster gedrückt → 90°
        targetAngle = 90;
    }
    else if (button1Pressed) {
        // Nur Taste 1 gedrückt → 0°
        targetAngle = 0;
    }
    else if (button2Pressed) {
        // Nur Taste 2 gedrückt → 180°
        targetAngle = 180;
    }
    else {
        // Keine Taste gedrückt → Potentiometerwert einlesen (0 bis 1023) und auf (0° bis 180°) skalieren
        int potiValue = analogRead(POTI_PIN);
        targetAngle = map(potiValue, 0, 1023, 0, 180);
    }

    // Servo auf die ermittelte Position fahren
    myServo.write(targetAngle);

    // Kleines Delay zur Stabilisierung des Analog-Werts
    delay(15);
}