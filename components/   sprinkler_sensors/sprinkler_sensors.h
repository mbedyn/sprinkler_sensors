#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/sprinkler/sprinkler.h"

namespace esphome {
namespace sprinkler_sensors {

class SprinklerSensorsComponent : public PollingComponent {
 public:
  void set_sprinkler(sprinkler::Sprinkler *s) { this->sprinkler_ = s; }
  void set_active_valve_sensor(sensor::Sensor *s) { this->active_valve_sensor_ = s; }
  void set_time_remaining_sensor(sensor::Sensor *s) { this->time_remaining_sensor_ = s; }
  void set_progress_sensor(sensor::Sensor *s) { this->progress_sensor_ = s; }
  void set_section_name_sensor(text_sensor::TextSensor *s) { this->section_name_sensor_ = s; }

  void update() override;
  void dump_config() override;

 protected:
  sprinkler::Sprinkler *sprinkler_{nullptr};
  sensor::Sensor *active_valve_sensor_{nullptr};
  sensor::Sensor *time_remaining_sensor_{nullptr};
  sensor::Sensor *progress_sensor_{nullptr};
  text_sensor::TextSensor *section_name_sensor_{nullptr};
};

}  // namespace sprinkler_sensors
}  // namespace esphome
