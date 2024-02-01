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

#include "gui.h"
#include "imgui.h"
#include "intConst.h"

void FurnaceGUI::drawCompatFlags() {
  if (nextWindow==GUI_WINDOW_COMPAT_FLAGS) {
    compatFlagsOpen=true;
    ImGui::SetNextWindowFocus();
    nextWindow=GUI_WINDOW_NOTHING;
  }
  if (!compatFlagsOpen) return;
  if (ImGui::Begin("Compatibility Flags",&compatFlagsOpen,globalWinFlags,_L("Compatibility Flags###Compatibility Flags"))) {
    ImGui::TextWrapped(_L("these flags are designed to provide better DefleMask/older Furnace compatibility.\nit is recommended to disable most of these unless you rely on specific quirks.##sgcf"));
    if (ImGui::BeginTabBar("settingsTab")) {
      if (ImGui::BeginTabItem("DefleMask")) {
        ImGui::Checkbox(_L("Game Boy instrument duty is wave volume##sgcf"),&e->song.waveDutyIsVol);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("if enabled, an instrument with duty macro in the wave channel will be mapped to wavetable volume.##sgcf"));
        }

        ImGui::Checkbox(_L("Restart macro on portamento##sgcf"),&e->song.resetMacroOnPorta);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, a portamento effect will reset the channel's macro if used in combination with a note.##sgcf"));
        }
        ImGui::Checkbox(_L("Ignore duplicate slide effects##sgcf"),&e->song.ignoreDuplicateSlides);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("if this is on, only the first slide of a row in a channel will be considered.##sgcf"));
        }
        ImGui::Checkbox(_L("Ignore 0Dxx on the last order##sgcf"),&e->song.ignoreJumpAtEnd);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("if this is on, a jump to next row effect will not take place when it is on the last order of a song.##sgcf"));
        }
        InvCheckbox(_L("Don't apply Game Boy envelope on note-less instrument change##sgcf"),&e->song.gbInsAffectsEnvelope);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("if this is on, an instrument change will not affect the envelope.##sgcf"));
        }
        ImGui::Checkbox(_L("Ignore DAC mode change outside of intended channel in ExtCh mode##sgcf"),&e->song.ignoreDACModeOutsideIntendedChannel);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("if this is on, 17xx has no effect on the operator channels in YM2612.##sgcf"));
        }
        ImGui::Checkbox(_L("SN76489 duty macro always resets phase##sgcf"),&e->song.snDutyReset);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, duty macro will always reset phase, even if its value hasn't changed.##sgcf"));
        }
        InvCheckbox(_L("Don't persist volume macro after it finishes##sgcf"),&e->song.volMacroLinger);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, a value in the volume column that happens after the volume macro is done will disregard the macro.##sgcf"));
        }
        ImGui::EndTabItem();
      }
      if (ImGui::BeginTabItem(_L(".mod import##sgcf"))) {
        ImGui::Checkbox(_L("Don't slide on the first tick of a row##sgcf"),&e->song.noSlidesOnFirstTick);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("simulates ProTracker's behavior of not applying volume/pitch slides on the first tick of a row.##sgcf"));
        }
        ImGui::Checkbox(_L("Reset arpeggio position on row change##sgcf"),&e->song.rowResetsArpPos);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("simulates ProTracker's behavior of arpeggio being bound to the current tick of a row.##sgcf"));
        }
        ImGui::EndTabItem();
      }
      if (ImGui::BeginTabItem(_L("Pitch/Playback##sgcf"))) {
        ImGui::Text(_L("Pitch linearity:##sgcf"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("None##sgcf"),e->song.linearPitch==0)) {
          e->song.linearPitch=0;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("like ProTracker/FamiTracker##sgcf"));
        }
        if (ImGui::RadioButton(_L("Full##sgcf"),e->song.linearPitch==2)) {
          e->song.linearPitch=2;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("like Impulse Tracker##sgcf"));
        }
        ImGui::Unindent();

        if (e->song.linearPitch==2) {
          ImGui::SameLine();
          ImGui::SetNextItemWidth(120.0f*dpiScale);
          if (ImGui::InputScalar(_L("Pitch slide speed multiplier##sgcf"),ImGuiDataType_U8,&e->song.pitchSlideSpeed,&_ONE,&_ONE)) {
            if (e->song.pitchSlideSpeed<1) e->song.pitchSlideSpeed=1;
            if (e->song.pitchSlideSpeed>64) e->song.pitchSlideSpeed=64;
          }
        }

        ImGui::Text(_L("Loop modality:##sgcf"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Reset channels##sgcf"),e->song.loopModality==0)) {
          e->song.loopModality=0;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("select to reset channels on loop. may trigger a voltage click on every loop!##sgcf"));
        }
        if (ImGui::RadioButton(_L("Soft reset channels##sgcf"),e->song.loopModality==1)) {
          e->song.loopModality=1;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("select to turn channels off on loop.##sgcf"));
        }
        if (ImGui::RadioButton(_L("Do nothing##sgcf"),e->song.loopModality==2)) {
          e->song.loopModality=2;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("select to not reset channels on loop.##sgcf"));
        }
        ImGui::Unindent();

        ImGui::Text(_L("Cut/delay effect policy:##sgcf"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Strict##sgcf"),e->song.delayBehavior==0)) {
          e->song.delayBehavior=0;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("only when time is less than speed (like DefleMask/ProTracker)##sgcf"));
        }
        if (ImGui::RadioButton(_L("Lax##sgcf"),e->song.delayBehavior==2)) {
          e->song.delayBehavior=2;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("no checks##sgcf"));
        }
        ImGui::Unindent();

        ImGui::Text(_L("Simultaneous jump (0B+0D) treatment:##sgcf"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Normal##sgcf"),e->song.jumpTreatment==0)) {
          e->song.jumpTreatment=0;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("accept 0B+0D to jump to a specific row of an order##sgcf"));
        }
        ImGui::Unindent();
        ImGui::EndTabItem();
      }
      if (ImGui::BeginTabItem(_L("Other##sgcf"))) {
        ImGui::Checkbox(_L("Auto-insert one tick gap between notes##sgcf"),&e->song.oneTickCut);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, a one-tick note cut will be inserted between non-legato/non-portamento notes.\nthis simulates the behavior of some Amiga/SNES music engines.\n\nineffective on C64.##sgcf"));
        }

        ImGui::Separator();

        InvCheckbox(_L("Don't reset slides after note off##sgcf"),&e->song.noteOffResetsSlides);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, note off will not reset the channel's slide effect.##sgcf"));
        }
        InvCheckbox(_L("Don't reset portamento after reaching target##sgcf"),&e->song.targetResetsSlides);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, the slide effect will not be disabled after it reaches its target.##sgcf"));
        }
        ImGui::Checkbox(_L("Continuous vibrato##sgcf"),&e->song.continuousVibrato);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, vibrato phase/position will not be reset on a new note.##sgcf"));
        }
        InvCheckbox(_L("Pitch macro is not linear##sgcf"),&e->song.pitchMacroIsLinear);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, the pitch macro of an instrument is in frequency/period space.##sgcf"));
        }
        ImGui::Checkbox(_L("Reset arpeggio effect position on new note##sgcf"),&e->song.resetArpPhaseOnNewNote);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, arpeggio effect (00xy) position is reset on a new note.##sgcf"));
        }
        ImGui::Checkbox(_L("Volume scaling rounds up##sgcf"),&e->song.ceilVolumeScaling);
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, volume macros round up when applied\nthis prevents volume scaling from causing vol=0, which is silent on some chips\n\nineffective on logarithmic channels##sgcf"));
        }
        ImGui::EndTabItem();
      }
      ImGui::EndTabBar();
    }
  }
  if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows)) curWindow=GUI_WINDOW_COMPAT_FLAGS;
  ImGui::End();
}