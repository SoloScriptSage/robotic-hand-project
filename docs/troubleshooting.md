# Troubleshooting Guide

Common issues and fixes for the robotic hand project.

---

## 🤚 Hand Not Moving At All

**1. Check the radio connection first**

Open Serial Monitor on the receiver Arduino. If you see nothing printed, the radio is not receiving.

- Make sure both NRF24L01 modules are powered from **3.3V not 5V**
- Add a 100µF capacitor across the VCC and GND pins of each NRF24L01 — power instability is the most common cause of radio failure
- Confirm both modules are on the same channel (`0x60`) and same data rate (`RF24_250KBPS`)
- Try swapping the transmitter and receiver modules — one may be faulty

**2. Check the servo power**

Servos must be powered from the battery directly, not from the Arduino 5V pin. Five MG996R servos under load will draw more current than the Arduino can supply and will cause resets or no movement.

---

## 📡 Intermittent or Dropped Connection

- Add the 100µF capacitor across NRF24L01 power pins if not already done
- Keep the modules away from motors and power wires — interference is common
- Try `radio.setPALevel(RF24_PA_LOW)` at short range — max power can cause reflections indoors
- Make sure antennas on both modules are not obstructed or touching metal

---

## 🖐️ Fingers Move in Wrong Direction

The `map()` function in `transmitter.ino` maps flat→bent to 1→180. If a finger moves backwards, swap the min and max for that finger:

```cpp
// Before (backwards)
const int FLEX_MIN[5] = {535, 535, 535, 535, 535};
const int FLEX_MAX[5] = {680, 680, 680, 680, 710};

// After (swap values for the affected finger, e.g. F2)
const int FLEX_MIN[5] = {535, 680, 535, 535, 535};
const int FLEX_MAX[5] = {680, 535, 680, 680, 710};
```

---

## 🤖 Servos Jitter or Stutter

- Power the servos from the battery with a common GND shared with the Arduino
- Add a 100µF capacitor across each servo's power pins
- Increase the `constrain()` range slightly if values are bouncing near the edges
- Check for loose connections on servo signal wires

---

## 📊 Sensor Readings Are Noisy

- Add a 10–100nF ceramic capacitor between each flex sensor analog pin and GND
- Slow down the `analogRead()` sampling — add a small `delay(10)` between reads
- Make sure the 10kΩ pull-down resistors are properly connected

---

## 🔢 Sensor Values Don't Change When Bending

- Check the voltage divider wiring — the flex sensor and 10kΩ resistor must form a divider between 5V and GND
- Measure voltage across the sensor with a multimeter while bending — it should change
- The sensor itself may be broken — test resistance with a multimeter (should change from ~10kΩ flat to ~40kΩ bent)

---

## 💻 Upload Fails in Arduino IDE

- Make sure the correct board and COM port are selected under **Tools**
- Only one Serial Monitor can be open at a time — close it before uploading
- If using Arduino Mega, CE and CSN pins may differ — check your wiring against the schematic

---

## 🔋 Arduino Keeps Resetting

- Servos are drawing too much current from Arduino 5V — power them directly from the battery
- Check for short circuits in wiring
- Make sure GND is shared between Arduino and battery

---

## Still Stuck?

1. Flash `firmware/test_sensors/test_sensors.ino` and verify flex sensors respond in Serial Monitor
2. Flash `firmware/servo_test/servo_test.ino` and verify all servos sweep correctly
3. If both work independently but not together, the issue is in the radio link
