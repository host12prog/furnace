/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2024 tildearrow and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "macroDraw.h"
#include "../gui.h"

class FurnaceGUI;

String genericGuide(float value) {
  return fmt::sprintf("%d",(int)value);
}

int deBit30(const int val) {
  if ((val&0xc0000000)==0x40000000 || (val&0xc0000000)==0x80000000) return val^0x40000000;
  return val;
}

bool enBit30(const int val) {
  if ((val&0xc0000000)==0x40000000 || (val&0xc0000000)==0x80000000) return true;
  return false;
}

String macroHoverNote(int id, float val, void* u) {
  int* macroVal=(int*)u;
  if ((macroVal[id]&0xc0000000)==0x40000000 || (macroVal[id]&0xc0000000)==0x80000000) {
    if (val<-60 || val>=120) return "???";
    return fmt::sprintf("%d: %s",id,noteNames[(int)val+60]);
  }
  return fmt::sprintf("%d: %d",id,(int)val);
}

String macroHover(int id, float val, void* u) {
  return fmt::sprintf("%d: %d",id,(int)val);
}

String macroHoverLoop(int id, float val, void* u) {
  if (val>1) return "Release";
  if (val>0) return "Loop";
  return "";
}

String macroHoverBit30(int id, float val, void* u) {
  if (val>0) return "Fixed";
  return "Relative";
}

char* int_to_char_array(int num)
{
  static char numberstring[50];
  memset(numberstring, 0, 50);
  snprintf(numberstring, 50, "%d", num);
  return numberstring;
}

String macroHoverGain(int id, float val, void* u) {
  return "";
}

String FurnaceGUI::realMacroHoverGain(int id, float val, void* u) {
  if (val>=224.0f) {
    return fmt::sprintf("%d: +%d (%s)",id,(int)(val-224), settings.language == DIV_LANG_ENGLISH ? "exponential" : _L("exponential##sgmu"));
  }
  if (val>=192.0f) {
    return fmt::sprintf("%d: +%d (%s)",id,(int)(val-192), settings.language == DIV_LANG_ENGLISH ? "linear" : _L("linear##sgmu"));
  }
  if (val>=160.0f) {
    return fmt::sprintf("%d: -%d (%s)",id,(int)(val-160), settings.language == DIV_LANG_ENGLISH ? "exponential" : _L("exponential##sgmu"));
  }
  if (val>=128.0f) {
    return fmt::sprintf("%d: -%d (%s)",id,(int)(val-128), settings.language == DIV_LANG_ENGLISH ? "linear" : _L("linear##sgmu"));
  }
  return fmt::sprintf("%d: %d (%s)",id,(int)val, settings.language == DIV_LANG_ENGLISH ? "direct" : _L("direct##sgmu"));
}

String macroHoverES5506FilterMode(int id, float val, void* u) {
  return "";
}

String FurnaceGUI::realMacroHoverES5506FilterMode(int id, float val, void* u) {
  String mode="???";
  switch (((int)val)&3) {
    case 0:
      mode=settings.language == DIV_LANG_ENGLISH ? "HP/K2, HP/K2" : _L("HP/K2, HP/K2##sgmu");
      break;
    case 1:
      mode=settings.language == DIV_LANG_ENGLISH ? "HP/K2, LP/K1" : _L("HP/K2, LP/K1##sgmu");
      break;
    case 2:
      mode=settings.language == DIV_LANG_ENGLISH ? "LP/K2, LP/K2" : _L("LP/K2, LP/K2##sgmu");
      break;
    case 3:
      mode=settings.language == DIV_LANG_ENGLISH ? "LP/K2, LP/K1" : _L("LP/K2, LP/K1##sgmu");
      break;
    default:
      break;
  }
  return fmt::sprintf("%d: %s",id,mode);
}

String macroLFOWaves(int id, float val, void* u) {
  return "";
}

String FurnaceGUI::realMacroLFOWaves(int id, float val, void* u) {
  switch (((int)val)&3) {
    case 0:
      return settings.language == DIV_LANG_ENGLISH ? "Saw" : _L("Saw##sgmu");
    case 1:
      return settings.language == DIV_LANG_ENGLISH ? "Square" : _L("Square##sgmu");
    case 2:
      return settings.language == DIV_LANG_ENGLISH ? "Triangle" : _L("Triangle##sgmu");
    case 3:
      return settings.language == DIV_LANG_ENGLISH ? "Random" : _L("Random##sgmu");
    default:
      return "???";
  }
  return "???";
}