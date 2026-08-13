🚗 Wireless Gesture Controlled 4-Wheel Robot Car

A wireless 4-wheel robotic car controlled using hand gestures. The hand controller uses an ESP32 + MPU6050 to detect hand tilting, and commands are transmitted wirelessly to another ESP32 using ESP-NOW. The car ESP32 controls four DC motors through an L298N motor driver.

The project is powered by a custom-made 3S 12V lithium-ion battery pack with a  3S BMS.

---

📌 Project Overview

This project demonstrates a wireless gesture-based robotic vehicle using two ESP32 boards.

The first ESP32 works as a hand gesture transmitter, while the second ESP32 works as the car receiver/controller.

System Flow

          ✋ HAND CONTROLLER
        ┌───────────────────┐
        │     MPU6050       │
        │ Accelerometer +   │
        │     Gyroscope     │
        └─────────┬─────────┘
                  │
                  ▼
        ┌───────────────────┐
        │      ESP32 #1     │
        │    Transmitter    │
        └─────────┬─────────┘
                  │
              ESP-NOW
            Wireless Link
                  │
                  ▼
        ┌───────────────────┐
        │      ESP32 #2     │
        │     Receiver      │
        └─────────┬─────────┘
                  │
                  ▼
        ┌───────────────────┐
        │       L298N       │
        │   Motor Driver    │
        └───────┬─────┬─────┘
                │     │
          Left Motors  Right Motors
             ×2           ×2

---

✨ Features

- ✋ Gesture-based car control
- 📡 ESP-NOW wireless communication
- 🚗 4-wheel drive
- ⚙️ L298N dual H-bridge motor driver
- 🧠 ESP32-based control system
- 📐 MPU6050 accelerometer and gyroscope
- 🔋 Custom 3S 12V lithium-ion battery pack
- 🛡️ Self-made 3S BMS
- 🛑 Automatic safety stop when communication is lost
- 🔌 No Wi-Fi router required

---

🧰 Components

Hand Controller

- ESP32 DevKit
- MPU6050
- Connecting wires
- Battery / portable power source
- Small enclosure or hand-held case

Car

- ESP32 DevKit
- L298N motor driver
- 4 × DC geared motors
- 4-wheel robot chassis
- Wheels
- Custom 3S 12V lithium-ion battery pack
- Self-made 3S BMS
- Connecting wires

---

🔌 Hand Controller Wiring

ESP32 → MPU6050

MPU6050| ESP32
VCC| 3.3V
GND| GND
SDA| GPIO 21
SCL| GPIO 22

The MPU6050 uses I²C communication.

MPU6050 I²C Address

0x68

---

🔌 Car ESP32 → L298N Wiring

L298N| ESP32
ENA| GPIO 15
IN1| GPIO 2
IN2| GPIO 4
IN3| GPIO 16
IN4| GPIO 17
ENB| GPIO 19
GND| GND

Motor Connections

L298N OUT1 + OUT2
        ↓
   Left Motors ×2

L298N OUT3 + OUT4
        ↓
   Right Motors ×2

The two motors on each side are connected in parallel.

---

📡 ESP-NOW Communication

The two ESP32 boards communicate directly using ESP-NOW.

No Wi-Fi router is required.

ESP32 #1
Hand Controller
      │
      │ ESP-NOW
      ▼
ESP32 #2
Car Controller

Commands

Gesture| Command| Car Action
Tilt Forward| "F"| Forward
Tilt Backward| "B"| Backward
Tilt Left| "L"| Left
Tilt Right| "R"| Right
Keep Level| "S"| Stop

---

✋ Gesture Control

The MPU6050 detects acceleration changes caused by tilting the hand controller.

Tilt Forward
      ↓
    ESP32
      ↓
ESP-NOW → F
      ↓
Car moves Forward

Tilt Backward
      ↓
    ESP32
      ↓
ESP-NOW → B
      ↓
Car moves Backward

Tilt Left
      ↓
    ESP32
      ↓
ESP-NOW → L
      ↓
Car turns Left

Tilt Right
      ↓
    ESP32
      ↓
ESP-NOW → R
      ↓
Car turns Right

---

🔋 Custom 3S 12V Battery Pack

The robot uses a custom-made 3S lithium-ion battery pack.

