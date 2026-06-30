Arduino Nano - LED Blink with Push Button
  ------------------------------------------
  Two modes are included below.
  Only ONE mode should be active at a time.

  Mode 1: DIRECT MODE      - LED is ON only while button is held down
  Mode 2: TOGGLE MODE      - Press once turns LED ON, press again turns it OFF

  Wiring:
    D2  -> Push button -> GND   (uses INPUT_PULLUP, no external resistor needed)
    D13 -> 220 ohm resistor -> LED anode (+)
    LED cathode (-) -> GND

  Set MODE below to 1 or 2 to choose which logic runs.
*/

#define MODE 2   // Change to 1 for Direct Mode, 2 for Toggle Mode

const int buttonPin = 2;
const int ledPin = 13;

#if MODE == 2
bool ledState = false;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
#endif

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
#if MODE == 1
  // ---------- DIRECT MODE ----------
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

#elif MODE == 2
  // ---------- TOGGLE MODE ----------
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && lastButtonState == HIGH) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  }

  lastButtonState = reading;
#endif
}
