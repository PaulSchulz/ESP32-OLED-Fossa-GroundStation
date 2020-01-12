/*
  Console.cpp - Class to handle serial console
  
  Copyright (C) 2020 @Paul_Schulz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "Console.h"
#include "Arduino.h"

//const char* ntpServer = "pool.ntp.org";
//const long  gmtOffset_sec = 0; // 3600;         // 3600 for Spain
//const int   daylightOffset_sec = 0; // 3600;

void consolePrintLocalTime();
void consolePrintControls();
void consoleSwitchTestmode();

Console::Console(ConfigManager& x)
: configManager(x)
{
  
}

// Initialisation
void Console::doInit(){
  Serial.print(F("[Console] Initializing ... "));
  Serial.println(F("success!"));
}

// Setup
void Console::doSetup(){
  Serial.println();
  // consolePrintLocalTime();
  Serial.printf("Fossa Ground station Version %d\n", status.version); 
  Serial.printf("Press 'h' for command options.\n");
  Serial.println();
}

// Function to call every loop
void Console::doLoop() {
  if(!Serial.available()) {
    return;
  } 

  radio.disableInterrupt();
  // get the first character
  char serialCmd = Serial.read();

  // wait for a bit to receive any trailing characters
  delay(50);

  // dump the serial buffer
  while(Serial.available()) {
    Serial.read();
  }

  // process serial command
  switch(serialCmd) {
    case 'h':
      consolePrintControls();
      break; 
    case 'c':
      Serial.println(F("Configuration"));
      configManager.printConfig();
      break;
    case 'p':
      Serial.println(F("Send ping frame"));
      if (!radio.isReady()) {
        Serial.println(F("Radio is not ready, please configure it properly before using this command."));
        break;
      }
      radio.sendPing();
      break;
    case 'q':
      Serial.println(F("Send pong frame (testing)"));
      if (!radio.isReady()) {
        Serial.println(F("Radio is not ready, please configure it properly before using this command."));
        break;
      }
      radio.sendFrame(0x10,"");
      break;  
    case 'i':
      Serial.println(F("Request satellite info"));
      if (!radio.isReady()) {
        Serial.println(F("Radio is not ready, please configure it properly before using this command."));
        break;
      }
      radio.requestInfo();
      break;
    case 'l':
      Serial.println(F("Request last packet info"));
      if (!radio.isReady()) {
        Serial.println(F("Radio is not ready, please configure it properly before using this command."));
        break;
      }
      radio.requestPacketInfo();
      break;
    case 'r':
      Serial.println(F("Send message to be retransmitted"));
      if (!radio.isReady()) {
        Serial.println(F("Radio is not ready, please configure it properly before using this command."));
        break;
      }
      Serial.println(F("Enter message to be sent:"));
      Serial.println(F("(max 32 characters, end with LF or CR+LF)"));
      {
        // get data to be retransmited
        char optData[32];
        uint8_t bufferPos = 0;
        while(bufferPos < 32) {
          while(!Serial.available());
          char c = Serial.read();
          Serial.print(c);
          if((c != '\r') && (c != '\n')) {
            optData[bufferPos] = c;
            bufferPos++;
          } else {
            break;
          }
        }
        optData[bufferPos] = '\0';

        // wait for a bit to receive any trailing characters
        delay(100);

        // dump the serial buffer
        while(Serial.available()) {
          Serial.read();
        }

        Serial.println();
        radio.requestRetransmit(optData);
      }
      break;
    case 'e':
      Serial.println(F("Erase board config and restart."));
      Serial.print(F("Are you sure (y/N)?"));
      while(!Serial.available());
      {
        char c = Serial.read();
        Serial.println(c);
        if((c == 'y') || (c == 'Y')) {
          Serial.println(F("** Reset and restart ***"));
          configManager.resetAllConfig();
          ESP.restart();
        } else {
          Serial.println(F("abort - No changes made"));
        }
      }
      break;
    case 't':
      Serial.println(F("Change the test mode and restart"));
      consoleSwitchTestmode();
      ESP.restart();
      break;
    case 'b':
        Serial.println(F("Reboot the board"));
        ESP.restart();
        break;
    default:
      Serial.print(F("Unknown command: "));
      Serial.println(serialCmd);
      break;
  }
  radio.enableInterrupt();
}

void consolePrintLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void consoleSwitchTestmode() {
  char temp_station[32];
  if ((configManager.getThingName()[0]=='t') 
      && (configManager.getThingName()[1]=='e')
      && (configManager.getThingName()[2]=='s')
      && (configManager.getThingName()[4]=='_')) {
    Serial.println(F("Changed from test mode to normal mode"));
    for (byte a=5; a<=strlen(configManager.getThingName()); a++ ) {
      configManager.getThingName()[a-5]=configManager.getThingName()[a];
    }
  }
  else
  {
    strcpy(temp_station,"test_");
    strcat(temp_station,configManager.getThingName());
    strcpy(configManager.getThingName(),temp_station);
    Serial.println(F("Changed from normal mode to test mode"));
  }

  configManager.configSave();
}

// function to print controls
void consolePrintControls() {
  Serial.println();
  Serial.println(F("------------- Controls -------------"));
  Serial.println(F("h - display this help message"       ));
  Serial.println(F("c - display configuration"           ));
  Serial.println(F("p - send ping frame"                 ));
  Serial.println(F("i - request satellite info"          ));
  Serial.println(F("l - request last packet info"        ));
  Serial.println(F("r - send message to be retransmitted"));
  Serial.println(F("t - change the test mode and restart"));
  Serial.println(F("e - erase board config and reset"    ));
  Serial.println(F("b - reboot the board"                ));
  Serial.println(F("------------------------------------"));
}
