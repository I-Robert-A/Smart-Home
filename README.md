# Smart-Home
Smart House Model
Demonstration: https://www.youtube.com/playlist?list=PLwkcLrl6-p9PPxoxIWMyOB2pYATnKIisF

SmartHouse IoT – Full-Scale Intelligent Home Automation System

Project Overview:
A comprehensive scale model of a multi-level smart home, integrating over 10 sensors and actuators. The project showcases a hybrid control architecture and a custom-built vertical transport system managed by an optimized scheduling algorithm.

Key Technical Components:

    Hybrid Control & Cloud Sync: Utilized an ESP8266 (NodeMCU) as the primary gateway for Wi-Fi connectivity, synchronized with an Arduino Uno for low-level hardware abstraction. Data persistence and real-time state tracking were handled via Firebase Realtime Database.

    Intelligent Elevator System: Designed and implemented a multi-level elevator using a DC motor, H-Bridge, and a rack-and-pinion mechanism. The system features a custom scheduling algorithm that queues floor requests and optimizes travel paths, ensuring efficient vertical movement across all levels.

    Garage & Gate Automation: Engineered a functional garage with an integrated car lift and automated sliding gates, utilizing mechanical gears and precise motor timing.

    Environmental Control & Energy: * Implemented an automated climate control system using temperature sensors and cooling fans.

        Integrated Solar Panels to demonstrate energy harvesting and sustainable power distribution within an IoT ecosystem.

        Advanced lighting control using both standard and RGB LEDs for status indication and ambient effects.

    Security & Remote Alerts: Integrated PIR motion sensors that trigger a local acoustic alarm (buzzer) and push an automated email notification to the owner’s smartphone upon detection of unauthorized entry.

    Interface: Dual-mode control through a custom-built mobile application and voice integration with Google Assistant, allowing for a seamless user experience.

Hardware Stack: ESP8266, Arduino Uno, L298N H-Bridge, DC Motors, PIR/Temp/LDR Sensors, Water Pump, Solar Panels, Radio Modules (RF).
