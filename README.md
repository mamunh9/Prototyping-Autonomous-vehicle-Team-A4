# POverview

This project focuses on developing a autonomous vehicle capable of driving on a predefined track using line detection, obstacle avoidance, and color-based decision making.

The system is designed following Systems Engineering principles and modeled using SysML diagrams, with an initial prototype simulated in Tinkercad.rototyping-Autonomous-vehicle.

Features
 Line following (track-based navigation)
 Obstacle detection and avoidance
 Color-based behavior (e.g., stop, reroute)
 Speed optimization
 Route execution:
 Oval track
 Figure-eight track
 Autonomous parking

 System Engineering Approach

This project is developed using a structured Systems Engineering methodology, including:
Requirements Engineering
Functional Requirements (line detection, obstacle avoidance, etc.)
Non-Functional Requirements (real-time response, reliability)
SysML Modeling
Requirements Diagram
Use Case Diagram
Block Definition Diagram (BDD)
Internal Block Diagram (IBD)
Activity Diagram
State Machine Diagram
System Architecture

Main Components
Sensors
Line sensors (IR)
Ultrasonic sensor 
Color sensor
Controller
Microcontroller ( Arduino)
Actuators
DC motors
Motor driver
Power Supply


System Workflow
Capture sensor data
Detect line position
Check for obstacles
Identify color signals
Make driving decisions
Control motors accordingly
