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
#include "misc/cpp/imgui_stdlib.h"
#include <fmt/printf.h>
#include <algorithm>

String sysDefID;

void FurnaceGUI::drawSysDefs(std::vector<FurnaceGUISysDef>& category, bool& accepted, std::vector<int>& sysDefStack, bool& alreadyHover) {
  int index=0;
  String sysDefIDLeader="##NS";
  for (int i: sysDefStack) {
    sysDefIDLeader+=fmt::sprintf("/%d",i);
  }
  for (FurnaceGUISysDef& i: category) {
    bool treeNode=false;
    bool isHovered=false;
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    if (!i.subDefs.empty()) {
      if (i.orig.empty()) {
        sysDefID=fmt::sprintf("%s%s/%dS",_L(i.name.c_str()),sysDefIDLeader,index);
      } else {
        sysDefID=fmt::sprintf("%s/%dS",sysDefIDLeader,index);
      }
      treeNode=ImGui::TreeNodeEx(sysDefID.c_str(),i.orig.empty()?ImGuiTreeNodeFlags_SpanAvailWidth:0);
      ImGui::SameLine();
    }
    if (!i.orig.empty()) {
      sysDefID=fmt::sprintf("%s%s/%d",_L(i.name.c_str()),sysDefIDLeader,index);
      if (ImGui::Selectable(sysDefID.c_str(),false,ImGuiSelectableFlags_DontClosePopups)) {
        nextDesc=i.definition;
        nextDescName=_L(i.name.c_str());
        accepted=true;
      }
      if (ImGui::IsItemHovered()) isHovered=true;
    } else if (i.subDefs.empty()) {
      ImGui::TextUnformatted(_L(i.name.c_str()));
      if (ImGui::IsItemHovered()) isHovered=true;
    }
    if (treeNode) {
      sysDefStack.push_back(index);
      drawSysDefs(i.subDefs,accepted,sysDefStack,alreadyHover);
      sysDefStack.erase(sysDefStack.end()-1);
      ImGui::TreePop();
    }
    if (isHovered && !alreadyHover) {
      alreadyHover=true;
      if (ImGui::BeginTooltip()) {
        std::map<DivSystem,int> chipCounts;
        std::vector<DivSystem> chips;
        for (FurnaceGUISysDefChip chip: i.orig) {
          if (chipCounts.find(chip.sys)==chipCounts.end()) {
            chipCounts[chip.sys]=1;
            chips.push_back(chip.sys);
          } else {
            chipCounts[chip.sys]+=1;
          }
        }
        for (size_t chipIndex=0; chipIndex<chips.size(); chipIndex++) {
          DivSystem chip=chips[chipIndex];
          const DivSysDef* sysDef=e->getSystemDef(chip);
          ImGui::PushTextWrapPos(MIN(scrW*dpiScale,400.0f*dpiScale));
          ImGui::Text("%s (x%d): ",_L(sysDef->name),chipCounts[chip]);
          ImGui::Text("%s",_L(sysDef->description));
          ImGui::PopTextWrapPos();
          if (chipIndex+1<chips.size()) {
            ImGui::Separator();
          }
        }

        ImGui::EndTooltip();
      }
    }
    index++;
  }
}

void findInSubs(std::vector<FurnaceGUISysDef>& where, std::vector<FurnaceGUISysDef>& newSongSearchResults, String lowerCase) {
  for (FurnaceGUISysDef& j: where) {
    if (!j.orig.empty()) {
      String lowerCase1=j.name;
      for (char& i: lowerCase1) {
        if (i>='A' && i<='Z') i+='a'-'A';
      }
      auto lastItem=std::remove_if(lowerCase1.begin(),lowerCase1.end(),[](char c) {
        return (c==' ' || c=='_' || c=='-');
      });
      lowerCase1.erase(lastItem,lowerCase1.end());
      if (lowerCase1.find(lowerCase)!=String::npos) {
        newSongSearchResults.push_back(j);
        newSongSearchResults[newSongSearchResults.size()-1].subDefs.clear();
      }
    }
    findInSubs(j.subDefs,newSongSearchResults,lowerCase);
  }
}

