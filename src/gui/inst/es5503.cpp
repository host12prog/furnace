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

void FurnaceGUI::drawInsES5503(DivInstrument* ins)
{
  if (ImGui::BeginTabItem("ES5503")) 
  {
    ImGui::AlignTextToFramePadding();
    ImGui::Text(_L("Oscillator mode:##sgi5503"));
    ImGui::SameLine();
    bool freerun = (ins->es5503.initial_osc_mode == OSC_MODE_FREERUN);
    bool oneshot = (ins->es5503.initial_osc_mode == OSC_MODE_ONESHOT);
    bool sync_am = (ins->es5503.initial_osc_mode == OSC_MODE_SYNC_OR_AM);
    bool swap = (ins->es5503.initial_osc_mode == OSC_MODE_SWAP);
    if (ImGui::RadioButton(_L("Freerun##sgi5503"),freerun)) 
    { PARAMETER
      freerun=true;
      oneshot=false;
      sync_am=false;
      swap=false;
      ins->es5503.initial_osc_mode=OSC_MODE_FREERUN;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton(_L("Oneshot##sgi5503"),oneshot)) 
    { PARAMETER
      freerun=false;
      oneshot=true;
      sync_am=false;
      swap=false;
      ins->es5503.initial_osc_mode=OSC_MODE_ONESHOT;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton(_L("Sync/AM##sgi5503"),sync_am)) 
    { PARAMETER
      freerun=false;
      oneshot=false;
      sync_am=true;
      swap=false;
      ins->es5503.initial_osc_mode=OSC_MODE_SYNC_OR_AM;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton(_L("Swap##sgi5503"),swap)) 
    { PARAMETER
      freerun=false;
      oneshot=false;
      sync_am=true;
      swap=false;
      ins->es5503.initial_osc_mode=OSC_MODE_SWAP;
    }

    P(ImGui::Checkbox(_L("Virtual softpan channel##sgi5503"),&ins->es5503.softpan_virtual_channel));
    if (ImGui::IsItemHovered())
    {
      ImGui::SetTooltip(_L("Combines odd and next even channel into one virtual channel with 256-step panning.\nInstrument, volume and effects need to be placed on the odd channel (e.g. 1st, 3rd, 5th etc.)##sgi5503"));
    }

    P(ImGui::Checkbox(_L("Phase reset on key-on##sgi5503"),&ins->es5503.phase_reset_on_start));
    
    ImGui::EndTabItem();
  }

  if(!ins->amiga.useSample) insTabWave(ins);
  insTabSample(ins);

  if (ImGui::BeginTabItem(_L("Macros##sgi5503"))) 
  {
    panMin=0;
    panMax=255;

    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##sgi5503"),ins,DIV_MACRO_VOL,0xff,0,255,160,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Arpeggio##sgi5503"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Pitch##sgi5503"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Osc. mode##sgi5503"),ins,DIV_MACRO_DUTY,0xff,0,3,160,uiColors[GUI_COLOR_MACRO_OTHER]));

    if(ins->es5503.softpan_virtual_channel)
    {
      macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (left)##sgi5503"),ins,DIV_MACRO_PAN_LEFT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER],false,(ins->type==DIV_INS_AMIGA)?macroQSoundMode:NULL));
      macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (right)##sgi5503"),ins,DIV_MACRO_PAN_RIGHT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER]));
    }

    if(!ins->amiga.useSample)
    {
      macroList.push_back(FurnaceGUIMacroDesc(_L("Waveform##sgi5503"),ins,DIV_MACRO_WAVE,0xff,0,MAX(1,e->song.waveLen-1),160,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,false,NULL,true));
    }

    macroList.push_back(FurnaceGUIMacroDesc(_L("Phase Reset##sgi5503"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Wave/sample pos.##sgi5503"),ins,DIV_MACRO_EX1,0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Osc. output##sgi5503"),ins,DIV_MACRO_EX2,0xff,0,7,64,uiColors[GUI_COLOR_MACRO_OTHER]));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}