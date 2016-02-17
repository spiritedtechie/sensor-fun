# sensor-fun
Pet project to capture, consume, store and analyse data from Arduino sensors.

The architecture consists of three key components:

1. sensor-devices - Colocated sensors + IO to capture raw data. Sensors can be colocated on a single device (monolith), or split out across multiple devices.
2. sensor-hub - Central hub used in the field to aggregate sensor data from multiple devices and route onwards.
3. backend - Scaled compute, storage and analytics system for the sensor data.

For this project we are using a single monolith sensor device with all three sensors attached and an LCD to display data:

1. Digital temperature
2. Digital humidity
3. Analog barometer for pressure
