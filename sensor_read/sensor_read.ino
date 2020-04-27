//Author: Thomas Lloyd

# include <Arduino_HTS221.h>
#include <ArduinoBLE.h>
#include <Wire.h>

BLEService environmentService("1101");
BLEUnsignedCharCharacteristic environmentDetailsChar("2101", BLERead | BLENotify);

void setup() {
  Serial.begin(9600);
  HTS.begin();

  //BLE
  //--------------------------------------
  while (!Serial);
  pinMode(LED_BUILTIN, OUTPUT);
  
  if (!BLE.begin()) {
  Serial.println("starting BLE failed!");
  while (1);
  }
  
  BLE.setLocalName("environment details");
  BLE.setAdvertisedService(environmentService);
  environmentService.addCharacteristic(environmentDetailsChar);
  BLE.addService(environmentService);
  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections..."); 
  //--------------------------------------

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    Serial.println("Trying again!");
    while (1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // read temp and humidity
  float temp_humid_array[2];
  temp_humid_array[0] = HTS.readTemperature();
  temp_humid_array[1] = HTS.readHumidity();

  Serial.print("temperature: ");
  Serial.print(temp_humid_array[0]);
  Serial.print(", humidity: ");
  Serial.println(temp_humid_array[1]);


  BLEDevice central = BLE.central();

  if (central) {
  Serial.print("Connected to central: ");
  Serial.println(central.address());
  digitalWrite(LED_BUILTIN, HIGH);

  while (central.connected()) {
        // read temp and humidity
        float temp_humid_array[2];
        temp_humid_array[0] = HTS.readTemperature();
        temp_humid_array[1] = HTS.readHumidity();

        Serial.print("temperature: ");
        Serial.print(temp_humid_array[0]);
        Serial.print(", humidity: ");
        Serial.println(temp_humid_array[1]);
        
        String environmentDetails = String("temperature: " + String(temp_humid_array[0]) + ", humidity: " + String(temp_humid_array[1]));
        int temp = int(temp_humid_array[0]);
        Serial.print("Bluetooth package prepared: ");
        Serial.println(environmentDetails);
        environmentDetailsChar.writeValue(temp);
        delay(200);
    }
  }
  
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
  delay(1000);
  
}
