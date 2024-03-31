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
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 120.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 98.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::Text(_L("Base note##sgiFZT"));
      ImGui::SameLine();
      char tempID[10];
      snprintf(tempID,10,"%s",noteNames[ins->fzt.base_note + 60]);
      ImGui::PushItemWidth(60.0f*dpiScale);
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
      ImGui::PopItemWidth();
      ImGui::TableNextColumn();
      ImGui::PushItemWidth(40.0f*dpiScale);
      ImGui::InputScalar(_L("Finetune##sgiFZT"),ImGuiDataType_S8,&ins->fzt.finetune,NULL,NULL,"%d");
      ImGui::PopItemWidth();
      ImGui::EndTable();
    }

    if (ImGui::BeginTable("FZTslide",4,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 100.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed, 45.0f*dpiScale);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed, 90.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_L("Slide speed##sgiFZT"),ImGuiDataType_U8,&ins->fzt.slide_speed,NULL,NULL,"%02X");
      ImGui::PopItemWidth();
      ImGui::TableNextColumn();
      bool fztSetPw = ins->fzt.flags & TE_SET_PW;
      if (ImGui::Checkbox(_L("Set PW##sgiFZT"),&fztSetPw)) 
      {
        ins->fzt.flags ^= TE_SET_PW;
      }
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("Set pulse width on keydown##sgiFZT"));
      }
      ImGui::TableNextColumn();
      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar("",ImGuiDataType_U8,&ins->fzt.pw,NULL,NULL,"%02X");
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("Initial pulse width##sgiFZT"));
      }
      ImGui::PopItemWidth();
      ImGui::TableNextColumn();
      bool fztSetCut = ins->fzt.flags & TE_SET_CUTOFF;
      if (ImGui::Checkbox(_L("Set cutoff##sgiFZT"),&fztSetCut)) 
      {
        ins->fzt.flags ^= TE_SET_CUTOFF;
      }
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("Set filter cutoff on keydown##sgiFZT"));
      }
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

    if (ImGui::BeginTable("FZTfilt",4,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 100.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed, 120.0f*dpiScale);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed, 220.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      bool fztSetPw = ins->fzt.sound_engine_flags & SE_ENABLE_FILTER;
      if (ImGui::Checkbox(_L("Enable filter##sgiFZT"),&fztSetPw)) 
      {
        ins->fzt.sound_engine_flags ^= SE_ENABLE_FILTER;
      }

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_L("Cutoff##sgiFZT"),ImGuiDataType_U8,&ins->fzt.filter_cutoff,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_L("Resonance##sgiFZT"),ImGuiDataType_U8,&ins->fzt.filter_resonance,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::Text(_L("Type##sgiFZT"));
      ImGui::SameLine();
      ImGui::PushItemWidth(140.0f*dpiScale);
      char tempID[40];
      snprintf(tempID,40,"%s",_L(fztFilterModes[ins->fzt.filter_type]));
      if (ImGui::BeginCombo("##NNN1",tempID)) 
      {
        for (int j=0; j<8; j++) 
        {
          snprintf(tempID,40,"%s",_L(fztFilterModes[j]));
          if (ImGui::Selectable(tempID,ins->fzt.filter_type==j))
          {
            ins->fzt.filter_type=j;
          }
        }
        ImGui::EndCombo();
      }
      ImGui::PopItemWidth();

      ImGui::EndTable();
    }

    if (ImGui::BeginTable("FZThard",4,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 160.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 130.0f*dpiScale);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed, 140.0f*dpiScale);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed, 130.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      bool fztRing = ins->fzt.sound_engine_flags & SE_ENABLE_RING_MOD;
      if (ImGui::Checkbox(_L("Enable ring modulation##sgiFZT"),&fztRing)) 
      {
        ins->fzt.sound_engine_flags ^= SE_ENABLE_RING_MOD;
      }

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_L("Ring mod source##sgiFZT"),ImGuiDataType_U8,&ins->fzt.ring_mod,NULL,NULL,"%02X");
      ImGui::PopItemWidth();
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("FF = self-modulation##sgiFZT"));
      }

      ImGui::TableNextColumn();

      bool fztSync = ins->fzt.sound_engine_flags & SE_ENABLE_HARD_SYNC;
      if (ImGui::Checkbox(_L("Enable hard sync##sgiFZT"),&fztSync)) 
      {
        ins->fzt.sound_engine_flags ^= SE_ENABLE_HARD_SYNC;
      }

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_L("Hard sync source##sgiFZT"),ImGuiDataType_U8,&ins->fzt.hard_sync,NULL,NULL,"%02X");
      ImGui::PopItemWidth();
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("FF = self-sync##sgiFZT"));
      }

      ImGui::EndTable();
    }

    if (ImGui::BeginTable("FZTsli",2,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 160.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 160.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      bool fztSlRetrig = ins->fzt.flags & TE_RETRIGGER_ON_SLIDE;
      if (ImGui::Checkbox(_L("Retrigger on slide##sgiFZT"),&fztSlRetrig)) 
      {
        ins->fzt.flags ^= TE_RETRIGGER_ON_SLIDE;
      }
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("Restart instrument and envelope even if slide command (03xx) is placed with the note.##sgiFZT"));
      }

      ImGui::TableNextColumn();

      bool fztKeySync = ins->fzt.sound_engine_flags & SE_ENABLE_KEYDOWN_SYNC;
      if (ImGui::Checkbox(_L("Sync osc. on keydown##sgiFZT"),&fztKeySync)) 
      {
        ins->fzt.sound_engine_flags ^= SE_ENABLE_KEYDOWN_SYNC;
      }
      if (ImGui::IsItemHovered()) 
      {
        ImGui::SetTooltip(_L("Reset phase of oscillator each time new note is played.\nDoes not happen when slide (03xx) or legato command is placed.##sgiFZT"));
      }

      ImGui::EndTable();
    }

    if (ImGui::BeginTable("FZTvib",4,ImGuiTableFlags_NoHostExtendX))
    {
      ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);
      ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);
      ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthFixed, 70.0f*dpiScale);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      bool fztVib = ins->fzt.flags & TE_ENABLE_VIBRATO;
      if (ImGui::Checkbox(_L("Vibrato##sgiFZT"),&fztVib)) 
      {
        ins->fzt.flags ^= TE_ENABLE_VIBRATO;
      }

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_L("Speed##sgiFZT0"),ImGuiDataType_U8,&ins->fzt.vibrato_speed,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_L("Depth##sgiFZT0"),ImGuiDataType_U8,&ins->fzt.vibrato_depth,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_L("Delay##sgiFZT0"),ImGuiDataType_U8,&ins->fzt.vibrato_delay,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      bool fztPwm = ins->fzt.flags & TE_ENABLE_PWM;
      if (ImGui::Checkbox(_L("PWM##sgiFZT"),&fztPwm)) 
      {
        ins->fzt.flags ^= TE_ENABLE_PWM;
      }

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_L("Speed##sgiFZT1"),ImGuiDataType_U8,&ins->fzt.pwm_speed,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_L("Depth##sgiFZT1"),ImGuiDataType_U8,&ins->fzt.pwm_depth,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::TableNextColumn();

      ImGui::PushItemWidth(25.0f*dpiScale);
      ImGui::InputScalar(_L("Delay##sgiFZT1"),ImGuiDataType_U8,&ins->fzt.pwm_delay,NULL,NULL,"%02X");
      ImGui::PopItemWidth();

      ImGui::EndTable();
    }

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

    ImGui::EndTabItem();
  }

  if (ImGui::BeginTabItem(_L("Instrument program##sgiFZT"))) 
  {
    ImGui::PushItemWidth(25.0f*dpiScale);
    ImGui::InputScalar(_L("Program period##sgiFZT"),ImGuiDataType_U8,&ins->fzt.program_period,NULL,NULL,"%02X");
    ImGui::PopItemWidth();

    ImGui::EndTabItem();
  }

  if (ImGui::BeginTabItem(_L("Macros##sgiFZT"))) 
  {
    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##sgiFZT"),ins,DIV_MACRO_VOL,0xff,0,0xff,160,uiColors[GUI_COLOR_MACRO_VOLUME]));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}