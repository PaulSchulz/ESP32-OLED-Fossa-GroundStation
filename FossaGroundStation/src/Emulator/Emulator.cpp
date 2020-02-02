/*
  Emulator.cpp - Class for Fossa Satellite emulation

  Copyright (C) 2020 @Paul_Schulz

  Based on original Emulator code by @4m1g0 found at:
  github:4m1g0/FossaSat-Micro-ESP32-Satellite-Emulator

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

#include "Emulator.h"
#include "../Comms/Comms.h"
#include "../Radio/Radio.h"
//#include <base64.h>

void emulatorInit() {
  Serial.print(F("[Emulator] Initialising.. "));
  Serial.println("Done.");
};

void emulatorUpdate(){
};

/* Respond to radio packets */
void emulatorRespond(){
};

void emulatorRespondPong() {
  uint8_t functionId = RESP_PONG;
  int state = 0;

  Serial.print(F("Sending pong frame ... "));
  state = radio.sendFrame(functionId);

  if (state == ERR_NONE) {
    Serial.println(F("sent successfully!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
  }
  
  Serial.println();
};

void emulatorSysInfoZero(uint8_t* optData, size_t optDataLen) {
  uint8_t* optDataPtr = optData;

  uint8_t batteryChargingVoltage = 0;
  memcpy(optDataPtr, &batteryChargingVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  int16_t batteryChargingCurrent = 0;
  memcpy(optDataPtr, &batteryChargingCurrent, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);

  uint8_t batteryVoltage = 0;
  memcpy(optDataPtr, &batteryVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  uint8_t solarCellAVoltage = 0;
  memcpy(optDataPtr, &solarCellAVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  uint8_t solarCellBVoltage = 0;
  memcpy(optDataPtr, &solarCellBVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  uint8_t solarCellCVoltage = 0;
  memcpy(optDataPtr, &solarCellCVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  int16_t batteryTemperature = 0;
  memcpy(optDataPtr, &batteryTemperature, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);

  int16_t boardTemperature = 0;
  memcpy(optDataPtr, &boardTemperature, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);

  int8_t mcuTemperature = 0;
  memcpy(optDataPtr, &mcuTemperature, sizeof(int8_t));
  optDataPtr += sizeof(int8_t);

  uint16_t resetCounter = 0;
  memcpy(optDataPtr, &resetCounter, sizeof(uint16_t));
  optDataPtr += sizeof(uint16_t);

  uint8_t powerConfig = 0;
  memcpy(optDataPtr, &powerConfig, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

}

void emulatorSysInfoRandom(uint8_t* optData, size_t optDataLen) {
  uint8_t* optDataPtr = optData;

  // batteryChargingVoltage
  uint8_t batteryChargingVoltage
    = ((float)random(1800, 3600) / 1000.0) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &batteryChargingVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  // batteryChargingCurrent
  int16_t batteryChargingCurrent
    = ((float)random(-50000, 50000) / 1000000.0) * (CURRENT_UNIT / CURRENT_MULTIPLIER);
  memcpy(optDataPtr, &batteryChargingCurrent, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);

  // batteryVoltage
  uint8_t batteryVoltage
    = ((float)random(1800, 3600) / 1000.0) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &batteryVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  // solarCellAVoltage
  uint8_t solarCellAVoltage
    = ((float)random(0, 330) / 100.0) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &solarCellAVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  // solarCellBVoltage
  uint8_t solarCellBVoltage
    = ((float)random(0, 330) / 100.0) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &solarCellBVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  // solarCellCVoltage
  uint8_t solarCellCVoltage
    = ((float)random(0, 330) / 100.0) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &solarCellCVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  // batteryTemperature
  int16_t batteryTemperature
    = ((float)random(-50000, 120000) / 1000.0) * (TEMPERATURE_UNIT / TEMPERATURE_MULTIPLIER);
  memcpy(optDataPtr, &batteryTemperature, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);

  // boardTemperature
  int16_t boardTemperature
    = ((float)random(-50000, 120000) / 1000.0) * (TEMPERATURE_UNIT / TEMPERATURE_MULTIPLIER);
  memcpy(optDataPtr, &boardTemperature, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);

  // mcuTemperature
  int8_t mcuTemperature = random(0,300) - 150;
  memcpy(optDataPtr, &mcuTemperature, sizeof(int8_t));
  optDataPtr += sizeof(int8_t);

  // resetCounter
  uint16_t resetCounter = 3;
  memcpy(optDataPtr, &resetCounter, sizeof(uint16_t));
  optDataPtr += sizeof(uint16_t);

  // powerConfig
  uint8_t powerConfig = 0xFF;
  memcpy(optDataPtr, &powerConfig, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);
}

void emulatorRespondSysInfo() {
  size_t optDataLen = 6*sizeof(uint8_t) + 3*sizeof(int16_t) + sizeof(uint16_t) + sizeof(int8_t);
  uint8_t* optData = new uint8_t[optDataLen];
  uint8_t* optDataPtr = optData;

  // emulatorSysInfoZero(optData, optDataLen);
  emulatorSysInfoRandom(optData, optDataLen);

  Serial.println();
  Serial.println(F("System info:"));

  // batteryChargingVoltage
  uint8_t batteryChargingVoltage = (uint8_t)(*optDataPtr);
  optDataPtr += sizeof(uint8_t);
  Serial.printf("  %-24s %5d   0x%2X * %d = %5d %s\n",
		(char *)F("batteryChargingVoltage"),
		batteryChargingVoltage,
		batteryChargingVoltage,
		VOLTAGE_MULTIPLIER,
		(batteryChargingVoltage * VOLTAGE_MULTIPLIER),
		(char *)F("mV"));
  
  // batteryChargingCurrent
  // DEBUG
  int16_t batteryChargingCurrent = *optDataPtr + 0x100 * *(optDataPtr+1);
  optDataPtr += sizeof(int16_t);
  Serial.printf("  %-24s %5d 0x%04X * %d = %5d %s\n",
		(char *)F("batteryChargingCurrent"),
		batteryChargingCurrent,
		batteryChargingCurrent,
		CURRENT_MULTIPLIER,
		(batteryChargingCurrent * CURRENT_MULTIPLIER),
		(char *)F("uA"));

  // batteryVoltage
  uint8_t batteryVoltage = (uint8_t)*optDataPtr;
  optDataPtr += sizeof(uint8_t);
  Serial.printf("  %-24s %5d   0x%02X * %d = %5d %s\n",
		(char *)F("batteryVoltage"),
		batteryVoltage,
		batteryVoltage,
		VOLTAGE_MULTIPLIER,
		(batteryVoltage * VOLTAGE_MULTIPLIER),
		(char *)F("mV"));

  // solarCellAVoltage
  uint8_t solarCellAVoltage = (uint8_t)*optDataPtr;
  optDataPtr += sizeof(uint8_t);
  Serial.printf("  %-24s %5d   0x%02X * %d = %5d %s\n",
		(char *)F("solarCellAVoltage"),
		solarCellAVoltage,
		solarCellAVoltage,
		VOLTAGE_MULTIPLIER,
		(solarCellAVoltage * VOLTAGE_MULTIPLIER),
		(char *)F("mV"));

  // solarCellBVoltage
  uint8_t solarCellBVoltage = (uint8_t)*optDataPtr;
  optDataPtr += sizeof(uint8_t);
  Serial.printf("  %-24s %5d   0x%02X * %d = %5d %s\n",
		(char *)F("solarCellBVoltage"),
		solarCellBVoltage,
		solarCellBVoltage,
		VOLTAGE_MULTIPLIER,
		(solarCellBVoltage * VOLTAGE_MULTIPLIER),
		(char *)F("mV"));

  // solarCellCVoltage
  uint8_t solarCellCVoltage =  (uint8_t)*optDataPtr;
  optDataPtr += sizeof(uint8_t);
  Serial.printf("  %-24s %5d   0x%02X * %d = %5d %s\n",
		(char *)F("solarCellCVoltage"),
		solarCellCVoltage,
		solarCellCVoltage,
		VOLTAGE_MULTIPLIER,
		(solarCellCVoltage * VOLTAGE_MULTIPLIER),
		(char *)F("mV"));

  // batteryTemperature
  int16_t batteryTemperature = (uint16_t)*optDataPtr;
  optDataPtr += sizeof(int16_t);
  Serial.printf("  %-24s %5d 0x%04X * %d = %5d %s\n",
		(char *)F("batteryTemperature"),
		batteryTemperature,
		batteryTemperature,
		TEMPERATURE_MULTIPLIER,
		(batteryTemperature * TEMPERATURE_MULTIPLIER),
		(char *)F("mdeg-C"));

  // boardTemperature
  // DEBUG
  int16_t boardTemperature = *optDataPtr + 0x100 * *(optDataPtr + 1);
  optDataPtr += sizeof(int16_t);
  Serial.printf("  %-24s %5d 0x%04X * %d = %5d %s\n",
		(char *)F("boardTemperature"),
		boardTemperature,
		boardTemperature,
		TEMPERATURE_MULTIPLIER,
		(boardTemperature * TEMPERATURE_MULTIPLIER),
		(char *)F("mdeg-C"));

  // mcuTemperature
  int8_t mcuTemperature = (int8_t)*optDataPtr;
  optDataPtr += sizeof(int8_t);
  Serial.printf("  %-24s %5d   0x%02X * %d = %5d %s\n",
		(char *)F("mcuTemperature"),
		mcuTemperature,
		(uint8_t) mcuTemperature,
		TEMPERATURE_MULTIPLIER,
		(mcuTemperature * TEMPERATURE_MULTIPLIER),
		(char *)F("mdeg-C"));
  
  // resetCounter
  // DEBUG
  uint16_t resetCounter = *optDataPtr + (*(optDataPtr + 1)<<8);
  optDataPtr += sizeof(uint16_t);
  Serial.printf("  %-24s %5d 0x%04X *  1 = %5d %s\n",
		(char *)F("resetCounter"),
		resetCounter,
		resetCounter,
		resetCounter,
		(char *)F("counts")
		);
  
  // powerConfig
  uint8_t powerConfig = (uint8_t)*optDataPtr;
  optDataPtr += sizeof(uint8_t);

  Serial.printf("  %-24s %5d   0x%02X *  1 = 0b",
		(char *)F("powerConfig"),
                powerConfig,
		powerConfig
		);
  Serial.println(powerConfig, BIN);

  Serial.print("Frame ");
  {
    int i = 0;
    for (i=0; i<optDataLen; i++){
      Serial.printf("-%02X",optData[i]);
    }
    Serial.println();
  }
  
  Serial.print(F("Sending sysInfo frame ... "));
  uint8_t functionId = RESP_SYSTEM_INFO;
  int state = 0;
  state = radio.sendFrame(functionId, (char *)optData, optDataLen);

  if (state == ERR_NONE) {
    Serial.println(F("sent successfully!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
  }

  Serial.println();
}
