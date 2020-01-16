/*
  Emulator.h - Class for Fossa Satellite emulation
  
  Copyright (C) 2020 @Paul Schulz

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

#ifndef _FOSSA_EMULATOR_H
#define _FOSSA_EMULATOR_H

#include "../ConfigManager/ConfigManager.h"
#include "../Radio/Radio.h"
#include "../Status.h"

void emulatorInit();
void emulatorUpdate();
void emulatorRespond();
void emulatorRespondPong();
void emulatorRespondSysInfo();

extern ConfigManager configManager;
extern Status status;
extern Radio radio;

#endif
