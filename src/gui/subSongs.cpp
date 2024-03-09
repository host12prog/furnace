#include "gui.h"
#include "imgui.h"
#include "IconsFontAwesome4.h"
#include "misc/cpp/imgui_stdlib.h"
#include "intConst.h"

void FurnaceGUI::drawSubSongs(bool asChild) {
  if (nextWindow==GUI_WINDOW_SUBSONGS) {
    subSongsOpen=true;
    ImGui::SetNextWindowFocus();
    nextWindow=GUI_WINDOW_NOTHING;
  }
  if (!subSongsOpen && !asChild) return;
  if (!asChild) {
    ImGui::SetNextWindowSizeConstraints(ImVec2(64.0f*dpiScale,32.0f*dpiScale),ImVec2(canvasW,canvasH));
  }
  bool began=asChild?ImGui::BeginChild("Subsongs"):ImGui::Begin("Subsongs",&subSongsOpen,globalWinFlags, _L("Subsongs###Subsongs"));
  if (began) {
    char id[1024];
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x-ImGui::GetFrameHeightWithSpacing()*3.0f-ImGui::GetStyle().ItemSpacing.x*2.0f);
    if (e->curSubSong->name.empty()) {
      snprintf(id,1023,_L("%d. <no name>##sgss0"),(int)e->getCurrentSubSong()+1);
    } else {
      snprintf(id,1023,"%d. %s",(int)e->getCurrentSubSong()+1,e->curSubSong->name.c_str());
    }
    if (ImGui::BeginCombo("##SubSong",id)) {
      if (ImGui::BeginTable("SubSongSelection",2)) {
        ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthFixed);
        for (size_t i=0; i<e->song.subsong.size(); i++) {
          if (e->song.subsong[i]->name.empty()) {
            snprintf(id,1023,_L("%d. <no name>##sgss1"),(int)i+1);
          } else {
            snprintf(id,1023,"%d. %s",(int)i+1,e->song.subsong[i]->name.c_str());
          }
          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          if (ImGui::Selectable(id,i==e->getCurrentSubSong())) {
            e->changeSongP(i);
            updateScroll(0);
            oldRow=0;
            cursor.xCoarse=0;
            cursor.xFine=0;
            cursor.y=0;
            selStart=cursor;
            selEnd=cursor;
            curOrder=0;
          }
          ImGui::TableNextColumn();
          ImGui::PushID(i);
          if (ImGui::SmallButton(ICON_FA_ARROW_UP "##SubUp")) {
            e->moveSubSongUp(i);
          }
          if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(_L("Move up##sgss"));
          }
          ImGui::SameLine();
          if (ImGui::SmallButton(ICON_FA_ARROW_DOWN "##SubDown")) {
            e->moveSubSongDown(i);
          }
          if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(_L("Move down##sgss"));
          }
          ImGui::PopID();
        }
        ImGui::EndTable();
      }
      ImGui::EndCombo();
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_PLUS "##SubSongAdd")) {
      if (!e->addSubSong()) {
        showError(settings.language == DIV_LANG_ENGLISH ? "too many subsongs!" : _L("too many subsongs!##sgss0"));
      } else {
        e->changeSongP(e->song.subsong.size()-1);
        updateScroll(0);
        oldRow=0;
        cursor.xCoarse=0;
        cursor.xFine=0;
        cursor.y=0;
        selStart=cursor;
        selEnd=cursor;
        curOrder=0;
        MARK_MODIFIED;
      }
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Add##sgss"));
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FILES_O "##SubSongDuplicate")) {
      if (!e->duplicateSubSong(e->getCurrentSubSong())) {
        showError(settings.language == DIV_LANG_ENGLISH ? "too many subsongs!" : _L("too many subsongs!##sgss1"));
      } else {
        e->changeSongP(e->song.subsong.size()-1);
        updateScroll(0);
        oldRow=0;
        cursor.xCoarse=0;
        cursor.xFine=0;
        cursor.y=0;
        selStart=cursor;
        selEnd=cursor;
        curOrder=0;
        MARK_MODIFIED;
      }
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Duplicate##sgss"));
    }
    ImGui::SameLine();
    pushDestColor();
    if (ImGui::Button(ICON_FA_MINUS "##SubSongDel")) {
      if (e->song.subsong.size()<=1) {
        showError(settings.language == DIV_LANG_ENGLISH ? "this is the only subsong!" : _L("this is the only subsong!##sgss"));
      } else {
        showWarning(settings.language == DIV_LANG_ENGLISH ? "are you sure you want to remove this subsong?" : _L("are you sure you want to remove this subsong?##sgss"),GUI_WARN_SUBSONG_DEL);
      }
    }
    popDestColor();
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip(_L("Remove##sgss"));
    }

    ImGui::AlignTextToFramePadding();
    ImGui::Text(_L("Name##sgss"));
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    if (ImGui::InputText("##SubSongName",&e->curSubSong->name,ImGuiInputTextFlags_UndoRedo)) {
      MARK_MODIFIED;
    }

    if (!asChild && ImGui::GetContentRegionAvail().y>(10.0f*dpiScale)) {
      if (ImGui::InputTextMultiline("##SubSongNotes",&e->curSubSong->notes,ImGui::GetContentRegionAvail(),settings.wrapText ? (ImGuiInputTextFlags_UndoRedo | ImGuiInputTextFlags_WordWrapping) : ImGuiInputTextFlags_UndoRedo)) {
        MARK_MODIFIED;
      }
    }
  }
  if (!asChild && ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows)) curWindow=GUI_WINDOW_SUBSONGS;
  if (asChild) {
    ImGui::EndChild();
  } else {
    ImGui::End();
  }
}
