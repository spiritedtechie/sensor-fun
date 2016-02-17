A sensor device is a remote in-field device which is responsible for capture of raw(ish) sensor data from one or more sensors and forwarding the data to the sensor hub via Bluetooth LE.

The sensor device here is implemented using a Genuino 101 board with one or more sensors attached to the IO pins, and an Arduino C++ program to read the IO for publishing data via Bluetooth LE to the sensor hub.

Hardware
--------
- Arduino / Genuino 101
- USB cable type A/B
- Breadboard + wiring
- Basic Temperature-humidity Sensor (DHT11)
- Barometric Pressure/Temperature/Altitude Sensor (BMP180)
- Digital Temperature Sensor (DS18B20)
- (Optional) I2C LCD1602 module

I recommend the Sun Founder Sensor Kit V2 as the sensors are pre-manufactured with appropriate resistors etc. so you can just plug and play!

Exception for debugging, avoid using the LCD to reduce power usage.

Arduino IDE Setup
-----------------
1. Install Arduino IDE 1.6.7+
2. Install 'Intel Curie Boards' via Boards Manager
3. Ensure 'Arduino 101' board is selected
4. Install the following libraries (via Manage Libraries):
  - OneWire
  - ArduinoJson by Benoit Blanchon
  - LiquidCrystal_I2C by Marco Schwartz
  - DallasTemperature
  - Adafruit BMP085 Library by Adafruit
  - DHT sensor library by Adafruit
5. Open the **monolith-sensor-device.ino** file from the IDE

Arduino Board Setup
-------------------
1) Connect Arduino to computer via USB

2) Wire up Analog I2C sensors:
```
I2C LCD1602 -> Genuino 101
GND -> GND
VCC -> 5V
SDA -> A4
SCL -> A5
```
```
BMP180 -> Genuino 101
GND -> GND
VCC -> 5V
SDA -> A4
SCL -> A5
```
You can add multiple I2C devices to same I2C bus provided they each use a different address (which they do in this project)

3) Wire up Digital sensors:
```
DHT11 -> Genuino 101
GND -> GND
VCC -> 5V
SIG -> 8
```
```
DHT11 -> Genuino 101
GND -> GND
VCC -> 5V
SIG -> 7
```

###### Monolithic Device
The following photos show a monolithic device with all sensors attached via a breadboard.
- The orange wires from/to the Arduino are used for the digital sensors
- The blue wires from/to the Arduino are used for the analog I2C bus
- The brown and white wires are the I2C slaves connected to the I2C bus
- The yellow wires are the digital sensors attached to the digital IO pins

![Top View](https://raw.githubusercontent.com/spiritedtechie/sensor-fun/master/sensor-devices/images/top-view.jpg)
![Side View 1](https://raw.githubusercontent.com/spiritedtechie/sensor-fun/master/sensor-devices/images/side-view-1.jpg)
![Side View 2](https://raw.githubusercontent.com/spiritedtechie/sensor-fun/master/sensor-devices/images/side-view-2.jpg)

Program Upload
--------------
Once the IDE and the Arduino board are setup.

1. Connect Arduino to computer using USB A/B cable
2. Upload sketch from Arduino IDE

Resources
---------
######Bluetooth LE Concepts
* https://learn.adafruit.com/downloads/pdf/introduction-to-bluetooth-low-energy.pdf

######Arduino Bluetooth LE
* https://github.com/01org/corelibs-arduino101/tree/master/libraries/CurieBle
* https://www.arduino.cc/en/Tutorial/Genuino101CurieBLEHeartRateMonitor
* https://github.com/bneedhamia/DHTBLESensor

######Arduino Sensors
* http://www.sunfounder.com/index.php?c=case_incs&a=detail_&id=321&name=Sensor%20Kit%20for%20Arduino%20V2.0
* http://www.sunfounder.com/index.php?c=case_incs&a=detail_&id=329&name=Sensor%20Kit%20for%20Arduino%20V2.0
* http://www.sunfounder.com/index.php?c=case_incs&a=detail_&id=333&name=Sensor%20Kit%20for%20Arduino%20V2.0
* http://www.sunfounder.com/index.php?c=case_incs&a=detail_&id=345&name=Sensor%20Kit%20for%20Arduino%20V2.0
