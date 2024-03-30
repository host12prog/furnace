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

void FurnaceGUI::drawInsFZT(DivInstrument* ins)
{
  if (ImGui::BeginTabItem("FZT")) 
  {
    if (ImGui::BeginTable("FZTnote",2,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 170.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 140.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::Text(_L("Base note##sgiFZT"));
      ImGui::SameLine();
      char tempID[10];
      snprintf(tempID,10,"%s",noteNames[ins->fzt.base_note + 60]);
      if (ImGui::BeginCombo("##NN1",tempID)) 
      {
        for (int j=0; j<=MAX_NOTE; j++) 
        {
          snprintf(tempID,10,"%s",noteNames[j + 60]);
          if (ImGui::Selectable(tempID,ins->fzt.base_note==j))
          {
            ins->fzt.base_note=j;
          }
        }
        ImGui::EndCombo();
      }
      ImGui::TableNextColumn();
      ImGui::InputScalar(_L("Finetune##sgiFZT"),ImGuiDataType_S8,&ins->fzt.finetune,NULL,NULL,"%d");
      ImGui::EndTable();
    }

    ImGui::AlignTextToFramePadding();
    ImGui::Text(_L("Waveform##sgiFZT"));
    ImGui::SameLine();
    bool fztNoise = ins->fzt.waveform & SE_WAVEFORM_NOISE;
    pushToggleColors(fztNoise);
    if (ImGui::Button(_L("noise##sgiFZT"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_NOISE;
    }
    popToggleColors();
    ImGui::SameLine();
    bool fztPulse = ins->fzt.waveform & SE_WAVEFORM_PULSE;
    pushToggleColors(fztPulse);
    if (ImGui::Button(_L("pulse##sgiFZT"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_PULSE;
    }
    popToggleColors();
    ImGui::SameLine();
    bool fztTri = ins->fzt.waveform & SE_WAVEFORM_TRIANGLE;
    pushToggleColors(fztTri);
    if (ImGui::Button(_L("triangle##sgiFZT"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_TRIANGLE;
    }
    popToggleColors();
    ImGui::SameLine();
    bool fztSaw = ins->fzt.waveform & SE_WAVEFORM_SAW;
    pushToggleColors(fztSaw);
    if (ImGui::Button(_L("saw##sgiFZT"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_SAW;
    }
    popToggleColors();
    ImGui::SameLine();
    bool fztMetal = ins->fzt.waveform & SE_WAVEFORM_NOISE_METAL;
    pushToggleColors(fztMetal);
    if (ImGui::Button(_L("metal##sgiFZT"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_NOISE_METAL;
    }
    popToggleColors();
    ImGui::SameLine();
    bool fztSine = ins->fzt.waveform & SE_WAVEFORM_SINE;
    pushToggleColors(fztSine);
    if (ImGui::Button(_L("sine##sgiFZT"))) 
    { PARAMETER
      ins->fzt.waveform ^= SE_WAVEFORM_SINE;
    }
    popToggleColors();

    ImVec2 sliderSize=ImVec2(30.0f*dpiScale,256.0*dpiScale);

    if (ImGui::BeginTable("FZTEnvParams",6,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c4",ImGuiTableColumnFlags_WidthFixed,sliderSize.x);
      ImGui::TableSetupColumn("c5",ImGuiTableColumnFlags_WidthStretch);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("A##sgiFZT"));
      ImGui::TextUnformatted(_L("A##sgiFZT"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("D##sgiFZT"));
      ImGui::TextUnformatted(_L("D##sgiFZT"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("S##sgiFZT"));
      ImGui::TextUnformatted(_L("S##sgiFZT"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("R##sgiFZT"));
      ImGui::TextUnformatted(_L("R##sgiFZT"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("VOL##sgiFZT"));
      ImGui::TextUnformatted(_L("VOL##sgiFZT"));
      ImGui::TableNextColumn();
      CENTER_TEXT(_L("Envelope##sgiFZT"));
      ImGui::TextUnformatted(_L("Envelope##sgiFZT"));

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Attack",sliderSize,ImGuiDataType_U8,&ins->fzt.adsr.a,&_ZERO,&_TWO_HUNDRED_FIFTY_FIVE)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Decay",sliderSize,ImGuiDataType_U8,&ins->fzt.adsr.d,&_ZERO,&_TWO_HUNDRED_FIFTY_FIVE)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Sustain",sliderSize,ImGuiDataType_U8,&ins->fzt.adsr.s,&_ZERO,&_TWO_HUNDRED_FIFTY_FIVE)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Release",sliderSize,ImGuiDataType_U8,&ins->fzt.adsr.r,&_ZERO,&_TWO_HUNDRED_FIFTY_FIVE)); rightClickable
      ImGui::TableNextColumn();
      P(CWVSliderScalar("##Volume",sliderSize,ImGuiDataType_U8,&ins->fzt.adsr.volume,&_ZERO,&_TWO_HUNDRED_FIFTY_FIVE)); rightClickable
      ImGui::TableNextColumn();
      drawFZTEnv(255-ins->fzt.adsr.volume,(ins->fzt.adsr.a == 0 ? (255) : (256-ins->fzt.adsr.a)),(ins->fzt.adsr.d == 0 ? (255) : (256-ins->fzt.adsr.d)),255-(ins->fzt.adsr.r == 255 ? (ins->fzt.adsr.r - 1) : ins->fzt.adsr.r),255-(ins->fzt.adsr.r == 255 ? (ins->fzt.adsr.r - 1) : ins->fzt.adsr.r),255-ins->fzt.adsr.s,0,0,0,255,256,255,ImVec2(ImGui::GetContentRegionAvail().x,sliderSize.y),ins->type); //the (ins->c64.r == 15 ? (ins->c64.r - 1) : ins->c64.r) is used so release part never becomes horizontal (which isn't the case with SID envelope)

      ImGui::EndTable();
    }

    /*P(CWSliderScalar(_L("Duty##sgiSID2"),ImGuiDataType_U16,&ins->c64.duty,&_ZERO,&_FOUR_THOUSAND_NINETY_FIVE)); rightClickable

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
    }*/
    ImGui::EndTabItem();
  }

  if (ImGui::BeginTabItem(_L("Macros##sgiFZT"))) 
  {
    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##sgiFZT"),ins,DIV_MACRO_VOL,0xff,0,0xff,160,uiColors[GUI_COLOR_MACRO_VOLUME]));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}