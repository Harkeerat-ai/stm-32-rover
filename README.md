# STM32 Autonomous Rover (Arduino IDE → Modular PlatformIO Upgrade)

## 🚀 Overview

This project implements an autonomous rover using an STM32 Blue Pill for real-time control and an ESP8266 (ESP-12F) for IoT telemetry.

The system was initially developed using the Arduino IDE as a single `.ino` file for rapid prototyping, and later structured into a modular architecture using PlatformIO for scalability and maintainability.

---

## 🧠 Development Approach

### Phase 1 — Rapid Prototyping (Arduino IDE)

* Implemented full system in a single `.ino` file
* Focused on:

  * Sensor integration (ultrasonic)
  * Motor control
  * Basic obstacle avoidance logic
* Enabled quick testing and hardware validation

### Phase 2 — Modular Refactoring (PlatformIO)

* Refactored code into multiple modules:

  * `sensors`
  * `motors`
  * `servo_control`
  * `logic`
* Introduced structured project architecture
* Improved readability, scalability, and debugging

---

## 🧠 System Architecture

STM32 (Control Layer):

* Sensor processing
* Decision making
* Motor control

ESP8266 (Communication Layer):

* Receives UART telemetry
* Sends data to web application

```
Sensors → STM32 → UART → ESP8266 → Web App
```

---

## ⚙️ Features

* Obstacle detection using ultrasonic sensor
* Motor control via H-bridge
* UART communication between STM32 and ESP8266
* Real-time telemetry transmission
* Transition from monolithic to modular firmware design

---

## 📁 Code Structure Comparison

### 🔴 Initial (Arduino IDE — Single File)

```
STM32_Rover.ino
```

* All logic in one file
* Fast to develop
* Difficult to scale and debug

---

### 🟢 Refactored (PlatformIO — Modular)

```
src/
  main.cpp
  sensors.cpp
  motors.cpp
  servo_control.cpp
  logic.cpp

include/
  config.h
  sensors.h
  motors.h
  servo_control.h
  logic.h
```

* Separation of concerns
* Cleaner architecture
* Easier debugging and extension

---

## 🔌 Hardware Used

* STM32 Blue Pill (STM32F103C8T6)
* ESP8266 (ESP-12F)
* Ultrasonic Sensor (HC-SR04)
* DC Motors + Motor Driver
* Servo Motor

---

## 🔧 Setup Instructions

### Arduino IDE Version

1. Open `STM32_Rover.ino`
2. Select Generic STM32F103C board
3. Upload code to STM32
4. Upload ESP8266 transmitter code separately

---

### PlatformIO Version

1. Open project in VS Code with PlatformIO
2. Build and upload firmware
3. Ensure correct board configuration (`bluepill_f103c8`)

---

## 📡 Communication Format

Example UART message:

```
DIST:23.5,MODE:OBSTACLE
```

---

## 🧪 Future Improvements

* Line following mode
* MQTT-based communication
* Remote control via web interface
* Advanced sensor fusion

---

## 💡 Key Takeaways

* Rapid prototyping enables faster hardware validation
* Modular architecture improves maintainability
* PlatformIO provides a more scalable embedded workflow

---

## 📜 License

Open-source for learning and experimentation
