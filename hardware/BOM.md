# Bill of Materials

Full component list for the robotic hand project. Includes both the glove (transmitter) and the robotic hand (receiver).

---

## Electronics

| # | Component | Description | Qty | Unit Price (est.) | Link |
|---|---|---|---|---|---|
| 1 | Arduino Uno / Mega | Microcontroller — one for glove, one for hand | 2 | ~$10 | [Amazon](https://a.co/d/7hcBaU4) |
| 2 | NRF24L01+ Module | 2.4GHz wireless transceiver | 2 | ~$2 | [Amazon](https://a.co/d/2pLEXYt) |
| 3 | Flex Sensor 2.2" | Bend-sensitive resistor for each finger | 5 | ~$8 | [Amazon](https://a.co/d/0HHEU9b) |
| 4 | MG996R Servo Motor | High-torque servo for finger actuation | 5 | ~$5 | [Amazon](https://a.co/d/9qywIPb) |
| 5 | 10kΩ Resistor | Pull-down resistor for flex sensor voltage divider | 5 | ~$0.10 | [Amazon](https://a.co/d/1EXjHHf) |
| 6 | LiPo 7.4V / NiMH 7.2V Battery | Power supply for servo side | 1 | ~$15 | [Amazon](https://a.co/d/2NYQ9gW) |
| 7 | Jumper Wires | M-M and M-F for connections | 1 set | ~$5 | [Amazon](https://a.co/d/2u9a7ZK) |

---

## Mechanical

| # | Component | Description | Qty | Link |
|---|---|---|---|---|
| 1 | 3D Printed Hand Parts | STL files in [`hardware/mechanical/robotic-hand-stls/`](mechanical/robotic-hand-stls/) | 1 set | — |
| 2 | Fish Wire | Finger tendon line | ~1m | [Amazon](https://a.co/d/iEQPEsA) |
| 3 | Hot Glue | For securing components | — | [Amazon](https://a.co/d/2u9a7ZK) |
| 4 | M2/M3 Screws | For mounting servos to hand frame | ~20 | — |

---

## Tools Required

| Tool | Notes |
|---|---|
| 3D Printer | PLA or PETG recommended |
| Soldering Iron | For secure sensor connections |
| Hot Glue Gun | For cable management and securing parts |
| Multimeter | For troubleshooting connections |
| Arduino IDE | Version 2.x recommended |

---

## Notes

- NRF24L01 modules must be powered from **3.3V**, not 5V
- MG996R servos draw significant current — power them from the battery directly, not from Arduino 5V
- A capacitor (100µF) across the NRF24L01 power pins helps stabilize the module

---

*Schematics are available in [`hardware/schematics/`](schematics/)*