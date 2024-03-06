#pragma once

#include <map>
#include <unordered_map>
#include <string>

#include <imgui.h>
#include <imgui_internal.h>

enum DivLang
{
    DIV_LANG_ENGLISH = 0,
    DIV_LANG_RUSSIAN,
    DIV_LANG_POLISH,
    DIV_LANG_PORTUGUESE,
    //DIV_LANG_TEMPLATE,
    DIV_LANG_MAX,
};

typedef struct
{
    std::map<int, std::string> plurals;
    std::map<int, std::string> contexts;
} LocaleEntry;

class DivLocale
{
    private:
        std::unordered_map<std::string, LocaleEntry> strings; //by my measurements at least 20% faster than std::map
        DivLang language;

    public:
        DivLocale()
        {
            strings.clear();
            getPluralIndex = NULL;
        }

        void setLanguage(DivLang lang);

        const char* getLangName(DivLang lang);
        DivLang getLangIndex();

        const char* getText(const char* text);
        const char* getTextPlural(const char* text, int p); //different plural forms
        const char* getTextContext(const char* text, int c); //different translations depending on context

        int (*getPluralIndex)(int); //function that returns plural forms array index based on the input integer

        //=====================================================
        //FUNCTIONS THAT DEFINE TRANSLATED STRINGS:

        void addTranslationsRussian();
        void addTranslationsPolish();
        void addTranslationsPortuguese();
        //void addTranslationsTemplate();

        size_t getMemoryUsage();
};