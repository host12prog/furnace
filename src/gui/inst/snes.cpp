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

void FurnaceGUI::drawInsSNES(DivInstrument* ins)
{
  if (ImGui::BeginTabItem("SNES")) 
  {
    P(ImGui::Checkbox(_L("Use envelope##sgiSNES"),&ins->snes.useEnv));
    ImVec2 sliderSize=ImVec2(20.0f*dpiScale,128.0*dpiScale);
    if (ins->snes.useEnv) 
    {
      if (ImGui::BeginTable("SNESEnvParams",ins->snes.sus?6:5,ImGuiTableFlags_NoHostExtendX)) 
      {
        ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
        ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
        ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
        if (ins->snes.sus) 
        {
          ImGui::TableSetupColumn("c2x",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
        }
        ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
        ImGui::TableSetupColumn("c4",ImGuiTableColumnFlags_WidthStretch);

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        CENTER_TEXT("A");
        ImGui::TextUnformatted("A");
        ImGui::TableNextColumn();
        CENTER_TEXT("D");
        ImGui::TextUnformatted("D");
        ImGui::TableNextColumn();
        CENTER_TEXT("S");
        ImGui::TextUnformatted("S");
        if (ins->snes.sus) 
        {
          ImGui::TableNextColumn();
          CENTER_TEXT("D2");
          ImGui::TextUnformatted("D2");
        }
        ImGui::TableNextColumn();
        CENTER_TEXT("R");
        ImGui::TextUnformatted("R");
        ImGui::TableNextColumn();
        CENTER_TEXT(_L("Envelope##sgiSNES0"));
        ImGui::TextUnformatted(_L("Envelope##sgiSNES1"));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        P(CWVSliderScalar("##Attack",sliderSize,ImGuiDataType_U8,&ins->snes.a,&_ZERO,&_FIFTEEN)); rightClickable
        ImGui::TableNextColumn();
        P(CWVSliderScalar("##Decay",sliderSize,ImGuiDataType_U8,&ins->snes.d,&_ZERO,&_SEVEN)); rightClickable
        ImGui::TableNextColumn();
        P(CWVSliderScalar("##Sustain",sliderSize,ImGuiDataType_U8,&ins->snes.s,&_ZERO,&_SEVEN)); rightClickable
        if (ins->snes.sus) 
        {
          ImGui::TableNextColumn();
          P(CWVSliderScalar("##Decay2",sliderSize,ImGuiDataType_U8,&ins->snes.d2,&_ZERO,&_THIRTY_ONE)); rightClickable
        }
        ImGui::TableNextColumn();
        P(CWVSliderScalar("##Release",sliderSize,ImGuiDataType_U8,&ins->snes.r,&_ZERO,&_THIRTY_ONE)); rightClickable
        ImGui::TableNextColumn();
        drawFMEnv(0,ins->snes.a+1,1+ins->snes.d*2,ins->snes.sus?ins->snes.d2:ins->snes.r,ins->snes.sus?ins->snes.r:31,(14-ins->snes.s*2),(ins->snes.r==0 || (ins->snes.sus && ins->snes.d2==0)),0,0,7,16,31,ImVec2(ImGui::GetContentRegionAvail().x,sliderSize.y),ins->type);

        ImGui::EndTable();
      }
      ImGui::Text(_L("Sustain/release mode:##sgiSNES"));
      if (ImGui::RadioButton(_L("Direct (cut on release)##sgiSNES"),ins->snes.sus==0)) 
      {
        ins->snes.sus=0;
      }
      if (ImGui::RadioButton(_L("Effective (linear decrease)##sgiSNES"),ins->snes.sus==1)) 
      {
        ins->snes.sus=1;
      }
      if (ImGui::RadioButton(_L("Effective (exponential decrease)##sgiSNES"),ins->snes.sus==2)) 
      {
        ins->snes.sus=2;
      }
      if (ImGui::RadioButton(_L("Delayed (write R on release)##sgiSNES"),ins->snes.sus==3)) 
      {
        ins->snes.sus=3;
      }
    } 
    else 
    {
      if (ImGui::BeginTable("SNESGainParams",2,ImGuiTableFlags_NoHostExtendX)) 
      {
        ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        CENTER_TEXT(_L("Gain Mode##sgiSNES0"));
        ImGui::TextUnformatted(_L("Gain Mode##sgiSNES1"));
        ImGui::TableNextColumn();
        CENTER_TEXT(_L("Gain##sgiSNES0"));
        ImGui::TextUnformatted(_L("Gain##sgiSNES1"));

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        if (ImGui::RadioButton(_L("Direct##sgiSNES"),ins->snes.gainMode==DivInstrumentSNES::GAIN_MODE_DIRECT)) 
        {
          ins->snes.gainMode=DivInstrumentSNES::GAIN_MODE_DIRECT;
          PARAMETER;
        }
        if (ImGui::RadioButton(_L("Decrease (linear)##sgiSNES"),ins->snes.gainMode==DivInstrumentSNES::GAIN_MODE_DEC_LINEAR)) 
        {
          ins->snes.gainMode=DivInstrumentSNES::GAIN_MODE_DEC_LINEAR;
          PARAMETER;
        }
        if (ImGui::RadioButton(_L("Decrease (logarithmic)##sgiSNES"),ins->snes.gainMode==DivInstrumentSNES::GAIN_MODE_DEC_LOG)) 
        {
          ins->snes.gainMode=DivInstrumentSNES::GAIN_MODE_DEC_LOG;
          PARAMETER;
        }
        if (ImGui::RadioButton(_L("Increase (linear)##sgiSNES"),ins->snes.gainMode==DivInstrumentSNES::GAIN_MODE_INC_LINEAR)) 
        {
          ins->snes.gainMode=DivInstrumentSNES::GAIN_MODE_INC_LINEAR;
          PARAMETER;
        }
        if (ImGui::RadioButton(_L("Increase (bent line)##sgiSNES"),ins->snes.gainMode==DivInstrumentSNES::GAIN_MODE_INC_INVLOG)) 
        {
          ins->snes.gainMode=DivInstrumentSNES::GAIN_MODE_INC_INVLOG;
          PARAMETER;
        }

        ImGui::TableNextColumn();
        unsigned char gainMax=(ins->snes.gainMode==DivInstrumentSNES::GAIN_MODE_DIRECT)?127:31;
        if (ins->snes.gain>gainMax) ins->snes.gain=gainMax;
        P(CWVSliderScalar("##Gain",sliderSize,ImGuiDataType_U8,&ins->snes.gain,&_ZERO,&gainMax)); rightClickable

        ImGui::EndTable();
      }
      if (ins->snes.gainMode==DivInstrumentSNES::GAIN_MODE_DEC_LINEAR || ins->snes.gainMode==DivInstrumentSNES::GAIN_MODE_DEC_LOG) 
      {
        ImGui::TextWrapped(_L("using decrease modes will not produce any sound at all, unless you know what you are doing.\nit is recommended to use the Gain macro for decrease instead.##sgiSNES"));
      }
    }
    ImGui::EndTabItem();
  }

  insTabWave(ins);
  insTabSample(ins);

  if (ImGui::BeginTabItem(_L("Macros##sgiSNES"))) 
  {
    panMin=0;
    panMax=127;

    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##sgiSNES"),ins,DIV_MACRO_VOL,0xff,0,127,160,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Arpeggio##sgiSNES"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Pitch##sgiSNES"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Noise Freq##sgiSNES"),ins,DIV_MACRO_DUTY,0xff,0,31,160,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Waveform##sgiSNES"),ins,DIV_MACRO_WAVE,0xff,0,WAVE_MACRO_MAX,160,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,false,NULL,true));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (left)##sgiSNES"),ins,DIV_MACRO_PAN_LEFT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER],false,(ins->type==DIV_INS_AMIGA)?macroQSoundMode:NULL));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (right)##sgiSNES"),ins,DIV_MACRO_PAN_RIGHT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER]));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Special##sgiSNES"),ins,DIV_MACRO_EX1,0xff,0,5,96,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,snesModeBits));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Gain##sgiSNES2"),ins,DIV_MACRO_EX2,0xff,0,255,256,uiColors[GUI_COLOR_MACRO_VOLUME],false,NULL,macroHoverGain,false));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}