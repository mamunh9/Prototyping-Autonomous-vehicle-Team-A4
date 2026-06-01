# Autonomous Driving Vehicle – Line Following with Obstacle Handling & Parking

> **Semester Project** – Development of an autonomous vehicle as a semester project for the Prototyping and System Engineering module at Hochschule Hamm-Lippstadt. The vehicle autonomously follows a line, detects and reacts to colored obstacles, optimizes speed, supports multiple routing layouts (oval, figure-8), and executes autonomous parking.


## Table of Contents
- [Overview](#-overview--system-features)
- [System Diagrams](./System%20Diagrams/)
- [Tinkercad Simulation](./Tinkercad%20Simulation/)
- [Hardware](./Hardware/)
- [Prototype Design](./Prototype%20Design/)
- [Assembly](./Assembly/)
- [Code Structure](#-code-structure)
- [Contributors](#-contributors)


## Overview & System Features

This repository presents a complete systems engineering approach to building an autonomous vehicle. The vehicle is designed to be highly responsive and intelligent, capable of achieving the following:

- **Line Following:** Tracks a black line on a white background using infrared (IR) sensors.
- **Obstacle Detection:** Identifies blockages in its path using an ultrasonic sensor.
- **Speed Optimization:** Adjusts motor speed for smoother turns on curves and faster straightaways.
- **Routing:** Supports navigation on both **oval** and **figure-8** tracks.
- **Automatic Finish Line:** Identifies the finish line and seamlessly parks at the designated spot.

---

##  Tinkercad Simulation Prototype

A fully functional simulation model has been constructed in **Tinkercad Circuits** to validate the logic before hardware implementation. 

**Key Virtual Components:**
- Arduino Uno R4 
- 2× IR Line Tracking Sensors
- 2× HC-SR04 Ultrasonic Sensors
- 2× DC Motors


##  Hardware Prototype & Assembly

The real-world implementation leverages customized 3D-printed parts and physical electronic components.

- **[Prototype Design](./Prototype%20Design/):** 3D models including the chassis, motor mounts, IR holders, ultrasonic sensor mounts, and breadboard holsters. 
- **[Assembly Instructions](./Assembly/):** Contains guides for wiring and physically constructing the robot. 
- **[Electronics & Hardware](./Hardware/):** Components, datasheets, and material layouts. 



##  Code Structure
Its done. More to impliment.



##  Contributors

A special thanks to the team behind this project:
- [S M Mahmud Hasan](https://github.com/mahmudhasan9)
- [Md Mamun Hossain](https://github.com/mamunh9)
- [Ryota Takeuchi](https://github.com/Ryota339951)
- [Md Jehadul Hasan](https://github.com/Mdjehad533)
