import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import sensor

CONF_ACTIVE_VALVE = "active_valve"
CONF_TIME_REMAINING = "time_remaining"
CONF_PROGRESS = "progress"
CONF_SECTION_NAME = "section_name"

sprinkler_sensors_schema = cv.Schema({
    cv.GenerateID(): cv.declare_id(sensor.Sensor),
    cv.Optional(CONF_ACTIVE_VALVE): sensor.sensor_schema(),
    cv.Optional(CONF_TIME_REMAINING): sensor.sensor_schema(),
    cv.Optional(CONF_PROGRESS): sensor.sensor_schema(),
    cv.Optional(CONF_SECTION_NAME): sensor.sensor_schema(),
})
