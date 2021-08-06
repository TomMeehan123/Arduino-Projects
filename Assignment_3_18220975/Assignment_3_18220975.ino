/**
   Name: Tom Meehan
   ID: 18220975
   Module: Sensors and Actuators
   Module Code: ET4224
   Lecturer: Bob Strunz
   Purpose: To measure the temperature using an I2C Sensor
   - The program uses a TC74A5 temperature sensor.
   - The temperature will be taken every 15 minutes over a 24 hour period.
   - The results will then be stored on an SD card as a txt file.
   - To use the SD card an SD module must be connected to the Arduino.
   - SPI communication is used to transfer the data from the Ardunio to the SD card.
*/
#include <SPI.h> // Includes the SPI library to communicate with the SD module
#include <SD.h> // Includes the SD library
#include <Wire.h> //  Includes the Wire library for I2C
#define SD_Card 10 // Defines the SD card pin as 10
File tempRecord; // Creates a variable called tempRecord for storing the temperatures
int address = 77; // Decimal address of the temperature Sensor taken from data sheet
long Hour = 3600000; //  defines 1 hour in milliseconds

void setup() {
  Serial.begin(9600); // Set the Baud rate
  Wire.begin(); // Create a wire object
  
  Serial.print("Searching for SD Card....");
  // If the sd card is not at pin 10
  if (!SD.begin(SD_Card)) {
    Serial.println("SD Card Could Not Be Found!!!");
    while (1);
  }
  Serial.println("SD Card Found!!!");
  // if the file exists
  if(SD.exists("temp.txt")){
  // Remove the existing file
  SD.remove("temp.txt");
  }
  // Open the file test.txt in the sd card
  tempRecord = SD.open("temp.txt", FILE_WRITE);
  // if the file opens print the following the the SD card and to the serial monitor
  if (tempRecord) {
    Serial.println("Recording Temperatures...");
    Serial.println("Sensor: TC74A5");
    Serial.println("Min Temp Degree C: -65C");
    Serial.println("Max Temp Degree C: = 130C");
    Serial.println("The Temperature Will Be Displayed Every 15 Minutes");

    tempRecord.println("Recording Temperatures...");
    tempRecord.println("Sensor: TC74A5");
    tempRecord.println("Min Temp Degree C: -65C");
    tempRecord.println("Max Temp Degree C: = 130C");
    tempRecord.println("The Temperature Will Be Displayed Every 15 Minutes");
    // Close the file
    tempRecord.close();
  } else {
    // the file could not open
    Serial.println("File could not Open!!!");
  }
}
void loop() {
 // open the file again in the sd card
  tempRecord = SD.open("temp.txt", FILE_WRITE);
  // if the file opens
  if(tempRecord){
    // if the total time is less that 24 hours
    if (millis()<24*Hour){
      int degC = readTemp(address); // Reads temperature in celsius
      float degF = (degC * (9 / 5)) + 32; // Converts temperature to fahrenheit
      float degK = degC + 273.15; // Converts temperature to kelvin
      // The following will be printed to the serial monitor
      Serial.println("----------------------------------");
      Serial.print("Temperature: ");
      Serial.print(degC);
      Serial.print("C | ");
      Serial.print(degF);
      Serial.print("F | ");
      Serial.print(degK);
      Serial.print("K | ");
      Serial.println("");
      
      // the following will be printed to the txt file
      tempRecord.println("----------------------------------");
      tempRecord.print("Temperature: ");
      tempRecord.print(degC);
      tempRecord.print("C | ");
      tempRecord.print(degF);
      tempRecord.print("F | ");
      tempRecord.print(degK);
      tempRecord.print("K | ");
      tempRecord.println("");

      tempRecord.close(); // close the txt file
      }
      else{
        // else time is greater than 24 hours, do nothing
        }
    }
      delay(900000); // Wait 15 minutes
}

int readTemp(int address) {
  // Starts communication with IC with the address xx
  Wire.beginTransmission(address);
  // Send a bit and ask for the register at 0
  Wire.write(0);
  // End transmission
  Wire.endTransmission();
  // Request 1 byte from an address location
  Wire.requestFrom(address, 1);
  // Determine if the wire is available
  while (Wire.available() == 0);
  // Read the temperature
  int temp = Wire.read();
  //
  return temp;
}
