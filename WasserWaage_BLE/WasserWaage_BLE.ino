/*
   -- WasserWaage --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.13 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.13.13 or later version;
     - for iOS 1.10.3 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE
#include <math.h>
#include <BLEDevice.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "RemoteXY"

#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 149 bytes
  { 255,13,0,49,0,142,0,17,0,0,0,31,1,106,200,1,1,11,0,11,
  6,7,20,20,6,24,71,12,104,81,81,56,0,2,24,255,0,0,0,0,
  0,0,180,67,0,0,52,66,0,0,112,65,0,0,160,64,24,0,67,34,
  34,40,10,4,2,26,11,67,34,48,40,10,4,2,26,11,67,34,61,40,
  10,4,2,26,11,129,8,34,20,9,17,112,105,116,99,104,0,129,8,48,
  13,9,17,114,111,108,108,0,129,9,62,16,9,17,121,97,119,0,67,34,
  75,40,10,4,2,26,11,1,78,4,24,24,0,2,31,122,101,114,111,0,
  70,12,103,81,81,148,26,134,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  float orientation_pitch; // from -PI to PI
  float orientation_roll; // from -PI to PI
  float orientation_yaw; // from -PI to PI
  uint8_t button_zero; // =1 if button pressed, else =0

    // output variables
  float instrument_01; // from 0 to 360
  char text_pitch[11]; // string UTF8 end zero
  char text_roll[11]; // string UTF8 end zero
  char text_yaw[11]; // string UTF8 end zero
  char text_angle[11]; // string UTF8 end zero
  uint8_t led_OK; // from 0 to 1

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)

#define MaxTilt 0.003
float offset_roll = 0;
float offset_pitch = 0;
float offset_yaw = 0;
float flt_roll = 0;
float flt_pitch = 0;
float flt_yaw = 0;
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

void setup() 
{
  RemoteXY_Init (); 
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  if(RemoteXY.button_zero){
    offset_roll = RemoteXY.orientation_roll;
    offset_pitch = RemoteXY.orientation_pitch;
    offset_yaw = RemoteXY.orientation_yaw;
  }
  flt_yaw = RemoteXY.orientation_yaw - offset_yaw;
  flt_pitch = RemoteXY.orientation_pitch - offset_pitch;
  flt_roll = RemoteXY.orientation_roll - offset_roll;
  
  if (sqrt(sq(flt_pitch) + sq(flt_roll)) < MaxTilt) {
      RemoteXY.led_OK = 1;
  } else {
      RemoteXY.led_OK = 0;
  }

  RemoteXY.instrument_01 = atan2(-(RemoteXY.orientation_roll - offset_roll), (RemoteXY.orientation_pitch - offset_pitch)) * 180.0 / PI + 180;
  dtostrf(RemoteXY.instrument_01, 10, 4, RemoteXY.text_angle);
  dtostrf(flt_yaw, 10, 4, RemoteXY.text_yaw);
  dtostrf(flt_pitch, 10, 4, RemoteXY.text_pitch);
  dtostrf(flt_roll, 10, 4, RemoteXY.text_roll);

  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay(), use instead RemoteXY_delay() 
}
