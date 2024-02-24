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

#include "../plot_nolerp.h"

extern "C" {
#include "../../extern/Nuked-OPLL/opll.h"
}

class FurnaceGUI;

void FurnaceGUI::localWaveListItem(int i, float* wavePreview, DivInstrument* ins)
{
    DivWavetable* wave = ins->std.local_waves[i];

    for (int ii=0; ii<wave->len; ii++) 
    {
        wavePreview[ii] = wave->data[ii];
    }

    if (wave->len>0) wavePreview[wave->len]=wave->data[wave->len-1];
    ImVec2 curPos=ImGui::GetCursorPos();
    ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign,ImVec2(0,0.5f));

    if (ImGui::Selectable(fmt::sprintf(" %d##_WAVE%d\n",i,i).c_str(),curLocalWave == i,0,ImVec2(0,ImGui::GetFrameHeight()))) 
    {
        curLocalWave = i;
        localWaveList = true;
    }

    ImGui::PopStyleVar();
    curPos.x+=ImGui::CalcTextSize("2222").x;
    if (wantScrollList && curLocalWave == i) ImGui::SetScrollHereY();
    if (ImGui::IsItemHovered()) 
    {
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) 
        {
            waveEditOpen = true;
            localWaveList = true;
            nextWindow = GUI_WINDOW_WAVE_EDIT;
        }
    }

    ImGui::SameLine();
    ImGui::SetCursorPos(curPos);
    PlotNoLerp(fmt::sprintf("##_WAVEP%d",i).c_str(),wavePreview,wave->len+1,0,NULL,0,wave->max,ImVec2(ImGui::GetContentRegionAvail().x,ImGui::GetFrameHeight()));
}

void FurnaceGUI::actualLocalWaveList()
{
    float wavePreview[257];

    DivInstrument* ins = e->song.ins[curIns];

    for (int i=0; i<(int)ins->std.local_waves.size(); i++) 
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        localWaveListItem(i,wavePreview,ins);
    }
}

