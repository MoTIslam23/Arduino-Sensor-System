const int BUTTON_PIN = 2;
const int LED_PIN = LED_BUILTIN;

const unsigned long BLINK_MS = 250;
const unsigned long DEBOUNCE_MS = 25;

bool blinking = false;
bool ledState = false;

int lastReading = LOW;
int stableState = LOW;
unsigned long lastChange = 0;
unsigned long lastToggle = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT);   // external pull-down resistor
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  // debounce
  if (reading != lastReading) {
    lastReading = reading;
    lastChange = millis();
  }

  if (millis() - lastChange >= DEBOUNCE_MS) {
    if (stableState != reading) {
      stableState = reading;

      // rising edge = button press
      if (stableState == HIGH) {
        blinking = !blinking;
        if (!blinking) {
          ledState = false;
          digitalWrite(LED_PIN, LOW);
        }
      }
    }
  }

  if (blinking) {
    unsigned long now = millis();
    if (now - lastToggle >= BLINK_MS) {
      lastToggle = now;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    }
  }
}
