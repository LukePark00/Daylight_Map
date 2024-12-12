# Daylight_Map

# About
The Daylight Map is a map of the United States that illuminates based on the time of day in each of the five time zones in the country. Depending on the time in these areas, the lights behind the map will light up with different levels of brightness to illustrate the overall daylight found at the current time. The two modes of the map toggle between an "on" setting where all time zones are illuminated and a motion sensor setting where moving the slider will cause only the corresponding time zone to light up. 

# Design Goals
- Retireve time of day and connect brightness levels to certain times
- Use button to toggle between modes
- Implement ultrasonic sensor to isolate different zones
- Create appropriate distance between map and lights

# Installation
Materials Needed:
- Push button
- Ultrasonic Sensor
- 40 LEDs
- 4 Half Sized Breadboards
- ESP32 TTGO T-Display
- USB-C Cable
- 20 220 Ω Resistor
- 1/8" Strathmore
- Tracing Paper
- Tape
- Glue

Connect the hardware and the breadboards as in the Fritzing Diagram and pictures. Then attach it (tape or glue) to the inside of the bottom face of the enclosure. Build the enclosure around the breadboards so that they are stable while leaving a gap for the sensor to detect the slider, the button, and a slot for the USB-C Cable to connect to the ESP32. Cut out a silhouette of the United States on the top face of the box (while again leaving a gap for the slider) and attach tracing paper to the bottom of it. Glue the map to the top of the box.

# Fritzing Diagram
<img width="1205" alt="Screenshot 2024-12-12 at 2 32 13 PM" src="https://github.com/user-attachments/assets/f7d2dce8-a88b-4a4b-9d48-f5d2af5fc0c4" />
