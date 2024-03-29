//The data is stored in the following format:
//data[0] is the direction pad, up
//data[1] is the direction pad, down
//data[2] is the direction pad, left
//data[3] is the direction pad, right
//data[4] is the start button
//data[5] is the back button
//data[6] is the left joystick button
//data[7] is the right joystick button
//data[8] is the left button (above the left bumper)
//data[9] is the right button (above the right bumper)
//data[10] is the A button
//data[11] is the B button
//data[12] is the X button
//data[13] is the Y button
//data[14] is the left joystick x axis value (128 is center, 0 is all the way to the right, 255 is all the way to the left)
//data[15] is the left joystick y axis value (128 is center, 0 is all the way down, 255 is all the way up)
//data[16] is the right joystick x axis value (128 is center, 0 is all the way to the right, 255 is all the way to the left)
//data[17] is the right joystick y axis value (128 is center, 0 is all the way down, 255 is all the way up)
//data[18] is the left bumper analog value (0 is not pressed, 255 is pressed all the way)
//data[19] is the right bumper analog value (0 is not pressed, 255 is pressed all the way)

//The following issues could arise (and the causes of those issues):
//1) The joystick values may only go down to 1 instead of 0 (clever rounding of a float to a byte to make easy data transmission)
//2) The joystick values may not reset to 128 if you let go of the stick (this is due to a mechanical issue in the controller;
//                                                                        I tried to add a deadzone, but it only covers part of the issue)
//3) There may be a very small lag if you spam all the inputs (I'm not sure where it's coming from, but I got rid of most of it;
//                                                              it should be so small you'd barely notice it, but if it's too much let me know)

//As far as I have tested, those are the only issues I see. If you find more, let me know.
//This code is given to you by Sasha, the Electrical Team Lead. If it ain't working, tell me: I'll fix it.
//                                                                If you ain't using it, I won't fix your shit, so GLHF.

#include <SPI.h>
#include <Nrf2401.h>
#include "RF24.h"
#define CEpin 7                               //The CE pin (pin 3) of the nRF24L01 can be connected to any digital pin.   ######## Change
#define CSpin 8                               //The CS pin (pin 4) of the nRF24L01 can be connected to any digital pin.   ######## Change
#define SizeOfMessage 27                      //The size of the message to be sent.
#define Channel 115                           //The channel has to be the same as that of the receiver. 0-125.
#define PALevel RF24_PA_MAX                   //The power amplifier level. Should work fine, but should check that if something isn't working.
#define DataRate RF24_250KBPS                 //The data rate. Only change it if you're doing something really crazy. Receiver has to have the same data rate.
RF24 myRadio(CEpin, CSpin);
byte addresses[][6] = {"0"};                  //This is used to set up the nRF24L01 pipes. I'm not 100% sure what it does, but it seems standard.
byte message[SizeOfMessage];                  //This is where the massage to be transmitted will be stored.

// Wheel Motor 1 : Pin D5 (H-Bridge:pin2) + D6 (H-Bridge:pin7)
const motorOneFront 5
const motorOneBack 6
// Wheel

void setup() 
{
  Serial.begin(115200);
  myRadio.begin();
  myRadio.setChannel(Channel);                //Set the communication channel. 0-125. Transmitter and reciener have to be on the same channel.
  myRadio.setPALevel(PALevel);                //Set the power amplifier level. MIN,LOW,HIGH,MAX. MAX for best range, MIN for less current (to work with shitty +3.3V).
  myRadio.setDataRate(DataRate);              //Set the data rate. 250KBPS, 1MBPS, 2MBPS.
  myRadio.openWritingPipe(addresses[0]);      //Still not sure about the pipe things, but It seems that this is the standard way of doing it.
  message[0] = 255;                           //Setting up the first message so it is valid (so if we don't get data from the computer we can still send an all zero message).
  message[1] = 255;
  message[2] = 255; 
  message[3] = 255;
  message[14] = 128;
  message[15] = 128;
  message[20] = 128;
  message[21] = 128;
  message[22] = 128;
  message[23] = 128;
  message[26] = 3;
}

void loop()  
{
  Serial.flush();
  delay(10);                                  //This is to let data get in. Should not have any noticable performace issues.

  if (myRadio.available()){
    myRadio.read(&message, SizeOfMessage);
  }
  
  for(int i = 0, i < sizeOfMessage; i++){
    Serial.println(message[i]);
  }
  
}
