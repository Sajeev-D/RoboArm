<<<<<<< HEAD
//libraries

#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include <Servo.h>

//constants relating to our adafruit board (these were found online)

#define BUFSIZE                        128
#define VERBOSE_MODE                   true

#define BLUEFRUIT_SWUART_RXD_PIN       9
#define BLUEFRUIT_SWUART_TXD_PIN       10
#define BLUEFRUIT_UART_CTS_PIN         11
#define BLUEFRUIT_UART_RTS_PIN         8

#ifdef Serial1
  #define BLUEFRUIT_HWSERIAL_NAME      Serial1
#endif

#define BLUEFRUIT_UART_MODE_PIN        12

#define BLUEFRUIT_SPI_CS               8
#define BLUEFRUIT_SPI_IRQ              7
#define BLUEFRUIT_SPI_RST              4

#define BLUEFRUIT_SPI_SCK              13
#define BLUEFRUIT_SPI_MISO             12
#define BLUEFRUIT_SPI_MOSI             11


// Constant for the servo pin
#define SERVO_PIN 9

//Define the objects which are the bluetooth module and the servo

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
Servo myServo;

// A function that prints the error
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

void setup(void)
{
  //attach the servo to pin 9
  myServo.attach(SERVO_PIN);

//check to see if a serial communication was established
  while (!Serial);
  delay(500);

  Serial.begin(115200);

  // Initialise the bluetooth module
  if ( !ble.begin(VERBOSE_MODE) ) {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }

  // Perform a factory reset to make sure everything is in a known state
  //the ble.factoryReset function is carried out and returns a bool if successful
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }

  //Disable command echo from Bluefruit so commands aren't sent back for confirmation
  ble.echo(false);

  //ble.info() can be used to get info about the bluefruit module

 // prevents module from sending extensive debug info
  ble.verbose(false);  
  
  //Wait for connection
  while (! ble.isConnected()) {
      delay(500);
  }


  // Set module to DATA mode
  ble.setMode(BLUEFRUIT_MODE_DATA);
}

void loop(void){

  while ( ble.available() )
  {
    int value = readIntValue();
    Serial.println(value);
    rotateServo(value);
  }
}

// Custom function to read a controller inputs, returns 1,2,3,4 corresponding with up, down, left, right 
int readDirValue(){
  int dirVal;
  char c;

  
}

// Custom function to read an integer value between 0 and 180 from the received data
int readIntValue() {
  int intValue = 0;
  char c;

  // Read characters until a non-digit character is encountered or the integer value exceeds 180
  while (ble.available()) {
    c = ble.read();

    // Ignore the 'enter' (newline) character
    if (c == '\n' || c == '\r') {
      continue;
    }

    if (isdigit(c)) {
      intValue = intValue * 10 + (c - '0');
      if (intValue > 180) {
        break;
      }
    } else {
      break;
    }
  }

  // If the integer value is greater than 180, limit it to 180
  if (intValue > 180) {
    intValue = 180;
  }

  // Return the result
  return intValue;
}


void rotateServo(int speed) {
  // Set the servo speed
  myServo.write(speed);
}
=======
//libraries

#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include <Servo.h>

//constants relating to our adafruit board (these were found online)

#define BUFSIZE                        128
#define VERBOSE_MODE                   true

#define BLUEFRUIT_SWUART_RXD_PIN       9
#define BLUEFRUIT_SWUART_TXD_PIN       10
#define BLUEFRUIT_UART_CTS_PIN         11
#define BLUEFRUIT_UART_RTS_PIN         8

#ifdef Serial1
  #define BLUEFRUIT_HWSERIAL_NAME      Serial1
#endif

#define BLUEFRUIT_UART_MODE_PIN        12

#define BLUEFRUIT_SPI_CS               8
#define BLUEFRUIT_SPI_IRQ              7
#define BLUEFRUIT_SPI_RST              4

#define BLUEFRUIT_SPI_SCK              13
#define BLUEFRUIT_SPI_MISO             12
#define BLUEFRUIT_SPI_MOSI             11


// Constant for the servo pin
#define SERVO_PIN 9

//Define the objects which are the bluetooth module and the servo

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
Servo myServo;

// A function that prints the error
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

void setup(void)
{
  //attach the servo to pin 9
  myServo.attach(SERVO_PIN);

//check to see if a serial communication was established
  while (!Serial);
  delay(500);

  Serial.begin(115200);

  // Initialise the bluetooth module
  if ( !ble.begin(VERBOSE_MODE) ) {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }

  // Perform a factory reset to make sure everything is in a known state
  //the ble.factoryReset function is carried out and returns a bool if successful
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }

  //Disable command echo from Bluefruit so commands aren't sent back for confirmation
  ble.echo(false);

  //ble.info() can be used to get info about the bluefruit module

 // prevents module from sending extensive debug info
  ble.verbose(false);  
  
  //Wait for connection
  while (! ble.isConnected()) {
      delay(500);
  }


  // Set module to DATA mode
  ble.setMode(BLUEFRUIT_MODE_DATA);
}

void loop(void){

  while ( ble.available() )
  {
    int value = readIntValue();
    Serial.println(value);
    rotateServo(value);
  }
}

// Custom function to read a controller inputs, returns 1,2,3,4 corresponding with up, down, left, right 
int readDirValue(){
  int dirVal;
  char c;

  
}

// Custom function to read an integer value between 0 and 180 from the received data
int readIntValue() {
  int intValue = 0;
  char c;

  // Read characters until a non-digit character is encountered or the integer value exceeds 180
  while (ble.available()) {
    c = ble.read();

    // Ignore the 'enter' (newline) character
    if (c == '\n' || c == '\r') {
      continue;
    }

    if (isdigit(c)) {
      intValue = intValue * 10 + (c - '0');
      if (intValue > 180) {
        break;
      }
    } else {
      break;
    }
  }

  // If the integer value is greater than 180, limit it to 180
  if (intValue > 180) {
    intValue = 180;
  }

  // Return the result
  return intValue;
}


void rotateServo(int speed) {
  // Set the servo speed
  myServo.write(speed);
}
>>>>>>> 62af231be196380409962d8e3b07f5fa5d8d03d9
