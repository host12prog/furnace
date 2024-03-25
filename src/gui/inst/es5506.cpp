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

#include "../../engine/platform/es5506.h"

class FurnaceGUI;

const char* friendly_filter_modes[] = 
{
  "Off",
  "6dB/oct lowpass",
  "12dB/oct lowpass",
  "18dB/oct lowpass",
  "24dB/oct lowpass",
  "6dB/oct highpass",
  "12dB/oct highpass",
  "12dB/oct lowpass + 12dB/oct lowpass",
  "18dB/oct lowpass + 6dB/oct lowpass",
  "12dB/oct lowpass + 12dB/oct highpass",
  "18dB/oct lowpass + 6dB/oct highpass",
  NULL
};

void FurnaceGUI::drawInsES5506(DivInstrument* ins)
{
  if (ImGui::BeginTabItem("ES5506")) 
  {
    //bool friendly = ins->es5506.friendly_mode;
    //ImGui::Checkbox("Friendly insrument editor", &ins->es5506.friendly_mode);
    //ImGui::Separator();
    
    /*if(friendly)
    {
      ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x-ImGui::CalcTextSize("Filter Mode").x);
      ImGui::Text("Filter Mode");
      ImGui::SameLine();
      if (ImGui::BeginCombo("##filtModes",friendly_filter_modes[ins->es5506.filter.virtual_filter_mode]))
      {
        int j = 0;
        while(friendly_filter_modes[j])
        {
          if (ImGui::Selectable(friendly_filter_modes[j]))
          {
            //ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)j;
            ins->es5506.filter.virtual_filter_mode = j;

            switch(j)
            {
              case 6:
              case 9: //nice?
              {
                ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)0;
                break;
              }
              case 5:
              case 10:
              {
                ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)1;
                break;
              }
              case 0:
              case 2:
              case 4:
              case 7:
              {
                ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)2;
                break;
              }
              case 1:
              case 3:
              case 8:
              {
                ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)3;
                break;
              }
              default: break;
            }
          }

          j++;
        }

        ImGui::EndCombo();
      }

      float N1 = 0.0;
      float N2 = 0.0;

      int max_cutoff1 = 0;
      int max_cutoff2 = 0;

      switch(ins->es5506.filter.virtual_filter_mode)
      {
        case 0:
        {
          ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)2;
          ins->es5506.filter.k1 = 65535;
          ins->es5506.filter.k2 = 65535;
          break;
        }
        case 1:
        {
          ins->es5506.filter.k1 = 65535;
          N1 = 0.7071f;
          ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)3;
          max_cutoff1 = DivPlatformES5506::calc_f_from_k(N1, 65536, 16000000 / (16*(32+1)), false);
          break;
        }
        case 2:
        {
          ins->es5506.filter.k2 = 65535;
          N1 = 0.8409f;
          ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)2;
          max_cutoff1 = DivPlatformES5506::calc_f_from_k(N1, 65536, 16000000 / (16*(32+1)), false); //WHYYYYY??Y?Y?Y?Y???
          break;
        }
        case 3:
        {
          ins->es5506.filter.k2 = 65535;
          N1 = 0.8909f;
          ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)3;
          max_cutoff1 = DivPlatformES5506::calc_f_from_k(N1, 65536, 16000000 / (16*(32+1)), false);
          break;
        }
        case 4: //both k1 and k2 are assigned the cutoff1 param
        {
          N1 = 0.9170f;
          ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)2;
          max_cutoff1 = DivPlatformES5506::calc_f_from_k(N1, 65536, 16000000 / (16*(32+1)), false);
          break;
        }
        case 5:
        {
          ins->es5506.filter.k1 = 65535;
          N1 = 0.7071f;
          ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)1;
          max_cutoff1 = DivPlatformES5506::calc_f_from_k(N1, 65535, 16000000 / (16*(32+1)), true);
          break;
        }
        case 6:
        {
          ins->es5506.filter.k1 = 65535;
          N1 = 0.8409f;
          ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)0;
          max_cutoff1 = DivPlatformES5506::calc_f_from_k(N1, 65535, 16000000 / (16*(32+1)), true);
          break;
        }
        case 7:
        {
          N1 = 0.8409f;
          N2 = 0.8409f;
          ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)2;
          max_cutoff1 = DivPlatformES5506::calc_f_from_k(N1, 65536, 16000000 / (16*(32+1)), false);
          max_cutoff2 = DivPlatformES5506::calc_f_from_k(N2, 65536, 16000000 / (16*(32+1)), false);
          break;
        }
        case 8:
        {
          N1 = 0.8909f;
          N2 = 0.7071f;
          ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)3;
          max_cutoff1 = DivPlatformES5506::calc_f_from_k(N1, 65536, 16000000 / (16*(32+1)), false);
          max_cutoff2 = DivPlatformES5506::calc_f_from_k(N2, 65536, 16000000 / (16*(32+1)), false);
          break;
        }
        case 9:
        {
          N1 = 0.8409f;
          N2 = 0.8409f;
          ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)0;
          max_cutoff1 = DivPlatformES5506::calc_f_from_k(N1, 65536, 16000000 / (16*(32+1)), false);
          max_cutoff2 = DivPlatformES5506::calc_f_from_k(N2, 65535, 16000000 / (16*(32+1)), true);
          break;
        }
        case 10:
        {
          N1 = 0.8909f;
          N2 = 0.7071f;
          ins->es5506.filter.mode = (DivInstrumentES5506::Filter::FilterMode)1;
          max_cutoff1 = DivPlatformES5506::calc_f_from_k(N1, 65536, 16000000 / (16*(32+1)), false);
          max_cutoff2 = DivPlatformES5506::calc_f_from_k(N2, 65535, 16000000 / (16*(32+1)), true);
          break;
        }
        default: break;
      }

      max_cutoff1 = abs(max_cutoff1);
      max_cutoff2 = abs(max_cutoff2);

      if(ins->es5506.filter.virtual_filter_mode >= 1 && ins->es5506.filter.virtual_filter_mode <= 6)
      {
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x-ImGui::CalcTextSize("Cutoff (Hz)").x);

        switch(ins->es5506.filter.virtual_filter_mode)
        {
          case 1:
          case 4:
          case 5:
          case 6: 
          {
            //if(ins->es5506.filter.k2 > max_cutoff1) ins->es5506.filter.k2 = max_cutoff1;
            P(CWSliderScalar("Cutoff (Hz)",ImGuiDataType_U16,&ins->es5506.filter.k2,&_ZERO,(const void*)&max_cutoff1)); rightClickable
            break;
          }

          case 2:
          case 3:
          {
            //if(ins->es5506.filter.k1 > max_cutoff1) ins->es5506.filter.k1 = max_cutoff1;
            P(CWSliderScalar("Cutoff (Hz)",ImGuiDataType_U16,&ins->es5506.filter.k1,&_ZERO,(const void*)&max_cutoff1)); rightClickable
            break;
          }
          default: break;
        }
      }

      if (ImGui::BeginTable("ESParams",2,ImGuiTableFlags_SizingStretchSame)) 
      {
        ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthStretch,0.0);
        ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthStretch,0.0);
        // filter
        if(ins->es5506.filter.virtual_filter_mode > 6)
        {
          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          //max_cutoff1 = DivPlatformES5506::calc_f_from_k(0.7071, 65534, 16000000 / (16*(32+1)), false); //doesn't work
          //if(ins->es5506.filter.k1 > max_cutoff1) ins->es5506.filter.k1 = max_cutoff1;
          //if(ins->es5506.filter.k2 > max_cutoff2) ins->es5506.filter.k2 = max_cutoff2;
          P(CWSliderScalar("Cutoff 1 (Hz)",ImGuiDataType_U16,&ins->es5506.filter.k1,&_ZERO,(const void*)&max_cutoff1)); rightClickable
          ImGui::TableNextColumn();
          P(CWSliderScalar("Cutoff 2 (Hz)",ImGuiDataType_U16,&ins->es5506.filter.k2,&_ZERO,(const void*)&max_cutoff2)); rightClickable
        }

        // envelope
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Envelope count##sgiOTTO"),ImGuiDataType_U16,&ins->es5506.envelope.ecount,&_ZERO,&_FIVE_HUNDRED_ELEVEN)); rightClickable
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Left Volume Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.lVRamp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Right Volume Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.rVRamp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Filter K1 Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.k1Ramp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Filter K2 Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.k2Ramp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Checkbox(_L("K1 Ramp Slowdown##sgiOTTO"),&ins->es5506.envelope.k1Slow);
        ImGui::TableNextColumn();
        ImGui::Checkbox(_L("K2 Ramp Slowdown##sgiOTTO"),&ins->es5506.envelope.k2Slow);
        ImGui::EndTable();
      }
    }*/
    //else
    //{
      if (ImGui::BeginTable("ESParams",2,ImGuiTableFlags_SizingStretchSame)) 
      {
        ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthStretch,0.0);
        ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthStretch,0.0);
        // filter
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Filter Mode##sgiOTTO0"),ImGuiDataType_U8,&ins->es5506.filter.mode,&_ZERO,&_THREE,_L(es5506FilterModes[ins->es5506.filter.mode&3])));
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Filter K1##sgiOTTO0"),ImGuiDataType_U16,&ins->es5506.filter.k1,&_ZERO,&_SIXTY_FIVE_THOUSAND_FIVE_HUNDRED_THIRTY_FIVE)); rightClickable
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Filter K2##sgiOTTO0"),ImGuiDataType_U16,&ins->es5506.filter.k2,&_ZERO,&_SIXTY_FIVE_THOUSAND_FIVE_HUNDRED_THIRTY_FIVE)); rightClickable
        // envelope
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Envelope length##sgiOTTO"),ImGuiDataType_U16,&ins->es5506.envelope.ecount,&_ZERO,&_FIVE_HUNDRED_ELEVEN)); rightClickable
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Left Volume Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.lVRamp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Right Volume Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.rVRamp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Filter K1 Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.k1Ramp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
        ImGui::TableNextColumn();
        P(CWSliderScalar(_L("Filter K2 Ramp##sgiOTTO"),ImGuiDataType_S8,&ins->es5506.envelope.k2Ramp,&_MINUS_ONE_HUNDRED_TWENTY_EIGHT,&_ONE_HUNDRED_TWENTY_SEVEN)); rightClickable
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Checkbox(_L("K1 Ramp Slowdown##sgiOTTO"),&ins->es5506.envelope.k1Slow);
        ImGui::TableNextColumn();
        ImGui::Checkbox(_L("K2 Ramp Slowdown##sgiOTTO"),&ins->es5506.envelope.k2Slow);
        ImGui::EndTable();
      }
    //}

    ImGui::EndTabItem();
  }

  insTabSample(ins);

  if (ImGui::BeginTabItem(_L("Macros##sgiOTTO"))) 
  {
    panMin=0;
    panMax=4095;

    macroList.push_back(FurnaceGUIMacroDesc(_L("Volume##sgiOTTO"),ins,DIV_MACRO_VOL,0xff,0,4095,160,uiColors[GUI_COLOR_MACRO_VOLUME]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Arpeggio##sgiOTTO"),ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Pitch##sgiOTTO"),ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (left)##sgiOTTO"),ins,DIV_MACRO_PAN_LEFT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER],false,(ins->type==DIV_INS_AMIGA)?macroQSoundMode:NULL));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Panning (right)##sgiOTTO"),ins,DIV_MACRO_PAN_RIGHT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Phase Reset##sgiOTTO"),ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Filter Mode##sgiOTTO1"),ins,DIV_MACRO_DUTY,0xff,0,3,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,&macroHoverES5506FilterMode));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Filter K1##sgiOTTO1"),ins,DIV_MACRO_EX1,0xff,((ins->std.get_macro(DIV_MACRO_EX1, true)->mode==1)?(-65535):0),65535,160,uiColors[GUI_COLOR_MACRO_OTHER],false,macroRelativeMode));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Filter K2##sgiOTTO1"),ins,DIV_MACRO_EX2,0xff,((ins->std.get_macro(DIV_MACRO_EX2, true)->mode==1)?(-65535):0),65535,160,uiColors[GUI_COLOR_MACRO_OTHER],false,macroRelativeMode));

    macroList.push_back(FurnaceGUIMacroDesc(_L("Outputs##sgiOTTO"),ins,DIV_MACRO_FB, 0xff,0,5,64,uiColors[GUI_COLOR_MACRO_OTHER]));
    macroList.push_back(FurnaceGUIMacroDesc(_L("Control##sgiOTTO"),ins,DIV_MACRO_ALG,0xff,0,2,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,es5506ControlModes));

    drawMacros(macroList,macroEditStateMacros);
    ImGui::EndTabItem();
  }
}