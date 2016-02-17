# sensor-fun
Pet project to capture, consume, store and analyse data from sensors.

The architecture consists of three key components:

1. **sensor-device** - Colocated sensors + IO board to capture raw data. Sensors can be colocated on a single device (monolith), or split out across multiple devices.
2. **sensor-hub** - Central hub used in the field to aggregate sensor data from multiple devices, process and route onwards to the backend.
3. **backend** - Scaled compute, storage and analytics system for the sensor data.

For this project, we are using a single monolithic sensor device with all sensors and an LCD attached to a one IO board.
