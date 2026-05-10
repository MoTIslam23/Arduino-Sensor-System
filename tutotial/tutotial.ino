/*******************************************************
 Task 2 (2 Sensors + 2 Actuators) — FINAL (BLUE on D12)
 ------------------------------------------------------
 Sensors:
  1) Photoresistor (LDR) on A0 using voltage divider:
       - LDR -> +5V
       - NODE -> A0
       - NODE -> 10k -> GND
  2) HC-SR04 Ultrasonic:
       - TRIG -> D7
       - ECHO -> D8
       - VCC  -> +5V
       - GND  -> GND

 Actuators:
  1) RGB LED (Common Cathode):
       - Common (longest leg) -> GND rail (your f27)
       - Red   -> D9  through 220Ω
       - Green -> D10 through 220Ω
       - Blue  -> D12 through 220Ω   (your final setup)
     NOTE: D12 is NOT PWM, so Blue uses SOFTWARE PWM below.
  2) PASSIVE buzzer:
       - + -> D3 (your j16 -> D3)
       - - -> GND (your j18 -> GND rail)

 Behavior:
  - LDR controls RGB color + brightness:
      dark -> blue, medium -> green, bright -> red
      (darker = brighter LED)
  - Ultrasonic controls buzzer pitch + beep rate:
      closer -> faster beeps + higher pitch
*******************************************************/

//////////////////// PIN DEFINITIONS ////////////////////
const int LDR_PIN    = A0;

const int TRIG_PIN   = 7;
const int ECHO_PIN   = 8;

const int BUZZER_PIN = 3;   // passive buzzer (+) -> D3, (-) -> GND

// RGB LED pins (match your final wiring)
const int R_PIN = 9;        // PWM
const int G_PIN = 10;       // PWM
const int B_PIN = 12;       // NOT PWM -> software PWM

//////////////////// BLUE SOFTWARE PWM ///////////////////
// This generates a PWM signal on D12 so Blue can dim.
// 2ms period => ~500Hz (usually no visible flicker)
const unsigned long BLUE_PWM_PERIOD_US = 2000;
int blueDuty = 0; // 0..255

//////////////////// BUZZER STATE ////////////////////////
unsigned long lastBeep = 0;
bool beepOn = false;
unsigned long beepStart = 0;

//////////////////// HELPERS /////////////////////////////
int clamp255(int v) {
  if (v < 0) return 0;
  if (v > 255) return 255;
  return v;
}

// Keep Blue dimming working on D12 (software PWM).
// Must be called frequently (every loop).
void updateBlueSoftPWM() {
  unsigned long phase  = micros() % BLUE_PWM_PERIOD_US;
  unsigned long onTime = (unsigned long)blueDuty * BLUE_PWM_PERIOD_US / 255UL;
  digitalWrite(B_PIN, (phase < onTime) ? HIGH : LOW);
}

// Set RGB color. R and G use hardware PWM. B uses software PWM target.
void setRGB(int r, int g, int b) {
  r = clamp255(r);
  g = clamp255(g);
  b = clamp255(b);

  analogWrite(R_PIN, r);
  analogWrite(G_PIN, g);
  blueDuty = b; // software PWM brightness for Blue
}

// Read distance from HC-SR04 in cm. Returns 999 if out-of-range/no echo.
long readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 25000UL); // ~4m max
  if (duration == 0) return 999;
  return (long)(duration / 58UL);
}

//////////////////// SETUP ///////////////////////////////
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);

  Serial.begin(9600);
}

//////////////////// LOOP ////////////////////////////////
void loop() {
  // Keep blue PWM stable on D12
  updateBlueSoftPWM();

  // -------- Read sensors --------
  int  ldr = analogRead(LDR_PIN);   // 0..1023
  long cm  = readDistanceCm();      // distance in cm

  // Optional debug
  Serial.print("LDR=");
  Serial.print(ldr);
  Serial.print("  Dist(cm)=");
  Serial.println(cm);

  // -------- RGB LED from LDR --------
  // Darker -> brighter LED; brighter -> dimmer (but not off)
  int brightness = map(ldr, 0, 1023, 255, 30);
  brightness = clamp255(brightness);

  // One color at a time:
  // dark -> blue, medium -> green, bright -> red
  int r = 0, g = 0, b = 0;
  if (ldr < 341) {
    b = brightness;
  } else if (ldr < 682) {
    g = brightness;
  } else {
    r = brightness;
  }
  setRGB(r, g, b);

  // -------- Buzzer from distance --------
  // Far (>120cm): silent
  // Close: faster beeps + higher pitch
  if (cm > 120) {
    noTone(BUZZER_PIN);
    beepOn = false;
  } else {
    long d = cm;
    if (d < 5) d = 5;
    if (d > 120) d = 120;

    int pitch = map(d, 5, 120, 1600, 200);                 // Hz
    unsigned long interval = (unsigned long)map(d, 5, 120, 80, 700); // ms

    unsigned long now = millis();

    // Start a short beep every "interval"
    if (!beepOn && (now - lastBeep >= interval)) {
      tone(BUZZER_PIN, pitch);
      beepOn = true;
      beepStart = now;
      lastBeep = now;
    }

    // Stop beep after 40ms so it sounds like pulses
    if (beepOn && (now - beepStart >= 40)) {
      noTone(BUZZER_PIN);
      beepOn = false;
    }
  }

  delay(10); // small delay; still fast enough for software PWM
}