#include <Wire.h>
#include <unistd.h>
#include "AltOSCompanion.h"

bool companionConnected = false;
unsigned long startTime;
const unsigned int MAX_MESSAGE_LENGTH = 5;
unsigned int number = 0;

#define COMPANION_ID 0x11E1
#define NUM_CHANNELS 2
#define FETCH_RATE 100

void setup() {

  Serial.begin (38400);
  Serial.print ("Arduino is running ");

  AltOSCompanion::configure(COMPANION_ID, FETCH_RATE, NUM_CHANNELS);

  startTime = millis();

}

 unsigned int outGoing;
 
void loop() {

/*
  if(AltOSCompanion::isConnected()) {
    Serial.print("Connected");
  }
*/

/*
    if(!companionConnected) {
    Serial.print("Connected");
  }

*/

    //Check if anything is available in the receive buffer
  while (Serial.available() > 0)
  {
  
    //Place to hold the incoming message
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;
  
    //Read next available byte in receive buffer
    char inByte = Serial.read();
  
    //Message coming in (check not terminating character)
    if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1))
    {
      //Add the incoming byte to our message
      message[message_pos] = inByte;
      message_pos++;
    }
    //Full message received...
    else
    {
      //Add null character to string
      message[message_pos] = '\0';
  
      //Print the message (or do other things)
      Serial.println(message);
      

      //Convert to integer and print
      number = atoi(message);
      Serial.println(number);

      delay(1000);
      Serial.println("3");
      delay(1000);
      Serial.println("2");
      delay(1000);
      Serial.println("1");
      delay(1000);
      Serial.println("The number from the input is: ");
      Serial.print(number);
  
      //Reset for the next message
      message_pos = 0;
    }

  }
  
  if(AltOSCompanion::isConnected() && !companionConnected) {
    Serial.print("Companion Board connected to Telemetrum (");
    Serial.print(AltOSCompanion::serialNumber());
    Serial.print(") Flight #");
    Serial.print(AltOSCompanion::flightNumber());
    companionConnected = true;
  }
 
  if(companionConnected) {

    AltOSCompanion::updateChannel(0,0);
    AltOSCompanion::updateChannel(1, number);

  }
  

}
