/*
  Emulator.cpp - Class for Fossa Satellite emulation

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
  state = radio.sendFrame(functionId,"");

  if (state == ERR_NONE) {
    Serial.println(F("sent successfully!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
  }
  
  Serial.println();
};

void emulatorRespondSysInfo() {
  size_t optDataLen = 6*sizeof(uint8_t) + 3*sizeof(int16_t) + sizeof(uint16_t) + sizeof(int8_t);
  uint8_t* optData = new uint8_t[optDataLen];
  uint8_t* optDataPtr = optData;

  Serial.println(F("System info:"));

  // set batteryChargingVoltage variable
  uint8_t batteryChargingVoltage = ((float)random(1800, 3600) / 1000.0) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &batteryChargingVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);
  Serial.print(batteryChargingVoltage);
  Serial.print('*');
  Serial.print(VOLTAGE_MULTIPLIER);
  Serial.println(F(" mV"));

  // set batteryChragingCurrent variable
  int16_t batteryChragingCurrent = ((float)random(-50000, 50000) / 1000000.0) * (CURRENT_UNIT / CURRENT_MULTIPLIER);
  memcpy(optDataPtr, &batteryChragingCurrent, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);
  Serial.print(batteryChragingCurrent);
  Serial.print('*');
  Serial.print(CURRENT_MULTIPLIER);
  Serial.println(F(" uA"));

  // set batteryVoltage variable
  uint8_t batteryVoltage = ((float)random(1800, 3600) / 1000.0) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &batteryVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);
  Serial.print(batteryVoltage);
  Serial.print('*');
  Serial.print(VOLTAGE_MULTIPLIER);
  Serial.println(F(" mV"));

  // set solarCellAVoltage variable
  uint8_t solarCellAVoltage = ((float)random(0, 330) / 100.0) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &solarCellAVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);
  Serial.print(solarCellAVoltage);
  Serial.print('*');
  Serial.print(VOLTAGE_MULTIPLIER);
  Serial.println(F(" mV"));

  // set solarCellBVoltage variable
  uint8_t solarCellBVoltage = ((float)random(0, 330) / 100.0) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &solarCellBVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);
  Serial.print(solarCellBVoltage);
  Serial.print('*');
  Serial.print(VOLTAGE_MULTIPLIER);
  Serial.println(F(" mV"));

  // set solarCellCVoltage variable
  uint8_t solarCellCVoltage = ((float)random(0, 330) / 100.0) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &solarCellCVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);
  Serial.print(solarCellCVoltage);
  Serial.print('*');
  Serial.print(VOLTAGE_MULTIPLIER);
  Serial.println(F(" mV"));

  // set batteryTemperature variable
  int16_t batteryTemperature = ((float)random(-50000, 120000) / 1000.0) * (TEMPERATURE_UNIT / TEMPERATURE_MULTIPLIER);
  memcpy(optDataPtr, &batteryTemperature, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);
  Serial.print(batteryTemperature);
  Serial.print('*');
  Serial.print(TEMPERATURE_MULTIPLIER);
  Serial.println(F(" mdeg C"));

  // set boardTemperature variable
  int16_t boardTemperature = ((float)random(-50000, 120000) / 1000.0) * (TEMPERATURE_UNIT / TEMPERATURE_MULTIPLIER);
  memcpy(optDataPtr, &boardTemperature, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);
  Serial.print(boardTemperature);
  Serial.print('*');
  Serial.print(TEMPERATURE_MULTIPLIER);
  Serial.println(F(" mdeg C"));

  // set mcuTemperature variable (read twice since first value is often nonsense)
  int8_t mcuTemperature = random(0,300) - 150;
  memcpy(optDataPtr, &mcuTemperature, sizeof(int8_t));
  optDataPtr += sizeof(int8_t);
  Serial.println(mcuTemperature);

  // set resetCounter variable
  uint16_t resetCounter = 3;
  memcpy(optDataPtr, &resetCounter, sizeof(uint16_t));
  optDataPtr += sizeof(uint16_t);
  Serial.println(resetCounter);

  // set powerConfig variable
  uint8_t powerConfig = 0xFF;
  Serial.print(F("Config: 0b"));
  Serial.println(powerConfig, BIN);
  memcpy(optDataPtr, &powerConfig, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  Serial.print(F("Sending sysInfo frame ... "));
  uint8_t functionId = RESP_SYSTEM_INFO;
  int state = 0;
  state = radio.sendFrame(functionId,(char *)optDataPtr);

  if (state == ERR_NONE) {
    Serial.println(F("sent successfully!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
  }

  Serial.println();
}
