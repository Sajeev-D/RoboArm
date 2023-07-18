
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

void setup(){
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

void loop(){
  char button;//default
  /*
  // Check for user input
  char n, inputs[BUFSIZE+1];

  if (Serial.available())
  {
    n = Serial.readBytes(inputs, BUFSIZE);
    inputs[n] = 0;
    // Send characters to Bluefruit
    Serial.print("Sending: ");
    Serial.println(inputs);

    // Send input data to host via Bluefruit
    ble.print(inputs);
  }
  */

  // get controller input as a single char
  if ( ble.available() ){
    button = getInput();
    //pressed: (Up, down, left, right) => (A,B,C,D)
    //let go: (Up, down, left, right) => (H,I,J,K)
    Serial.println(button);// TESTING

  }

  //rotate servo according to input
  rotateServo(button);
}

//function that reads the next 5 chars, returns the last button pressed (whether on or off) but rlly
//pressed: (Up, down, left, right) => (A,B,C,D)
//let go: (Up, down, left, right) => (H,I,J,K)
char getInput(){
  char output;
  char btnNum;
  char onOrOff;
  //first two chars are always !B
  output = ble.read();
  output = ble.read();
  //third char says which button, 4th char says whether it was pressed or let go
  btnNum = ble.read();
  onOrOff = ble.read();

  //5th char is useless, go over it (so you dont accidently read it later)
  output = ble.read();

  //logic
  if(onOrOff=='1'){
    //all the cases where the btn was pressed (not let go)
    if(btnNum=='5'){
      output = 'A';
    }else if(btnNum=='6'){
      output = 'B';
    }else if(btnNum=='7'){
      output = 'C';
    }else if(btnNum=='8'){
      output = 'D';
    }
  }else{// onOrOff=='0'
    //all the cases where the btn was let go
    if(btnNum=='5'){
      output = 'H';
    }else if(btnNum=='6'){
      output = 'I';
    }else if(btnNum=='7'){
      output = 'J';
    }else if(btnNum=='8'){
      output = 'K';
    }
  }

  return output;
}


//rotate servo according to input from the getInput() function
void rotateServo(char c){
  //pressed: (Up, down, left, right) => (A,B,C,D)
  //let go: (Up, down, left, right) => (H,I,J,K)

  if(c == 'H' || c == 'I' || c == 'J' || c == 'K'){
    myServo.write(90);
  }else if(c == 'C'){
    //left
    myServo.write(110);
  }else if(c=='D'){
    //right
    myServo.write(70);
  }
}
