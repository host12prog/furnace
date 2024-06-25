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
  if (ImGui::BeginTabItem(_("MultiPCM##sgiMULPCM"))) 
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
      CENTER_TEXT(_("AR##sgiMULPCM0"));
      ImGui::TextUnformatted(_("AR##sgiMULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("Attack Rate##sgiMULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_("D1R##sgiMULPCM0"));
      ImGui::TextUnformatted(_("D1R##sgiMULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("Decay 1 Rate##sgiMULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_("DL##sgiMULPCM0"));
      ImGui::TextUnformatted(_("DL##sgiMULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("Decay Level##sgiMULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_("D2R##sgiMULPCM0"));
      ImGui::TextUnformatted(_("D2R##sgiMULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("Decay 2 Rate##sgiMULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_("RR##sgiMULPCM0"));
      ImGui::TextUnformatted(_("RR##sgiMULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("Release Rate##sgiMULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_("RC##sgiMULPCM0"));
      ImGui::TextUnformatted(_("RC##sgiMULPCM1"));
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_("Rate Correction##sgiMULPCM"));
      }
      ImGui::TableNextColumn();
      CENTER_TEXT(_("Envelope##sgiMULPCM0"));
      ImGui::TextUnformatted(_("Envelope##sgiMULPCM1"));

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
      P(CWSliderScalar(_("LFO Rate##sgiMULPCM"),ImGuiDataType_U8,&ins->multipcm.lfo,&_ZERO,&_SEVEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWSliderScalar(_("PM Depth##sgiMULPCM"),ImGuiDataType_U8,&ins->multipcm.vib,&_ZERO,&_SEVEN)); rightClickable
      ImGui::TableNextColumn();
      P(CWSliderScalar(_("AM Depth##sgiMULPCM"),ImGuiDataType_U8,&ins->multipcm.am,&_ZERO,&_SEVEN)); rightClickable
      ImGui::EndTable();
    }
    ImGui::EndTabItem();
  }

  insTabSample(ins);

  if (ImGui::BeginTabItem(_("Macros##sgiMULPCM"))) 
  {
    panMin=-7;
    panMax=7;

    macroList.push_back(FurnaceGUIMacroDesc(_("Volume##sgiMULPCM"),ins,DIV_MACRO_VOL,0xff,0,127,160,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_("Arpeggio##sgiMULPCM"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_("Pitch##sgiMULPCM"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_("Panning##sgiMULPCM"),ins,DIV_MACRO_PAN_LEFT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER],false,(ins->type==DIV_INS_AMIGA)?macroQSoundMode:NULL));

    macroList.push_back(FurnaceGUIMacroDesc(_("Phase Reset##sgiMULPCM"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}