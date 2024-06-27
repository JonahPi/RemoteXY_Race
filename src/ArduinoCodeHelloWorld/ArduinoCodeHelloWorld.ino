/*
   -- HelloWorld --
   
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

// RemoteXY Definition und Import der Kommunikationsbibliothek
#define REMOTEXY_MODE__ESP32CORE_BLE

#include <BLEDevice.h>

// RemoteXY Verbindungsname und Einbindung der Bibliothek
#define REMOTEXY_BLUETOOTH_NAME "RemoteXY"
#include <RemoteXY.h>

// RemoteXY Konfiguration des App-Bildschirms (GUI) 
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 37 bytes
  { 255,1,0,11,0,30,0,17,0,0,0,31,1,106,200,1,1,2,0,1,
  43,69,24,24,0,2,31,0,67,37,112,40,10,4,2,26,11 };
  
// Die folgende struct-Variable zeigt alle Variablen die in der App verwendet werden
struct {

    // Eingabe Variablen z.B. Buttons, Schalter
  uint8_t button_01; // =1 if button pressed, else =0

    // Ausgabe Variablen z.B. Textfelder, Instrumente
  char text_01[11]; // string UTF8 end zero

    // Weitere Variablen
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


int x=0;

void setup() 
{
  RemoteXY_Init (); 
}

void loop() 
{ 
  RemoteXY_Handler();
  if (RemoteXY.button_01 != 1) {
    x += 1;
    snprintf(RemoteXY.text_01, sizeof(RemoteXY.text_01), "%d", x);
  } else {
    x = 0;
  } 
  RemoteXY_delay(1000);
}