void FurnaceGUI::drawNewSong() {
  bool accepted=false;
  std::vector<int> sysDefStack;

  ImGui::PushFont(bigFont);
  ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x-ImGui::CalcTextSize(_L("Choose a System!##sgns")).x)*0.5);
  ImGui::Text(_L("Choose a System!##sgns"));
  ImGui::PopFont();

  ImVec2 avail=ImGui::GetContentRegionAvail();
  avail.y-=ImGui::GetFrameHeightWithSpacing();

  if (ImGui::BeginChild("sysPickerC",avail,false,ImGuiWindowFlags_NoScrollWithMouse|ImGuiWindowFlags_NoScrollbar)) {
    if (newSongFirstFrame)
      ImGui::SetKeyboardFocusHere();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    if (ImGui::InputTextWithHint("##SysSearch",settings.language == DIV_LANG_ENGLISH ? "Search..." : _L("Search...##sgns"),&newSongQuery)) {
      String lowerCase=newSongQuery;
      
      for (char& i: lowerCase) {
        if (i>='A' && i<='Z') i+='a'-'A';
      }
      auto lastItem=std::remove_if(lowerCase.begin(),lowerCase.end(),[](char c) {
        return (c==' ' || c=='_' || c=='-');
      });
      lowerCase.erase(lastItem,lowerCase.end());
      newSongSearchResults.clear();
      for (FurnaceGUISysCategory& i: sysCategories) 
      {
        for (FurnaceGUISysDef& j: i.systems) 
        {
          if (!j.orig.empty()) 
          {
            String lowerCase1=j.name;
            for (char& i: lowerCase1) 
            {
              if (i>='A' && i<='Z') i+='a'-'A';
            }
            auto lastItem=std::remove_if(lowerCase1.begin(),lowerCase1.end(),[](char c) 
            {
              return (c==' ' || c=='_' || c=='-');
            });
            lowerCase1.erase(lastItem,lowerCase1.end());
            if (lowerCase1.find(lowerCase)!=String::npos) 
            {
              newSongSearchResults.push_back(j);
              newSongSearchResults[newSongSearchResults.size()-1].subDefs.clear();
            }
          }
          findInSubs(j.subDefs,newSongSearchResults,lowerCase);
        }
      }
      std::sort(newSongSearchResults.begin(),newSongSearchResults.end(),[](const FurnaceGUISysDef& a, const FurnaceGUISysDef& b) {
        String namea1 = a.name.substr(0, a.name.find("##"));
        String nameb1 = b.name.substr(0, b.name.find("##"));
        return strcmp(namea1.c_str(),nameb1.c_str())<0;
      });
      auto lastItem1=std::unique(newSongSearchResults.begin(),newSongSearchResults.end(),[](const FurnaceGUISysDef& a, const FurnaceGUISysDef& b) {
        String namea1 = a.name.substr(0, a.name.find("##"));
        String nameb1 = b.name.substr(0, b.name.find("##"));
        return namea1 == nameb1;
      });
      newSongSearchResults.erase(lastItem1,newSongSearchResults.end());
    }
    if (ImGui::BeginTable("sysPicker",newSongQuery.empty()?2:1,ImGuiTableFlags_BordersInnerV)) {
      if (newSongQuery.empty()) {
        ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthFixed,0.0f);
      }
      ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthStretch,0.0f);

      if (newSongQuery.empty()) {
        ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
        ImGui::TableNextColumn();
        ImGui::Text(_L("Categories##sgns"));
        ImGui::TableNextColumn();
        ImGui::Text(_L("Systems##sgns"));
      }

      ImGui::TableNextRow();

      // CATEGORIES
      if (newSongQuery.empty()) {
        ImGui::TableNextColumn();
        int index=0;
        for (FurnaceGUISysCategory& i: sysCategories) {
          if (ImGui::Selectable(_L(i.name),newSongCategory==index,ImGuiSelectableFlags_DontClosePopups)) { \
            newSongCategory=index;
          }
          if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("%s",_L(i.description));
          }
          if (strcmp(i.name,_L("User##sgpr"))==0) ImGui::Separator();
          index++;
        }
      }

      // SYSTEMS
      ImGui::TableNextColumn();
      if (ImGui::BeginTable("Systems",1,ImGuiTableFlags_BordersInnerV|ImGuiTableFlags_ScrollY)) 
      {
        std::vector<FurnaceGUISysDef>& category=(newSongQuery.empty())?(sysCategories[newSongCategory].systems):(newSongSearchResults);
        if (category.empty()) 
        {
          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          if (newSongQuery.empty()) 
          {
            ImGui::Text(_L("no systems here yet!##sgns"));
          } 
          else 
          {
            ImGui::Text(_L("no results##sgns"));
          }
        } 
        else 
        {
          bool alreadyHover=false;
          sysDefStack.push_back(newSongQuery.empty()?newSongCategory:-1);
          drawSysDefs(category,accepted,sysDefStack,alreadyHover);
          sysDefStack.erase(sysDefStack.end()-1);
        }
        ImGui::EndTable();
      }

      ImGui::EndTable();
    }
  }
  ImGui::EndChild();

  if (ImGui::Button(_L("I'm feeling lucky##sgns"))) {
    if (sysCategories.size()==0) {
      showError(_L("no categories available! what in the world.##sgns"));
      ImGui::CloseCurrentPopup();
    } else {
      int tries=0;
      for (tries=0; tries<50; tries++) {
        FurnaceGUISysCategory* newSystemCat=&sysCategories[rand()%sysCategories.size()];
        if (newSystemCat->systems.empty()) {
          continue;
        } else {
          unsigned int selection=rand()%newSystemCat->systems.size();

          if (newSystemCat->systems[selection].orig.empty() && newSystemCat->systems[selection].subDefs.empty()) continue;
          if (!newSystemCat->systems[selection].subDefs.empty()) {
            if (rand()%2) {
              unsigned int subSel=rand()%newSystemCat->systems[selection].subDefs.size();
              nextDesc=newSystemCat->systems[selection].subDefs[subSel].definition;
              nextDescName=newSystemCat->systems[selection].subDefs[subSel].name;
              accepted=true;
            } else {
              if (newSystemCat->systems[selection].orig.empty()) continue;
              nextDesc=newSystemCat->systems[selection].definition;
              nextDescName=newSystemCat->systems[selection].name;
              accepted=true;
            }
          } else {
            nextDesc=newSystemCat->systems[selection].definition;
            nextDescName=newSystemCat->systems[selection].name;
            accepted=true;
          }
        }

        if (accepted) break;
      }

      if (tries>=50) {
        showError(_L("it appears you're extremely lucky today!##sgns"));
        ImGui::CloseCurrentPopup();
      }
    }
  }

  ImGui::SameLine();

  if (ImGui::Button(_L("Cancel##sgns")) || ImGui::IsKeyPressed(ImGuiKey_Escape)) {
    ImGui::CloseCurrentPopup();
  }

  if (accepted) {
    String temmrrrp = nextDescName.substr(0, nextDescName.find("##"));
    String temmrrrp_desc = nextDesc.substr(0, nextDesc.find("##"));
    e->createNew(temmrrrp_desc.c_str(),temmrrrp,false);
    undoHist.clear();
    redoHist.clear();
    curFileName="";
    modified=false;
    curNibble=false;
    orderNibble=false;
    orderCursor=-1;
    samplePos=0;
    updateSampleTex=true;
    selStart=SelectionPoint();
    selEnd=SelectionPoint();
    cursor=SelectionPoint();
    updateWindowTitle();
    ImGui::CloseCurrentPopup();
  }

  newSongFirstFrame=false;
}