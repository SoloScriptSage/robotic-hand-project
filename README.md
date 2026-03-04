# 🤖 Robotic Hand Project

A wireless gesture-controlled robotic hand built with Arduino, flex sensors, and NRF24L01 radio modules. A glove fitted with flex sensors captures hand movements and transmits them wirelessly to a 3D-printed robotic hand, which mirrors the gestures in real time via servo motors.

Originally developed as an open-source prosthetic research platform.

---

## 📸 Demo

![Robotic Hand Demo](images/3d__model_testing.gif)

---

## ✨ Features

- Real-time wireless gesture control via NRF24L01 (250KBPS, ~100m range)
- 5-finger articulation using MG996R servo motors
- Flex sensor glove for intuitive hand tracking
- Per-finger calibration support
- Simple, hackable codebase — easy to extend

---

## 📁 Repository Structure

```
robotic-hand-project/
│
├── firmware/
│   ├── transmitter/        ← glove Arduino code
│   ├── receiver/           ← hand Arduino code
│   ├── test_sensors/       ← flex sensor calibration helper
│   └── servo_test/         ← servo sweep test
│
├── hardware/
│   ├── schematics/         ← wiring diagrams
│   ├── pcb/                ← PCB files
│   ├── mechanical/
│   │   └── robotic-hand-stls/  ← 3D print files
│   ├── assembly-guides/    ← step by step assembly
│   ├── datasheets/         ← component datasheets
│   └── BOM.md              ← full bill of materials
│
├── docs/
│   ├── calibration.md      ← flex sensor calibration guide
│   └── troubleshooting.md  ← common issues and fixes
│
├── images/                 ← photos and demo gifs
├── .gitignore
├── LICENSE
└── README.md
```

---

## 🛠️ Materials

Full bill of materials with component links and prices → [`hardware/BOM.md`](hardware/BOM.md)

---

## 🗺️ Schematics

Wiring diagrams for both transmitter and receiver → [`hardware/schematics/`](hardware/schematics/)

> ⚠️ Power the NRF24L01 modules from the **3.3V pin only** — they are not 5V tolerant.

---

## 🖨️ 3D Model

The hand structure is sourced from [Viral Science](https://www.viralsciencecreativity.com/post/arduino-flex-sensor-controlled-robot-hand). Print files are available in [`hardware/mechanical/robotic-hand-stls/`](hardware/mechanical/robotic-hand-stls/).

Print settings:
- Material: PLA or PETG
- Infill: 20–30%
- Supports: Yes (for finger joints)

---

## ⚙️ Setup

### 1. Clone the repository
```bash
git clone https://github.com/SoloScriptSage/robotic-hand-project.git
```

### 2. Install Arduino libraries
In Arduino IDE go to **Sketch → Include Library → Manage Libraries** and install:
- `RF24` by TMRh20
- `Servo` (built-in)

### 3. Assemble the hardware
- Print and assemble the 3D hand following the guides in [`hardware/assembly-guides/`](hardware/assembly-guides/)
- Wire flex sensors to the glove according to the schematics
- Wire servos to the receiver board according to the schematics

### 4. Calibrate the flex sensors
Follow the step-by-step guide → [`docs/calibration.md`](docs/calibration.md)

### 5. Flash the firmware
- Flash [`firmware/transmitter/transmitter.ino`](firmware/transmitter/transmitter.ino) to the **glove Arduino**
- Flash [`firmware/receiver/receiver.ino`](firmware/receiver/receiver.ino) to the **hand Arduino**

### 6. Test
- Flash [`firmware/servo_test/servo_test.ino`](firmware/servo_test/servo_test.ino) to verify all servos sweep correctly
- Power both Arduinos and open Serial Monitor — you should see sensor values on the transmitter and matching received values on the receiver

---

## 💻 Code Overview

| File | Description |
|---|---|
| `transmitter.ino` | Reads flex sensors, maps to servo angles, transmits via NRF24L01 |
| `receiver.ino` | Receives data, writes angles to servo motors |
| `test_sensors.ino` | Prints raw flex sensor values for calibration |
| `servo_test.ino` | Sweeps all servos 0→180→0 for hardware testing |

---

## 🧪 Testing

![Sensor Testing](images/sensors_testing.gif)
![Bending Testing](images/bending_testing.gif)

---

## 📖 Docs

- [Calibration Guide](docs/calibration.md)
- [Troubleshooting](docs/troubleshooting.md)

---

## 🚀 Roadmap

- [ ] Per-finger calibration via Serial Monitor wizard
- [ ] Haptic feedback on glove (vibration motors)
- [ ] NRF24L01 external antenna for extended range
- [ ] Replace flex sensors with IMU-based gesture recognition
- [ ] Full prosthetic enclosure design
- [ ] Support for wrist rotation (6th servo)

---

## 🙏 Acknowledgments

- [Viral Science](https://www.viralsciencecreativity.com/post/arduino-flex-sensor-controlled-robot-hand) for the 3D hand model
- [TMRh20](https://github.com/nRF24/RF24) for the RF24 library
- The open-source Arduino community

---

## 📄 License

This project is open-source under the [MIT License](LICENSE).