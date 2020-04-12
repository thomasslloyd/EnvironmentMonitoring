# include <Arduino_HTS221.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600)
  HTS.begin()
  float temperature
  float humdity
  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    Serial.println("Trying again!");
    while(1)
  }

}

float HTSRead(float temperature float humidity) {
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");
  return temperature, humidity 
}




void endGTS() {
  HTS.end()
}
