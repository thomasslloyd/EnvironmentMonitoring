//Author: Thomas Lloyd


# include <Arduino_HTS221.h>
# include <WStream.h>

void setup() {
  Serial.begin(9600)
  HTS.begin()

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    Serial.println("Trying again!");
    while(1);
  }
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  temperature, humidity = HTSRead(float temperature float humidity)
  
}

float HTSRead() {

  float temperature = HTS.readTemperature();
  float humidity    = HTS.readHumidity();
  
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(temperature);
  Serial.println(" %");

  // print an empty line
  Serial.println();

  // wait 1 second to print again
  delay(1000);
  
  return temperature, humidity 
}


void endGTS() {
  HTS.end();
}
