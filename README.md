Chicken Pastil Automation System (Arduino)

An Arduino-based automation system for controlling a Chicken Pastil
processing machine, handling heating, dispensing, motor movement, and
finishing stages with safety and timing controls.

------------------------------------------------------------------------

Features

-   Automated heating cycle
-   Valve control for dispensing
-   Bidirectional motor control (CW / CCW)
-   Spinner activation
-   Buzzer alerts and notifications
-   LCD display interface (20x4 I2C)
-   Time-based automation using Chrono
-   State machine workflow
-   Limit switch safety (extend / retract)
-   Push button start (INPUT_PULLUP)

------------------------------------------------------------------------

Hardware Requirements

-   Arduino (Uno / Mega / compatible)
-   20x4 LCD with I2C module
-   Relay modules / motor driver
-   Heater element
-   Solenoid valve
-   DC motor
-   Spinner motor
-   Limit switches (2x)
-   Push button
-   Buzzer
-   Proper power supply

------------------------------------------------------------------------

Pin Configuration

Heater: 7
Valve: 6
Pilot Light: 8
Motor A: 9
Motor B: 10
Spinner: 11
Button: A2
Limit Return: A0
Limit Extend: A3
Buzzer: 13

------------------------------------------------------------------------

Timing Configuration

HEATER_TIME = 20000
VALVE_TIME = 20000
MOTOR_TIME = 20000
SPINNER_TIME = 20000
HEATER_REST_TIME = 300000

------------------------------------------------------------------------

Workflow

-   Initialize → Move motor to return limit
-   Wait for START
-   Heating
-   Valve dispensing
-   Motor extend
-   Motor retract
-   Spinner
-   Buzzer alert
-   Reset

------------------------------------------------------------------------

Testing Mode (Serial)

0 = All OFF
q = Heater
w = Valve
e = Pilot
r = Motor CW
t = Motor CCW
y = Spinner
u = Buzzer

------------------------------------------------------------------------

Safety

-   Limit switches prevent over-travel
-   Timed operations prevent overheating
-   Manual reset required

------------------------------------------------------------------------

Libraries

Wire.h
LiquidCrystal_I2C.h
Chrono.h
Streaming.h

------------------------------------------------------------------------

Setup

1.  Connect hardware
2.  Install libraries
3.  Upload code
4.  Power system
5.  Press START


