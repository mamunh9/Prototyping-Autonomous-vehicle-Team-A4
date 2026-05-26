# Autonomous Driving Vehicle – Line Following with Obstacle Handling & Parking


> **Semester Project** – Development of an autonomous vehicle as a semester project for Prototyping and System Engineering module at Hochschule Hamm-Lippstadt that follows a line, detects obstacles (by color), avoids them, optimizes speed, supports different routings (oval, figure-8), and parks autonomously.

---

##  Table of Contents
- [Overview](https://github.com/mamunh9/Prototyping-Autonomous-vehicle-Team-A4/blob/main/README.md)
- [Features](#features)
- [System Diagrams](https://github.com/mamunh9/Prototyping-Autonomous-vehicle-Team-A4/tree/main/System%20Diagrams)
- [Tinkercad Simulation](https://github.com/mamunh9/Prototyping-Autonomous-vehicle-Team-A4/tree/main/Tinkercad%20Simulation)
- [Hardware](https://github.com/mamunh9/Prototyping-Autonomous-vehicle-Team-A4/tree/main/Hardware)
- [Prototype Design](https://github.com/mamunh9/Prototyping-Autonomous-vehicle-Team-A4/tree/main/Prototype%20Design)
- [Assembly](https://github.com/mamunh9/Prototyping-Autonomous-vehicle-Team-A4/tree/main/Assembly)
- [Code Structure](#code-structure)
- [Results & Demonstration](#results--demonstration)



## Overview

This repository presents a complete systems engineering approach to building an autonomous vehicle. The vehicle is capable of:

- Following a black line on a white background using infrared sensors.
- Detecting obstacles via ultrasonic sensor.
- Identifying obstacle color (Red, Green, Blue) using an RGB LED and photoresistor (simulated) / TCS3200 (future).
- Reacting based on color: **remove** (red), **avoid** (blue), or **wait** (green).
- Optimizing speed on curves vs. straights.
- Driving in **oval** and **figure-8** routes.
- Performing **automatic parking** at a designated spot.




## Tinkercad Simulation Prototype

A fully functional simulation was built in **Tinkercad Circuits**. It uses:

- Arduino Uno R4
- 2× IR line tracking sensors
- 2× HC-HR04 ultrasonic sensor
- 2× DC motors


###  Simulation Walkthrough




---

## Hardware Prototype 




### Contributors

- [Md Mamun Hossain](https://github.com/mamunh9)
- [Ryota Takeuchi](https://github.com/Ryota339951)
- [S M Mahmud Hasan](https://github.com/Redoy-Hasan)
- [Md Jehadul Hasan](https://github.com/Mdjehad533)
