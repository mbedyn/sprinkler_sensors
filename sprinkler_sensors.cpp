#include "sprinkler_sensors.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sprinkler_sensors {

static const char *TAG = "sprinkler_sensors";

void SprinklerSensorsComponent::loop() {
  if (!this->sprinkler_) return;

  auto active = this->sprinkler_->active_valve();
  auto remain = this->sprinkler_->time_remaining_active_valve();

  if (active.has_value() && this->active_valve_sensor_) {
    this->active_valve_sensor_->publish_state(active.value());
  }

  if (remain.has_value() && this->time_remaining_sensor_) {
    this->time_remaining_sensor_->publish_state(remain.value());
  }

  if (active.has_value() && remain.has_value() && this->progress_sensor_) {
    int total = this->sprinkler_->valves()[active.value()].run_duration();
    int elapsed = total - remain.value();
    float pct = (float)elapsed / (float)total * 100.0f;
    this->progress_sensor_->publish_state(pct);
  }

  if (active.has_value() && this->section_name_sensor_) {
    int idx = active.value();
    std::string name = this->sprinkler_->valves()[idx].get_name();
    this->section_name_sensor_->publish_state(name);
  }
}

}  // namespace sprinkler_sensors
}  // namespace esphome
