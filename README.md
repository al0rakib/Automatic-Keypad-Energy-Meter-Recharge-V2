# Automating Digital Prepaid Keypad Energy Meters via Mobile App Interface (Wi-Fi Version)

This project presents a modernized solution for automating the manual button-pressing process of prepaid digital keypad energy meters. It replaces the original Bluetooth-Arduino setup with a Wi-Fi-enabled ESP8266 system and a smartphone app interface. This redesign significantly improves accessibility, range, and reliability for remote energy meter recharging.

---

## 📂 Project Files

- `Prepaid_Meter_Automation.ino` – ESP8266 firmware for stepper and servo control
- `Test_Stepper.ino` – Test script for X and Y motors
- `Test_Servo.ino` – Servo motor test script
- `Test_Web.ino` – HTTP GET input handling test
- `Automatic Keypad Energy Meter Recharge V2 Flowchart.mmd` – Mermaid syntax system flow diagram
- `Documentation of Automatic Keypad Energy Meter Recharge V2.pdf` – Complete documentation of the build process
- `Automatic Keypad Energy Meter Recharge V2.fzz` – Circuit Diagram of the System
- `Energy Meter Recharge V2 App.apk` – Downloadable Android Mobile App for Automatic Recharge
- `README.md` – GitHub project overview and guide

---

## 🛠 Hardware Used

- ESP8266 NodeMCU V2 (Wi-Fi Microcontroller)
- 2× Bipolar Stepper Motors with L298N Drivers (X and Y axis)
- SG90 Servo Motor (Z axis tap)
- 11.1V Power Supply (3× 3.7V Li-ion)
- Custom X-Y frame for positioning[2x D8-MOTOR80 was used in this project]
- Digital Prepaid Keypad Energy Meter

---

## 📱 Mobile App Interface

- Built using MIT App Inventor
- Optimized UI for elderly users
- Sends 5-digit token using `http://<ESP-IP>/submit?code=XXXXX`
- Wi-Fi based communication (ESP acts as a web server)

---

## ⚙️ System Workflow

1. User enters a 5-digit recharge token in the mobile app
2. App sends token to ESP8266 via Wi-Fi (HTTP GET request)
3. ESP8266 parses and maps each digit to grid coordinates
4. Stepper motors position the press head to each digit
5. Servo performs a tap to simulate button press
6. System tracks last (X,Y) to optimize movement
7. Sequence completes after all digits are entered

---

## 🔁 Replication Notes

- Adjust `STEP_X_SPACING` and `STEP_Y_SPACING` based on your meter’s keypad layout
- Use test scripts to confirm proper motion before running the final system
- Ensure common GND between ESP8266, L298Ns, servo, and battery
- Include jumper caps on ENA and ENB or connect them to 5V
- Make sure to change ip address in MIT app interface of your microcontroller

---

## 🌐 Future Improvements

- Add mDNS (`esp8266.local`) for dynamic IP handling
- Support SVG or G-code input for drawing/writing bots
- Integrate token confirmation feedback (LCD or voice)
- Convert system to compact XY plotter or printer

---

## 🗓️ Project Timeline

- Designed, tested, and documented in May 2025  
- Project Author: **Abdullah Al Rakib**
- Institution: **KUET**
- Department: **Mechtronics Engineering**
- Student ID: **1931014**
