# 🚨 Gesture-Controlled Smart Gas, Fire & Safety System

> A touchless safety system that detects gas leaks and fire hazards while enabling gesture-based control using ESP32 and MPU6050.

![ESP32](https://img.shields.io/badge/ESP32-IoT-blue)
![Arduino](https://img.shields.io/badge/Arduino-C++-green)
![Safety](https://img.shields.io/badge/Application-Safety%20System-red)

---

## 🌟 Overview

What if a gas leak occurs when reaching a switch is unsafe?

This project was developed as a smart safety solution that continuously monitors the environment for gas leaks and fire hazards while allowing users to interact with the system without touching any buttons.

Using an **ESP32**, **MQ135 Gas Sensor**, **Flame Sensor**, and **MPU6050 Motion Sensor**, the system can detect dangerous conditions, trigger alerts, display real-time status information, and respond to gesture commands.

The goal is to combine **safety, accessibility, automation, and embedded intelligence** into a single low-cost system.

---

## 🎯 Problem Statement

Gas leaks and fire hazards are among the most common causes of accidents in homes, laboratories, and industrial environments.

Traditional systems often:

- Require physical interaction
- Provide limited feedback
- Lack accessibility features
- Do not support touchless operation

This project addresses these issues through real-time monitoring and gesture-controlled operation.

---

## ✨ Features

### 🌫️ Gas Leak Detection
Detects harmful gases and smoke using the MQ135 sensor.

### 🔥 Fire Detection
Monitors flame presence using an infrared flame sensor.

### 👋 Gesture-Based Control
Control the system without touching any buttons.

| Gesture | Action |
|----------|---------|
| 👉 Tilt Right | System ON |
| 👈 Tilt Left | System OFF |
| ⬆️ Tilt Up | Reset Alarm |
| ⚡ Shake | Emergency Mode |

### 📟 Real-Time LCD Monitoring
Displays system status and gas sensor values continuously.

### 🚨 Smart Alert System

- Red LED for danger indication
- Green LED for safe condition
- Audio alerts using buzzer
- Real-time LCD notifications

### ♿ Accessibility-Oriented Design
Designed for situations where physical interaction may not be safe or convenient.

---

## 🧠 How It Works

The ESP32 continuously reads data from:

- MQ135 Gas Sensor
- Flame Sensor
- MPU6050 Gesture Controller

The system follows a priority-based decision model:

```text
Emergency Mode
      ↓
Fire Detection
      ↓
Gas Detection
      ↓
Safe State
```

### Gas Detected

- Red LED ON
- Buzzer Alert
- LCD Warning Message

### Fire Detected

- Continuous Alert
- High Priority Warning
- Real-Time Notification

### Emergency Gesture

- Triggered by shaking the MPU6050
- Overrides all other states
- Activates emergency mode

---

## 🏗️ System Architecture

```text
             MQ135
               │
               ▼
        ┌────────────┐
        │   ESP32    │
        └────────────┘
          ▲        ▲
          │        │
      MPU6050   Flame Sensor
          │
          ▼

     Gesture Commands

Outputs:
├── LCD Display
├── LEDs
└── Buzzer
```

---

## 🛠️ Components Used

| Component | Quantity |
|------------|-----------|
| ESP32 Development Board | 1 |
| MQ135 Gas Sensor | 1 |
| Flame Sensor | 1 |
| MPU6050 | 1 |
| 16x2 I2C LCD | 1 |
| Buzzer | 1 |
| LEDs | 2 |
| Breadboard | 1 |
| Jumper Wires | As Required |

---

## 🚀 Applications

- Smart Homes
- Laboratories
- Chemical Industries
- Workshops
- Industrial Safety Systems
- Educational IoT Projects
- Accessibility-Oriented Safety Solutions

---

## 📸 Project Demonstration

### Safe Condition
✅ Green LED ON

✅ LCD displays live status

✅ Monitoring active

### Gas Alert
⚠️ Red LED ON

⚠️ Buzzer activated

⚠️ Gas warning displayed

### Fire Alert
🔥 Continuous alarm

🔥 Immediate hazard indication

🔥 High-priority warning

### Emergency Mode
🚨 Triggered by gesture

🚨 Overrides normal operation

🚨 Maximum alert condition

---

## 🔮 Future Scope

- WiFi-Based Notifications
- Mobile App Integration
- Cloud Dashboard
- Data Logging
- Battery Backup
- Voice Alerts
- Automatic Ventilation System
- Industrial-Grade Gas Sensors

---

## 📚 Learning Outcomes

This project provided hands-on experience with:

- Embedded Systems
- ESP32 Programming
- Sensor Interfacing
- I2C Communication
- Real-Time Monitoring
- Gesture Recognition
- IoT System Design
- Safety Automation

---

## 💡 Why This Project Matters

Safety systems should not only detect danger but also make interaction easier during emergencies.

This project demonstrates how low-cost hardware and embedded intelligence can be combined to create a practical, accessible, and scalable safety solution for real-world environments.

---

## 👩‍💻 Author

**Sakshi Gupta**

Electronics & Computer Engineering  
Embedded Systems • IoT • Hardware Innovation

⭐ If you found this project interesting, consider giving it a star!
