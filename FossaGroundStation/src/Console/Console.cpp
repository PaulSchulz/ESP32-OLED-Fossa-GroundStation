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

Console::Console(ConfigManager& x)
: configManager(x)
{
  
}

void Console::init(){
  Serial.print(F("[Serial] Initializing ... "));
}