# Autonomous Driving Vehicle – Line Following with Obstacle Handling & Parking


> **Academic Project** – Development of an autonomous vehicle that follows a line, detects obstacles (by color), avoids them, optimizes speed, supports different routings (oval, figure-8), and parks autonomously.

---

##  Table of Contents
- [Overview](#overview)
- [Features](#features)
- [System Engineering Model (SysML)](#system-engineering-model-sysml)
- [Tinkercad Simulation Prototype](#tinkercad-simulation-prototype)
- [Hardware Prototype (Upcoming)](#hardware-prototype-upcoming)
- [Setup & Usage](#setup--usage)
- [Code Structure](#code-structure)
- [Results & Demonstration](#results--demonstration)
- [Future Work](#future-work)

---

## Overview

This repository presents a complete systems engineering approach to building an autonomous vehicle. The vehicle is capable of:

- Following a black line on a white background using infrared sensors.
- Detecting obstacles via ultrasonic sensor.
- Identifying obstacle color (Red, Green, Blue) using an RGB LED and photoresistor (simulated) / TCS3200 (future).
- Reacting based on color: **remove** (red), **avoid** (blue), or **wait** (green).
- Optimizing speed on curves vs. straights.
- Driving in **oval** and **figure-8** routes.
- Performing **automatic parking** at a designated spot.

The project follows the **Systems Engineering** V-Model. Task 1 delivers SysML diagrams (requirements, use cases, blocks, state machine, etc.). Task 2 implements a working prototype in **Tinkercad** (simulation). Task 3 (ongoing) will migrate to real hardware.

---

## Features

| Feature | Description |
|---------|-------------|
| **Line Detection** | 2× IR sensors detect line position (left/right/center). |
| **Obstacle Detection** | Ultrasonic HC‑SR04 measures distance. |
| **Color‑Based Reaction** | <ul><li> **Red** → Servo arm pushes obstacle away.</li><li> **Blue** → Vehicle steers around obstacle.</li><li> **Green** →.</li></ul> |
| **Speed Optimization** | Slows down on curves (based on line deviation), speeds up on straights. |
| **Routing** | Selectable **Oval** (continuous loop) or **Figure‑8** (intersection handling). |
| **Automatic Parking** | Detects a line-end marker  → stops. |
| **Safety** | Emergency stop when obstacle too close or line lost. |

---

## System Engineering Model (SysML)

All models are available in the [`/docs/sysml`](/docs/sysml) folder as diagrams (drawn with Draw.io / Papyrus) and as structured text tables. The following diagrams are included:

- **Requirements Diagram** – Captures functional, safety, and project constraints.
- **Use Case Diagram** – Actors: Vehicle, Supervisor; UCs: Drive, Follow Line, Detect Obstacle, Handle by Color, Park, etc.
- **Block Definition Diagram (BDD)** – Top‑level system blocks: `AutonomousVehicleSystem`, `LineSensorArray`, `ObstacleSensor`, `ColorSensor`, `Controller`, `ActuatorSet`, `RoutePlanner`.
- **Internal Block Diagram (IBD)** – Data flow between sensors, controller, and actuators.
- **State Machine Diagram** – States: INIT → IDLE → LINE_FOLLOW → OBSTACLE_DETECTED → HANDLE_OBSTACLE → PARKING → EMERGENCY_STOP.
- **Activity Diagram** – Speed optimization & routing decision workflow.
- **Parametric Diagram** – Constraint equations for speed vs. curvature, braking distance, parking accuracy.

>  *The SysML model satisfies **Task 1** of the project specification.*

---

## Tinkercad Simulation Prototype

A fully functional simulation was built in **Tinkercad Circuits**. It uses:

- Arduino Uno R4
- 2× IR line tracking sensors
- 2× HC-HR04 ultrasonic sensor
- 2× DC motors


###  Simulation Walkthrough




---

## Hardware Prototype 
