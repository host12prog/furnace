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

#include "fmEnvUtil.h"
#include "stringsUtil.h"
#include "macroDraw.h"
#include "fmPublicVars.h"
#include "publicVars.h"
#include "fm.h"
#include "../intConst.h"

class FurnaceGUI;

void FurnaceGUI::drawInsAY(DivInstrument* ins)
{
  insTabSample(ins);
  if (!ins->amiga.useSample)
  {
    if (ImGui::BeginTabItem(_("Timer Macros##sgiAY")))
    {
      macroList.push_back(FurnaceGUIMacroDesc(_("Timer FX##sgiAY"),ins,DIV_MACRO_EX6,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
      macroList.push_back(FurnaceGUIMacroDesc(_("TFX Offset##sgiAY"),ins,DIV_MACRO_EX7,0xff,0,127,64,uiColors[GUI_COLOR_MACRO_OTHER]));
      macroList.push_back(FurnaceGUIMacroDesc(_("Timer Num##sgiAY"),ins,DIV_MACRO_EX8,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
      macroList.push_back(FurnaceGUIMacroDesc(_("Timer Den##sgiAY"),ins,DIV_MACRO_EX9,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
      drawMacros(macroList,macroEditStateMacros);
      ImGui::EndTabItem();
    }
  }
  if (ImGui::BeginTabItem(_("Macros##sgiAY")))
  {
    macroList.push_back(FurnaceGUIMacroDesc(_("Volume##sgiAY"),ins,DIV_MACRO_VOL,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Arpeggio##sgiAY"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_("Pitch##sgiAY"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));

    if(!ins->amiga.useSample)
    {
      macroList.push_back(FurnaceGUIMacroDesc(_("Noise Freq##sgiAY"),ins,DIV_MACRO_DUTY,0xff,0,31,64,uiColors[GUI_COLOR_MACRO_OTHER]));
      macroList.push_back(FurnaceGUIMacroDesc(_("Waveform##sgiAY"),ins,DIV_MACRO_WAVE,0xff,0,3,48,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,true,ayShapeBits));
    }

    macroList.push_back(FurnaceGUIMacroDesc(_("Raw Period##sgiAY"),ins,DIV_MACRO_EX4,0xff,0,0xfff,256,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Raw Envelope Period##sgiAY"),ins,DIV_MACRO_EX5,0xff,0,0xffff,256,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_("Phase Reset##sgiAY"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    macroList.push_back(FurnaceGUIMacroDesc(_("Envelope##sgiAY"),ins,DIV_MACRO_EX2,0xff,0,4,64,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,ayEnvBits));

    macroList.push_back(FurnaceGUIMacroDesc(_("AutoEnv Num##sgiAY"),ins,DIV_MACRO_EX3,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_("AutoEnv Den##sgiAY"),ins,DIV_MACRO_ALG,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}
