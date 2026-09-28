import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

from .schema import (
    sprinkler_sensors_schema,
    CONF_ACTIVE_VALVE,
    CONF_TIME_REMAINING,
    CONF_PROGRESS,
    CONF_SECTION_NAME,
)

sprinkler_ns = cg.esphome_ns.namespace("sprinkler_sensors")
SprinklerSensorsComponent = sprinkler_ns.class_("SprinklerSensorsComponent", cg.Component)

# *** KLUCZOWE: powiązanie SCHEMATU z platformą ***
CONFIG_SCHEMA = sprinkler_sensors_schema

# *** KLUCZOWE: rejestracja platformy sensorowej ***
sensor.register_sensor_platform("sprinkler_sensors", CONFIG_SCHEMA)

def to_code(config):
    comp = cg.new_Pvariable(config[CONF_ID])
    cg.add(comp.set_sprinkler_id(cg.get_variable("garden_ctrl")))

    if CONF_ACTIVE_VALVE in config:
        sens = yield sensor.new_sensor(config[CONF_ACTIVE_VALVE])
        cg.add(comp.set_active_valve_sensor(sens))

    if CONF_TIME_REMAINING in config:
        sens = yield sensor.new_sensor(config[CONF_TIME_REMAINING])
        cg.add(comp.set_time_remaining_sensor(sens))

    if CONF_PROGRESS in config:
        sens = yield sensor.new_sensor(config[CONF_PROGRESS])
        cg.add(comp.set_progress_sensor(sens))

    if CONF_SECTION_NAME in config:
        sens = yield sensor.new_sensor(config[CONF_SECTION_NAME])
        cg.add(comp.set_section_name_sensor(sens))

    cg.add(comp.setup())
