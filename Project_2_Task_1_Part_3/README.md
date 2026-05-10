# Part 3: Dual-Button PWM Brightness Control

Uses two buttons to select between four LED brightness levels via Pulse Width Modulation (PWM).

## What It Does

| Button 1 | Button 2 | Brightness |
|----------|----------|------------|
| Released | Released | 100% (255) |
| Pressed  | Released | 75% (191)  |
| Released | Pressed  | 50% (127)  |
| Pressed  | Pressed  | 25% (64)   |

## Circuit

| Component | Connection |
|-----------|------------|
| Button 1  | Pin D2 (with external pull-down resistor) |
| Button 2  | Pin D3 (with external pull-down resistor) |
| LED       | Pin D9 (PWM-capable) |

## Concepts Introduced

- **PWM (Pulse Width Modulation)** — simulating analog output on a digital pin using `analogWrite()`
- **Combinational input logic** — mapping multiple binary inputs to discrete output states
- Using PWM-capable pins (denoted with `~` on the Arduino board)
