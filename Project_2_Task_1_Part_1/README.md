# Part 1: LED Blink

The foundational Arduino sketch — blinks an LED on and off at 1-second intervals.

## What It Does

- Turns an LED on pin 7 **HIGH** for 1 second, then **LOW** for 1 second, repeating indefinitely.

## Circuit

| Component | Connection |
|-----------|------------|
| LED (+)   | Pin D7 (through resistor) |
| LED (-)   | GND |

## Concepts Introduced

- `pinMode()` for configuring digital pins
- `digitalWrite()` for controlling output state
- `delay()` for timing
- The Arduino `setup()` / `loop()` program structure
