# Part 2: Button-Controlled LED with Debounce

Adds a physical button to toggle LED blinking on and off, with software debouncing to handle electrical noise.

## What It Does

- Pressing the button toggles the LED between **blinking** (250ms interval) and **off**.
- A 25ms debounce window filters out false triggers caused by mechanical switch bounce.

## Circuit

| Component | Connection |
|-----------|------------|
| Button    | Pin D2 (with external pull-down resistor) |
| LED       | Built-in LED (`LED_BUILTIN`) |

## Concepts Introduced

- `digitalRead()` for reading button state
- **Debouncing** — filtering noisy input signals with a time threshold
- **Rising-edge detection** — responding only to the moment a button is pressed, not while it's held
- **State management** — tracking multiple variables (`blinking`, `ledState`, `stableState`) across loop iterations
- Non-blocking timing with `millis()` instead of `delay()`
