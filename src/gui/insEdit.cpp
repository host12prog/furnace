/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2023 tildearrow and contributors
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

#define _USE_MATH_DEFINES
#include "gui.h"
#include "../ta-log.h"
#include "imgui_internal.h"
#include "../engine/macroInt.h"
#include "IconsFontAwesome4.h"
#include "furIcons.h"
#include "misc/cpp/imgui_stdlib.h"
#include "guiConst.h"
#include "intConst.h"
#include <fmt/printf.h>
#include <imgui.h>
#include "plot_nolerp.h"

#include "inst/macroDraw.h"
#include "inst/stringsUtil.h"
#include "inst/sampleDraw.h"
#include "inst/fmEnvUtil.h"

#include "inst/publicVars.h"
#include "inst/fmPublicVars.h"

#include "inst/fm.h"

extern "C" {
#include "../../extern/Nuked-OPLL/opll.h"
}

void FurnaceGUI::drawActualInsEditor()
{
  DivInstrument* ins=e->song.ins[curIns];
  if (updateFMPreview) {
    renderFMPreview(ins);
    updateFMPreview=false;
  }
  if (settings.insEditColorize) {
    if (ins->type>=DIV_INS_MAX) {
      pushAccentColors(uiColors[GUI_COLOR_INSTR_UNKNOWN],uiColors[GUI_COLOR_INSTR_UNKNOWN],uiColors[GUI_COLOR_INSTR_UNKNOWN],ImVec4(0.0f,0.0f,0.0f,0.0f));
    } else {
      pushAccentColors(uiColors[GUI_COLOR_INSTR_STD+ins->type],uiColors[GUI_COLOR_INSTR_STD+ins->type],uiColors[GUI_COLOR_INSTR_STD+ins->type],ImVec4(0.0f,0.0f,0.0f,0.0f));
    }
  }
  if (ImGui::BeginTable("InsProp",3)) {
    ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    String insIndex=fmt::sprintf("%.2X",curIns);
    ImGui::SetNextItemWidth(72.0f*dpiScale);
    if (ImGui::BeginCombo("##InsSelect",insIndex.c_str())) {
      String name;
      for (size_t i=0; i<e->song.ins.size(); i++) {
        name=fmt::sprintf("%.2X: %s##_INSS%d",i,e->song.ins[i]->name,i);
        if (ImGui::Selectable(name.c_str(),curIns==(int)i)) {
          curIns=i;
          ins=e->song.ins[curIns];
          wavePreviewInit=true;
          updateFMPreview=true;
        }
      }
      ImGui::EndCombo();
    }

    ImGui::TableNextColumn();
    ImGui::Text("Name");

    ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    ImGui::PushID(2+curIns);
    if (ImGui::InputText("##Name",&ins->name)) {
      MARK_MODIFIED;
    }
    ImGui::PopID();

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    if (ImGui::Button(ICON_FA_FOLDER_OPEN "##IELoad")) {
      doAction(GUI_ACTION_INS_LIST_OPEN_REPLACE);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip("Open");
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FLOPPY_O "##IESave")) {
      doAction(GUI_ACTION_INS_LIST_SAVE);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip("Save");
    }
    if (ImGui::BeginPopupContextItem("InsSaveFormats",ImGuiMouseButton_Right)) {
      if (ImGui::MenuItem("save as .dmp...")) {
        doAction(GUI_ACTION_INS_LIST_SAVE_DMP);
      }
      ImGui::EndPopup();
    }

    ImGui::TableNextColumn();
    ImGui::Text("Type");

    ImGui::TableNextColumn();
    int insType=ins->type;
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    bool warnType=true;
    for (DivInstrumentType i: e->getPossibleInsTypes()) {
      if (i==insType) {
        warnType=false;
      }
    }

    pushWarningColor(warnType,warnType && failedNoteOn);
    if (ImGui::BeginCombo("##Type",(insType>=DIV_INS_MAX)?"Unknown":insTypes[insType][0])) {
      std::vector<DivInstrumentType> insTypeList;
      if (settings.displayAllInsTypes) {
        for (int i=0; insTypes[i][0]; i++) {
          insTypeList.push_back((DivInstrumentType)i);
        }
      } else {
        insTypeList=e->getPossibleInsTypes();
      }
      for (DivInstrumentType i: insTypeList) {
        if (ImGui::Selectable(insTypes[i][0],insType==i)) {
          ins->type=i;

          // reset macro zoom
          
          for(int i = 0; i < (int)ins->std.macros.size(); i++)
          {
            ins->std.macros[i].vZoom = -1;
          }

          for(int j = 0; j < (int)ins->std.ops.size(); j++)
          {
            for(int i = 0; i < (int)ins->std.ops[j].macros.size(); i++)
            {
              ins->std.ops[j].macros[i].vZoom = -1;
            }
          }
        }
      }
      ImGui::EndCombo();
    } else if (warnType) {
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("none of the currently present chips are able to play this instrument type!");
      }
    }
    popWarningColor();

    ImGui::EndTable();
  }

  if (ImGui::BeginTabBar("insEditTab")) 
  {
    macroList.clear();
    macroList.shrink_to_fit();

    switch(ins->type)
    {
      case DIV_INS_FM:
      {
        drawInsOPN(ins); break;
      }

      case DIV_INS_OPM:
      {
        drawInsOPM(ins); break;
      }

      case DIV_INS_OPZ:
      {
        drawInsOPZ(ins); break;
      }

      case DIV_INS_ESFM:
      {
        drawInsESFM(ins); break;
      }

      case DIV_INS_OPL:
      case DIV_INS_OPL_DRUMS:
      {
        drawInsOPL(ins); break;
      }

      case DIV_INS_OPLL:
      {
        drawInsOPLL(ins); break;
      }

      case DIV_INS_GB:
      {
        drawInsGB(ins); break;
      }

      case DIV_INS_C64:
      {
        drawInsC64(ins); break;
      }

      case DIV_INS_ES5503:
      {
        drawInsES5503(ins); break;
      }

      case DIV_INS_SU:
      {
        drawInsSU(ins); break;
      }

      case DIV_INS_N163:
      {
        drawInsN163(ins); break;
      }

      case DIV_INS_FDS:
      {
        drawInsFDS(ins); break;
      }

      case DIV_INS_VBOY:
      {
        drawInsVBOY(ins); break;
      }

      case DIV_INS_ES5506:
      {
        drawInsES5506(ins); break;
      }

      case DIV_INS_MULTIPCM:
      {
        drawInsMULTIPCM(ins); break;
      }

      case DIV_INS_SNES:
      {
        drawInsSNES(ins); break;
      }

      case DIV_INS_ADPCMA:
      {
        drawInsADPCMA(ins); break;
      }

      case DIV_INS_ADPCMB:
      {
        drawInsADPCMB(ins); break;
      }

      case DIV_INS_AMIGA:
      {
        drawInsAmiga(ins); break;
      }

      case DIV_INS_AY:
      {
        drawInsAY(ins); break;
      }

      case DIV_INS_AY8930:
      {
        drawInsAY8930(ins); break;
      }

      case DIV_INS_BEEPER:
      {
        drawInsBEEPER(ins); break;
      }

      case DIV_INS_C140:
      {
        drawInsC140(ins); break;
      }

      case DIV_INS_C219:
      {
        drawInsC219(ins); break;
      }

      case DIV_INS_GA20:
      {
        drawInsGA20(ins); break;
      }

      case DIV_INS_K007232:
      {
        drawInsK007232(ins); break;
      }

      default: break;
    }

    if (ins->type==DIV_INS_MSM6258 ||
        ins->type==DIV_INS_MSM6295 ||
        ins->type==DIV_INS_ADPCMA ||
        ins->type==DIV_INS_ADPCMB ||
        ins->type==DIV_INS_SEGAPCM ||
        ins->type==DIV_INS_QSOUND ||
        ins->type==DIV_INS_YMZ280B ||
        ins->type==DIV_INS_RF5C68 ||
        ins->type==DIV_INS_AMIGA ||
        ins->type==DIV_INS_MULTIPCM ||
        ins->type==DIV_INS_SU ||
        ins->type==DIV_INS_SNES ||
        ins->type==DIV_INS_ES5506 ||
        ins->type==DIV_INS_K007232 ||
        ins->type==DIV_INS_GA20 ||
        ins->type==DIV_INS_K053260 ||
        ins->type==DIV_INS_C140 ||
        ins->type==DIV_INS_C219) {
      //insTabSample(ins);
    }
    
    if (ins->type==DIV_INS_GB ||
        (ins->type==DIV_INS_AMIGA && ins->amiga.useWave) ||
        (ins->type==DIV_INS_X1_010 && !ins->amiga.useSample) ||
        ins->type==DIV_INS_N163 ||
        ins->type==DIV_INS_FDS ||
        (ins->type==DIV_INS_SWAN && !ins->amiga.useSample) ||
        (ins->type==DIV_INS_PCE && !ins->amiga.useSample) ||
        (ins->type==DIV_INS_ES5503 && !ins->amiga.useSample) ||
        (ins->type==DIV_INS_VBOY) ||
        ins->type==DIV_INS_SCC ||
        ins->type==DIV_INS_SNES ||
        ins->type==DIV_INS_NAMCO ||
        ins->type==DIV_INS_SM8521) 
        {
          //insTabWave(ins);
        }
        
    if (ins->type>DIV_INS_MAX) if (ImGui::BeginTabItem("Macros")) {
      //const char* volumeLabel="Volume";

      volMax=15;
      volMin=0;
      if (ins->type==DIV_INS_PCE || ins->type==DIV_INS_AY8930 || ins->type==DIV_INS_SM8521) {
        volMax=31;
      }
      if (ins->type==DIV_INS_OPL || ins->type==DIV_INS_OPL_DRUMS || ins->type==DIV_INS_VERA || ins->type==DIV_INS_VRC6_SAW || ins->type==DIV_INS_ESFM) {
        volMax=63;
      }
      if (ins->type==DIV_INS_AMIGA) {
        volMax=64;
      }
      if (ins->type==DIV_INS_FM || ins->type==DIV_INS_SEGAPCM || ins->type==DIV_INS_MIKEY ||
          ins->type==DIV_INS_MULTIPCM || ins->type==DIV_INS_SU || ins->type==DIV_INS_OPZ ||
          ins->type==DIV_INS_OPM || ins->type==DIV_INS_SNES || ins->type==DIV_INS_MSM5232 ||
          ins->type==DIV_INS_K053260) {
        volMax=127;
      }
      if (ins->type==DIV_INS_GB) {
        if (ins->gb.softEnv) {
          volMax=15;
        } else {
          volMax=0;
        }
      }
      if (ins->type==DIV_INS_PET || ins->type==DIV_INS_BEEPER || ins->type==DIV_INS_PV1000) {
        volMax=1;
      }
      if (ins->type==DIV_INS_FDS) {
        volMax=32;
      }
      if (ins->type==DIV_INS_ES5506) {
        volMax=4095;
      }
      if (ins->type==DIV_INS_MSM6258) {
        volMax=0;
      }
      if (ins->type==DIV_INS_MSM6295 || ins->type==DIV_INS_TED) {
        volMax=8;
      }
      if (ins->type==DIV_INS_ADPCMA) {
        volMax=31;
      }
      if (ins->type==DIV_INS_ADPCMB || ins->type==DIV_INS_YMZ280B || ins->type==DIV_INS_RF5C68 ||
          ins->type==DIV_INS_GA20 || ins->type==DIV_INS_C140 || ins->type==DIV_INS_C219 || ins->type==DIV_INS_ES5503) {
        volMax=255;
      }
      if (ins->type==DIV_INS_QSOUND) {
        volMax=16383;
      }
      if (ins->type==DIV_INS_POKEMINI) {
        volMax=2;
      }

      //const char* dutyLabel="Duty/Noise";
      dutyMin=0;
      dutyMax=3;
      if (ins->type==DIV_INS_C64) {
        dutyLabel="Duty";
        if (ins->c64.dutyIsAbs) {
          dutyMax=4095;
        } else {
          dutyMin=-4095;
          dutyMax=4095;
        }
      }
      if (ins->type==DIV_INS_STD) {
        dutyLabel="Duty";
      }
      if (ins->type==DIV_INS_OPM || ins->type==DIV_INS_OPZ) {
        dutyMax=32;
      }
      if (ins->type==DIV_INS_AY) {
        dutyMax=ins->amiga.useSample?0:31;
      }
      if (ins->type==DIV_INS_AY || ins->type==DIV_INS_AY8930 || ins->type==DIV_INS_FM || ins->type==DIV_INS_OPM) {
        dutyLabel="Noise Freq";
      }
      if (ins->type==DIV_INS_POKEY) {
        dutyLabel="AUDCTL";
        dutyMax=8;
      }
      if (ins->type==DIV_INS_MIKEY) {
        dutyLabel="Duty/Int";
        dutyMax=ins->amiga.useSample?0:10;
      }
      if (ins->type==DIV_INS_MSM5232) {
        dutyLabel="Group Ctrl";
        dutyMax=5;
      }
      if (ins->type==DIV_INS_C219) {
        dutyLabel="Control";
        dutyMax=3;
      }
      if (ins->type==DIV_INS_BEEPER || ins->type==DIV_INS_POKEMINI) {
        dutyLabel="Pulse Width";
        dutyMax=255;
      }
      if (ins->type==DIV_INS_T6W28) {
        dutyLabel="Noise Type";
        dutyMax=1;
      }
      if (ins->type==DIV_INS_AY8930) {
        dutyMax=ins->amiga.useSample?0:255;
      }
      if (ins->type==DIV_INS_TIA || ins->type==DIV_INS_AMIGA || ins->type==DIV_INS_SCC ||
          ins->type==DIV_INS_PET || ins->type==DIV_INS_SEGAPCM ||
          ins->type==DIV_INS_FM || ins->type==DIV_INS_K007232 || ins->type==DIV_INS_GA20 ||
          ins->type==DIV_INS_SM8521 || ins->type==DIV_INS_PV1000 || ins->type==DIV_INS_K053260 ||
          ins->type==DIV_INS_C140) {
        dutyMax=0;
      }
      if (ins->type==DIV_INS_VBOY) {
        dutyLabel="Noise Length";
        dutyMax=7;
      }
      if (ins->type==DIV_INS_PCE) {
        dutyLabel="Noise";
        dutyMax=(!ins->amiga.useSample)?1:0;
      }
      if (ins->type==DIV_INS_NAMCO) {
        dutyLabel="Noise";
        dutyMax=1;
      }
      if (ins->type==DIV_INS_VIC) {
        dutyLabel="On/Off";
        dutyMax=1;
      }
      if (ins->type==DIV_INS_TED) {
        dutyLabel="Square/Noise";
        dutyMax=2;
      }
      if (ins->type==DIV_INS_SWAN) {
        dutyLabel="Noise";
        dutyMax=ins->amiga.useSample?0:8;
      }
      if (ins->type==DIV_INS_SNES) {
        dutyLabel="Noise Freq";
        dutyMax=31;
      }
      if (ins->type==DIV_INS_OPLL || ins->type==DIV_INS_OPL || ins->type==DIV_INS_OPL_DRUMS ||
          ins->type==DIV_INS_VRC6_SAW || ins->type==DIV_INS_FDS || ins->type==DIV_INS_MULTIPCM) {
        dutyMax=0;
      }
      if (ins->type==DIV_INS_VERA) {
        dutyLabel="Duty";
        dutyMax=63;
      }
      if (ins->type==DIV_INS_N163) {
        dutyLabel="Wave Pos";
        dutyMax=255;
      }
      if (ins->type==DIV_INS_VRC6) {
        dutyLabel="Duty";
        dutyMax=ins->amiga.useSample?0:7;
      }
      if (ins->type==DIV_INS_ES5506) {
        dutyLabel="Filter Mode";
        dutyMax=3;
      }
      if (ins->type==DIV_INS_SU) {
        dutyMax=127;
      }
      if (ins->type==DIV_INS_ES5506) {
        dutyLabel="Filter Mode";
        dutyMax=3;
      }
      if (ins->type==DIV_INS_MSM6258) {
        dutyLabel="Frequency Divider";
        dutyMax=2;
      }
      if (ins->type==DIV_INS_MSM6295) {
        dutyLabel="Frequency Divider";
        dutyMax=1;
      }
      if (ins->type==DIV_INS_ADPCMA) {
        dutyLabel="Global Volume";
        dutyMax=63;
      }
      if (ins->type==DIV_INS_ADPCMB || ins->type==DIV_INS_YMZ280B || ins->type==DIV_INS_RF5C68) {
        dutyMax=0;
      }
      if (ins->type==DIV_INS_QSOUND) {
        dutyLabel="Echo Level";
        dutyMax=32767;
      }
      if (ins->type==DIV_INS_ESFM) {
        dutyLabel="OP4 Noise Mode";
      }
      if (ins->type==DIV_INS_ES5503) {
        dutyLabel="Osc. mode";
        dutyMax=3;
      }

      //const char* waveLabel="Waveform";
      waveMax=(ins->type==DIV_INS_VERA)?3:(MAX(1,e->song.waveLen-1));
      waveBitMode=false;
      if (ins->type==DIV_INS_C64 || ins->type==DIV_INS_SAA1099) {
        waveBitMode=true;
      }
      if (ins->type==DIV_INS_STD || ins->type==DIV_INS_VRC6_SAW || ins->type==DIV_INS_NES ||
          ins->type==DIV_INS_T6W28 || ins->type==DIV_INS_PV1000)
          waveMax=0;
      if (ins->type==DIV_INS_TIA || ins->type==DIV_INS_VIC || ins->type==DIV_INS_OPLL) waveMax=15;
      if (ins->type==DIV_INS_C64) waveMax=4;
      if (ins->type==DIV_INS_ES5503) waveMax=ins->amiga.useSample?0:255;
      if (ins->type==DIV_INS_SAA1099) waveMax=2;
      if (ins->type==DIV_INS_FM || ins->type==DIV_INS_OPL || ins->type==DIV_INS_OPL_DRUMS || ins->type==DIV_INS_OPZ || ins->type==DIV_INS_OPM || ins->type==DIV_INS_ESFM) waveMax=0;
      if (ins->type==DIV_INS_MIKEY) waveMax=0;
      if (ins->type==DIV_INS_MULTIPCM) waveMax=0;
      if (ins->type==DIV_INS_ADPCMA) waveMax=0;
      if (ins->type==DIV_INS_ADPCMB) waveMax=0;
      if (ins->type==DIV_INS_QSOUND) waveMax=0;
      if (ins->type==DIV_INS_YMZ280B) waveMax=0;
      if (ins->type==DIV_INS_RF5C68) waveMax=0;
      if (ins->type==DIV_INS_MSM5232) waveMax=0;
      if (ins->type==DIV_INS_MSM6258) waveMax=0;
      if (ins->type==DIV_INS_MSM6295) waveMax=0;
      if (ins->type==DIV_INS_SEGAPCM) waveMax=0;
      if (ins->type==DIV_INS_K007232) waveMax=0;
      if (ins->type==DIV_INS_ES5506) waveMax=0;
      if (ins->type==DIV_INS_GA20) waveMax=0;
      if (ins->type==DIV_INS_K053260) waveMax=0;
      if (ins->type==DIV_INS_BEEPER) waveMax=0;
      if (ins->type==DIV_INS_POKEMINI) waveMax=0;
      if (ins->type==DIV_INS_TED) waveMax=0;
      if (ins->type==DIV_INS_C140) waveMax=0;
      if (ins->type==DIV_INS_C219) waveMax=0;
      if (ins->type==DIV_INS_SU || ins->type==DIV_INS_POKEY) waveMax=7;
      if (ins->type==DIV_INS_PET) {
        waveMax=8;
        waveBitMode=true;
      }
      if (ins->type==DIV_INS_VRC6) {
        waveMax=ins->amiga.useSample?(MAX(1,e->song.waveLen-1)):0;
      }
      
      if (ins->type==DIV_INS_OPLL) {
        waveLabel="Patch";
      }

      if (ins->type==DIV_INS_ES5503) {
        waveLabel="Wavetable";
      }

      if (ins->type==DIV_INS_AY || ins->type==DIV_INS_AY8930) {
        waveMax=ins->amiga.useSample?0:3;
        waveBitMode=ins->amiga.useSample?false:true;
      }

      waveNames=NULL;
      if (ins->type==DIV_INS_AY || ins->type==DIV_INS_AY8930 || ins->type==DIV_INS_SAA1099) waveNames=ayShapeBits;
      if (ins->type==DIV_INS_C64) waveNames=c64ShapeBits;

      ex1Max=(ins->type==DIV_INS_AY8930)?8:0;
      ex2Max=(ins->type==DIV_INS_AY || ins->type==DIV_INS_AY8930)?4:0;
      ex2Bit=true;

      if (ins->type==DIV_INS_C64) {
        ex1Max=4;
        ex2Max=15;
      }
      if (ins->type==DIV_INS_X1_010) {
        dutyMax=0;
        ex1Max=ins->amiga.useSample?0:7;
        ex2Max=ins->amiga.useSample?0:255;
        ex2Bit=false;
      }
      if (ins->type==DIV_INS_N163) {
        ex1Max=252;
      }
      if (ins->type==DIV_INS_FDS) {
        ex1Max=63;
        ex2Max=4095;
      }
      if (ins->type==DIV_INS_SU) {
        ex1Max=16383;
        ex2Max=255;
      }
      if (ins->type==DIV_INS_MSM6258) {
        ex1Max=1;
      }
      if (ins->type==DIV_INS_QSOUND) {
        ex1Max=16383;
        ex2Max=2725;
      }
      if (ins->type==DIV_INS_SAA1099) ex1Max=8;
      if (ins->type==DIV_INS_ES5506) {
        ex1Max=65535;
        ex2Max=65535;
      }
      if (ins->type==DIV_INS_SNES) {
        ex1Max=5;
        ex2Max=255;
      }
      if (ins->type==DIV_INS_MSM5232) {
        ex1Max=5;
        ex2Max=11;
      }
      if (ins->type==DIV_INS_ES5503) {
        ex1Max=255;
        ex2Max=7;
      }

      panMin=0;
      panMax=0;
      panSingle=false;
      panSingleNoBit=false;
      if (ins->type==DIV_INS_STD ||//Game Gear
          ins->type==DIV_INS_FM ||
          ins->type==DIV_INS_OPM ||
          ins->type==DIV_INS_GB ||
          ins->type==DIV_INS_OPZ ||
          ins->type==DIV_INS_MSM6258 ||
          ins->type==DIV_INS_VERA ||
          ins->type==DIV_INS_ADPCMA ||
          ins->type==DIV_INS_ADPCMB ||
          ins->type==DIV_INS_ESFM) {
        panMax=2;
        panSingle=true;
      }
      if (ins->type==DIV_INS_OPL ||
          ins->type==DIV_INS_OPL_DRUMS) {
        panMax=4;
        panSingle=true;
      }
      if (ins->type==DIV_INS_X1_010 || ins->type==DIV_INS_PCE || ins->type==DIV_INS_MIKEY ||
          ins->type==DIV_INS_SAA1099 || ins->type==DIV_INS_NAMCO || ins->type==DIV_INS_RF5C68 ||
          ins->type==DIV_INS_VBOY || ins->type==DIV_INS_T6W28 || ins->type==DIV_INS_K007232) {
        panMax=15;
      }
      if (ins->type==DIV_INS_SEGAPCM) {
        panMax=127;
      }
      if (ins->type==DIV_INS_AMIGA) {
        if (ins->std.get_macro(DIV_MACRO_PAN_LEFT, true)->mode) {
          panMin=-16;
          panMax=16;
        } else {
          panMin=0;
          panMax=127;
        }
      }
      if (ins->type==DIV_INS_QSOUND) {
        panMin=-16;
        panMax=16;
        panSingleNoBit=true;
      }
      if (ins->type==DIV_INS_MULTIPCM || ins->type==DIV_INS_YMZ280B) {
        panMin=-7;
        panMax=7;
        panSingleNoBit=true;
      }
      if (ins->type==DIV_INS_K053260) {
        panMin=-3;
        panMax=3;
        panSingleNoBit=true;
      }
      if (ins->type==DIV_INS_SU) {
        panMin=-127;
        panMax=127;
        panSingleNoBit=true;
      }
      if (ins->type==DIV_INS_SNES) {
        panMin=0;
        panMax=127;
      }
      if (ins->type==DIV_INS_C140 || ins->type==DIV_INS_C219) {
        panMin=0;
        panMax=255;
      }
      if (ins->type==DIV_INS_ES5506) {
        panMax=4095;
      }
      if (ins->type==DIV_INS_ES5503 && ins->es5503.softpan_virtual_channel) {
        panMax=255;
      }

      if (volMax>0) {
        macroList.push_back(FurnaceGUIMacroDesc(volumeLabel,ins,DIV_MACRO_VOL,0xff,volMin,volMax,160,uiColors[GUI_COLOR_MACRO_VOLUME]));
      }
      if (ins->type!=DIV_INS_MSM6258 && ins->type!=DIV_INS_MSM6295 && ins->type!=DIV_INS_ADPCMA) {
        macroList.push_back(FurnaceGUIMacroDesc("Arpeggio",ins,DIV_MACRO_ARP,0xff,-120,120,160,uiColors[GUI_COLOR_MACRO_PITCH],true,NULL,macroHoverNote,false,NULL,0,true,ins->std.get_macro(DIV_MACRO_ARP, true)->val));
      }
      if (dutyMax>0) {
        if (ins->type==DIV_INS_MIKEY) {
          macroList.push_back(FurnaceGUIMacroDesc(dutyLabel,ins,DIV_MACRO_DUTY,0xff,0,dutyMax,160,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,mikeyFeedbackBits));
        } else if (ins->type==DIV_INS_POKEY) {
          macroList.push_back(FurnaceGUIMacroDesc(dutyLabel,ins,DIV_MACRO_DUTY,0xff,0,dutyMax,160,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,pokeyCtlBits));
        } else if (ins->type==DIV_INS_TED) {
          macroList.push_back(FurnaceGUIMacroDesc(dutyLabel,ins,DIV_MACRO_DUTY,0xff,0,dutyMax,80,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,tedControlBits));
        } else if (ins->type==DIV_INS_MSM5232) {
          macroList.push_back(FurnaceGUIMacroDesc(dutyLabel,ins,DIV_MACRO_DUTY,0xff,0,dutyMax,160,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,msm5232ControlBits));
        } else if (ins->type==DIV_INS_ES5506) {
          macroList.push_back(FurnaceGUIMacroDesc(dutyLabel,ins,DIV_MACRO_DUTY,0xff,dutyMin,dutyMax,160,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,&macroHoverES5506FilterMode));
        } else if (ins->type==DIV_INS_C219) {
          macroList.push_back(FurnaceGUIMacroDesc(dutyLabel,ins,DIV_MACRO_DUTY,0xff,0,dutyMax,120,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,c219ControlBits));
        } else {
          macroList.push_back(FurnaceGUIMacroDesc(dutyLabel,ins,DIV_MACRO_DUTY,0xff,dutyMin,dutyMax,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        }
      }
      if (waveMax>0) {
        macroList.push_back(FurnaceGUIMacroDesc(waveLabel,ins,DIV_MACRO_WAVE,0xff,0,waveMax,(waveBitMode && ins->type!=DIV_INS_PET)?64:160,uiColors[GUI_COLOR_MACRO_WAVE],false,NULL,NULL,waveBitMode,waveNames,((ins->type==DIV_INS_AY || ins->type==DIV_INS_AY8930)?1:0)));
      }
      if (panMax>0) {
        if (panSingle) {
          macroList.push_back(FurnaceGUIMacroDesc("Panning",ins,DIV_MACRO_PAN_LEFT,0xff,0,panMax,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,panBits));
        } else if (ins->type==DIV_INS_QSOUND) {
          macroList.push_back(FurnaceGUIMacroDesc("Panning",ins,DIV_MACRO_PAN_LEFT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER]));
          macroList.push_back(FurnaceGUIMacroDesc("Surround",ins,DIV_MACRO_PAN_RIGHT,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
        } else {
          if (panSingleNoBit || (ins->type==DIV_INS_AMIGA && ins->std.get_macro(DIV_MACRO_PAN_LEFT, true)->mode)) {
            macroList.push_back(FurnaceGUIMacroDesc("Panning",ins,DIV_MACRO_PAN_LEFT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER],false,(ins->type==DIV_INS_AMIGA)?macroQSoundMode:NULL));
          } else {
            macroList.push_back(FurnaceGUIMacroDesc("Panning (left)",ins,DIV_MACRO_PAN_LEFT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER],false,(ins->type==DIV_INS_AMIGA)?macroQSoundMode:NULL));
          }
          if (!panSingleNoBit) {
            if (ins->type==DIV_INS_AMIGA && ins->std.get_macro(DIV_MACRO_PAN_LEFT, true)->mode) {
              macroList.push_back(FurnaceGUIMacroDesc("Surround",ins,DIV_MACRO_PAN_RIGHT,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
            } else {
              macroList.push_back(FurnaceGUIMacroDesc("Panning (right)",ins,DIV_MACRO_PAN_RIGHT,0xff,panMin,panMax,CLAMP(31+panMax-panMin,32,160),uiColors[GUI_COLOR_MACRO_OTHER]));
            }
          }
        }
      }
      if (ins->type!=DIV_INS_MSM5232 && ins->type!=DIV_INS_MSM6258 && ins->type!=DIV_INS_MSM6295 && ins->type!=DIV_INS_ADPCMA) {
        macroList.push_back(FurnaceGUIMacroDesc("Pitch",ins,DIV_MACRO_PITCH,0xff,-2048,2047,160,uiColors[GUI_COLOR_MACRO_PITCH],true,macroRelativeMode));
      }
      if (ins->type==DIV_INS_FM ||
          ins->type==DIV_INS_OPM ||
          ins->type==DIV_INS_STD ||
          ins->type==DIV_INS_NES ||
          ins->type==DIV_INS_OPL ||
          ins->type==DIV_INS_OPL_DRUMS ||
          ins->type==DIV_INS_OPZ ||
          ins->type==DIV_INS_PCE ||
          ins->type==DIV_INS_GB ||
          ins->type==DIV_INS_MSM6258 ||
          ins->type==DIV_INS_MSM6295 ||
          ins->type==DIV_INS_ADPCMA ||
          ins->type==DIV_INS_ADPCMB ||
          ins->type==DIV_INS_SEGAPCM ||
          ins->type==DIV_INS_QSOUND ||
          ins->type==DIV_INS_YMZ280B ||
          ins->type==DIV_INS_RF5C68 ||
          ins->type==DIV_INS_AMIGA ||
          ins->type==DIV_INS_OPLL ||
          ins->type==DIV_INS_AY ||
          ins->type==DIV_INS_AY8930 ||
          ins->type==DIV_INS_SWAN ||
          ins->type==DIV_INS_MULTIPCM ||
          (ins->type==DIV_INS_VRC6 && ins->amiga.useSample) ||
          ins->type==DIV_INS_SU ||
          ins->type==DIV_INS_MIKEY ||
          ins->type==DIV_INS_ES5506 ||
          ins->type==DIV_INS_T6W28 ||
          ins->type==DIV_INS_VBOY ||
          (ins->type==DIV_INS_X1_010 && ins->amiga.useSample) ||
          ins->type==DIV_INS_K007232 ||
          ins->type==DIV_INS_GA20 ||
          ins->type==DIV_INS_K053260 ||
          ins->type==DIV_INS_C140 ||
          ins->type==DIV_INS_C219 ||
          ins->type==DIV_INS_TED ||
          ins->type==DIV_INS_ESFM ||
          ins->type==DIV_INS_ES5503) {
        macroList.push_back(FurnaceGUIMacroDesc("Phase Reset",ins,DIV_MACRO_PHASE_RESET,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
      }
      if (ex1Max>0) {
        if (ins->type==DIV_INS_C64) {
          int cutoffMin=-2047;
          int cutoffMax=2047;

          if (ins->c64.filterIsAbs) {
            cutoffMin=0;
            cutoffMax=2047;
          }
          macroList.push_back(FurnaceGUIMacroDesc("Cutoff",ins,DIV_MACRO_ALG,0xff,cutoffMin,cutoffMax,160,uiColors[GUI_COLOR_MACRO_OTHER]));
          macroList.push_back(FurnaceGUIMacroDesc("Filter Mode",ins,DIV_MACRO_EX1,0xff,0,ex1Max,64,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,filtModeBits));
        } else if (ins->type==DIV_INS_SAA1099) {
          macroList.push_back(FurnaceGUIMacroDesc("Envelope",ins,DIV_MACRO_EX1,0xff,0,ex1Max,160,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,saaEnvBits));
        } else if (ins->type==DIV_INS_X1_010 && !ins->amiga.useSample) {
          macroList.push_back(FurnaceGUIMacroDesc("Envelope Mode",ins,DIV_MACRO_EX1,0xff,0,ex1Max,160,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,x1_010EnvBits));
        } else if (ins->type==DIV_INS_N163) {
          macroList.push_back(FurnaceGUIMacroDesc("Wave Length",ins,DIV_MACRO_EX1,0xff,0,ex1Max,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else if (ins->type==DIV_INS_FDS) {
          macroList.push_back(FurnaceGUIMacroDesc("Mod Depth",ins,DIV_MACRO_EX1,0xff,0,ex1Max,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else if (ins->type==DIV_INS_SU) {
          macroList.push_back(FurnaceGUIMacroDesc("Cutoff",ins,DIV_MACRO_EX1,0xff,0,ex1Max,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else if (ins->type==DIV_INS_ES5506) {
          macroList.push_back(FurnaceGUIMacroDesc("Filter K1",ins,DIV_MACRO_EX1,0xff,((ins->std.get_macro(DIV_MACRO_EX1, true)->mode==1)?(-ex1Max):0),ex1Max,160,uiColors[GUI_COLOR_MACRO_OTHER],false,macroRelativeMode));
        } else if (ins->type==DIV_INS_MSM6258) {
          macroList.push_back(FurnaceGUIMacroDesc("Clock Divider",ins,DIV_MACRO_EX1,0xff,0,ex1Max,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else if (ins->type==DIV_INS_QSOUND) {
          macroList.push_back(FurnaceGUIMacroDesc("Echo Feedback",ins,DIV_MACRO_EX1,0xff,0,ex1Max,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else if (ins->type==DIV_INS_SNES) {
          macroList.push_back(FurnaceGUIMacroDesc("Special",ins,DIV_MACRO_EX1,0xff,0,ex1Max,96,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,snesModeBits));
        } else if (ins->type==DIV_INS_MSM5232) {
          macroList.push_back(FurnaceGUIMacroDesc("Group Attack",ins,DIV_MACRO_EX1,0xff,0,ex1Max,96,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else if (ins->type==DIV_INS_ES5503) {
          macroList.push_back(FurnaceGUIMacroDesc("Wave/sample pos.",ins,DIV_MACRO_EX1,0xff,0,ex1Max,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else {
          macroList.push_back(FurnaceGUIMacroDesc("Duty",ins,DIV_MACRO_EX1,0xff,0,ex1Max,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        }
      }
      if (ex2Max>0) {
        if (ins->type==DIV_INS_C64) {
          macroList.push_back(FurnaceGUIMacroDesc("Resonance",ins,DIV_MACRO_EX2,0xff,0,ex2Max,64,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else if (ins->type==DIV_INS_FDS) {
          macroList.push_back(FurnaceGUIMacroDesc("Mod Speed",ins,DIV_MACRO_EX2,0xff,0,ex2Max,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else if (ins->type==DIV_INS_SU) {
          macroList.push_back(FurnaceGUIMacroDesc("Resonance",ins,DIV_MACRO_EX2,0xff,0,ex2Max,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else if (ins->type==DIV_INS_ES5506) {
          macroList.push_back(FurnaceGUIMacroDesc("Filter K2",ins,DIV_MACRO_EX2,0xff,((ins->std.get_macro(DIV_MACRO_EX2, true)->mode==1)?(-ex2Max):0),ex2Max,160,uiColors[GUI_COLOR_MACRO_OTHER],false,macroRelativeMode));
        } else if (ins->type==DIV_INS_QSOUND) {
          macroList.push_back(FurnaceGUIMacroDesc("Echo Length",ins,DIV_MACRO_EX2,0xff,0,ex2Max,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else if (ins->type==DIV_INS_SNES) {
          macroList.push_back(FurnaceGUIMacroDesc("Gain",ins,DIV_MACRO_EX2,0xff,0,ex2Max,256,uiColors[GUI_COLOR_MACRO_VOLUME],false,NULL,macroHoverGain,false));
        } else if (ins->type==DIV_INS_MSM5232) {
          macroList.push_back(FurnaceGUIMacroDesc("Group Decay",ins,DIV_MACRO_EX2,0xff,0,ex2Max,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else if (ins->type==DIV_INS_ES5503) {
          macroList.push_back(FurnaceGUIMacroDesc("Osc. output",ins,DIV_MACRO_EX2,0xff,0,ex2Max,64,uiColors[GUI_COLOR_MACRO_OTHER]));
        } else {
          macroList.push_back(FurnaceGUIMacroDesc("Envelope",ins,DIV_MACRO_EX2,0xff,0,ex2Max,ex2Bit?64:160,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,ex2Bit,ayEnvBits));
        }
      }
      if (ins->type==DIV_INS_C64) {
        macroList.push_back(FurnaceGUIMacroDesc("Filter toggle",ins,DIV_MACRO_EX3,0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
        macroList.push_back(FurnaceGUIMacroDesc("Special",ins,DIV_MACRO_EX4,0xff,0,4,64,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,c64TestGateBits));
        macroList.push_back(FurnaceGUIMacroDesc("Attack",ins,DIV_MACRO_EX5, 0xff,0,15,128,uiColors[GUI_COLOR_MACRO_OTHER]));
        macroList.push_back(FurnaceGUIMacroDesc("Decay",ins,DIV_MACRO_EX6, 0xff,0,15,128,uiColors[GUI_COLOR_MACRO_OTHER]));
        macroList.push_back(FurnaceGUIMacroDesc("Sustain",ins,DIV_MACRO_EX7, 0xff,0,15,128,uiColors[GUI_COLOR_MACRO_OTHER]));
        macroList.push_back(FurnaceGUIMacroDesc("Release",ins,DIV_MACRO_EX8, 0xff,0,15,128,uiColors[GUI_COLOR_MACRO_OTHER]));
      }
      if (ins->type==DIV_INS_AY || ins->type==DIV_INS_AY8930 || (ins->type==DIV_INS_X1_010 && !ins->amiga.useSample)) {
        macroList.push_back(FurnaceGUIMacroDesc("AutoEnv Num",ins,DIV_MACRO_EX3, 0xff,0,15,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        macroList.push_back(FurnaceGUIMacroDesc("AutoEnv Den",ins,DIV_MACRO_ALG,0xff,0,15,160,uiColors[GUI_COLOR_MACRO_OTHER]));
      }
      if (ins->type==DIV_INS_AY8930) {
        // oh my i am running out of macros
        macroList.push_back(FurnaceGUIMacroDesc("Noise AND Mask",ins,DIV_MACRO_FB, 0xff,0,8,96,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
        macroList.push_back(FurnaceGUIMacroDesc("Noise OR Mask",ins,DIV_MACRO_FMS, 0xff,0,8,96,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
      }
      if (ins->type==DIV_INS_FDS) {
        macroList.push_back(FurnaceGUIMacroDesc("Mod Position",ins,DIV_MACRO_EX3, 0xff,0,127,160,uiColors[GUI_COLOR_MACRO_OTHER]));
      }
      if (ins->type==DIV_INS_SU) {
        macroList.push_back(FurnaceGUIMacroDesc("Control",ins,DIV_MACRO_EX3, 0xff,0,4,64,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,suControlBits));
        macroList.push_back(FurnaceGUIMacroDesc("Phase Reset Timer",ins,DIV_MACRO_EX4,0xff,0,65535,160,uiColors[GUI_COLOR_MACRO_OTHER])); // again reuse code from resonance macro but use ex4 instead
      }
      if (ins->type==DIV_INS_ES5506) {
        /*macroList.push_back(FurnaceGUIMacroDesc("Envelope counter",ins,DIV_MACRO_EX3, 0xff,0,511,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        macroList.push_back(FurnaceGUIMacroDesc("Envelope left volume ramp",ins,DIV_MACRO_EX4,0xff,-128,127,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        macroList.push_back(FurnaceGUIMacroDesc("Envelope right volume ramp",ins,DIV_MACRO_EX5, 0xff,-128,127,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        macroList.push_back(FurnaceGUIMacroDesc("Envelope K1 ramp",ins,DIV_MACRO_EX6, 0xff,-128,127,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        macroList.push_back(FurnaceGUIMacroDesc("Envelope K2 ramp",ins,DIV_MACRO_EX7, 0xff,-128,127,160,uiColors[GUI_COLOR_MACRO_OTHER]));
        macroList.push_back(FurnaceGUIMacroDesc("Envelope mode",ins,DIV_MACRO_EX8, 0xff,0,2,64,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,es5506EnvelopeModes));*/
        macroList.push_back(FurnaceGUIMacroDesc("Outputs",ins,DIV_MACRO_FB, 0xff,0,5,64,uiColors[GUI_COLOR_MACRO_OTHER]));
        macroList.push_back(FurnaceGUIMacroDesc("Control",ins,DIV_MACRO_ALG,0xff,0,2,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true,es5506ControlModes));
      }
      if (ins->type==DIV_INS_MSM5232) {
        macroList.push_back(FurnaceGUIMacroDesc("Noise",ins,DIV_MACRO_EX3, 0xff,0,1,32,uiColors[GUI_COLOR_MACRO_OTHER],false,NULL,NULL,true));
      }

      /*for(int i = 0; i < (int)ins->std.macros.size(); i++) // reset macro zoom
      {
        ins->std.macros[i].vZoom = -1;
      }*/

      drawMacros(macroList,macroEditStateMacros);
      ImGui::EndTabItem();
    }
    if (ins->type==DIV_INS_NES ||
        ins->type==DIV_INS_AY ||
        ins->type==DIV_INS_AY8930 ||
        ins->type==DIV_INS_MIKEY ||
        ins->type==DIV_INS_PCE ||
        ins->type==DIV_INS_X1_010 ||
        ins->type==DIV_INS_SWAN ||
        ins->type==DIV_INS_VRC6 ||
        ins->type==DIV_INS_ES5503) {
      //insTabSample(ins);
    }
    if (ins->type>=DIV_INS_MAX) {
      if (ImGui::BeginTabItem("Error")) {
        ImGui::Text("invalid instrument type! change it first.");
        ImGui::EndTabItem();
      }
    }
    ImGui::EndTabBar();
  }
  if (settings.insEditColorize) {
    popAccentColors();
  }
}

void FurnaceGUI::drawInsEdit() {
  if (nextWindow==GUI_WINDOW_INS_EDIT) {
    insEditOpen=true;
    ImGui::SetNextWindowFocus();
    nextWindow=GUI_WINDOW_NOTHING;
  }
  if (!insEditOpen) return;
  if (mobileUI) {
    patWindowPos=(portrait?ImVec2(0.0f,(mobileMenuPos*-0.65*canvasH)):ImVec2((0.16*canvasH)+0.5*canvasW*mobileMenuPos,0.0f));
    patWindowSize=(portrait?ImVec2(canvasW,canvasH-(0.16*canvasW)-(pianoOpen?(0.4*canvasW):0.0f)):ImVec2(canvasW-(0.16*canvasH),canvasH-(pianoOpen?(0.3*canvasH):0.0f)));
    ImGui::SetNextWindowPos(patWindowPos);
    ImGui::SetNextWindowSize(patWindowSize);
  } else {
    ImGui::SetNextWindowSizeConstraints(ImVec2(440.0f*dpiScale,400.0f*dpiScale),ImVec2(canvasW,canvasH));
  }
  if (ImGui::Begin("Instrument Editor",&insEditOpen,globalWinFlags|(settings.allowEditDocking?0:ImGuiWindowFlags_NoDocking))) {
    if (curIns<0 || curIns>=(int)e->song.ins.size()) {
      ImGui::SetCursorPosY(ImGui::GetCursorPosY()+(ImGui::GetContentRegionAvail().y-ImGui::GetFrameHeightWithSpacing()*(e->song.ins.empty()?2.0f:3.0f)+ImGui::GetStyle().ItemSpacing.y)*0.5f);
      CENTER_TEXT("no instrument selected");
      ImGui::Text("no instrument selected");
      if (ImGui::BeginTable("noAssetCenter",3)) {
        ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthStretch,0.5f);
        ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthStretch,0.5f);

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();

        if (e->song.ins.size()>0) {
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::BeginCombo("##InsSelect","select one...")) {
            String name;
            for (size_t i=0; i<e->song.ins.size(); i++) {
              name=fmt::sprintf("%.2X: %s##_INSS%d",i,e->song.ins[i]->name,i);
              if (ImGui::Selectable(name.c_str(),curIns==(int)i)) {
                curIns=i;
                wavePreviewInit=true;
                updateFMPreview=true;
              }
            }
            ImGui::EndCombo();
          }
          ImGui::AlignTextToFramePadding();
          ImGui::TextUnformatted("or");
          ImGui::SameLine();
        }
        if (ImGui::Button("Open")) {
          doAction(GUI_ACTION_INS_LIST_OPEN);
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("or");
        ImGui::SameLine();
        if (ImGui::Button("Create New")) {
          doAction(GUI_ACTION_INS_LIST_ADD);
        }

        ImGui::TableNextColumn();
        ImGui::EndTable();
      }
    } else {
      drawActualInsEditor();
    }
    
    if (displayMacroMenu) {
      displayMacroMenu=false;
      if (lastMacroDesc.get_macro()!=NULL) {
        ImGui::OpenPopup("macroMenu");
      }
    }
    if (ImGui::BeginPopup("macroMenu",ImGuiWindowFlags_NoMove|ImGuiWindowFlags_AlwaysAutoResize|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoSavedSettings)) {
      if (ImGui::MenuItem("copy")) {
        String mmlStr;
        encodeMMLStr(mmlStr,lastMacroDesc.get_macro()->val,lastMacroDesc.get_macro()->len,lastMacroDesc.get_macro()->loop,lastMacroDesc.get_macro()->rel);
        SDL_SetClipboardText(mmlStr.c_str());
      }
      if (ImGui::MenuItem("paste")) {
        String mmlStr;
        char* clipText=SDL_GetClipboardText();
        if (clipText!=NULL) {
          if (clipText[0]) {
            mmlStr=clipText;
          }
          SDL_free(clipText);
        }
        if (!mmlStr.empty()) {
          decodeMMLStr(mmlStr,lastMacroDesc.get_macro()->val,lastMacroDesc.get_macro()->len,lastMacroDesc.get_macro()->loop,lastMacroDesc.min,(lastMacroDesc.isBitfield)?((1<<(lastMacroDesc.isBitfield?lastMacroDesc.max:0))-1):lastMacroDesc.max,lastMacroDesc.get_macro()->rel);
        }
      }
      ImGui::Separator();
      if (ImGui::MenuItem("clear")) {
        lastMacroDesc.get_macro()->len=0;
        lastMacroDesc.get_macro()->loop=255;
        lastMacroDesc.get_macro()->rel=255;
        for (int i=0; i<256; i++) {
          lastMacroDesc.get_macro()->val[i]=0;
        }
      }
      if (ImGui::MenuItem("clear contents")) {
        for (int i=0; i<256; i++) {
          lastMacroDesc.get_macro()->val[i]=0;
        }
      }
      ImGui::Separator();
      if (ImGui::BeginMenu("offset...")) {
        ImGui::InputInt("X",&macroOffX,1,10);
        ImGui::InputInt("Y",&macroOffY,1,10);
        if (ImGui::Button("offset")) {
          int oldData[256];
          memset(oldData,0,256*sizeof(int));
          memcpy(oldData,lastMacroDesc.get_macro()->val,lastMacroDesc.get_macro()->len*sizeof(int));

          for (int i=0; i<lastMacroDesc.get_macro()->len; i++) {
            int val=0;
            if ((i-macroOffX)>=0 && (i-macroOffX)<lastMacroDesc.get_macro()->len) {
              val=oldData[i-macroOffX]+macroOffY;
              if (val<lastMacroDesc.min) val=lastMacroDesc.min;
              if (val>lastMacroDesc.max) val=lastMacroDesc.max;
            }
            lastMacroDesc.get_macro()->val[i]=val;
          }

          if (lastMacroDesc.get_macro()->loop<lastMacroDesc.get_macro()->len) {
            lastMacroDesc.get_macro()->loop+=macroOffX;
          } else {
            lastMacroDesc.get_macro()->loop=255;
          }
          if ((lastMacroDesc.get_macro()->rel+macroOffX)>=0 && (lastMacroDesc.get_macro()->rel+macroOffX)<lastMacroDesc.get_macro()->len) {
            lastMacroDesc.get_macro()->rel+=macroOffX;
          } else {
            lastMacroDesc.get_macro()->rel=255;
          }

          ImGui::CloseCurrentPopup();
        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("scale...")) {
        if (ImGui::InputFloat("X",&macroScaleX,1.0f,10.0f,"%.2f%%")) {
          if (macroScaleX<0.1) macroScaleX=0.1;
          if (macroScaleX>12800.0) macroScaleX=12800.0;
        }
        ImGui::InputFloat("Y",&macroScaleY,1.0f,10.0f,"%.2f%%");
        if (ImGui::Button("scale")) {
          int oldData[256];
          memset(oldData,0,256*sizeof(int));
          memcpy(oldData,lastMacroDesc.get_macro()->val,lastMacroDesc.get_macro()->len*sizeof(int));

          lastMacroDesc.get_macro()->len=MIN(128,((double)lastMacroDesc.get_macro()->len*(macroScaleX/100.0)));

          for (int i=0; i<lastMacroDesc.get_macro()->len; i++) {
            int val=0;
            double posX=round((double)i*(100.0/macroScaleX)-0.01);
            if (posX>=0 && posX<lastMacroDesc.get_macro()->len) {
              val=round((double)oldData[(int)posX]*(macroScaleY/100.0));
              if (val<lastMacroDesc.min) val=lastMacroDesc.min;
              if (val>lastMacroDesc.max) val=lastMacroDesc.max;
            }
            lastMacroDesc.get_macro()->val[i]=val;
          }

          ImGui::CloseCurrentPopup();
        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("randomize...")) {
        if (macroRandMin<lastMacroDesc.min) macroRandMin=lastMacroDesc.min;
        if (macroRandMin>lastMacroDesc.max) macroRandMin=lastMacroDesc.max;
        if (macroRandMax<lastMacroDesc.min) macroRandMax=lastMacroDesc.min;
        if (macroRandMax>lastMacroDesc.max) macroRandMax=lastMacroDesc.max;
        ImGui::InputInt("Min",&macroRandMin,1,10);
        ImGui::InputInt("Max",&macroRandMax,1,10);
        if (ImGui::Button("randomize")) {
          for (int i=0; i<lastMacroDesc.get_macro()->len; i++) {
            int val=0;
            if (macroRandMax<=macroRandMin) {
              val=macroRandMin;
            } else {
              val=macroRandMin+(rand()%(macroRandMax-macroRandMin+1));
            }
            lastMacroDesc.get_macro()->val[i]=val;
          }

          ImGui::CloseCurrentPopup();
        }
        ImGui::EndMenu();
      }
      
      ImGui::EndPopup();
    }
  }
  if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows)) curWindow=GUI_WINDOW_INS_EDIT;
  ImGui::End();
}