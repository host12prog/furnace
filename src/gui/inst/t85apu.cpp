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

void FurnaceGUI::drawInsT85APU(DivInstrument* ins)
{
  if (ImGui::BeginTabItem(_L("Macros##sgiT85APU"))) 
  {
    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##sgiT85APU"),ins,DIV_MACRO_VOL,0xff,0,255,160,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Arpeggio##sgiT85APU"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Pitch##sgiT85APU"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Duty##sgiT85APU"),ins,DIV_MACRO_DUTY,0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Waveform##sgiT85APU"),ins,DIV_MACRO_WAVE,0xff,0,3,48,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,true,ayShapeBits));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Envelope Shape##sgiT85APU"),ins,DIV_MACRO_EX1,0xff,0,3,48,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,ayEnvBits));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Envelope Number##sgiT85APU"),ins,DIV_MACRO_EX4,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER]));
    //macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (left)##sgiT85APU"),ins,DIV_MACRO_PAN_LEFT,0xff,0,3,32,uiColors[GUI_COLOR_MACRO_OTHER],false,(ins->type==DIV_INS_AMIGA)?macroQSoundMode:NULL));
    //macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (right)##sgiT85APU"),ins,DIV_MACRO_PAN_RIGHT,0xff,0,3,32,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Phase Reset##sgiT85APU"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Envelope Starting Phase##sgiT85APU"),ins,DIV_MACRO_EX3,0xff,0,65535,160,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_L("LFSR Feedback bits##sgiT85APU"),ins,DIV_MACRO_EX2,0xff,0,16,256,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}