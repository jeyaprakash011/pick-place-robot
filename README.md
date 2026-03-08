# pick-place-robot
ESP32 based pick &amp; place robot with autonomous and manual control using Blynk, limit switches, and IR object detection for agricultural automation.
# ESP32 Pick & Place Robot

## Project Overview

This project is an **ESP32 based autonomous Pick & Place robot designed for cotton harvesting and object handling applications**. The system uses **limit switches, IR sensors, and relay-based motor control** to perform automated object pickup and placement.

The robot can operate in **two modes**:

• **Automatic Mode** – The robot detects an object using an IR sensor and automatically performs the pick-and-place sequence.  
• **Manual Mode** – The robot can be controlled remotely using the **Blynk IoT mobile application**.

The robotic arm moves in **multiple axes (X, Y, Z)** and uses a **gripper mechanism** to pick objects and place them in a storage container mounted on the robot platform.

This system demonstrates **embedded automation, IoT control, and robotic motion control using ESP32**.

---

## System Design

### CAD Design

![Robot CAD Design](images/cad_design.png)

The robot includes:

• Mobile platform with wheels  
• Storage bin for collected cotton  
• Robotic arm with gripper  
• Multi-axis movement mechanism  

---

## Features

- ESP32 based robotic control system  
- **Automatic object detection using IR sensor**  
- **Manual control using Blynk mobile application**  
- Relay controlled DC motor driving system  
- **Limit switches for position detection**  
- Multi-axis robotic arm movement (X, Y, Z)  
- Gripper control for pick & place  
- Autonomous working cycle  
- Buzzer notification system  

---

## Hardware Components

- ESP32 Development Board  
- Relay Module (Motor control)  
- DC Motors  
- IR Object Detection Sensor  
- Limit Switches (6 units)  
- Buzzer  
- Power Supply  
- Robotic Gripper Mechanism  
- Mobile Robot Chassis  

---

## Software & Technologies

Microcontroller  
ESP32

Programming Language  
Embedded C (Arduino Framework)

Development Environment  
Arduino IDE

IoT Platform  
Blynk IoT

Libraries Used

- WiFi
- BlynkSimpleEsp32

---

## Robot Working Process

### 1️⃣ Homing Process

When the robot starts:

• Arm moves to the **home position**  
• Limit switches define the reference position  
• Buzzer indicates homing completion  

---

### 2️⃣ Automatic Mode

1. Robot moves forward
2. IR sensor detects object
3. Robot stops
4. Gripper closes to grab object
5. Arm lifts the object
6. Arm moves right toward storage bin
7. Gripper opens and releases object
8. Arm returns to original position
9. Cycle repeats

---

### 3️⃣ Manual Mode (Blynk)

The robot can be controlled using the **Blynk mobile app**.

Manual controls include:

- Forward
- Reverse
- Left
- Right
- Arm Up
- Arm Down
- Arm Left
- Arm Right
- Gripper Open
- Gripper Close

---

## Blynk Control Interface

The Blynk app communicates with ESP32 through WiFi allowing remote control of the robot movements.

Control pins:

```
V0  - Forward
V1  - Reverse
V2  - Left
V3  - Right
V4  - Arm Up
V5  - Arm Down
V6  - Arm Left
V7  - Arm Right
V8  - Gripper Open
V9  - Gripper Close
V10 - Auto Mode
```

---

## Safety Features

- Limit switch based motion control
- Automatic stop on position limit
- Debouncing logic for reliable switching
- Emergency stop through Blynk

---

## Applications

- Cotton harvesting robots
- Agricultural automation
- Industrial pick & place systems
- Warehouse object handling
- Embedded robotics research

---

## Future Improvements

- Computer vision based cotton detection
- GPS based field navigation
- Solar powered robot
- AI based harvesting system
- Cloud monitoring system

---

## Author

**Jeyaprakash V**  
Embedded Systems & IoT Developer
