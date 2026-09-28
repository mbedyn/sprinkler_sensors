#include "sprinkler_sensors.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sprinkler_sensors {

static const char *const TAG = "sprinkler_sensors";

void SprinklerSensorsComponent::update() {
  if (this->sprinkler_ == nullptr)
    return;

  auto active = this->sprinkler_->active_valve();
  auto remaining = this->sprinkler_->time_remaining_active_valve();

  if (this->active_valve_sensor_ != nullptr)
    this->active_valve_sensor_->publish_state(active.has_value() ? (float) *active : NAN);

  if (this->time_remaining_sensor_ != nullptr)
    this->time_remaining_sensor_->publish_state(remaining.has_value() ? (float) *remaining : NAN);

  if (this->progress_sensor_ != nullptr) {
    float progress = NAN;
    if (active.has_value() && remaining.has_value()) {
      uint32_t total = this->sprinkler_->valve_run_duration_adjusted(*active);
      if (total > 0) {
        float p = 100.0f * (1.0f - (float) *remaining / (float) total);
        progress = p < 0.0f ? 0.0f : (p > 100.0f ? 100.0f : p);
      }
    }
    this->progress_sensor_->publish_state(progress);
  }

  if (this->section_name_sensor_ != nullptr)
    this->section_name_sensor_->publish_state(
        active.has_value() ? this->sprinkler_->valve_name(*active) : "");
}

void SprinklerSensorsComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Sprinkler Sensors");
  LOG_UPDATE_INTERVAL(this);
  LOG_SENSOR("  ", "Active valve", this->active_valve_sensor_);
  LOG_SENSOR("  ", "Time remaining", this->time_remaining_sensor_);
  LOG_SENSOR("  ", "Progress", this->progress_sensor_);
  LOG_TEXT_SENSOR("  ", "Section name", this->section_name_sensor_);
}

}  // namespace sprinkler_sensors
}  // namespace esphome
