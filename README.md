# Sprinkler Sensors – External Component for ESPHome

**Sprinkler Sensors** is an external ESPHome component that exposes additional
sensor data from the built‑in `sprinkler:` controller:

- Active valve index  
- Time remaining for the active valve  
- Section progress (%)  
- Section name  

This component works on **all ESPHome-supported platforms**, including  
**ESP32‑C6 / ESP-IDF**, where YAML `template:` and `custom_component:` are not available.

---

## ✨ Features

- ✔ Reads real-time data directly from ESPHome Sprinkler Controller  
- ✔ Works on ESP-IDF (ESP32‑C6, ESP32‑C3, ESP32‑H2)  
- ✔ Provides 4 sensors:
  - `active_valve`
  - `time_remaining`
  - `progress`
  - `section_name`
- ✔ Zero YAML hacks — full CONFIG_SCHEMA support  
- ✔ Clean integration with Home Assistant  
- ✔ Lightweight and fast (updates every loop)

---

## 📦 Installation

Add this repository as an external component in your ESPHome YAML:

```yaml
external_components:
  - source: github://mbedyn/sprinkler_sensors
    refresh: 60s
