#include "locale.h"

#include "template.h"
#include "russian.h"
#include "polish.h"
#include "portuguese.h"

const char* languages[] = 
{
    "English",
    "Русский",
    "Polski",
    "Português",
    //"TEMPLATE",
    NULL
};

size_t DivLocale::getMemoryUsage()
{
    size_t count = 0;
    count += strings.size();

    for (const auto& kv : strings) 
    {
        count += kv.first.size();

        for(const auto& pl : kv.second.plurals)
        {
            count += pl.second.size();
        }
    }

    return count;
}

const char* DivLocale::getLangName(DivLang lang)
{
    return languages[lang];
}

DivLang DivLocale::getLangIndex()
{
    return language;
}

static const ImGuiLocEntry GLocalizationEntriesEnUS[] =
{
    { ImGuiLocKey_VersionStr,           "Dear ImGui " IMGUI_VERSION " (" IM_STRINGIFY(IMGUI_VERSION_NUM) ")" },
    { ImGuiLocKey_TableSizeOne,         "Size column to fit###SizeOne"          },
    { ImGuiLocKey_TableSizeAllFit,      "Size all columns to fit###SizeAll"     },
    { ImGuiLocKey_TableSizeAllDefault,  "Size all columns to default###SizeAll" },
    { ImGuiLocKey_TableResetOrder,      "Reset order###ResetOrder"              },
    { ImGuiLocKey_WindowingMainMenuBar, "(Main menu bar)"                       },
    { ImGuiLocKey_WindowingPopup,       "(Popup)"                               },
    { ImGuiLocKey_WindowingUntitled,    "(Untitled)"                            },
    { ImGuiLocKey_DockingHideTabBar,    "Hide tab bar###HideTabBar"             },
};

int getPluralIndexPlaceholder(int n)
{
    return 0;
}

void DivLocale::setLanguage(DivLang lang) //if false, just update ImGui localization
{
    if(lang >= DIV_LANG_MAX)
    {
        return;
    }

    strings.clear(); //language is valid, so we clear the std::unordered_map containing translations.
    strings.rehash(0);
    language = lang;
    getPluralIndex = &getPluralIndexPlaceholder; //by default we have no plural forms!
    // Lower is a switch that calls the corresponding function to fill it again with translations of specific language.

    switch(lang)
    {
        case DIV_LANG_ENGLISH:
        {
            ImGui::LocalizeRegisterEntries(GLocalizationEntriesEnUS, IM_ARRAYSIZE(GLocalizationEntriesEnUS)); //so we default to English ImGUI text...
            break;
        }

        case DIV_LANG_RUSSIAN:
        {
            addTranslationsRussian();
            getPluralIndex = &getPluralIndexRussian;
            break;
        }
        
        case DIV_LANG_POLISH:
        {
            addTranslationsPolish();
            getPluralIndex = &getPluralIndexPolish;
            break;
        }
        
        case DIV_LANG_PORTUGUESE:
        {
            addTranslationsPortuguese();
            getPluralIndex = &getPluralIndexPortuguese;
            break;
        }
        
        /*case DIV_LANG_TEMPLATE:
        {
            addTranslationsTemplate();
            getPluralIndex = &getPluralIndexTemplate;
            break;
        }*/

        default: break;
    }
}

const char* DivLocale::getText(const char* text)
{
    if(text == NULL) return text;
    if(language == DIV_LANG_ENGLISH) return text; //nothing to translate!

    auto iter = strings.find(text);

    if (iter == strings.end()) 
    {
        return text; //fall back to orig string
    }
    else 
    {
        const char* str = iter->second.plurals[0].c_str();
        return strcmp(str, "") == 0 ? text : str; //found string. The default string (without plural form/context specified) lies in plurals[0]
    }
}

const char* DivLocale::getTextPlural(const char* text, int p)
{
    if(getPluralIndex == NULL) return text;
    if(text == NULL) return text;
    if(language == DIV_LANG_ENGLISH) return text; //nothing to translate!

    auto iter = strings.find(text);

    if (iter == strings.end()) 
    {
        return text; //fall back to orig string
    }
    else 
    {
        const char* str = iter->second.plurals[getPluralIndex(p)].c_str();
        return strcmp(str, "") == 0 ? text : str; //found string
    }
}
