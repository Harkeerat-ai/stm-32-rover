# STM32 Autonomous Rover

## Overview
A multi-mode autonomous rover using STM32 Blue Pill and ESP8266 for IoT telemetry.

## Features
- Obstacle detection using ultrasonic sensor
- Motor control via H-bridge
- UART communication with ESP8266
- Real-time data transmission to web app

## Hardware Used
- STM32 Blue Pill
- ESP8266 (ESP-12F)
- Ultrasonic sensor
- DC motors + driver
- Servo motor

## Architecture
STM32 → UART → ESP8266 → Web App

## Setup Instructions
1. Upload STM32 code
2. Upload ESP8266 code
3. Connect UART pins
4. Power system

## Future Improvements
- Line following mode
- MQTT integration
- Remote control
