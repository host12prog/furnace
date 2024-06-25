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

void FurnaceGUI::drawInsGBAMINMOD(DivInstrument* ins)
{
  if(ins->amiga.useWave)
  {
    insTabWave(ins);
  }

  insTabSample(ins);

  if (ImGui::BeginTabItem(_("Macros##sgiGBAMINMOD"))) 
  {
    macroList.push_back(FurnaceGUIMacroDesc(_("Volume##sgiGBAMINMOD"),ins,DIV_MACRO_VOL,0xff,0,255,160,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Arpeggio##sgiGBAMINMOD"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_("Pitch##sgiGBAMINMOD"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_("Waveform##sgiGBAMINMOD"), ins, DIV_MACRO_WAVE, 0xff, 0, WAVE_MACRO_MAX, 160, uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,false,NULL,true));
    macroList.push_back(FurnaceGUIMacroDesc(_("Panning (left)##sgiGBAMINMOD"),ins,DIV_MACRO_PAN_LEFT,0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER],false,(ins->type==DIV_INS_AMIGA)?macroQSoundMode:NULL));
    macroList.push_back(FurnaceGUIMacroDesc(_("Panning (right)##sgiGBAMINMOD"),ins,DIV_MACRO_PAN_RIGHT,0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_("Special##sgiGBAMINMOD"),ins,DIV_MACRO_EX1,0xff,0,2,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,minModModeBits));

    macroList.push_back(FurnaceGUIMacroDesc(_("Phase Reset##sgiGBAMINMOD"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}