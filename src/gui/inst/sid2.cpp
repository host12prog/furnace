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

void FurnaceGUI::drawInsSID2(DivInstrument* ins)
{
  if (ImGui::BeginTabItem("SID2")) 
  {
    ImGui::AlignTextToFramePadding();
    ImGui::Text(_L("Waveform##sgiSID2"));
    ImGui::SameLine();
    pushToggleColors(ins->c64.triOn);
    if (ImGui::Button(_L("tri##sgiSID2"))) 
    { PARAMETER
      ins->c64.triOn=!ins->c64.triOn;
    }
    popToggleColors();
    ImGui::SameLine();
    pushToggleColors(ins->c64.sawOn);
    if (ImGui::Button(_L("saw##sgiSID2"))) 
    { PARAMETER
      ins->c64.sawOn=!ins->c64.sawOn;
    }
    popToggleColors();
    ImGui::SameLine();
    pushToggleColors(ins->c64.pulseOn);
    if (ImGui::Button(_L("pulse##sgiSID2"))) 
    { PARAMETER
      ins->c64.pulseOn=!ins->c64.pulseOn;
    }
    popToggleColors();
    ImGui::SameLine();
    pushToggleColors(ins->c64.noiseOn);
    if (ImGui::Button(_L("noise##sgiSID2"))) 
    { PARAMETER
      ins->c64.noiseOn=!ins->c64.noiseOn;
    }
    popToggleColors();

    ImVec2 sliderSize=ImVec2(20.0f*dpiScale,128.0*dpiScale);

    //if (ImGui::BeginTable("C64EnvParams",6,ImGuiTableFlags_NoHostExtendX))
    if (ImGui::BeginTable("C64EnvParams",5,ImGuiTableFlags_NoHostExtendX)) //sigh tildearrow
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      //ImGui::TableSetupColumn("c4",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c5",ImGuiTableColumnFlags_WidthStretch);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("A##sgiSID2"));
      ImGui::TextUnformatted(_L("A##sgiSID2"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("D##sgiSID2"));
      ImGui::TextUnformatted(_L("D##sgiSID2"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("S##sgiSID2"));
      ImGui::TextUnformatted(_L("S##sgiSID2"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("R##sgiSID2"));
      ImGui::TextUnformatted(_L("R##sgiSID2"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("VOL##sgiSID2"));
      ImGui::TextUnformatted(_L("VOL##sgiSID2"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("Envelope##sgiSID2"));
      ImGui::TextUnformatted(_L("Envelope##sgiSID2"));

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Attack",sliderSize,ImGuiDataType_U8,&ins->c64.a,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Decay",sliderSize,ImGuiDataType_U8,&ins->c64.d,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Sustain",sliderSize,ImGuiDataType_U8,&ins->c64.s,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Release",sliderSize,ImGuiDataType_U8,&ins->c64.r,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      //P(CWVSliderScalar("##Volume",sliderSize,ImGuiDataType_U8,&ins->sid2.volume,&_ZERO,&_FIFTEEN)); rightClickable
      //ImGui::TableNextColumn();
      drawFMEnv(15-ins->sid2.volume,16-ins->c64.a,16-ins->c64.d,15-(ins->c64.r == 15 ? (ins->c64.r - 1) : ins->c64.r),15-(ins->c64.r == 15 ? (ins->c64.r - 1) : ins->c64.r),15-ins->c64.s,0,0,0,15,16,15,ImVec2(ImGui::GetContentRegionAvail().x,sliderSize.y),ins->type); //the (ins->c64.r == 15 ? (ins->c64.r - 1) : ins->c64.r) is used so release part never becomes horizontal (which isn't the case with SID envelope)

      ImGui::EndTable();
    }

    P(CWSliderScalar(_L("Duty##sgiSID2"),ImGuiDataType_U16,&ins->c64.duty,&_ZERO,&_FOUR_THOUSAND_NINETY_FIVE)); rightClickable

    bool ringMod=ins->c64.ringMod;
    if (ImGui::Checkbox(_L("Ring Modulation##sgiSID2"),&ringMod)) 
    { PARAMETER
      ins->c64.ringMod=ringMod;
    }
    bool oscSync=ins->c64.oscSync;
    if (ImGui::Checkbox(_L("Oscillator Sync##sgiSID2"),&oscSync)) 
    { PARAMETER
      ins->c64.oscSync=oscSync;
    }

    P(ImGui::Checkbox(_L("Enable filter##sgiSID2"),&ins->c64.toFilter));
    P(ImGui::Checkbox(_L("Initialize filter##sgiSID2"),&ins->c64.initFilter));
    
    P(CWSliderScalar(_L("Cutoff##sgiSID2"),ImGuiDataType_U16,&ins->c64.cut,&_ZERO,&_FOUR_THOUSAND_NINETY_FIVE)); rightClickable
    P(CWSliderScalar(_L("Resonance##sgiSID2"),ImGuiDataType_U8,&ins->c64.res,&_ZERO,&_TWO_HUNDRED_FIFTY_FIVE)); rightClickable

    ImGui::AlignTextToFramePadding();
    ImGui::Text(_L("Filter Mode##sgiSID2"));
    ImGui::SameLine();
    pushToggleColors(ins->c64.lp);
    if (ImGui::Button(_L("low##sgiSID2"))) 
    { PARAMETER
      ins->c64.lp=!ins->c64.lp;
    }
    popToggleColors();
    ImGui::SameLine();
    pushToggleColors(ins->c64.bp);
    if (ImGui::Button(_L("band##sgiSID2"))) 
    { PARAMETER
      ins->c64.bp=!ins->c64.bp;
    }
    popToggleColors();
    ImGui::SameLine();
    pushToggleColors(ins->c64.hp);
    if (ImGui::Button(_L("high##sgiSID2"))) 
    { PARAMETER
      ins->c64.hp=!ins->c64.hp;
    }
    popToggleColors();

    P(CWSliderScalar(_L("Noise Mode##sgiSID2"),ImGuiDataType_U8,&ins->sid2.noise_mode,&_ZERO,&_THREE));
    P(CWSliderScalar(_L("Wave Mix Mode##sgiSID2"),ImGuiDataType_U8,&ins->sid2.mix_mode,&_ZERO,&_THREE,_L(SID2waveMixModes[ins->sid2.mix_mode&3])));

    if (ImGui::Checkbox(_L("Absolute Cutoff Macro##sgiSID2"),&ins->c64.filterIsAbs)) 
    {
      ins->std.get_macro(DIV_MACRO_ALG, true)->vZoom=-1;
      PARAMETER;
    }
    if (ImGui::Checkbox(_L("Absolute Duty Macro##sgiSID2"),&ins->c64.dutyIsAbs)) 
    {
      ins->std.get_macro(DIV_MACRO_DUTY, true)->vZoom=-1;
      PARAMETER;
    }
    ImGui::EndTabItem();
  }

  if (ImGui::BeginTabItem(_L("Macros##sgiSID2"))) 
  {
    int dutyMin = 0;
    int dutyMax = 0;

    if (ins->c64.dutyIsAbs)
    {
      dutyMin=0;
      dutyMax=4095;
    }

    else 
    {
      dutyMin=-4095;
      dutyMax=4095;
    }

    int cutoffMin=-4095;
    int cutoffMax=4095;

    if (ins->c64.filterIsAbs) 
    {
      cutoffMin=0;
    }

    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##sgiSID2"),ins,DIV_MACRO_VOL,0xff,0,15,64,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Arpeggio##sgiSID2"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Pitch##sgiSID2"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Duty##sgiSID21"),ins,DIV_MACRO_DUTY,0xff,dutyMin,dutyMax,160,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Waveform##sgiSID21"),ins,DIV_MACRO_WAVE,0xff,0,4,64,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,true,c64ShapeBits,0));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Noise Mode##sgiSID21"),ins,DIV_MACRO_EX10,0xff,0,3,32,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Wave Mix Mode##sgiSID21"),ins,DIV_MACRO_EX11,0xff,0,3,32,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Cutoff##sgiSID21"),ins,DIV_MACRO_ALG,0xff,cutoffMin,cutoffMax,160,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Filter Mode##sgiSID21"),ins,DIV_MACRO_EX1,0xff,0,3,48,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,SID2filtModeBits));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Filter Toggle##sgiSID2"),ins,DIV_MACRO_EX3,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Resonance##sgiSID21"),ins,DIV_MACRO_EX2,0xff,0,255,160,uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Phase Reset##sgiSID2"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Envelope Reset/Key Control##sgiSID2"),ins,DIV_MACRO_EX9,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Special##sgiSID2"),ins,DIV_MACRO_EX4,0xff,0,2,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,SID2controlBits));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Attack##sgiSID2"),ins,DIV_MACRO_EX5, 0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Decay##sgiSID2"),ins,DIV_MACRO_EX6, 0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Sustain##sgiSID2"),ins,DIV_MACRO_EX7, 0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Release##sgiSID2"),ins,DIV_MACRO_EX8, 0xff,0,15,64,uiColors[GUI_COLOR_MACRO_OTHER]));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}