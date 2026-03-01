# Smart-Home
Smart House Model
Demonstration: https://www.youtube.com/playlist?list=PLwkcLrl6-p9PPxoxIWMyOB2pYATnKIisF

SmartHouse IoT – Full-Scale Intelligent Home Automation System

Project Overview:
A comprehensive 1 m2 scale model of a smart home, integrating over 10 sensors and actuators to simulate a fully automated living environment. The project features a hybrid control system (Mobile App & Voice Control) with real-time data synchronization.

Key Technical Components:

    Hybrid Control Architecture: Utilized an ESP8266 for Wi-Fi connectivity and cloud communication, interfaced with an Arduino Uno for low-level peripheral management.

    Real-time Cloud Integration: Implemented Firebase Realtime Database to synchronize the state of all household devices (lights, gates, security) across multiple control interfaces.

    Voice & Mobile Interface: Developed a mobile application and integrated Google Assistant via IFTTT/Adafruit IO to allow hands-free voice commands.

    Advanced Electromechanics: Designed and built a functional garage elevator and sliding gates using DC motors, H-Bridges, and custom gear/rack-and-pinion mechanisms.

    Environmental & Energy Management: * Automated climate control using fans and temperature sensors.

        Integrated Solar Panels to simulate sustainable energy harvesting.

        Lighting system featuring both standard and RGB LEDs for mood lighting.

    Security & Alert System: PIR motion sensors trigger a local buzzer alarm and send an automated email notification to the owner upon detecting an intrusion.

Hardware Stack: ESP8266 (NodeMCU), Arduino Uno, H-Bridge (L298N), DC Motors, PIR/Temp/Light Sensors, Water Pump, Solar Panels, Radio Modules.
