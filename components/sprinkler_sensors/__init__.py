import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, text_sensor, sprinkler
from esphome.const import UNIT_PERCENT, UNIT_SECOND, CONF_ID

AUTO_LOAD = ["sensor", "text_sensor"]
DEPENDENCIES = ["sprinkler"]

CONF_SPRINKLER_ID = "sprinkler_id"
CONF_ACTIVE_VALVE = "active_valve"
CONF_TIME_REMAINING = "time_remaining"
CONF_PROGRESS = "progress"
CONF_SECTION_NAME = "section_name"

sprinkler_sensors_ns = cg.esphome_ns.namespace("sprinkler_sensors")
SprinklerSensorsComponent = sprinkler_sensors_ns.class_(
    "SprinklerSensorsComponent", cg.PollingComponent
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SprinklerSensorsComponent),
        cv.Required(CONF_SPRINKLER_ID): cv.use_id(sprinkler.Sprinkler),
        cv.Optional(CONF_ACTIVE_VALVE): text_sensor.text_sensor_schema(),
        cv.Optional(CONF_TIME_REMAINING): sensor.sensor_schema(
            unit_of_measurement=UNIT_SECOND, accuracy_decimals=0
        ),
        cv.Optional(CONF_PROGRESS): sensor.sensor_schema(
            unit_of_measurement=UNIT_PERCENT, accuracy_decimals=0
        ),
        cv.Optional(CONF_SECTION_NAME): text_sensor.text_sensor_schema(),
    }
).extend(cv.polling_component_schema("1s"))

NUMERIC = {
    CONF_TIME_REMAINING: "set_time_remaining_sensor",
    CONF_PROGRESS: "set_progress_sensor",
}

TEXT = {
    CONF_ACTIVE_VALVE: "set_active_valve_sensor",
    CONF_SECTION_NAME: "set_section_name_sensor",
}


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    spr = await cg.get_variable(config[CONF_SPRINKLER_ID])
    cg.add(var.set_sprinkler(spr))

    for key, setter in NUMERIC.items():
        if key in config:
            s = await sensor.new_sensor(config[key])
            cg.add(getattr(var, setter)(s))

    for key, setter in TEXT.items():
        if key in config:
            ts = await text_sensor.new_text_sensor(config[key])
            cg.add(getattr(var, setter)(ts))
