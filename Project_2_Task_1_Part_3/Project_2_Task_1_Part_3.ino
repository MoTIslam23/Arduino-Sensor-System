const int BUTTON1_PIN = 2;   // existing button
const int BUTTON2_PIN = 3;   // new button you will add
const int LED_PWM_PIN = 9;   // MUST be a PWM pin (~9)

void setup() {
  pinMode(BUTTON1_PIN, INPUT);   // external pull-down resistor
  pinMode(BUTTON2_PIN, INPUT);   // external pull-down resistor
  pinMode(LED_PWM_PIN, OUTPUT);
}

void loop() {
  bool b1 = (digitalRead(BUTTON1_PIN) == HIGH);
  bool b2 = (digitalRead(BUTTON2_PIN) == HIGH);

  int pwm;

  if (!b1 && !b2) {
    pwm = 255;     // 100%
  } else if (b1 && !b2) {
    pwm = 191;     // ~75%
  } else if (!b1 && b2) {
    pwm = 127;     // ~50%
  } else {
    pwm = 64;      // 25% (both pressed)
  }

  analogWrite(LED_PWM_PIN, pwm);
}
