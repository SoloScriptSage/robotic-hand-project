# Flex Sensor Calibration Guide

Each flex sensor behaves slightly differently depending on its physical properties and how it is mounted on the glove. This guide walks you through measuring the real min/max values for each finger and updating the firmware accordingly.

---

## What You Need

- Transmitter Arduino (glove side)
- USB cable connected to your PC
- Arduino IDE with Serial Monitor
- `test_sensors.ino` flashed to the transmitter Arduino

---

## Step 1 — Flash the Test Sketch

Open `firmware/test_sensors/test_sensors.ino` in Arduino IDE and upload it to the **transmitter Arduino** (glove side).

---

## Step 2 — Open Serial Monitor

In Arduino IDE go to **Tools → Serial Monitor** and set the baud rate to **9600**.

You should see output like this every 500ms:
```
F1: 537    F2: 540    F3: 533    F4: 538    F5: 535
```

---

## Step 3 — Record Flat Values (FLEX_MIN)

Hold your hand **completely flat and relaxed** — do not bend any fingers.

Wait a few seconds for the readings to stabilize, then record the value for each finger:

| Finger | Pin | Flat Value (your reading) |
|---|---|---|
| F1 (thumb) | A1 | |
| F2 (index) | A2 | |
| F3 (middle) | A3 | |
| F4 (ring) | A4 | |
| F5 (pinky) | A5 | |

---

## Step 4 — Record Bent Values (FLEX_MAX)

Curl each finger **fully** into a fist, one at a time, while watching the Serial Monitor.

Record the maximum value reached for each finger:

| Finger | Pin | Bent Value (your reading) |
|---|---|---|
| F1 (thumb) | A1 | |
| F2 (index) | A2 | |
| F3 (middle) | A3 | |
| F4 (ring) | A4 | |
| F5 (pinky) | A5 | |

---

## Step 5 — Update the Firmware

Open `firmware/transmitter/transmitter.ino` and update `FLEX_MIN` and `FLEX_MAX` with your recorded values:

```cpp
// Replace these with your actual measured values
const int FLEX_MIN[5] = {537, 540, 533, 538, 535}; // flat
const int FLEX_MAX[5] = {680, 695, 672, 688, 710}; // fully bent
```

The order is: `{F1, F2, F3, F4, F5}` → `{thumb, index, middle, ring, pinky}`

---

## Step 6 — Verify

Flash the updated `transmitter.ino` and open Serial Monitor again. Now the output should show values between **1 and 180** instead of raw ADC values:

```
Sensors: 1    1    1    1    1       ← hand flat
Sensors: 180  175  170  180  168     ← fist
```

If a finger reads 180 even when flat, or 1 even when fully bent — swap the min and max values for that finger.

---

## Tips

- Redo calibration if you remount the sensors on the glove
- If readings are noisy, add a small capacitor (10–100nF) between the sensor pin and GND
- `constrain()` in the code will clamp any out-of-range values so the servos won't go past their limits