void FurnaceGUI::insTabWave(DivInstrument* ins)
{
    if (ImGui::BeginTabItem(_L("Wavetable##sgiwave"))) 
    {
        switch (ins->type)
        {
            case DIV_INS_GB:
            case DIV_INS_NAMCO:
            case DIV_INS_SM8521:
            case DIV_INS_SWAN:
                wavePreviewLen=32;
                wavePreviewHeight=15;
                break;
            case DIV_INS_PCE:
                wavePreviewLen=32;
                wavePreviewHeight=31;
                break;
            case DIV_INS_VBOY:
                wavePreviewLen=32;
                wavePreviewHeight=63;
                break;
            case DIV_INS_SCC:
                wavePreviewLen=32;
                wavePreviewHeight=255;
                break;
            case DIV_INS_FDS:
                wavePreviewLen=64;
                wavePreviewHeight=63;
                break;
            case DIV_INS_N163:
                wavePreviewLen=ins->n163.waveLen;
                wavePreviewHeight=15;
                break;
            case DIV_INS_X1_010:
                wavePreviewLen=128;
                wavePreviewHeight=255;
                break;
            case DIV_INS_AMIGA:
                wavePreviewLen=ins->amiga.waveLen+1;
                wavePreviewHeight=255;
                break;
            case DIV_INS_SNES:
                wavePreviewLen=ins->amiga.waveLen+1;
                wavePreviewHeight=15;
                break;
            case DIV_INS_ES5503:
                wavePreviewLen=256;
                wavePreviewHeight=255;
                break;
            default:
                wavePreviewLen=32;
                wavePreviewHeight=31;
                break;
        }
        if (ImGui::Checkbox(_L("Enable synthesizer##sgiwave"),&ins->ws.enabled)) 
        {
            wavePreviewInit=true;
        }
        if (ins->ws.enabled) 
        {
            ImGui::SameLine();
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            if (ins->ws.effect&0x80) {
                if ((ins->ws.effect&0x7f)>=DIV_WS_DUAL_MAX) {
                ins->ws.effect=0;
                wavePreviewInit=true;
                }
            } else {
                if ((ins->ws.effect&0x7f)>=DIV_WS_SINGLE_MAX) {
                ins->ws.effect=0;
                wavePreviewInit=true;
                }
            }
            if (ImGui::BeginCombo("##WSEffect",(ins->ws.effect&0x80)?_L(dualWSEffects[ins->ws.effect&0x7f]):_L(singleWSEffects[ins->ws.effect&0x7f]))) 
            {
                ImGui::Text(_L("Single-waveform##sgiwave"));
                ImGui::Indent();
                for (int i=0; i<DIV_WS_SINGLE_MAX; i++) 
                {
                    if (ImGui::Selectable(_L(singleWSEffects[i]))) 
                    {
                        ins->ws.effect=i;
                        wavePreviewInit=true;
                    }
                }
                ImGui::Unindent();
                ImGui::Text(_L("Dual-waveform##sgiwave"));
                ImGui::Indent();
                for (int i=129; i<DIV_WS_DUAL_MAX; i++) 
                {
                    if (ImGui::Selectable(_L(dualWSEffects[i-128]))) 
                    {
                        ins->ws.effect=i;
                        wavePreviewInit=true;
                    }
                }
                ImGui::Unindent();
                ImGui::EndCombo();
            }
            const bool isSingleWaveFX=(ins->ws.effect>=128);
            if (ImGui::BeginTable("WSPreview",isSingleWaveFX?3:2)) 
            {
                DivWavetable* wave1=NULL;
                DivWavetable* wave2=NULL;
                if(ins->ws.wave1global)
                {
                    wave1=e->getWave(ins->ws.wave1);
                }
                else
                {
                    wave1=e->getLocalWave(ins, ins->ws.wave1);
                }
                if(ins->ws.wave2global)
                {
                    wave2=e->getWave(ins->ws.wave2);
                }
                else
                {
                    wave2=e->getLocalWave(ins, ins->ws.wave2);
                }
                if (wavePreviewInit) 
                {
                    wavePreview.init(ins,wavePreviewLen,wavePreviewHeight,true);
                    wavePreviewInit=false;
                }
                float wavePreview1[257];
                float wavePreview2[257];
                float wavePreview3[257];
                for (int i=0; i<wave1->len; i++) 
                {
                    if (wave1->data[i]>wave1->max) 
                    {
                        wavePreview1[i]=wave1->max;
                    } 
                    else 
                    {
                        wavePreview1[i]=wave1->data[i];
                    }
                }
                if (wave1->len>0) 
                {
                    wavePreview1[wave1->len]=wave1->data[wave1->len-1];
                }
                for (int i=0; i<wave2->len; i++) 
                {
                    if (wave2->data[i]>wave2->max) 
                    {
                        wavePreview2[i]=wave2->max;
                    } 
                    else 
                    {
                        wavePreview2[i]=wave2->data[i];
                    }
                }
                if (wave2->len>0) 
                {
                    wavePreview2[wave2->len]=wave2->data[wave2->len-1];
                }
                if (ins->ws.enabled && (!wavePreviewPaused || wavePreviewInit)) 
                {
                    wavePreview.tick(true);
                    WAKE_UP;
                }
                for (int i=0; i<wavePreviewLen; i++) 
                {
                    wavePreview3[i]=wavePreview.output[i];
                }
                if (wavePreviewLen>0) 
                {
                    wavePreview3[wavePreviewLen]=wavePreview3[wavePreviewLen-1];
                }

                float ySize=(isSingleWaveFX?96.0f:128.0f)*dpiScale;

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImVec2 size1=ImVec2(ImGui::GetContentRegionAvail().x,ySize);
                PlotNoLerp("##WaveformP1",wavePreview1,wave1->len+1,0,_L("Wave 1##sgiwave0"),0,wave1->max,size1);
                if (isSingleWaveFX) 
                {
                    ImGui::TableNextColumn();
                    ImVec2 size2=ImVec2(ImGui::GetContentRegionAvail().x,ySize);
                    PlotNoLerp("##WaveformP2",wavePreview2,wave2->len+1,0,_L("Wave 2##sgiwave0"),0,wave2->max,size2);
                }
                ImGui::TableNextColumn();
                ImVec2 size3=ImVec2(ImGui::GetContentRegionAvail().x,ySize);
                PlotNoLerp("##WaveformP3",wavePreview3,wavePreviewLen+1,0,_L("Result##sgiwave"),0,wavePreviewHeight,size3);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                if (ins->std.get_macro(DIV_MACRO_WAVE, true)->len>0) 
                {
                    ImGui::PushStyleColor(ImGuiCol_Text,uiColors[GUI_COLOR_WARNING]);
                    ImGui::AlignTextToFramePadding();

                    if(settings.language == DIV_LANG_ENGLISH)
                    {
                        ImGui::Text("Wave 1 " ICON_FA_EXCLAMATION_TRIANGLE);
                    }
                    else
                    {
                        std::string str1 = _L("Wave 1 ##sgiwave");
                        std::string str2 = ICON_FA_EXCLAMATION_TRIANGLE;

                        std::string sumstr = str1 + str2;
                        ImGui::Text(sumstr.c_str());
                    }
                    
                    ImGui::PopStyleColor();
                    if (ImGui::IsItemHovered()) 
                    {
                        ImGui::SetTooltip(_L("waveform macro is controlling wave 1!\nthis value will be ineffective.##sgiwave"));
                    }
                } 
                else 
                {
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text(_L("Wave 1##sgiwave1"));
                }
                ImGui::SameLine();
                if (ImGui::Checkbox(_L("Global##sgiwave1"),&ins->ws.wave1global)) 
                {
                    wavePreviewInit=true;
                }
                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                if (ImGui::InputInt("##SelWave1",&ins->ws.wave1,1,4)) 
                {
                    if (ins->ws.wave1<0) ins->ws.wave1=0;

                    if(ins->ws.wave1global)
                    {
                        if (ins->ws.wave1>=(int)e->song.wave.size()) ins->ws.wave1=(int)e->song.wave.size()-1;
                    }
                    else
                    {
                        if (ins->ws.wave1>=(int)e->song.ins[curIns]->std.local_waves.size()) ins->ws.wave1=(int)e->song.ins[curIns]->std.local_waves.size()-1;
                    }
                    wavePreviewInit=true;
                }
                if (ins->std.get_macro(DIV_MACRO_WAVE, true)->len>0) 
                {
                    if (ImGui::IsItemHovered()) 
                    {
                        ImGui::SetTooltip(_L("waveform macro is controlling wave 1!\nthis value will be ineffective.##sgiwave"));
                    }
                }
                if (isSingleWaveFX) 
                {
                    ImGui::TableNextColumn();
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text(_L("Wave 2##sgiwave1"));
                    ImGui::SameLine();
                    if (ImGui::Checkbox(_L("Global##sgiwave2"),&ins->ws.wave2global))
                    {
                        wavePreviewInit=true;
                    }
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                    if (ImGui::InputInt("##SelWave2",&ins->ws.wave2,1,4)) 
                    {
                        if (ins->ws.wave2<0) ins->ws.wave2=0;

                        if(ins->ws.wave2global)
                        {
                            if (ins->ws.wave2>=(int)e->song.wave.size()) ins->ws.wave2=(int)e->song.wave.size()-1;
                        }
                        else
                        {
                            if (ins->ws.wave2>=(int)e->song.ins[curIns]->std.local_waves.size()) ins->ws.wave2=(int)e->song.ins[curIns]->std.local_waves.size()-1;
                        }
                        wavePreviewInit=true;
                    }
                }
                ImGui::TableNextColumn();
                if (ImGui::Button(wavePreviewPaused?(ICON_FA_PLAY "##WSPause"):(ICON_FA_PAUSE "##WSPause"))) 
                {
                    wavePreviewPaused=!wavePreviewPaused;
                }
                if (ImGui::IsItemHovered()) 
                {
                    if (wavePreviewPaused) 
                    {
                        ImGui::SetTooltip(_L("Resume preview##sgiwave"));
                    } 
                    else 
                    {
                        ImGui::SetTooltip(_L("Pause preview##sgiwave"));
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button(ICON_FA_REPEAT "##WSRestart")) 
                {
                    wavePreviewInit=true;
                }
                if (ImGui::IsItemHovered()) 
                {
                    ImGui::SetTooltip(_L("Restart preview##sgiwave"));
                }
                ImGui::SameLine();
                if (ImGui::Button(ICON_FA_UPLOAD "##WSCopy")) 
                {
                    curWave=e->addWave();
                    if (curWave==-1)
                    {
                        showError(settings.language == DIV_LANG_ENGLISH ? "too many wavetables!" : _L("too many wavetables!##sgiwave"));
                    } 
                    else 
                    {
                        wantScrollList=true;
                        MARK_MODIFIED;
                        RESET_WAVE_MACRO_ZOOM;
                        nextWindow=GUI_WINDOW_WAVE_EDIT;

                        DivWavetable* copyWave=e->song.wave[curWave];
                        copyWave->len=wavePreviewLen;
                        copyWave->max=wavePreviewHeight;
                        memcpy(copyWave->data,wavePreview.output,256*sizeof(int));
                    }
                }
                if (ImGui::IsItemHovered()) 
                {
                    ImGui::SetTooltip(_L("Copy to new wavetable##sgiwave"));
                }
                ImGui::SameLine();
                ImGui::Text("(%d×%d)",wavePreviewLen,wavePreviewHeight+1);
                ImGui::EndTable();
            }

            if (ImGui::InputScalar(_L("Update Rate##sgiwave"),ImGuiDataType_U8,&ins->ws.rateDivider,&_ONE,&_EIGHT)) 
            {
                wavePreviewInit=true;
            }
            int speed=ins->ws.speed+1;
            if (ImGui::InputInt(_L("Speed##sgiwave"),&speed,1,8)) 
            {
                if (speed<1) speed=1;
                if (speed>256) speed=256;
                ins->ws.speed=speed-1;
                wavePreviewInit=true;
            }

            if (ImGui::InputScalar(_L("Amount##sgiwave"),ImGuiDataType_U8,&ins->ws.param1,&_ONE,&_EIGHT)) 
            {
                wavePreviewInit=true;
            }

            if (ins->ws.effect==DIV_WS_PHASE_MOD) 
            {
                if (ImGui::InputScalar(_L("Power##sgiwave"),ImGuiDataType_U8,&ins->ws.param2,&_ONE,&_EIGHT)) 
                {
                    wavePreviewInit=true;
                }
            }

            if (ImGui::Checkbox(_L("Global##sgiwave"),&ins->ws.global)) 
            {
                wavePreviewInit=true;
            }
        } 
        else 
        {
            ImGui::TextWrapped(_L("wavetable synthesizer disabled.\nuse the Waveform macro to set the wave for this instrument.##sgiwave"));
        }

        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem(_L("Local Waves##sgiwave"))) 
    {
        if (ImGui::Button(ICON_FA_PLUS "##WaveAdd")) 
        {
            doAction(GUI_ACTION_LOCAL_WAVE_LIST_ADD);
        }
        if (ImGui::IsItemHovered()) 
        {
            ImGui::SetTooltip(_L("Add##sgdl1"));
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_FILES_O "##WaveClone")) 
        {
            doAction(GUI_ACTION_LOCAL_WAVE_LIST_DUPLICATE);
        }
        if (ImGui::IsItemHovered()) 
        {
            ImGui::SetTooltip(_L("Duplicate##sgdl3"));
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_FOLDER_OPEN "##WaveLoad")) 
        {
            doAction(GUI_ACTION_LOCAL_WAVE_LIST_OPEN);
        }
        if (ImGui::IsItemHovered()) 
        {
            ImGui::SetTooltip(_L("Open##sgdl1"));
        }
        if (ImGui::BeginPopupContextItem("WaveOpenOpt")) 
        {
            if (ImGui::MenuItem(_L("replace...##sgdl3"))) 
            {
                doAction((curLocalWave>=0 && curLocalWave<(int)e->song.ins[curIns]->std.local_waves.size())?GUI_ACTION_LOCAL_WAVE_LIST_OPEN_REPLACE:GUI_ACTION_LOCAL_WAVE_LIST_OPEN);
            }
            ImGui::EndPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_FLOPPY_O "##WaveSave")) 
        {
            doAction(GUI_ACTION_LOCAL_WAVE_LIST_SAVE);
        }
        if (ImGui::IsItemHovered()) 
        {
            ImGui::SetTooltip(_L("Save##sgdl3"));
        }
        if (ImGui::BeginPopupContextItem("WaveSaveFormats",ImGuiMouseButton_Right)) 
        {
            if (ImGui::MenuItem(_L("save as .dmw...##sgdl"))) 
            {
                doAction(GUI_ACTION_LOCAL_WAVE_LIST_SAVE_DMW);
            }
            if (ImGui::MenuItem(_L("save raw...##sgdl0"))) 
            {
                doAction(GUI_ACTION_LOCAL_WAVE_LIST_SAVE_RAW);
            }
            ImGui::EndPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_ARROW_UP "##WaveUp")) 
        {
            doAction(GUI_ACTION_LOCAL_WAVE_LIST_MOVE_UP);
        }
        if (ImGui::IsItemHovered()) 
        {
            ImGui::SetTooltip(_L("Move up##sgdl1"));
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_ARROW_DOWN "##WaveDown")) 
        {
            doAction(GUI_ACTION_LOCAL_WAVE_LIST_MOVE_DOWN);
        }
        if (ImGui::IsItemHovered()) 
        {
            ImGui::SetTooltip(_L("Move down##sgdl1"));
        }
        ImGui::SameLine();
        pushDestColor();
        if (ImGui::Button(ICON_FA_TIMES "##WaveDelete")) 
        {
            doAction(GUI_ACTION_LOCAL_WAVE_LIST_DELETE);
        }
        popDestColor();
        if (ImGui::IsItemHovered()) 
        {
            ImGui::SetTooltip(_L("Delete##sgdl4"));
        }
        ImGui::Separator();
        if (ImGui::BeginTable("WaveListScroll",1,ImGuiTableFlags_ScrollY)) 
        {
            actualLocalWaveList();
            ImGui::EndTable();
        }

        ImGui::EndTabItem();
    }
}