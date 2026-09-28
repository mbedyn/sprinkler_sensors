#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/sprinkler/sprinkler.h"

namespace esphome {
namespace sprinkler_sensors {

class SprinklerSensorsComponent : public Component {
 public:
  void set_sprinkler_id(sprinkler::Sprinkler *sprinkler) { this->sprinkler_ = sprinkler; }
  void set_active_valve_sensor(sensor::Sensor *s) { this->active_valve_sensor_ = s; }
  void set_time_remaining_sensor(sensor::Sensor *s) { this->time_remaining_sensor_ = s; }
  void set_progress_sensor(sensor::Sensor *s) { this->progress_sensor_ = s; }
  void set_section_name_sensor(sensor::Sensor *s) { this->section_name_sensor_ = s; }

  void setup() override {}
  void loop() override;

 protected:
  sprinkler::Sprinkler *sprinkler_;
  sensor::Sensor *active_valve_sensor_{nullptr};
  sensor::Sensor *time_remaining_sensor_{nullptr};
  sensor::Sensor *progress_sensor_{nullptr};
  sensor::Sensor *section_name_sensor_{nullptr};
};

}  // namespace sprinkler_sensors
}  // namespace esphome
