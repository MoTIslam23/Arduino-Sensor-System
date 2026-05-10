# Tutorial: Reference Implementation

This is a standalone reference implementation of the full sensor-actuator system from [Project_2_Task_2](../Project_2_Task_2). It serves as a clean, self-contained example for building and testing the complete circuit.

## What It Does

Combines a photoresistor and ultrasonic distance sensor with an RGB LED and passive buzzer:

- **LDR** reads ambient light and maps it to RGB LED color (dark = blue, medium = green, bright = red) with inversely scaled brightness
- **HC-SR04** measures distance and drives the buzzer with proximity-based pitch and beep rate (closer = faster, higher-pitched beeps)
- **Software PWM** on pin D12 enables smooth dimming of the blue LED channel on a non-PWM pin

See the [Project_2_Task_2 README](../Project_2_Task_2/README.md) for full circuit wiring and detailed behavior descriptions.
