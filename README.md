# Arduino Sensor Series

A progressive series of Arduino projects demonstrating embedded systems fundamentals — from basic LED control to a multi-sensor, multi-actuator integrated system. Built on the **Arduino Uno** using only core Arduino libraries (no external dependencies).

## Author

**Mo Islam** — [GitHub: MoTIslam23](https://github.com/MoTIslam23)

## Project Overview

This repository contains five Arduino sketches that build on each other, each introducing new hardware concepts and programming techniques:

| Folder | Description | Key Concepts |
|--------|-------------|--------------|
| [Project_2_Task_1_Part_1](./Project_2_Task_1_Part_1) | LED Blink | Digital output, `setup()`/`loop()` pattern |
| [Project_2_Task_1_Part_2](./Project_2_Task_1_Part_2) | Button-Controlled LED | Digital input, debouncing, state management |
| [Project_2_Task_1_Part_3](./Project_2_Task_1_Part_3) | Dual-Button PWM Brightness | Multi-input logic, PWM (analog output) |
| [Project_2_Task_2](./Project_2_Task_2) | Sensor-Actuator Integration | Analog sensors, software PWM, real-time control |
| [tutorial](./tutotial) | Reference Implementation | Complete working example of the final system |

## Hardware Used

**Sensors (Input):**
- Photoresistor (LDR) with 10k voltage divider — ambient light detection
- HC-SR04 Ultrasonic Distance Sensor — proximity measurement up to ~4m

**Actuators (Output):**
- LEDs and RGB LED (common cathode) with 220 current-limiting resistors
- Passive Buzzer — variable pitch audio feedback

## Final System Behavior

The capstone project (`Project_2_Task_2`) combines all components into a real-time feedback system:

- **Light sensor controls the RGB LED** — dark environments produce blue light, medium light produces green, and bright environments produce red. LED brightness inversely scales with ambient light.
- **Ultrasonic sensor controls the buzzer** — objects closer than 120cm trigger pulsed beeps. Pitch increases and interval decreases as objects get closer, similar to a parking sensor.

## Getting Started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software)
2. Connect an Arduino Uno via USB
3. Open any `.ino` file from the project folders
4. Select your board and port under **Tools**
5. Click **Upload**

No external libraries are required — all sketches use only the Arduino core.

## Repository Structure

```
ArduinoSensorSeries/
├── Project_2_Task_1_Part_1/   # LED blink
├── Project_2_Task_1_Part_2/   # Button + LED with debounce
├── Project_2_Task_1_Part_3/   # Two buttons + PWM brightness
├── Project_2_Task_2/          # Full sensor-actuator system
└── tutotial/                  # Reference implementation
```