Battery Configuration

3 × Lithium-Ion Cells

Cell 1 ─┐
Cell 2 ─┼── 3S Series Pack
Cell 3 ─┘

Nominal Voltage

3S = 3 × 3.7V
    ≈ 11.1V nominal

Fully Charged Voltage

3 × 4.2V
= 12.6V

The battery pack is therefore commonly referred to as a 3S 12V battery pack.

---

🛡️ Self-Made 3S BMS

A custom 3S BMS (Battery Management System) was designed and assembled for the battery pack.

The BMS is used for battery protection functions such as:

- Overcharge protection
- Over-discharge protection
- Cell monitoring
- Battery pack protection
- Safe charging/discharging management

3S Battery Structure

Cell 1        Cell 2        Cell 3
4.2V max     4.2V max     4.2V max
   │             │             │
   └─────────────┴─────────────┘
                 │
              3S BMS
                 │
                 ▼
            11.1V nominal
            12.6V maximum

«⚠️ Lithium-ion batteries can be dangerous if incorrectly assembled or charged. Use appropriate protection, insulation, cell matching, and a suitable 3S charger/BMS design. Never short-circuit or charge damaged cells.»

---

💻 Software

Development Environment

- Arduino IDE
- ESP32 Board Package
- C/C++

Libraries

Wire.h
WiFi.h
esp_now.h
Adafruit_MPU6050.h
Adafruit_Sensor.h

---

🧠 Pin Configuration

Hand ESP32

MPU6050

SDA → GPIO 21
SCL → GPIO 22
VCC → 3.3V
GND → GND

Car ESP32

L298N

ENA → GPIO 15
IN1 → GPIO 2
IN2 → GPIO 4

IN3 → GPIO 16
IN4 → GPIO 17
ENB → GPIO 19

---

🛑 Safety Stop

The car includes a communication timeout mechanism.

If the car does not receive a command for a short period:

Communication Lost
        ↓
Safety Timer
        ↓
Motors STOP

This helps prevent the car from continuing to move if the wireless controller disconnects.

---

🚀 How to Run

Step 1 — Prepare the Hand Controller

Connect:

ESP32 + MPU6050

Upload the transmitter code.

Step 2 — Prepare the Car

Connect:

ESP32 + L298N + 4 Motors

Upload the receiver code.

Step 3 — Configure ESP-NOW

Get the MAC address of the car ESP32 and add it to the hand controller code.

Example:

uint8_t carMAC[] = {
  0x24, 0x6F, 0x28,
  0xAA, 0xBB, 0xCC
};

Replace the example MAC address with the actual MAC address of your car ESP32.

Step 4 — Test the MPU6050

The MPU6050 should be detected at:

I2C Address: 0x68

Step 5 — Test the Car

For the first test, keep the wheels off the ground.

Test:

Forward
↓
Backward
↓
Left
↓
Right
↓
Stop

Step 6 — Full Test

Once all directions work correctly, place the car on the ground and test the complete wireless gesture-control system.

---

📁 Project Structure

Wireless-Gesture-Controlled-Car/
│
├── Hand_Controller/
│   └── Hand_Controller.ino
│
├── Car_Controller/
│   └── Car_Controller.ino
│
├── Circuit_Diagrams/
│   ├── Hand_Controller_Wiring.png
│   └── Car_Wiring.png
│
├── Images/
│   └── Project_Photos/
│
└── README.md

---

🔮 Future Improvements

- Speed control using hand tilt angle
- Variable PWM motor speed
- Battery voltage monitoring
- OLED/LCD status display
- Emergency stop button
- Improved gesture recognition
- Obstacle detection using ultrasonic sensors
- GPS tracking
- IoT-based monitoring
- Custom PCB for the controller
- Improved motor driver with higher current capacity

---

👨‍💻 Author

Sasidu Wishshanka

Project

Wireless Gesture Controlled 4-Wheel Robot Car

Technologies:

ESP32
MPU6050
ESP-NOW
L298N
DC Motors
3S Li-Ion Battery
Custom 3S BMS
Embedded C/C++
Arduino IDE

---

📜 License

This project is open-source and available for educational and personal use.

Copyright © 2026 Sasindu Wishshanka
