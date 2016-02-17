# Monolith sensor device with all sensors on one board / location

#include <OneWire.h>
#include <CurieBle.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>

#define ONE_WIRE_BUS 7
#define LED_PIN 13
const char *BLE_LOCAL_NAME = "EnvironmentSensors";

// Bluetooth LE
BLEPeripheral blePeripheral;
BLEService environmentalService("181A");
BLEDoubleCharacteristic humidityChar("2A6F", BLERead | BLENotify);
BLEDoubleCharacteristic temperatureChar("2A6E", BLERead | BLENotify);
BLEDoubleCharacteristic pressureChar("2A6D", BLERead | BLENotify);
boolean centralConnected = false;

// LCD
// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Digital temperature
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Barometer BMP sensor
Adafruit_BMP085 bmp;

// Humidity DHT11
#define DHT_PIN 8
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  // Bluetooth LE init
  blePeripheral.setLocalName(BLE_LOCAL_NAME);
  blePeripheral.setAdvertisedServiceUuid(environmentalService.uuid());
  blePeripheral.addAttribute(environmentalService);
  blePeripheral.addAttribute(temperatureChar);
  blePeripheral.addAttribute(humidityChar);
  blePeripheral.addAttribute(pressureChar);

  blePeripheral.begin();

  // LCD init
  lcd.init();
  lcd.backlight();

  // Digital temp sensor init
  sensors.begin();

  // Barometer BMP init
  if (!bmp.begin()) {
    Serial.println("BMP180 init fail\n\n");
    while (1); // Pause forever.
  }

  // Humidity DHT11 init
  pinMode(DHT_PIN, INPUT);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  // BLUETOOTH LE
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();
  if (central && central.connected()) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_PIN, HIGH);
    centralConnected = true;
  } else {
    Serial.println("Not connected to central");
    digitalWrite(LED_PIN, LOW);
    centralConnected = false;
  }

  // TEMPERATURE
  sensors.requestTemperatures();
  double temp = sensors.getTempCByIndex(0);
  printTemperatureOnLcd(temp);

  // PRESSURE
  double press = bmp.readPressure();
  printPressureOnLcd(press);

  // HUMIDITY
  float hum = dht.readHumidity();

  // PUBLISH
  String json = buildJson(temp, press, hum);
  publishDataToSerial(json);

  publishDataToBLE(temp, press, hum);

  delay(2000);
}

void printTemperatureOnLcd(double temp) {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 2);
  lcd.print(" *C");
}

void printPressureOnLcd(double pressure) {
  lcd.setCursor(0, 1);
  lcd.print("Pres: ");
  lcd.print(pressure, 0);
  lcd.print(" Pa");
}

void publishDataToSerial(String data) {
  Serial.println(data);
}

void publishDataToBLE(double temp, double press, float hum) {

  if (centralConnected) {
    temperatureChar.setValue(temp);
    pressureChar.setValue(press);
    humidityChar.setValue(hum);
  } else {
    Serial.println("Bluetooth not connected, cannot publish data via BLE");
  }
}

String buildJson(double temp, double pressure, float hum) {
  StaticJsonBuffer<100> jsonBuffer;
  String json;

  JsonObject& root = jsonBuffer.createObject();
  root["temp"] = temp;
  root["press"] = pressure;
  root["humidity"] = hum;
  root.printTo(json);

  return json;
}
