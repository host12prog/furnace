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

void FurnaceGUI::drawInsMULTIPCM(DivInstrument* ins)
{
  if (ImGui::BeginTabItem("MultiPCM")) 
  {
    ImVec2 sliderSize=ImVec2(20.0f*dpiScale,128.0*dpiScale);
    if (ImGui::BeginTable("MultiPCMADSRParams",7,ImGuiTableFlags_NoHostExtendX)) 
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c4",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c5",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c6",ImGuiTableColumnFlags_WidthStretch);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("AR##MULPCM0"));
      ImGui::TextUnformatted(_L("AR##MULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("Attack Rate##MULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("D1R##MULPCM0"));
      ImGui::TextUnformatted(_L("D1R##MULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("Decay 1 Rate##MULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("DL##MULPCM0"));
      ImGui::TextUnformatted(_L("DL##MULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("Decay Level##MULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("D2R##MULPCM0"));
      ImGui::TextUnformatted(_L("D2R##MULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("Decay 2 Rate##MULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("RR##MULPCM0"));
      ImGui::TextUnformatted(_L("RR##MULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("Release Rate##MULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("RC##MULPCM0"));
      ImGui::TextUnformatted(_L("RC##MULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("Rate Correction##MULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("Envelope##MULPCM0"));
      ImGui::TextUnformatted(_L("Envelope##MULPCM1"));

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Attack Rate",sliderSize,ImGuiDataType_U8,&ins->multipcm.ar,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Decay 1 Rate",sliderSize,ImGuiDataType_U8,&ins->multipcm.d1r,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Decay Level",sliderSize,ImGuiDataType_U8,&ins->multipcm.dl,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Decay 2 Rate",sliderSize,ImGuiDataType_U8,&ins->multipcm.d2r,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Release Rate",sliderSize,ImGuiDataType_U8,&ins->multipcm.rr,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Rate Correction",sliderSize,ImGuiDataType_U8,&ins->multipcm.rc,&_ZERO,&_FIFTEEN)); rightClickable
      ImGui::TableNextColumn();
      drawFMEnv(0,ins->multipcm.ar,ins->multipcm.d1r,ins->multipcm.d2r,ins->multipcm.rr,ins->multipcm.dl,0,0,0,127,15,15,ImVec2(ImGui::GetContentRegionAvail().x,sliderSize.y),ins->type);
      ImGui::EndTable();
    }

    if (ImGui::BeginTable("MultiPCMLFOParams",3,ImGuiTableFlags_SizingStretchSame)) 
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthStretch,0.0);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthStretch,0.0);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthStretch,0.0);
      ImGui::TableNextColumn();
      P(CWSliderScalar(_L("LFO Rate##MULPCM"),ImGuiDataType_U8,&ins->multipcm.lfo,&_ZERO,&_SEVEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWSliderScalar(_L("PM Depth##MULPCM"),ImGuiDataType_U8,&ins->multipcm.vib,&_ZERO,&_SEVEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWSliderScalar(_L("AM Depth##MULPCM"),ImGuiDataType_U8,&ins->multipcm.am,&_ZERO,&_SEVEN)); rightClickable
      ImGui::EndTable();
    }
    ImGui::EndTabItem();
  }

  insTabSample(ins);

  if (ImGui::BeginTabItem(_L("Macros##MULPCM"))) 
  {
    panMin=-7;
    panMax=7;

    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##MULPCM"),ins,DIV_MACRO_VOL,0xff,0,127,160,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Arpeggio##MULPCM"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,0,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Pitch##MULPCM"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Panning##MULPCM"),ins,DIV_MACRO_PAN_LEFT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER],false,(ins->type==DIV_INS_AMIGA)?macroQSoundMode:NULL));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Phase Reset##MULPCM"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}