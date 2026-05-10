# Task 2: Multi-Sensor Actuator System

The capstone project — integrates two sensors and two actuators into a real-time feedback system.

## What It Does

**Light Sensor (LDR) controls the RGB LED:**
- Dark environment (LDR 0-341) — blue light
- Medium light (LDR 341-682) — green light
- Bright environment (LDR 682-1023) — red light
- LED brightness inversely scales with ambient light (darker = brighter LED)

**Ultrasonic Sensor (HC-SR04) controls the Buzzer:**
- Objects > 120cm away — silent
- Objects < 120cm — pulsed beeps with pitch and rate scaling by proximity
- Closest range (5cm): 1600 Hz pitch, 80ms beep interval
- Farthest trigger (120cm): 200 Hz pitch, 700ms beep interval

## Circuit

| Component | Connections |
|-----------|-------------|
| **Photoresistor (LDR)** | LDR to +5V; junction to A0 and 10k resistor to GND |
| **HC-SR04 Ultrasonic** | TRIG to D7, ECHO to D8, VCC to +5V, GND to GND |
| **RGB LED (Common Cathode)** | Red to D9, Green to D10, Blue to D12 (each through 220 resistor); common to GND |
| **Passive Buzzer** | (+) to D3, (-) to GND |

## Concepts Introduced

- **Analog sensor reading** — `analogRead()` for continuous-range input (0-1023)
- **Ultrasonic distance measurement** — trigger/echo pulse timing with `pulseIn()`
- **Software PWM** — custom PWM implementation for pin D12 (not hardware PWM-capable) using `micros()` timing at ~500 Hz
- **Sensor-to-actuator mapping** — `map()` to translate sensor ranges into actuator control values
- **Real-time multi-device control** — managing multiple inputs and outputs simultaneously in a single loop
- **Serial debugging** — printing sensor values for monitoring via the Serial Monitor
