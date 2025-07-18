**THIS IS NOT A COMPLETE PROJECT WORK IN PROGRESS**

# Wireless Soil Monitoring System (NPK + Moisture + Temperature)

A low-cost, wireless soil health monitoring solution that measures key environmental parameters—**Soil Moisture**, **NPK (Nitrogen, Phosphorous, Potassium)**, and **Temperature**—and sends the data to **ThingSpeak** via **ESP32** using **NRF24L01** wireless communication.

---

## System Overview

This project is designed to support **precision agriculture** and **remote soil monitoring** by wirelessly transmitting sensor data from a field-deployed node (transmitter) to a cloud-connected gateway (receiver) for real-time visualization and logging.

---

## Features

* Wireless communication using **nRF24L01** modules
* Measures:

  * Soil Moisture (Analog Sensor)
  * Soil Nutrients (NPK) via RS485 Modbus
  * Temperature using DS18B20 sensor
* Data is:

  * **Transmitted wirelessly** from Arduino to ESP32
  * **Logged to ThingSpeak** for historical tracking and analysis
* Compact and deployable in field conditions

---

## Hardware Requirements

### Transmitter (Arduino)

| Component            | Description                            |
| -------------------- | -------------------------------------- |
| Arduino UNO/Nano     | Main controller                        |
| nRF24L01 Module      | Wireless transmitter                   |
| Soil Moisture Sensor | Analog-based sensor                    |
| DS18B20 Sensor       | 1-wire digital temperature sensor      |
| NPK Sensor (Modbus)  | Reads nitrogen, phosphorous, potassium |
| RS485 to TTL Module  | Interface for NPK sensor               |

### Receiver (ESP32)

| Component          | Description                |
| ------------------ | -------------------------- |
| ESP32 Wi-Fi Module | Cloud gateway              |
| nRF24L01 Module    | Wireless receiver          |
| ThingSpeak Account | For IoT cloud data logging |

---

## Pin Configuration

### Transmitter (Arduino)

| Pin     | Function                   |
| ------- | -------------------------- |
| D9, D10 | CE and CSN (nRF24L01)      |
| D2, D3  | SoftwareSerial for RS485   |
| D5      | DS18B20 Temperature Sensor |
| A0      | Soil Moisture Sensor       |
| D7, D8  | DE and RE for RS485        |

### Receiver (ESP32)

| Pin      | Function              |
| -------- | --------------------- |
| GPIO4, 5 | CE and CSN (nRF24L01) |

---

## Data Packet Structure

Data is transmitted using a packed struct:

```cpp
struct MyVariable {
  byte soilmoisturepercent;
  byte nitrogen;
  byte phosphorous;
  byte potassium;
  byte temperature;
};
```

---

## Setup Instructions

### 1. Arduino Transmitter

* Upload the Arduino code to UNO/Nano
* Connect all sensors as per pin configuration
* Tune the soil moisture sensor’s `AirValue` and `WaterValue` for calibration
* Ensure RS485 Modbus sensor returns valid NPK data
* Power the board and confirm serial output

### 2. ESP32 Receiver

* Update the following in the ESP32 code:

  ```cpp
  const char* ssid = "YOUR_WIFI_SSID";
  const char* password = "YOUR_WIFI_PASSWORD";
  String apiKey = "YOUR_THINGSPEAK_API_KEY";
  ```
* Flash the code onto ESP32
* Check ThingSpeak for updates under your channel fields

---

## Serial Monitor Output

Transmitter:

```
Soil Moisture: 63%
Nitrogen: 20 mg/kg
Phosphorous: 18 mg/kg
Potassium: 25 mg/kg
Temperature: 29°C
Data Packet Sent
```

Receiver:

```
Receiver Started....
WiFi connected
Data Received:
Soil Moisture: 63%
Nitrogen: 20 mg/kg
Phosphorous: 18 mg/kg
Potassium: 25 mg/kg
Temperature: 29°C
Data Sent to Server
```

---

## Cloud Logging

The ESP32 uploads sensor data to **ThingSpeak** using the official REST API. The following fields are mapped:

| ThingSpeak Field | Sensor Value        |
| ---------------- | ------------------- |
| Field1           | Soil Moisture (%)   |
| Field2           | Nitrogen (mg/kg)    |
| Field3           | Phosphorous (mg/kg) |
| Field4           | Potassium (mg/kg)   |
| Field5           | Temperature (°C)    |

---

## Applications

* Precision farming
* Remote soil health diagnostics
* Smart agriculture projects
* Research and academic applications

---

## Author

**Sourashis Das**
IoT and Embedded Systems Developer

