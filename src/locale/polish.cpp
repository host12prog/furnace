#include <map>
#include <string>
#include "locale.h"

#include "polish.h"

int getPluralIndexPolish(int n)
{
    return (n%10==1 && n%100!=11) ? 0 : ((n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20)) ? 1 : 2);
    //here you can provide plural forms indices based on the integer.
    //you can find one-liners for common languages here:
    //https://www.gnu.org/software/gettext/manual/html_node/Plural-forms.html
    //these would need some adaptation to work in this code
}

static const ImGuiLocEntry GLocalizationEntriesPlPL[] =
{
    { ImGuiLocKey_VersionStr,           "Dear ImGui " IMGUI_VERSION " (" IM_STRINGIFY(IMGUI_VERSION_NUM) ")" },
    { ImGuiLocKey_TableSizeOne,         "Skaluj kolumnę według rozmiaru###SizeOne"           },
    { ImGuiLocKey_TableSizeAllFit,      "Skaluj wszystkie kolumny według rozmiaru###SizeAll"       },
    { ImGuiLocKey_TableSizeAllDefault,  "Domyuślnie skaluj wszystkie kolumny###SizeAll"     },
    { ImGuiLocKey_TableResetOrder,      "Resetuj kolejność###ResetOrder"                         },
    { ImGuiLocKey_WindowingMainMenuBar, "(Pasek głównego menu)"                                },
    { ImGuiLocKey_WindowingPopup,       "(Wyskakujące okno)"                                    },
    { ImGuiLocKey_WindowingUntitled,    "(Bez tytułu)"                                        },
    { ImGuiLocKey_DockingHideTabBar,    "Ukryj pasek zakładek###HideTabBar"                },
};

class DivLocale;

void DivLocale::addTranslationsPolish()
{
    // everything in a string after the ## or ### must remain as is
    // example: Sparkles!##sgab1 means the second instance of "Sparkles!"
    //   in `src/gui/about.cpp`.

    ImGui::LocalizeRegisterEntries(GLocalizationEntriesPlPL, IM_ARRAYSIZE(GLocalizationEntriesPlPL));

    strings["%d apple"].plurals[0] = "%d jabłko";
    strings["%d apple"].plurals[1] = "%d jabłka";
    strings["%d apple"].plurals[2] = "%d jabłek";

    //src/gui/about.cpp

    strings["About Furnace###About Furnace"].plurals[0] = "O Furnace";

    strings["and Furnace-B developers##sgab"].plurals[0] = "i deweloperzy Furnace-B";
    strings["are proud to present##sgab"].plurals[0] = "z dumą prezentują";
    strings["the biggest multi-system chiptune tracker!##sgab"].plurals[0] = "największy multi-platformowy tracker muzyczny!";
    strings["featuring DefleMask song compatibility.##sgab"].plurals[0] = "kompatybilny z Deflemaskiem.";

    strings["> CREDITS <##sgab"].plurals[0] = "> TWÓRCY <";
    strings["-- program --##sgab"].plurals[0] = "-- program właściwy --";
    strings["A M 4 N (intro tune)##sgab"].plurals[0] = "A M 4 N (muzyka w intro)";
    strings["-- graphics/UI design --##sgab"].plurals[0] = "-- grafika/projekt interfejsu użytkownika --";
    strings["-- documentation --##sgab"].plurals[0] = "-- dokumentacja --";
    strings["-- demo songs --##sgab"].plurals[0] = "-- utwory demonstracyjne --";
    strings["-- additional feedback/fixes --##sgab"].plurals[0] = "-- dodatkowe opinie/poprawki --";
    strings["-- translations and related work --##sgab"].plurals[0] = "-- tłumaczenia --";
    strings["LTVA1 (Russian translation)##sgab"].plurals[0] = "LTVA1 (tłumaczenie na język rosyjski)";
    strings["freq-mod (Polish translation)##sgab"].plurals[0] = "freq-mod (tłumaczenie na język polski)";

    strings["powered by:##sgab"].plurals[0] = "z użyciem następujących komponentów:";
    strings["Dear ImGui by Omar Cornut##sgab"].plurals[0] = "Dear ImGui autorstwa Omara Cornuta";
    strings["SDL2 by Sam Lantinga##sgab"].plurals[0] = "SDL2 autorstwa Sama Lantingi";
    strings["zlib by Jean-loup Gailly##sgab"].plurals[0] = "zlib autorstwa Jean-loupa Gailly'ego";
    strings["and Mark Adler##sgab"].plurals[0] = "i Marka Adlera";
    strings["libsndfile by Erik de Castro Lopo##sgab"].plurals[0] = "libsndfile autorstwa Erika de Castro Lopo";
    strings["Portable File Dialogs by Sam Hocevar##sgab"].plurals[0] = "Portable File Dialogs autorstwa Sama Hocevara";
    strings["Native File Dialog by Frogtoss Games##sgab"].plurals[0] = "Native File Dialog autorstwa Frogtoss Games";
    strings["Weak-JACK by x42##sgab"].plurals[0] = "Weak-JACK autorstwa x42";
    strings["RtMidi by Gary P. Scavone##sgab"].plurals[0] = "RtMidi autorstwa Gary'ego P. Scavone";
    strings["FFTW by Matteo Frigo and Steven G. Johnson##sgab"].plurals[0] = "FFTW autorstwa Matteo Frigo i Stevena G. Johnsona";
    strings["backward-cpp by Google##sgab"].plurals[0] = "backward-cpp autorstwa Google";
    strings["adpcm by superctr##sgab"].plurals[0] = "adpcm autorstwa superctr";
    strings["Nuked-OPL3/OPLL/OPM/OPN2/PSG by nukeykt##sgab"].plurals[0] = "Nuked-OPL3/OPLL/OPM/OPN2/PSG autorstwa nukeykt";
    strings["YM3812-LLE, YMF262-LLE and YMF276-LLE by nukeykt##sgab"].plurals[0] = "YM3812-LLE, YMF262-LLE i YMF276-LLE autorstwa nukeykt";
    strings["ymfm by Aaron Giles##sgab"].plurals[0] = "ymfm autorstwa Aarona Gilesa";
    strings["MAME SN76496 by Nicola Salmoria##sgab"].plurals[0] = "MAME SN76496 autorstwa Nicoli Salmorii";
    strings["MAME AY-3-8910 by Couriersud##sgab"].plurals[0] = "MAME AY-3-8910 autorstwa Couriersud";
    strings["with AY8930 fixes by Eulous, cam900 and Grauw##sgab"].plurals[0] = "z poprawkami dla AY8930 autorstwa Eulousa, cam900 i Grauwa";
    strings["MAME SAA1099 by Juergen Buchmueller and Manuel Abadia##sgab"].plurals[0] = "MAME SAA1099 autorstwa Juergena Buchmuellera i Manuela Abadii";
    strings["MAME Namco WSG by Nicola Salmoria and Aaron Giles##sgab"].plurals[0] = "MAME Namco WSG autorstwa Nicoli Salmorii i Aarona Gilesa";
    strings["MAME RF5C68 core by Olivier Galibert and Aaron Giles##sgab"].plurals[0] = "rdzeń MAME RF5C68 autorstwa Oliviera Galiberta i Aarona Gilesa";
    strings["MAME MSM5232 core by Jarek Burczynski and Hiromitsu Shioya##sgab"].plurals[0] = "rdzeń MAME MSM5232 autorstwa Jarka Burczyńskiego i Hiromitsu Shioyi";
    strings["MAME MSM6258 core by Barry Rodewald##sgab"].plurals[0] = "rdzeń MAME MSM6258 autorstwa Barry'ego Rodewalda";
    strings["MAME YMZ280B core by Aaron Giles##sgab"].plurals[0] = "rdzeń MAME YMZ280B autorstwa Aarona Gilesa";
    strings["MAME GA20 core by Acho A. Tang and R. Belmont##sgab"].plurals[0] = "rdzeń MAME GA20 autorstwa Acho A. Tanga i R. Belmonta";
    strings["MAME SegaPCM core by Hiromitsu Shioya and Olivier Galibert##sgab"].plurals[0] = "rdzeń MAME SegaPCM autorstwa Hiromitsu Shioyi i Oliviera Galiberta";
    strings["SAASound by Dave Hooper and Simon Owen##sgab"].plurals[0] = "SAASound autorstwa Dave'a Hoopera i Simona Owena";
    strings["SameBoy by Lior Halphon##sgab"].plurals[0] = "SameBoy autorstwa Liora Halphona";
    strings["Mednafen PCE, WonderSwan, T6W28 and Virtual Boy audio cores##sgab"].plurals[0] = "Rdzenie emulacji Mednafen PCE, WonderSwan, T6W28 i Virtual Boy";
    strings["SNES DSP core by Blargg##sgab"].plurals[0] = "rdzeń SNES DSP autorstwa Blargga";
    strings["puNES (NES, MMC5 and FDS) by FHorse##sgab"].plurals[0] = "puNES (NES, MMC5 i FDS) autorstwa FHorse";
    strings["NSFPlay (NES and FDS) by Brad Smith and Brezza##sgab"].plurals[0] = "NSFPlay (NES i FDS) autorstwa Brada Smitha i Brezza";
    strings["reSID by Dag Lem##sgab"].plurals[0] = "reSID autorstwa Daga Lema";
    strings["reSIDfp by Dag Lem, Antti Lankila##sgab"].plurals[0] = "reSIDfp autorstwa Daga Lema, Antti Lankili";
    strings["and Leandro Nini##sgab"].plurals[0] = "i Leandro Nini";
    strings["dSID by DefleMask Team based on jsSID##sgab"].plurals[0] = "dSID autorstwa ekipy DefleMaska (oparty o jsSID)";
    strings["Stella by Stella Team##sgab"].plurals[0] = "Stella autorstwa Stella Team";
    strings["QSound emulator by superctr and Valley Bell##sgab"].plurals[0] = "Emulator QSound-a autorstwa superctr i Valley Bella";
    strings["VICE VIC-20 sound core by Rami Rasanen and viznut##sgab"].plurals[0] = "Rdzeń emulacji VICE VIC-20 autorstwa Rami Rasanena i viznuta";
    strings["VICE TED sound core by Andreas Boose, Tibor Biczo##sgab"].plurals[0] = "Rdzeń emulacji VICE TED autorstwa Andreasa Boose;a, Tibora Biczo";
    strings["and Marco van den Heuvel##sgab"].plurals[0] = "i Marco van den Heuvela";
    strings["VERA sound core by Frank van den Hoef##sgab"].plurals[0] = "Rdzeń emulacji VERA autorstwa Franka van den Hoefa";
    strings["mzpokeysnd POKEY emulator by Michael Borisov##sgab"].plurals[0] = "mzpokeysnd (emulator POKEY-a) autorstwa Michaela Borisowa";
    strings["ASAP POKEY emulator by Piotr Fusik##sgab"].plurals[0] = "ASAP (emulator POKEY-a) autorstwa Piotra Fusika";
    strings["ported by laoo to C++##sgab"].plurals[0] = "przepisany na C++ przez laoo";
    strings["vgsound_emu (second version, modified version) by cam900##sgab"].plurals[0] = "vgsound_emu (wersja druga, zmodyfikowana) autorstwa cam900";
    strings["SM8521 emulator (modified version) by cam900##sgab"].plurals[0] = "Emulator SM8521 (wersja zmodyfikowana) autorstwa cam900";
    strings["D65010G031 emulator (modified version) by cam900##sgab"].plurals[0] = "Emulator D65010G031 (wersja zmodyfikowana) autorstwa cam900";
    strings["Namco C140/C219 emulator (modified version) by cam900##sgab"].plurals[0] = "Emulator C140/C219 (wersja zmodyfikowana) autorstwa cam900";
    strings["ESFMu emulator by Kagamiin~##sgab"].plurals[0] = "Emulator ESFMu autorstwa Kagamiin~";
    strings["PowerNoise emulator by scratchminer##sgab"].plurals[0] = "Emulator PowerNoise autorstwa scratchminera";
    strings["ep128emu by Istvan Varga##sgab"].plurals[0] = "ep128emu autorstwa Istvana Vargi";

    strings["greetings to:##sgab"].plurals[0] = "z pozdrowieniami dla:";
    strings["NEOART Costa Rica##sgab"].plurals[0] = "NEOART Costa Rica";
    strings["Xenium Demoparty##sgab"].plurals[0] = "Demoparty Xenium";
    strings["all members of Deflers of Noice!##sgab"].plurals[0] = "wszystkich członków Deflers of Noice!";

    strings["copyright © 2021-2024 tildearrow##sgab"].plurals[0] = "Wszelkie prawa zastrzeżone © 2021-2024 tildearrow";
    strings["(and contributors).##sgab"].plurals[0] = "(i innych współautorów).";
    strings["licensed under GPLv2+! see##sgab"].plurals[0] = "program na licencji GPLv2+!";
    strings["LICENSE for more information.##sgab"].plurals[0] = "więcej informacji w pliku LICENSE";

    strings["help Furnace grow:##sgab"].plurals[0] = "wesprzyj rozwój Furnace:";
    strings["help Furnace-B:##sgab"].plurals[0] = "wesprzyj rozwój Furnace-B:";

    strings["contact tildearrow at:##sgab"].plurals[0] = "skontaktuj się z tildearrow poprzez:";

    strings["disclaimer:##sgab"].plurals[0] = "uwaga:";
    strings["despite the fact this program works##sgab"].plurals[0] = "pomimo tego, że program działa";
    strings["with the .dmf file format, it is NOT##sgab"].plurals[0] = "na plikach formatu .dmf, NIE JEST";
    strings["affiliated with Delek or DefleMask in##sgab"].plurals[0] = "w żaden sposób powiązany z Delkiem bądź Deflemaskiem,";
    strings["any way, nor it is a replacement for##sgab"].plurals[0] = "nie jest również zamiennikiem";
    strings["the original program.##sgab"].plurals[0] = "oryginalnego programu.";

    strings["it also comes with ABSOLUTELY NO WARRANTY.##sgab"].plurals[0] = "jest również udostępniany BEZ JAKIELKOWIEK FORMY GWARANCJI.";

    strings["thanks to all contributors/bug reporters!##sgab"].plurals[0] = "dziękujemy wszystkim współautorom i testerom!";

    //src/gui/channels.cpp

    strings["Pat##sgch"].plurals[0] = "Wz.";
    strings["Osc##sgch"].plurals[0] = "Osc.";
    strings["Swap##sgch"].plurals[0] = "Zamien";
    strings["Name##sgch"].plurals[0] = "Nazwa";
    strings["Show in pattern##sgch"].plurals[0] = "Pokaz w oknie wzorcow";
    strings["Show in per-channel oscilloscope##sgch"].plurals[0] = "Pokaż w oknie oscyloskopu dla poszegolnych kanałów";
    strings["%s #%d\n(drag to swap channels)##sgch"].plurals[0] = "%s #%d\n(przeciągnij by zamienić miejscami kanały)";

    //src/gui/chanOsc.cpp

    strings["None (0%)##sgco"].plurals[0] = "Brak (0%)";
    strings["None (50%)##sgco"].plurals[0] = "Brak (50%)";
    strings["None (100%)##sgco"].plurals[0] = "Brak (100%)";
    strings["Frequency##sgco"].plurals[0] = "Czestotliwosc";
    strings["Volume##sgco"].plurals[0] = "Głośność";
    strings["Channel##sgco"].plurals[0] = "Kanal";
    strings["Brightness##sgco"].plurals[0] = "Jasnosc";
    strings["Note Trigger##sgco"].plurals[0] = "Nowa nuta";
    strings["Off##sgco"].plurals[0] = "Wyl.";
    strings["Mode 1##sgco"].plurals[0] = "Tryb 1";
    strings["Mode 2##sgco"].plurals[0] = "Tryb 2";
    strings["Mode 3##sgco"].plurals[0] = "Tryb 3";

    strings["Columns##sgco"].plurals[0] = "Kolumny";
    strings["Size (ms)##sgco"].plurals[0] = "Rozmiar (w ms)";
    strings["Automatic columns##sgco"].plurals[0] = "Automatyczna ilość kolumn";
    strings["Center waveform##sgco"].plurals[0] = "Centruj fale";
    strings["Randomize phase on note##sgco"].plurals[0] = "Losowa faza przy nowej nucie";
    strings["Amplitude##sgco"].plurals[0] = "Amplituda";
    strings["Gradient##sgco"].plurals[0] = "Gradient";
    strings["Color##sgco0"].plurals[0] = "Kolor";
    strings["Distance##sgco"].plurals[0] = "Dystans";
    strings["Spread##sgco"].plurals[0] = "Rozmycie";
    strings["Remove##sgco"].plurals[0] = "usuń";
    strings["Background##sgco"].plurals[0] = "Kolor tla";
    strings["X Axis##AxisX"].plurals[0] = "Oś X##AxisX";
    strings["Y Axis##AxisY"].plurals[0] = "Oś Y##AxisY";
    strings["Color##sgco1"].plurals[0] = "Kolor";
    strings["Text format:##sgco"].plurals[0] = "Formatowanie tekstu:";

    strings["format guide:\n"
            "- %c: channel name\n"
            "- %C: channel short name\n"
            "- %d: channel number (starting from 0)\n"
            "- %D: channel number (starting from 1)\n"
            "- %n: channel note\n"
            "- %i: instrument name\n"
            "- %I: instrument number (decimal)\n"
            "- %x: instrument number (hex)\n"
            "- %s: chip name\n"
            "- %p: chip part number\n"
            "- %S: chip ID\n"
            "- %v: volume (decimal)\n"
            "- %V: volume (percentage)\n"
            "- %b: volume (hex)\n"
            "- %l: new line\n"
            "- %%: percent sign##sgco"].plurals[0] = 

            "instrukcja formatowania:\n"
            "- %c: nazwa kanału\n"
            "- %C: krotka nazwa kanału\n"
            "- %d: numer kanału (zaczynajac od 0)\n"
            "- %D: numer kanału (zaczynajac od 1)\n"
            "- %n: nuta kanału\n"
            "- %i: nazwa instrumenty\n"
            "- %I: numer instrumentu (dziesietny)\n"
            "- %x: numer instrumnety (szesnastkowy)\n"
            "- %s: nazwa ukladu\n"
            "- %p: numer wewnetrzny ukladu\n"
            "- %S: ID ukladu\n"
            "- %v: Głośność (dziesietna)\n"
            "- %V: Głośność (w procentach)\n"
            "- %b: Głośność (szesnastkowa)\n"
            "- %l: nowy wiersz\n"
            "- %%: znak procenta";

    strings["Text color##sgco"].plurals[0] = "Kolor tekstu";
    strings["Error!##sgco"].plurals[0] = "Blad!";
    strings["\nquiet##sgco"].plurals[0] = "\ncicho";

    //src/gui/clock.cpp

    strings["Clock###Clock"].plurals[0] = "Zegar###Clock";

    //   sgcf  src/gui/compatFlags.cpp

    strings["Compatibility Flags###Compatibility Flags"].plurals[0] = "Flagi kompatybilności###Compatibility Flags";
    strings["these flags are designed to provide better DefleMask/older Furnace compatibility.\nit is recommended to disable most of these unless you rely on specific quirks.##sgcf"].plurals[0] = "эти флаги предназначены для лучшей совместимости с DefleMask/стрыми версиями Furnace.\nрекомендуется отключать большинство из них, если вы не полагаетесь на специфику работы программы, которую они обеспечивают.";
    strings["Game Boy instrument duty is wave volume##sgcf"].plurals[0] = "Макрос скважности инструмента Game Boy контролирует громкость канала волновых таблиц";
    strings["if enabled, an instrument with duty macro in the wave channel will be mapped to wavetable volume.##sgcf"].plurals[0] = "при включении макрос скважности инструмента будет назначен для контроля громкости канала волновых таблиц.";
    strings["Restart macro on portamento##sgcf"].plurals[0] = "Перезапуск макроса при портаменто";
    strings["when enabled, a portamento effect will reset the channel's macro if used in combination with a note.##sgcf"].plurals[0] = "при включении этого флага эффект портаменто, будучи размещённым рядом с нотой, будет перезапускать макросы инструмента.";
    strings["Ignore duplicate slide effects##sgcf"].plurals[0] = "Игнорировать дублирующиеся эффекты авто-портаменто";
    strings["if this is on, only the first slide of a row in a channel will be considered.##sgcf"].plurals[0] = "при включении этого флага только первый эффект авто-портаменто в данной строке будет эффективен.";
    strings["Ignore 0Dxx on the last order##sgcf"].plurals[0] = "Игнорировать 0Dxx на последней строке матрицы паттернов";
    strings["if this is on, a jump to next row effect will not take place when it is on the last order of a song.##sgcf"].plurals[0] = "при включении флага эффект прыжка на следующий паттерн не будет работать, если паттерн проигрывается в последней строке матрицы паттернов.";
    strings["Don't apply Game Boy envelope on note-less instrument change##sgcf"].plurals[0] = "nie uzywaj obwiedni Game Boya przy zmianie instrumntu bez nuty";
    strings["if this is on, an instrument change will not affect the envelope.##sgcf"].plurals[0] = "при включении этого флага смена инструмента без смены ноты не будет влиять на огибающую.";
    strings["Ignore DAC mode change outside of intended channel in ExtCh mode##sgcf"].plurals[0] = "Игнорировать переключение режима ЦАП, если оно не происходит на соответствующем канале, в режиме расширенного канала";
    strings["if this is on, 17xx has no effect on the operator channels in YM2612.##sgcf"].plurals[0] = "при включении этого флага 17xx не работает, если размещён на каналах операторов расширенного канала (для YM2612).";
    strings["SN76489 duty macro always resets phase##sgcf"].plurals[0] = "Макрос скважности SN76489 всегда сбрасывает фазу";
    strings["when enabled, duty macro will always reset phase, even if its value hasn't changed.##sgcf"].plurals[0] = "при включении этого флага макрос скважности всегда будет сбрасывать фазу, даже если значение скважности не меняется.";
    strings["Don't persist volume macro after it finishes##sgcf"].plurals[0] = "Не удерживать значение макроса громкости после его завершения";
    strings["when enabled, a value in the volume column that happens after the volume macro is done will disregard the macro.##sgcf"].plurals[0] = "при включении этого флага значение в столбце громкости, расположенное после завершения макроса громкости, не будет учитывать значение макроса.";
    strings[".mod import##sgcf"].plurals[0] = "импорт .mod";
    strings["Don't slide on the first tick of a row##sgcf"].plurals[0] = "Не исполнять авто-портаменто в первый шаг движка трекера каждой строки";
    strings["simulates ProTracker's behavior of not applying volume/pitch slides on the first tick of a row.##sgcf"].plurals[0] = "симулирует поведение программы ProTracker, которая не исполняет изменения громкости и частоты на первом шаге движка каждого столбца.";
    strings["Reset arpeggio position on row change##sgcf"].plurals[0] = "Перезапуск позиции арпеджио при продвижении по строкам паттерна";
    strings["simulates ProTracker's behavior of arpeggio being bound to the current tick of a row.##sgcf"].plurals[0] = "симулирует поведение программы ProTracker, которая привязывает исполнение арпеджио к номеру шага движка в каждой строке паттерна.";
    strings["Pitch/Playback##sgcf"].plurals[0] = "Частота/Воспроизведение";
    strings["Pitch linearity:##sgcf"].plurals[0] = "Линейность частоты (в долях полутонов):";
    strings["None##sgcf"].plurals[0] = "Нет (прямая работа с частотой)";
    strings["like ProTracker/FamiTracker##sgcf"].plurals[0] = "tak jak ProTracker/FamiTracker";
    strings["Full##sgcf"].plurals[0] = "Полная";
    strings["like Impulse Tracker##sgcf"].plurals[0] = "tak jak Impulse Tracker";
    strings["Pitch slide speed multiplier##sgcf"].plurals[0] = "Множитель скорости команды авто-портаменто";
    strings["Loop modality:##sgcf"].plurals[0] = "Работа зацикливания:";
    strings["Reset channels##sgcf"].plurals[0] = "Reset kanałów";
    strings["select to reset channels on loop. may trigger a voltage click on every loop!##sgcf"].plurals[0] = "выберите для перезапуска каналов каждый раз в начале цикла. может вызывать щелчок в каждом начале цикла из-за смены напряжения!";
    strings["Soft reset channels##sgcf"].plurals[0] = "Miękki reset kanałów";
    strings["select to turn channels off on loop.##sgcf"].plurals[0] = "выберите для отключения каналов в начале цикла.";
    strings["Do nothing##sgcf"].plurals[0] = "Nie rób nic";
    strings["select to not reset channels on loop.##sgcf"].plurals[0] = "выберите, чтобы отключить перезапуск каналов в начале цикла.";
    strings["Cut/delay effect policy:##sgcf"].plurals[0] = "Поведение эффектов заглушения/задержки ноты:";
    strings["Strict##sgcf"].plurals[0] = "Ścisły";
    strings["only when time is less than speed (like DefleMask/ProTracker)##sgcf"].plurals[0] = "только в случае, когда параметр меньше скорости (как DefleMask/ProTracker)";
    strings["Lax##sgcf"].plurals[0] = "Luźny";
    strings["no checks##sgcf"].plurals[0] = "bez sprawdzania";
    strings["Simultaneous jump (0B+0D) treatment:##sgcf"].plurals[0] = "Поведение при одновременном прыжке (0B+0D):";
    strings["Normal##sgcf"].plurals[0] = "Нормальное";
    strings["accept 0B+0D to jump to a specific row of an order##sgcf"].plurals[0] = "принять 0B+0D как прыжок на конкретную строку паттерна на конкретной позиции матрицы паттернов";
    strings["Other##sgcf"].plurals[0] = "Другое";
    strings["Auto-insert one tick gap between notes##sgcf"].plurals[0] = "Автоматически вставлять паузу в 1 шаг движка между нотами";
    strings["when enabled, a one-tick note cut will be inserted between non-legato/non-portamento notes.\nthis simulates the behavior of some Amiga/SNES music engines.\n\nineffective on C64.##sgcf"].plurals[0] = "при включении этого флага между нотами без эффекта легато и авто-портаменто будет вставлено заглушение ноты длиной в один шаг движка.\nэто симуляция повдения некоторых музыкальных драйверов Amiga/SNES.\n\nничего не меняет для C64.";
    strings["Don't reset slides after note off##sgcf"].plurals[0] = "Не переинициализировать авто-портаменто после окончания ноты";
    strings["when enabled, note off will not reset the channel's slide effect.##sgcf"].plurals[0] = "при включении этого флага окончание ноты не будет останавливать авто-портаменто на этом канале.";
    strings["Don't reset portamento after reaching target##sgcf"].plurals[0] = "Не переинициализировать авто-портаменто после достижения цели";
    strings["when enabled, the slide effect will not be disabled after it reaches its target.##sgcf"].plurals[0] = "при включении этого флага эффект авто-портаменто не будет переинициализирован при достижении целевой частоты.";
    strings["Continuous vibrato##sgcf"].plurals[0] = "Непрерывное вибрато";
    strings["when enabled, vibrato phase/position will not be reset on a new note.##sgcf"].plurals[0] = "при включении этого флага фаза/положение вибрато не будут сбрасываться на новой ноте.";
    strings["Pitch macro is not linear##sgcf"].plurals[0] = "Нелинейный макрос частоты";
    strings["when enabled, the pitch macro of an instrument is in frequency/period space.##sgcf"].plurals[0] = "при включении этого флага макрос частоты будет работать относительно периода/частоты, а не долей полутона.";
    strings["Reset arpeggio effect position on new note##sgcf"].plurals[0] = "Сбрасывать положение эффекта арпеджио на новой ноте";
    strings["when enabled, arpeggio effect (00xy) position is reset on a new note.##sgcf"].plurals[0] = "при включении этого флага положение эффекта арпеджио (00xy) сбрасывается на новой ноте.";
    strings["Volume scaling rounds up##sgcf"].plurals[0] = "Масштабирование громкости округляется вверх";
    strings["when enabled, volume macros round up when applied\nthis prevents volume scaling from causing vol=0, which is silent on some chips\n\nineffective on logarithmic channels##sgcf"].plurals[0] = "при включении этого флага значения макросов громкости округляются вверх\nэто предотвращает возникновение ситуации vol=0 при масштабировании громкости, что приводит к заглушению на некоторых чипах\n\nне эффективно на чипах с логарифмическим контролем громкости";

    //   sgdl  src/gui/dataList.cpp

    strings["Bug!##sgdl"].plurals[0] = "Blad!";
    strings["Unknown##sgdl"].plurals[0] = "Nieznany typ instrumnety";
    strings["duplicate##sgdl0"].plurals[0] = "duplikuj";
    strings["replace...##sgdl0"].plurals[0] = "zamień...";
    strings["save##sgdl0"].plurals[0] = "zapisz";
    strings["export (.dmp)##sgdl"].plurals[0] = "eksportuj .dmp";
    strings["delete##sgdl0"].plurals[0] = "usuń";
    strings["%.2X: <INVALID>##sgdl"].plurals[0] = "%.2X: <NIEPOPRAWNY.>";
    strings["- None -##sgdl"].plurals[0] = "- brak -";
    strings["out of memory for this sample!##sgdl"].plurals[0] = "brak miejsca w pamięci dla tego sampla!";
    strings["make instrument##sgdl"].plurals[0] = "stwórz instrument";
    strings["make me a drum kit##sgdl"].plurals[0] = "stwórz zestaw perkusji";
    strings["duplicate##sgdl1"].plurals[0] = "duplikuj";
    strings["replace...##sgdl1"].plurals[0] = "zamień...";
    strings["save##sgdl1"].plurals[0] = "zapisz";
    strings["delete##sgdl1"].plurals[0] = "usuń";
    strings["Add##sgdl0"].plurals[0] = "Dodaj";
    strings["Duplicate##sgdl2"].plurals[0] = "Sklonuj";
    strings["Open##sgdl0"].plurals[0] = "Otwórz";
    strings["replace instrument...##sgdl"].plurals[0] = "zamień instrument...";
    strings["load instrument from TX81Z##sgdl"].plurals[0] = "zaladuj instrument z TX81Z";
    strings["replace wavetable...##sgdl"].plurals[0] = "zamień tablice fal...";
    strings["replace sample...##sgdl"].plurals[0] = "zamień sampel...";
    strings["import raw sample...##sgdl"].plurals[0] = "importuj surowy sampel...";
    strings["import raw sample (replace)...##sgdl"].plurals[0] = "importuj surowy sampel (zamień)...";
    strings["replace...##sgdl2"].plurals[0] = "zamień...";
    strings["load from TX81Z##sgdl"].plurals[0] = "zaladuj z TX81Z";
    strings["Open (insert; right-click to replace)##sgdl"].plurals[0] = "Otwórz (wstaw; PPM by zastapic)";
    strings["Save##sgdl2"].plurals[0] = "Zapisz";
    strings["save instrument as .dmp...##sgdl"].plurals[0] = "zapisz instrument jako .dmp...";
    strings["save wavetable as .dmw...##sgdl"].plurals[0] = "zapisz tablice fal jako .dmw...";
    strings["save raw wavetable...##sgdl"].plurals[0] = "zapisz surowa tablice fal...";
    strings["save raw sample...##sgdl"].plurals[0] = "zapisz surowy sampel";
    strings["save as .dmp...##sgdl"].plurals[0] = "zapisz jako .dmp...";
    strings["Toggle folders/standard view##sgdl0"].plurals[0] = "Przełącz między widokiem złożonym i normalnym";
    strings["Move up##sgdl0"].plurals[0] = "Przesuń w góre o jedną pozycję";
    strings["Move down##sgdl0"].plurals[0] = "Przesuń w dół o jedną pozycję";
    strings["Create##sgdl0"].plurals[0] = "Stwórz";
    strings["New folder##sgdl0"].plurals[0] = "Nowy folder";
    strings["Preview (right click to stop)##sgdl0"].plurals[0] = "Podglad (PPM aby zatrzymac)";
    strings["Delete##sgdl2"].plurals[0] = "Usuń";
    strings["Instruments##sgdl"].plurals[0] = "Instrumenty";
    strings["<uncategorized>##sgdl0"].plurals[0] = "<bez kategorii>";
    strings["rename...##sgdl0"].plurals[0] = "zmień nazwe...";
    strings["delete##sgdl3"].plurals[0] = "usuń";
    strings["Wavetables##sgdl"].plurals[0] = "Tablice fal";
    strings["Samples##sgdl"].plurals[0] = "Sample";
    strings["Add##sgdl1"].plurals[0] = "Dodaj";
    strings["Duplicate##sgdl3"].plurals[0] = "Sklonuj";
    strings["Open##sgdl1"].plurals[0] = "Otwórz";
    strings["replace...##sgdl3"].plurals[0] = "zamień...";
    strings["Save##sgdl3"].plurals[0] = "Zapisz";
    strings["save as .dmw...##sgdl"].plurals[0] = "zapisz jako .dmw...";
    strings["save raw...##sgdl0"].plurals[0] = "zapisz dane surowe...";
    strings["Toggle folders/standard view##sgdl1"].plurals[0] = "Przełączanie między widokiem złożonym i normalnym";
    strings["Move up##sgdl1"].plurals[0] = "Przesun w gore o jedną pozycję";
    strings["Move down##sgdl1"].plurals[0] = "Przesun w dół o jedną pozycję";
    strings["Create##sgdl1"].plurals[0] = "Stwórz";
    strings["New folder##sgdl1"].plurals[0] = "Nowy folder";
    strings["Delete##sgdl4"].plurals[0] = "usuń";
    strings["Add##sgdl2"].plurals[0] = "Dodaj";
    strings["Duplicate##sgdl4"].plurals[0] = "Sklonuj";
    strings["Open##sgdl2"].plurals[0] = "Otwórz";
    strings["replace...##sgdl4"].plurals[0] = "zamień...";
    strings["import raw...##sgdl"].plurals[0] = "importuj dane surowe...";
    strings["import raw (replace)...##sgdl"].plurals[0] = "importuj dane surowe (zamień)...";
    strings["Save##sgdl4"].plurals[0] = "Zapisz";
    strings["save raw...##sgdl1"].plurals[0] = "zapisz dane surowe...";
    strings["Toggle folders/standard view##sgdl2"].plurals[0] = "Przełączanie między widokiem złożonym i normalnym";
    strings["Move up##sgdl2"].plurals[0] = "Przesun w gore o jedną pozycję";
    strings["Move down##sgdl2"].plurals[0] = "Przesun w dół o jedną pozycję";
    strings["Create##sgdl2"].plurals[0] = "Stwórz";
    strings["New folder##sgdl2"].plurals[0] = "Nowy folder";
    strings["Preview (right click to stop)##sgdl1"].plurals[0] = "Podglad (PPM by zatrzymac)";
    strings["Delete##sgdl5"].plurals[0] = "Usuń";
    strings["<uncategorized>##sgdl1"].plurals[0] = "<bez kategorii>";
    strings["rename...##sgdl1"].plurals[0] = "zmien nazwe...";
    strings["delete##sgdl6"].plurals[0] = "usuń";
    strings["rename...##sgdl2"].plurals[0] = "zmien nazwe...";
    strings["Delete##sgdl7"].plurals[0] = "Usuń";

    //src/gui/gui.cpp

    strings["Instrument %d##sggu"].plurals[0] = "Instrument %d";
    strings["Sample %d"].plurals[0] = "Sampel %d";
    strings["the song is over!##sggu0"].plurals[0] = "koniec piosenki!";
    strings["the song is over!##sggu1"].plurals[0] = "koniec piosenki!";
    strings["Open File##sggu"].plurals[0] = "Otwórz plik";
    strings["compatible files##sggu0"].plurals[0] = "kompatybilne pliki";
    strings["all files##sggu0"].plurals[0] = "wszystkie pliki";
    strings["no backups made yet!##sggu"].plurals[0] = "nie utworzono jeszcze zadnych kopii zapasowych";
    strings["Restore Backup##sggu"].plurals[0] = "Wczytaj kopie zapasowa";
    strings["Furnace song##sggu0"].plurals[0] = "Piosenka Furnace";
    strings["Save File##sggu0"].plurals[0] = "Zapisz plik";
    strings["DefleMask 1.1.3 module##sggu"].plurals[0] = "piosenka DefleMask 1.1.3";
    strings["Save File##sggu1"].plurals[0] = "Zapisz plik";
    strings["DefleMask 1.0/legacy module##sggu"].plurals[0] = "piosenka DefleMask 1.0/legacy";
    strings["Save File##sggu2"].plurals[0] = "Zapisz plik";
    strings["Furnace song##sggu1"].plurals[0] = "modul Furnace";
    strings["Load Instrument##sggu"].plurals[0] = "Wczytaj instrument";
    strings["all compatible files##sggu1"].plurals[0] = "wszystkie kompatybilne pliki";
    strings["Furnace instrument##sggu0"].plurals[0] = "instrument Furnace";
    strings["DefleMask preset##sggu0"].plurals[0] = "preset DefleMaska";
    strings["TFM Music Maker instrument##sggu"].plurals[0] = "instrument programu TFM Music Maker";
    strings["VGM Music Maker instrument##sggu"].plurals[0] = "instrument programu VGM Music Maker";
    strings["Scream Tracker 3 instrument##sggu"].plurals[0] = "instrument programu Scream Tracker 3";
    strings["SoundBlaster instrument##sggu"].plurals[0] = "instrument SoundBlaster";
    strings["Wohlstand OPL instrument##sggu"].plurals[0] = "instrument typu Wohlstand OPL";
    strings["Wohlstand OPN instrument##sggu"].plurals[0] = "instrument typu Wohlstand OPN";
    strings["Gens KMod patch dump##sggu"].plurals[0] = "zrzut z Gens KMod";
    strings["BNK file (AdLib)##sggu"].plurals[0] = "bank brzmien BNK (AdLib)";
    strings["FF preset bank##sggu"].plurals[0] = "bank presetow FF";
    strings["2612edit GYB preset bank##sggu"].plurals[0] = "bank presetow 2612edit GYB";
    strings["VOPM preset bank##sggu"].plurals[0] = "bank presetow VOPM";
    strings["Wohlstand WOPL bank##sggu"].plurals[0] = "bank brzmien Wohlstand WOPL";
    strings["Wohlstand WOPN bank##sggu"].plurals[0] = "bank brzmien Wohlstand WOPN";
    strings["all files##sggu1"].plurals[0] = "wszystkie pliki";
    strings["Save Instrument##sggu0"].plurals[0] = "Zapisz instrument";
    strings["Furnace instrument##sggu1"].plurals[0] = "instrument Furnace";
    strings["Save Instrument##sggu1"].plurals[0] = "Zapisz instrument";
    strings["DefleMask preset##sggu1"].plurals[0] = "preset DefleMaska";
    strings["Load Wavetable##sggu"].plurals[0] = "Wczytaj tablice fal";
    strings["compatible files##sggu2"].plurals[0] = "kompatybilne pliki";
    strings["all files##sggu2"].plurals[0] = "wszystkie pliki";
    strings["Save Wavetable##sggu0"].plurals[0] = "Zapisz tablice fal";
    strings["Furnace wavetable##sggu"].plurals[0] = "Tablica fal Furnace";
    strings["Save Wavetable##sggu1"].plurals[0] = "Zapisz tablice fal";
    strings["DefleMask wavetable##sggu"].plurals[0] = "Tablica fal DefleMaska";
    strings["Save Wavetable##sggu2"].plurals[0] = "Zapisz tablice fal";
    strings["raw data##sggu"].plurals[0] = "surowe dane";
    strings["Load Sample##sggu"].plurals[0] = "Wczytaj sampel";
    strings["compatible files##sggu3"].plurals[0] = "kompatybilne formaty plikow";
    strings["all files##sggu3"].plurals[0] = "wszystkie pliki";
    strings["Load Raw Sample##sggu"].plurals[0] = "Wczytaj surowy sampel";
    strings["all files##sggu4"].plurals[0] = "wszystkie pliki";
    strings["Save Sample##sggu"].plurals[0] = "Zapisz sampel";
    strings["Wave file##sggu0"].plurals[0] = "plik WAV";
    strings["Save Raw Sample##sggu"].plurals[0] = "Zapisz surowy sampel";
    strings["all files##sggu5"].plurals[0] = "wszystkie pliki";
    strings["Export Audio##sggu0"].plurals[0] = "Eksportuj audio";
    strings["Wave file##sggu1"].plurals[0] = "plik WAV";
    strings["Export Audio##sggu1"].plurals[0] = "Eksportuj audio";
    strings["Wave file##sggu2"].plurals[0] = "plik WAV";
    strings["Export Audio##sggu2"].plurals[0] = "Eksportuj audio";
    strings["Wave file##sggu3"].plurals[0] = "plik WAV";
    strings["Export VGM##sggu"].plurals[0] = "Eksportuj VGM";
    strings["VGM file##sggu"].plurals[0] = "plik VGM";
    strings["Export ZSM##sggu"].plurals[0] = "Eksportuj ZSM";
    strings["ZSM file##sggu"].plurals[0] = "plik ZSM";
    strings["Export Command Stream##sggu0"].plurals[0] = "Eksportuj strumień komend";
    strings["text file##sggu0"].plurals[0] = "plik tekstowy";
    strings["Export Command Stream##sggu1"].plurals[0] = "eksportuj strumień komend";
    strings["text file##sggu1"].plurals[0] = "plik tekstowy";
    strings["Export Command Stream##sggu2"].plurals[0] = "eksportuj strumień komend";
    strings["binary file##sggu"].plurals[0] = "plik binarny";
    strings["Coming soon!##sggu"].plurals[0] = "Juz wkrótce!";
    strings["Select Font##sggu0"].plurals[0] = "Wybierz czcionkę";
    strings["compatible files##sggu4"].plurals[0] = "kompatybilne pliki";
    strings["Select Font##sggu1"].plurals[0] = "Wybierz czcionkę";
    strings["compatible files##sggu5"].plurals[0] = "kompatybilne pliki";
    strings["Select Font##sggu2"].plurals[0] = "Wybierz czcionkę";
    strings["compatible files##sggu6"].plurals[0] = "kompatybilne pliki";
    strings["Select Color File##sggu"].plurals[0] = "Wybierz plik z ustawieniami kolorów";
    strings["configuration files##sggu0"].plurals[0] = "pliki konfiguracji";
    strings["Select Keybind File##sggu"].plurals[0] = "Wybierz plik z przypisaniami klawiszy";
    strings["configuration files##sggu1"].plurals[0] = "pliki konfiguracji";
    strings["Select Layout File##sggu"].plurals[0] = "Wybierz plik z ustawieniami ukladu okna";
    strings[".ini files##sggu0"].plurals[0] = "pliki .ini";
    strings["Export Colors##sggu"].plurals[0] = "eksportuj ustawienia kolorow";
    strings["configuration files##sggu2"].plurals[0] = "pliki konfiguracji";
    strings["Export Keybinds##sggu"].plurals[0] = "eksportuj przypisania klawiszy";
    strings["configuration files##sggu3"].plurals[0] = "pliki konfiguracji";
    strings["Export Layout##sggu"].plurals[0] = "eksportuj uklad okna";
    strings[".ini files##sggu1"].plurals[0] = "pliki .ini";
    strings["Load ROM##sggu"].plurals[0] = "wczytaj ROM";
    strings["compatible files##sggu7"].plurals[0] = "kompatybilne pliki";
    strings["all files##sggu6"].plurals[0] = "wszystkie pliki";
    strings["Play Command Stream##sggu"].plurals[0] = "odtwarzaj strumień komend";
    strings["command stream##sggu"].plurals[0] = "strumień komend";
    strings["all files##sggu7"].plurals[0] = "wszystkie pliki";
    strings["Open Test##sggu"].plurals[0] = "Otwórz test";
    strings["compatible files##sggu8"].plurals[0] = "kompatybilne pliki";
    strings["another option##sggu0"].plurals[0] = "inna opcja";
    strings["all files##sggu8"].plurals[0] = "wszystkie pliki";
    strings["Open Test (Multi)##sggu"].plurals[0] = "Otwórz test (wiele plików)";
    strings["compatible files##sggu9"].plurals[0] = "kompatybilne pliki";
    strings["another option##sggu1"].plurals[0] = "inna opcja";
    strings["all files##sggu9"].plurals[0] = "wszystkie pliki";
    strings["Save Test##sggu"].plurals[0] = "Zapisz test";
    strings["Furnace song##sggu"].plurals[0] = "piosenka Furnace";
    strings["DefleMask module##sggu"].plurals[0] = "modul DefleMask";
    strings["you have loaded a backup!\nif you need to, please save it somewhere.\n\nDO NOT RELY ON THE BACKUP SYSTEM FOR AUTO-SAVE!\nFurnace will not save backups of backups.##sggu"].plurals[0] = "wczytano kopie zapasowa!\njeśli to konieczne, zapisz ją w innym miejscu.\n\nSYSTEM KOPII ZAPASOWYCH NIE JEST SYSTEMEM ZAPISU AUTOMATYCZNEGO!\nFurnace nie zapisuje kopii zapasowych kopii zapasowych.";
    strings["cut##sggu"].plurals[0] = "wytnij";
    strings["copy##sggu"].plurals[0] = "kopiuj";
    strings["paste##sggu0"].plurals[0] = "wklej";
    strings["paste special...##sggu"].plurals[0] = "wklej specjalne...";
    strings["paste mix##sggu"].plurals[0] = "wstaw i nałóż";
    strings["paste mix (background)##sggu"].plurals[0] = "wklej (zastąp istniejący)";
    strings["paste with ins (foreground)##sggu"].plurals[0] = "wklej na wierzch instrument (bez zastępowania istniejącego)";
    strings["no instruments available##sggu0"].plurals[0] = "brak dostepnych instrumentow";
    strings["paste with ins (background)##sggu"].plurals[0] = "wklej instrumnet na wierzch (zastępując istniejący)";
    strings["no instruments available##sggu1"].plurals[0] = "brak dostępnych instrumentów";
    strings["paste flood##sggu"].plurals[0] = "wstaw z buforem, powtarzając cykl (do końca wzorca)";
    strings["paste overflow##sggu"].plurals[0] = "wstaw (z możliwym przejściem do następnego wzoru))";
    strings["delete##sggu0"].plurals[0] = "usuń";
    strings["select all##sggu"].plurals[0] = "wybierz wszystko";
    strings["operation mask...##sggu"].plurals[0] = "maska operacji...";
    strings["delete##sggu1"].plurals[0] = "usuń";
    strings["pull delete##sggu"].plurals[0] = "usuń z zaciągnięciem następujących rzędów";
    strings["insert##sggu"].plurals[0] = "wstaw pusty rząd";
    strings["paste##sggu1"].plurals[0] = "wklej";
    strings["transpose (note)##sggu"].plurals[0] = "transponuj nutę";
    strings["transpose (value)##sggu"].plurals[0] = "transponuj (parametry))";
    strings["interpolate##sggu0"].plurals[0] = "interpoluj";
    strings["fade##sggu"].plurals[0] = "zanikaj";
    strings["invert values##sggu0"].plurals[0] = "odwróć parametry";
    strings["scale##sggu"].plurals[0] = "skaluj";
    strings["randomize##sggu"].plurals[0] = "wypełnij losowymi wartościami";
    strings["flip##sggu"].plurals[0] = "odwróć";
    strings["collapse/expand##sggu"].plurals[0] = "skróć/rozszerz";
    strings["input latch##sggu"].plurals[0] = "bufor wejścia";
    strings["&&: selected instrument\n..: no instrument##sggu"].plurals[0] = "&&: wybrany instrument\n..: brak instrumentu";
    strings["Set##sggu"].plurals[0] = "Ustaw";
    strings["Reset##sggu"].plurals[0] = "Resetuj";
    strings["note up##sggu"].plurals[0] = "półton wyżej";
    strings["note down##sggu"].plurals[0] = "półton niżej";
    strings["octave up##sggu"].plurals[0] = "oktawa wyżej";
    strings["octave down##sggu"].plurals[0] = "oktawa niżej";
    strings["values up##sggu"].plurals[0] = "parametr wyżej";
    strings["values down##sggu"].plurals[0] = "parametr niżej";
    strings["values up (+16)##sggu"].plurals[0] = "parametr wyżej (+16)";
    strings["values down (-16)##sggu"].plurals[0] = "parametr niżej (-16)";
    strings["transpose##sggu"].plurals[0] = "transponuj";
    strings["Notes##sggu"].plurals[0] = "Nuty";
    strings["Values##sggu"].plurals[0] = "Parametry";
    strings["interpolate##sggu1"].plurals[0] = "interpoluj";
    strings["change instrument...##sggu"].plurals[0] = "zmień instrument...";
    strings["no instruments available##sggu"].plurals[0] = "żaden instrument nie jest dostepny";
    strings["gradient/fade...##sggu"].plurals[0] = "gradient/zanikanie...";
    strings["Start##sggu"].plurals[0] = "Poczatek";
    strings["End##sggu"].plurals[0] = "Koniec";
    strings["Nibble mode##sggu0"].plurals[0] = "Tryb półbajtow";
    strings["Go ahead##sggu"].plurals[0] = "Zastosuj";
    strings["scale...##sggu"].plurals[0] = "skaluj...";
    strings["Scale##sggu"].plurals[0] = "Skaluj";
    strings["randomize...##sggu"].plurals[0] = "wypełnij losowymi wartościami...";
    strings["Minimum##sggu"].plurals[0] = "Dolna granica";
    strings["Maximum##sggu"].plurals[0] = "Gorna granica";
    strings["Nibble mode##sggu1"].plurals[0] = "Tryb półbajtow";
    strings["Randomize##sggu"].plurals[0] = "Losuj";
    strings["invert values##sggu1"].plurals[0] = "odwróć wartości";
    strings["flip selection##sggu"].plurals[0] = "odwróć wybrany obszar";
    strings["collapse/expand amount##CollapseAmount"].plurals[0] = "współczynnik skracania/rozszerzania##CollapseAmount";
    strings["collapse##sggu"].plurals[0] = "skroc";
    strings["expand##sggu"].plurals[0] = "rozszerz";
    strings["collapse pattern##sggu"].plurals[0] = "skróć wzorzec";
    strings["expand pattern##sggu"].plurals[0] = "rozszerz wzorzec";
    strings["collapse song##sggu"].plurals[0] = "skróć utwor";
    strings["expand song##sggu"].plurals[0] = "rozszerz utwor";
    strings["find/replace##sggu"].plurals[0] = "znajdź/zamień";
    strings["Furnace has been started in Safe Mode.\nthis means that:\n\n- software rendering is being used\n- audio output may not work\n- font loading is disabled\n\ncheck any settings which may have made Furnace start up in this mode.\nfont loading is one of these.##sggu"].plurals[0] = "Furnace został uruchomiony w trybie awaryjnym.\noznacza to, że:\n\n- używane jest renderowanie programowe\n- wyjście dźwięku może nie działać\n- wczytywanie czcionek jest wyłączone\n\nnależy sprawdzić, jakie ustawienia mogły spowodować, że program działa w tym trybie.\nczytanie czcionki mogło być jednym z nich.";
    strings["Unsaved changes! Save changes before opening file?##sggu0"].plurals[0] = "Niezapisano zmiany! Zapisać je przed wczytaniem pliku?";
    strings["Error while loading file! (%s)##sggu0"].plurals[0] = "Błąd podczas wczytywania pliku! (%s)";
    strings["Unsaved changes! Save changes before quitting?##sggu"].plurals[0] = "Niezapisane zmiany! Czy chcesz je zapisać przed wyjściem?";
    strings["error while loading fonts! please check your settings.##sggu0"].plurals[0] = "błąd podczas ładowania czcionek! sprawdź swoje ustawienia.";
    strings["File##menubar"].plurals[0] = "Plik##menubar";
    strings["file##menubar"].plurals[0] = "plik##menubar";
    strings["new...##sggu"].plurals[0] = "nowy...";
    strings["Unsaved changes! Save changes before creating a new song?##sggu"].plurals[0] = "Niezapisane zmiany! Zapisać zmiany przed srtworzeniem nowego utworu?";
    strings["open...##sggu"].plurals[0] = "otwórz...";
    strings["Unsaved changes! Save changes before opening another file?##sggu"].plurals[0] = "Niezapisane zmiany! Zapisać zmiany przed otwarciem innego pliku?";
    strings["open recent##sggu"].plurals[0] = "otwórz ostatnie";
    strings["Unsaved changes! Save changes before opening file?##sggu1"].plurals[0] = "Niezapisane zmiany! Zapisać zmiany przed otwarciem pliku?";
    strings["Error while loading file! (%s)##sggu1"].plurals[0] = "Blad podczas wczytywania pliku! (%s)";
    strings["nothing here yet##sggu"].plurals[0] = "na razie nic tu nie ma";
    strings["clear history##sggu"].plurals[0] = "wyczyść historię";
    strings["Are you sure you want to clear the recent file list?##sggu"].plurals[0] = "Czy jestes pewien ze chcesz usunąć listę ostatnio wczytanych plików?";
    strings["save##sggu"].plurals[0] = "zapisz";
    strings["Error while saving file! (%s)##sggu0"].plurals[0] = "Błąd podczas zapisu pliku! (%s)";
    strings["save as...##sggu"].plurals[0] = "zapisz jako...";
    strings["export audio...##sggu0"].plurals[0] = "eksportuj audio...";
    strings["export VGM...##sggu0"].plurals[0] = "eksportuj VGM...";
    strings["export .dmf (1.1.3+)...##sggu0"].plurals[0] = "eksportuj .dmf (1.1.3+)...";
    strings["export .dmf (1.0/legacy)...##sggu0"].plurals[0] = "eksportuj .dmf (1.0/legacy)...";
    strings["export ZSM...##sggu0"].plurals[0] = "eksportuj ZSM...";
    strings["export Amiga validation data...##sggu0"].plurals[0] = "eksportuj plik kontrolny dla Amigi...";
    strings["export text...##sggu0"].plurals[0] = "eksportuj tekst...";
    strings["export command stream...##sggu0"].plurals[0] = "eksportuj strumień komend...";
    strings["export audio...##sggu1"].plurals[0] = "eksportuj audio...";
    strings["export VGM...##sggu1"].plurals[0] = "eksportuj VGM...";
    strings["export .dmf (1.1.3+)...##sggu1"].plurals[0] = "eksportuj .dmf (1.1.3+)...";
    strings["export .dmf (1.0/legacy)...##sggu1"].plurals[0] = "eksportuj .dmf (1.0/legacy)...";
    strings["export ZSM...##sggu1"].plurals[0] = "eksportuj ZSM...";
    strings["export Amiga validation data...##sggu1"].plurals[0] = "eksportuj plik kontrolny dla Amigi...";
    strings["export text...##sggu1"].plurals[0] = "eksportuj tekst...";
    strings["export command stream...##sggu1"].plurals[0] = "eksportuj strumień komend...";
    strings["export...##sggu"].plurals[0] = "eksportuj...";
    strings["manage chips##sggu"].plurals[0] = "menedżer układów";
    strings["add chip...##sggu"].plurals[0] = "dodaj uklad...";
    strings["cannot add chip! (##sggu"].plurals[0] = "nie można dodac układu! (";
    strings["configure chip...##sggu"].plurals[0] = "konfiguruj układ...";
    strings["change chip...##sggu"].plurals[0] = "zmien ukald...";
    strings["Preserve channel positions##sggu0"].plurals[0] = "Zachowaj pozycje kanałow";
    strings["remove chip...##sggu"].plurals[0] = "usuń układ..";
    strings["Preserve channel positions##sggu1"].plurals[0] = "Zachowaj pozycje kanałow";
    strings["cannot remove chip! (##sggu"].plurals[0] = "nie mozna usunąć ukladu! (";
    strings["open built-in assets directory##sggu"].plurals[0] = "otwórz wbudowany folder z zasobami";
    strings["restore backup##sggu"].plurals[0] = "przywróć kopię zapasową";
    strings["exit##sggu"].plurals[0] = "wyjdz";
    strings["Unsaved changes! Save before quitting?##sggu"].plurals[0] = "Niezapisane zmiany! Czy zapisać je przed wyjściem?";
    strings["Edit##menubar"].plurals[0] = "Edytuj##menubar";
    strings["edit##menubar"].plurals[0] = "edytuj##menubar";
    strings["undo##sggu"].plurals[0] = "cofnij";
    strings["redo##sggu"].plurals[0] = "ponów";
    strings["clear...##sggu"].plurals[0] = "wyczyść...";
    strings["Settings##menubar"].plurals[0] = "Ustawienia##menubar";
    strings["settings##menubar"].plurals[0] = "ustawienia##menubar";
    strings["full screen##sggu"].plurals[0] = "tryb pełnoekranowy";
    strings["lock layout##sggu"].plurals[0] = "zablokuj układ okna";
    strings["visualizer##sggu"].plurals[0] = "wizualizator";
    strings["reset layout##sggu"].plurals[0] = "resetuj układ okna";
    strings["Are you sure you want to reset the workspace layout?##sggu"].plurals[0] = "Czy jestes pewien ze chcesz zresetowac uklad okna?";
    strings["switch to mobile view##sggu"].plurals[0] = "przelacz na tryb mobilny";
    strings["settings...##sggu"].plurals[0] = "ustawienia...";
    strings["Window##menubar"].plurals[0] = "Okno##menubar";
    strings["window##menubar"].plurals[0] = "okno##menubar";
    strings["song information##sggu"].plurals[0] = "o utworze";
    strings["subsongs##sggu"].plurals[0] = "podutwory";
    strings["speed##sggu"].plurals[0] = "prędkość";
    strings["assets##sggu"].plurals[0] = "zasoby";
    strings["instruments##sggu"].plurals[0] = "instrumenty";
    strings["wavetables##sggu"].plurals[0] = "fale tablic";
    strings["samples##sggu"].plurals[0] = "sample";
    strings["orders##sggu"].plurals[0] = "matryca wzorców";
    strings["pattern##sggu"].plurals[0] = "wzorzec";
    strings["mixer##sggu"].plurals[0] = "mikser";
    strings["grooves##sggu"].plurals[0] = "wzór rytmu";
    strings["channels##sggu"].plurals[0] = "kanały";
    strings["pattern manager##sggu"].plurals[0] = "menedzer wzorcow";
    strings["chip manager##sggu"].plurals[0] = "menedzer ukladow";
    strings["compatibility flags##sggu"].plurals[0] = "flagi kompatybilnosci";
    strings["song comments##sggu"].plurals[0] = "komentarze do utworu";
    strings["instrument editor##sggu"].plurals[0] = "edytor instrumentow";
    strings["wavetable editor##sggu"].plurals[0] = "edyor tablic fal";
    strings["sample editor##sggu"].plurals[0] = "edytor sampli";
    strings["play/edit controls##sggu"].plurals[0] = "kontrola edycji/odtwarzania";
    strings["piano/input pad##sggu"].plurals[0] = "klawiatura pianina/panel wejściowy";
    strings["oscilloscope (master)##sggu"].plurals[0] = "oscyloskop";
    strings["oscilloscope (per-channel)##sggu"].plurals[0] = "oscyloskop (dla poszczegolnych kanałow)";
    strings["oscilloscope (X-Y)##sggu"].plurals[0] = "oscyloskop (X-Y)";
    strings["volume meter##sggu"].plurals[0] = "poziom głośności";
    strings["clock##sggu"].plurals[0] = "zegar";
    strings["register view##sggu"].plurals[0] = "podgląd rejestrow";
    strings["log viewer##sggu"].plurals[0] = "podglad logow";
    strings["statistics##sggu"].plurals[0] = "statystyki";
    strings["spoiler##sggu"].plurals[0] = "spoiler";
    strings["Help##menubar"].plurals[0] = "Pomoc##menubar";
    strings["help##menubar"].plurals[0] = "pomoc##menubar";
    strings["effect list##sggu"].plurals[0] = "lista efektow";
    strings["debug menu##sggu"].plurals[0] = "menu debugowania";
    strings["inspector##sggu"].plurals[0] = "menu debugowania ImGUI";
    strings["panic##sggu"].plurals[0] = "panika";
    strings["about...##sggu"].plurals[0] = "o programie...";
    strings["| Speed %d:%d##sggu"].plurals[0] = "| Predkosc %d:%d";
    strings["| Speed %d##sggu"].plurals[0] = "| Predkosc %d";
    strings["| Groove##sggu"].plurals[0] = "| Wzor rytmu";
    strings[" @ %gHz (%g BPM) ##sggu"].plurals[0] = " @ %gHz (%g BPM) ";
    strings["| Order %.2X/%.2X ##sggu"].plurals[0] = "| Rząd matrycy wzorców %.2X/%.2X ";
    strings["| Order %d/%d ##sggu"].plurals[0] = "| Rząd matrycy wzorców. %d/%d ";
    strings["| Row %.2X/%.2X ##sggu"].plurals[0] = "| Rząd %.2X/%.2X ";
    strings["| Row %d/%d ##sggu"].plurals[0] = "| Rząd %d/%d ";
    strings["Don't you have anything better to do?##sggu"].plurals[0] = "Serio nie masz nic lepszego do roboty?";
    strings["%d years ##sggu"].plurals[0] = "%d rok ";
    strings["%d years ##sggu"].plurals[1] = "%d roku ";
    strings["%d years ##sggu"].plurals[2] = "%d lat ";
    strings["%d months ##sggu"].plurals[0] = "%d miesiac ";
    strings["%d months ##sggu"].plurals[1] = "%d miesiaca ";
    strings["%d months ##sggu"].plurals[2] = "%d miesiecy ";
    strings["%d days ##sggu"].plurals[0] = "%d dzien ";
    strings["%d days ##sggu"].plurals[1] = "%d dnia ";
    strings["%d days ##sggu"].plurals[2] = "%d dni ";
    strings["Note off (cut)##sggu"].plurals[0] = "Odcięcie nuty (nagłe)";
    strings["Note off (release)##sggu"].plurals[0] = "Odcięcie nuty (z włączoną fazą zanikania obwiedni)";
    strings["Macro release only##sggu"].plurals[0] = "Odcięcie nuty (tylko dla makr)";
    strings["Note on: %s##sggu"].plurals[0] = "Nuta: %s";
    strings["Ins %d: <invalid>##sggu"].plurals[0] = "Instrument %d: <niepoprawny.>";
    strings["Ins %d: %s##sggu"].plurals[0] = "Instrument %d: %s";
    strings["Set volume: %d (%.2X, INVALID!)##sggu"].plurals[0] = "Głośność: %d (%.2X, NIEPOPRAWNA!)";
    strings["Set volume: %d (%.2X, %d%%)##sggu"].plurals[0] = "Głośność: %d (%.2X, %d%%)";
    strings["| modified##sggu"].plurals[0] = "| zmodyfikowany";
    strings["there was an error in the file dialog! you may want to report this issue to:\nhttps://github.com/tildearrow/furnace/issues\ncheck the Log Viewer (window > log viewer) for more information.\n\nfor now please disable the system file picker in Settings > General.##sggu"].plurals[0] = "wystąpił błąd w oknie dialogowym pliku!możesz chcieć zgłosić błąd:\nhttps://github.com/tildearrow/furnace/issues\nAby uzyskać więcej informacji, można otworzyć podgląd logów (okno > podgląd logów).\n\nna razie można wyłączyć systemowe okno dialogowe plików w ustawieniach > podstawowe.";
    strings["can't do anything without Storage permissions!##sggu"].plurals[0] = "nie da się zrobić niczego bez pozwolenia na zapis";
    strings["Zenity/KDialog not available!\nplease install one of these, or disable the system file picker in Settings > General.##sggu"].plurals[0] = "nie znaleziono Zenity/KDialog!\nzainstaluj jedno z nich lub wyłącz systemowe okno dialogowe w ustawieniach > podstawowe.";
    strings["Error while loading file! (%s)##sggu2"].plurals[0] = "Błąd podczas wczytywania pliku!  (%s)";
    strings["Error while saving file! (%s)##sggu1"].plurals[0] = "Błąd podczas zapisywania pliku!  (%s)";
    strings["Error while loading file! (%s)##sggu3"].plurals[0] = "Błąd podczas wczytywania pliku!  (%s)";
    strings["Error while saving file! (%s)##sggu2"].plurals[0] = "Błąd podczas zapisywania pliku! (%s)";
    strings["Error while saving file! (%s)##sggu3"].plurals[0] = "Błąd podczas zapisywania pliku! (%s)";
    strings["error while saving instrument! only the following instrument types are supported:\n- FM (OPN)\n- SN76489/Sega PSG\n- Game Boy\n- PC Engine\n- NES\n- C64\n- FM (OPLL)\n- FDS##sggu"].plurals[0] = "błąd podczas zapisywania! tylko następujące typy instruymentów są wspierane:\n- FM (OPN)\n- SN76489/Sega PSG\n- Game Boy\n- PC Engine\n- NES\n- C64\n- FM (OPLL)\n- FDS";
    strings["there were some errors while loading samples:\n#sggu"].plurals[0] = "podczas ładowania sampli wystąpiły następujące błędy:\n";
    strings["...but you haven't selected a sample!##sggu0"].plurals[0] = "...ale nie wybrano sampla!";
    strings["could not save sample! open Log Viewer for more information.##sggu0"].plurals[0] = "nie udało się zapisać sampla! otwoórz podgląd logów aby uzyskać więcej informacji.";
    strings["could not save sample! open Log Viewer for more information.##sggu1"].plurals[0] = "nie udało się zapisać sampla! otwoórz podgląd logów aby uzyskać więcej informacji.";
    strings["there were some warnings/errors while loading instruments:\n#sggu"].plurals[0] = "podczas wczytywania instrumentów wystąpiły następujące błędy i ostrzeżenia:\n";
    strings["> %s: cannot load instrument! (%s)\n#sggu"].plurals[0] = "> %s: nie można wczytać instrumentu! (%s)\n";
    strings["...but you haven't selected an instrument!##sggu0"].plurals[0] = "...ale nie wybrano instrumentu!";
    strings["cannot load instrument! (##sggu"].plurals[0] = "nie można wczytać instrumentu!";
    strings["congratulations! you managed to load nothing.\nyou are entitled to a bug report.##sggu"].plurals[0] = "Gratulacje! Nie udało ci się nic wczytać.\nmożesz spokojnie zgłosić błąd w programie.";
    strings["there were some errors while loading wavetables:\n##sggu"].plurals[0] = "wystapily problemy podczas wczytywania tablic fal:\n";
    strings["cannot load wavetable! (##sggu"].plurals[0] = "nie mozna wczytać tablicy fal! (";
    strings["...but you haven't selected a wavetable!##sggu"].plurals[0] = "...ale nie wybrano tablicy!";
    strings["could not open file!##sggu"].plurals[0] = "nie udalo sie otworzyć pliku!";
    strings["Could not write ZSM! (%s)##sggu"].plurals[0] = "nie udalo sie zapisać pliku ZSM! (%s)";
    strings["could not write text! (%s)##sggu"].plurals[0] = "nie udalo sie zapisać pliku tekstowego! (%s)";
    strings["could not write command stream! (%s)##sggu"].plurals[0] = "nie udalo sie zapisać strumienia komend! (%s)";
    strings["Error while loading file! (%s)##sggu4"].plurals[0] = "Blad podczas wczytywania pliku! (%s)";
    strings["You opened: %s##sggu"].plurals[0] = "Otwarto: %s";
    strings["You opened:##sggu"].plurals[0] = "Otwarto:";
    strings["You saved: %s##sggu"].plurals[0] = "Zapisano: %s";
    strings["Rendering...###Rendering..."].plurals[0] = "Renderowanie...###Rendering...";
    strings["Please wait...##sggu"].plurals[0] = "Proszę czekać...";
    strings["Abort##sggu"].plurals[0] = "Przerwij";
    strings["New Song###New Song"].plurals[0] = "Nowy Utwór###New Song";
    strings["Export###Export"].plurals[0] = "eksportuj###Export";
    strings["Error###Error"].plurals[0] = "Błąd###Error";
    strings["OK##sggu0"].plurals[0] = "OK";
    strings["Warning###Warning"].plurals[0] = "Uwaga###Warning";
    strings["Yes##sggu0"].plurals[0] = "Tak";
    strings["No##sggu0"].plurals[0] = "Nie";
    strings["Yes##sggu1"].plurals[0] = "Tak";
    strings["No##sggu1"].plurals[0] = "Nie";
    strings["Yes##sggu2"].plurals[0] = "Tak";
    strings["No##sggu2"].plurals[0] = "Nie";
    strings["Yes##sggu3"].plurals[0] = "Tak";
    strings["No##sggu3"].plurals[0] = "Nie";
    strings["Cancel##sggu0"].plurals[0] = "Anuluj";
    strings["Erasing##sggu"].plurals[0] = "Usuwanie:";
    strings["All subsongs##sggu"].plurals[0] = "Wszystkie podutwory";
    strings["Current subsong##sggu"].plurals[0] = "Obecny podutwór";
    strings["Orders##sggu"].plurals[0] = "Matryca wzorców";
    strings["Pattern##sggu"].plurals[0] = "Wzorzec";
    strings["Instruments##sggu"].plurals[0] = "Instrumenty";
    strings["Wavetables##sggu"].plurals[0] = "Tablice fal";
    strings["Samples##sggu"].plurals[0] = "Sample";
    strings["Optimization##sggu"].plurals[0] = "Optymalizuj:";
    strings["De-duplicate patterns##sggu"].plurals[0] = "Usuń powtarzające się wzorce";
    strings["Remove unused instruments##sggu"].plurals[0] = "Usuń nieużywane instrumenty";
    strings["Remove unused samples##sggu"].plurals[0] = "Usun nieużywane sample";
    strings["Never mind! Cancel##sggu1"].plurals[0] = "Nie wazne! Anuluj";
    strings["Yes##sggu4"].plurals[0] = "Tak";
    strings["No##sggu4"].plurals[0] = "Nie";
    strings["Yes##sggu5"].plurals[0] = "Tak";
    strings["No##sggu5"].plurals[0] = "Nie";
    strings["Yes##sggu6"].plurals[0] = "Tak";
    strings["No##sggu6"].plurals[0] = "Nie";
    strings["Yes##sggu7"].plurals[0] = "Tak";
    strings["Yes##sggu8"].plurals[0] = "Tak";
    strings["Yes##sggu9"].plurals[0] = "Tak";
    strings["Yes##sggu10"].plurals[0] = "Tak";
    strings["Yes##sggu11"].plurals[0] = "Tak";
    strings["No##sggu8"].plurals[0] = "Nie";
    strings["No##sggu9"].plurals[0] = "Nie";
    strings["No##sggu10"].plurals[0] = "Nie";
    strings["No##sggu11"].plurals[0] = "Nie";
    strings["No##sggu12"].plurals[0] = "Nie";
    strings["Cancel##sggu4"].plurals[0] = "Anuluj";
    strings["Cancel##sggu5"].plurals[0] = "Anuluj";
    strings["Cancel##sggu6"].plurals[0] = "Anuluj";
    strings["Cancel##sggu7"].plurals[0] = "Anuluj";
    strings["Cancel##sggu8"].plurals[0] = "Anuluj";
    strings["OK##sggu1"].plurals[0] = "OK";
    strings["Drum kit mode:##sggu"].plurals[0] = "Tryb zestawu perkusji:";
    strings["Normal##sggu"].plurals[0] = "Normalny";
    strings["12 samples per octave##sggu"].plurals[0] = "12 sampli na oktawę";
    strings["Starting octave##sggu"].plurals[0] = "Oktawa poczatkowa";
    strings["too many instruments!##sggu"].plurals[0] = "zbyt wiele instrumentow!";
    strings["too many wavetables!##sggu"].plurals[0] = "zbyt wiele tablic fal!";
    strings["Select Instrument###Select Instrument"].plurals[0] = "Wybierz instrument###Select Instrument";
    strings["this is an instrument bank! select which one to use:##sggu"].plurals[0] = "to jest bank brzmień! wybierz instrument który checsz uzyć:";
    strings["this is an instrument bank! select which ones to load:##sggu"].plurals[0] = "to jest bank brzmień! wybierz instrument który checsz wczytać";
    strings["All##sggu"].plurals[0] = "Wszystkie";
    strings["None##sggu"].plurals[0] = "Zadne";
    strings["OK##sggu2"].plurals[0] = "Ok";
    strings["Cancel##sggu2"].plurals[0] = "Anuluj";
    strings["...but you haven't selected an instrument!##sggu1"].plurals[0] = "...ale nie wybrano instrumentu!";
    strings["Import Raw Sample###Import Raw Sample"].plurals[0] = "Importuj surowy sampel###Import Raw Sample";
    strings["Data type:##sggu"].plurals[0] = "Typ danych:";
    strings["Sample rate##sggu"].plurals[0] = "Częstotliwość samplowania";
    strings["Channels##sggu"].plurals[0] = "Ilość kanałów";
    strings["(will be mixed down to mono)##sggu"].plurals[0] = "(zostanie zmiksowany do mono)";
    strings["Unsigned##sggu"].plurals[0] = "Bez znaku";
    strings["Big endian##sggu"].plurals[0] = "Big endian";
    strings["Swap nibbles##sggu"].plurals[0] = "zamień miejscami półbajty";
    strings["Swap words##sggu"].plurals[0] = "zamień miejscami slowa maszynowe";
    strings["Encoding:##sggu"].plurals[0] = "Kodowanie:";
    strings["Reverse bit order##sggu"].plurals[0] = "Odwrotna kolejność bitów";
    strings["OK##sggu3"].plurals[0] = "OK";
    strings["...but you haven't selected a sample!##sggu1"].plurals[0] = "...ale nie wybrano sampla!";
    strings["Cancel##sggu3"].plurals[0] = "Anuluj";
    strings["Error! No string provided!##sggu"].plurals[0] = "Błąd! Nie podano ciągu znaków!";
    strings["OK##sggu4"].plurals[0] = "Ok";
    strings["error while loading fonts! please check your settings.##sggu1"].plurals[0] = "błąd podczas wczytywania czcionek! Sprawdź swoje ustawienia.";
    strings["it appears I couldn't load these fonts. any setting you can check?##sggu"].plurals[0] = "wygląda na to że nie mogę wczytać tych czcionek. czy możesz sprawdzić ustawienia?";
    strings["could not init renderer! %s##sggu"].plurals[0] = "N=nie udało się zainicjować silnika renderującego! %s";
    strings["\r\nthe render driver has been set to a safe value. please restart Furnace.##sggu"].plurals[0] = "\r\nsilnik renderujący został zresetowany do bezpiecznego stanu. uruchom ponownie Furnace.";
    strings["could not open window! %s##sggu"].plurals[0] = "nie udało się otworzyć okna! %s";
    strings["error while loading fonts! please check your settings.##sggu2"].plurals[0] = "błąd podczas wczytywania czcionek! proszę sprawdzić swoje ustawienia.";
    strings["could NOT save layout! %s##sggu"].plurals[0] = "nie udało się zapisać układu okna! %s";

    //   sggc  src/gui/guiConst.cpp

    strings["Generic Sample##sggc"].plurals[0] = "Zwykły sampel";
    strings["Beeper##sggc"].plurals[0] = "Brzęczyk";
    strings["VRC6 (saw)##sggc"].plurals[0] = "VRC6 (fala piłokształtna)";
    strings["OPL (drums)##sggc"].plurals[0] = "OPL (perkusja)";
    strings["PowerNoise (noise)##sggc"].plurals[0] = "PowerNoise (szum)";
    strings["PowerNoise (slope)##sggc"].plurals[0] = "PowerNoise (spadek)";
    strings["Forward##sggc"].plurals[0] = "Do przodu";
    strings["Backward##sggc"].plurals[0] = "Do tyłu";
    strings["Ping pong##sggc"].plurals[0] = "W obie strony";
    strings["1-bit PCM##sggc"].plurals[0] = "1-bitowy PCM";
    strings["1-bit DPCM##sggc"].plurals[0] = "1-bitowy DPCM";
    strings["8-bit PCM##sggc"].plurals[0] = "8-bitowy PCM";
    strings["8-bit µ-law PCM##sggc"].plurals[0] = "8-bitowy PCM (µ-prawo)";
    strings["16-bit PCM##sggc"].plurals[0] = "16-bitowy PCM";
    strings["none##sggc"].plurals[0] = "brak";
    strings["linear##sggc"].plurals[0] = "liniowy";
    strings["cubic spline##sggc"].plurals[0] = "sześcienny spline";
    strings["blep synthesis##sggc"].plurals[0] = "synteza BLEP";
    strings["sinc##sggc"].plurals[0] = "sinc";
    strings["best possible##sggc"].plurals[0] = "najlepszy";
    strings["Pitch##sggc"].plurals[0] = "Wysokość";
    strings["Song##sggc"].plurals[0] = "Utwor";
    strings["Time##sggc"].plurals[0] = "Czas";
    strings["Speed##sggc0"].plurals[0] = "Prędkość";
    strings["Panning##sggc"].plurals[0] = "Panning";
    strings["Volume##sggc"].plurals[0] = "Głośność";
    strings["System Primary##sggc"].plurals[0] = "Główne efekty układu";
    strings["System Secondary##sggc"].plurals[0] = "Poboczne efekty układu";
    strings["Miscellaneous##sggc"].plurals[0] = "Inne";
    strings["Invalid##sggc"].plurals[0] = "Nieaktywne";

    strings["---Global##sggc"].plurals[0] = "---Globalny";
    strings["New##sggc"].plurals[0] = "Nowy";
    strings["Open file##sggc"].plurals[0] = "Otwórz plik";
    strings["Restore backup##sggc"].plurals[0] = "Przywróc kopię zapasową";
    strings["Save file##sggc"].plurals[0] = "Zapisz plik";
    strings["Save as##sggc"].plurals[0] = "Zapisz jako";
    strings["Export##sggc"].plurals[0] = "Eksportuj";
    strings["Undo##sggc"].plurals[0] = "Cofnij";
    strings["Redo##sggc"].plurals[0] = "Ponow";
    strings["Exit##sggc"].plurals[0] = "Wyjdz";
    strings["Play/Stop (toggle)##sggc"].plurals[0] = "Start/stop (przelacznik))";
    strings["Play##sggc"].plurals[0] = "Odtwarzaj";
    strings["Stop##sggc"].plurals[0] = "Stop";
    strings["Play (from beginning)##sggc"].plurals[0] = "Odtwarzaj (od początku)";
    strings["Play (repeat pattern)##sggc"].plurals[0] = "Odtwarzaj (zapętl bieżącegy wzorzec)";
    strings["Play from cursor##sggc"].plurals[0] = "Odtwarzaj od kursora";
    strings["Step row##sggc"].plurals[0] = "Сделать один шаг по паттерну";
    strings["Octave up##sggc"].plurals[0] = "Oktawa do góry";
    strings["Octave down##sggc"].plurals[0] = "Oktawa w dół";
    strings["Previous instrument##sggc"].plurals[0] = "Poprzedni instrument";
    strings["Next instrument##sggc"].plurals[0] = "Następny instrument";
    strings["Increase edit step##sggc"].plurals[0] = "Увеличить шаг редактирования";
    strings["Decrease edit step##sggc"].plurals[0] = "Уменьшить шаг редактирования";
    strings["Toggle edit mode##sggc"].plurals[0] = "Переключить режим редактирования";
    strings["Metronome##sggc"].plurals[0] = "Metronom";
    strings["Toggle repeat pattern##sggc"].plurals[0] = "Переключить режим зацикливания паттерна";
    strings["Follow orders##sggc"].plurals[0] = "След. за воспр. в матр. патт.";
    strings["Follow pattern##sggc"].plurals[0] = "След. за воспр. в патт.";
    strings["Toggle full-screen##sggc"].plurals[0] = "Перключить полноэкранный режим";
    strings["Request voice from TX81Z##sggc"].plurals[0] = "Запросить канал у TX81Z";
    strings["Panic##sggc"].plurals[0] = "Паника";
    strings["Clear song data##sggc"].plurals[0] = "Wyczyść dane utworu";

    strings["Edit Controls##sggc"].plurals[0] = "Edycja";
    strings["Orders##sggc"].plurals[0] = "Matryca wzorców";
    strings["Instrument List##sggc"].plurals[0] = "Lista instrumentów";
    strings["Instrument Editor##sggc"].plurals[0] = "Edytor instrumentów";
    strings["Song Information##sggc"].plurals[0] = "Informacje o utworze";
    strings["Speed##sggc"].plurals[0] = "Prędkość";
    strings["Pattern##sggc"].plurals[0] = "Wzorce";
    strings["Wavetable List##sggc"].plurals[0] = "Lista tablic fal";
    strings["Wavetable Editor##sggc"].plurals[0] = "Edytor tablic fal";
    strings["Sample List##sggc"].plurals[0] = "Lista sampli";
    strings["Sample Editor##sggc"].plurals[0] = "Edytor sampli";
    strings["About##sggc"].plurals[0] = "O programie";
    strings["Settings##sggc"].plurals[0] = "Ustawienia";
    strings["Mixer##sggc"].plurals[0] = "Mikser";
    strings["Debug Menu##sggc"].plurals[0] = "Menu debugowania";
    strings["Oscilloscope (master)##sggc"].plurals[0] = "Oscyloskop";
    strings["Volume Meter##sggc"].plurals[0] = "Miernik poziomu głośności";
    strings["Statistics##sggc"].plurals[0] = "Statystyki";
    strings["Compatibility Flags##sggc"].plurals[0] = "Flagi kompatybilności";
    strings["Piano##sggc"].plurals[0] = "Klawiatura fortepianu";
    strings["Song Comments##sggc"].plurals[0] = "Komentarze do utworu";
    strings["Channels##sggc"].plurals[0] = "Kanały";
    strings["Pattern Manager##sggc"].plurals[0] = "Menedżer wzorców";
    strings["Chip Manager##sggc"].plurals[0] = "Menedżer układów";
    strings["Register View##sggc"].plurals[0] = "Podgląd rejestrów";
    strings["Log Viewer##sggc"].plurals[0] = "Podgląd logów";
    strings["Effect List##sggc"].plurals[0] = "Lista efektów";
    strings["Oscilloscope (per-channel)##sggc"].plurals[0] = "Oscyloskop (dla poszczególnych kanałów)";
    strings["Subsongs##sggc"].plurals[0] = "Podutwory";
    strings["Find/Replace##sggc"].plurals[0] = "Znajdź/zamień";
    strings["Clock##sggc"].plurals[0] = "Zegar";
    strings["Grooves##sggc"].plurals[0] = "Wzory rytmów";
    strings["Oscilloscope (X-Y)##sggc"].plurals[0] = "Oscyloskop (X-Y)";

    strings["Collapse/expand current window##sggc"].plurals[0] = "Maksymalizuj/minimalizuj obecne okno";
    strings["Close current window##sggc"].plurals[0] = "Zamknij obecne okno";

    strings["---Pattern##sggc"].plurals[0] = "---Pattern";
    strings["Transpose (+1)##sggc"].plurals[0] = "Transponuj (+1)";
    strings["Transpose (-1)##sggc"].plurals[0] = "Transponuj (-1)";
    strings["Transpose (+1 octave)##sggc"].plurals[0] = "Transponuj (+1 oktawa)";
    strings["Transpose (-1 octave)##sggc"].plurals[0] = "Transponuj (-1 oktawa)";
    strings["Increase values (+1)##sggc"].plurals[0] = "Zwieksz wartosci (+1)";
    strings["Increase values (-1)##sggc"].plurals[0] = "Zmniejsz wartosci (-1)";
    strings["Increase values (+16)##sggc"].plurals[0] = "Zwieksz wartosci (+16)";
    strings["Increase values (-16)##sggc"].plurals[0] = "Zmniejsz wartosci (-16)";
    strings["Select all##sggc0"].plurals[0] = "Wybierz wszystko";
    strings["Cut##sggc0"].plurals[0] = "Wytnij";
    strings["Copy##sggc0"].plurals[0] = "Kopiuj";
    strings["Paste##sggc0"].plurals[0] = "Wklej";
    strings["Paste Mix (foreground)##sggc"].plurals[0] = "Вставить поверх";
    strings["Paste Mix (background)##sggc"].plurals[0] = "Вставить поверх (с заменой существующего)";
    strings["Paste Flood##sggc"].plurals[0] = "Вставить с цикл. повт. буфера (до конца патт.)";
    strings["Paste Overflow##sggc"].plurals[0] = "Вставить (с возможным переходом в след. паттерн)";
    strings["Move cursor up##sggc"].plurals[0] = "Kursor w gore";
    strings["Move cursor down##sggc"].plurals[0] = "Kursor w dol";
    strings["Move cursor left##sggc"].plurals[0] = "Kursor w lewo";
    strings["Move cursor right##sggc"].plurals[0] = "Kursor w prawo";
    strings["Move cursor up by one (override Edit Step)##sggc"].plurals[0] = "Курсор вверх на один шаг (игнорировать шаг редактирования)";
    strings["Move cursor down by one (override Edit Step)##sggc"].plurals[0] = "Курсор вниз на один шаг (игнорировать шаг редактирования)";
    strings["Move cursor to previous channel##sggc"].plurals[0] = "Сдвинуть курсор на предыдущий канал";
    strings["Move cursor to next channel##sggc"].plurals[0] = "Сдвинуть курсор на следующий канал";
    strings["Move cursor to next channel (overflow)##sggc"].plurals[0] = "Сдвинуть курсор на предыдущий канал (с переполнением)";
    strings["Move cursor to previous channel (overflow)##sggc"].plurals[0] = "Сдвинуть курсор на следующий канал (с переполнением)";
    strings["Move cursor to beginning of pattern##sggc"].plurals[0] = "Сдвинуть курсор в начало паттерна";
    strings["Move cursor to end of pattern##sggc"].plurals[0] = "Сдвинуть курсор в конец паттерна";
    strings["Move cursor up (coarse)##sggc"].plurals[0] = "Курсор вверх (грубо)";
    strings["Move cursor down (coarse)##sggc"].plurals[0] = "Курсор вниз (грубо)";
    strings["Expand selection upwards##sggc"].plurals[0] = "Расширить выделенную область вверх";
    strings["Expand selection downwards##sggc"].plurals[0] = "Расширить выделенную область вниз";
    strings["Expand selection to the left##sggc"].plurals[0] = "Расширить выделенную область влево";
    strings["Expand selection to the right##sggc"].plurals[0] = "Расширить выделенную область вправо";
    strings["Expand selection upwards by one (override Edit Step)##sggc"].plurals[0] = "Расширить выделенную область вверх (игнорировать шаг редактирования)";
    strings["Expand selection downwards by one (override Edit Step)##sggc"].plurals[0] = "Расширить выделенную область вниз (игнорировать шаг редактирования)";
    strings["Expand selection to beginning of pattern##sggc"].plurals[0] = "Расширить выделенную область до начала паттерна";
    strings["Expand selection to end of pattern##sggc"].plurals[0] = "Расширить выделенную область до конца паттерна";
    strings["Expand selection upwards (coarse)##sggc"].plurals[0] = "Расширить выделенную область вверх (грубо)";
    strings["Expand selection downwards (coarse)##sggc"].plurals[0] = "Расширить выделенную область вниз (грубо)";
    strings["Delete##sggc"].plurals[0] = "usuń";
    strings["Pull delete##sggc"].plurals[0] = "Удалить с подтягиванием следующих строк";
    strings["Insert##sggc"].plurals[0] = "Вставить с сдвигом строк вниз";
    strings["Mute channel at cursor##sggc"].plurals[0] = "Заглушить выделенный канал";
    strings["Solo channel at cursor##sggc"].plurals[0] = "Соло выделенного канала";
    strings["Unmute all channels##sggc"].plurals[0] = "Включить все каналы";
    strings["Go to next order##sggc"].plurals[0] = "Перейти на следующую строку матрицы паттернов";
    strings["Go to previous order##sggc"].plurals[0] = "Перейти на предыдущую строку матрицы паттернов";
    strings["Collapse channel at cursor##sggc"].plurals[0] = "Сжать текущий канал";
    strings["Increase effect columns##sggc"].plurals[0] = "Dodaj столбец эффектов";
    strings["Decrease effect columns##sggc"].plurals[0] = "Убрать столбец эффектов";
    strings["Interpolate##sggc"].plurals[0] = "Интерполировать";
    strings["Fade##sggc"].plurals[0] = "Затухание/градиент";
    strings["Invert values##sggc"].plurals[0] = "Инвертировать параметры";
    strings["Flip selection##sggc"].plurals[0] = "Перевернуть выделенную область";
    strings["Collapse rows##sggc"].plurals[0] = "Сжать строки";
    strings["Expand rows##sggc"].plurals[0] = "Расширить строки";
    strings["Collapse pattern##sggc"].plurals[0] = "Сжать паттерн";
    strings["Expand pattern##sggc"].plurals[0] = "Расширить паттерн";
    strings["Collapse song##sggc"].plurals[0] = "Сжать трек";
    strings["Expand song##sggc"].plurals[0] = "Расширить трек";
    strings["Set note input latch##sggc"].plurals[0] = "Задать буфер ввода для нот";
    strings["Change mobile scroll mode##sggc"].plurals[0] = "Переключить режим мобильной прокрутки";
    strings["Clear note input latch##sggc"].plurals[0] = "Очистить буфер ввода для нот";

    strings["---Instrument list##sggc"].plurals[0] = "---Instrument list";
    strings["Add##sggc0"].plurals[0] = "Dodaj";
    strings["Duplicate##sggc0"].plurals[0] = "Sklonuj";
    strings["Open##sggc0"].plurals[0] = "Otwórz";
    strings["Open (replace current)##sggc0"].plurals[0] = "Otwórz (z zamiana obecnego)";
    strings["Save##sggc0"].plurals[0] = "Zapisz";
    strings["Export (.dmp)##sggc"].plurals[0] = "Eksportuj (.dmp)";
    strings["Move up##sggc0"].plurals[0] = "Przesun w gore";
    strings["Move down##sggc0"].plurals[0] = "Przesun w dol";
    strings["Delete##sggc0"].plurals[0] = "Usuń";
    strings["Edit##sggc0"].plurals[0] = "Educja";
    strings["Cursor up##sggc0"].plurals[0] = "Kursor w górę";
    strings["Cursor down##sggc0"].plurals[0] = "Kursor w dół";
    strings["Toggle folders/standard view##sggc0"].plurals[0] = "Przełączaj między widokiem złożonym i normalnym";

    strings["---Wavetable list##sggc"].plurals[0] = "---Wavetable list";
    strings["Add##sggc1"].plurals[0] = "Dodaj";
    strings["Duplicate##sggc1"].plurals[0] = "Sklonuj";
    strings["Open##sggc1"].plurals[0] = "Otwórz";
    strings["Open (replace current)##sggc1"].plurals[0] = "Otwórz (z zamianą obecnego)";
    strings["Save##sggc1"].plurals[0] = "Zapisz";
    strings["Save (.dmw)##sggc"].plurals[0] = "Zapisz (.dmw)";
    strings["Save (raw)##sggc0"].plurals[0] = "Zapisz (dane surowe)";
    strings["Move up##sggc1"].plurals[0] = "Przesun w gore";
    strings["Move down##sggc1"].plurals[0] = "Przesun w dol";
    strings["Delete##sggc1"].plurals[0] = "usuń";
    strings["Edit##sggc1"].plurals[0] = "Edytuj";
    strings["Cursor up##sggc1"].plurals[0] = "Kursor do góry";
    strings["Cursor down##sggc1"].plurals[0] = "Kursur w dół";
    strings["Toggle folders/standard view##sggc1"].plurals[0] = "Przełączaj między widokiem złożonym i normalnym";

    strings["---Sample list##sggc"].plurals[0] = "---Sample list";
    strings["Add##sggc2"].plurals[0] = "Dodaj";
    strings["Duplicate##sggc2"].plurals[0] = "Sklonuj";
    strings["Open##sggc2"].plurals[0] = "Otwórz";
    strings["Open (replace current)##sggc2"].plurals[0] = "Otwórz (z zamianą obecnego)";
    strings["Import raw data##sggc"].plurals[0] = "Importuj dane surowe ";
    strings["Import raw data (replace current)##sggc"].plurals[0] = "Importuj dane surowe (z zamianą obecnych)";
    strings["Save##sggc2"].plurals[0] = "Zapisz";
    strings["Save (raw)##sggc1"].plurals[0] = "Zapisz (dane surowe)";
    strings["Move up##sggc2"].plurals[0] = "Przesuń w góę";
    strings["Move down##sggc2"].plurals[0] = "Przesuń w dół";
    strings["Delete##sggc2"].plurals[0] = "Usuń";
    strings["Edit##sggc2"].plurals[0] = "Edytuj";
    strings["Cursor up##sggc2"].plurals[0] = "Kursor w górę";
    strings["Cursor down##sggc2"].plurals[0] = "Kursor w dół";
    strings["Preview##sggc"].plurals[0] = "Podglad";
    strings["Stop preview##sggc"].plurals[0] = "Zatrzymaj podgląd";
    strings["Toggle folders/standard view##sggc2"].plurals[0] = "Przełączaj między widokiem złożonym i normalnym";

    strings["---Sample editor##sggc"].plurals[0] = "---Sample editor";
    strings["Edit mode: Select##sggc"].plurals[0] = "Режим редактирования: выделение";
    strings["Edit mode: Draw##sggc"].plurals[0] = "Режим редактирования: рисование";
    strings["Cut##sggc1"].plurals[0] = "Wytnij";
    strings["Copy##sggc1"].plurals[0] = "Kopiuj";
    strings["Paste##sggc1"].plurals[0] = "Wklej";
    strings["Paste replace##sggc"].plurals[0] = "Вставить с заменой";
    strings["Paste mix##sggc"].plurals[0] = "Вставить со смешением";
    strings["Select all##sggc1"].plurals[0] = "Wybierz wszystko";
    strings["Resize##sggc"].plurals[0] = "Zmień roznmiar";
    strings["Resample##sggc"].plurals[0] = "Изменить частоту дискретизации";
    strings["Amplify##sggc"].plurals[0] = "Wzmocnij";
    strings["Normalize##sggc"].plurals[0] = "Normalizuj";
    strings["Fade in##sggc"].plurals[0] = "Плавное нарастание";
    strings["Fade out##sggc"].plurals[0] = "Плавное затухание";
    strings["Apply silence##sggc"].plurals[0] = "Применить тишину";
    strings["Insert silence##sggc"].plurals[0] = "Вставить тишину";
    strings["Delete##sggc3"].plurals[0] = "Usuń";
    strings["Trim##sggc"].plurals[0] = "Obetnij";
    strings["Reverse##sggc"].plurals[0] = "Реверс";
    strings["Invert##sggc"].plurals[0] = "Инверсия";
    strings["Signed/unsigned exchange##sggc"].plurals[0] = "Знаковый <-> беззнаковый";
    strings["Apply filter##sggc"].plurals[0] = "Применить фильтр";
    strings["Crossfade loop points##sggc"].plurals[0] = "Сделать плавный переход между началом и концом зацикленной части";
    strings["Preview sample##sggc"].plurals[0] = "Podgląd";
    strings["Stop sample preview##sggc"].plurals[0] = "Zatrzymaj podgląd";
    strings["Zoom in##sggc"].plurals[0] = "Przybliż";
    strings["Zoom out##sggc"].plurals[0] = "Oddal";
    strings["Toggle auto-zoom##sggc"].plurals[0] = "Włącz auto-przybliżenie";
    strings["Create instrument from sample##sggc"].plurals[0] = "Utwórz instrument z sampla";
    strings["Set loop to selection##sggc"].plurals[0] = "Ustaw zapętlenie na bazie zaznaczenia";
    strings["Create wavetable from selection##sggc"].plurals[0] = "Stwórz tablice fal na bazie zaznaczenia";

    strings["---Orders##sggc"].plurals[0] = "---Orders";
    strings["Previous order##sggc"].plurals[0] = "Poprzedni rząd matrycy wzorców";
    strings["Next order##sggc"].plurals[0] = "Następny rząd matrycy wzorców";
    strings["Cursor left##sggc"].plurals[0] = "Kursor w lewo";
    strings["Cursor right##sggc"].plurals[0] = "Kursor w prawo";
    strings["Increase value##sggc"].plurals[0] = "Zwieksz wartosc";
    strings["Decrease value##sggc"].plurals[0] = "Zmniejsz wartosc";
    strings["Switch edit mode##sggc"].plurals[0] = "Wlacz tryb edytowania";
    strings["Toggle alter entire row##sggc"].plurals[0] = "Wlacz tryb zmiany całego rzędu";
    strings["Add##sggc3"].plurals[0] = "Dodaj";
    strings["Duplicate##sggc3"].plurals[0] = "Sklonuj";
    strings["Deep clone##sggc"].plurals[0] = "Sklonuj gleboko";
    strings["Duplicate to end of song##sggc"].plurals[0] = "Sklonuj i wstaw na koniec utworu";
    strings["Deep clone to end of song##sggc"].plurals[0] = "Głęboko sklouj i wstaw na koniec utworu";
    strings["Remove##sggc"].plurals[0] = "Usuń";
    strings["Move up##sggc3"].plurals[0] = "Przesuń w górę";
    strings["Move down##sggc3"].plurals[0] = "Przesuń w dół";
    strings["Replay##sggc"].plurals[0] = "Powtórz";

    strings["All chips##sggc"].plurals[0] = "Wszystkie uklady";
    strings["Square##sggc"].plurals[0] = "PSG";
    strings["Wavetable##sggc"].plurals[0] = "Syntezatory tablicowe.";
    strings["Special##sggc"].plurals[0] = "Specjalne";
    strings["Sample##sggc"].plurals[0] = "Samplery";
    strings["Modern/fantasy##sggc"].plurals[0] = "Nowoczesne/nieistniejace";

    //   sgda  src/gui/doAction.cpp

    strings["Unsaved changes! Save changes before creating a new song?##sgda"].plurals[0] = "Niezapisane zmiany! Zapisać przed utworzeniem nowego utworu?";
    strings["Unsaved changes! Save changes before opening another file?##sgda"].plurals[0] = "Niezapisane zmiany! Zapisać je przed otwarciem kolejnego pliku?";
    strings["Unsaved changes! Save changes before opening backup?##sgda"].plurals[0] = "Niezapisane zmiany! Zapisać je przed otwarciem kopii zapasowej?";
    strings["Error while saving file! (%s)##sgda"].plurals[0] = "Błąd podczas zapisu plików! (%s)";
    strings["Error while sending request (MIDI output not configured?)##sgda"].plurals[0] = "Błąd podczas wysyłania żądania (wyjście MIDI nie jest ustawione?)";
    strings["Select an option: (cannot be undone!)##sgda"].plurals[0] = "Wybierz opcję: (akcji nie można cofnąć!)";
    strings["too many instruments!##sgda0"].plurals[0] = "zbyt wiele instrumentów!";
    strings["too many instruments!##sgda1"].plurals[0] = "zbyt wiele instrumentów!";
    strings["too many wavetables!##sgda0"].plurals[0] = "zbyt wiele tablic fal!";
    strings["too many wavetables!##sgda1"].plurals[0] = "zbyt wiele tablic fal!";
    strings["too many samples!##sgda0"].plurals[0] = "zbyt wiele sampli!";
    strings["too many samples!##sgda1"].plurals[0] = "zbyt wiele sampli!";
    strings["couldn't paste! make sure your sample is 8 or 16-bit.##sgda"].plurals[0] = "nie udało się wkleić! upewnij się że twój sampel jest 8 lub 16-bitowy.";
    strings["too many instruments!##sgda2"].plurals[0] = "zbyt wiele instrumentów!";
    strings["select at least one sample!##sgda"].plurals[0] = "wybierz co najmniej jeden sampel!";
    strings["maximum size is 256 samples!##sgda"].plurals[0] = "maksymalny rozmiar to 256 sampli!";
    strings["too many wavetables!##sgda2"].plurals[0] = "zbyt wiele tablic fal!";

    //   sgec  src/gui/editControls.cpp

    strings["Mobile Edit###MobileEdit"].plurals[0] = "Mobilne menu edytowania###MobileEdit";
    strings["Mobile Controls###Mobile Controls"].plurals[0] = "Mobile menu ustawien###Mobile Controls";
    strings["Mobile Menu###Mobile Menu"].plurals[0] = "Mobilne menu###Mobile Menu";
    strings["Pattern##sgec0"].plurals[0] = "Wzorzec";
    strings["Orders##sgec0"].plurals[0] = "Matryca wzorcow";
    strings["Ins##sgec"].plurals[0] = "Instr..";
    strings["Wave##sgec"].plurals[0] = "Tab. fal";
    strings["Sample##sgec"].plurals[0] = "Sample";
    strings["Song##sgec"].plurals[0] = "Utwor";
    strings["Channels##sgec"].plurals[0] = "Kanaly";
    strings["Chips##sgec"].plurals[0] = "Ukladu";
    strings["Mixer##sgec"].plurals[0] = "Mikser";
    strings["Other##sgec"].plurals[0] = "Inne";
    strings["New##sgec"].plurals[0] = "Nowy";
    strings["Unsaved changes! Save changes before creating a new song?##sgec"].plurals[0] = "Niezapisane zmiany! Zapisać zmiany przed stworzeniem nowego utworu?";
    strings["Open##sgec"].plurals[0] = "Otwórz";
    strings["Save##sgec"].plurals[0] = "Zapisz";
    strings["Save as...##sgec"].plurals[0] = "Zapisz jako...";
    strings["Legacy .dmf##sgec"].plurals[0] = ".dmf (legacy)";
    strings["Export##sgec"].plurals[0] = "Eksportuj";
    strings["Restore Backup##sgec"].plurals[0] = "Przywroc kopie zapasowa";
    strings["Song Info##sgec"].plurals[0] = "O utworze";
    strings["Subsongs##sgec"].plurals[0] = "Podutwory";
    strings["Speed##sgec"].plurals[0] = "Prędkość";
    strings["Channels here...##sgec"].plurals[0] = "Tutaj są kanały...";
    strings["Chips here...##sgec"].plurals[0] = "Tutaj są układy...";
    strings["What the hell...##sgec"].plurals[0] = "Co do kurwy...";
    strings["Osc##sgec"].plurals[0] = "Osc.";
    strings["ChanOsc##sgec"].plurals[0] = "Osc. na kanał";
    strings["RegView##sgec"].plurals[0] = "Rejestry";
    strings["Stats##sgec"].plurals[0] = "Statsy";
    strings["Grooves##sgec"].plurals[0] = "Wzór rytmu";
    strings["Compat Flags##sgec"].plurals[0] = "Flagi kompat.";
    strings["XYOsc##sgec"].plurals[0] = "Osc. XY";
    strings["Panic##sgec"].plurals[0] = "Panika";
    strings["Settings##sgec"].plurals[0] = "Ustwienia";
    strings["Log##sgec"].plurals[0] = "Logi";
    strings["Debug##sgec"].plurals[0] = "Menu debugowania";
    strings["About##sgec"].plurals[0] = "O programie";
    strings["Switch to Desktop Mode##sgec"].plurals[0] = "Przełącz na tryb komputerowy";
    strings["this is NOT ROM export! only use for making sure the\n"
            "Furnace Amiga emulator is working properly by\n"
            "comparing it with real Amiga output."].plurals[0] = 

            "это НЕ экспорт в файл ROM! используйте только для\n"
            "проверки того, что эмулятор Amiga в Furnace работает правильно,\n"
            "сравнивая звук настоящей Amiga и Furnace.";
    strings["Directory##sgec"].plurals[0] = "Folder";
    strings["Bake Data##sgec"].plurals[0] = "Создать данные";
    strings["Done! Baked %d files.##sgec"].plurals[0] = "Готово! Создан %d файл.";
    strings["Done! Baked %d files.##sgec"].plurals[1] = "Готово! Создано %d файла.";
    strings["Done! Baked %d files.##sgec"].plurals[2] = "Готово! Создано %d файлов.";
    strings["Play/Edit Controls###Play/Edit Controls"].plurals[0] = "Управл. воспр./ред.###Play/Edit Controls";
    strings["Octave##sgec0"].plurals[0] = "Oktawa";
    strings["Edit Step##sgec0"].plurals[0] = "Krok edycji";
    strings["Play##sgec0"].plurals[0] = "Odtwarzaj";
    strings["Stop##sgec0"].plurals[0] = "Stop";
    strings["Edit##sgec0"].plurals[0] = "Edytuj";
    strings["Metronome##sgec0"].plurals[0] = "Metronom";
    strings["Follow##sgec0"].plurals[0] = "Следовать за прогрессом воспроизведения";
    strings["Orders##sgec1"].plurals[0] = "Matryca wzorcow";
    strings["Pattern##sgec1"].plurals[0] = "Wzorzec";
    strings["Repeat pattern##sgec0"].plurals[0] = "Зациклить текущий паттерн";
    strings["Step one row##sgec0"].plurals[0] = "Сделать один шаг по паттерну";
    strings["Poly##PolyInput"].plurals[0] = "Полифония##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Mono##PolyInput";
    strings["Polyphony##sgec0"].plurals[0] = "Полифония превью";
    strings["Stop##sgec1"].plurals[0] = "Stop";
    strings["Play##sgec1"].plurals[0] = "Odtwarzaj";
    strings["Step one row##sgec1"].plurals[0] = "Сделать один шаг по паттерну";
    strings["Repeat pattern##sgec1"].plurals[0] = "Зациклить текущий паттерн";
    strings["Edit##sgec1"].plurals[0] = "Режим редактирования";
    strings["Metronome##sgec1"].plurals[0] = "Metronom";
    strings["Octave##sgec1"].plurals[0] = "Oktawa";
    strings["Edit Step##sgec1"].plurals[0] = "Krok edycji";
    strings["Follow##sgec1"].plurals[0] = "Следовать за прогрессом воспроизведения";
    strings["Orders##sgec2"].plurals[0] = "Matryca wzorcow";
    strings["Pattern##sgec2"].plurals[0] = "Wzorzec";
    strings["Poly##PolyInput"].plurals[0] = "Polifonia##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Mono##PolyInput";
    strings["Polyphony##sgec1"].plurals[0] = "Полифония превью";
    strings["Play##sgec2"].plurals[0] = "Odtwarzaj";
    strings["Stop##sgec2"].plurals[0] = "Stop";
    strings["Step one row##sgec2"].plurals[0] = "Сделать один шаг по паттерну";
    strings["Repeat pattern##sgec2"].plurals[0] = "Зациклить текущий паттерн";
    strings["Edit##sgec2"].plurals[0] = "Режим редактирования";
    strings["Metronome##sgec2"].plurals[0] = "Metronom";
    strings["Oct.##sgec"].plurals[0] = "Okt.";
    strings["Octave##sgec2"].plurals[0] = "Oktawa";
    strings["Step##sgec0"].plurals[0] = "Krok";
    strings["Foll.##sgec"].plurals[0] = "Podazaj";
    strings["Follow##sgec2"].plurals[0] = "Podążaj za postępem odtwarzania";
    strings["Ord##FollowOrders"].plurals[0] = "Matr.##FollowOrders";
    strings["Orders##sgec3"].plurals[0] = "Matryca wzorcow";
    strings["Pat##FollowPattern"].plurals[0] = "Wz.##FollowPattern";
    strings["Pattern##sgec3"].plurals[0] = "Wzorzec";
    strings["Poly##PolyInput"].plurals[0] = "Polifonia##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Mono##PolyInput";
    strings["Polyphony##sgec2"].plurals[0] = "Polifonia podglądu";
    strings["Play Controls###Play Controls"].plurals[0] = "Управление воспроизведением###Play Controls";
    strings["Stop##sgec3"].plurals[0] = "Stop";
    strings["Play##sgec3"].plurals[0] = "Odtwarzaj";
    strings["Play from the beginning of this pattern##sgec"].plurals[0] = "Odtwarzaj с начала этого паттерна";
    strings["Repeat from the beginning of this pattern##sgec"].plurals[0] = "Воспроизвести с начала этого паттерна с зацикливанием паттерна";
    strings["Step one row##sgec3"].plurals[0] = "Сделать один шаг по паттерну";
    strings["Edit##sgec3"].plurals[0] = "Редактировать";
    strings["Metronome##sgec3"].plurals[0] = "Metronom";
    strings["Repeat pattern##sgec3"].plurals[0] = "Зациклить текущий паттерн";
    strings["Poly##PolyInput"].plurals[0] = "Полифония##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Mono##PolyInput";
    strings["Polyphony##sgec3"].plurals[0] = "Полифония превью";
    strings["Edit Controls###Edit Controls"].plurals[0] = "Управление редактированием###Edit Controls";
    strings["Octave##sgec3"].plurals[0] = "Oktawa";
    strings["Step##sgec1"].plurals[0] = "Krok";
    strings["Follow orders##sgec"].plurals[0] = "След. за воспр. в матр. патт.";
    strings["Follow pattern##sgec"].plurals[0] = "След. за воспр. в патт.";

    //   sged  src/gui/editing.cpp

    strings["can't collapse any further!##sged"].plurals[0] = "nie da się skrócić jeszcze bardziej!";
    strings["can't expand any further!##sged"].plurals[0] = "nie da się rozzszerzyć jeszcze bardziej!";

    //   sgef  src/gui/effectList.cpp

    strings["Effect List###Effect List"].plurals[0] = "Lista efektow###Effect List";
    strings["Chip at cursor: %s##sgef"].plurals[0] = "Zazanaczony uklad: %s";
    strings["Search##sgef"].plurals[0] = "Szukaj";
    strings["Effect types to show:##sgef"].plurals[0] = "Wyswietlanie typow efektow:";
    strings["All##sgef"].plurals[0] = "Wszystkie";
    strings["None##sgef"].plurals[0] = "Zadnego";
    strings["Name##sgef"].plurals[0] = "Nazwa";
    strings["Description##sgef"].plurals[0] = "Opis";

    //   sgeo  src/gui/exportOptions.cpp

    strings["one file##sgeo"].plurals[0] = "jeden plik";
    strings["multiple files (one per chip)##sgeo"].plurals[0] = "wiele plikow (po jednym na uklad)";
    strings["multiple files (one per channel)##sgeo"].plurals[0] = "wiele plikow (po jednym na kanał)";
    strings["Loops##sgeo"].plurals[0] = "Ilosc powtorzen";
    strings["Fade out (seconds)##sgeo"].plurals[0] = "Zanikanie (w sekundach))";
    strings["Cancel##sgeo0"].plurals[0] = "Anuluj";
    strings["Export##sgeo0"].plurals[0] = "Eksportuj";
    strings["settings:##sgeo"].plurals[0] = "ustawienia:";
    strings["format version##sgeo"].plurals[0] = "wersja formatu";
    strings["loop##sgeo0"].plurals[0] = "zapętlenie";
    strings["loop trail:##sgeo"].plurals[0] = "znacznik końca pętli:";
    strings["auto-detect##sgeo"].plurals[0] = "automatyczny";
    strings["add one loop##sgeo1"].plurals[0] = "добавить один цикл";
    strings["custom##sgeo"].plurals[0] = "niestandardowy";
    strings["add pattern change hints##sgeo"].plurals[0] = "добавить метки концов паттернов";
    strings["inserts data blocks on pattern changes.\n"
            "useful if you are writing a playback routine.\n\n"
            "the format of a pattern change data block is:\n"
            "67 66 FE ll ll ll ll 01 oo rr pp pp pp ...\n"
            "- ll: length, a 32-bit little-endian number\n"
            "- oo: order\n"
            "- rr: initial row (a 0Dxx effect is able to select a different row)\n"
            "- pp: pattern index (one per channel)\n\n"
            "pattern indexes are ordered as they appear in the song."].plurals[0] = 

            "вставляет блоки данных в местах смены паттернов.\n"
            "полезно, если вы пишете программу для воспроизведения.\n\n"
            "формат блока данных при смене паттерна:\n"
            "67 66 FE ll ll ll ll 01 oo rr pp pp pp ...\n"
            "- ll: długość, liczba 32-bitowa, bezpośrednia kolejność bajtów (little endian)\n"
            "- oo: строка матрицы паттернов\n"
            "- rr: начальная строка паттерна (эффект 0Dxx может её поменять)\n"
            "- pp: индекс паттерна (один на канал)\n\n"
            "индексы паттернов рассортированы в том порядке, в котором они\n"
            "встречаются в треке\n";
    strings["direct stream mode##sgeo"].plurals[0] = "tryb bezpośredniego strumienia";
    strings["required for DualPCM and MSM6258 export.\n\n"
            "allows for volume/direction changes when playing samples,\n"
            "at the cost of a massive increase in file size."].plurals[0] = 

            "необходим для экспорта DualPCM и MSM6258.\n\n"
            "повзоляет записывать изменение громкости/направления воспроизведения сэмплов\n"
            "ценой сильного увеличения размера файла.";
    strings["chips to export:##sgeo"].plurals[0] = "экспорт следующих чипов:";
    strings["this chip is only available in VGM %d.%.2x and higher!##sgeo"].plurals[0] = "этот чип доступен только в файле VGM версии %d.%.2x и выше!";
    strings["this chip is not supported by the VGM format!##sgeo"].plurals[0] = "ten uklad nie jest wspierany przez format VGM!";
    strings["select the chip you wish to export, but only up to %d of each type.##sgeo"].plurals[0] = "выберите чипы, данные для которых вы хотите включить в файл, но не более %d чипа каждого типа.";
    strings["select the chip you wish to export, but only up to %d of each type.##sgeo"].plurals[1] = "выберите чипы, данные для которых вы хотите включить в файл, но не более %d чипов каждого типа.";
    strings["select the chip you wish to export, but only up to %d of each type.##sgeo"].plurals[2] = "выберите чипы, данные для которых вы хотите включить в файл, но не более %d чипов каждого типа.";
    strings["Cancel##sgeo1"].plurals[0] = "Anuluj";
    strings["Export##sgeo1"].plurals[0] = "eksportuj";
    strings["nothing to export##sgeo2"].plurals[0] = "nic do eksportu";
    strings["Cancel##sgeo2"].plurals[0] = "Anuluj";
    strings["Commander X16 Zsound Music File##sgeo"].plurals[0] = "Commander X16 Zsound Music File";
    strings["Tick Rate (Hz)##sgeo"].plurals[0] = "Частота движка (Hz)";
    strings["loop##sgeo2"].plurals[0] = "zapętlenie";
    strings["optimize size##sgeo"].plurals[0] = "optymalizuj rozmiar";
    strings["Cancel##sgeo3"].plurals[0] = "Anuluj";
    strings["Export##sgeo3"].plurals[0] = "Eksportuj";
    strings["DefleMask file (1.1.3+)##sgeo"].plurals[0] = "plik DefleMaska (1.1.3+)";
    strings["Cancel##sgeo4"].plurals[0] = "Anuluj";
    strings["Export##sgeo4"].plurals[0] = "eksportuj";
    strings["DefleMask file (1.0/legacy)##sgeo"].plurals[0] = "plik DefleMaskq (1.0/legacy)";
    strings["Cancel##sgeo5"].plurals[0] = "Anuluj";
    strings["Export##sgeo5"].plurals[0] = "Eksportuj";
    strings["Directory##sgeo"].plurals[0] = "Folder";
    strings["Cancel##sgeo6"].plurals[0] = "Anuluj";
    strings["Bake Data##sgeo"].plurals[0] = "Wstaw dane";
    strings["Done! Baked %d files.##sgeo"].plurals[0] = "Gotowe! Wstawiono %d plik.";
    strings["Done! Baked %d files.##sgeo"].plurals[1] = "Gotowe! Wstawiono %d pliki.";
    strings["Done! Baked %d files.##sgeo"].plurals[2] = "Gotowe! Wstawiono %d plików.";
    strings["this option exports the song to a text file.\n##sgeo"].plurals[0] = "эта опция позволяет экспортировать трек в текстовый файл.\n";
    strings["Cancel##sgeo7"].plurals[0] = "Anuluj";
    strings["Export##sgeo6"].plurals[0] = "Eksportuj";
    strings["this option exports a text or binary file which\n"
            "contains a dump of the internal command stream\n"
            "produced when playing the song.\n\n"
            "technical/development use only!"].plurals[0] = 

            "эта опция позволяет создать текстовый или бинарный файл,\n"
            "в котором содержится дамп внутренних команд,\n"
            "созданных во время проигрыаания трека.\n\n"
            "используйте только при разработке!";
    strings["Cancel##sgeo8"].plurals[0] = "Anuluj";
    strings["Export (binary)##sgeo"].plurals[0] = "Eksportuj (dane binarne)";
    strings["Export (text)##sgeo"].plurals[0] = "Eksportuj (tekst)";
    strings["Audio##sgeo"].plurals[0] = "Audio";
    strings["DMF (1.0/legacy)##sgeo"].plurals[0] = "DMF (1.0/legacy)";
    strings["Amiga Validation##sgeo"].plurals[0] = "Проверка Amiga";
    strings["Text##sgeo"].plurals[0] = "Tekst";
    strings["Command Stream##sgeo"].plurals[0] = "Strumień komend";
    strings["congratulations! you've unlocked a secret panel.##sgeo"].plurals[0] = "поздравляю! вы открыли секретную панель.";
    strings["Toggle hidden systems##sgeo"].plurals[0] = "Włącz ukryhte systemy";
    strings["Toggle all instrument types##sgeo"].plurals[0] = "Включить все типы инструментов";
    strings["Set pitch linearity to Partial##sgeo"].plurals[0] = "Выставить частичную линейность высоты тона";
    strings["Enable multi-threading settings##sgeo"].plurals[0] = "Открыть настройки многопоточности";
    strings["Set fat to max##sgeo"].plurals[0] = "Выкрутить жирность на максимум";
    strings["Set muscle and fat to zero##sgeo"].plurals[0] = "Убрать все мышцы и жир";
    strings["Tell tildearrow this must be a mistake##sgeo"].plurals[0] = "Powiedz tildearrowowi, że to musi być błąd";
    strings["yeah, it's a bug. write a bug report in the GitHub page and tell me how did you get here.##sgeo"].plurals[0] = "Tak, to błąd. Wypełnij ticket na githubie i powiedz mi, jak się tu dostałeś.";

    //   sgfr  src/gui/findReplace.cpp

    strings["ignore##sgfr"].plurals[0] = "ignoruj";
    strings["equals##sgfr"].plurals[0] = "równe";
    strings["not equal##sgfr"].plurals[0] = "nie równe";
    strings["between##sgfr"].plurals[0] = "między";
    strings["not between##sgfr"].plurals[0] = "za wyjątkiem przedziału";
    strings["any##sgfr"].plurals[0] = "każdy";
    strings["none##sgfr"].plurals[0] = "żaden";
    strings["set##sgfr"].plurals[0] = "ustaw";
    strings["add##sgfr"].plurals[0] = "dodaj";
    strings["add (overflow)##sgfr"].plurals[0] = "dodaj z przepełnieniem)";
    strings["scale %##sgfr"].plurals[0] = "skaluj (w %)";
    strings["clear##sgfr"].plurals[0] = "wyczyść";

    strings["Find/Replace###Find/Replace"].plurals[0] = "znajdź/zamień###Find/Replace";
    strings["Find##sgfr0"].plurals[0] = "znajdź";
    strings["order##sgfr0"].plurals[0] = "rząd matrycy  wzorców";
    strings["row##sgfr0"].plurals[0] = "rząd";
    strings["order##sgfr1"].plurals[0] = "rząd matrycy  wzorców";
    strings["row##sgfr1"].plurals[0] = "rząd";
    strings["channel##sgfr"].plurals[0] = "kanał";
    strings["go##sgfr"].plurals[0] = "start";
    strings["no matches found!##sgfr"].plurals[0] = "nie znaleziono żadnych dopasowań!";
    strings["Back##sgfr"].plurals[0] = "Wstecz";
    strings["Note##sgfr0"].plurals[0] = "Nuta";
    strings["Ins##sgfr0"].plurals[0] = "Instrument";
    strings["Volume##sgfr0"].plurals[0] = "Głośność";
    strings["Effect##sgfr0"].plurals[0] = "Efekt";
    strings["Value##sgfr0"].plurals[0] = "Parametr";
    strings["Delete query##sgfr"].plurals[0] = "Usuń zapytanie";
    strings["Add effect##sgfr0"].plurals[0] = "Dodaj efekt";
    strings["Remove effect##sgfr0"].plurals[0] = "Usuń efekt";
    strings["Search range:##sgfr"].plurals[0] = "Zakres wyszukiwania:";
    strings["Song##sgfr"].plurals[0] = "Utwór";
    strings["Selection##sgfr"].plurals[0] = "Zaznaczenie";
    strings["Pattern##sgfr"].plurals[0] = "Wzorzec";
    strings["Confine to channels##sgfr"].plurals[0] = "Tylko wybrane kanały";
    strings["From##sgfr"].plurals[0] = "Od";
    strings["To##sgfr"].plurals[0] = "Do";
    strings["Match effect position:##sgfr"].plurals[0] = "Dopasuj położenie efektu:";
    strings["No##sgfr"].plurals[0] = "Nie";
    strings["match effects regardless of position.##sgfr"].plurals[0] = "эффекты обнаруживаются вне зависимости от положения.";
    strings["Lax##sgfr"].plurals[0] = "Luźno";
    strings["match effects only if they appear in-order.##sgfr"].plurals[0] = "эффекты обнаруживаются, если они идут в правильном порядке.";
    strings["Strict##sgfr"].plurals[0] = "Ściśle";
    strings["match effects only if they appear exactly as specified.##sgfr"].plurals[0] = "эффекты обнаруживаются, если они полностью соответствуют запросу.";
    strings["Find##sgfr1"].plurals[0] = "Znajdź";
    strings["Replace##sgfr"].plurals[0] = "Zamień";
    strings["Note##sgfr1"].plurals[0] = "Nuta";
    strings["INVALID##sgfr"].plurals[0] = "NIEPOPRAWNY.";
    strings["Ins##sgfr1"].plurals[0] = "Instrument";
    strings["Volume##sgfr1"].plurals[0] = "Głośność";
    strings["Effect##sgfr1"].plurals[0] = "Efekt";
    strings["Value##sgfr1"].plurals[0] = "Paramtr";
    strings["Add effect##sgfr1"].plurals[0] = "Dodaj efekt";
    strings["Remove effect##sgfr1"].plurals[0] = "Usuń efekt";
    strings["Effect replace mode:##sgfr"].plurals[0] = "Режим замены эффектов:";
    strings["Replace matches only##sgfr"].plurals[0] = "Заменять только совпадения";
    strings["Replace matches, then free spaces##sgfr"].plurals[0] = "Заменять совпадения, заполнять пустые ячейки";
    strings["Clear effects##sgfr"].plurals[0] = "Wyczyść efekty";
    strings["Insert in free spaces##sgfr"].plurals[0] = "Вставлять эффекты в пустых ячейках";
    strings["Replace##QueryReplace"].plurals[0] = "Zamień##QueryReplace";

    //   sggv  src/gui/grooves.cpp

    strings["Grooves###Grooves"].plurals[0] = "Wzor rytmu###Grooves";
    strings["use effect 09xx to select a groove pattern.##sggv"].plurals[0] = "użyj efektu 09xx, aby wybrać wzór rytmu.##sggv";
    strings["pattern##sggv"].plurals[0] = "wzór##sggv";
    strings["remove##sggv"].plurals[0] = "usuń##sggv";

    //   sgie  src/gui/insEdit.cpp

    strings["Name##sgie"].plurals[0] = "Nazwa";
    strings["Open##sgie0"].plurals[0] = "Otwórz";
    strings["Save##sgie"].plurals[0] = "Zapisz";
    strings["export .dmp...##sgie"].plurals[0] = "eksportuj .dmp...";
    strings["Type##sgie"].plurals[0] = "Typ";
    strings["Unknown##sgie"].plurals[0] = "Nieznany";
    strings["none of the currently present chips are able to play this instrument type!##sgie"].plurals[0] = "żaden z obecnych układów nie obsługuje instrumentu tego typu !";
    strings["Error##sgie"].plurals[0] = "Błąd";
    strings["invalid instrument type! change it first.##sgie"].plurals[0] = "nieprawidłowy typ instrumentu! zmień go najpierw.";
    strings["Instrument Editor###Instrument Editor"].plurals[0] = "Edytor instrumentów###Instrument Editor";
    strings["waiting...##sgie0"].plurals[0] = "czekaj...";
    strings["waiting...##sgie1"].plurals[0] = "czekaj...";
    strings["no instrument selected##sgie0"].plurals[0] = "nie wybrano żadnego instrumentu";
    strings["no instrument selected##sgie1"].plurals[0] = "nie wybrano żadnego instrumentu";
    strings["select one...##sgie"].plurals[0] = "wybierz jeden...";
    strings["or##sgie0"].plurals[0] = "albo";
    strings["Open##sgie1"].plurals[0] = "Otwórz";
    strings["or##sgie1"].plurals[0] = "albo";
    strings["Create New##sgie"].plurals[0] = "Stwórz nowy";
    strings["copy##sgie"].plurals[0] = "kopiuj";
    strings["paste##sgie"].plurals[0] = "wklej";
    strings["clear contents##sgie"].plurals[0] = "wyczysc zawartosc";
    strings["offset...##sgie"].plurals[0] = "przesuniecie...";
    strings["offset##sgie"].plurals[0] = "przesuniecie";
    strings["scale...##sgie"].plurals[0] = "skaluj...";
    strings["scale##sgie"].plurals[0] = "skaluj";
    strings["randomize...##sgie"].plurals[0] = "wypełnij losowymi wartościami...";
    strings["Min##sgie"].plurals[0] = "mininum";
    strings["Max##sgie"].plurals[0] = "maksimum";
    strings["randomize##sgie"].plurals[0] = "losuj";

    //   sgmx  src/gui/mixer.cpp

    strings["input##sgmx"].plurals[0] = "wejscie";
    strings["output##sgmx"].plurals[0] = "wyjscie";
    strings["Mixer##sgmx"].plurals[0] = "Mikser";
    strings["Master Volume##sgmx"].plurals[0] = "Główna Głośność";
    strings["Invert##sgmx"].plurals[0] = "Odwróć";
    strings["Volume##sgmx"].plurals[0] = "Głośność";
    strings["Panning##sgmx"].plurals[0] = "Panning";
    strings["Front/Rear##sgmx"].plurals[0] = "Przód/Tył";
    strings["Patchbay##sgmx"].plurals[0] = "Połączenie kanałów";
    strings["Automatic patchbay##sgmx"].plurals[0] = "Automatyczne poł. kanałów";
    strings["Display hidden ports##sgmx"].plurals[0] = "Wyświetl ukryte porty";
    strings["Display internal##sgmx"].plurals[0] = "Porty wewnętrzne";
    strings["System##sgmx0"].plurals[0] = "System";
    strings["Sample Preview##sgmx"].plurals[0] = "Podgląd sampla";
    strings["Metronome##sgmx"].plurals[0] = "Metronom";
    strings["System##sgmx1"].plurals[0] = "System";
    strings["disconnect all##sgmx"].plurals[0] = "rozłącz wszystko";

    //   sgns  src/gui/newSong.cpp

    strings["Choose a System!##sgns"].plurals[0] = "Wybierz system!";
    strings["Search...##sgns"].plurals[0] = "Szukaj...";
    strings["Categories##sgns"].plurals[0] = "Kategorie";
    strings["Systems##sgns"].plurals[0] = "Systemy";
    strings["I'm feeling lucky##sgns"].plurals[0] = "Szczęśliwy traf";
    strings["Cancel##sgns"].plurals[0] = "Anuluj";

    //   sgor  src/gui/orders.cpp

    strings["Add new order##sgor"].plurals[0] = "Dodaj nowy rząd matrycy";
    strings["Remove order##sgor"].plurals[0] = "Usuń rząd matrycy";
    strings["Duplicate order (right-click to deep clone)##sgor"].plurals[0] = "Sklonuj rząd (PPM by glęboko sklonować)";
    strings["Move order up##sgor"].plurals[0] = "Przenieś rząd w górę";
    strings["Move order down##sgor"].plurals[0] = "Przenieś rząd w dół";
    strings["Duplicate order at end of song (right-click to deep clone)##sgor"].plurals[0] = "Sklonuj rząd i wstaw na koniec utworu (PPM by glęboko sklonować)";
    strings["Order change mode: entire row##sgor"].plurals[0] = "Tryb zmiany: cały rząd";
    strings["Order change mode: one##sgor"].plurals[0] = "Tryb zmiany: jedna komórka";
    strings["Order edit mode: Select and type (scroll vertically)##sgor"].plurals[0] = "Режим редактирования: Выбрать и печатать (вертикальная прокрутка)";
    strings["Order edit mode: Select and type (scroll horizontally)##sgor"].plurals[0] = "Режим редактирования: Выбрать и печатать (горизонтальная прокрутка)";
    strings["Order edit mode: Select and type (don't scroll)##sgor"].plurals[0] = "Режим редактирования: Выбрать и печатать (без прокрутки)";
    strings["Order edit mode: Click to change##sgor"].plurals[0] = "Режим редактирования: нажмите для изменения";

    //   sgos  src/gui/osc.cpp

    strings["Oscilloscope###Oscilloscope"].plurals[0] = "Oscyloskop###Oscilloscope";
    strings["zoom: %.2fx (%.1fdB)##sgos"].plurals[0] = "powiększenie: %.2fx (%.1f dB)";
    strings["window size: %.1fms##sgos"].plurals[0] = "rozmiar okna: %.1f ms";
    strings["(-Infinity)dB##sgos"].plurals[0] = "(-nieskończoność) dB";

    //   sgpm  src/gui/patManager.cpp

    strings["Pattern Manager###Pattern Manager"].plurals[0] = "Menedżer wzorców###Pattern Manager";
    strings["Global Tasks##sgpm"].plurals[0] = "Globalne edytowanie";
    strings["De-duplicate patterns##sgpm"].plurals[0] = "Usuń zduplikowane wzorce";
    strings["Re-arrange patterns##sgpm"].plurals[0] = "Sortuj wzorce";
    strings["Pattern %.2X\n- not allocated##sgpm"].plurals[0] = "Wzorzec %.2X\n- niewykorzystywany";
    strings["Pattern %.2X\n- use count: %d (%.0f%%)\n\nright-click to erase##sgpm"].plurals[0] = "Wzorzec %.2X\n- ile razy pojawia się w utworze: %d (%.0f%%)\n\nPPM, aby usunąć";

    //   sgpa  src/gui/pattern.cpp

    strings["Pattern###Pattern"].plurals[0] = "Wzorzec###Pattern";
    strings["click for pattern options (effect columns/pattern names/visualizer)##sgpa"].plurals[0] = "naciśnij, aby otworzyć menu ustawień (kolumny efektów/nazwy wzorców/wizualizator efektów)";
    strings["Options:##sgpa"].plurals[0] = "Opcje:";
    strings["Effect columns/collapse##sgpa"].plurals[0] = "Roszerzanie kolumn efektów";
    strings["Pattern names##sgpa"].plurals[0] = "Nazwy wzorców";
    strings["Channel group hints##sgpa"].plurals[0] = "Wskazówki dotyczące grupowania kanałów";
    strings["Visualizer##sgpa"].plurals[0] = "Wizualizator";
    strings["Channel status:##sgpa"].plurals[0] = "Status kanału:";
    strings["No##_PCS0"].plurals[0] = "Nie##_PCS0";
    strings["Yes##_PCS1"].plurals[0] = "Tak##_PCS1";
    strings["WARNING!!##sgpa"].plurals[0] = "UWAGA!!!";
    strings["this instrument cannot be previewed because##sgpa"].plurals[0] = "ten instrument ne może zostać użyty z powodu:";
    strings["none of the chips can play it##sgpa"].plurals[0] = "żaden układ nie jest w stanie tego zagrać";
    strings["your instrument is in peril!! be careful...##sgpa"].plurals[0] = "twój instrument jest w niebezpieczeństwie!!! bądź ostrożny!...";

    //   sgpi  src/gui/piano.cpp

    strings["Piano###Piano"].plurals[0] = "Klawiatura pianina###Piano";
    strings["Options##sgpi"].plurals[0] = "Opcje";
    strings["Key layout:##sgpi"].plurals[0] = "Uklad klawiszy:";
    strings["Automatic##sgpi"].plurals[0] = "Automatyczny";
    strings["Standard##sgpi"].plurals[0] = "Standardowy";
    strings["Continuous##sgpi"].plurals[0] = "Ciągły";
    strings["Value input pad:##sgpi"].plurals[0] = "Panel wprowadzania wartości:";
    strings["Disabled##sgpi"].plurals[0] = "Wyłączony";
    strings["Replace piano##sgpi"].plurals[0] = "Zastąp klawiaturę";
    strings["Split (automatic)##sgpi"].plurals[0] = "Podzielony (automatyczny)";
    strings["Split (always visible)##sgpi"].plurals[0] = "Podzielony (zawsze widoczny)";
    strings["Share play/edit offset/range##sgpi"].plurals[0] = "Po wyłączeniu przesunięcie/zakres pianina jest inny podczas grania/edycji.";
    strings["Read-only (can't input notes)##sgpi"].plurals[0] = "Tylko do odczytu (bez możliwości wprowadzania nut)";
    strings["Input Pad###Input Pad"].plurals[0] = "Panel wprowadzania###Input Pad";

    //   sgpr  src/gui/presets.cpp

    strings["Game consoles##sgpr"].plurals[0] = "Konsole do gier wideo";
    strings["let's play some chiptune making games!##sgpr"].plurals[0] = "Zagrajmy w tworzenie chiptunów!";
    strings["Sega Genesis (extended channel 3)##sgpr"].plurals[0] = "Sega Mega Drive z rozszerzonym kanałem 3";
    strings["Sega Genesis (DualPCM, extended channel 3)##sgpr"].plurals[0] = "Sega Mega Drive (DualPCM, z rozszerzonym kanałem 3)";
    strings["Sega Genesis (with Sega CD)##sgpr"].plurals[0] = "Sega Mega Drive (z Sega Mega-CD)";
    strings["Sega Genesis (extended channel 3 with Sega CD)##sgpr"].plurals[0] = "Sega Mega Drive (z rozszerzonym kanałem 3 i Sega Mega-CD)";
    strings["Sega Genesis (CSM with Sega CD)##sgpr"].plurals[0] = "Sega Mega Drive (CSM i Sega Mega-CD)";
    strings["Sega Master System (with FM expansion)##sgpr"].plurals[0] = "Sega Master System (z rozszerzeniem FM)";
    strings["Sega Master System (with FM expansion in drums mode)##sgpr"].plurals[0] = "Sega Master System (z rozszerzeniem FM w trybie perkusji)";
    strings["Famicom with Konami VRC6##sgpr"].plurals[0] = "Famicom z Konami VRC6";
    strings["Famicom with Konami VRC7##sgpr0"].plurals[0] = "Famicom z Konami VRC7";
    strings["Famicom with MMC5##sgpr"].plurals[0] = "Famicom z MMC5";
    strings["Famicom with Sunsoft 5B##sgpr"].plurals[0] = "Famicom z Sunsoft 5B";
    strings["Famicom with Namco 163##sgpr"].plurals[0] = "Famicom z Namco 163";
    strings["Neo Geo AES (extended channel 2)##sgpr"].plurals[0] = "Neo Geo AES z rozszerzonym kanałem 2";
    strings["Neo Geo AES (extended channel 2 and CSM)##sgpr"].plurals[0] = "Neo Geo AES z rozszerzonym kanałem 2 i CSM";
    strings["Computers##sgpr"].plurals[0] = "Komputery";
    strings["let's get to work on chiptune today.##sgpr"].plurals[0] = "popracujmy dziś nad chiptunami.";
    strings["Commodore 64 (C64, 6581 SID + Sound Expander in drums mode)##sgpr"].plurals[0] = "Commodore 64 (C64, 6581 SID + Sound Expander w trybie perkusji)";
    strings["Commodore 64 (C64, 8580 SID + Sound Expander in drums mode)##sgpr"].plurals[0] = "Commodore 64 (C64, 8580 SID + Sound Expander w trybie perkusji)";
    strings["Commodore 64 (C64, 6581 SID + FM-YAM in drums mode)##sgpr"].plurals[0] = "Commodore 64 (C64, 6581 SID + FM-YAM w trybie perkusji)";
    strings["Commodore 64 (C64, 8580 SID + FM-YAM in drums mode)##sgpr"].plurals[0] = "Commodore 64 (C64, 8580 SID + FM-YAM w trybie perkusji)";
    strings["MSX + MSX-AUDIO (drums mode)##sgpr"].plurals[0] = "MSX + MSX-AUDIO (tryb perkusji)";
    strings["MSX + MSX-MUSIC (drums mode)##sgpr"].plurals[0] = "MSX + MSX-MUSIC (tryb perkusji)";
    strings["MSX + Neotron (extended channel 2)##sgpr"].plurals[0] = "MSX + Neotron z rozszerzonym kanałem 2";
    strings["MSX + Neotron (extended channel 2 and CSM)##sgpr"].plurals[0] = "MSX + Neotron z rozszerzonym kanałem 2 i CSM";
    strings["MSX + Neotron (with YM2610B)##sgpr"].plurals[0] = "MSX + Neotron (z YM2610B)";
    strings["MSX + Neotron (with YM2610B; extended channel 3)##sgpr"].plurals[0] = "MSX + Neotron (z YM2610B; z rozszerzonym kanałem 3 3)";
    strings["MSX + Neotron (with YM2610B; extended channel 3 and CSM)##sgpr"].plurals[0] = "MSX + Neotron (z YM2610B; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-88 (with PC-8801-10)##sgpr"].plurals[0] = "NEC PC-88 (z PC-8801-10)";
    strings["NEC PC-88 (with PC-8801-11)##sgpr"].plurals[0] = "NEC PC-88 (z PC-8801-11)";
    strings["NEC PC-88 (with PC-8801-11; extended channel 3)##sgpr"].plurals[0] = "NEC PC-88 (z PC-8801-11; z rozszerzonym kanałem 3)";
    strings["NEC PC-88 (with PC-8801-11; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-88 (z PC-8801-11; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-88 (with PC-8801-23)##sgpr"].plurals[0] = "NEC PC-88 (z PC-8801-23)";
    strings["NEC PC-88 (with PC-8801-23; extended channel 3)##sgpr"].plurals[0] = "NEC PC-88 (z PC-8801-23; z rozszerzonym kanałem 3)";
    strings["NEC PC-88 (with PC-8801-23; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-88 (z PC-8801-23; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-88 (with HMB-20 HIBIKI-8800)##sgpr"].plurals[0] = "NEC PC-88 (z HMB-20 HIBIKI-8800)";
    strings["NEC PC-8801mk2SR (with PC-8801-10)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-10)";
    strings["NEC PC-8801mk2SR (with PC-8801-10; extended channel 3)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-10; z rozszerzonym kanałem 3)";
    strings["NEC PC-8801mk2SR (with PC-8801-10; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-10; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-8801mk2SR (with PC-8801-11)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-11)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-11; z rozszerzonym kanałem 3 na wbudowanym OPN-ie)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on external OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-11; z rozszerzonym kanałem 3 na dodatkowym OPN-ie)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-11; z rozszerzonym kanałem 3 na obydwu OPN-ach)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-11; z rozszerzonym kanałem 3 i CSM na obydwu OPN-ach)";
    strings["NEC PC-8801mk2SR (with PC-8801-23)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-23)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-23; z rozszerzonym kanałem 3 na wbudowanym OPN-ie)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-23; z rozszerzonym kanałem 3 i CSM na wbudowanym OPN-ie)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on external OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-23; z rozszerzonym kanałem 3 na dodatkowym OPN-ie)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on external OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-23; z rozszerzonym kanałem 3 i CSM na dodatkowym OPN-ie)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-23; extended channel 3 na obydwu OPN-ach)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z PC-8801-23; z rozszerzonym kanałem 3 i CSM na obydwu OPN-ach)";
    strings["NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z HMB-20 HIBIKI-8800)";
    strings["NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800; extended channel 3)##sgpr"].plurals[0] = "NEC PC-8801mk2SR z HMB-20 HIBIKI-8800; z rozszerzonym kanałem 3)";
    strings["NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (z HMB-20 HIBIKI-8800; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-8801FA (with PC-8801-10)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-10)";
    strings["NEC PC-8801FA (with PC-8801-10; extended channel 3)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-10; z rozszerzonym kanałem 3)";
    strings["NEC PC-8801FA (with PC-8801-11)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-11)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-11; z rozszerzonym kanałem 3 na wbudowanym OPN-ie)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 on external OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-11; z rozszerzonym kanałem 3 na dodatkowym OPN-ie)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 and CSM on external OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-11; z rozszerzonym kanałem 3 i CSM na dodatkowym OPN-ie)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-11; z rozszerzonym kanałem 3 na obydwu OPN-ach)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-11; z rozszerzonym kanałem 3 i CSM na obydwu OPN-ach)";
    strings["NEC PC-8801FA (with PC-8801-23)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-23)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-23; z rozszerzonym kanałem 3 na wbudowanym OPN-ie)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-23; z rozszerzonym kanałem 3 i CSM na wbudowanym OPN-ie)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 on external OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-23; z rozszerzonym kanałem 3 na dodatkowym OPN-ie)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on external OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-23; z rozszerzonym kanałem 3 i CSM na dodatkowym OPN-ie)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-23; z rozszerzonym kanałem 3 na obydwu OPN-ach)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801FA (z PC-8801-23; z rozszerzonym kanałem 3 i CSM na obydwu OPN-ach)";
    strings["NEC PC-8801FA (with HMB-20 HIBIKI-8800)##sgpr"].plurals[0] = "NEC PC-8801FA (z HMB-20 HIBIKI-8800)";
    strings["NEC PC-8801FA (with HMB-20 HIBIKI-8800; extended channel 3)##sgpr"].plurals[0] = "NEC PC-8801FA (z HMB-20 HIBIKI-8800; z rozszerzonym kanałem 3)";
    strings["NEC PC-8801FA (with HMB-20 HIBIKI-8800; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-8801FA (z HMB-20 HIBIKI-8800; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-98 (with PC-9801-26/K)##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-26/K)";
    strings["NEC PC-98 (with PC-9801-26/K; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-26/K; z rozszerzonym kanałem 3)";
    strings["NEC PC-98 (with PC-9801-26/K; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-26/K; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-98 (with Sound Orchestra)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra)";
    strings["NEC PC-98 (with Sound Orchestra; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra; z rozszerzonym kanałem 3)";
    strings["NEC PC-98 (with Sound Orchestra; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-98 (with Sound Orchestra in drums mode)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra w trybie perkusji)";
    strings["NEC PC-98 (with Sound Orchestra in drums mode; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra w trybie perkusji; z rozszerzonym kanałem 3)";
    strings["NEC PC-98 (with Sound Orchestra in drums mode; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra w trybie perkusji; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-98 (with Sound Orchestra V)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra V)";
    strings["NEC PC-98 (with Sound Orchestra V; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra V; z rozszerzonym kanałem 3)";
    strings["NEC PC-98 (with Sound Orchestra V; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra V; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-98 (with Sound Orchestra V in drums mode)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra V w trybie perkusji)";
    strings["NEC PC-98 (with Sound Orchestra V in drums mode; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra V w trybie perkusji; z rozszerzonym kanałem 3)";
    strings["NEC PC-98 (with Sound Orchestra V in drums mode; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Orchestra V w trybie perkusji; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-98 (with PC-9801-86)##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-86)";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-86; z rozszerzonym kanałem 3)";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-86; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-98 (with PC-9801-86) stereo##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-86) stereo";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3) stereo##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-86; z rozszerzonym kanałem 3) stereo";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3 and CSM) stereo##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-86; z rozszerzonym kanałem 3 i CSM) stereo";
    strings["NEC PC-98 (with PC-9801-73)##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-73)";
    strings["NEC PC-98 (with PC-9801-73; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-73; z rozszerzonym kanałem 3)";
    strings["NEC PC-98 (with PC-9801-73; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (z PC-9801-73; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Blaster 16 dla PC-9800, kompatybilny z PC-9801-26/K)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Blaster 16 для PC-9800, kompatybilny z PC-9801-26/K; z rozszerzonym kanałem 3)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Blasterem 16 для PC-9800, kompatybilny z PC-9801-26/K; z rozszerzonym kanałem 3 i CSM)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Blasterem 16 dla PC-9800, kompatybilny z PC-9801-26/K w trybie perkusji)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Blasterem 16 dla PC-9800, kompatybilny z PC-9801-26/K w trybie perkusji; z rozszerzonym kanałem 3)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Blasterem 16 dla PC-9800, kompatybilny z PC-9801-26/K w trybie perkusji; z rozszerzonym kanałem 3 i CSM)";
    strings["ZX Spectrum (48K, SFX-like engine)##sgpr"].plurals[0] = "ZX Spectrum (48K, silnik pokroju SFX)";
    strings["ZX Spectrum (48K, QuadTone engine)##sgpr"].plurals[0] = "ZX Spectrum (48K, silnik QuadTone)";
    strings["ZX Spectrum (128K) with TurboSound##sgpr"].plurals[0] = "ZX Spectrum (128K) z TurboSound";
    strings["ZX Spectrum (128K) with TurboSound FM##sgpr"].plurals[0] = "ZX Spectrum (128K) z TurboSound FM";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 on first OPN)##sgpr"].plurals[0] = "ZX Spectrum (128K) z TurboSound FM z rozszerzonym kanałem 3 na pierwszym OPN-ie)";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on first OPN)##sgpr"].plurals[0] = "ZX Spectrum (128K) z TurboSound FM z rozszerzonym kanałem 3 i CSM na pierwszym OPNie";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 on second OPN)##sgpr"].plurals[0] = "ZX Spectrum (128K) z TurboSound FM z rozszerzonym kanałem 3 da drugim OPN-ie";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on second OPN)##sgpr"].plurals[0] = "ZX Spectrum (128K) z TurboSound FM (z rozszerzonym kanałem 3 i CSM na drugim OPN-ie";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 on both OPNs)##sgpr"].plurals[0] = "ZX Spectrum (128K) z TurboSound FM (z rozszerzonym kanałem 3 na obydwu OPN-ach";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "ZX Spectrum (128K) z TurboSound FM (z rozszerzonym kanałem 3 i CSM na obydwu OPN-ach";
    strings["Atari 800 (stereo)##sgpr"].plurals[0] = "Atari 800 (stereo)";
    strings["PC (beeper)##sgpr"].plurals[0] = "PC (brzęczyk)";
    strings["PC + AdLib (drums mode)##sgpr"].plurals[0] = "PC + AdLib (tryb perkusji)";
    strings["PC + Sound Blaster (drums mode)##sgpr"].plurals[0] = "PC + Sound Blaster (tryb perkusji)";
    strings["PC + Sound Blaster w/Game Blaster Compatible##sgpr"].plurals[0] = "PC + Sound Blaster komp. z Game Blaster";
    strings["PC + Sound Blaster w/Game Blaster Compatible (drums mode)##sgpr"].plurals[0] = "PC + Sound Blaster komp. z Game Blaster (tryb perkusji)";
    strings["PC + Sound Blaster Pro (drums mode)##sgpr"].plurals[0] = "PC + Sound Blaster Pro (tryb perkusji)";
    strings["PC + Sound Blaster Pro 2 (drums mode)##sgpr"].plurals[0] = "PC + Sound Blaster Pro 2 (tryb perkusji)";
    strings["PC + ESS AudioDrive ES1488 (native ESFM mode)##sgpr"].plurals[0] = "PC + ESS AudioDrive ES1488 (natywny tryb ESFM)";
    strings["Sharp X1 + FM addon##sgpr"].plurals[0] = "Sharp X1 + rozszerzenie FM";
    strings["FM Towns (extended channel 3)##sgpr"].plurals[0] = "FM Towns z rozszerzonym kanałem 3";
    strings["Commander X16 (VERA only)##sgpr0"].plurals[0] = "Commander X16 (tylko VERA)";
    strings["Commander X16 (with OPM)##sgpr"].plurals[0] = "Commander X16 (z OPM)";
    strings["Commander X16 (with Twin OPL3)##sgpr"].plurals[0] = "Commander X16 (z podwójnym OPL3)";
    strings["Arcade systems##sgpr"].plurals[0] = "Automaty do gier";
    strings["INSERT COIN##sgpr"].plurals[0] = "WRZUĆ MONETĘ##sgpr";
    strings["Williams/Midway Y/T unit w/ADPCM sound board##sgpr"].plurals[0] = "Аutomat Williams/Midway Y/T z kartą dźwiękową ADPCM";
    strings["Konami Battlantis (drums mode on first OPL2)##sgpr"].plurals[0] = "Konami Battlantis (pierwszy OPL2 w trybie perkusji)";
    strings["Konami Battlantis (drums mode on second OPL2)##sgpr"].plurals[0] = "Konami Battlantis (drugi OPL2 w trybie perkusji)";
    strings["Konami Battlantis (drums mode on both OPL2s)##sgpr"].plurals[0] = "Konami Battlantis (obydwa OPL2 w trybie perkusji)";
    strings["Konami Haunted Castle (drums mode)##sgpr"].plurals[0] = "Konami Haunted Castle (tryb perkusji)";
    strings["Konami S.P.Y. (drums mode)##sgpr"].plurals[0] = "Konami S.P.Y. (tryb perkusji)";
    strings["Konami Rollergames (drums mode)##sgpr"].plurals[0] = "Konami Rollergames (tryb perkusji)";
    strings["Sega System E (with FM expansion)##sgpr"].plurals[0] = "Sega System E (z rozszerzeniem FM)";
    strings["Sega System E (with FM expansion in drums mode)##sgpr"].plurals[0] = "Sega System E (z rozszerzeniem FM i trybem perkusji)";
    strings["Sega Hang-On (extended channel 3)##sgpr"].plurals[0] = "Sega Hang-On z rozszerzonym kanałem 3";
    strings["Sega Hang-On (extended channel 3 and CSM)##sgpr"].plurals[0] = "Sega Hang-On z rozszerzonym kanałem 3 i CSM)";
    strings["Sega System 18 (extended channel 3 on first OPN2C)##sgpr"].plurals[0] = "Sega System 18 z rozszerzonym kanałem 3 na pierwszym OPN2C";
    strings["Sega System 18 (extended channel 3 and CSM on first OPN2C)##sgpr"].plurals[0] = "Sega System 18 z rozszerzonym kanałem 3 i CSM na pierwszym OPN2C";
    strings["Sega System 18 (extended channel 3 on second OPN2C)##sgpr"].plurals[0] = "Sega System 18 z rozszerzonym kanałem 3 na drugim OPN2C";
    strings["Sega System 18 (extended channel 3 and CSM on second OPN2C)##sgpr"].plurals[0] = "Sega System 18 z rozszerzonym kanałem 3 i CSM na drugim OPN2C";
    strings["Sega System 18 (extended channel 3 on both OPN2Cs)##sgpr"].plurals[0] = "Sega System 18 z rozszerzonym kanałem 3 na obydwu OPN2C";
    strings["Sega System 18 (extended channel 3 and CSM on both OPN2Cs)##sgpr"].plurals[0] = "Sega System 18 z rozszerzonym kanałem 3 i CSM na obydwu OPN2C";
    strings["Sega System 32 (extended channel 3 on first OPN2C)##sgpr"].plurals[0] = "Sega System 32 z rozszerzonym kanałem 3 na pierwszym OPN2C";
    strings["Sega System 32 (extended channel 3 and CSM on first OPN2C)##sgpr"].plurals[0] = "Sega System 32 z rozszerzonym kanałem 3 i CSM na pierwszym OPN2C";
    strings["Sega System 32 (extended channel 3 on second OPN2C)##sgpr"].plurals[0] = "Sega System 32 z rozszerzonym kanałem 3 na drugim OPN2C";
    strings["Sega System 32 (extended channel 3 and CSM on second OPN2C)##sgpr"].plurals[0] = "Sega System 32 z rozszerzonym kanałem 3 i CSM na drugim OPN2C";
    strings["Sega System 32 (extended channel 3 on both OPN2Cs)##sgpr"].plurals[0] = "Sega System 32 z rozszerzonym kanałem 3 na obydwu OPN2C";
    strings["Sega System 32 (extended channel 3 and CSM on both OPN2Cs)##sgpr"].plurals[0] = "Sega System 32 z rozszerzonym kanałem 3 i CSM na obydwu OPN2C";
    strings["Capcom Arcade##sgpr"].plurals[0] = "Capcom Arcade";
    strings["Capcom Arcade (extended channel 3 on first OPN)##sgpr"].plurals[0] = "Capcom Arcade z rozszerzonym kanałem 3 na pierwszym OPN-ie";
    strings["Capcom Arcade (extended channel 3 and CSM on first OPN)##sgpr"].plurals[0] = "Capcom Arcade z rozszerzonym kanałem 3 i CSM na pierwszym OPN-ie";
    strings["Capcom Arcade (extended channel 3 on second OPN)##sgpr"].plurals[0] = "Capcom Arcade z rozszerzonym kanałem 3 na drugim OPN-ie";
    strings["Capcom Arcade (extended channel 3 and CSM on second OPN)##sgpr"].plurals[0] = "Capcom Arcade z rozszerzonym kanałem 3 i CSM na drugim OPN-ie";
    strings["Capcom Arcade (extended channel 3 on both OPNs)##sgpr"].plurals[0] = "Capcom Arcade z rozszerzonym kanałem 3 na obydwu OPN-ach";
    strings["Capcom Arcade (extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "Capcom Arcade z rozszerzonym kanałem 3 i CSM na obydwu OPN-ach";
    strings["Jaleco Ginga NinkyouDen (drums mode)##sgpr"].plurals[0] = "Jaleco Ginga NinkyouDen (tryb perkusji)";
    strings["NMK 16-bit Arcade##sgpr"].plurals[0] = "NMK 16-bit Arcade";
    strings["NMK 16-bit Arcade (extended channel 3)##sgpr"].plurals[0] = "NMK 16-bit Arcade z rozszerzonym kanałem 3";
    strings["NMK 16-bit Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "NMK 16-bit Arcade z rozszerzonym kanałem 3 i CSM)";
    strings["NMK 16-bit Arcade (w/NMK112 bankswitching)##sgpr"].plurals[0] = "NMK 16-bit Arcade (ze zmieniarką banków NMK112)";
    strings["NMK 16-bit Arcade (w/NMK112 bankswitching, extended channel 3)##sgpr"].plurals[0] = "NMK 16-bit Arcade (ze zmieniarką banków NMK112 i rozszerzonym kanałem 3";
    strings["NMK 16-bit Arcade (w/NMK112 bankswitching, extended channel 3 and CSM)##sgpr"].plurals[0] = "NMK 16-bit Arcade ze zmieniarką banków NMK112, rozszerzonym kanałem 3 i CSM)";
    strings["Atlus Power Instinct 2 (extended channel 3)##sgpr"].plurals[0] = "Atlus Power Instinct 2 z rozszerzonym kanałem 3";
    strings["Atlus Power Instinct 2 (extended channel 3 and CSM)##sgpr"].plurals[0] = "Atlus Power Instinct 2 z rozszerzonym kanałem 3 i CSM)";
    strings["Kaneko DJ Boy (extended channel 3)##sgpr"].plurals[0] = "Kaneko DJ Boy z rozszerzonym kanałem 3";
    strings["Kaneko DJ Boy (extended channel 3 and CSM)##sgpr"].plurals[0] = "Kaneko DJ Boy z rozszerzonym kanałem 3 i CSM)";
    strings["Kaneko Air Buster (extended channel 3)##sgpr"].plurals[0] = "Kaneko Air Buster z rozszerzonym kanałem 3";
    strings["Kaneko Air Buster (extended channel 3 and CSM)##sgpr"].plurals[0] = "Kaneko Air Buster z rozszerzonym kanałem 3 i CSM)";
    strings["Tecmo Ninja Gaiden (extended channel 3 on first OPN)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden z rozszerzonym kanałem 3 na pierwszym OPN-ie";
    strings["Tecmo Ninja Gaiden (extended channel 3 and CSM on first OPN)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden z rozszerzonym kanałem 3 i CSM na pierwszym OPN-ie";
    strings["Tecmo Ninja Gaiden (extended channel 3 on second OPN)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden z rozszerzonym kanałem 3 na drugim OPN-ie)";
    strings["Tecmo Ninja Gaiden (extended channel 3 and CSM on second OPN)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden z rozszerzonym kanałem 3 i CSM na drugim OPN-ie)";
    strings["Tecmo Ninja Gaiden (extended channel 3 on both OPNs)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden z rozszerzonym kanałem 3 na obydwu OPN-ach)";
    strings["Tecmo Ninja Gaiden (extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden z rozszerzonym kanałem 3 i CSM na obydwu OPN-ach";
    strings["Tecmo System (drums mode)##sgpr"].plurals[0] = "Tecmo System (tryb perkusji)";
    strings["Seibu Kaihatsu Raiden (drums mode)##sgpr"].plurals[0] = "Seibu Kaihatsu Raiden (tryb perkusji)";
    strings["Sunsoft Arcade##sgpr"].plurals[0] = "Sunsoft Arcade";
    strings["Sunsoft Arcade (extended channel 3)##sgpr"].plurals[0] = "Sunsoft Arcade z rozszerzonym kanałem 3";
    strings["Sunsoft Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "Sunsoft Arcade (z rozszerzonym kanałem 3 i CSM)";
    strings["Atari Rampart (drums mode)##sgpr"].plurals[0] = "Atari Rampart (tryb perkusji)";
    strings["Data East Karnov (extended channel 3)##sgpr"].plurals[0] = "Data East Karnov (z rozszerzonym kanałem 3 3)";
    strings["Data East Karnov (extended channel 3 and CSM)##sgpr"].plurals[0] = "Data East Karnov (z rozszerzonym kanałem 3 i CSM)";
    strings["Data East Karnov (drums mode)##sgpr"].plurals[0] = "Data East Karnov (tryb perkusji)";
    strings["Data East Karnov (extended channel 3; drums mode)##sgpr"].plurals[0] = "Data East Karnov (z rozszerzonym kanałem 3; tryb perkusji)";
    strings["Data East Karnov (extended channel 3 and CSM; drums mode)##sgpr"].plurals[0] = "Data East Karnov (z rozszerzonym kanałem 3 i CSM; tryb perkusji)";
    strings["Data East Arcade##sgpr"].plurals[0] = "Data East Arcade";
    strings["Data East Arcade (extended channel 3)##sgpr"].plurals[0] = "Data East Arcade z rozszerzonym kanałem 3";
    strings["Data East Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "Data East Arcade (z rozszerzonym kanałem 3 i CSM)";
    strings["Data East Arcade (drums mode)##sgpr"].plurals[0] = "Data East Arcade (tryb perkusji)";
    strings["Data East Arcade (extended channel 3; drums mode)##sgpr"].plurals[0] = "Data East Arcade (z rozszerzonym kanałem 3; tryb perkusji)";
    strings["Data East Arcade (extended channel 3 and CSM; drums mode)##sgpr"].plurals[0] = "Data East Arcade (z rozszerzonym kanałem 3 i CSM; tryb perkusji)";
    strings["Data East PCX (extended channel 3)##sgpr"].plurals[0] = "Data East PCX z rozszerzonym kanałem 3";
    strings["Data East PCX (extended channel 3 and CSM)##sgpr"].plurals[0] = "Data East PCX (z rozszerzonym kanałem 3 i CSM)";
    strings["Data East Dark Seal (extended channel 3)##sgpr"].plurals[0] = "Data East Dark Seal z rozszerzonym kanałem 3";
    strings["Data East Dark Seal (extended channel 3 and CSM)##sgpr"].plurals[0] = "Data East Dark Seal (z rozszerzonym kanałem 3 i CSM)";
    strings["SNK Ikari Warriors (drums mode on first OPL)##sgpr"].plurals[0] = "SNK Ikari Warriors (pierwszy OPL w trybie perkusji)";
    strings["SNK Ikari Warriors (drums mode on second OPL)##sgpr"].plurals[0] = "SNK Ikari Warriors (drugi OPL w trybie perkusji)";
    strings["SNK Ikari Warriors (drums mode on both OPLs)##sgpr"].plurals[0] = "SNK Ikari Warriors (obydwa OPL-e w trybie perkusji)";
    strings["SNK Triple Z80 (drums mode on Y8950)##sgpr"].plurals[0] = "SNK Triple Z80 (Y8950 w trybie perkusji)";
    strings["SNK Triple Z80 (drums mode on OPL)##sgpr"].plurals[0] = "SNK Triple Z80 (OPL w trybie perkusji)";
    strings["SNK Triple Z80 (drums mode on Y8950 and OPL)##sgpr"].plurals[0] = "SNK Triple Z80 (Y8950 i OPL w trybie perkusji)";
    strings["SNK Chopper I (drums mode on Y8950)##sgpr"].plurals[0] = "SNK Chopper I (Y8950 w trybie perkusji)";
    strings["SNK Chopper I (drums mode on OPL2)##sgpr"].plurals[0] = "SNK Chopper I (OPL2 w trybie perkusji)";
    strings["SNK Chopper I (drums mode on Y8950 and OPL2)##sgpr"].plurals[0] = "SNK Chopper I (Y8950 i OPL2 w trybie perkusji)";
    strings["SNK Touchdown Fever (drums mode on OPL)##sgpr"].plurals[0] = "SNK Touchdown Fever (OPL w trybie perkusji)";
    strings["SNK Touchdown Fever (drums mode on Y8950)##sgpr"].plurals[0] = "SNK Touchdown Fever (Y8950 w trybie perkusji)";
    strings["SNK Touchdown Fever (drums mode on OPL and Y8950)##sgpr"].plurals[0] = "SNK Touchdown Fever (Y8950 i OPL2 w trybie perkusji)";
    strings["Alpha denshi Alpha-68K (extended channel 3)##sgpr"].plurals[0] = "Alpha denshi Alpha-68K z rozszerzonym kanałem 3";
    strings["Alpha denshi Alpha-68K (extended channel 3 and CSM)##sgpr"].plurals[0] = "Alpha denshi Alpha-68K (z rozszerzonym kanałem 3 i CSM)";
    strings["Alpha denshi Alpha-68K (drums mode)##sgpr"].plurals[0] = "Alpha denshi Alpha-68K (tryb perkusji)";
    strings["Alpha denshi Alpha-68K (extended channel 3; drums mode)##sgpr"].plurals[0] = "Alpha denshi Alpha-68K (z rozszerzonym kanałem 3; tryb perkusji)";
    strings["Alpha denshi Alpha-68K (extended channel 3 and CSM; drums mode)##sgpr"].plurals[0] = "Alpha denshi Alpha-68K (z rozszerzonym kanałem 3 i CSM; tryb perkusji)";
    strings["Neo Geo MVS (extended channel 2)##sgpr"].plurals[0] = "Neo Geo MVS z rozszerzonym kanałem 2";
    strings["Neo Geo MVS (extended channel 2 and CSM)##sgpr"].plurals[0] = "Neo Geo MVS z rozszerzonym kanałem 2 i CSM";
    strings["Namco (3-channel WSG)##sgpr"].plurals[0] = "Namco (3-kanałowy syntezator tablicowy)";
    strings["Taito Arcade##sgpr"].plurals[0] = "Taito Arcade";
    strings["Taito Arcade (extended channel 3)##sgpr"].plurals[0] = "Taito Arcade z rozszerzonym kanałem 3";
    strings["Taito Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "Taito Arcade (z rozszerzonym kanałem 3 i CSM)";
    strings["Seta 1 + FM addon##sgpr"].plurals[0] = "Seta 1 + rozszerzenie FM";
    strings["Seta 1 + FM addon (extended channel 3)##sgpr"].plurals[0] = "Seta 1 + rozszerzenie FM z rozszerzonym kanałem 3";
    strings["Seta 1 + FM addon (extended channel 3 and CSM)##sgpr"].plurals[0] = "Seta 1 + rozszerzenie FM (z rozszerzonym kanałem 3 i CSM)";
    strings["Coreland Cyber Tank (drums mode)##sgpr"].plurals[0] = "Coreland Cyber Tank (tryb perkusji)";
    strings["Toaplan 1 (drums mode)##sgpr"].plurals[0] = "Toaplan 1 (tryb perkusji)";
    strings["Dynax/Nakanihon 3rd generation hardware##sgpr"].plurals[0] = "Trzecia generacja sprzetu Dynax/Nakanihon";
    strings["Dynax/Nakanihon 3rd generation hardware (drums mode)##sgpr"].plurals[0] = "Trzecia generacja sprzetu Dynax/Nakanihon (tryb perkusji)";
    strings["Dynax/Nakanihon Real Break (drums mode)##sgpr"].plurals[0] = "Dynax/Nakanihon Real Break (tryb perkusji)";
    strings["chips which use frequency modulation (FM) to generate sound.\nsome of these also pack more (like square and sample channels).\nActually \"FM\" here stands for phase modulation,\nbut these two are indistinguishable\nif you use sine waves.##sgpr"].plurals[0] = "układy wykorzystujące modulację częstotliwości (syntezę FM) do generowania dźwięku\nw niektorych z nich stosowane sa rowniez inne metody syntezy dźwięku (kanały fali prostokątnej lub sample).\nW rzeczywistości \"FM\" oznacza tutaj modulację fazy, ale są one nie do odróżnienia od siebie, gdy używają fal sinusoidalnych.";
    strings["Yamaha YM2203 (extended channel 3)##sgpr"].plurals[0] = "Yamaha YM2203 z rozszerzonym kanałem 3";
    strings["Yamaha YM2203 (extended channel 3 and CSM)##sgpr"].plurals[0] = "Yamaha YM2203 z rozszerzonym kanałem 3 i CSM)";
    strings["Yamaha YM2608 (extended channel 3)##sgpr"].plurals[0] = "Yamaha YM2608 z rozszerzonym kanałem 3";
    strings["Yamaha YM2608 (extended channel 3 and CSM)##sgpr"].plurals[0] = "Yamaha YM2608 z rozszerzonym kanałem 3 i CSM)";
    strings["Yamaha YM2610 (extended channel 2)##sgpr"].plurals[0] = "Yamaha YM2610 z rozszerzonym kanałem 2";
    strings["Yamaha YM2610 (extended channel 2 and CSM)##sgpr"].plurals[0] = "Yamaha YM2610 z rozszerzonym kanałem 2 i CSM)";
    strings["Yamaha YM2610B (extended channel 3)##sgpr"].plurals[0] = "Yamaha YM2610B z rozszerzonym kanałem 3";
    strings["Yamaha YM2610B (extended channel 3 and CSM)##sgpr"].plurals[0] = "Yamaha YM2610B z rozszerzonym kanałem 3 i CSM)";
    strings["Yamaha YM2612 (extended channel 3)##sgpr"].plurals[0] = "Yamaha YM2612 z rozszerzonym kanałem 3";
    strings["Yamaha YM2612 (OPN2) with DualPCM##sgpr"].plurals[0] = "Yamaha YM2612 (OPN2) z DualPCM";
    strings["Yamaha YM2612 (extended channel 3) with DualPCM and CSM##sgpr"].plurals[0] = "Yamaha YM2612 z rozszerzonym kanałem 3, DualPCM i CSM";
    strings["Yamaha YM2413 (drums mode)##sgpr"].plurals[0] = "Yamaha YM2413 (tryb perkusji)";
    strings["Yamaha YM3438 (extended channel 3)##sgpr"].plurals[0] = "Yamaha YM3438 z rozszerzonym kanałem 3";
    strings["Yamaha YM3438 (OPN2C) with DualPCM##sgpr"].plurals[0] = "Yamaha YM3438 (OPN2C) z DualPCM";
    strings["Yamaha YM3438 (extended channel 3) with DualPCM and CSM##sgpr"].plurals[0] = "Yamaha YM3438 z rozszerzonym kanałem 3, DualPCM i CSM";
    strings["Yamaha YM3526 (drums mode)##sgpr"].plurals[0] = "Yamaha YM3526 (tryb perkusji)";
    strings["Yamaha Y8950 (drums mode)##sgpr"].plurals[0] = "Yamaha Y8950 (tryb perkusji)";
    strings["Yamaha YM3812 (drums mode)##sgpr"].plurals[0] = "Yamaha YM3812 (tryb perkusji)";
    strings["Yamaha YMF262 (drums mode)##sgpr"].plurals[0] = "Yamaha YMF262 (tryb perkusji)";
    strings["Yamaha YMF289B (drums mode)##sgpr"].plurals[0] = "Yamaha YMF289B (tryb perkusji)";
    strings["ESS ES1xxx series (ESFM)##sgpr"].plurals[0] = "ESS serii ES1xxx (ESFM)";
    strings["Square##sgpr"].plurals[0] = "PSG";
    strings["these chips generate square/pulse tones only (but may include noise).##sgpr"].plurals[0] = "Układy te są w stanie generować tylko fale kwadratowe/prostokątne (ale mogą również generować szum).";
    strings["Tandy PSSJ 3-voice sound##sgpr"].plurals[0] = "Tandy PSSJ trzykanałowy syntezator dzwieku";
    strings["Sega PSG (SN76489-like)##sgpr"].plurals[0] = "Sega PSG (pochodna SN76489)";
    strings["Sega PSG (SN76489-like, Stereo)##sgpr"].plurals[0] = "Sega PSG (pochodna SN76489, stereo)";
    strings["PC Speaker##sgpr"].plurals[0] = "PC Speaker (brzeczyk)";
    strings["Sample##sgpr"].plurals[0] = "Samplery";
    strings["chips/systems which use PCM or ADPCM samples for sound synthesis.##sgpr"].plurals[0] = "uklady/systemy wykorzystujące sample formatu PCM lub ADPCM do odtwarzania dźwięku.";
    strings["Generic PCM DAC##sgpr"].plurals[0] = "Typowy przetwornik C/A";
    strings["Wavetable##sgpr"].plurals[0] = "Syntezatory tablicowe";
    strings["chips which use user-specified waveforms to generate sound.##sgpr"].plurals[0] = "chipy wykorzystujące fale zdefiniowane przez użytkownika do syntezy dźwięku.";
    strings["Namco C15 (8-channel mono)##sgpr"].plurals[0] = "Namco C15 (8-kanałowy, mono)";
    strings["Namco C30 (8-channel stereo)##sgpr"].plurals[0] = "Namco C30 (8-kanałowy, stereo)";
    strings["Famicom Disk System (chip)##sgpr"].plurals[0] = "Famicom Disk System (sam uklad)";
    strings["Specialized##sgpr"].plurals[0] = "Wyspecjalizowane";
    strings["chips/systems with unique sound synthesis methods.##sgpr"].plurals[0] = "Uklady/systemy z unikalnymi technikami syntezy dźwięku.";
    strings["Commodore PET (pseudo-wavetable)##sgpr"].plurals[0] = "Commodore PET (pseudo synteza tablicowa)";
    strings["ZX Spectrum (beeper only, SFX-like engine)##sgpr"].plurals[0] = "ZX Spectrum (tylko brzęczyk, silnik pokroju SFX)";
    strings["ZX Spectrum (beeper only, QuadTone engine)##sgpr"].plurals[0] = "ZX Spectrum (tylko brzęczyk, silnik QuadTone)";
    strings["Modern/fantasy##sgpr"].plurals[0] = "Nowoczene/nieistniejace.";
    strings["chips/systems which do not exist in reality or were made just several years ago.##sgpr"].plurals[0] = "Uklady/systemy, które nie wystepuja w fizycznej postaci lub zostały wyprodukowane zaledwie kilka lat temu.";
    strings["Commander X16 (VERA only)##sgpr1"].plurals[0] = "Commander X16 (tylko VERA)";
    strings["DefleMask-compatible##sgpr"].plurals[0] = "Zgodne z DefleMaskiem";
    strings["these configurations are compatible with DefleMask.\nselect this if you need to save as .dmf or work with that program.##sgpr"].plurals[0] = "Te presety są kompatybilne z DefleMask. Wybierz je, jeśli chcesz wyeksportować moduł do .dmf lub pracować z tym programem.";
    strings["Sega Genesis (extended channel 3)##sgpr1"].plurals[0] = "Sega Mega Drive z rozszerzeniem kanału 3";
    strings["Sega Master System (with FM expansion)##sgpr1"].plurals[0] = "Sega Master System (z rozszerzeniem FM)";
    strings["Famicom with Konami VRC7##sgpr"].plurals[0] = "Famicom z Konami VRC7";
    strings["Arcade (YM2151 and SegaPCM)##sgpr1"].plurals[0] = "Arcade (YM2151 i SegaPCM)";
    strings["Neo Geo CD (extended channel 2)##sgpr1"].plurals[0] = "Neo Geo CD  z rozszerzonym kanałem 2";

    //   sgrv  src/gui/regView.cpp

    strings["Register View###Register View"].plurals[0] = "Podglad rejestrow###Register View";
    strings["- no register pool available##sgrv"].plurals[0] = "- lista rejestrów niedostępna";

    //   sgse  src/gui/sampleEdit.cpp

    strings["%s: maximum sample rate is %d##sgse"].plurals[0] = "%s: maksymalna częstotliwość samplowania to %d";
    strings["%s: minimum sample rate is %d##sgse"].plurals[0] = "%s: minimalna częstotliwość samplowania to %d";
    strings["%s: sample rate must be %d##sgse"].plurals[0] = "%s: częstotliwość samplowania musi wynosić %d";
    strings["Sample Editor###Sample Editor"].plurals[0] = "Edytor sampli###Sample Editor";
    strings["no sample selected##sgse"].plurals[0] = "nie wybrano sampla";
    strings["select one...##sgse"].plurals[0] = "wybierz jeden...";
    strings["or##sgse0"].plurals[0] = "albo";
    strings["Open##sgse0"].plurals[0] = "Otwórz";
    strings["or##sgse1"].plurals[0] = "albo";
    strings["Create New##sgse"].plurals[0] = "Stwórz nowy";
    strings["Invalid##sgse0"].plurals[0] = "Niepoprawny.";
    strings["Invalid##sgse1"].plurals[0] = "Niepoprawny.";
    strings["%d: %s"].plurals[0] = "%d: %s";
    strings["Open##sgse1"].plurals[0] = "Otwórz";
    strings["import raw...##sgse"].plurals[0] = "importj dane surowe...";
    strings["Save##sgse"].plurals[0] = "zapisz";
    strings["save raw...##sgse"].plurals[0] = "zapisz dane surowe...";
    strings["Name##sgse"].plurals[0] = "nazwa";
    strings["SNES: loop start must be a multiple of 16 (try with %d)##sgse"].plurals[0] = "SNES: начало цикла должно быть кратно 16 (попробуйте %d)";
    strings["SNES: loop end must be a multiple of 16 (try with %d)##sgse"].plurals[0] = "SNES: конец цикла должен быть кратен 16 (попробуйте %d)";
    strings["SNES: sample length will be padded to multiple of 16##sgse"].plurals[0] = "SNES: длина сэмпла будет скорректирована до кратности 16";
    strings["QSound: loop cannot be longer than 32767 samples##sgse"].plurals[0] = "QSound: цикл не может быть длиннее 32767 сэмплов";
    strings["QSound: maximum sample length is 65535##sgse"].plurals[0] = "QSound: максимальная длина сэмпла: 65535";
    strings["NES: loop point ignored on DPCM (may only loop entire sample)##sgse"].plurals[0] = "NES: точка зацикливания игнорируется для ДИКМ (зациклить можно только сэмпл целиком)";
    strings["NES: maximum DPCM sample length is 32648##sgse"].plurals[0] = "NES: максимальная длина ДИКМ-сэмпла равна 32648";
    strings["X1-010: samples can't loop##sgse"].plurals[0] = "X1-010: сэмплы не могут быть зациклены";
    strings["X1-010: maximum sample length is 131072##sgse"].plurals[0] = "X1-010: максимальная длина сэмпла равна 131072";
    strings["GA20: samples can't loop##sgse"].plurals[0] = "GA20: сэмплы не могут быть зациклены";
    strings["YM2608: loop point ignored on ADPCM (may only loop entire sample)##sgse"].plurals[0] = "YM2608: точка зацикливания игнорируется для АДИКМ (зациклить можно только сэмпл целиком)";
    strings["YM2608: sample length will be padded to multiple of 512##sgse"].plurals[0] = "YM2608: длина сэмпла будет скорректирована до кратности 512";
    strings["YM2610: ADPCM-A samples can't loop##sgse"].plurals[0] = "YM2610: ADPCM-A сэмплы не могут быть зациклены";
    strings["YM2610: loop point ignored on ADPCM-B (may only loop entire sample)##sgse"].plurals[0] = "YM2610: точка зацикливания игнорируется для АДИКМ-B (зациклить можно только сэмпл целиком)";
    strings["YM2610: sample length will be padded to multiple of 512##sgse"].plurals[0] = "YM2610: длина сэмпла будет скорректирована до кратности 512";
    strings["YM2610: maximum ADPCM-A sample length is 2097152##sgse"].plurals[0] = "YM2610: максимальная длина АДИКМ-A сэмпла равна 2097152";
    strings["Y8950: loop point ignored on ADPCM (may only loop entire sample)##sgse"].plurals[0] = "Y8950: точка зацикливания игнорируется для АДИКМ (зациклить можно только сэмпл целиком)";
    strings["Y8950: sample length will be padded to multiple of 512##sgse"].plurals[0] = "Y8950: длина сэмпла будет скорректирована до кратности 512";
    strings["Amiga: loop start must be a multiple of 2##sgse"].plurals[0] = "Amiga: начало зацикливания должно быть кратно 2";
    strings["Amiga: loop end must be a multiple of 2##sgse"].plurals[0] = "Amiga: конец зацикливания должен быть кратен 2";
    strings["Amiga: maximum sample length is 131070##sgse"].plurals[0] = "Amiga: максимальная длина сэмпла равна 131070";
    strings["SegaPCM: maximum sample length is 65280##sgse"].plurals[0] = "SegaPCM: максимальная длина сэмпла равна 65280";
    strings["K053260: loop point ignored (may only loop entire sample)##sgse"].plurals[0] = "K053260: точка зацикливания игнорируется (зациклить можно только сэмпл целиком)";
    strings["K053260: maximum sample length is 65535##sgse"].plurals[0] = "K053260: максимальная длина сэмпла равна 65535";
    strings["C140: maximum sample length is 65535##sgse"].plurals[0] = "C140: максимальная длина сэмпла равна 65535";
    strings["C219: loop start must be a multiple of 2##sgse"].plurals[0] = "C219: начало зацикливания должно быть кратно 2";
    strings["C219: loop end must be a multiple of 2##sgse"].plurals[0] = "C219: конец зацикливания должен быть кратен 2";
    strings["C219: maximum sample length is 131072##sgse"].plurals[0] = "C219: максимальная длина сэмпла равна 131072";
    strings["MSM6295: samples can't loop##sgse"].plurals[0] = "MSM6295: сэмплы не могут быть зациклены";
    strings["MSM6295: maximum bankswitched sample length is 129024##sgse"].plurals[0] = "MSM6295: максимальная длина сэмпла с заменой банков равна 129024";
    strings["ES5506: backward loop mode isn't supported##sgse"].plurals[0] = "ES5506: режим обратного зацикливания не поддерживается";
    strings["backward/ping-pong only supported in Generic PCM DAC\nping-pong also on ES5506##sgse"].plurals[0] = "режим обратного и \"туда-обратно\" зацикливания поддерживается только для универсального ИКМ ЦАП\n\"туда-обратно\" также поддерживается для ES5506";
    strings["Info##sgse"].plurals[0] = "Информация";
    strings["Rate##sgse0"].plurals[0] = "Частота";
    strings["Compat Rate##sgse"].plurals[0] = "Совместимая частота";
    strings["used in DefleMask-compatible sample mode (17xx), in where samples are mapped to an octave.##sgse"].plurals[0] = "используется при воспроизведении в режиме совместимости с DefleMask (17xx), в котором сэмплы соответствуют октаве.";
    strings["Loop##sgse"].plurals[0] = "Цикл";
    strings["Loop (length: %d)##Loop"].plurals[0] = "Цикл (длина: %d)##Loop";
    strings["changing the loop in a BRR sample may result in glitches!##sgse0"].plurals[0] = "Смена зацикленной части в сэмпле BRR может привести к сбоям!";
    strings["Chips##sgse"].plurals[0] = "Układy";
    strings["Type##sgse"].plurals[0] = "Typ";
    strings["BRR emphasis##sgse"].plurals[0] = "Постобработка для BRR";
    strings["this is a BRR sample.\nenabling this option will muffle it (only affects non-SNES chips).##sgse"].plurals[0] = "это сэмпл BRR.\nвключение этой опции \"приглушит\" его (на всех чипах кроме SNES).";
    strings["enable this option to slightly boost high frequencies\nto compensate for the SNES' Gaussian filter's muffle.##sgse"].plurals[0] = "включите эту опцию для небольшого усиления высоких частот\nдля компенсации фильтрующего свойства гауссовой интерполяции, из-за которого сэмпл \"приглушается\".";
    strings["8-bit dither##sgse"].plurals[0] = "8-bitowy dithering";
    strings["dither the sample when used on a chip that only supports 8-bit samples.##sgse"].plurals[0] = "произвести дизеринг для сэмпла при его использовании для чипа, поддерживающего только 8-битные сэмплы.";
    strings["Note##sgse"].plurals[0] = "Nuta";
    strings["%s"].plurals[0] = "%s";
    strings["Fine##sgse"].plurals[0] = "Расстройка";
    strings["Mode##sgse"].plurals[0] = "Tryb";
    strings["Start##sgse"].plurals[0] = "Start";
    strings["changing the loop in a BRR sample may result in glitches!##sgse1"].plurals[0] = "смена зацикленной части в сэмпле BRR может привести к сбоям!";
    strings["End##sgse"].plurals[0] = "Koniec";
    strings["changing the loop in a BRR sample may result in glitches!##sgse2"].plurals[0] = "смена зацикленной части в сэмпле BRR может привести к сбоям!";
    strings["%s\n%d bytes free##sgse"].plurals[0] = "%s\nwolny %d bajt";
    strings["%s\n%d bytes free##sgse"].plurals[1] = "%s\nсвободно %d байта";
    strings["%s\n%d bytes free##sgse"].plurals[2] = "%s\nсвободно %d байт";
    strings["%s (%s)\n%d bytes free##sgse"].plurals[0] = "%s (%s)\nсвободен %d байт";
    strings["%s (%s)\n%d bytes free##sgse"].plurals[1] = "%s (%s)\nсвободно %d байта";
    strings["%s (%s)\n%d bytes free##sgse"].plurals[2] = "%s (%s)\nсвободно %d байт";
    strings["\n\nnot enough memory for this sample!##sgse"].plurals[0] = "\n\nнедостаточно памяти для этого сэмпла!";
    strings["Edit mode: Select##sgse"].plurals[0] = "Режим редактирования: выделение";
    strings["Edit mode: Draw##sgse"].plurals[0] = "Режим редактирования: рисование";
    strings["Resize##sgse0"].plurals[0] = "Масштабировать";
    strings["Samples##sgse0"].plurals[0] = "Сэмплов (новый размер)";
    strings["Resize##sgse1"].plurals[0] = "Масштабировать";
    strings["couldn't resize! make sure your sample is 8 or 16-bit.##sgse"].plurals[0] = "не получилось отмасштабировать! убедитесь, что это 8- или 16-битный сэмпл.";
    strings["Resample##sgse0"].plurals[0] = "Изменить частоту дискретизации";
    strings["Rate##sgse1"].plurals[0] = "Частота";
    strings["Factor##sgse"].plurals[0] = "Współczynnik";
    strings["Filter##sgse"].plurals[0] = "Filtr";
    strings["Resample##sgse1"].plurals[0] = "Применить";
    strings["couldn't resample! make sure your sample is 8 or 16-bit.##sgse"].plurals[0] = "не получилось изменить частоту дискретизации! убедитесь, что это 8- или 16-битный сэмпл.";
    strings["Undo##sgse"].plurals[0] = "Отменить";
    strings["Redo##sgse"].plurals[0] = "Повторить";
    strings["Amplify##sgse"].plurals[0] = "Усилить";
    strings["Volume##sgse"].plurals[0] = "Głośność";
    strings["Apply##sgse0"].plurals[0] = "Zastosuj";
    strings["Normalize##sgse"].plurals[0] = "Normalizuj";
    strings["Fade in##sgse"].plurals[0] = "Плавное нарастание";
    strings["Fade out##sgse"].plurals[0] = "Плавное затухание";
    strings["Insert silence##sgse"].plurals[0] = "Вставить тишину";
    strings["Samples##sgse1"].plurals[0] = "Сэмплов";
    strings["Go##sgse"].plurals[0] = "Применить";
    strings["couldn't insert! make sure your sample is 8 or 16-bit.##sgse"].plurals[0] = "не получилось вставить! убедитесь, что это 8- или 16-битный сэмпл.";
    strings["Apply silence##sgse"].plurals[0] = "Применить тишину";
    strings["Delete##sgse"].plurals[0] = "Usuń";
    strings["Trim##sgse"].plurals[0] = "Obetnij";
    strings["Reverse##sgse"].plurals[0] = "Реверс";
    strings["Invert##sgse"].plurals[0] = "Инвертировать";
    strings["Signed/unsigned exchange##sgse"].plurals[0] = "Знаковый <-> беззнаковый";
    strings["Apply filter##sgse"].plurals[0] = "Zastosuj filtr";
    strings["Cutoff:##sgse"].plurals[0] = "Частота среза:";
    strings["From##sgse"].plurals[0] = "Od";
    strings["To##sgse"].plurals[0] = "Do";
    strings["Resonance##sgse"].plurals[0] = "Резонанс (добротность)";
    strings["Power##sgse"].plurals[0] = "Порядок фильтра";
    strings["Low-pass##sgse"].plurals[0] = "dolno-przepustowy";
    strings["Band-pass##sgse"].plurals[0] = "środkowo-przepustowy";
    strings["High-pass##sgse"].plurals[0] = "górno-przepustowy";
    strings["Apply##sgse1"].plurals[0] = "Zastosuj";
    strings["Crossfade loop points##sgse"].plurals[0] = "Сделать плавный переход между началом и концом зацикленной части";
    strings["Number of samples##sgse"].plurals[0] = "Ilosc sampli";
    strings["Linear <-> Equal power##sgse"].plurals[0] = "Линейный <-> Одинаковая степень";
    strings["Apply##sgse2"].plurals[0] = "Zastosuj";
    strings["Crossfade: length would go out of bounds. Aborted...##sgse"].plurals[0] = "Плавный переход: длина выйдет за границы. Действие отменено.";
    strings["Crossfade: length would overflow loopStart. Try a smaller random value.##sgse"].plurals[0] = "Плавный переход: длина выйдет за пределы начала цикла. Попробуйте с меньшим случайным значением.";
    strings["Preview sample##sgse"].plurals[0] = "Poglad sampla";
    strings["Stop sample preview##sgse"].plurals[0] = "Zatrzymaj podglad sampla";
    strings["Create instrument from sample##sgse"].plurals[0] = "Stwórz instrument z sampla";
    strings["Zoom##sgse0"].plurals[0] = "Powieksz";
    strings["Zoom##sgse1"].plurals[0] = "Powieksz";
    strings["Auto##sgse"].plurals[0] = "Automatyczny";
    strings["cut##sgse"].plurals[0] = "wytnij";
    strings["copy##sgse"].plurals[0] = "kopiuj";
    strings["paste##sgse"].plurals[0] = "wklej";
    strings["paste (replace)##sgse"].plurals[0] = "wklej i zamień";
    strings["paste (mix)##sgse"].plurals[0] = "вставить со смешением";
    strings["select all##sgse"].plurals[0] = "wybierz wszystko";
    strings["set loop to selection##sgse"].plurals[0] = "зациклить по выделенной части";
    strings["create wavetable from selection##sgse"].plurals[0] = "создать волновую таблицу из выделенной части";
    strings["Draw##sgse"].plurals[0] = "Rysuj";
    strings["Select##sgse"].plurals[0] = "Wybierz";
    strings["%d samples##sgse"].plurals[0] = "%d sampel";
    strings["%d samples##sgse"].plurals[1] = "%d sample";
    strings["%d samples##sgse"].plurals[2] = "%d sampli";
    strings["%d bytes##sgse"].plurals[0] = "%d bajt";
    strings["%d bytes##sgse"].plurals[1] = "%d bajty";
    strings["%d bytes##sgse"].plurals[2] = "%d bajtów";
    strings[" (%d-%d: %d samples)##sgse"].plurals[0] = " (%d-%d: %d sampel)";
    strings[" (%d-%d: %d samples)##sgse"].plurals[1] = " (%d-%d: %d sample)";
    strings[" (%d-%d: %d samples)##sgse"].plurals[2] = " (%d-%d: %d sampli)";
    strings["Non-8/16-bit samples cannot be edited without prior conversion.##sgse"].plurals[0] = "Sample w formacie innym niż 8-bitowy lub 16-bitowy PCM nie mogą być edytowane bez uprzedniej konwersji do jednego z tych formatów.";

    //   sgsi  src/gui/songInfo.cpp

    strings["Song Info###Song Information"].plurals[0] = "O utworze###Song Information";
    strings["Name##sgsi"].plurals[0] = "Nazwa";
    strings["Author##sgsi"].plurals[0] = "Autor";
    strings["Album##sgsi"].plurals[0] = "Album";
    strings["System##sgsi"].plurals[0] = "System";
    strings["Auto##sgsi"].plurals[0] = "Auto";
    strings["Tuning (A-4)##sgsi"].plurals[0] = "Tuning (A-4))";

    //   sgsn  src/gui/songNotes.cpp

    strings["Song Comments###Song Comments"].plurals[0] = "Komentarze do utworu###Song Comments";

    //   sgsp  src/gui/speed.cpp

    strings["Speed###Speed"].plurals[0] = "Prędkość###Speed";
    strings["Base Tempo##TempoOrHz"].plurals[0] = "Tempo bazowe##TempoOrHz";
    strings["Tick Rate##TempoOrHz"].plurals[0] = "Częstotliwość odświeżania##TempoOrHz";
    strings["click to display tick rate##sgsp"].plurals[0] = "kliknij aby wyświetlić częstotliwość odświeżania";
    strings["click to display base tempo##sgsp"].plurals[0] = "kliknuj aby wyświetlić tempo bazowe";
    strings["Groove##sgsp"].plurals[0] = "Wzór rytmu";
    strings["click for one speed##sgsp"].plurals[0] = "nnaciśnij, aby wyświetlić jedną prędkość";
    strings["Speeds##sgsp"].plurals[0] = "Prędkości";
    strings["click for groove pattern##sgsp"].plurals[0] = "naciśnij, aby wyświetlić wzory rytmu";
    strings["Speed##sgsp"].plurals[0] = "Prędkość";
    strings["click for two (alternating) speeds##sgsp"].plurals[0] = "naciśnij, aby wyświetlić dwie (naprzemienne) prędkości";
    strings["Virtual Tempo##sgsp"].plurals[0] = "Wirtualne tempo";
    strings["Numerator##sgsp"].plurals[0] = "Licznik";
    strings["Denominator (set to base tempo)##sgsp"].plurals[0] = "Mianownik (ustaw na równe tempu podstawowemu)";
    strings["Divider##sgsp"].plurals[0] = "Dzielnik";
    strings["Highlight##sgsp"].plurals[0] = "Podświetlenie";
    strings["Pattern Length##sgsp"].plurals[0] = "Długość wzorca";
    strings["Song Length##sgsp"].plurals[0] = "Długość utworu";

    //   sgst  src/gui/stats.cpp

    strings["Statistics###Statistics"].plurals[0] = "Statystyki###Statistics";
    strings["Audio load##sgst"].plurals[0] = "Obciążenie audio";
    strings["%d/%dKB##sgst"].plurals[0] = "%d/%d kB";

    //   sgss  src/gui/subSongs.cpp

    strings["Subsongs###Subsongs"].plurals[0] = "Podutwory###Subsongs";
    strings["%d. <no name>##sgss0"].plurals[0] = "%d. <bez nazwy>";
    strings["%d. <no name>##sgss1"].plurals[0] = "%d. <bez nazwy>";
    strings["Move up##sgss"].plurals[0] = "Przesuń w górę";
    strings["Move down##sgss"].plurals[0] = "Przesuń w dół";
    strings["too many subsongs!##sgss0"].plurals[0] = "zbyt wiele podutworów!";
    strings["Add##sgss"].plurals[0] = "Dodaj";
    strings["too many subsongs!##sgss1"].plurals[0] = "zbyt wiele podutworów!!";
    strings["Duplicate##sgss"].plurals[0] = "Sklonuj";
    strings["this is the only subsong!##sgss"].plurals[0] = "to jest jedyny podutwór!";
    strings["are you sure you want to remove this subsong?##sgss"].plurals[0] = "czy jesteś pewien że chcesz usuąć ten podutwór?";
    strings["Remove##sgss"].plurals[0] = "Usuń";
    strings["Name##sgss"].plurals[0] = "Nazwa";

    //   sgsc  src/gui/sysConf.cpp

    strings["Clock rate:##sgsc0"].plurals[0] = "Taktowanie zegara:";
    strings["Chip type:##sgsc0"].plurals[0] = "Typ układu:";
    strings["YM3438 (9-bit DAC)##sgsc"].plurals[0] = "YM3438 (9-bitowy DAC)";
    strings["YM2612 (9-bit DAC with distortion)##sgsc"].plurals[0] = "YM2612 (9-bitowy DAC ze zniekształceniami)";
    strings["YMF276 (external DAC)##sgsc"].plurals[0] = "YMF276 (zewnętrzy DAC)";
    strings["Disable ExtCh FM macros (compatibility)##sgsc0"].plurals[0] = "Wyłacz makra rozszerzonych kanałów FM (dla kompatybilności)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc0"].plurals[0] = "Zmiana instr. na operatorach 2-4 rozsz. kanału ma wpływ na FB (dla kompatybilności)";
    strings["Clock rate:##sgsc1"].plurals[0] = "Taktowanie zegara:";
    strings["1.79MHz (Half NTSC)##sgsc"].plurals[0] = "1.79 MHz (połowa NTSC)";
    strings["Chip type:##sgsc1"].plurals[0] = "Typ układu:";
    strings["TI SN76489 with Atari-like short noise##sgsc"].plurals[0] = "TI SN76489 z krótkim szumem podobnym do Atari";
    strings["Tandy PSSJ 3-voice sound##sgsc"].plurals[0] = "Trzykanałowe audio Tandy PSSJ";
    strings["Disable noise period change phase reset##sgsc"].plurals[0] = "Wyłącz reset fazy podczas zmiany okresu szumu";
    strings["Disable easy period to note mapping on upper octaves##sgsc0"].plurals[0] = "Wyłącz uproszczone mapowanie okresu na nutę na wyższych oktawach ";
    strings["Pseudo-PAL##sgsc0"].plurals[0] = "Pseudo-PAL";
    strings["Disable anti-click##sgsc0"].plurals[0] = "Wyłącz anty-stukanie";
    strings["Chip revision:##sgsc0"].plurals[0] = "Rewizja układu:";
    strings["HuC6280 (original)##sgsc"].plurals[0] = "HuC6280 (oryginalny)";
    strings["CPU rate:##sgsc"].plurals[0] = "Taktowanie CPU:";
    strings["Sample memory:##sgsc"].plurals[0] = "Pamięć na sample:";
    strings["8K (rev A/B/E)##sgsc"].plurals[0] = "8kB (wersje A/B/E)";
    strings["64K (rev D/F)##sgsc"].plurals[0] = "64kB (wersje D/F)";
    strings["DAC resolution:##sgsc"].plurals[0] = "Rozdzielczość DAC:";
    strings["16-bit (rev A/B/D/F)##sgsc"].plurals[0] = "16-bit (wersje A/B/D/F)";
    strings["8-bit + TDM (rev C/E)##sgsc"].plurals[0] = "8-bit + multipleksowanie z podziałem czasu (wersje C/E)";
    strings["Enable echo##sgsc0"].plurals[0] = "Wlacz echo";
    strings["Swap echo channels##sgsc"].plurals[0] = "Zamień miejscami kanały echo";
    strings["Echo delay:##sgsc0"].plurals[0] = "Задержка эхо:";
    strings["Echo resolution:##sgsc"].plurals[0] = "Разрешение эхо:";
    strings["Echo feedback:##sgsc0"].plurals[0] = "Обратная связь эхо:";
    strings["Echo volume:##sgsc0"].plurals[0] = "Głośność echo:";
    strings["Disable anti-click##sgsc1"].plurals[0] = "Wyłącz anty-stukanie";
    strings["Chip revision:##sgsc1"].plurals[0] = "Rewizja konsoli:";
    strings["Original (DMG)##sgsc"].plurals[0] = "Oryginalny (DMG)";
    strings["Game Boy Color (rev C)##sgsc"].plurals[0] = "Game Boy Color (wersja C)";
    strings["Game Boy Color (rev E)##sgsc"].plurals[0] = "Game Boy Color (wersja E)";
    strings["Wave channel orientation:##sgsc"].plurals[0] = "Orientacja koanału syntezy tablicowej";
    strings["Normal##sgsc"].plurals[0] = "Normalna";
    strings["Inverted##sgsc"].plurals[0] = "Odwrócona";
    strings["Exact data (inverted)##sgsc"].plurals[0] = "Te same dane (odwrócona)";
    strings["Exact output (normal)##sgsc"].plurals[0] = "Ten sam dźwięk (normalna)";
    strings["Pretty please one more compat flag when I use arpeggio and my sound length##sgsc"].plurals[0] = "Ну пожалуйста ещё один флаг совместимости когда я использую арпеджио и малую длину звука на шумовом канале";
    strings["Clock rate:##sgsc2"].plurals[0] = "Taktowanie zegara:";
    strings["Arcade (4MHz)##sgsc"].plurals[0] = "Arcade (4 MHz)";
    strings["Half NTSC (1.79MHz)##sgsc"].plurals[0] = "Polowa NTSC (1.79 MHz)";
    strings["Patch set:##sgsc"].plurals[0] = "Zestaw instrumentów:";
    strings["Ignore top/hi-hat frequency changes##sgsc"].plurals[0] = "Ignoruj zmiany częstotliwości talerzy i hi-hatów";
    strings["Apply fixed frequency to all drums at once##sgsc"].plurals[0] = "Stosuj stałą częstotliwość do wszystich instrumentów perkusyjnych";
    strings["Broken pitch macro/slides (compatibility)##sgsc0"].plurals[0] = "Сломанное портаменто эффектов и макросов (совместимость)";
    strings["Pseudo-PAL##sgsc1"].plurals[0] = "Pseudo-PAL";
    strings["Broken pitch macro/slides (compatibility)##sgsc1"].plurals[0] = "Сломанное портаменто эффектов и макросов (совместимость)";
    strings["Clock rate:##sgsc20"].plurals[0] = "Taktowanie zegara:";
    strings["DPCM channel mode:##sgsc"].plurals[0] = "Tryb kanału DPCM:";
    strings["DPCM (muffled samples; low CPU usage)##sgsc"].plurals[0] = "DPCM (przytłumione sample, niskie zużycie CPU)";
    strings["PCM (crisp samples; high CPU usage)##sgsc"].plurals[0] = "PCM (czyste sample, wysokie zużycie CPU)";
    strings["Clock rate:##sgsc18"].plurals[0] = "Taktowanie zegara:";
    strings["Clock rate:##sgsc19"].plurals[0] = "Taktowanie zegara:";
    strings["Global parameter priority:##sgsc0"].plurals[0] = "Приоритет глобальных параметров:";
    strings["Left to right##sgsc0"].plurals[0] = "Z lewej do prawej";
    strings["Last used channel##sgsc0"].plurals[0] = "Последний использованный канал";
    strings["Hard reset envelope:##sgsc"].plurals[0] = "Obwiednia при жёстком перезапуске:";
    strings["Attack##sgsc"].plurals[0] = "Atak";
    strings["Decay##sgsc"].plurals[0] = "Opadanie";
    strings["Sustain##sgsc"].plurals[0] = "Poodtrzymanie";
    strings["Release##sgsc"].plurals[0] = "Zwolnienie";
    strings["Envelope reset time:##sgsc"].plurals[0] = "Czas resetowania obwiedni:";
    strings["- 0 disables envelope reset. not recommended!\n- 1 may trigger SID envelope bugs.\n- values that are too high may result in notes being skipped.##sgsc"].plurals[0] = "- 0 отключает сброс огибающей. не рекомендуется!\n- 1 может привести к появлению сбоев огибающей SID.\n- слишком большие значения могут привести к пропуску коротких нот.";
    strings["Disable 1Exy env update (compatibility)##sgsc"].plurals[0] = "Отключить обновление огибающей при применении эффекта 1Exy (совместимость)";
    strings["Relative duty and cutoff macros are coarse (compatibility)##sgsc"].plurals[0] = "Makra скважности и частоты среза в относительном режиме имеют меньшее разрешение (совместимость)";
    strings["Disable ExtCh FM macros (compatibility)##sgsc1"].plurals[0] = "Отключить FM-макросы для расширенного канала (совместимость)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc1"].plurals[0] = "Смена инструмента на операторах 2-4 расш. канала меняет FB (совместимость)";
    strings["SSG Volume##sgsc0"].plurals[0] = "Głośność SSG";
    strings["FM/ADPCM Volume##sgsc0"].plurals[0] = "Głośność FM/ADPCM";
    strings["Clock rate:##sgsc3"].plurals[0] = "Taktowanie zegara:";
    strings["0.83MHz (Pre-divided Sunsoft 5B on PAL)##sgsc"].plurals[0] = "0.83 MHz (Sunsoft 5B с предварительным делителем частоты, PAL)";
    strings["0.89MHz (Pre-divided Sunsoft 5B)##sgsc"].plurals[0] = "0.89 MHz (Sunsoft 5B с предварительным делителем частоты)";
    strings["Chip type:##sgsc2"].plurals[0] = "Typ układu:";
    strings["note: AY-3-8914 is not supported by the VGM format!##sgsc"].plurals[0] = "uwaga: AY-3-8914 nie jest wspieramy przez format VGM!";
    strings["Stereo##_AY_STEREO"].plurals[0] = "Stereo##_AY_STEREO";
    strings["Separation##sgsc"].plurals[0] = "Rozdzielenie";
    strings["Half Clock divider##_AY_CLKSEL"].plurals[0] = "Podziel taktowania zegara przez 2##_AY_CLKSEL";
    strings["Stereo separation:##sgsc"].plurals[0] = "Rozdzielenie stereo:";
    strings["Model:##sgsc"].plurals[0] = "Model:";
    strings["Chip memory:##sgsc"].plurals[0] = "Pamiec ukladu:";
    strings["2MB (ECS/AGA max)##sgsc"].plurals[0] = "2 MB (maksimum dla ECS/AGA)";
    strings["512KB (OCS max)##sgsc"].plurals[0] = "512 kB (maksimum dla OCS)";
    strings["Bypass frequency limits##sgsc"].plurals[0] = "Ignoruj limity częstotliwości";
    strings["Mixing mode:##sgsc"].plurals[0] = "Tryb miksowania:";
    strings["Mono##sgsc"].plurals[0] = "Mono";
    strings["Mono (no distortion)##sgsc"].plurals[0] = "Mono (bez zakłóceń)";
    strings["Stereo##sgsc0"].plurals[0] = "Stereo";
    strings["Clock rate:##sgsc4"].plurals[0] = "Taktowanie zegara:";
    strings["Speaker type:##sgsc"].plurals[0] = "Typ brzęczyka:";
    strings["Unfiltered##sgsc"].plurals[0] = "Bez filtrowania";
    strings["Cone##sgsc"].plurals[0] = "Stożek";
    strings["Piezo##sgsc"].plurals[0] = "Piezo";
    strings["Use system beeper (Linux only!)##sgsc"].plurals[0] = "Używaj prawdziwego brzęczyka systemowego (tylko na Linuxie!)";
    strings["Reset phase on frequency change##sgsc"].plurals[0] = "Resetuj fazę podczas zmiany częstotliwości";
    strings["Echo delay:##sgsc1"].plurals[0] = "Opóżnienie:";
    strings["Echo feedback:##sgsc1"].plurals[0] = "Sprzężenie zwrotne echo:";
    strings["Clock rate:##sgsc5"].plurals[0] = "Taktowanie zegara:";
    strings["Stereo##sgsc1"].plurals[0] = "Stereo";
    strings["Bankswitched (Seta 2)##sgsc"].plurals[0] = "Ze zmieniarką banków (Seta 2)";
    strings["Clock rate:##sgsc6"].plurals[0] = "Taktowanie zegara:";
    strings["Initial channel limit:##sgsc0"].plurals[0] = "Początkowy limit ilości kanałów:";
    strings["Disable hissing##sgsc"].plurals[0] = "Wyłącz trzeszczenie";
    strings["Scale frequency to wave length##sgsc"].plurals[0] = "Масштабировать частоту под длину волны";
    strings["Initial channel limit:##sgsc1"].plurals[0] = "Początkowy limit ilości kanałów:";
    strings["Volume scale:##sgsc0"].plurals[0] = "Масштабирование громкости:";
    strings["Clock rate:##sgsc7"].plurals[0] = "Taktowanie zegara:";
    strings["Output rate:##sgsc0"].plurals[0] = "Частота квантования на выходе:";
    strings["FM: clock / 72, SSG: clock / 16##sgsc0"].plurals[0] = "FM: takt. zegara / 72, SSG: takt. zegara / 16";
    strings["FM: clock / 36, SSG: clock / 8##sgsc"].plurals[0] = "FM: takt. zegara / 36, SSG: takt. zegara / 8";
    strings["FM: clock / 24, SSG: clock / 4##sgsc"].plurals[0] = "FM: takt. zegara / 24, SSG: takt. zegara / 4";
    strings["SSG Volume##sgsc1"].plurals[0] = "Głośność SSG";
    strings["FM Volume##sgsc"].plurals[0] = "Głośność FM";
    strings["Disable ExtCh FM macros (compatibility)##sgsc2"].plurals[0] = "Отключить FM-макросы для расширенного канала (совместимость)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc2"].plurals[0] = "Смена инструмента на операторах 2-4 расш. канала меняет FB (совместимость)";
    strings["Clock rate:##sgsc8"].plurals[0] = "Taktowanie zegara:";
    strings["8MHz (Arcade)##sgsc"].plurals[0] = "8 MHz (Arcade)";
    strings["Output rate:##sgsc1"].plurals[0] = "Частота квантования на выходе:";
    strings["FM: clock / 144, SSG: clock / 32##sgsc"].plurals[0] = "FM: takt. zegara / 144, SSG: takt. zegara / 32";
    strings["FM: clock / 72, SSG: clock / 16##sgsc1"].plurals[0] = "FM: takt. zegara / 72, SSG: takt. zegara / 16";
    strings["FM: clock / 48, SSG: clock / 8##sgsc"].plurals[0] = "FM: takt. zegara / 48, SSG: takt. zegara / 8";
    strings["SSG Volume##sgsc2"].plurals[0] = "Głośność SSG";
    strings["FM/ADPCM Volume##sgsc1"].plurals[0] = "Głośność FM/ADPCM";
    strings["Disable ExtCh FM macros (compatibility)##sgsc3"].plurals[0] = "Отключить FM-макросы для расширенного канала (совместимость)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc3"].plurals[0] = "Смена инструмента на операторах 2-4 расш. канала меняет FB (совместимость)";
    strings["Clock rate:##sgsc9"].plurals[0] = "Taktowanie zegara:";
    strings["Chip type:##sgsc3"].plurals[0] = "Typ ukłądu:";
    strings["RF5C68 (10-bit output)##sgsc"].plurals[0] = "RF5C68 (10-bitowe audio)";
    strings["RF5C164 (16-bit output)##sgsc"].plurals[0] = "RF5C164 (16-bitowe audio)";
    strings["Clock rate:##sgsc10"].plurals[0] = "Taktowanie zegara:";
    strings["Sample rate table:##sgsc"].plurals[0] = "Таблица частот квантования:";
    strings["divider \\ clock##sgsc"].plurals[0] = "Делитель тактовой частоты";
    strings["full##sgsc"].plurals[0] = "полная";
    strings["half##sgsc"].plurals[0] = "половина";
    strings["Clock rate:##sgsc11"].plurals[0] = "Taktowanie zegara:";
    strings["Output rate:##sgsc2"].plurals[0] = "Частота квантования на выходе:";
    strings["clock / 132##sgsc"].plurals[0] = "takt. zegara / 132";
    strings["clock / 165##sgsc"].plurals[0] = "takt. zegara / 165";
    strings["Bankswitched (NMK112)##sgsc"].plurals[0] = "Ze zmieniarką banków (NMK112)";
    strings["Clock rate:##sgsc12"].plurals[0] = "Taktowanie zegara:";
    strings["1.5MHz (Arcade)##sgsc"].plurals[0] = "1.5 MHz (Arcade)";
    strings["Clock rate:##sgsc13"].plurals[0] = "Taktowanie zegara:";
    strings["Clock rate:##sgsc14"].plurals[0] = "Taktowanie zegara:";
    strings["Chip type:##sgsc4"].plurals[0] = "Typ układu:";
    strings["Compatible panning (0800)##sgsc"].plurals[0] = "Совместимое панорамирование (0800)";
    strings["Clock rate:##sgsc15"].plurals[0] = "Taktowanie zegara:";
    strings["Output rate:##sgsc3"].plurals[0] = "Частота квантования на выходе:";
    strings["Output bit depth:##sgsc"].plurals[0] = "Глубина квантования на выходе:";
    strings["Stereo##sgsc2"].plurals[0] = "Stereo";
    strings["Interpolation:##sgsc"].plurals[0] = "Interpolacja:";
    strings["None##sgsc"].plurals[0] = "Wył.";
    strings["Linear##sgsc"].plurals[0] = "Liniowa";
    strings["Cubic##sgsc"].plurals[0] = "Sześcienna";
    strings["Sinc##sgsc"].plurals[0] = "Sinc";
    strings["Volume scale:##sgsc1"].plurals[0] = "Масштабирование громкости:";
    strings["Left##VolScaleL"].plurals[0] = "Слева##VolScaleL";
    strings["Right##VolScaleL"].plurals[0] = "Справа##VolScaleL";
    strings["Enable echo##sgsc1"].plurals[0] = "Włącz echo";
    strings["Initial echo state:##sgsc"].plurals[0] = "Początkowy stan echo:";
    strings["Delay##EchoDelay"].plurals[0] = "Задержка##EchoDelay";
    strings["Feedback##EchoFeedback"].plurals[0] = "Обр. связь##EchoFeedback";
    strings["Echo volume:##sgsc1"].plurals[0] = "Głośność echo:";
    strings["Left##EchoVolL"].plurals[0] = "Слева##EchoVolL";
    strings["Right##EchoVolL"].plurals[0] = "Справа##EchoVolL";
    strings["Echo filter:##sgsc"].plurals[0] = "Filtr echo:";
    strings["Hex##SNESFHex"].plurals[0] = "Шест.##SNESFHex";
    strings["Dec##SNESFHex"].plurals[0] = "Дес.##SNESFHex";
    strings["sum: %d##sgsc"].plurals[0] = "suma: %d";
    strings["Detune##sgsc"].plurals[0] = "Rozstrojenie";
    strings["Capacitor values (nF):##sgsc"].plurals[0] = "Ёмкость конденсаторов (нФ):";
    strings["Initial part volume (channel 1-4):##sgsc"].plurals[0] = "Начальная громкость (каналы 1-4):";
    strings["Initial part volume (channel 5-8):##sgsc"].plurals[0] = "Начальная громкость (каналы 5-8):";
    strings["Envelope mode (channel 1-4):##sgsc"].plurals[0] = "Режим огибающей (каналы 1-4):";
    strings["Capacitor (attack/decay)##EM00"].plurals[0] = "Конденсатор (атака/спад)##EM00";
    strings["External (volume macro)##EM01"].plurals[0] = "Внешняя (макрос громкости)##EM01";
    strings["Envelope mode (channel 5-8):##sgsc"].plurals[0] = "Режим огибающей (каналы 5-8):";
    strings["Capacitor (attack/decay)##EM10"].plurals[0] = "Конденсатор (атака/спад)##EM10";
    strings["External (volume macro)##EM11"].plurals[0] = "Внешняя (макрос громкости)##EM11";
    strings["Global vibrato:##sgsc"].plurals[0] = "Глобальное вибрато:";
    strings["Speed##sgsc"].plurals[0] = "Prędkość";
    strings["Depth##sgsc"].plurals[0] = "Głębokość";
    strings["Disable easy period to note mapping on upper octaves##sgsc1"].plurals[0] = "Отключить простое преобразование периода в ноту на верхних октавах";
    strings["Stereo##sgsc3"].plurals[0] = "Stereo";
    strings["Waveform storage mode:##sgsc0"].plurals[0] = "Sposób przechowywania fal:";
    strings["RAM##sgsc"].plurals[0] = "RAM";
    strings["ROM (up to 8 waves)##sgsc"].plurals[0] = "RAM (maks. 8 fal)";
    strings["Compatible noise frequencies##sgsc"].plurals[0] = "Kompatybilne częstotliwości szumu";
    strings["Legacy slides and pitch (compatibility)##sgsc"].plurals[0] = "Старые частоты и портаменто (совместимость)";
    strings["Clock rate:##sgsc16"].plurals[0] = "Taktowanie zegara:";
    strings["Clock rate:##sgsc17"].plurals[0] = "Taktowanie zegara:";
    strings["Global parameter priority:##sgsc1"].plurals[0] = "Приоритет глобальных параметров:";
    strings["Left to right##sgsc1"].plurals[0] = "Od lewej do prawej";
    strings["Last used channel##sgsc1"].plurals[0] = "Последний использованный канал";
    strings["Banking style:##sgsc"].plurals[0] = "Sposób przełączania banków:";
    strings["Raw (16MB; no VGM export!)##sgsc"].plurals[0] = "Surowy (16 MB; brak możliwości eksportu do VGM!)";
    strings["Waveform storage mode:##sgsc1"].plurals[0] = "Tryb przechowywania fal:";
    strings["Dynamic (unconfirmed)##sgsc"].plurals[0] = "Dynamiczny (niezweryfikowany)";
    strings["Static (up to 5 waves)##sgsc"].plurals[0] = "Statyczny (maks. 5 fal)";
    strings["nothing to configure##sgsc"].plurals[0] = "nic do skonfigurowania";
    strings["Downmix chip output to mono##sgsc"].plurals[0] = "Miksuj dźwięk układu do mono";
    strings["Reserved blocks for wavetables:##sgsc"].plurals[0] = "Zarezerwowane bloki dla tablic fal:";
    strings["Reserve this many blocks 256 bytes each in sample memory.\nEach block holds one wavetable (is used for one wavetable channel),\nso reserve as many as you need.##sgsc"].plurals[0] = "Zarezerwuj tyle bloków, każdy po 256 bajtów, w pamięci na sample.\nW każdym bloku znajduje się jedna tablica fal (jest ona używana dla jednego kanału w trybie tablic fal),\nwięc zarezerwuj ich tyle, ile potrzebujesz.";
    strings["Custom clock rate##sgsc"].plurals[0] = "Niestandardowe taktowanie zegara";
    strings["1MB##sgsc"].plurals[0] = "1 MB";
    strings["256KB##sgsc"].plurals[0] = "256 kB";
    strings["Namco System 2 (2MB)##sgsc"].plurals[0] = "Namco System 2 (2 MB)";
    strings["Namco System 21 (4MB)##sgsc"].plurals[0] = "Namco System 21 (4 MB)";

    //   sgsm  src/gui/sysManager.cpp

    strings["Chip Manager###Chip Manager"].plurals[0] = "Menedżer układó###Chip Manager";
    strings["Preserve channel order##sgsm"].plurals[0] = "Сохранить порядок каналов";
    strings["Name##sgsm"].plurals[0] = "Nazwa";
    strings["Actions##sgsm"].plurals[0] = "Działania";
    strings["(drag to swap chips)##sgsm"].plurals[0] = "(перетащите, чтобы поменять местами каналы)";
    strings["Change##SysChange"].plurals[0] = "Zmień##SysChange";
    strings["Are you sure you want to remove this chip?##sgsm"].plurals[0] = "Вы действительно хотите удалить этот чип?";
    strings["Remove##sgsm"].plurals[0] = "Usuń";
    strings["cannot add chip! (##sgsm"].plurals[0] = "nie da się dodać układu! (";

    //   sgsa  src/gui/sysPartNumber.cpp

    strings["ZXS Beeper##sgsa"].plurals[0] = "ZXS (brzęczyk)";

    //   sgsp  src/gui/sysPicker.cpp

    strings["Search...##sgsp"].plurals[0] = "Szukaj...";

    // # sgvm  src/gui/volMeter.cpp

    strings["Volume Meter###Volume Meter"].plurals[0] = "Измеритель громкости###Volume Meter";

    //   sgwe  src/gui/waveEdit.cpp

    strings["Sine##sgwe0"].plurals[0] = "Синус";
    strings["Triangle##sgwe0"].plurals[0] = "Треуг. волна";
    strings["Saw##sgwe0"].plurals[0] = "Пила";
    strings["Pulse##sgwe"].plurals[0] = "Меандр";

    strings["None##sgwe"].plurals[0] = "Нет";
    strings["Linear##sgwe"].plurals[0] = "Линейная";
    strings["Cosine##sgwe"].plurals[0] = "Косинусоидная";
    strings["Cubic##sgwe"].plurals[0] = "Кубическая";

    strings["Sine##sgwe1"].plurals[0] = "Синус";
    strings["Rect. Sine##sgwe"].plurals[0] = "Выпрямл. синус";
    strings["Abs. Sine##sgwe"].plurals[0] = "Модуль синуса";
    strings["Quart. Sine##sgwe"].plurals[0] = "Четвертинки синуса";
    strings["Squish. Sine##sgwe"].plurals[0] = "Сжатый синус";
    strings["Abs. Squish. Sine##sgwe"].plurals[0] = "Модуль сж. синуса";
    strings["Square##sgwe"].plurals[0] = "Меандр";
    strings["rectSquare##sgwe"].plurals[0] = "Выпрямл. меандр";
    strings["Saw##sgwe1"].plurals[0] = "Пила";
    strings["Rect. Saw##sgwe"].plurals[0] = "Выпрямл. пила";
    strings["Abs. Saw##sgwe"].plurals[0] = "Модуль пилы";
    strings["Cubed Saw##sgwe"].plurals[0] = "Пила в кубе";
    strings["Rect. Cubed Saw##sgwe"].plurals[0] = "Выпрямл. пила в кубе";
    strings["Abs. Cubed Saw##sgwe"].plurals[0] = "Модуль пилы в кубе";
    strings["Cubed Sine##sgwe"].plurals[0] = "Куб синуса";
    strings["Rect. Cubed Sine##sgwe"].plurals[0] = "Выпрямл. куб синуса";
    strings["Abs. Cubed Sine##sgwe"].plurals[0] = "Модуль куба синуса";
    strings["Quart. Cubed Sine##sgwe"].plurals[0] = "Четвертинки куба синуса";
    strings["Squish. Cubed Sine##sgwe"].plurals[0] = "Сжатый куб синуса";
    strings["Squish. Abs. Cub. Sine##sgwe"].plurals[0] = "Модуль сж. куба синуса";
    strings["Triangle##sgwe1"].plurals[0] = "Треуг. волна";
    strings["Rect. Triangle##sgwe"].plurals[0] = "Выпрямл. треуг. волна";
    strings["Abs. Triangle##sgwe"].plurals[0] = "Модуль треуг. волны";
    strings["Quart. Triangle##sgwe"].plurals[0] = "Четвертинки треуг. волны";
    strings["Squish. Triangle##sgwe"].plurals[0] = "Сжатая треуг. волна";
    strings["Abs. Squish. Triangle##sgwe"].plurals[0] = "Модуль сж. треуг. волны";
    strings["Cubed Triangle##sgwe"].plurals[0] = "Куб треуг. волны";
    strings["Rect. Cubed Triangle##sgwe"].plurals[0] = "Выпрямл. куб треуг. волны";
    strings["Abs. Cubed Triangle##sgwe"].plurals[0] = "Модуль куба треуг. волны";
    strings["Quart. Cubed Triangle##sgwe"].plurals[0] = "Четвертинки куба треуг. волны";
    strings["Squish. Cubed Triangle##sgwe"].plurals[0] = "Сжатый куб треуг. волны";
    strings["Squish. Abs. Cub. Triangle##sgwe"].plurals[0] = "Сжатый модуль куба треуг. волны";

    strings["Wavetable Editor###Wavetable Editor"].plurals[0] = "Редактор волновых таблиц###Wavetable Editor";
    strings["no wavetable selected##sgwe0"].plurals[0] = "не выбрано ни одной волновой таблицы";
    strings["no wavetable selected##sgwe1"].plurals[0] = "не выбрано ни одной волновой таблицы";
    strings["select one...##sgwe"].plurals[0] = "выберите волновую таблицу...";
    strings["or##sgwe0"].plurals[0] = "albo";
    strings["Open##sgwe0"].plurals[0] = "Откройте";
    strings["or##sgwe1"].plurals[0] = "или";
    strings["Create New##sgwe"].plurals[0] = "Создайте новую";
    strings["Open##sgwe1"].plurals[0] = "Otwórz";
    strings["Save##sgwe"].plurals[0] = "Сохранить";
    strings["export .dmw...##sgwe"].plurals[0] = "экспорт .dmw...";
    strings["export raw...##sgwe"].plurals[0] = "экспорт сырых данных...";
    strings["Steps##sgwe"].plurals[0] = "Kroki";
    strings["Lines##sgwe"].plurals[0] = "Linie";
    strings["Width##sgwe"].plurals[0] = "Szerokość";
    strings["use a width of:\n- any on Amiga/N163\n- 32 on Game Boy, PC Engine, SCC, Konami Bubble System, Namco WSG, Virtual Boy and WonderSwan\n- 64 on FDS\n- 128 on X1-010\n- 256 for ES5503\nany other widths will be scaled during playback.##sgwe"].plurals[0] = "используйте следующие длины:\n- любую для Amiga/N163\n- 32 для Game Boy, PC Engine, SCC, Konami Bubble System, Namco WSG, Virtual Boy и WonderSwan\n- 64 для FDS\n- 128 для X1-010\n- 256 для ES5503\nлюбые другие длины будут отмасштабированы во время воспроизведения.";
    strings["Height##sgwe"].plurals[0] = "Wysokość";
    strings["use a height of:\n- 16 for Game Boy, WonderSwan, Namco WSG, Konami Bubble System, X1-010 Envelope shape and N163\n- 32 for PC Engine\n- 64 for FDS and Virtual Boy\n- 256 for X1-010, SCC and ES5503\nany other heights will be scaled during playback.##sgwe"].plurals[0] = "используйте следующие высоты:\n- 16 для Game Boy, WonderSwan, Namco WSG, Konami Bubble System, формы огибающей X1-010 и N163\n- 32 для PC Engine\n- 64 для FDS и Virtual Boy\n- 256 для X1-010, SCC и ES5503\nлюбые другие высоты будут отмасштабированы во время воспроизведения.";
    strings["Shapes##sgwe"].plurals[0] = "Kształty fal";
    strings["Duty##sgwe"].plurals[0] = "Скважность";
    strings["Exponent##sgwe"].plurals[0] = "Пок. степени";
    strings["XOR Point##sgwe"].plurals[0] = "Точка XOR";
    strings["Amplitude/Phase##sgwe"].plurals[0] = "Амплитуда/фаза";
    strings["Op##sgwe0"].plurals[0] = "Op";
    strings["Level##sgwe"].plurals[0] = "Głośność";
    strings["Mult##sgwe"].plurals[0] = "Mnoznik";
    strings["FB##sgwe"].plurals[0] = "Обр. св.";
    strings["Op##sgwe1"].plurals[0] = "Опер.";
    strings["Waveform##sgwe"].plurals[0] = "Волна";
    strings["Connection Diagram##sgwe0"].plurals[0] = "Матрица модуляции";
    strings["Connection Diagram##sgwe1"].plurals[0] = "Матрица модуляции";
    strings["Out##sgwe"].plurals[0] = "Вывод";
    strings["WaveTools##sgwe"].plurals[0] = "Инструменты";
    strings["Scale X##sgwe"].plurals[0] = "Масштаб X";
    strings["wavetable longer than 256 samples!##sgwe"].plurals[0] = "волновая таблица длинее 256 шагов!";
    strings["Scale Y##sgwe"].plurals[0] = "Масштаб Y";
    strings["Offset X##sgwe"].plurals[0] = "Сдвиг X";
    strings["Offset Y##sgwe"].plurals[0] = "Сдвиг Y";
    strings["Smooth##sgwe"].plurals[0] = "Сгладить";
    strings["Amplify##sgwe"].plurals[0] = "Усилить";
    strings["Normalize##sgwe"].plurals[0] = "Нормализовать";
    strings["Invert##sgwe"].plurals[0] = "Инвертировать";
    strings["Reverse##sgwe"].plurals[0] = "Реверс";
    strings["Half##sgwe"].plurals[0] = "Сократить 2х";
    strings["Double##sgwe"].plurals[0] = "Растянуть 2х";
    strings["Convert Signed/Unsigned##sgwe"].plurals[0] = "Конверт. знаковая <-> беззнаковая";
    strings["Randomize##sgwe"].plurals[0] = "Заполнить случ. знач.";
    strings["Dec##sgwe"].plurals[0] = "Dec.";
    strings["Hex##sgwe"].plurals[0] = "Hex.";
    strings["Signed/Unsigned##sgwe"].plurals[0] = "Знаковая <-> беззнаковая";

    //   sgxy  src/gui/xyOsc.cpp

    strings["Oscilloscope (X-Y)###Oscilloscope (X-Y)"].plurals[0] = "Oscyloskop (X-Y)###Oscilloscope (X-Y)";
    strings["X Channel##sgxy"].plurals[0] = "Kanał osi X";
    strings["Invert##X"].plurals[0] = "Odwróć";
    strings["Y Channel##sgxy"].plurals[0] = "Kanał osi Y";
    strings["Invert##Y"].plurals[0] = "Odwróć";
    strings["Zoom##sgxy"].plurals[0] = "Przybliż";
    strings["Samples##sgxy"].plurals[0] = "Sample";
    strings["Decay Time (ms)##sgxy"].plurals[0] = "Czas opadania (ms)";
    strings["Intensity##sgxy"].plurals[0] = "Natężenie";
    strings["Line Thickness##sgxy"].plurals[0] = "Grubość linii";
    strings["OK##sgxy"].plurals[0] = "OK";
    strings["(-Infinity)dB,(-Infinity)dB##sgxy"].plurals[0] = "(-Nieskończoność) dB,(-Nieskończoność) dB";
    strings["(-Infinity)dB,%.1fdB##sgxy"].plurals[0] = "(-Nieskończoność) dB,%.1f db";
    strings["%.1fdB,(-Infinity)dB##sgxy"].plurals[0] = "%.1f dB,(-Nieskończoność) dB";

    //WINDOW NAMES

    strings["Orders###Orders"].plurals[0] = "Matryca wzorców###Orders";
    strings["About Furnace###About Furnace"].plurals[0] = "O Furnace###About Furnace";
    strings["Channels###Channels"].plurals[0] = "Kanały###Channels";
    strings["Oscilloscope (per-channel)###Oscilloscope (per-channel)"].plurals[0] = "Oscyloskop (na poscz. kanał)###Oscilloscope (per-channel)";
    strings["Instruments###Instruments"].plurals[0] = "Instrumnety###Instruments";
    strings["Wavetables###Wavetables"].plurals[0] = "Tablice fal###Wavetables";
    strings["Debug###Debug"].plurals[0] = "Menu Debugowania###Debug";
    strings["Samples###Samples"].plurals[0] = "Sample###Samples";
    strings["MobileEdit###MobileEdit"].plurals[0] = "Mobilne menu edycji###MobileEdit";
    strings["Log Viewer###Log Viewer"].plurals[0] = "Podgląd logów###Log Viewer";
    strings["Mixer###Mixer"].plurals[0] = "Mikser###Mixer";
    strings["OrderSel###OrderSel"].plurals[0] = "Wybór matr. wzorców###OrderSel";
    strings["Spoiler###Spoiler"].plurals[0] = "Spoiler###Spoiler";
    //popups
    strings["Warning###Warning"].plurals[0] = "Uwaga###Warning";
    strings["Error###Error"].plurals[0] = "Błąd###Error";
    strings["Select Instrument###Select Instrument"].plurals[0] = "Wybierz Instrument###Select Instrument";
    strings["Import Raw Sample###Import Raw Sample"].plurals[0] = "Importuj surowy sampel###Import Raw Sample";
    strings["Rendering...###Rendering..."].plurals[0] = "Renderowanie...###Rendering...";
    
    //MACRO EDITOR

    //macro hover notes

    strings["exponential##sgmu"].plurals[0] = "wykładnicze";
    strings["linear##sgmu"].plurals[0] = "liniowe";
    strings["direct##sgmu"].plurals[0] = "bezpośrednie";

    strings["Release"].plurals[0] = "Релиз";
    strings["Loop"].plurals[0] = "Цикл";

    strings["HP/K2, HP/K2##sgmu"].plurals[0] = "HP/K2, HP/K2";
    strings["HP/K2, LP/K1##sgmu"].plurals[0] = "HP/K2, LP/K1";
    strings["LP/K2, LP/K2##sgmu"].plurals[0] = "LP/K2, LP/K2";
    strings["LP/K2, LP/K1##sgmu"].plurals[0] = "LP/K2, LP/K1";

    strings["Saw##sgmu"].plurals[0] = "Пила";
    strings["Square##sgmu"].plurals[0] = "Меандр";
    strings["Triangle##sgmu"].plurals[0] = "Треугольная волна";
    strings["Random##sgmu"].plurals[0] = "Шум";

    //src/gui/settings.cpp


    strings["<Use system font>##sgse0"].plurals[0] = "<Использовать системный шрифт>";
    strings["<Custom...>##sgse0"].plurals[0] = "<Внешний...>";
    strings["<Use system font>##sgse1"].plurals[0] = "<Использовать системный шрифт>";
    strings["<Custom...>##sgse1"].plurals[0] = "<Внешний...>";
    strings["<Use system font>##sgse2"].plurals[0] = "<Использовать системный шрифт>";
    strings["<Custom...>##sgse2"].plurals[0] = "<Внешний...>";
    strings["Mono##sgse0"].plurals[0] = "Моно";
    strings["Stereo##sgse"].plurals[0] = "Stereo";
    strings["What?##sgse0"].plurals[0] = "Co?";
    strings["Quadraphonic##sgse"].plurals[0] = "Евадрафонический";
    strings["What?##sgse1"].plurals[0] = "Co?";
    strings["5.1 Surround##sgse"].plurals[0] = "5.1 объёмный звук";
    strings["What?##sgse2"].plurals[0] = "Co?";
    strings["7.1 Surround##sgse"].plurals[0] = "7.1 объёмный звук";
    strings["High##sgse"].plurals[0] = "Высокое";
    strings["Low##sgse"].plurals[0] = "Низкое";
    strings["ASAP (C++ port)##sgse"].plurals[0] = "ASAP (портирован на C++)";
    strings["KIOCSOUND on /dev/tty1##sgse"].plurals[0] = "KIOCSOUND na /dev/tty1";
    strings["KIOCSOUND on standard output##sgse"].plurals[0] = "KIOCSOUND в стандартном выводе";
    strings["Disabled/custom##sgse0"].plurals[0] = "Выкл./пользовательский";
    strings["Two octaves (0 is C-4, F is D#5)##sgse"].plurals[0] = "Две октавы (0 = C-4, F = D#5)";
    strings["Raw (note number is value)##sgse"].plurals[0] = "Сырой ввод (номер ноты - само значение)";
    strings["Two octaves alternate (lower keys are 0-9, upper keys are A-F)##sgse"].plurals[0] = "Альтернативный ввод двух октав (нижние клавиши 0-9, верхние - A-F)";
    strings["Use dual control change (one for each nibble)##sgse0"].plurals[0] = "Использовать двойную смену значения контроллера (по одному на тетраду)";
    strings["Use 14-bit control change##sgse0"].plurals[0] = "Использовать 14-битную смену значения контроллера";
    strings["Use single control change (imprecise)##sgse0"].plurals[0] = "Использовать однократную смену значения контроллера (малая точность)";
    strings["Disabled/custom##sgse1"].plurals[0] = "Выкл./пользовательский";
    strings["Use dual control change (one for each nibble)##sgse1"].plurals[0] = "Использовать двойную смену значения контроллера (по одному на тетраду)";
    strings["Use 14-bit control change##sgse1"].plurals[0] = "Использовать 14-битную смену значения контроллера";
    strings["Use single control change (imprecise)##sgse1"].plurals[0] = "Использовать однократную смену значения контроллера (малая точность)";
    strings["--select--##sgse"].plurals[0] = "--wybierz--";
    strings["Note Off##sgse"].plurals[0] = "Отпускание клавиши";
    strings["Note On##sgse"].plurals[0] = "Нажатие клавиши";
    strings["Aftertouch##sgse"].plurals[0] = "Давление на клавишу после нажатия";
    strings["Control##sgse"].plurals[0] = "Значение контроллера";
    strings["Program##sgse0"].plurals[0] = "Программа";
    strings["ChanPressure##sgse"].plurals[0] = "Одинаковое давление на все нажатые клавиши в одном канале";
    strings["Pitch Bend##sgse"].plurals[0] = "Смена высоты тона";
    strings["SysEx##sgse"].plurals[0] = "SysEx";
    strings["Instrument##sgse0"].plurals[0] = "Instrument";
    strings["Volume##sgse0"].plurals[0] = "Głośność";
    strings["Effect 1 type##sgse"].plurals[0] = "Индекс эффекта №1";
    strings["Effect 1 value##sgse"].plurals[0] = "Параметр эффекта №1";
    strings["Effect 2 type##sgse"].plurals[0] = "Индекс эффекта №2";
    strings["Effect 2 value##sgse"].plurals[0] = "Параметр эффекта №2";
    strings["Effect 3 type##sgse"].plurals[0] = "Индекс эффекта №3";
    strings["Effect 3 value##sgse"].plurals[0] = "Параметр эффекта №3";
    strings["Effect 4 type##sgse"].plurals[0] = "Индекс эффекта №4";
    strings["Effect 4 value##sgse"].plurals[0] = "Параметр эффекта №4";
    strings["Effect 5 type##sgse"].plurals[0] = "Индекс эффекта №5";
    strings["Effect 5 value##sgse"].plurals[0] = "Параметр эффекта №5";
    strings["Effect 6 type##sgse"].plurals[0] = "Индекс эффекта №6";
    strings["Effect 6 value##sgse"].plurals[0] = "Параметр эффекта №6";
    strings["Effect 7 type##sgse"].plurals[0] = "Индекс эффекта №7";
    strings["Effect 7 value##sgse"].plurals[0] = "Параметр эффекта №7";
    strings["Effect 8 type##sgse"].plurals[0] = "Индекс эффекта №8";
    strings["Effect 8 value##sgse"].plurals[0] = "Параметр эффекта №8";

    strings["Press key...##sgse"].plurals[0] = "Naciśnij klawisz...";
    strings["Settings###Settings"].plurals[0] = "Ustawienia###Settings";
    strings["Do you want to save your settings?##sgse"].plurals[0] = "Czyt chcesz zapisać swoje ustawienia?";

    strings["General##sgse"].plurals[0] = "Основные";
    strings["Program##sgse1"].plurals[0] = "Программа";
    strings["Render backend##sgse"].plurals[0] = "Библиотека отрисовки";
    strings["you may need to restart Furnace for this setting to take effect.##sgse0"].plurals[0] = "возможно, вам потребуется перезапустить Furnace, чтобы эта настрока применилась.";
    strings["Render driver##sgse"].plurals[0] = "Драйвер отрисовки";
    strings["Automatic##sgse0"].plurals[0] = "Выбирать автоматически";
    strings["Automatic##sgse1"].plurals[0] = "Выбирать автоматически";
    strings["you may need to restart Furnace for this setting to take effect.##sgse1"].plurals[0] = "возможно, вам потребуется перезапустить Furnace, чтобы эта настрока применилась.";
    strings["Late render clear##sgse"].plurals[0] = "Запаздывающая очистка буфера отрисовщика";
    strings["calls rend->clear() after rend->present(). might reduce UI latency by one frame in some drivers.##sgse"].plurals[0] = "вызывает rend->clear() после rend->present(). может устранить запаздывание отрисовки интерфейса на один кадр для некоторых драйверов.";
    strings["Power-saving mode##sgse"].plurals[0] = "Режим энергосбережения";
    strings["saves power by lowering the frame rate to 2fps when idle.\nmay cause issues under Mesa drivers!##sgse"].plurals[0] = "уменьшает энергопотребление при помощи уменьшения частоты отрисовки до двух кадров в секунду в режиме ожидания.\nможет приводить к проблемам на драйверах Mesa!";
    strings["Disable threaded input (restart after changing!)##sgse"].plurals[0] = "Отключить обработку нажатий для превью инструмента в отдельном потоке (перезагрузите программу после изменения!)";
    strings["threaded input processes key presses for note preview on a separate thread (on supported platforms), which reduces latency.\nhowever, crashes have been reported when threaded input is on. enable this option if that is the case.##sgse"].plurals[0] = "обработка нажатий клавиш для превью инструмента происходит в отдельном потоке (на поддерживаемых платформах), что позволяет уменьшить задержку ввода.\nтем не менее, есть сообщения о вылетах программы при выключённой настройке. включите её, если у вас программа вылетает.";
    strings["Enable event delay##sgse"].plurals[0] = "Включить задержку событий";
    strings["may cause issues with high-polling-rate mice when previewing notes.##sgse"].plurals[0] = "может привести к проблемам во время превью инструмента, если подключена мышь с большой частотой обновления.";
    strings["Per-channel oscilloscope threads##sgse"].plurals[0] = "Потоки исполнения осциллографов для отдельных каналов";
    strings["you're being silly, aren't you? that's enough.##sgse"].plurals[0] = "может, хватит уже хернёй страдать? этого достаточно.";
    strings["what are you doing? stop!##sgse"].plurals[0] = "ты чё делаешь? хватит!";
    strings["it is a bad idea to set this number higher than your CPU core count (%d)!##sgse"].plurals[0] = "не рекомендуется выставлять здесь значение, большее количества ядер вашего ЦП (%d)!";
    strings["File##sgse"].plurals[0] = "Plik";
    strings["Use system file picker##sgse"].plurals[0] = "Использовать диалоговое окно выбора файлов ОС";
    strings["Number of recent files##sgse"].plurals[0] = "Количество недавних файлов";
    strings["Compress when saving##sgse"].plurals[0] = "Сжимать сохраняемые файлы";
    strings["use zlib to compress saved songs.##sgse"].plurals[0] = "использовать библиотеку zlib для сжатия сохраняемых модулей.";
    strings["Save unused patterns##sgse"].plurals[0] = "Сохранять неиспользуемые паттерны";
    strings["Use new pattern format when saving##sgse"].plurals[0] = "Использовать новый формат сохранения паттернов";
    strings["use a packed format which saves space when saving songs.\ndisable if you need compatibility with older Furnace and/or tools\nwhich do not support this format.##sgse"].plurals[0] = "использовать сжатый формат сохранения паттернов, что позволяет уменьшить размер файла с модулем.\nотключите, если нужна совместимость со старыми версиями Furnace и/или другими программами,\nкоторые не поддерживают новый формат.";
    strings["Don't apply compatibility flags when loading .dmf##sgse"].plurals[0] = "Не применять флаги совместимости при загрузке .dmf";
    strings["do not report any issues arising from the use of this option!##sgse"].plurals[0] = "не жалуйтесь на проблемы, которые возникнут после включения этой настройки!";
    strings["Play after opening song:##sgse"].plurals[0] = "Проигрывание модуля после его загрузки:";
    strings["No##pol0"].plurals[0] = "Nie##pol0";
    strings["Only if already playing##pol1"].plurals[0] = "Только если до этого уже играл##pol1";
    strings["Yes##pol0"].plurals[0] = "Tak##pol0";
    strings["Audio export loop/fade out time:##sgse"].plurals[0] = "Количество циклов проигрывания и время затухания при экспорте аудио:";
    strings["Set to these values on start-up:##fot0"].plurals[0] = "Выставить эти значения при запуске:##fot0";
    strings["Loops##sgse"].plurals[0] = "Циклы";
    strings["Fade out (seconds)##sgse"].plurals[0] = "Затухание (в секундах)";
    strings["Remember last values##fot1"].plurals[0] = "Запоминать предыдущие значения##fot1";
    strings["Store instrument name in .fui##sgse"].plurals[0] = "Сохранять название инструмента в файле .fui";
    strings["when enabled, saving an instrument will store its name.\nthis may increase file size.##sgse"].plurals[0] = "При включении имя инструмента будет сохраняться в файле.\nэто может увеличить размер файла.";
    strings["Load instrument name from .fui##sgse"].plurals[0] = "Загружать имя инструмента из файла .fui";
    strings["when enabled, loading an instrument will use the stored name (if present).\notherwise, it will use the file name.##sgse"].plurals[0] = "При включении имя инструмента будет загружаться из файла (при наличии имени в файле).\nВ противном случае будет использоваться имя файла.";
    strings["New Song##sgse"].plurals[0] = "Новая композиция";
    strings["Initial system:##sgse"].plurals[0] = "Система по умолчанию:";
    strings["Current system##sgse"].plurals[0] = "Текущая";
    strings["Randomize##sgse"].plurals[0] = "Выбрать случайно";
    strings["Reset to defaults##sgse"].plurals[0] = "Устан. по умолчанию";
    strings["Name##sgse"].plurals[0] = "Название";
    strings["Invert##sgse0"].plurals[0] = "Обр.";
    strings["Invert##sgse1"].plurals[0] = "Обр.";
    strings["Volume##sgse1"].plurals[0] = "Głośność";
    strings["Panning##sgse"].plurals[0] = "Panning";
    strings["Front/Rear##sgse"].plurals[0] = "Передн./задн.";
    strings["Configure##sgse"].plurals[0] = "Настроить";
    strings["When creating new song:##sgse"].plurals[0] = "При создании новой композиции:";
    strings["Display system preset selector##NSB0"].plurals[0] = "Отобразить окно выбора пресета системы##NSB0";
    strings["Start with initial system##NSB1"].plurals[0] = "Начать с системы по умолчанию##NSB1";
    strings["Default author name##sgse"].plurals[0] = "Имя автора по умолчанию";
    strings["Start-up##sgse"].plurals[0] = "Запуск";
    strings["Disable fade-in during start-up##sgse"].plurals[0] = "Отключить плавное появление интерфейса при запуске";
    strings["About screen party time##sgse"].plurals[0] = "Вечеринка на экране \"О программе\"";
    strings["Warning: may cause epileptic seizures.##sgse"].plurals[0] = "Внимание: может вызвать эпилептические приступы.";
    strings["Behavior##sgse"].plurals[0] = "Поведение программы";
    strings["New instruments are blank##sgse"].plurals[0] = "Пустые новые инструменты";
    strings["Language##sgse"].plurals[0] = "Język";
    strings["GUI language##sgse"].plurals[0] = "Język GUI";
    strings["Audio##sgse"].plurals[0] = "Аудио";
    strings["Output##sgse"].plurals[0] = "Вывод";
    strings["Backend##sgse"].plurals[0] = "Interfejs";
    strings["Driver##sgse"].plurals[0] = "Sterownik";
    strings["Automatic##sgse2"].plurals[0] = "Automatyczny";
    strings["you may need to restart Furnace for this setting to take effect.##sgse2"].plurals[0] = "возможно, вам придётся перезапустить Furnace для применения настройки.";
    strings["Device##sgse"].plurals[0] = "Устройство вывода";
    strings["<click on OK or Apply first>##sgse"].plurals[0] = "<сначала нажмите на кнопки \"OK\" или \"Применить\">";
    strings["ALERT - TRESPASSER DETECTED##sgse"].plurals[0] = "ВНИМАНИЕ - ОБНАРУЖЕН НАРУШИТЕЛЬ";
    strings["you have been arrested for trying to engage with a disabled combo box.##sgse"].plurals[0] = "вы были арестованы за попытку взаимодействия с выключенным выпадающим списком.";
    strings["<System default>##sgse0"].plurals[0] = "<По умолчанию>";
    strings["<System default>##sgse1"].plurals[0] = "<По умолчанию>";
    strings["Sample rate##sgse"].plurals[0] = "Частота дискретизации";
    strings["Outputs##sgse"].plurals[0] = "Wyjścia";
    strings["Channels##sgse"].plurals[0] = "Число каналов";
    strings["What?##sgse3"].plurals[0] = "Co?";
    strings["Buffer size##sgse"].plurals[0] = "Размер буфера";
    strings["%d (latency: ~%.1fms)##sgse"].plurals[0] = "%d (задержка: ~%.1f мс)";
    strings["Multi-threaded (EXPERIMENTAL)##sgse"].plurals[0] = "Wielowątkowość (EKSPERYMENTALNA)";
    strings["runs chip emulation on separate threads.\nmay increase performance when using heavy emulation cores.\n\nwarnings:\n- experimental!\n- only useful on multi-chip songs.##sgse"].plurals[0] = "исполняет эмуляторы чипов в отдельных потоках.\nможет повысить производительность при использовании тяжёлых эмуляторов.\n\nвнимание:\n- экспериментальная функция!\n- полезна только для композиций, использующих несколько чипов.";
    strings["Number of threads##sgse"].plurals[0] = "Ilość wątków";
    strings["that's the limit!##sgse"].plurals[0] = "to już limit!";
    strings["it is a VERY bad idea to set this number higher than your CPU core count (%d)!##sgse"].plurals[0] = "это ОЧЕНЬ плохая идея - устанавливать это значение большим, чем колчество ядер ЦП (%d)!";
    strings["Low-latency mode##sgse"].plurals[0] = "Режим малой задержки";
    strings["reduces latency by running the engine faster than the tick rate.\nuseful for live playback/jam mode.\n\nwarning: only enable if your buffer size is small (10ms or less).##sgse"].plurals[0] = "уменьшает задержку, исполняя код движка трекера быстрее, чем указано в настройках.\nполезно для режима исполнения в реальном времени.\n\nвнимание: включайте только если размер вашего аудиобуфера мал (10 мс или меньше).";
    strings["Force mono audio##sgse"].plurals[0] = "Wymuś dźwięk mono";
    strings["Exclusive mode##sgse"].plurals[0] = "Исключительный режим";
    strings["want: %d samples @ %.0fHz (%d %s)##sgse"].plurals[0] = "potrzeba: %d sampli @ %.0f Hz (%d %s)";
    strings["channel##sgse"].plurals[0] = "канал";
    strings["channel##sgse"].plurals[1] = "канала";
    strings["channel##sgse"].plurals[2] = "каналов";
    strings["got: %d samples @ %.0fHz (%d %s)##sgse"].plurals[0] = "otzrymano: %d sampli @ %.0f Hz (%d %s)";
    strings["Mixing##sgse"].plurals[0] = "Miksing";
    strings["Quality##sgse"].plurals[0] = "Jakość";
    strings["Software clipping##sgse"].plurals[0] = "Программное ограничение сигнала";
    strings["DC offset correction##sgse"].plurals[0] = "Коррекция смещения пост. составляющей";
    strings["Metronome##sgse"].plurals[0] = "Metronom";
    strings["Volume##sgse2"].plurals[0] = "Głośność метронома";
    strings["Sample preview##sgse"].plurals[0] = "Превью сэмпла";
    strings["Volume##sgse3"].plurals[0] = "Głośność";
    strings["MIDI##sgse"].plurals[0] = "MIDI";
    strings["MIDI input##sgse0"].plurals[0] = "Wyjście MIDI";
    strings["MIDI input##sgse1"].plurals[0] = "MIDI вход";
    strings["<disabled>##sgse0"].plurals[0] = "<wył.>";
    strings["<disabled>##sgse1"].plurals[0] = "<wył.>";
    strings["Re-scan MIDI devices##sgse"].plurals[0] = "Перезап. скан. для обнаруж. MIDI-устройств";
    strings["Note input##sgse0"].plurals[0] = "Ввод нот";
    strings["Velocity input##sgse"].plurals[0] = "Ввод скорости нажатия";
    strings["Map MIDI channels to direct channels##sgse"].plurals[0] = "Привязать MIDI-каналы к прямым каналам";
    strings["Program change pass-through##sgse"].plurals[0] = "Пропускать на выход сообщения об изменении программы";
    strings["Map Yamaha FM voice data to instruments##sgse"].plurals[0] = "Привязать данные тембров Yamaha FM к инструментам";
    strings["Program change is instrument selection##sgse"].plurals[0] = "Смена программы = выбор инструмента";
    strings["Listen to MIDI clock##sgse"].plurals[0] = "Следить за тактовой частотой MIDI";
    strings["Listen to MIDI time code##sgse"].plurals[0] = "Следить за временным кодом MIDI";
    strings["Value input style##sgse0"].plurals[0] = "Стиль ввода значений";
    strings["Value input style##sgse1"].plurals[0] = "Стиль ввода значений";
    strings["Control##valueCCS"].plurals[0] = "Управление##valueCCS";
    strings["CC of upper nibble##valueCC1"].plurals[0] = "Управляющая команда для верхней тетрады##valueCC1";
    strings["MSB CC##valueCC1"].plurals[0] = "Управл. ком. для старш. бита##valueCC1";
    strings["CC of lower nibble##valueCC2"].plurals[0] = "Управляющая команда для нижней тетрады##valueCC2";
    strings["LSB CC##valueCC2"].plurals[0] = "Управл. ком. для младш. бита##valueCC2";
    strings["Per-column control change##sgse"].plurals[0] = "Изменение управления для каждого столбца";
    strings["Control##valueCCS"].plurals[0] = "Управление##valueCCS";
    strings["CC of upper nibble##valueCC1"].plurals[0] = "Управляющая команда для верхней тетрады##valueCC1";
    strings["MSB CC##valueCC1"].plurals[0] = "Управл. ком. для старш. бита##valueCC1";
    strings["CC of lower nibble##valueCC2"].plurals[0] = "Управляющая команда для нижней тетрады##valueCC2";
    strings["LSB CC##valueCC2"].plurals[0] = "Управл. ком. для младш. бита##valueCC2";
    strings["Volume curve##sgse0"].plurals[0] = "Кривая громкости";
    strings["Volume curve##sgse1"].plurals[0] = "Кривая громкости";
    strings["Actions:##sgse"].plurals[0] = "Действия:";
    strings["(learning! press a button or move a slider/knob/something on your device.)##sgse"].plurals[0] = "(обучение! нажмите кнопку или подвигайте что-то на вашем устройстве.)";
    strings["Type##sgse0"].plurals[0] = "Typ";
    strings["Channel##sgse0"].plurals[0] = "Kanał";
    strings["Note/Control##sgse"].plurals[0] = "Нота/управление";
    strings["Velocity/Value##sgse"].plurals[0] = "Скор. наж./парам.";
    strings["Action##sgse"].plurals[0] = "Действие";
    strings["Any##sgse0"].plurals[0] = "Любой";
    strings["Any##sgse1"].plurals[0] = "Любая";
    strings["Any##sgse2"].plurals[0] = "Любая";
    strings["Any##sgse3"].plurals[0] = "Любое";
    strings["--none--##sgse"].plurals[0] = "--żaden--";
    strings["waiting...##BLearn"].plurals[0] = "czekaj...##BLearn";
    strings["Learn##BLearn"].plurals[0] = "Запомнить##BLearn";
    strings["MIDI output##sgse0"].plurals[0] = "MIDI вывод";
    strings["MIDI output##sgse1"].plurals[0] = "Устройство вывода MIDI";
    strings["<disabled>##sgse2"].plurals[0] = "<wył.>";
    strings["<disabled>##sgse3"].plurals[0] = "<wył.>";
    strings["Output mode:##sgse"].plurals[0] = "Tryb wyjścia:";
    strings["Off (use for TX81Z)##sgse"].plurals[0] = "Wył. (używać przy TX81Z)";
    strings["Melodic##sgse"].plurals[0] = "Melodyczny";
    //strings["Light Show (use for Launchpad)##sgse"].plurals[0] = "Light Show (use for Launchpad)";
    strings["Send Program Change##sgse"].plurals[0] = "Посылать команду изменения программы";
    strings["Send MIDI clock##sgse"].plurals[0] = "Посылать тактовую частоту MIDI";
    strings["Send MIDI timecode##sgse"].plurals[0] = "Посылать временной код MIDI";
    strings["Timecode frame rate:##sgse"].plurals[0] = "Частота посылок временного кода:";
    strings["Closest to Tick Rate##sgse"].plurals[0] = "Ближайшая к частоте движка трекера";
    strings["Film (24fps)##sgse"].plurals[0] = "Киноплёнка (24 fps)";
    strings["PAL (25fps)##sgse"].plurals[0] = "PAL (25 fps)";
    strings["NTSC drop (29.97fps)##sgse"].plurals[0] = "NTSC с выпадением кадров (29.97 fps";
    strings["NTSC non-drop (30fps)##sgse"].plurals[0] = "NTSC без выпадения кадров (30 fps)";
    strings["Emulation##sgse"].plurals[0] = "Emulacja";
    strings["Cores##sgse"].plurals[0] = "Rdzenie emulacji";
    strings["System##sgse"].plurals[0] = "Systemy";
    strings["Playback Core(s)##sgse"].plurals[0] = "Rdzenie odtwarzania";
    strings["used for playback##sgse"].plurals[0] = "używane do odtwarzania";
    strings["Render Core(s)##sgse"].plurals[0] = "Rdzenie renderowania";
    strings["used in audio export##sgse"].plurals[0] = "używane do eksportowania audio";
    strings["PC Speaker strategy##sgse"].plurals[0] = "Działanie PC Speaker'a";
    strings["Sample ROMs:##sgse"].plurals[0] = "Obrazy ROM sampli:";
    strings["OPL4 YRW801 path##sgse"].plurals[0] = "Sćieżka do OPL4 YRW801";
    strings["MultiPCM TG100 path##sgse"].plurals[0] = "Sćieżka do OPL4 MultiPCM TG100";
    strings["MultiPCM MU5 path##sgse"].plurals[0] = "Sćieżka do OPL4 MultiPCM MU5";
    strings["Keyboard##sgse0"].plurals[0] = "Клавиатура";
    strings["Keyboard##sgse1"].plurals[0] = "Привязка клавиш";
    strings["Import##sgse0"].plurals[0] = "Importij";
    strings["Export##sgse0"].plurals[0] = "Eksportuj";
    strings["Reset defaults##sgse0"].plurals[0] = "Сбросить до настроек по умолчанию";
    strings["Are you sure you want to reset the keyboard settings?##sgse"].plurals[0] = "Вы действительно хотите сбросить настройки привязки клавиш?";
    strings["Global hotkeys##sgse"].plurals[0] = "Глобальные горячие клавиши";
    strings["Window activation##sgse"].plurals[0] = "Активация окон";
    strings["Note input##sgse1"].plurals[0] = "Ввод нот";
    strings["Key##sgse"].plurals[0] = "Клавиша";
    strings["Type##sgse1"].plurals[0] = "Тип";
    strings["Value##sgse"].plurals[0] = "Значение";
    strings["Remove##sgse"].plurals[0] = "Убрать";
    strings["Macro release##SNType_%d"].plurals[0] = "\"Отпускание клавиши\" (только для макросов)##SNType_%d";
    strings["Note release##SNType_%d"].plurals[0] = "\"Отпускание клавиши\" (с включением фазы затухания огибающей)##SNType_%d";
    strings["Note off##SNType_%d"].plurals[0] = "\"Отпускание клавиши\" (резкое)##SNType_%d";
    strings["Note##SNType_%d"].plurals[0] = "Нота##SNType_%d";
    strings["Add...##sgse"].plurals[0] = "Dodaj...";
    strings["Pattern##sgse0"].plurals[0] = "Паттерн";
    strings["Instrument list##sgse"].plurals[0] = "Список инструментов";
    strings["Wavetable list##sgse"].plurals[0] = "Список волновых таблиц";
    strings["Sample list##sgse"].plurals[0] = "Список сэмплов";
    strings["Orders##sgse0"].plurals[0] = "Matryca wzorcow";
    strings["Sample editor##sgse"].plurals[0] = "Редактор сэмплов";
    strings["Interface##sgse0"].plurals[0] = "Интерфейс";
    strings["Layout##sgse"].plurals[0] = "Компоновка интерфейса";
    strings["Workspace layout:##sgse"].plurals[0] = "Расположение окон интерфейса:";
    strings["Import##sgse1"].plurals[0] = "Importuj";
    strings["Export##sgse1"].plurals[0] = "Eksportuj";
    strings["Reset##sgse"].plurals[0] = "Сбросить";
    strings["Are you sure you want to reset the workspace layout?##sgse"].plurals[0] = "Вы действительно хотите сбросить компоновку окон интерфейса?";
    strings["Allow docking editors##sgse"].plurals[0] = "Разрешить стыковать окна редакторов";
    strings["Remember window position##sgse"].plurals[0] = "Запоминать положение окон";
    strings["remembers the window's last position on start-up.##sgse"].plurals[0] = "при запуске программы восстанавливает последнее положение каждого окна.";
    strings["Only allow window movement when clicking on title bar##sgse"].plurals[0] = "Разрешать перемещение окон только при нажатии на их полосу заголовка";
    strings["Center pop-up windows##sgse"].plurals[0] = "Центрировать всплывающие окна";
    strings["Play/edit controls layout:##sgse"].plurals[0] = "Компоновка управления вспроизведением/редактированием:";
    strings["Classic##ecl0"].plurals[0] = "Klasyczny##ecl0";
    strings["Compact##ecl1"].plurals[0] = "Kompatowy##ecl1";
    strings["Compact (vertical)##ecl2"].plurals[0] = "Kompaktowy (pionowy)##ecl2";
    strings["Split##ecl3"].plurals[0] = "Podzielony na dwa okna##ecl3";
    strings["Position of buttons in Orders:##sgse"].plurals[0] = "Pozycja przyciskow w matrycy wzorcow:";
    strings["Top##obp0"].plurals[0] = "Na gorze##obp0";
    strings["Left##obp1"].plurals[0] = "Z lewej##obp1";
    strings["Right##obp2"].plurals[0] = "Z prawej##obp2";
    strings["Mouse##sgse"].plurals[0] = "Mysz";
    strings["Double-click time (seconds)##sgse"].plurals[0] = "Время двойного нажатия (в секундах)";
    strings["Don't raise pattern editor on click##sgse"].plurals[0] = "Не поднимать редактор паттернов при нажатии";
    strings["Focus pattern editor when selecting instrument##sgse"].plurals[0] = "Переместить фокус на редактор паттернов при выборе инструмента";
    strings["Note preview behavior:##sgse"].plurals[0] = "Превью нот:";
    strings["Never##npb0"].plurals[0] = "Nigdy##npb0";
    strings["When cursor is in Note column##npb1"].plurals[0] = "Когда курсор находится в столбце нот##npb1";
    strings["When cursor is in Note column or not in edit mode##npb2"].plurals[0] = "Когда курсор находится в столбце нот или не включён режим редактирования##npb2";
    strings["Always##npb3"].plurals[0] = "Всегда##npb3";
    strings["Allow dragging selection:##sgse"].plurals[0] = "Разрешить перемещение выделенного фрагмента:";
    strings["No##dms0"].plurals[0] = "Nie##dms0";
    strings["Yes##dms1"].plurals[0] = "Tak##dms1";
    strings["Yes (while holding Ctrl only)##dms2"].plurals[0] = "Да (только при нажатой клавише Ctrl)##dms2";
    strings["Toggle channel solo on:##sgse"].plurals[0] = "Включать режим соло для канала:";
    strings["Right-click or double-click##soloA"].plurals[0] = "ПКМ или двойное нажатие##soloA";
    strings["Right-click##soloR"].plurals[0] = "ПКМ##soloR";
    strings["Double-click##soloD"].plurals[0] = "Двойное нажатие##soloD";
    strings["Double click selects entire column##sgse"].plurals[0] = "Двойное нажатие выделяет весь столбец";
    strings["Cursor behavior##sgse"].plurals[0] = "Поведение курсора";
    strings["Insert pushes entire channel row##sgse"].plurals[0] = "Клавиша Insert сдвигает паттерны на всех каналах";
    strings["Pull delete affects entire channel row##sgse"].plurals[0] = "Удаление с подтягиванием следующих строк сдвигает паттерны на всех каналах";
    strings["Push value when overwriting instead of clearing it##sgse"].plurals[0] = "Отодвинуть значение ячейки в соседнюю вместо удаления при перезаписи ячейки";
    strings["Effect input behavior:##sgse"].plurals[0] = "Ввод эффектов:";
    strings["Move down##eicb0"].plurals[0] = "перемещаться вниз##eicb0";
    strings["Move to effect value (otherwise move down)##eicb1"].plurals[0] = "Перепрыгнуть на параметр эффекта (иначе перемещаться вниз)##eicb1";
    strings["Move to effect value/next effect and wrap around##eicb2"].plurals[0] = "Перепрыгнуть на параметр эффекта/следующий эффект, в конце строки перепрыгнуть в начало строки эффектов##eicb2";
    strings["Delete effect value when deleting effect##sgse"].plurals[0] = "Удалять параметр эффекта при удалении эффекта";
    strings["Change current instrument when changing instrument column (absorb)##sgse"].plurals[0] = "Изменять выделенный инструмент при редактировании столбца инструмента";
    strings["Remove instrument value when inserting note off/release##sgse"].plurals[0] = "Удалять значение столбца инструмента при вводе ноты OFF/===";
    strings["Remove volume value when inserting note off/release##sgse"].plurals[0] = "Удалять значение столбца громкости при вводе ноты OFF/===";
    strings["Cursor movement##sgse"].plurals[0] = "Передвижение курсора";
    strings["Wrap horizontally:##sgse"].plurals[0] = "Переносить по горизонтали:";
    strings["No##wrapH0"].plurals[0] = "Нет##wrapH0";
    strings["Yes##wrapH1"].plurals[0] = "Да##wrapH1";
    strings["Yes, and move to next/prev row##wrapH2"].plurals[0] = "Да, и переходить на следующую/предыдущую строку##wrapH2";
    strings["Wrap vertically:##sgse"].plurals[0] = "Переносить по вертикали:";
    strings["No##wrapV0"].plurals[0] = "Nie##wrapV0";
    strings["Yes##wrapV1"].plurals[0] = "Tak##wrapV1";
    strings["Yes, and move to next/prev pattern##wrapV2"].plurals[0] = "Да, и переходить на следующий/предыдущий паттерн##wrapV2";
    strings["Yes, and move to next/prev pattern (wrap around)##wrapV2"].plurals[0] = "Да, и переходить на следующий/предыдущий паттерн (с переносом в начало/конец)##wrapV2";
    strings["Cursor movement keys behavior:##sgse"].plurals[0] = "Передвижение курсора при помощи клавиш:";
    strings["Move by one##cmk0"].plurals[0] = "Сдвигать на одну позицию##cmk0";
    strings["Move by Edit Step##cmk1"].plurals[0] = "Сдвигать на шаг редактирования##cmk1";
    strings["Move cursor by edit step on delete##sgse"].plurals[0] = "Сдвигать курсор на шаг редактирования при удалении";
    strings["Move cursor by edit step on insert (push)##sgse"].plurals[0] = "Сдвигать курсор на шаг редактирования при вставке";
    strings["Move cursor up on backspace-delete##sgse"].plurals[0] = "Сдвигать курсор вверх при удалении по нажатию Backspace";
    strings["Move cursor to end of clipboard content when pasting##sgse"].plurals[0] = "Сдвигать курсор в конец вставленного фрагмента при вставке";
    strings["Scrolling##sgse"].plurals[0] = "Прокрутка";
    strings["Change order when scrolling outside of pattern bounds:##sgse"].plurals[0] = "Менять положение в матрице паттернов при прокрутке за пределы паттернов:";
    strings["No##pscroll0"].plurals[0] = "Nie##pscroll0";
    strings["Yes##pscroll1"].plurals[0] = "Tak##pscroll1";
    strings["Yes, and wrap around song##pscroll2"].plurals[0] = "Да, и переносить в начало/конец трека##pscroll2";
    strings["Cursor follows current order when moving it##sgse"].plurals[0] = "Курсор остаётся на строке матрицы паттернов при перемещении этой строки";
    strings["applies when playback is stopped.##sgse"].plurals[0] = "действительно только при остановленном воспроизведении.";
    strings["Don't scroll when moving cursor##sgse"].plurals[0] = "Не прокручивать при перемещении курсора";
    strings["Move cursor with scroll wheel:##sgse"].plurals[0] = "Перемещать курсор при помощи колёсика мыши:";
    strings["No##csw0"].plurals[0] = "Nie##csw0";
    strings["Yes##csw1"].plurals[0] = "Tak##csw1";
    strings["Inverted##csw2"].plurals[0] = "Да, но в обратном направлении##csw2";
    strings["Assets##sgse0"].plurals[0] = "Zasoby";
    strings["Display instrument type menu when adding instrument##sgse"].plurals[0] = "Отображать тип инструмента при добавлении инструмента";
    strings["Select asset after opening one##sgse"].plurals[0] = "Wybierz obiekt po jego otwarciu";
    strings["Appearance##sgse"].plurals[0] = "Wyglad";
    strings["Scaling##sgse"].plurals[0] = "Skalowanie";
    strings["Automatic UI scaling factor##sgse"].plurals[0] = "Автоматическое масштабирование интерфейса";
    strings["UI scaling factor##sgse"].plurals[0] = "Масштаб интерфейса";
    strings["Icon size##sgse"].plurals[0] = "Rozmiar ikon";
    strings["Text##sgse"].plurals[0] = "Tekst";
    strings["Font renderer##sgse"].plurals[0] = "Отрисовщик шрифта";
    strings["Main font##sgse"].plurals[0] = "Основной шрифт";
    strings["Size##MainFontSize"].plurals[0] = "Rozmiar##MainFontSize";
    strings["Header font##sgse"].plurals[0] = "Шрифт заголовков";
    strings["Size##HeadFontSize"].plurals[0] = "Rozmiar##HeadFontSize";
    strings["Pattern font##sgse"].plurals[0] = "Шрифт паттернов";
    strings["Size##PatFontSize"].plurals[0] = "Rozmiar##PatFontSize";
    strings["Anti-aliased fonts##sgse"].plurals[0] = "Wygladzanie czcionek";
    strings["Support bitmap fonts##sgse"].plurals[0] = "Wspieraj bitmapowe czcionki";
    strings["Hinting:##sgse"].plurals[0] = "Хинтование";
    strings["Off (soft)##fh0"].plurals[0] = "Нет (слабое)##fh0";
    strings["Slight##fh1"].plurals[0] = "Небольшое##fh1";
    strings["Normal##fh2"].plurals[0] = "Normalne##fh2";
    strings["Full (hard)##fh3"].plurals[0] = "Полное (жёсткое)##fh3";
    strings["Auto-hinter:##sgse"].plurals[0] = "Автоматическое хинтирование";
    strings["Disable##fah0"].plurals[0] = "Wyłącz##fah0";
    strings["Enable##fah1"].plurals[0] = "Włącz##fah1";
    strings["Force##fah2"].plurals[0] = "Wymuś##fah2";
    strings["Display Japanese characters##sgse"].plurals[0] = "Wyświetlaj japońskie znaki";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "このオプションは、十分なグラフィックメモリがある場合にのみ切り替えてください。\n"
            "これは、Dear ImGuiにダイナミックフォントアトラスが実装されるまでの一時的な解決策です。##sgse"].plurals[0] = 
            
            "Włącz to ustawienie tylko wtedy, gdy masz wystarczającą ilość VRAM-u.\n"
            "Jest to rozwiązanie tymczasowe, ponieważ Dear ImGui nie obsługuje obecnie dynamicznego atlasu czcionek.\n\n"
            "このオプションは、十分なグラフィックメモリがある場合にのみ切り替えてください。\n"
            "これは、Dear ImGuiにダイナミックフォントアトラスが実装されるまでの一時的な解決策です。";
    strings["Display Chinese (Simplified) characters##sgse"].plurals[0] = "Wyświetlaj chińskie znaki (uproszczone)";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "请在确保你有足够的显存后再启动此设定\n"
            "这是一个在ImGui实现动态字体加载之前的临时解决方案##sgse"].plurals[0] = 
            
            "Włącz to ustawienie tylko wtedy, gdy masz wystarczającą ilość VRAM-u.\n"
            "Jest to rozwiązanie tymczasowe, ponieważ Dear ImGui nie obsługuje obecnie dynamicznego atlasu czcionek.\n\n"
            "请在确保你有足够的显存后再启动此设定\n"
            "这是一个在ImGui实现动态字体加载之前的临时解决方案";
    strings["Display Chinese (Traditional) characters##sgse"].plurals[0] = "Wyświetlaj chińskie znaki (tradycyjne)";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "請在確保你有足夠的顯存后再啟動此設定\n"
            "這是一個在ImGui實現動態字體加載之前的臨時解決方案##sgse"].plurals[0] = 
            
            "Włącz to ustawienie tylko wtedy, gdy masz wystarczającą ilość VRAM-u.\n"
            "Jest to rozwiązanie tymczasowe, ponieważ Dear ImGui nie obsługuje obecnie dynamicznego atlasu czcionek.\n\n"
            "請在確保你有足夠的顯存后再啟動此設定\n"
            "這是一個在ImGui實現動態字體加載之前的臨時解決方案";
    strings["Display Korean characters##sgse"].plurals[0] = "Wyświetlaj koreańskie znaki";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "그래픽 메모리가 충분한 경우에만 이 옵션을 선택하십시오.\n"
            "이 옵션은 Dear ImGui에 동적 글꼴 아틀라스가 구현될 때까지 임시 솔루션입니다.##sgse"].plurals[0] = 
            
            "Włącz to ustawienie tylko wtedy, gdy masz wystarczającą ilość VRAM-u.\n"
            "Jest to rozwiązanie tymczasowe, ponieważ Dear ImGui nie obsługuje obecnie dynamicznego atlasu czcionek.\n\n"
            "그래픽 메모리가 충분한 경우에만 이 옵션을 선택하십시오.\n"
            "이 옵션은 Dear ImGui에 동적 글꼴 아틀라스가 구현될 때까지 임시 솔루션입니다.";

    strings["Program##sgse2"].plurals[0] = "Program";
    strings["Title bar:##sgse"].plurals[0] = "Pasek tytułu okna";
    strings["Furnace-B##tbar0"].plurals[0] = "Furnace-B##tbar0";
    strings["Song Name - Furnace-B##tbar1"].plurals[0] = "Nazwa utworu - Furnace-B##tbar1";
    strings["file_name.fur - Furnace-B##tbar2"].plurals[0] = "nazwa_pliku.fur - Furnace-B##tbar2";
    strings["/path/to/file.fur - Furnace-B##tbar3"].plurals[0] = "/scieżka/do/pliku.fur - Furnace-B##tbar3";
    strings["Display system name on title bar##sgse"].plurals[0] = "Wyświetlaj nazwę układu/systemu na pasku tytułu okna";
    strings["Display chip names instead of \"multi-system\" in title bar##sgse"].plurals[0] = "Отображать названия чипов/систем вместо \"мульти-система\" в полосе заголовка окна";
    strings["Status bar:##sgse"].plurals[0] = "Pasek stanu:";
    strings["Cursor details##sbar0"].plurals[0] = "Информация о выделенном элементе##sbar0";
    strings["File path##sbar1"].plurals[0] = "Sciezka do pliku##sbar1";
    strings["Cursor details or file path##sbar2"].plurals[0] = "Информация о выделенном элементе или путь к файлу##sbar2";
    strings["Nothing##sbar3"].plurals[0] = "Ничего##sbar3";
    strings["Export options layout:##sgse"].plurals[0] = "Вид настроек экспорта:";
    strings["Sub-menus in File menu##eol0"].plurals[0] = "Подпункты в меню \"Файл\"##eol0";
    strings["Modal window with tabs##eol1"].plurals[0] = "Модальное окно с вкладками##eol1";
    strings["Modal windows with options in File menu##eol2"].plurals[0] = "Модальное окно с настройками в меню \"Файл\"";
    strings["Capitalize menu bar##sgse"].plurals[0] = "Названия пунктов в горизонтальном меню с большой буквы";
    strings["Display add/configure/change/remove chip menus in File menu##sgse"].plurals[0] = "Отображать в меню \"Файл\" пункты: добавить/настроить/изменить/убрать чип";
    strings["Orders##sgse1"].plurals[0] = "Matryca wzorcow";
    strings["Highlight channel at cursor in Orders##sgse"].plurals[0] = "Выделить в матрице паттернов канал, на котором находится курсор";
    strings["Orders row number format:##sgse"].plurals[0] = "Формат отображения номера строки матрицы паттернов:";
    strings["Decimal##orbD"].plurals[0] = "Dziesiętny##orbD";
    strings["Hexadecimal##orbH"].plurals[0] = "Szesnastkowy##orbH";
    strings["Pattern##sgse1"].plurals[0] = "Wzorzec";
    strings["Center pattern view##sgse"].plurals[0] = "Центрировать отображаемые паттерны внутри окна";
    strings["Overflow pattern highlights##sgse"].plurals[0] = "Продолжать полосы подсветки строк паттернов за пределы самих паттернов";
    strings["Display previous/next pattern##sgse"].plurals[0] = "Отображать предыдущий/следующий паттерн";
    strings["Pattern row number format:##sgse"].plurals[0] = "Формат отображения номера строки паттерна:";
    strings["Decimal##prbD"].plurals[0] = "Dziesiętny##prbD";
    strings["Hexadecimal##prbH"].plurals[0] = "Szesnastkowy##prbH";
    strings["Pattern view labels:##sgse"].plurals[0] = "Маркировка ячеек в паттерне";
    strings["Note off (3-char)##sgse"].plurals[0] = "\"Отпускание клавиши\" (резкое) (3 символа)";
    strings["Note release (3-char)##sgse"].plurals[0] = "\"Отпускание клавиши\" (с включением фазы затухания огибающей) (3 символа)";
    strings["Macro release (3-char)##sgse"].plurals[0] = "\"Отпускание клавиши\" (только для макросов (3 символа))";
    strings["Empty field (3-char)##sgse"].plurals[0] = "Пустая ячейка (3 символа)";
    strings["Empty field (2-char)##sgse"].plurals[0] = "Пустая ячейка (2 символа)";
    strings["Pattern view spacing after:##sgse"].plurals[0] = "Разбивка в отображении паттерна:";
    strings["Note##sgse"].plurals[0] = "Nuta";
    strings["Instrument##sgse1"].plurals[0] = "Instrument";
    strings["Volume##sgse4"].plurals[0] = "Głośność";
    strings["Effect##sgse"].plurals[0] = "Индекс эффекта";
    strings["Effect value##sgse"].plurals[0] = "Параметр эффекта";
    strings["Single-digit effects for 00-0F##sgse"].plurals[0] = "Отображать одной цифрой индекс эффекта для индексов 00-0F";
    strings["Use flats instead of sharps##sgse"].plurals[0] = "Отображать бемоли вместо диезов";
    strings["Use German notation##sgse"].plurals[0] = "Использовать немецкие имена нот";
    strings["Channel##sgse1"].plurals[0] = "Kanał";
    strings["Channel style:##sgse"].plurals[0] = "Стиль заголовка:";
    strings["Classic##CHS0"].plurals[0] = "Klasyczny##CHS0";
    strings["Line##CHS1"].plurals[0] = "Линия##CHS1";
    strings["Round##CHS2"].plurals[0] = "Со скруглениями##CHS2";
    strings["Split button##CHS3"].plurals[0] = "С отдельной кнопкой отключения звука##CHS3";
    strings["Square border##CHS4"].plurals[0] = "С прямоугольной границей вокруг названия##CHS4";
    strings["Round border##CHS5"].plurals[0] = "Со скруглённой границей вокруг названия##CHS5";
    strings["Channel volume bar:##sgse"].plurals[0] = "Полоска громкости в заголовке канала:";
    strings["Non##CHV0"].plurals[0] = "Brak##CHV0";
    strings["Simple##CHV1"].plurals[0] = "Простая##CHV1";
    strings["Stereo##CHV2"].plurals[0] = "Stereo##CHV2";
    strings["Real##CHV3"].plurals[0] = "Настоящая громкость##CHV3";
    strings["Real (stereo)##CHV4"].plurals[0] = "Настоящая громкость (стерео)##CHV4";
    strings["Channel feedback style:##sgse"].plurals[0] = "Подсветка заголовка канала:";
    strings["Off##CHF0"].plurals[0] = "Wył.##CHF0";
    strings["Note##CHF1"].plurals[0] = "Начало ноты##CHF1";
    strings["Volume##CHF2"].plurals[0] = "Пропорционально громкости##CHF2";
    strings["Active##CHF3"].plurals[0] = "При активности канала##CHF3";
    strings["Channel font:##sgse"].plurals[0] = "Шрифт заголовка канала:";
    strings["Regular##CHFont0"].plurals[0] = "Обычный##CHFont0";
    strings["Monospace##CHFont1"].plurals[0] = "Моноширинный##CHFont1";
    strings["Center channel name##sgse"].plurals[0] = "Центрировать название канала";
    strings["Channel colors:##sgse"].plurals[0] = "Цвета заголовка канала";
    strings["Single##CHC0"].plurals[0] = "Единый цвет##CHC0";
    strings["Channel type##CHC1"].plurals[0] = "Согласно типу канала##CHC1";
    strings["Instrument type##CHC2"].plurals[0] = "Согласно типу инструмента##CHC2";
    strings["Channel name colors:##sgse"].plurals[0] = "Цвета названия канала:";
    strings["Single##CTC0"].plurals[0] = "Единый цвет##CTC0";
    strings["Channel type##CTC1"].plurals[0] = "Согласно типу канала##CTC1";
    strings["Instrument type##CTC2"].plurals[0] = "Согласно типу инструмента##CTC2";
    strings["Assets##sgse1"].plurals[0] = "Представление ресурсов модуля";
    strings["Unified instrument/wavetable/sample list##sgse"].plurals[0] = "Единый список инструментов, волновых таблиц и сэмплов";
    strings["Horizontal instrument list##sgse"].plurals[0] = "Горизонтальный список инструментов";
    strings["Instrument list icon style:##sgse"].plurals[0] = "Стиль иконок в списке инструментов:";
    strings["None##iis0"].plurals[0] = "Nie pokazuj##iis0";
    strings["Graphical icons##iis1"].plurals[0] = "Графические иконки##iis1";
    strings["Letter icons##iis2"].plurals[0] = "Иконки с буквами##iis2";
    strings["Colorize instrument editor using instrument type##sgse"].plurals[0] = "Изменять оттенки цветов редактора инструмента согласно типу инструмента";
    strings["Macro Editor##sgse0"].plurals[0] = "Редактор макросов";
    strings["Macro editor layout:##sgse"].plurals[0] = "Компоновка редактора макросов:";
    strings["Unified##mel0"].plurals[0] = "Общий список##mel0";
    strings["Grid##mel2"].plurals[0] = "Прямоугольная сетка##mel2";
    strings["Single (with list)##mel3"].plurals[0] = "Окно редактирования одного макроса + список##mel3";
    strings["Use classic macro editor vertical slider##sgse"].plurals[0] = "Использовать классическую вертикальную полосу прокрутки";
    strings["Wave Editor##sgse"].plurals[0] = "Редактор волновых таблиц";
    strings["Use compact wave editor##sgse"].plurals[0] = "Использовать компактный редактор волновых таблиц";
    strings["FM Editor##sgse0"].plurals[0] = "Edytor instrumentów FM";
    strings["FM parameter names:##sgse"].plurals[0] = "Nazwy parametrów FM:";
    strings["Friendly##fmn0"].plurals[0] = "Przyjazne##fmn0";
    strings["Technical##fmn1"].plurals[0] = "Techniczne##fmn1";
    strings["Technical (alternate)##fmn2"].plurals[0] = "Techniczne (alternatywne)##fmn2";
    strings["Use standard OPL waveform names##sgse"].plurals[0] = "Używaj standardowych nazw kształtów fal OPL";
    strings["FM parameter editor layout:##sgse"].plurals[0] = "Układ edytora parametrów FM";
    strings["Modern##fml0"].plurals[0] = "Nowoczesny##fml0";
    strings["Compact (2x2, classic)##fml1"].plurals[0] = "Kompaktowy (2x2, klasyczny)##fml1";
    strings["Compact (1x4)##fml2"].plurals[0] = "Kompaktowy (1x4)##fml2";
    strings["Compact (4x1)##fml3"].plurals[0] = "Kompaktowy (4x1)##fml3";
    strings["Alternate (2x2)##fml4"].plurals[0] = "Alternatywny (2x2)##fml4";
    strings["Alternate (1x4)##fml5"].plurals[0] = "Alternatywny (1x4)##fml5";
    strings["Alternate (4x1)##fml6"].plurals[0] = "Alternatywny (4x1)##fml6";
    strings["Position of Sustain in FM editor:##sgse"].plurals[0] = "Позиция параметра \"Сустейн\" в редакторе:";
    strings["Between Decay and Sustain Rate##susp0"].plurals[0] = "Между спадом и уклоном сустейна##susp0";
    strings["After Release Rate##susp1"].plurals[0] = "После уклона релиза##susp1";
    strings["Use separate colors for carriers/modulators in FM editor##sgse"].plurals[0] = "Использовать различные цвета для модулирующих и несущих операторов";
    strings["Unsigned FM detune values##sgse"].plurals[0] = "Беззнаковое значение параметра расстройки";
    strings["Statistics##sgse"].plurals[0] = "Okno statystyk";
    strings["Chip memory usage unit:##sgse"].plurals[0] = "Jednostki wyświatlania obciążenia pamięci układu:";
    strings["Bytes##MUU0"].plurals[0] = "Bajty##MUU0";
    strings["Kilobytes##MUU1"].plurals[0] = "Kilobajty##MUU1";
    strings["Oscilloscope##set"].plurals[0] = "Осциллограф##set";
    strings["Rounded corners##sgse"].plurals[0] = "Закруглённые края";
    strings["Border##sgse"].plurals[0] = "Granica";
    strings["Mono##sgse1"].plurals[0] = "Nono";
    strings["Anti-aliased##sgse"].plurals[0] = "Со сглаживанием";
    strings["Fill entire window##sgse"].plurals[0] = "Полностью заполняет окно";
    strings["Waveform goes out of bounds##sgse"].plurals[0] = "Волна может выходить за пределы окна";
    strings["Windows##sgse"].plurals[0] = "Окна";
    strings["Rounded window corners##sgse"].plurals[0] = "Закруглённые края окон";
    strings["Rounded buttons##sgse"].plurals[0] = "Закруглённые края кнопок";
    strings["Rounded tabs##sgse"].plurals[0] = "Закруглённые края заголовков вкладок";
    strings["Rounded scrollbars##sgse"].plurals[0] = "Закруглённые края ползунка полосы прокрутки";
    strings["Rounded menu corners##sgse"].plurals[0] = "Закруглённые края выпадающих меню";
    strings["Borders around widgets##sgse"].plurals[0] = "Границы вокруг кнопок, списков и т.д.";
    strings["Misc##sgse"].plurals[0] = "Inne";
    strings["Wrap text##sgse"].plurals[0] = "Переносить текст на новую строку";
    strings["Wrap text in song/subsong comments window.##sgse"].plurals[0] = "Переносить текст на новую строку в окне информации/комментариев к композиции.";
    strings["Frame shading in text windows##sgse"].plurals[0] = "Градиент в текстовых окнах";
    strings["Apply frame shading to the multiline text fields\nsuch as song/subsong info/comments.##sgse"].plurals[0] = "Применять градиент в окне информации/комментариев к композиции.";
    strings["Color##sgse"].plurals[0] = "Kolor";
    strings["Color scheme##sgse"].plurals[0] = "Schemat kolorow";
    strings["Import##sgse2"].plurals[0] = "Importuj";
    strings["Export##sgse2"].plurals[0] = "Eksportuj";
    strings["Reset defaults##sgse1"].plurals[0] = "Domyslne";
    strings["Are you sure you want to reset the color scheme?##sgse"].plurals[0] = "Вы действительно хотите сбросить цветовую схему?";
    strings["Interface##sgse1"].plurals[0] = "Interfejs";
    strings["Frame shading##sgse"].plurals[0] = "Затенение рамок";
    strings["Interface (other)##sgse"].plurals[0] = "Interfejs (inne)";
    strings["Miscellaneous##sgse"].plurals[0] = "Inne";
    strings["File Picker (built-in)##sgse"].plurals[0] = "Wbudowany wybierak plikow";
    strings["Oscilloscope##sgse"].plurals[0] = "Oscyloskop";
    strings["Wave (non-mono)##sgse"].plurals[0] = "Fala (nie mono)";
    strings["Volume Meter##sgse"].plurals[0] = "Измеритель громкости";
    strings["Orders##sgse2"].plurals[0] = "Matryca wzorcow";
    strings["Envelope View##sgse"].plurals[0] = "Podglad obwiedni";
    strings["FM Editor##sgse1"].plurals[0] = "Edytor instrumentow FM";
    strings["Macro Editor##sgse1"].plurals[0] = "Edytor makr";
    strings["Instrument Types##sgse"].plurals[0] = "Typy instrumentow";
    strings["Channel##sgse2"].plurals[0] = "Kanal";
    strings["Pattern##sgse2"].plurals[0] = "Wzorzec";
    strings["Sample Editor##sgse"].plurals[0] = "Edytor sampli";
    strings["Pattern Manager##sgse"].plurals[0] = "Menedzer wzorcow";
    strings["Piano##sgse"].plurals[0] = "Klawiatura pianina";
    strings["Clock##sgse"].plurals[0] = "Zegar";
    strings["Patchbay##sgse"].plurals[0] = "Соединение каналов";
    strings["Log Viewer##sgse"].plurals[0] = "Podgląd logów";

    // these are messy, but the ##CC_GUI... is required.
    strings["Button##CC_GUI_COLOR_BUTTON"].plurals[0] = "Przycisk##CC_GUI_COLOR_BUTTON";
    strings["Button (hovered)##CC_GUI_COLOR_BUTTON_HOVER"].plurals[0] = "Кнопка (курсор на кнопке)##CC_GUI_COLOR_BUTTON_HOVER";
    strings["Button (active)##CC_GUI_COLOR_BUTTON_ACTIVE"].plurals[0] = "Кнопка (нажатая)##CC_GUI_COLOR_BUTTON_ACTIVE";
    strings["Tab##CC_GUI_COLOR_TAB"].plurals[0] = "Вкладка##CC_GUI_COLOR_TAB";
    strings["Tab (hovered)##CC_GUI_COLOR_TAB_HOVER"].plurals[0] = "Вкладка (курсор на вкладке)##CC_GUI_COLOR_TAB_HOVER";
    strings["Tab (active)##CC_GUI_COLOR_TAB_ACTIVE"].plurals[0] = "Вкладка (активная)##CC_GUI_COLOR_TAB_ACTIVE";
    strings["Tab (unfocused)##CC_GUI_COLOR_TAB_UNFOCUSED"].plurals[0] = "Вкладка (не текущая)##CC_GUI_COLOR_TAB_UNFOCUSED";
    strings["Tab (unfocused and active)##CC_GUI_COLOR_TAB_UNFOCUSED_ACTIVE"].plurals[0] = "Вкладка (курсор на вкладке, текущая)##CC_GUI_COLOR_TAB_UNFOCUSED_ACTIVE";
    strings["ImGui header##CC_GUI_COLOR_IMGUI_HEADER"].plurals[0] = "Заголовок ImGui##CC_GUI_COLOR_IMGUI_HEADER";
    strings["ImGui header (hovered)##CC_GUI_COLOR_IMGUI_HEADER_HOVER"].plurals[0] = "Заголовок ImGui (курсор на заголовке)##CC_GUI_COLOR_IMGUI_HEADER_HOVER";
    strings["ImGui header (active)##CC_GUI_COLOR_IMGUI_HEADER_ACTIVE"].plurals[0] = "Заголовок ImGui (активный)##CC_GUI_COLOR_IMGUI_HEADER_ACTIVE";
    strings["Resize grip##CC_GUI_COLOR_RESIZE_GRIP"].plurals[0] = "Захват для изменения размера окна##CC_GUI_COLOR_RESIZE_GRIP";
    strings["Resize grip (hovered)##CC_GUI_COLOR_RESIZE_GRIP_HOVER"].plurals[0] = "Захват для изменения размера окна (курсор на захвате)##CC_GUI_COLOR_RESIZE_GRIP_HOVER";
    strings["Resize grip (active)##CC_GUI_COLOR_RESIZE_GRIP_ACTIVE"].plurals[0] = "Захват для изменения размера окна (активный)##CC_GUI_COLOR_RESIZE_GRIP_ACTIVE";
    strings["Widget background##CC_GUI_COLOR_WIDGET_BACKGROUND"].plurals[0] = "Задний фон виджета##CC_GUI_COLOR_WIDGET_BACKGROUND";
    strings["Widget background (hovered)##CC_GUI_COLOR_WIDGET_BACKGROUND_HOVER"].plurals[0] = "Задний фон виджета (курсор на виджете)##CC_GUI_COLOR_WIDGET_BACKGROUND_HOVER";
    strings["Widget background (active)##CC_GUI_COLOR_WIDGET_BACKGROUND_ACTIVE"].plurals[0] = "Задний фон виджета (активный)##CC_GUI_COLOR_WIDGET_BACKGROUND_ACTIVE";
    strings["Slider grab##CC_GUI_COLOR_SLIDER_GRAB"].plurals[0] = "Ползунок выставления значения##CC_GUI_COLOR_SLIDER_GRAB";
    strings["Slider grab (active)##CC_GUI_COLOR_SLIDER_GRAB_ACTIVE"].plurals[0] = "Ползунок выставления значения (активный)##CC_GUI_COLOR_SLIDER_GRAB_ACTIVE";
    strings["Title background (active)##CC_GUI_COLOR_TITLE_BACKGROUND_ACTIVE"].plurals[0] = "Задний фон заголовка (активный)##CC_GUI_COLOR_TITLE_BACKGROUND_ACTIVE";
    strings["Checkbox/radio button mark##CC_GUI_COLOR_CHECK_MARK"].plurals[0] = "Маркировка в поле для галочки и радиокнопке##CC_GUI_COLOR_CHECK_MARK";
    strings["Text selection##CC_GUI_COLOR_TEXT_SELECTION"].plurals[0] = "ВЫделение текста##CC_GUI_COLOR_TEXT_SELECTION";
    strings["Line plot##CC_GUI_COLOR_PLOT_LINES"].plurals[0] = "Цвет линий##CC_GUI_COLOR_PLOT_LINES";
    strings["Line plot (hovered)##CC_GUI_COLOR_PLOT_LINES_HOVER"].plurals[0] = "Цвет линий (курсор на поле)##CC_GUI_COLOR_PLOT_LINES_HOVER";
    strings["Histogram plot##CC_GUI_COLOR_PLOT_HISTOGRAM"].plurals[0] = "Столбчатая диаграмма##CC_GUI_COLOR_PLOT_HISTOGRAM";
    strings["Histogram plot (hovered)##CC_GUI_COLOR_PLOT_HISTOGRAM_HOVER"].plurals[0] = "Столбчатая диаграмма (курсор на диаграмме)##CC_GUI_COLOR_PLOT_HISTOGRAM_HOVER";
    strings["Table row (even)##CC_GUI_COLOR_TABLE_ROW_EVEN"].plurals[0] = "Строка таблицы (чётная)##CC_GUI_COLOR_TABLE_ROW_EVEN";
    strings["Table row (odd)##CC_GUI_COLOR_TABLE_ROW_ODD"].plurals[0] = "Строка таблицы (нечётная)##CC_GUI_COLOR_TABLE_ROW_ODD";

    strings["Background##CC_GUI_COLOR_BACKGROUND"].plurals[0] = "Задний фон##CC_GUI_COLOR_BACKGROUND";
    strings["Window background##CC_GUI_COLOR_FRAME_BACKGROUND"].plurals[0] = "Фон окон##CC_GUI_COLOR_FRAME_BACKGROUND";
    strings["Sub-window background##CC_GUI_COLOR_FRAME_BACKGROUND_CHILD"].plurals[0] = "Фон подокн##CC_GUI_COLOR_FRAME_BACKGROUND_CHILD";
    strings["Pop-up background##CC_GUI_COLOR_FRAME_BACKGROUND_POPUP"].plurals[0] = "Фон всплывающих окон##CC_GUI_COLOR_FRAME_BACKGROUND_POPUP";
    strings["Modal backdrop##CC_GUI_COLOR_MODAL_BACKDROP"].plurals[0] = "Затенение при возникновении модального окна##CC_GUI_COLOR_MODAL_BACKDROP";
    strings["Header##CC_GUI_COLOR_HEADER"].plurals[0] = "Nagłówek##CC_GUI_COLOR_HEADER";
    strings["Text##CC_GUI_COLOR_TEXT"].plurals[0] = "Tekst##CC_GUI_COLOR_TEXT";
    strings["Text (disabled)##CC_GUI_COLOR_TEXT_DISABLED"].plurals[0] = "Tekst (выключенный)##CC_GUI_COLOR_TEXT_DISABLED";
    strings["Title bar (inactive)##CC_GUI_COLOR_TITLE_INACTIVE"].plurals[0] = "Полоса заголовка (неактивная)##CC_GUI_COLOR_TITLE_INACTIVE";
    strings["Title bar (collapsed)##CC_GUI_COLOR_TITLE_COLLAPSED"].plurals[0] = "Полоса заголовка (свёрнутое окно)##CC_GUI_COLOR_TITLE_COLLAPSED";
    strings["Menu bar##CC_GUI_COLOR_MENU_BAR"].plurals[0] = "Полоса меню##CC_GUI_COLOR_MENU_BAR";
    strings["Border##CC_GUI_COLOR_BORDER"].plurals[0] = "Граница##CC_GUI_COLOR_BORDER";
    strings["Border shadow##CC_GUI_COLOR_BORDER_SHADOW"].plurals[0] = "Тень границы##CC_GUI_COLOR_BORDER_SHADOW";
    strings["Scroll bar##CC_GUI_COLOR_SCROLL"].plurals[0] = "Полоса прокрутки##CC_GUI_COLOR_SCROLL";
    strings["Scroll bar (hovered)##CC_GUI_COLOR_SCROLL_HOVER"].plurals[0] = "Полоса прокрутки (курсор на полосе)##CC_GUI_COLOR_SCROLL_HOVER";
    strings["Scroll bar (clicked)##CC_GUI_COLOR_SCROLL_ACTIVE"].plurals[0] = "Полоса прокрутки (нажата)##CC_GUI_COLOR_SCROLL_ACTIVE";
    strings["Scroll bar background##CC_GUI_COLOR_SCROLL_BACKGROUND"].plurals[0] = "Фон полосы прокрутки##CC_GUI_COLOR_SCROLL_BACKGROUND";
    strings["Separator##CC_GUI_COLOR_SEPARATOR"].plurals[0] = "Разделитель строк##CC_GUI_COLOR_SEPARATOR";
    strings["Separator (hover)##CC_GUI_COLOR_SEPARATOR_HOVER"].plurals[0] = "Разделитель строк (курсор на разделителе)##CC_GUI_COLOR_SEPARATOR_HOVER";
    strings["Separator (active)##CC_GUI_COLOR_SEPARATOR_ACTIVE"].plurals[0] = "Разделитель строк (активный)##CC_GUI_COLOR_SEPARATOR_ACTIVE";
    strings["Docking preview##CC_GUI_COLOR_DOCKING_PREVIEW"].plurals[0] = "Превью стыковки окон##CC_GUI_COLOR_DOCKING_PREVIEW";
    strings["Docking empty##CC_GUI_COLOR_DOCKING_EMPTY"].plurals[0] = "Пустое поле стыковки окон##CC_GUI_COLOR_DOCKING_EMPTY";
    strings["Table header##CC_GUI_COLOR_TABLE_HEADER"].plurals[0] = "Заголовок таблицы##CC_GUI_COLOR_TABLE_HEADER";
    strings["Table border (hard)##CC_GUI_COLOR_TABLE_BORDER_HARD"].plurals[0] = "Заголовок таблицы (жёсткий)##CC_GUI_COLOR_TABLE_BORDER_HARD";
    strings["Table border (soft)##CC_GUI_COLOR_TABLE_BORDER_SOFT"].plurals[0] = "Заголовок таблицы (мягкий)##CC_GUI_COLOR_TABLE_BORDER_SOFT";
    strings["Drag and drop target##CC_GUI_COLOR_DRAG_DROP_TARGET"].plurals[0] = "Цель перетаскивания##CC_GUI_COLOR_DRAG_DROP_TARGET";
    strings["Window switcher (highlight)##CC_GUI_COLOR_NAV_WIN_HIGHLIGHT"].plurals[0] = "Переключатель окон (подсвечен)##CC_GUI_COLOR_NAV_WIN_HIGHLIGHT";
    strings["Window switcher backdrop##CC_GUI_COLOR_NAV_WIN_BACKDROP"].plurals[0] = "Переключатель окон (цвет затенения остального интерфейса)##CC_GUI_COLOR_NAV_WIN_BACKDROP";

    strings["Toggle on##CC_GUI_COLOR_TOGGLE_ON"].plurals[0] = "Переключатель вкл.##CC_GUI_COLOR_TOGGLE_ON";
    strings["Toggle off##CC_GUI_COLOR_TOGGLE_OFF"].plurals[0] = "Переключатель выкл.##CC_GUI_COLOR_TOGGLE_OFF";
    strings["Playback status##CC_GUI_COLOR_PLAYBACK_STAT"].plurals[0] = "Статус воспроизведения##CC_GUI_COLOR_PLAYBACK_STAT";
    strings["Destructive hint##CC_GUI_COLOR_DESTRUCTIVE"].plurals[0] = "Подсказка об удалении##CC_GUI_COLOR_DESTRUCTIVE";
    strings["Warning hint##CC_GUI_COLOR_WARNING"].plurals[0] = "Подсказка о сообщении##CC_GUI_COLOR_WARNING";
    strings["Error hint##CC_GUI_COLOR_ERROR"].plurals[0] = "Подсказка об ошибке##CC_GUI_COLOR_ERROR";

    strings["Directory##CC_GUI_COLOR_FILE_DIR"].plurals[0] = "Folder##CC_GUI_COLOR_FILE_DIR";
    strings["Song (native)##CC_GUI_COLOR_FILE_SONG_NATIVE"].plurals[0] = "Файл трека (нативно поддерживается)##CC_GUI_COLOR_FILE_SONG_NATIVE";
    strings["Song (import)##CC_GUI_COLOR_FILE_SONG_IMPORT"].plurals[0] = "Файл трека (импорт)##CC_GUI_COLOR_FILE_SONG_IMPORT";
    strings["Instrument##CC_GUI_COLOR_FILE_INSTR"].plurals[0] = "Instrument##CC_GUI_COLOR_FILE_INSTR";
    strings["Audio##CC_GUI_COLOR_FILE_AUDIO"].plurals[0] = "Audio##CC_GUI_COLOR_FILE_AUDIO";
    strings["Wavetable##CC_GUI_COLOR_FILE_WAVE"].plurals[0] = "Tablica fal##CC_GUI_COLOR_FILE_WAVE";
    strings["VGM##CC_GUI_COLOR_FILE_VGM"].plurals[0] = "VGM##CC_GUI_COLOR_FILE_VGM";
    strings["ZSM##CC_GUI_COLOR_FILE_ZSM"].plurals[0] = "ZSM##CC_GUI_COLOR_FILE_ZSM";
    strings["Font##CC_GUI_COLOR_FILE_FONT"].plurals[0] = "Czcionka##CC_GUI_COLOR_FILE_FONT";
    strings["Other##CC_GUI_COLOR_FILE_OTHER"].plurals[0] = "Inne##CC_GUI_COLOR_FILE_OTHER";

    strings["Border##CC_GUI_COLOR_OSC_BORDER"].plurals[0] = "Граница осциллографа##CC_GUI_COLOR_OSC_BORDER";
    strings["Background (top-left)##CC_GUI_COLOR_OSC_BG1"].plurals[0] = "Фон (верхний левый угол)##CC_GUI_COLOR_OSC_BG1";
    strings["Background (top-right)##CC_GUI_COLOR_OSC_BG2"].plurals[0] = "Фон (верхний правый угол)##CC_GUI_COLOR_OSC_BG2";
    strings["Background (bottom-left)##CC_GUI_COLOR_OSC_BG3"].plurals[0] = "Фон (нижний левый угол)##CC_GUI_COLOR_OSC_BG3";
    strings["Background (bottom-right)##CC_GUI_COLOR_OSC_BG4"].plurals[0] = "Фон (нижний правый угол)##CC_GUI_COLOR_OSC_BG4";
    strings["Waveform##CC_GUI_COLOR_OSC_WAVE"].plurals[0] = "Волна##CC_GUI_COLOR_OSC_WAVE";
    strings["Waveform (clip)##CC_GUI_COLOR_OSC_WAVE_PEAK"].plurals[0] = "Волна (зашкал амплитуды)##CC_GUI_COLOR_OSC_WAVE_PEAK";
    strings["Reference##CC_GUI_COLOR_OSC_REF"].plurals[0] = "Образец##CC_GUI_COLOR_OSC_REF";
    strings["Guide##CC_GUI_COLOR_OSC_GUIDE"].plurals[0] = "Справка##CC_GUI_COLOR_OSC_GUIDE";

    strings["Waveform (1)##CC_GUI_COLOR_OSC_WAVE_CH0"].plurals[0] = "Волна (1)##CC_GUI_COLOR_OSC_WAVE_CH0";
    strings["Waveform (2)##CC_GUI_COLOR_OSC_WAVE_CH1"].plurals[0] = "Волна (2)##CC_GUI_COLOR_OSC_WAVE_CH1";
    strings["Waveform (3)##CC_GUI_COLOR_OSC_WAVE_CH2"].plurals[0] = "Волна (3)##CC_GUI_COLOR_OSC_WAVE_CH2";
    strings["Waveform (4)##CC_GUI_COLOR_OSC_WAVE_CH3"].plurals[0] = "Волна (4)##CC_GUI_COLOR_OSC_WAVE_CH3";
    strings["Waveform (5)##CC_GUI_COLOR_OSC_WAVE_CH4"].plurals[0] = "Волна (5)##CC_GUI_COLOR_OSC_WAVE_CH4";
    strings["Waveform (6)##CC_GUI_COLOR_OSC_WAVE_CH5"].plurals[0] = "Волна (6)##CC_GUI_COLOR_OSC_WAVE_CH5";
    strings["Waveform (7)##CC_GUI_COLOR_OSC_WAVE_CH6"].plurals[0] = "Волна (7)##CC_GUI_COLOR_OSC_WAVE_CH6";
    strings["Waveform (8)##CC_GUI_COLOR_OSC_WAVE_CH7"].plurals[0] = "Волна (8)##CC_GUI_COLOR_OSC_WAVE_CH7";
    strings["Waveform (9)##CC_GUI_COLOR_OSC_WAVE_CH8"].plurals[0] = "Волна (9)##CC_GUI_COLOR_OSC_WAVE_CH8";
    strings["Waveform (10)##CC_GUI_COLOR_OSC_WAVE_CH9"].plurals[0] = "Волна (10)##CC_GUI_COLOR_OSC_WAVE_CH9";
    strings["Waveform (11)##CC_GUI_COLOR_OSC_WAVE_CH10"].plurals[0] = "Волна (11)##CC_GUI_COLOR_OSC_WAVE_CH10";
    strings["Waveform (12)##CC_GUI_COLOR_OSC_WAVE_CH11"].plurals[0] = "Волна (12)##CC_GUI_COLOR_OSC_WAVE_CH11";
    strings["Waveform (13)##CC_GUI_COLOR_OSC_WAVE_CH12"].plurals[0] = "Волна (13)##CC_GUI_COLOR_OSC_WAVE_CH12";
    strings["Waveform (14)##CC_GUI_COLOR_OSC_WAVE_CH13"].plurals[0] = "Волна (14)##CC_GUI_COLOR_OSC_WAVE_CH13";
    strings["Waveform (15)##CC_GUI_COLOR_OSC_WAVE_CH14"].plurals[0] = "Волна (15)##CC_GUI_COLOR_OSC_WAVE_CH14";
    strings["Waveform (16)##CC_GUI_COLOR_OSC_WAVE_CH15"].plurals[0] = "Волна (16)##CC_GUI_COLOR_OSC_WAVE_CH15";

    strings["Low##CC_GUI_COLOR_VOLMETER_LOW"].plurals[0] = "Низкий уровень##CC_GUI_COLOR_VOLMETER_LOW";
    strings["High##CC_GUI_COLOR_VOLMETER_HIGH"].plurals[0] = "Высокий уровень##CC_GUI_COLOR_VOLMETER_HIGH";
    strings["Clip##CC_GUI_COLOR_VOLMETER_PEAK"].plurals[0] = "Зашкал##CC_GUI_COLOR_VOLMETER_PEAK";

    strings["Order number##CC_GUI_COLOR_ORDER_ROW_INDEX"].plurals[0] = "Номер строки##CC_GUI_COLOR_ORDER_ROW_INDEX";
    strings["Playing order background##CC_GUI_COLOR_ORDER_ACTIVE"].plurals[0] = "Фон текущей строки##CC_GUI_COLOR_ORDER_ACTIVE";
    strings["Song loop##CC_GUI_COLOR_SONG_LOOP"].plurals[0] = "Место зацикливания трека##CC_GUI_COLOR_SONG_LOOP";
    strings["Selected order##CC_GUI_COLOR_ORDER_SELECTED"].plurals[0] = "Выделенный столбец##CC_GUI_COLOR_ORDER_SELECTED";
    strings["Similar patterns##CC_GUI_COLOR_ORDER_SIMILAR"].plurals[0] = "Похожие паттерны##CC_GUI_COLOR_ORDER_SIMILAR";
    strings["Inactive patterns##CC_GUI_COLOR_ORDER_INACTIVE"].plurals[0] = "Неактивные паттерны##CC_GUI_COLOR_ORDER_INACTIVE";

    strings["Envelope##CC_GUI_COLOR_FM_ENVELOPE"].plurals[0] = "Obwiednia##CC_GUI_COLOR_FM_ENVELOPE";
    strings["Sustain guide##CC_GUI_COLOR_FM_ENVELOPE_SUS_GUIDE"].plurals[0] = "Визуализация сустейна##CC_GUI_COLOR_FM_ENVELOPE_SUS_GUIDE";
    strings["Release##CC_GUI_COLOR_FM_ENVELOPE_RELEASE"].plurals[0] = "Релиз##CC_GUI_COLOR_FM_ENVELOPE_RELEASE";

    strings["Algorithm background##CC_GUI_COLOR_FM_ALG_BG"].plurals[0] = "Задний фон схемы алгоритма##CC_GUI_COLOR_FM_ALG_BG";
    strings["Algorithm lines##CC_GUI_COLOR_FM_ALG_LINE"].plurals[0] = "Линии схемы алгоритма##CC_GUI_COLOR_FM_ALG_LINE";
    strings["Modulator##CC_GUI_COLOR_FM_MOD"].plurals[0] = "Modulator##CC_GUI_COLOR_FM_MOD";
    strings["Carrier##CC_GUI_COLOR_FM_CAR"].plurals[0] = "Fala nośna##CC_GUI_COLOR_FM_CAR";

    strings["SSG-EG##CC_GUI_COLOR_FM_SSG"].plurals[0] = "SSG-EG##CC_GUI_COLOR_FM_SSG";
    strings["Waveform##CC_GUI_COLOR_FM_WAVE"].plurals[0] = "Волна##CC_GUI_COLOR_FM_WAVE";

    strings["Mod. accent (primary)##CC_GUI_COLOR_FM_PRIMARY_MOD"].plurals[0] = "Оттенок модулирующего оператора (основной)##CC_GUI_COLOR_FM_PRIMARY_MOD";
    strings["Mod. accent (secondary)##CC_GUI_COLOR_FM_SECONDARY_MOD"].plurals[0] = "Оттенок модулирующего оператора (неосновной)##CC_GUI_COLOR_FM_SECONDARY_MOD";
    strings["Mod. border##CC_GUI_COLOR_FM_BORDER_MOD"].plurals[0] = "Граница модулирующего оператора##CC_GUI_COLOR_FM_BORDER_MOD";
    strings["Mod. border shadow##CC_GUI_COLOR_FM_BORDER_SHADOW_MOD"].plurals[0] = "Тень границы модулирующего оператора##CC_GUI_COLOR_FM_BORDER_SHADOW_MOD";

    strings["Car. accent (primary)##CC_GUI_COLOR_FM_PRIMARY_CAR"].plurals[0] = "Оттенок несущего оператора (основной)##CC_GUI_COLOR_FM_PRIMARY_CAR";
    strings["Car. accent (secondary)##CC_GUI_COLOR_FM_SECONDARY_CAR"].plurals[0] = "Оттенок несущего оператора (неосновной)##CC_GUI_COLOR_FM_SECONDARY_CAR";
    strings["Car. border##CC_GUI_COLOR_FM_BORDER_CAR"].plurals[0] = "Граница несущего оператора##CC_GUI_COLOR_FM_BORDER_CAR";
    strings["Car. border shadow##CC_GUI_COLOR_FM_BORDER_SHADOW_CAR"].plurals[0] = "Тень границы несущего оператора##CC_GUI_COLOR_FM_BORDER_SHADOW_CAR";

    strings["Volume##CC_GUI_COLOR_MACRO_VOLUME"].plurals[0] = "Głośność##CC_GUI_COLOR_MACRO_VOLUME";
    strings["Pitch##CC_GUI_COLOR_MACRO_PITCH"].plurals[0] = "Wysokość##CC_GUI_COLOR_MACRO_PITCH";
    strings["Wave##CC_GUI_COLOR_MACRO_WAVE"].plurals[0] = "Волна##CC_GUI_COLOR_MACRO_WAVE";
    strings["Other##CC_GUI_COLOR_MACRO_OTHER"].plurals[0] = "Inne##CC_GUI_COLOR_MACRO_OTHER";

    strings["FM (OPN)##CC_GUI_COLOR_INSTR_FM"].plurals[0] = "FM (OPN)##CC_GUI_COLOR_INSTR_FM";
    strings["SN76489/Sega PSG##CC_GUI_COLOR_INSTR_STD"].plurals[0] = "SN76489/Sega PSG##CC_GUI_COLOR_INSTR_STD";
    strings["T6W28##CC_GUI_COLOR_INSTR_T6W28"].plurals[0] = "T6W28##CC_GUI_COLOR_INSTR_T6W28";
    strings["Game Boy##CC_GUI_COLOR_INSTR_GB"].plurals[0] = "Game Boy##CC_GUI_COLOR_INSTR_GB";
    strings["C64##CC_GUI_COLOR_INSTR_C64"].plurals[0] = "C64##CC_GUI_COLOR_INSTR_C64";
    strings["Amiga/Generic Sample##CC_GUI_COLOR_INSTR_AMIGA"].plurals[0] = "Amiga/Zwykły sampel##CC_GUI_COLOR_INSTR_AMIGA";
    strings["PC Engine##CC_GUI_COLOR_INSTR_PCE"].plurals[0] = "PC Engine##CC_GUI_COLOR_INSTR_PCE";
    strings["AY-3-8910/SSG##CC_GUI_COLOR_INSTR_AY"].plurals[0] = "AY-3-8910/SSG##CC_GUI_COLOR_INSTR_AY";
    strings["AY8930##CC_GUI_COLOR_INSTR_AY8930"].plurals[0] = "AY8930##CC_GUI_COLOR_INSTR_AY8930";
    strings["TIA##CC_GUI_COLOR_INSTR_TIA"].plurals[0] = "TIA##CC_GUI_COLOR_INSTR_TIA";
    strings["SAA1099##CC_GUI_COLOR_INSTR_SAA1099"].plurals[0] = "SAA1099##CC_GUI_COLOR_INSTR_SAA1099";
    strings["VIC##CC_GUI_COLOR_INSTR_VIC"].plurals[0] = "VIC##CC_GUI_COLOR_INSTR_VIC";
    strings["PET##CC_GUI_COLOR_INSTR_PET"].plurals[0] = "PET##CC_GUI_COLOR_INSTR_PET";
    strings["VRC6##CC_GUI_COLOR_INSTR_VRC6"].plurals[0] = "VRC6##CC_GUI_COLOR_INSTR_VRC6";
    strings["VRC6 (saw)##CC_GUI_COLOR_INSTR_VRC6_SAW"].plurals[0] = "VRC6 (пила)##CC_GUI_COLOR_INSTR_VRC6_SAW";
    strings["FM (OPLL)##CC_GUI_COLOR_INSTR_OPLL"].plurals[0] = "FM (OPLL)##CC_GUI_COLOR_INSTR_OPLL";
    strings["FM (OPL)##CC_GUI_COLOR_INSTR_OPL"].plurals[0] = "FM (OPL)##CC_GUI_COLOR_INSTR_OPL";
    strings["FDS##CC_GUI_COLOR_INSTR_FDS"].plurals[0] = "FDS##CC_GUI_COLOR_INSTR_FDS";
    strings["Virtual Boy##CC_GUI_COLOR_INSTR_VBOY"].plurals[0] = "Virtual Boy##CC_GUI_COLOR_INSTR_VBOY";
    strings["Namco 163##CC_GUI_COLOR_INSTR_N163"].plurals[0] = "Namco 163##CC_GUI_COLOR_INSTR_N163";
    strings["Konami SCC##CC_GUI_COLOR_INSTR_SCC"].plurals[0] = "Konami SCC##CC_GUI_COLOR_INSTR_SCC";
    strings["FM (OPZ)##CC_GUI_COLOR_INSTR_OPZ"].plurals[0] = "FM (OPZ)##CC_GUI_COLOR_INSTR_OPZ";
    strings["POKEY##CC_GUI_COLOR_INSTR_POKEY"].plurals[0] = "POKEY##CC_GUI_COLOR_INSTR_POKEY";
    strings["PC Beeper##CC_GUI_COLOR_INSTR_BEEPER"].plurals[0] = "PC Beeper##CC_GUI_COLOR_INSTR_BEEPER";
    strings["WonderSwan##CC_GUI_COLOR_INSTR_SWAN"].plurals[0] = "WonderSwan##CC_GUI_COLOR_INSTR_SWAN";
    strings["Lynx##CC_GUI_COLOR_INSTR_MIKEY"].plurals[0] = "Lynx##CC_GUI_COLOR_INSTR_MIKEY";
    strings["VERA##CC_GUI_COLOR_INSTR_VERA"].plurals[0] = "VERA##CC_GUI_COLOR_INSTR_VERA";
    strings["X1-010##CC_GUI_COLOR_INSTR_X1_010"].plurals[0] = "X1-010##CC_GUI_COLOR_INSTR_X1_010";
    strings["ES5506##CC_GUI_COLOR_INSTR_ES5506"].plurals[0] = "ES5506##CC_GUI_COLOR_INSTR_ES5506";
    strings["MultiPCM##CC_GUI_COLOR_INSTR_MULTIPCM"].plurals[0] = "MultiPCM##CC_GUI_COLOR_INSTR_MULTIPCM";
    strings["SNES##CC_GUI_COLOR_INSTR_SNES"].plurals[0] = "SNES##CC_GUI_COLOR_INSTR_SNES";
    strings["Sound Unit##CC_GUI_COLOR_INSTR_SU"].plurals[0] = "Звуковой модуль##CC_GUI_COLOR_INSTR_SU";
    strings["Namco WSG##CC_GUI_COLOR_INSTR_NAMCO"].plurals[0] = "Namco WSG##CC_GUI_COLOR_INSTR_NAMCO";
    strings["FM (OPL Drums)##CC_GUI_COLOR_INSTR_OPL_DRUMS"].plurals[0] = "FM (OPL, ударные)##CC_GUI_COLOR_INSTR_OPL_DRUMS";
    strings["FM (OPM)##CC_GUI_COLOR_INSTR_OPM"].plurals[0] = "FM (OPM)##CC_GUI_COLOR_INSTR_OPM";
    strings["NES##CC_GUI_COLOR_INSTR_NES"].plurals[0] = "NES##CC_GUI_COLOR_INSTR_NES";
    strings["MSM6258##CC_GUI_COLOR_INSTR_MSM6258"].plurals[0] = "MSM6258##CC_GUI_COLOR_INSTR_MSM6258";
    strings["MSM6295##CC_GUI_COLOR_INSTR_MSM6295"].plurals[0] = "MSM6295##CC_GUI_COLOR_INSTR_MSM6295";
    strings["ADPCM-A##CC_GUI_COLOR_INSTR_ADPCMA"].plurals[0] = "ADPCM-A##CC_GUI_COLOR_INSTR_ADPCMA";
    strings["ADPCM-B##CC_GUI_COLOR_INSTR_ADPCMB"].plurals[0] = "ADPCM-B##CC_GUI_COLOR_INSTR_ADPCMB";
    strings["Sega PCM##CC_GUI_COLOR_INSTR_SEGAPCM"].plurals[0] = "Sega PCM##CC_GUI_COLOR_INSTR_SEGAPCM";
    strings["QSound##CC_GUI_COLOR_INSTR_QSOUND"].plurals[0] = "QSound##CC_GUI_COLOR_INSTR_QSOUND";
    strings["YMZ280B##CC_GUI_COLOR_INSTR_YMZ280B"].plurals[0] = "YMZ280B##CC_GUI_COLOR_INSTR_YMZ280B";
    strings["RF5C68##CC_GUI_COLOR_INSTR_RF5C68"].plurals[0] = "RF5C68##CC_GUI_COLOR_INSTR_RF5C68";
    strings["MSM5232##CC_GUI_COLOR_INSTR_MSM5232"].plurals[0] = "MSM5232##CC_GUI_COLOR_INSTR_MSM5232";
    strings["K007232##CC_GUI_COLOR_INSTR_K007232"].plurals[0] = "K007232##CC_GUI_COLOR_INSTR_K007232";
    strings["GA20##CC_GUI_COLOR_INSTR_GA20"].plurals[0] = "GA20##CC_GUI_COLOR_INSTR_GA20";
    strings["Pokémon Mini##CC_GUI_COLOR_INSTR_POKEMINI"].plurals[0] = "Pokémon Mini##CC_GUI_COLOR_INSTR_POKEMINI";
    strings["SM8521##CC_GUI_COLOR_INSTR_SM8521"].plurals[0] = "SM8521##CC_GUI_COLOR_INSTR_SM8521";
    strings["PV-1000##CC_GUI_COLOR_INSTR_PV1000"].plurals[0] = "PV-1000##CC_GUI_COLOR_INSTR_PV1000";
    strings["K053260##CC_GUI_COLOR_INSTR_K053260"].plurals[0] = "K053260##CC_GUI_COLOR_INSTR_K053260";
    strings["C140##CC_GUI_COLOR_INSTR_C140"].plurals[0] = "C140##CC_GUI_COLOR_INSTR_C140";
    strings["C219##CC_GUI_COLOR_INSTR_C219"].plurals[0] = "C219##CC_GUI_COLOR_INSTR_C219";
    strings["ESFM##CC_GUI_COLOR_INSTR_ESFM"].plurals[0] = "ESFM##CC_GUI_COLOR_INSTR_ESFM";
    strings["ES5503##CC_GUI_COLOR_INSTR_ES5503"].plurals[0] = "ES5503##CC_GUI_COLOR_INSTR_ES5503";
    strings["PowerNoise (noise)##CC_GUI_COLOR_INSTR_POWERNOISE"].plurals[0] = "PowerNoise (szum)##CC_GUI_COLOR_INSTR_POWERNOISE";
    strings["PowerNoise (slope)##CC_GUI_COLOR_INSTR_POWERNOISE_SLOPE"].plurals[0] = "PowerNoise (spadek)##CC_GUI_COLOR_INSTR_POWERNOISE_SLOPE";
    strings["Other/Unknown##CC_GUI_COLOR_INSTR_UNKNOWN"].plurals[0] = "Inny/nieznany##CC_GUI_COLOR_INSTR_UNKNOWN";

    strings["Single color (background)##CC_GUI_COLOR_CHANNEL_BG"].plurals[0] = "Один цвет (фон)##CC_GUI_COLOR_CHANNEL_BG";
    strings["Single color (text)##CC_GUI_COLOR_CHANNEL_FG"].plurals[0] = "Один цвет (текст)##CC_GUI_COLOR_CHANNEL_FG";
    strings["FM##CC_GUI_COLOR_CHANNEL_FM"].plurals[0] = "FM##CC_GUI_COLOR_CHANNEL_FM";
    strings["Pulse##CC_GUI_COLOR_CHANNEL_PULSE"].plurals[0] = "Меандр##CC_GUI_COLOR_CHANNEL_PULSE";
    strings["Noise##CC_GUI_COLOR_CHANNEL_NOISE"].plurals[0] = "Szum##CC_GUI_COLOR_CHANNEL_NOISE";
    strings["PCM##CC_GUI_COLOR_CHANNEL_PCM"].plurals[0] = "PCM##CC_GUI_COLOR_CHANNEL_PCM";
    strings["Wave##CC_GUI_COLOR_CHANNEL_WAVE"].plurals[0] = "Волна##CC_GUI_COLOR_CHANNEL_WAVE";
    strings["FM operator##CC_GUI_COLOR_CHANNEL_OP"].plurals[0] = "FM-оператор##CC_GUI_COLOR_CHANNEL_OP";
    strings["Muted##CC_GUI_COLOR_CHANNEL_MUTED"].plurals[0] = "Заглушен##CC_GUI_COLOR_CHANNEL_MUTED";

    strings["Playhead##CC_GUI_COLOR_PATTERN_PLAY_HEAD"].plurals[0] = "Указатель воспроизведения##CC_GUI_COLOR_PATTERN_PLAY_HEAD";
    strings["Editing##CC_GUI_COLOR_EDITING"].plurals[0] = "Редактирование##CC_GUI_COLOR_EDITING";
    strings["Editing (will clone)##CC_GUI_COLOR_EDITING_CLONE"].plurals[0] = "Редактирование (будет клонирован)##CC_GUI_COLOR_EDITING_CLONE";
    strings["Cursor##CC_GUI_COLOR_PATTERN_CURSOR"].plurals[0] = "Kursor##CC_GUI_COLOR_PATTERN_CURSOR";
    strings["Cursor (hovered)##CC_GUI_COLOR_PATTERN_CURSOR_HOVER"].plurals[0] = "Курсор (мышь на курсоре)##CC_GUI_COLOR_PATTERN_CURSOR_HOVER";
    strings["Cursor (clicked)##CC_GUI_COLOR_PATTERN_CURSOR_ACTIVE"].plurals[0] = "Курсор (нажат)##CC_GUI_COLOR_PATTERN_CURSOR_ACTIVE";
    strings["Selection##CC_GUI_COLOR_PATTERN_SELECTION"].plurals[0] = "Выделение##CC_GUI_COLOR_PATTERN_SELECTION";
    strings["Selection (hovered)##CC_GUI_COLOR_PATTERN_SELECTION_HOVER"].plurals[0] = "Выделение (курсор мыши на выделении)##CC_GUI_COLOR_PATTERN_SELECTION_HOVER";
    strings["Selection (clicked)##CC_GUI_COLOR_PATTERN_SELECTION_ACTIVE"].plurals[0] = "Выделение (нажато)##CC_GUI_COLOR_PATTERN_SELECTION_ACTIVE";
    strings["Highlight 1##CC_GUI_COLOR_PATTERN_HI_1"].plurals[0] = "Подсветка 1##CC_GUI_COLOR_PATTERN_HI_1";
    strings["Highlight 2##CC_GUI_COLOR_PATTERN_HI_2"].plurals[0] = "Подсветка 2##CC_GUI_COLOR_PATTERN_HI_2";
    strings["Row number##CC_GUI_COLOR_PATTERN_ROW_INDEX"].plurals[0] = "Номер строки##CC_GUI_COLOR_PATTERN_ROW_INDEX";
    strings["Row number (highlight 1)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI1"].plurals[0] = "Номер строки (подсветка 1)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI1";
    strings["Row number (highlight 2)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI2"].plurals[0] = "Номер строки (подсветка 2)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI2";
    strings["Note##CC_GUI_COLOR_PATTERN_ACTIVE"].plurals[0] = "Нота##CC_GUI_COLOR_PATTERN_ACTIVE";
    strings["Note (highlight 1)##CC_GUI_COLOR_PATTERN_ACTIVE_HI1"].plurals[0] = "Нота (подсветка 1)##CC_GUI_COLOR_PATTERN_ACTIVE_HI1";
    strings["Note (highlight 2)##CC_GUI_COLOR_PATTERN_ACTIVE_HI2"].plurals[0] = "Нота (подсветка 2)##CC_GUI_COLOR_PATTERN_ACTIVE_HI2";
    strings["Blank##CC_GUI_COLOR_PATTERN_INACTIVE"].plurals[0] = "Пустая ячейка##CC_GUI_COLOR_PATTERN_INACTIVE";
    strings["Blank (highlight 1)##CC_GUI_COLOR_PATTERN_INACTIVE_HI1"].plurals[0] = "Пустая ячейка (подсветка 1)##CC_GUI_COLOR_PATTERN_INACTIVE_HI1";
    strings["Blank (highlight 2)##CC_GUI_COLOR_PATTERN_INACTIVE_HI2"].plurals[0] = "Пустая ячейка (подсветка 2)##CC_GUI_COLOR_PATTERN_INACTIVE_HI2";
    strings["Instrument##CC_GUI_COLOR_PATTERN_INS"].plurals[0] = "Инструмент##CC_GUI_COLOR_PATTERN_INS";
    strings["Instrument (invalid type)##CC_GUI_COLOR_PATTERN_INS_WARN"].plurals[0] = "Инструмент (неправильный тип)##CC_GUI_COLOR_PATTERN_INS_WARN";
    strings["Instrument (out of range)##CC_GUI_COLOR_PATTERN_INS_ERROR"].plurals[0] = "Инструмент (индекс не соответствует существующему инструменту)##CC_GUI_COLOR_PATTERN_INS_ERROR";
    strings["Volume (0%)##CC_GUI_COLOR_PATTERN_VOLUME_MIN"].plurals[0] = "Głośność (0%)##CC_GUI_COLOR_PATTERN_VOLUME_MIN";
    strings["Volume (50%)##CC_GUI_COLOR_PATTERN_VOLUME_HALF"].plurals[0] = "Głośność (50%)##CC_GUI_COLOR_PATTERN_VOLUME_HALF";
    strings["Volume (100%)##CC_GUI_COLOR_PATTERN_VOLUME_MAX"].plurals[0] = "Głośność (100%)##CC_GUI_COLOR_PATTERN_VOLUME_MAX";
    strings["Invalid effect##CC_GUI_COLOR_PATTERN_EFFECT_INVALID"].plurals[0] = "Неправильный индекс эффекта##CC_GUI_COLOR_PATTERN_EFFECT_INVALID";
    strings["Pitch effect##CC_GUI_COLOR_PATTERN_EFFECT_PITCH"].plurals[0] = "Эффект (частота)##CC_GUI_COLOR_PATTERN_EFFECT_PITCH";
    strings["Volume effect##CC_GUI_COLOR_PATTERN_EFFECT_VOLUME"].plurals[0] = "Эффект (громкость)##CC_GUI_COLOR_PATTERN_EFFECT_VOLUME";
    strings["Panning effect##CC_GUI_COLOR_PATTERN_EFFECT_PANNING"].plurals[0] = "Эффект (панорамирование)##CC_GUI_COLOR_PATTERN_EFFECT_PANNING";
    strings["Song effect##CC_GUI_COLOR_PATTERN_EFFECT_SONG"].plurals[0] = "Эффект (трек)##CC_GUI_COLOR_PATTERN_EFFECT_SONG";
    strings["Time effect##CC_GUI_COLOR_PATTERN_EFFECT_TIME"].plurals[0] = "Эффект (время)##CC_GUI_COLOR_PATTERN_EFFECT_TIME";
    strings["Speed effect##CC_GUI_COLOR_PATTERN_EFFECT_SPEED"].plurals[0] = "Эффект (громкость)##CC_GUI_COLOR_PATTERN_EFFECT_SPEED";
    strings["Primary specific effect##CC_GUI_COLOR_PATTERN_EFFECT_SYS_PRIMARY"].plurals[0] = "Основной эффект чипа##CC_GUI_COLOR_PATTERN_EFFECT_SYS_PRIMARY";
    strings["Secondary specific effect##CC_GUI_COLOR_PATTERN_EFFECT_SYS_SECONDARY"].plurals[0] = "Вспомогательный эффект чипа##CC_GUI_COLOR_PATTERN_EFFECT_SYS_SECONDARY";
    strings["Miscellaneous##CC_GUI_COLOR_PATTERN_EFFECT_MISC"].plurals[0] = "Эффект (рзное)##CC_GUI_COLOR_PATTERN_EFFECT_MISC";
    strings["External command output##CC_GUI_COLOR_EE_VALUE"].plurals[0] = "Вывод внешней команды##CC_GUI_COLOR_EE_VALUE";
    strings["Status: off/disabled##CC_GUI_COLOR_PATTERN_STATUS_OFF"].plurals[0] = "Статус: выкл./отключён##CC_GUI_COLOR_PATTERN_STATUS_OFF";
    strings["Status: off + macro rel##CC_GUI_COLOR_PATTERN_STATUS_REL"].plurals[0] = "Статус: выкл. + релиз макроса##CC_GUI_COLOR_PATTERN_STATUS_REL";
    strings["Status: on + macro rel##CC_GUI_COLOR_PATTERN_STATUS_REL_ON"].plurals[0] = "Статус: вкл. + релиз макроса##CC_GUI_COLOR_PATTERN_STATUS_REL_ON";
    strings["Status: on##CC_GUI_COLOR_PATTERN_STATUS_ON"].plurals[0] = "Статус: вкл.##CC_GUI_COLOR_PATTERN_STATUS_ON";
    strings["Status: volume##CC_GUI_COLOR_PATTERN_STATUS_VOLUME"].plurals[0] = "Статус: громкость##CC_GUI_COLOR_PATTERN_STATUS_VOLUME";
    strings["Status: pitch##CC_GUI_COLOR_PATTERN_STATUS_PITCH"].plurals[0] = "Статус: частота##CC_GUI_COLOR_PATTERN_STATUS_PITCH";
    strings["Status: panning##CC_GUI_COLOR_PATTERN_STATUS_PANNING"].plurals[0] = "Статус: панорамирование##CC_GUI_COLOR_PATTERN_STATUS_PANNING";
    strings["Status: chip (primary)##CC_GUI_COLOR_PATTERN_STATUS_SYS1"].plurals[0] = "Статус: основной эффект чипа##CC_GUI_COLOR_PATTERN_STATUS_SYS1";
    strings["Status: chip (secondary)##CC_GUI_COLOR_PATTERN_STATUS_SYS2"].plurals[0] = "Статус: вспомогательный эффект чипа##CC_GUI_COLOR_PATTERN_STATUS_SYS2";
    strings["Status: mixing##CC_GUI_COLOR_PATTERN_STATUS_MIXING"].plurals[0] = "Статус: микширование##CC_GUI_COLOR_PATTERN_STATUS_MIXING";
    strings["Status: DSP effect##CC_GUI_COLOR_PATTERN_STATUS_DSP"].plurals[0] = "Статус: эффект ЦОС##CC_GUI_COLOR_PATTERN_STATUS_DSP";
    strings["Status: note altering##CC_GUI_COLOR_PATTERN_STATUS_NOTE"].plurals[0] = "Статус: изменение ноты##CC_GUI_COLOR_PATTERN_STATUS_NOTE";
    strings["Status: misc color 1##CC_GUI_COLOR_PATTERN_STATUS_MISC1"].plurals[0] = "Статус: разное (цвет 1)##CC_GUI_COLOR_PATTERN_STATUS_MISC1";
    strings["Status: misc color 2##CC_GUI_COLOR_PATTERN_STATUS_MISC2"].plurals[0] = "Статус: разное (цвет 2)##CC_GUI_COLOR_PATTERN_STATUS_MISC2";
    strings["Status: misc color 3##CC_GUI_COLOR_PATTERN_STATUS_MISC3"].plurals[0] = "Статус: разное (цвет 3)##CC_GUI_COLOR_PATTERN_STATUS_MISC3";
    strings["Status: attack##CC_GUI_COLOR_PATTERN_STATUS_ATTACK"].plurals[0] = "Статус: атака##CC_GUI_COLOR_PATTERN_STATUS_ATTACK";
    strings["Status: decay##CC_GUI_COLOR_PATTERN_STATUS_DECAY"].plurals[0] = "Статус: спад##CC_GUI_COLOR_PATTERN_STATUS_DECAY";
    strings["Status: sustain##CC_GUI_COLOR_PATTERN_STATUS_SUSTAIN"].plurals[0] = "Статус: сустейн##CC_GUI_COLOR_PATTERN_STATUS_SUSTAIN";
    strings["Status: release##CC_GUI_COLOR_PATTERN_STATUS_RELEASE"].plurals[0] = "Статус: релиз##CC_GUI_COLOR_PATTERN_STATUS_RELEASE";
    strings["Status: decrease linear##CC_GUI_COLOR_PATTERN_STATUS_DEC_LINEAR"].plurals[0] = "Статус: линейное уменьшение##CC_GUI_COLOR_PATTERN_STATUS_DEC_LINEAR";
    strings["Status: decrease exp##CC_GUI_COLOR_PATTERN_STATUS_DEC_EXP"].plurals[0] = "Статус: экспоненциальное уменьшение##CC_GUI_COLOR_PATTERN_STATUS_DEC_EXP";
    strings["Status: increase##CC_GUI_COLOR_PATTERN_STATUS_INC"].plurals[0] = "Статус: увеличение##CC_GUI_COLOR_PATTERN_STATUS_INC";
    strings["Status: bent##CC_GUI_COLOR_PATTERN_STATUS_BENT"].plurals[0] = "Status: изменена частота##CC_GUI_COLOR_PATTERN_STATUS_BENT";
    strings["Status: direct##CC_GUI_COLOR_PATTERN_STATUS_DIRECT"].plurals[0] = "Статус: прямой##CC_GUI_COLOR_PATTERN_STATUS_DIRECT";

    strings["Background##CC_GUI_COLOR_SAMPLE_BG"].plurals[0] = "Tło##CC_GUI_COLOR_SAMPLE_BG";
    strings["Waveform##CC_GUI_COLOR_SAMPLE_FG"].plurals[0] = "Kształt fali##CC_GUI_COLOR_SAMPLE_FG";
    strings["Time background##CC_GUI_COLOR_SAMPLE_TIME_BG"].plurals[0] = "Фон поля времени##CC_GUI_COLOR_SAMPLE_TIME_BG";
    strings["Time text##CC_GUI_COLOR_SAMPLE_TIME_FG"].plurals[0] = "Текст поля времени##CC_GUI_COLOR_SAMPLE_TIME_FG";
    strings["Loop region##CC_GUI_COLOR_SAMPLE_LOOP"].plurals[0] = "Зацикленная часть##CC_GUI_COLOR_SAMPLE_LOOP";
    strings["Center guide##CC_GUI_COLOR_SAMPLE_CENTER"].plurals[0] = "Центральная полоса##CC_GUI_COLOR_SAMPLE_CENTER";
    strings["Grid##CC_GUI_COLOR_SAMPLE_GRID"].plurals[0] = "Сетка##CC_GUI_COLOR_SAMPLE_GRID";
    strings["Selection##CC_GUI_COLOR_SAMPLE_SEL"].plurals[0] = "Выделение##CC_GUI_COLOR_SAMPLE_SEL";
    strings["Selection points##CC_GUI_COLOR_SAMPLE_SEL_POINT"].plurals[0] = "Границы выделения##CC_GUI_COLOR_SAMPLE_SEL_POINT";
    strings["Preview needle##CC_GUI_COLOR_SAMPLE_NEEDLE"].plurals[0] = "Курсор воспроизведения превью##CC_GUI_COLOR_SAMPLE_NEEDLE";
    strings["Playing needles##CC_GUI_COLOR_SAMPLE_NEEDLE_PLAYING"].plurals[0] = "Курсоры воспроизведения##CC_GUI_COLOR_SAMPLE_NEEDLE_PLAYING";
    strings["Loop markers##CC_GUI_COLOR_SAMPLE_LOOP_POINT"].plurals[0] = "Маркеры зацикливания##CC_GUI_COLOR_SAMPLE_LOOP_POINT";
    strings["Chip select: disabled##CC_GUI_COLOR_SAMPLE_CHIP_DISABLED"].plurals[0] = "Выбор чипа: выкл.##CC_GUI_COLOR_SAMPLE_CHIP_DISABLED";
    strings["Chip select: enabled##CC_GUI_COLOR_SAMPLE_CHIP_ENABLED"].plurals[0] = "Выбор чипа: вкл.##CC_GUI_COLOR_SAMPLE_CHIP_ENABLED";
    strings["Chip select: enabled (failure)##CC_GUI_COLOR_SAMPLE_CHIP_WARNING"].plurals[0] = "Выбор чипа: вкл. (ошибка)##CC_GUI_COLOR_SAMPLE_CHIP_WARNING";

    strings["Unallocated##CC_GUI_COLOR_PAT_MANAGER_NULL"].plurals[0] = "Паттерн не используется и память под него не выделена##CC_GUI_COLOR_PAT_MANAGER_NULL";
    strings["Unused##CC_GUI_COLOR_PAT_MANAGER_UNUSED"].plurals[0] = "Паттерн не используется##CC_GUI_COLOR_PAT_MANAGER_UNUSED";
    strings["Used##CC_GUI_COLOR_PAT_MANAGER_USED"].plurals[0] = "Паттерн используется##CC_GUI_COLOR_PAT_MANAGER_USED";
    strings["Overused##CC_GUI_COLOR_PAT_MANAGER_OVERUSED"].plurals[0] = "Паттерн используется очень часто##CC_GUI_COLOR_PAT_MANAGER_OVERUSED";
    strings["Really overused##CC_GUI_COLOR_PAT_MANAGER_EXTREMELY_OVERUSED"].plurals[0] = "Паттерн используется крайне часто##CC_GUI_COLOR_PAT_MANAGER_EXTREMELY_OVERUSED";
    strings["Combo Breaker##CC_GUI_COLOR_PAT_MANAGER_COMBO_BREAKER"].plurals[0] = "Число использований паттерна больше, чем длина трека!##CC_GUI_COLOR_PAT_MANAGER_COMBO_BREAKER";

    strings["Background##CC_GUI_COLOR_PIANO_BACKGROUND"].plurals[0] = "Фон##CC_GUI_COLOR_PIANO_BACKGROUND";
    strings["Upper key##CC_GUI_COLOR_PIANO_KEY_TOP"].plurals[0] = "Верхние клавиши##CC_GUI_COLOR_PIANO_KEY_TOP";
    strings["Upper key (feedback)##CC_GUI_COLOR_PIANO_KEY_TOP_HIT"].plurals[0] = "Верхние клавиши (обратная связь)##CC_GUI_COLOR_PIANO_KEY_TOP_HIT";
    strings["Upper key (pressed)##CC_GUI_COLOR_PIANO_KEY_TOP_ACTIVE"].plurals[0] = "Верхние клавиши (нажатые)##CC_GUI_COLOR_PIANO_KEY_TOP_ACTIVE";
    strings["Lower key##CC_GUI_COLOR_PIANO_KEY_BOTTOM"].plurals[0] = "Нижние клавиши##CC_GUI_COLOR_PIANO_KEY_BOTTOM";
    strings["Lower key (feedback)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_HIT"].plurals[0] = "Нижние клавиши (обратная связь)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_HIT";
    strings["Lower key (pressed)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_ACTIVE"].plurals[0] = "Нижние клавиши (нажатые)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_ACTIVE";

    strings["Clock text##CC_GUI_COLOR_CLOCK_TEXT"].plurals[0] = "Текст часов##CC_GUI_COLOR_CLOCK_TEXT";
    strings["Beat (off)##CC_GUI_COLOR_CLOCK_BEAT_LOW"].plurals[0] = "Слабая доля##CC_GUI_COLOR_CLOCK_BEAT_LOW";
    strings["Beat (on)##CC_GUI_COLOR_CLOCK_BEAT_HIGH"].plurals[0] = "Сильная доля##CC_GUI_COLOR_CLOCK_BEAT_HIGH";

    strings["PortSet##CC_GUI_COLOR_PATCHBAY_PORTSET"].plurals[0] = "grupa portów##CC_GUI_COLOR_PATCHBAY_PORTSET";
    strings["Port##CC_GUI_COLOR_PATCHBAY_PORT"].plurals[0] = "Port##CC_GUI_COLOR_PATCHBAY_PORT";
    strings["Port (hidden/unavailable)##CC_GUI_COLOR_PATCHBAY_PORT_HIDDEN"].plurals[0] = "Port (ukryty/niedostępny)##CC_GUI_COLOR_PATCHBAY_PORT_HIDDEN";
    strings["Connection (selected)##CC_GUI_COLOR_PATCHBAY_CONNECTION"].plurals[0] = "Соединение (выделенное)##CC_GUI_COLOR_PATCHBAY_CONNECTION";
    strings["Connection (other)##CC_GUI_COLOR_PATCHBAY_CONNECTION_BG"].plurals[0] = "Соединение (обычное)##CC_GUI_COLOR_PATCHBAY_CONNECTION_BG";

    strings["Log level: Error##CC_GUI_COLOR_LOGLEVEL_ERROR"].plurals[0] = "Уровень лога: ошибка##CC_GUI_COLOR_LOGLEVEL_ERROR";
    strings["Log level: Warning##CC_GUI_COLOR_LOGLEVEL_WARNING"].plurals[0] = "Уровень лога: предупреждение##CC_GUI_COLOR_LOGLEVEL_WARNING";
    strings["Log level: Info##CC_GUI_COLOR_LOGLEVEL_INFO"].plurals[0] = "Уровень лога: информация##CC_GUI_COLOR_LOGLEVEL_INFO";
    strings["Log level: Debug##CC_GUI_COLOR_LOGLEVEL_DEBUG"].plurals[0] = "Уровень лога: отладка##CC_GUI_COLOR_LOGLEVEL_DEBUG";
    strings["Log level: Trace/Verbose##CC_GUI_COLOR_LOGLEVEL_TRACE"].plurals[0] = "Уровень лога: диагностика/подробный##CC_GUI_COLOR_LOGLEVEL_TRACE";

    strings["OK##SettingsOK"].plurals[0] = "OK##SettingsOK";
    strings["Cancel##SettingsCancel"].plurals[0] = "Anuluj##SettingsCancel";
    strings["Apply##SettingsApply"].plurals[0] = "Zastosuj##SettingsApply";

    //src/gui/util.cpp

    strings["<nothing>##sgut"].plurals[0] = "<brak>";
    strings["Unknown##sgut0"].plurals[0] = "Nieznany";
    strings["Unknown##sgut1"].plurals[0] = "Nieznane";
    
    //   sgiPCMA  src/gui/inst/adpcma.cpp

    strings["Macros##sgiPCMA"].plurals[0] = "Makra";
    strings["Volume##sgiPCMA"].plurals[0] = "Głośność";
    strings["Global Volume##sgiPCMA"].plurals[0] = "Globalna głośność";
    strings["Panning##sgiPCMA"].plurals[0] = "Panning";
    strings["Phase Reset##sgiPCMA"].plurals[0]  = "Reset fazy";

    //   sgiPCMB   src/gui/inst/adpcmb.cpp

    strings["Macros##sgiPCMB"].plurals[0] = "Makra";
    strings["Volume##sgiPCMB"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiPCMB"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiPCMB"].plurals[0] = "Wysokość";
    strings["Panning##sgiPCMB"].plurals[0] = "Panning";
    strings["Phase Reset##sgiPCMB"].plurals[0]  = "Reset fazy";

    //   sgiSAMPLE src/gui/inst/amiga.cpp

    strings["Macros##sgiSAMPLE"].plurals[0] = "Makra";
    strings["Volume##sgiSAMPLE"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiSAMPLE"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiSAMPLE"].plurals[0] = "Wysokość";
    strings["Panning##sgiSAMPLE"].plurals[0] = "Panning";
    strings["Panning (left)##sgiSAMPLE"].plurals[0] = "Panning (lewo)";
    strings["Surround##sgiSAMPLE"].plurals[0] = "Dzwiek przestrzenny";
    strings["Panning (right)##sgiSAMPLE"].plurals[0] = "Panning (prawo)";
    strings["Waveform##sgiSAMPLE"].plurals[0] = "Fala";
    strings["Phase Reset##sgiSAMPLE"].plurals[0]  = "Reset fazy";

    //   sgiAY     src/gui/inst/ay.cpp

    strings["Macros##sgiAY"].plurals[0] = "Makra";
    strings["Volume##sgiAY"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiAY"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiAY"].plurals[0] = "Wysokość";
    strings["Noise Freq##sgiAY"].plurals[0] = "Czestotliwosc szumu";
    strings["Waveform##sgiAY"].plurals[0] = "Kształt fali";
    strings["Phase Reset##sgiAY"].plurals[0]  = "Reset fazy";
    strings["Envelope##sgiAY"].plurals[0] = "Obwiednia";
    strings["AutoEnv Num##sgiAY"].plurals[0] = "Licznik czest. auto-obw.";
    strings["AutoEnv Den##sgiAY"].plurals[0] = "Mianownik czest. auto-obw.";

    //   sgi8930   src/gui/inst/ay8930.cpp

    strings["Macros##sgi8930"].plurals[0] = "Makra";
    strings["Volume##sgi8930"].plurals[0] = "Głośność";
    strings["Arpeggio##sgi8930"].plurals[0] = "Arpeggio";
    strings["Pitch##sgi8930"].plurals[0] = "Wysokość";
    strings["Noise Freq##sgi8930"].plurals[0] = "Czestotliwosc szumu";
    strings["Waveform##sgi8930"].plurals[0] = "Kształt fali";
    strings["Phase Reset##sgi8930"].plurals[0]  = "Reset fazy";
    strings["Duty##sgi8930"].plurals[0] = "Szerokość pulsu";
    strings["Envelope##sgi8930"].plurals[0] = "Obwiednia";
    strings["AutoEnv Num##sgi8930"].plurals[0] = "Licznik. częst. аuto-obwiedni";
    strings["AutoEnv Den##sgi8930"].plurals[0] = "Mianownik. częst. аuto-obwiedni";
    strings["Noise AND Mask##sgi8930"].plurals[0] = "Maska szumu (logiczne AND)";
    strings["Noise OR Mask##sgi8930"].plurals[0] = "Maska szumu (logiczne OR)";
    strings["Macros##sgiB"].plurals[0] = "Makra";
    strings["Volume##sgiB"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiB"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiB"].plurals[0] = "Wysokość";
    strings["Pulse Width##sgiB"].plurals[0] = "Szerokość pulsu";

    //   sgiC140   src/gui/inst/c140.cpp

    strings["Macros##sgiC140"].plurals[0] = "Makra";
    strings["Volume##sgiC140"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiC140"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiC140"].plurals[0] = "Wysokość";
    strings["Panning (left)##sgiC140"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiC140"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiC140"].plurals[0] = "Reset fazy";

    //   sgiC219   src/gui/inst/c219.cpp

    strings["Macros##sgiC219"].plurals[0] = "Makra";
    strings["Volume##sgiC219"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiC219"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiC219"].plurals[0] = "Wysokość";
    strings["Control##sgiC219"].plurals[0] = "Sterowanie";
    strings["Panning (left)##sgiC219"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiC219"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiC219"].plurals[0] = "Reset fazy";

    //   sgiC64    src/gui/inst/c64.cpp

    strings["Waveform##sgiC640"].plurals[0] = "Kształt fali";
    strings["tri##sgiC64"].plurals[0] = "trojkatna";
    strings["saw##sgiC64"].plurals[0] = "piłokształtna";
    strings["pulse##sgiC64"].plurals[0] = "kwadratowa";
    strings["noise##sgiC64"].plurals[0] = "szum";
    strings["A##sgiC640"].plurals[0] = "A";
    strings["A##sgiC641"].plurals[0] = "A";
    strings["D##sgiC640"].plurals[0] = "D";
    strings["D##sgiC641"].plurals[0] = "D";
    strings["S##sgiC640"].plurals[0] = "S";
    strings["S##sgiC641"].plurals[0] = "S";
    strings["R##sgiC640"].plurals[0] = "R";
    strings["R##sgiC641"].plurals[0] = "R";
    strings["Envelope##sgiC640"].plurals[0] = "Obwiednia";
    strings["Envelope##sgiC641"].plurals[0] = "Obwiednia";
    strings["Duty##sgiC640"].plurals[0] = "Szerokość pulsu";
    strings["Ring Modulation##sgiC64"].plurals[0] = "Modulacja kolowa";
    strings["Oscillator Sync##sgiC64"].plurals[0] = "Synchronizacja oscylotorow";
    strings["Enable filter##sgiC64"].plurals[0] = "Wlacz filtr";
    strings["Initialize filter##sgiC64"].plurals[0] = "Inicjalizuj filtr";
    strings["Cutoff##sgiC640"].plurals[0] = "Punkt odciecia";
    strings["Resonance##sgiC640"].plurals[0] = "Rezonans)";
    strings["Filter Mode##sgiC640"].plurals[0] = "typ filtra";
    strings["low##sgiC64"].plurals[0] = "dolno";
    strings["band##sgiC64"].plurals[0] = "środk.";
    strings["high##sgiC64"].plurals[0] = "górno";
    strings["ch3off##sgiC64"].plurals[0] = "wyl. kanał 3";
    strings["Absolute Cutoff Macro##sgiC64"].plurals[0] = "Absolutne makro punktu odcięcia";
    strings["Absolute Duty Macro##sgiC64"].plurals[0] = "Absolutne makro szerokości pulsu";
    strings["Don't test before new note##sgiC64"].plurals[0] = "Nie włączaj bitu testowego przed nową nutą";
    strings["Macros##sgiC64"].plurals[0] = "Makra";
    strings["Volume##sgiC64"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiC64"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiC64"].plurals[0] = "Wysokość";
    strings["Duty##sgiC641"].plurals[0] = "Szerokość pulsu";
    strings["Waveform##sgiC641"].plurals[0] = "Kształt fali";
    strings["Cutoff##sgiC641"].plurals[0] = "Punkt odcięcia";
    strings["Filter Mode##sgiC641"].plurals[0] = "Typ filtra";
    strings["Filter Toggle##sgiC64"].plurals[0] = "Wl/Wyl filtr";
    strings["Resonance##sgiC641"].plurals[0] = "Rezonans";
    strings["Special##sgiC64"].plurals[0] = "Specjalne";
    strings["Attack##sgiC64"].plurals[0] = "Atak";
    strings["Decay##sgiC64"].plurals[0] = "Opadanie";
    strings["Sustain##sgiC64"].plurals[0] = "Podtrzymanie";
    strings["Release##sgiC64"].plurals[0] = "Puszczenie";

     //   sgiDAVE   src/gui/inst/dave.cpp

    strings["Macros##sgiDAVE"].plurals[0] = "Makra";
    strings["Volume##sgiDAVE"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiDAVE"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiDAVE"].plurals[0] = "Wysokość";
    strings["Noise Freq##sgiDAVE"].plurals[0] = "Czestotliwosc szumu";
    strings["Waveform##sgiDAVE"].plurals[0] = "Kształt fali";
    strings["Panning (left)##sgiDAVE"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiDAVE"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiDAVE"].plurals[0] = "Reset fazy";
    strings["Control##sgiDAVE"].plurals[0] = "Sterowanie";

    //   sgi5503   src/gui/inst/es5503.cpp

    strings["Oscillator mode:##sgi5503"].plurals[0] = "Tryb oscylatora:";
    strings["Freerun##sgi5503"].plurals[0] = "Swobodny";
    strings["Oneshot##sgi5503"].plurals[0] = "Jednokrotny";
    strings["Sync/AM##sgi5503"].plurals[0] = "Synchro./AM";
    strings["Swap##sgi5503"].plurals[0] = "Zamiana";
    strings["Virtual softpan channel##sgi5503"].plurals[0] = "Wirtualny kanał stereo";
    strings["Combines odd and next even channel into one virtual channel with 256-step panning.\nInstrument, volume and effects need to be placed on the odd channel (e.g. 1st, 3rd, 5th etc.)##sgi5503"].plurals[0] = "Wykorzystuje kanał nieparzysty i następujący po nim kanał parzysty do utworzenia kanału wirtualnego z możliwością płynnego panningu (256 kroków).\nNuty, instrumenty, polecenia głośności i efekty powinny być umieszczane w kanałach o numerach nieparzystych (1., 3. itd.).";
    strings["Phase reset on key-on##sgi5503"].plurals[0] = "Reset fazy przy nowej nucie";
    strings["Macros##sgi5503"].plurals[0] = "Makra";
    strings["Volume##sgi5503"].plurals[0] = "Głośność";
    strings["Arpeggio##sgi5503"].plurals[0] = "Arpeggio";
    strings["Pitch##sgi5503"].plurals[0] = "Wysokość";
    strings["Osc. mode##sgi5503"].plurals[0] = "Tryb oscyl.";
    strings["Panning (left)##sgi5503"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgi5503"].plurals[0] = "Panning (prawo)";
    strings["Waveform##sgi5503"].plurals[0] = "Fala";
    strings["Phase Reset##sgi5503"].plurals[0] = "Reset fazy";
    strings["Wave/sample pos.##sgi5503"].plurals[0] = "Pozycja fali/sampla";
    strings["Osc. output##sgi5503"].plurals[0] = "Wyjście oscyl.";

    //   sgiOTTO   src/gui/inst/es5506.cpp

    strings["Filter Mode##sgiOTTO0"].plurals[0] = "Tryb filtra";
    strings["Filter K1##sgiOTTO0"].plurals[0] = "K1 filtra";
    strings["Filter K2##sgiOTTO0"].plurals[0] = "K2 filtra";
    strings["Envelope length##sgiOTTO"].plurals[0] = "Długośc obwiedni";
    strings["Left Volume Ramp##sgiOTTO"].plurals[0] = "Zwiększenie głośności lewej strony.";
    strings["Right Volume Ramp##sgiOTTO"].plurals[0] = "Zwiększenie głośności prawej strony.";
    strings["Filter K1 Ramp##sgiOTTO"].plurals[0] = "Narastanie obw. K1 filtra";
    strings["Filter K2 Ramp##sgiOTTO"].plurals[0] = "Narastanie obw. K2 filtra";
    strings["K1 Ramp Slowdown##sgiOTTO"].plurals[0] = "Spowolnienie obw. K1";
    strings["K2 Ramp Slowdown##sgiOTTO"].plurals[0] = "Spowolnienie obw. K2";
    strings["Macros##sgiOTTO"].plurals[0] = "Makra";
    strings["Volume##sgiOTTO"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiOTTO"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiOTTO"].plurals[0] = "Wysokość";
    strings["Panning (left)##sgiOTTO"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiOTTO"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiOTTO"].plurals[0] = "Reset fazy";
    strings["Filter Mode##sgiOTTO1"].plurals[0] = "Tryb filtra";
    strings["Filter K1##sgiOTTO1"].plurals[0] = "K1 filtra";
    strings["Filter K2##sgiOTTO1"].plurals[0] = "K2 filtra";
    strings["Outputs##sgiOTTO"].plurals[0] = "Wyjście";
    strings["Control##sgiOTTO"].plurals[0] = "Sterowanie";

    //   sgiESFM   src/gui/inst/esfm.cpp

    strings["Other##sgiESFM0"].plurals[0] = "Inne";
    strings["Other##sgiESFM1"].plurals[0] = "Inne";
    strings["Envelope##sgiESFM0"].plurals[0] = "Obwiednia";
    strings["Envelope##sgiESFM1"].plurals[0] = "Obwiednia";
    strings["op%d##sgiESFM0"].plurals[0] = "op%d";
    strings["OP%d##sgiESFM1"].plurals[0] = "OP%d";
    strings["Detune in semitones##sgiESFM0"].plurals[0] = "Rozstrojenie w półtonach";
    strings["Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.##sgiESFM0"].plurals[0] = "Rozstrojenie w ułamkach półtonu.\n128 = +1 półton, -128 = -1 półton.";
    strings["If operator outputs sound, enable left channel output.##sgiESFM0"].plurals[0] = "włącz wyjście audio dla lewego kanału.";
    strings["If operator outputs sound, enable right channel output.##sgiESFM0"].plurals[0] = "włącz wyjście audio dla prawego kanału.";
    strings["Block##sgiESFM0"].plurals[0] = "Blok";
    strings["FreqNum##sgiESFM0"].plurals[0] = "FreqNum";
    strings["op%d##sgiESFM2"].plurals[0] = "op%d";
    strings["Operator %d##sgiESFM"].plurals[0] = "Operator %d";
    strings["Waveform##sgiESFM"].plurals[0] = "Kształt fali";
    strings["Envelope##sgiESFM"].plurals[0] = "Obwiednia";
    strings["Blk##sgiESFM"].plurals[0] = "Blk";
    strings["Block##sgiESFM1"].plurals[0] = "Blok";
    strings["F##sgiESFM"].plurals[0] = "F";
    strings["Frequency (F-Num)##sgiESFM"].plurals[0] = "Wysokość (F-Num)";
    strings["Detune in semitones##sgiESFM1"].plurals[0] = "Rozstrojenie w półtonach";
    strings["Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.##sgiESFM1"].plurals[0] = "Rozstrojenie w ułamkach półtonu.\n128 = +1 półton, -128 = -1 półton.";
    strings["If operator outputs sound, enable left channel output.##sgiESFM1"].plurals[0] = "włącz wyjście audio dla lewego kanału.";
    strings["If operator outputs sound, enable right channel output.##sgiESFM1"].plurals[0] = "włącz wyjście audio dla prawego kanału.";
    strings["op%d##sgiESFM3"].plurals[0] = "op%d";
    strings["OP%d##sgiESFM4"].plurals[0] = "OP%d";
    strings["Block##sgiESFM2"].plurals[0] = "Blok";
    strings["FreqNum##sgiESFM1"].plurals[0] = "FreqNum";
    strings["Detune in semitones##sgiESFM2"].plurals[0] = "Rozstrojenie w półtonach";
    strings["Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.##sgiESFM2"].plurals[0] = "Rozstrojenie w ułamkach półtonu.\n128 = +1 półton, -128 = -1 półton.";
    strings["If operator outputs sound, enable left channel output.##sgiESFM2"].plurals[0] = "włącz wyjście audio dla lewego kanału.";
    strings["If operator outputs sound, enable right channel output.##sgiESFM2"].plurals[0] = "włącz wyjście audio dla prawego kanału.";
    strings["OP%d Macros##sgiESFM"].plurals[0] = "Makra op.%d";
    strings["Block##sgiESFM3"].plurals[0] = "Blok";
    strings["FreqNum##sgiESFM2"].plurals[0] = "FreqNum";
    strings["Op. Arpeggio##sgiESFM"].plurals[0] = "Arpeggio operatora";
    strings["Op. Pitch##sgiESFM"].plurals[0] = "Wysokość operatora";
    strings["Op. Panning##sgiESFM"].plurals[0] = "Panning operatora";
    strings["Macros##sgiESFM"].plurals[0] = "Makra";
    strings["Volume##sgiESFM"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiESFM"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiESFM"].plurals[0] = "Wysokość";
    strings["OP4 Noise Mode##sgiESFM"].plurals[0] = "Tryb szumu OP4";
    strings["Panning##sgiESFM"].plurals[0] = "Panning";
    strings["Phase Reset##sgiESFM"].plurals[0] = "Reset fazy";

    //   sgiFDS    src/gui/inst/fds.cpp

    strings["Compatibility mode##sgiFDS"].plurals[0] = "Tryb kompatybilnosci";
    strings["only use for compatibility with .dmf modules!\n- initializes modulation table with first wavetable\n- does not alter modulation parameters on instrument change##sgiFDS"].plurals[0] = "tylko dla kompatybilności z modułami .dmf!\n- inicjalizuje tablice modulatora wraz z pierwszą tablica fal\n- nie zmienia parametrów modulacji przy zmianie instrumentu";
    strings["Modulation depth##sgiFDS"].plurals[0] = "Glebokosc modulacji";
    strings["Modulation speed##sgiFDS"].plurals[0] = "Szybkosc modulacji";
    strings["Modulation table##sgiFDS"].plurals[0] = "Tabela modulacji";
    strings["Macros##sgiFDS"].plurals[0] = "Makra";
    strings["Volume##sgiFDS"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiFDS"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiFDS"].plurals[0] = "Wysokość";
    strings["Waveform##sgiFDS"].plurals[0] = "Fala";
    strings["Mod Depth##sgiFDS"].plurals[0] = "Glebokosc mod..";
    strings["Mod Speed##sgiFDS"].plurals[0] = "Szybkosc mod.";
    strings["Mod Position##sgiFDS"].plurals[0] = "Polozenie mod.";

    //   sgifmeu   src/gui/inst/fmEnvUtil.cpp

    strings["left click to restart\nmiddle click to pause\nright click to see algorithm##sgifmeu"].plurals[0] = "LPM aby zrestartować\nSPM żeby zatrzymać\nPPM, aby przełączyć na podgląd algorytmu";
    strings["left click to configure TL scaling\nright click to see FM preview##sgifmeu"].plurals[0] = "LPM by skonfigurować skalowanie TL operatora\nPPM, aby przełączyć na podgląd sygnału FM";
    strings["right click to see FM preview##sgifmeu"].plurals[0] = "PPM, aby przełączyć na podgląd sygnału FM";
    strings["operator level changes with volume?##sgifmeu"].plurals[0] = "poziom opeartora ma się zmieniać wraz z głośnością?";
    strings["AUTO##OPKVS"].plurals[0] = "AUTO##OPKVS";
    strings["NO##OPKVS"].plurals[0] = "NIE##OPKVS";
    strings["YES##OPKVS"].plurals[0] = "TAK##OPKVS";

    //   sgifmeh   src/gui/inst/fmEnvUtil.h

    strings["(copying)##sgifmeh"].plurals[0] = "(kopiowanie)";
    strings["(swapping)##sgifmeh"].plurals[0] = "(zamiana)";
    strings["- drag to swap operator\n- shift-drag to copy operator##sgifmeh"].plurals[0] = "- przeciągnij i upuść, aby zamienić parametry operatora miesjcami\n- przeciągnij i upuść z wciśniętym SHIFT, aby skopiować parametry operatora";

    //   sgiGA20   src/gui/inst/ga20.cpp

    strings["Macros##sgiGA20"].plurals[0] = "Makra";
    strings["Volume##sgiGA20"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiGA20"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiGA20"].plurals[0] = "Wysokość";
    strings["Phase Reset##sgiGA20"].plurals[0] = "Reset fazy";
    
    //   sgiGB     src/gui/inst/gb.cpp

    strings["Game Boy##sgiGB"].plurals[0] = "Game Boy";
    strings["Use software envelope##sgiGB"].plurals[0] = "Uzywaj obwiedni sprzetowej";
    strings["Initialize envelope on every note##sgiGB"].plurals[0] = "Inicjalizuj obwiednie przy kazdej nucie";
    strings["Volume##sgiGB0"].plurals[0] = "Głośność";
    strings["Length##sgiGB"].plurals[0] = "Długość";
    strings["Sound Length##sgiGB0"].plurals[0] = "Dlugość dzwięku";
    strings["Infinity##sgiGB"].plurals[0] = "Nieskończoność";
    strings["Direction##sgiGB"].plurals[0] = "Kierunek";
    strings["Up##sgiGB0"].plurals[0] = "Góra";
    strings["Down##sgiGB0"].plurals[0] = "Dół";
    strings["Hardware Sequence##sgiGB"].plurals[0] = "Sekwencja sprzętowa";
    strings["Tick##sgiGB"].plurals[0] = "Skok";
    strings["Command##sgiGB"].plurals[0] = "Komenda";
    strings["Move/Remove##sgiGB"].plurals[0] = "Przenieś/usuń";
    strings["Volume##sgiGB1"].plurals[0] = "Głośność";
    strings["Env Length##sgiGB"].plurals[0] = "Dlugość obwiedni";
    strings["Sound Length##sgiGB1"].plurals[0] = "Dlugość dzwieku";
    strings["Up##sgiGB1"].plurals[0] = "Góra";
    strings["Down##sgiGB1"].plurals[0] = "Dół";
    strings["Shift##sgiGB"].plurals[0] = "Jak bardzo";
    strings["Speed##sgiGB"].plurals[0] = "Prędkość";
    strings["Up##sgiGB2"].plurals[0] = "Góra";
    strings["Down##sgiGB2"].plurals[0] = "Dól";
    strings["Ticks##sgiGB"].plurals[0] = "Kroki";
    strings["Position##sgiGB"].plurals[0] = "Położenie";
    strings["Macros##sgiGB"].plurals[0] = "Makra";
    strings["Volume##sgiGB2"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiGB"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiGB"].plurals[0] = "Wysokość";
    strings["Duty/Noise##sgiGB"].plurals[0] = "Szerokość pulsu/tryb szumu";
    strings["Waveform##sgiGB"].plurals[0] = "Fala";
    strings["Panning##sgiGB"].plurals[0] = "Panning";
    strings["Phase Reset##sgiGB"].plurals[0] = "Reset fazy";

    //   sgiK00    src/gui/inst/k007232.cpp

    strings["Macros##sgiK00"].plurals[0] = "Makra";
    strings["Volume##sgiK00"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiK00"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiK00"].plurals[0] = "Wysokość";
    strings["Waveform##sgiK00"].plurals[0] = "Fala";
    strings["Panning (left)##sgiK00"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiK00"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiK00"].plurals[0] = "Reset fazy";

    //   sgiK05    src/gui/inst/k053260.cpp

    strings["Macros##sgiK05"].plurals[0] = "Makra";
    strings["Volume##sgiK05"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiK05"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiK05"].plurals[0] = "Wysokość";
    strings["Panning##sgiK05"].plurals[0] = "Panning";
    strings["Phase Reset##sgiK05"].plurals[0] = "Reset fazy";

    //   sgimcd    src/gui/inst/macroDraw.cpp

    strings["Triangle##sgimcd"].plurals[0] = "Fala trójkątna";
    strings["Saw##sgimcd"].plurals[0] = "Fala piłokształtna";
    strings["Square##sgimcd"].plurals[0] = "Fala kwadratowa";
    strings["How did you even##sgimcd0"].plurals[0] = "Jak ci się to w ogóle udało?";
    strings["Bottom##sgimcd0"].plurals[0] = "Min.";
    strings["Top##sgimcd0"].plurals[0] = "Maks.";
    strings["Attack##sgimcd"].plurals[0] = "Atak";
    strings["Sustain##sgimcd"].plurals[0] = "Podtrzymanie";
    strings["Hold##sgimcd"].plurals[0] = "Opóźnienie po ataku";
    strings["SusTime##sgimcd"].plurals[0] = "Długość podtrzymania";
    strings["Decay##sgimcd"].plurals[0] = "Opadanie";
    strings["SusDecay##sgimcd"].plurals[0] = "Opadanie podtrzymania";
    strings["Release##sgimcd"].plurals[0] = "Релиз";
    strings["Bottom##sgimcd1"].plurals[0] = "Min.";
    strings["Top##sgimcd1"].plurals[0] = "Maks.";
    strings["Speed##sgimcd"].plurals[0] = "Prędkość";
    strings["Phase##sgimcd"].plurals[0] = "Faza";
    strings["Shape##sgimcd"].plurals[0] = "Kształt fali";
    strings["Macro type: Sequence##sgimcd"].plurals[0] = "Typ makra: Sekwencja";
    strings["Macro type: ADSR##sgimcd"].plurals[0] = "Typ makra: obwiednia ADSR";
    strings["Macro type: LFO##sgimcd"].plurals[0] = "Typ makra: LFO";
    strings["Macro type: What's going on here?##sgimcd"].plurals[0] = "Typ makra: Co tu sie dzieje?";
    strings["Delay/Step Length##sgimcd"].plurals[0] = "Задержка/длина шага";
    strings["Step Length (ticks)##IMacroSpeed"].plurals[0] = "Длина шага (в шагах движка трекера)##IMacroSpeed";
    strings["Delay##IMacroDelay"].plurals[0] = "Opóźnienie##IMacroDelay";
    strings["Release mode: Active (jump to release pos)##sgimcd"].plurals[0] = "Тип релиза: активный (прыгнуть на позицию релиза)";
    strings["Release mode: Passive (delayed release)##sgimcd"].plurals[0] = "Тип релиза: пассивный (отложенный релиз)";
    strings["Tabs##sgimcd"].plurals[0] = "Zakladki";
    strings["Length##sgimcd"].plurals[0] = "Długość";
    strings["StepLen##sgimcd"].plurals[0] = "Dł. kroku";
    strings["Delay##sgimcd"].plurals[0] = "Opóźnienie";
    strings["The heck? No, this isn't even working correctly...##sgimcd"].plurals[0] = "Что за?.. Нет, оно ведь работает неправильно...";
    strings["The only problem with that selectedMacro is that it's a bug...##sgimcd"].plurals[0] = "Единственная проблема с тем selectedMacro в том, что это не сбой...";
    strings["Single (combo box)##sgimcd"].plurals[0] = "Один (выпадающий список)";

    //   sgiLYNX   src/gui/inst/mikey.cpp

    strings["Macros##sgiLYNX"].plurals[0] = "Makra";
    strings["Volume##sgiLYNX"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiLYNX"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiLYNX"].plurals[0] = "Wysokość";
    strings["Duty/Int##sgiLYNX"].plurals[0] = "Szerokość pulsu/int.";
    strings["Panning (left)##sgiLYNX"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiLYNX"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiLYNX"].plurals[0] = "Reset fazy";

    //   sgi5232   src/gui/inst/msm5232.cpp

    strings["Macros##sgi5232"].plurals[0] = "Makra";
    strings["Volume##sgi5232"].plurals[0] = "Głośność";
    strings["Arpeggio##sgi5232"].plurals[0] = "Arpeggio";
    strings["Pitch##sgi5232"].plurals[0] = "Wysokość";
    strings["Group Ctrl##sgi5232"].plurals[0] = "Sterowanie grupą";
    strings["Group Attack##sgi5232"].plurals[0] = "Atak grupy";
    strings["Group Decay##sgi5232"].plurals[0] = "Opadanie grupy";
    strings["Noise##sgi5232"].plurals[0] = "Szum";

    //   sgi6258   src/gui/inst/msm6258.cpp

    strings["Macros##sgi6258"].plurals[0] = "Makra";
    strings["Frequency Divider##sgi6258"].plurals[0] = "Dzielnik częstotliwości";
    strings["Panning##sgi6258"].plurals[0] = "Panning";
    strings["Phase Reset##sgi6258"].plurals[0] = "Reset fazy";
    strings["Clock Divider##sgi6258"].plurals[0] = "Dzielnik taktowania zegara";

    //   sgi6295   src/gui/inst/msm6295.cpp

    strings["Macros##sgi6295"].plurals[0] = "Makra";
    strings["Volume##sgi6295"].plurals[0] = "Głośność";
    strings["Frequency Divider##sgi6295"].plurals[0] = "Dzielnik częstotliwości";
    strings["Phase Reset##sgi6295"].plurals[0] = "Reset fazy";

    //   sgiMULPCM src/gui/inst/multipcm.cpp

    strings["MultiPCM##sgiMULPCM"].plurals[0] = "MultiPCM";
    strings["AR##sgiMULPCM0"].plurals[0] = "AR";
    strings["AR##sgiMULPCM1"].plurals[0] = "AR";
    strings["Attack Rate##sgiMULPCM"].plurals[0] = "Скорость атаки";
    strings["D1R##sgiMULPCM0"].plurals[0] = "С1С";
    strings["D1R##sgiMULPCM1"].plurals[0] = "С1С";
    strings["Decay 1 Rate##sgiMULPCM"].plurals[0] = "Скорость спада 1";
    strings["DL##sgiMULPCM0"].plurals[0] = "УС";
    strings["DL##sgiMULPCM1"].plurals[0] = "УС";
    strings["Decay Level##sgiMULPCM"].plurals[0] = "Уровень спада";
    strings["D2R##sgiMULPCM0"].plurals[0] = "С2С";
    strings["D2R##sgiMULPCM1"].plurals[0] = "С2С";
    strings["Decay 2 Rate##sgiMULPCM"].plurals[0] = "Скорость спада 2";
    strings["RR##sgiMULPCM0"].plurals[0] = "СР";
    strings["RR##sgiMULPCM1"].plurals[0] = "СР";
    strings["Release Rate##sgiMULPCM"].plurals[0] = "Скорость релиза";
    strings["RC##sgiMULPCM0"].plurals[0] = "КС";
    strings["RC##sgiMULPCM1"].plurals[0] = "КС";
    strings["Rate Correction##sgiMULPCM"].plurals[0] = "Коррекция скорости";
    strings["Envelope##sgiMULPCM0"].plurals[0] = "Obwiednia";
    strings["Envelope##sgiMULPCM1"].plurals[0] = "Obwiednia";
    strings["LFO Rate##sgiMULPCM"].plurals[0] = "Skala LFO";
    strings["PM Depth##sgiMULPCM"].plurals[0] = "Głębokość PM";
    strings["AM Depth##sgiMULPCM"].plurals[0] = "Głębokość AM";
    strings["Macros##sgiMULPCM"].plurals[0] = "Makra";
    strings["Volume##sgiMULPCM"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiMULPCM"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiMULPCM"].plurals[0] = "Wysokość";
    strings["Panning##sgiMULPCM"].plurals[0] = "Panning";
    strings["Phase Reset##sgiMULPCM"].plurals[0] = "Reset fazy";

    //   sgiN163   src/gui/inst/n163.cpp

    strings["Namco 163##sgiN163"].plurals[0] = "Namco 163";
    strings["Load waveform##sgiN163"].plurals[0] = "Wczytaj falę";
    strings["when enabled, a waveform will be loaded into RAM.\nwhen disabled, only the offset and length change.##sgiN163"].plurals[0] = "gdy ta opcja jest włączona, fala zostanie załadowana do pamięci RAM.\nw przeciwnym razie, zmieni się tylko przesunięcie i długość fali.";
    strings["Waveform##WAVE"].plurals[0] = "Fala##WAVE";
    strings["Per-channel wave position/length##sgiN163"].plurals[0] = "Położenie i długość fali oddzielnie dla każdego kanału";
    strings["Ch##sgiN163"].plurals[0] = "Kanał";
    strings["Position##sgiN163"].plurals[0] = "Położenie";
    strings["Length##sgiN163"].plurals[0] = "Długość";
    strings["Position##WAVEPOS"].plurals[0] = "Położenie##WAVEPOS";
    strings["Length##WAVELEN"].plurals[0] = "Długość##WAVELEN";
    strings["Macros##sgiN163"].plurals[0] = "Makra";
    strings["Volume##sgiN163"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiN163"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiN163"].plurals[0] = "Wysokość";
    strings["Wave Pos##sgiN163"].plurals[0] = "Poz. fali";
    strings["Waveform##sgiN163"].plurals[0] = "Fala";
    strings["Wave Length##sgiN163"].plurals[0] = "Długość";

    //   sgiWSG    src/gui/inst/namco.cpp

    strings["Macros##sgiWSG"].plurals[0] = "Makra";
    strings["Volume##sgiWSG"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiWSG"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiWSG"].plurals[0] = "Wysokość";
    strings["Noise##sgiWSG"].plurals[0] = "Szum";
    strings["Waveform##sgiWSG"].plurals[0] = "Fala";
    strings["Panning (left)##sgiWSG"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiWSG"].plurals[0] = "Panning (prawo)";

    //   sgiNES    src/gui/inst/nes.cpp

    strings["Macros##sgiNES"].plurals[0] = "Makra";
    strings["Volume##sgiNES"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiNES"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiNES"].plurals[0] = "Wysokość";
    strings["Duty/Noise##sgiNES"].plurals[0] = "Szerokość pulsu/tryb szumu";
    strings["Phase Reset##sgiNES"].plurals[0] = "Reset fazy";

    //   sgiOPL    src/gui/inst/opl.cpp

    strings["4-op##sgiOPL"].plurals[0] = "4-op";
    strings["Drums##sgiOPL"].plurals[0] = "Perkusja";
    strings["Fixed frequency mode##sgiOPL"].plurals[0] = "Tryb stalej czestotliwosci";
    strings["when enabled, drums will be set to the specified frequencies, ignoring the note.##sgiOPL"].plurals[0] = "gdy tryb ten jest włączony, instrumenty perkusji będą grane na określonych częstotliwościach. Wartości nut będą ignorowane.";
    strings["Drum##sgiOPL"].plurals[0] = "Perkusja";
    strings["Block##sgiOPL"].plurals[0] = "Blok";
    strings["FreqNum##sgiOPL"].plurals[0] = "FreqNum";
    strings["Kick##sgiOPL0"].plurals[0] = "Bęben basowy";
    strings["Snare/Hi-hat##sgiOPL"].plurals[0] = "Werbel/Hi-hat";
    strings["Tom/Top##sgiOPL"].plurals[0] = "Tom/Talerz";
    strings["Other##sgiOPL0"].plurals[0] = "Inne";
    strings["Other##sgiOPL1"].plurals[0] = "Inne";
    strings["Envelope##sgiOPL0"].plurals[0] = "Obwiednia";
    strings["Envelope##sgiOPL1"].plurals[0] = "Obwiednia";
    strings["op%d##sgiOPL0"].plurals[0] = "op%d";
    strings["Kick##sgiOPL1"].plurals[0] = "Bęben basowy";
    strings["Env##sgiOPL"].plurals[0] = "Obw.";
    strings["OP%d##sgiOPL1"].plurals[0] = "OP%d";
    strings["OPL2/3 only (last 4 waveforms are OPL3 only)##sgiOPL0"].plurals[0] = "Tylko OPL2/3 (ostanie 4 kształty fal sa dostepne tylko na OPL3)";
    strings["op%d##sgiOPL2"].plurals[0] = "op%d";
    strings["Envelope 2 (kick only)##sgiOPL0"].plurals[0] = "Obwiednia 2 (tylko dla bebna basowego)";
    strings["Envelope##sgiOPL2"].plurals[0] = "Obwiednia";
    strings["Operator %d##sgiOPL"].plurals[0] = "Operator %d";
    strings["Waveform##sgiOPL"].plurals[0] = "Kształt fali";
    strings["Envelope##sgiOPL3"].plurals[0] = "Obwiednia";
    strings["OPL2/3 only (last 4 waveforms are OPL3 only)##sgiOPL1"].plurals[0] = "Tylko OPL2/3 (ostanie 4 kształty fal sa dostepne tylko na OPL3)";
    strings["op%d##sgiOPL3"].plurals[0] = "op%d";
    strings["Envelope 2 (kick only)##sgiOPL1"].plurals[0] = "Obwiednia 2 (tylko dla bebna basowego)";
    strings["Envelope##sgiOPL4"].plurals[0] = "Obwiednia";
    strings["OP%d##sgiOPL4"].plurals[0] = "OP%d";
    strings["OPL2/3 only (last 4 waveforms are OPL3 only)##sgiOPL2"].plurals[0] = "Tylko OPL2/3 (ostanie 4 kształty fal sa dostepne tylko na OPL3)";
    strings["FM Macros##sgiOPL"].plurals[0] = "Makra FM";
    strings["OP%d Macros##sgiOPL"].plurals[0] = "Makra OP%d";
    strings["Macros##sgiOPL"].plurals[0] = "Makra";
    strings["Volume##sgiOPL"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiOPL"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiOPL"].plurals[0] = "Wysokość";
    strings["Panning##sgiOPL"].plurals[0] = "Panning";
    strings["Phase Reset##sgiOPL"].plurals[0] = "Reset fazy";

    //   sgiOPLL   src/gui/inst/opll.cpp

    strings["%s name##sgiOPLL"].plurals[0] = "nazwa %s";
    strings["Fixed frequency mode##sgiOPLL"].plurals[0] = "Tryb stalej czestotliwosci";
    strings["when enabled, drums will be set to the specified frequencies, ignoring the note.##sgiOPLL"].plurals[0] = "gdy tryb ten jest włączony, instrumenty perkusji będą grane na określonych częstotliwościach. Wartości nut będą ignorowane.";
    strings["Drum##sgiOPLL"].plurals[0] = "Perkusja";
    strings["Block##sgiOPLL"].plurals[0] = "Blok";
    strings["FreqNum##sgiOPLL"].plurals[0] = "FreqNum";
    strings["Kick##sgiOPLL"].plurals[0] = "Bęben basowy";
    strings["Snare/Hi-hat##sgiOPLL"].plurals[0] = "Werbel/Hi-hat";
    strings["Tom/Top##sgiOPLL"].plurals[0] = "Tom/Talerz";
    strings["Volume##TL"].plurals[0] = "Głośność##TL";
    strings["this volume slider only works in compatibility (non-drums) system.##sgiOPLL"].plurals[0] = "ta regulacja głośności działa tylko w kompatybilnym (nie-perkusyjnym) systemie.";
    strings["Other##sgiOPLL0"].plurals[0] = "Inne";
    strings["Other##sgiOPLL1"].plurals[0] = "Inne";
    strings["Envelope##sgiOPLL0"].plurals[0] = "Obwiednia";
    strings["Envelope##sgiOPLL1"].plurals[0] = "Obwiednia";
    strings["op%d##sgiOPLL0"].plurals[0] = "op%d";
    strings["OP%d##sgiOPLL1"].plurals[0] = "OP%d";
    strings["op%d##sgiOPLL2"].plurals[0] = "op%d";
    strings["Operator %d##sgiOPLL"].plurals[0] = "Operator %d";
    strings["Waveform##sgiOPLL"].plurals[0] = "Kształt fali";
    strings["Envelope##sgiOPLL2"].plurals[0] = "Obwiednia";
    strings["op%d##sgiOPLL3"].plurals[0] = "op%d";
    strings["OP%d##sgiOPLL4"].plurals[0] = "OP%d";
    strings["SSG On##sgiOPLL"].plurals[0] = "Wł. SSG";
    strings["FM Macros##sgiOPLL"].plurals[0] = "Makra FM";
    strings["OP%d Macros##sgiOPLL"].plurals[0] = "Makra OP%d";
    strings["Macros##sgiOPLL"].plurals[0] = "Makra";
    strings["Volume##sgiOPLL"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiOPLL"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiOPLL"].plurals[0] = "Wysokość";
    strings["Patch##sgiOPLL"].plurals[0] = "Instrument";
    strings["Phase Reset##sgiOPLL"].plurals[0] = "Reset fazy";

    //   sgiOPM    src/gui/inst/opm.cpp

    strings["Envelope##sgiOPM0"].plurals[0] = "Obwiednia";
    strings["op%d##sgiOPM0"].plurals[0] = "op%d";
    strings["OP%d##sgiOPM3"].plurals[0] = "OP%d";
    strings["op%d##sgiOPM1"].plurals[0] = "op%d";
    strings["Operator %d##sgiOPM"].plurals[0] = "Operator %d";
    strings["Waveform##sgiOPM"].plurals[0] = "Fala";
    strings["Envelope##sgiOPM1"].plurals[0] = "Obwiednia";
    strings["op%d##sgiOPM2"].plurals[0] = "op%d";
    strings["OP%d##sgiOPM4"].plurals[0] = "OP%d";
    strings["FM Macros##sgiOPM"].plurals[0] = "Makra FM";
    strings["AM Depth##sgiOPM"].plurals[0] = "Głębokość AM";
    strings["PM Depth##sgiOPM"].plurals[0] = "Głębokość PM";
    strings["LFO Speed##sgiOPM"].plurals[0] = "Prędkość LFO";
    strings["LFO Shape##sgiOPM"].plurals[0] = "Kształt fali LFO";
    strings["OpMask##sgiOPM"].plurals[0] = "Maska operatorów";
    strings["OP%d Macros##sgiOPM"].plurals[0] = "Makra OP%d";
    strings["Macros##sgiOPM"].plurals[0] = "Makra";
    strings["Volume##sgiOPM"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiOPM"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiOPM"].plurals[0] = "Wysokość";
    strings["Noise Freq##sgiOPM"].plurals[0] = "Wysokość szumu";
    strings["Panning##sgiOPM"].plurals[0] = "Panning";
    strings["Phase Reset##sgiOPM"].plurals[0] = "Reset fazy";

    //   sgiOPN    src/gui/inst/opn.cpp

    strings["Envelope##sgiOPN0"].plurals[0] = "Obwiednia";
    strings["Envelope##sgiOPN1"].plurals[0] = "Obwiednia";
    strings["op%d##sgiOPN0"].plurals[0] = "op%d";
    strings["OP%d##sgiOPN1"].plurals[0] = "OP%d";
    strings["op%d##sgiOPN2"].plurals[0] = "op%d";
    strings["Operator %d##sgiOPN"].plurals[0] = "Operator %d";
    strings["SSG-EG##sgiOPN"].plurals[0] = "SSG-EG";
    strings["Envelope##sgiOPN2"].plurals[0] = "Obwiednia";
    strings["op%d##sgiOPN3"].plurals[0] = "op%d";
    strings["OP%d##sgiOPN4"].plurals[0] = "OP%d";
    strings["SSG On##sgiOPN"].plurals[0] = "Wł. SSG";
    strings["FM Macros##sgiOPN"].plurals[0] = "Makra FM";
    strings["LFO Speed##sgiOPN"].plurals[0] = "Prędkość LFO";
    strings["OpMask##sgiOPN"].plurals[0] = "Maska operatoró";
    strings["OP%d Macros##sgiOPN"].plurals[0] = "Makra OP%d";
    strings["Macros##sgiOPN"].plurals[0] = "Makra";
    strings["Volume##sgiOPN"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiOPN"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiOPN"].plurals[0] = "Wysokość";
    strings["Panning##sgiOPN"].plurals[0] = "Panning";
    strings["Phase Reset##sgiOPN"].plurals[0] = "Reset fazy";

    //   sgiOPZ    src/gui/inst/opz.cpp

    strings["Request from TX81Z##sgiOPZ"].plurals[0] = "Żądaj dane od TX81Z";
    strings["Other##sgiOPZ0"].plurals[0] = "Inne";
    strings["Other##sgiOPZ1"].plurals[0] = "Inne";
    strings["Envelope##sgiOPZ0"].plurals[0] = "Obwiednia";
    strings["Envelope##sgiOPZ1"].plurals[0] = "Obwiednia";
    strings["op%d##sgiOPZ0"].plurals[0] = "op%d";
    strings["OP%d##sgiOPZ1"].plurals[0] = "OP%d";
    strings["Fixed##sgiOPZ0"].plurals[0] = "Stały";
    strings["Block##sgiOPZ0"].plurals[0] = "Blok";
    strings["FreqNum##sgiOPZ0"].plurals[0] = "FreqNum";
    strings["op%d##sgiOPZ2"].plurals[0] = "op%d";
    strings["Operator %d##sgiOPZ"].plurals[0] = "Operator %d";
    strings["Waveform##sgiOPZ"].plurals[0] = "Fala";
    strings["Envelope##sgiOPZ2"].plurals[0] = "Obwiednia";
    strings["Block##sgiOPZ1"].plurals[0] = "Blok";
    strings["Freq##sgiOPZ"].plurals[0] = "Częst.";
    strings["Fixed##sgiOPZ1"].plurals[0] = "Stały";
    strings["op%d##sgiOPZ3"].plurals[0] = "op%d";
    strings["OP%d##sgiOPZ4"].plurals[0] = "OP%d";
    strings["Fixed##sgiOPZ2"].plurals[0] = "Stały";
    strings["Block##sgiOPZ2"].plurals[0] = "Blok";
    strings["FreqNum##sgiOPZ1"].plurals[0] = "FreqNum";
    strings["FM Macros##sgiOPZ"].plurals[0] = "Makra FM";
    strings["AM Depth##sgiOPZ"].plurals[0] = "Głębokość AM";
    strings["PM Depth##sgiOPZ"].plurals[0] = "Głębokość PM";
    strings["LFO Speed##sgiOPZ"].plurals[0] = "Prędkość LFO";
    strings["LFO Shape##sgiOPZ"].plurals[0] = "Kształt fali LFO";
    strings["AM Depth 2##sgiOPZ"].plurals[0] = "Głębokość AM 2";
    strings["PM Depth 2##sgiOPZ"].plurals[0] = "Głębokość PM 2";
    strings["LFO2 Speed##sgiOPZ"].plurals[0] = "Prędkość LFO 2";
    strings["LFO2 Shape##sgiOPZ"].plurals[0] = "Kształt fali 2";
    strings["OP%d Macros##sgiOPZ"].plurals[0] = "Makra OP%d";
    strings["Macros##sgiOPZ"].plurals[0] = "Makra";
    strings["Volume##sgiOPZ"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiOPZ"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiOPZ"].plurals[0] = "Wysokość";
    strings["Noise Freq##sgiOPZ"].plurals[0] = "Wysokość szumu";
    strings["Panning##sgiOPZ"].plurals[0] = "Panning";
    strings["Phase Reset##sgiOPZ"].plurals[0] = "Reset fazy";

    //   sgiPCE    src/gui/inst/pce.cpp

    strings["Macros##sgiPCE"].plurals[0] = "Makra";
    strings["Volume##sgiPCE"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiPCE"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiPCE"].plurals[0] = "Wysokość";
    strings["Noise##sgiPCE"].plurals[0] = "Szum";
    strings["Waveform##sgiPCE"].plurals[0] = "Fala";
    strings["Panning (left)##sgiPCE"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiPCE"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiPCE"].plurals[0] = "Reset fazy";

    //   sgiPET    src/gui/inst/pet.cpp

    strings["Macros##sgiPET"].plurals[0] = "Makra";
    strings["Volume##sgiPET"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiPET"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiPET"].plurals[0] = "Wysokość";
    strings["Waveform##sgiPET"].plurals[0] = "Kształt fali";

    //   sgiPMQT   src/gui/inst/pokemini.cpp

    strings["Macros##sgiPMQT"].plurals[0] = "Makra";
    strings["Volume##sgiPMQT"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiPMQT"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiPMQT"].plurals[0] = "Wysokość";
    strings["Pulse Width##sgiPMQT"].plurals[0] = "Szerokość pulsu";

    //   sgiPOKEY  src/gui/inst/pokey.cpp

    strings["Macros##sgiPOKEY"].plurals[0] = "Makra";
    strings["Volume##sgiPOKEY"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiPOKEY"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiPOKEY"].plurals[0] = "Wysokość";
    strings["Waveform##sgiPOKEY"].plurals[0] = "Kształt fali";

    //   sgiPNN    src/gui/inst/powernoise.cpp

    strings["Octave offset##sgiPNN"].plurals[0] = "Przesunięcie oktawy";
    strings["go to Macros for other parameters.##sgiPNN"].plurals[0] = "Otwórz kartę makr, aby kontrolować inne parametry.";
    strings["Macros##sgiPNN"].plurals[0] = "Makra";
    strings["Volume##sgiPNN"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiPNN"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiPNN"].plurals[0] = "Wysokość";
    strings["Panning (left)##sgiPNN"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiPNN"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiPNN"].plurals[0] = "Reset fazy";
    strings["Control##sgiPNN"].plurals[0] = "Kontrola";
    strings["Tap A Location##sgiPNN"].plurals[0] = "Pozycja przełącznika A";
    strings["Tap B Location##sgiPNN"].plurals[0] = "Pozycja przełącznika B";
    strings["Load LFSR##sgiPNN"].plurals[0] = "Załaduj LFSR";

    //   sgiPNS    src/gui/inst/powernoise_slope.cpp

    strings["Octave offset##sgiPNS"].plurals[0] = "Przesunięcie oktawy";
    strings["go to Macros for other parameters.##sgiPNS"].plurals[0] = "Otwórz kartę makr, aby kontrolować inne parametry";
    strings["Macros##sgiPNS"].plurals[0] = "Makra";
    strings["Volume##sgiPNS"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiPNS"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiPNS"].plurals[0] = "Wysokość";
    strings["Panning (left)##sgiPNS"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiPNS"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiPNS"].plurals[0] = "Reset fazy";
    strings["Control##sgiPNS"].plurals[0] = "Sterowanie";
    strings["Portion A Length##sgiPNS"].plurals[0] = "Długość części A";
    strings["Portion B Length##sgiPNS"].plurals[0] = "Długość części B";
    strings["Portion A Offset##sgiPNS"].plurals[0] = "Przesunięcie części A";
    strings["Portion B Offset##sgiPNS"].plurals[0] = "Przesunięcie części B";

    //   sgiPV     src/gui/inst/pv1000.cpp

    strings["Macros##sgiPV"].plurals[0] = "Makra";
    strings["Volume##sgiPV"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiPV"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiPV"].plurals[0] = "Wysokość";

    //   sgiQ      src/gui/inst/qsound.cpp

    strings["Macros##sgiQ"].plurals[0] = "Makra";
    strings["Volume##sgiQ"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiQ"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiQ"].plurals[0] = "Wysokość";
    strings["Panning##sgiQ"].plurals[0] = "Panning";
    strings["Surround##sgiQ"].plurals[0] = "Dźwięk przestrzenny";
    strings["Phase Reset##sgiQ"].plurals[0] = "Reset fazy";
    strings["Echo Level##sgiQ"].plurals[0] = "Poziom echo";
    strings["Echo Feedback##sgiQ"].plurals[0] = "Sprzęzenie zwrotne echo";
    strings["Echo Length##sgiQ"].plurals[0] = "Długość echo";

    //   sgiRF5    src/gui/inst/rf5c68.cpp

    strings["Macros##sgiRF5"].plurals[0] = "Makra";
    strings["Volume##sgiRF5"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiRF5"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiRF5"].plurals[0] = "Wysokość";
    strings["Panning (left)##sgiRF5"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiRF5"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiRF5"].plurals[0] = "Reset fazy";

    //   sgiSAA    src/gui/inst/saa1099.cpp

    strings["Macros##sgiSAA"].plurals[0] = "Makra";
    strings["Volume##sgiSAA"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiSAA"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiSAA"].plurals[0] = "Wysokość";
    strings["Duty/Noise##sgiSAA"].plurals[0] = "Szerokość pulsu/szum";
    strings["Waveform##sgiSAA"].plurals[0] = "Kształt fali";
    strings["Panning (left)##sgiSAA"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiSAA"].plurals[0] = "Panning (prawo)";
    strings["Envelope##sgiSAA"].plurals[0] = "Obwiednia";

    //   sgismpd   src/gui/inst/sampleDraw.cpp

    strings["Sample##sgismpd0"].plurals[0] = "Sampel";
    strings["DPCM##sgismpd"].plurals[0] = "DPCM";
    strings["new DPCM features disabled (compatibility)!##sgismpd"].plurals[0] = "новые функции ДИКМ отключены (совместимость)!";
    strings["click here to enable them.##sgismpd"].plurals[0] = "нажмите сюда, чтобы включить их.";
    strings["none selected##sgismpd"].plurals[0] = "nie wybrano";
    strings["Use sample##sgismpd"].plurals[0] = "Użyj sampla";
    strings["Sample bank slot##BANKSLOT"].plurals[0] = "Номер банка сэмплов##BANKSLOT";
    strings["Sample##sgismpd1"].plurals[0] = "Sampel";
    strings["Use wavetable (Amiga/SNES/Generic DAC only)##sgismpd"].plurals[0] = "Używaj tablicy fal (tylko dla Amiga/SNES/typowego przetwornika C/A)";
    strings["Width##sgismpd"].plurals[0] = "Szerokość";
    strings["Use sample map##sgismpd"].plurals[0] = "Użyj mapy sampli";
    strings["pitch##sgismpd"].plurals[0] = "wysokość dźwięku";
    strings["delta##sgismpd"].plurals[0] = "delta";
    strings["note##sgismpd"].plurals[0] = "nuta";
    strings["sample name##sgismpd"].plurals[0] = "nazwa sampla";
    strings["set entire map to this pitch##sgismpd"].plurals[0] = "установить эту частоту для всей карты";
    strings["set entire map to this delta counter value##sgismpd"].plurals[0] = "установить это нач. знач. дельта-счётчика для всей карты";
    strings["set entire map to this note##sgismpd"].plurals[0] = "установить эту ноту для всей карты";
    strings["set entire map to this sample##sgismpd"].plurals[0] = "установить этот сэмпл для всей карты";
    strings["reset pitches##sgismpd"].plurals[0] = "сбросить частоты";
    strings["clear delta counter values##sgismpd"].plurals[0] = "очистить нач. знач. дельта-счётчика";
    strings["reset notes##sgismpd"].plurals[0] = "resetuj nuty";
    strings["clear map samples##sgismpd"].plurals[0] = "wyczyść mapę sampli";

    //   sgiSCC    src/gui/inst/scc.cpp

    strings["Macros##sgiSCC"].plurals[0] = "Makra";
    strings["Volume##sgiSCC"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiSCC"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiSCC"].plurals[0] = "Wysokość";
    strings["Waveform##sgiSCC"].plurals[0] = "Fala";

    //   sgiSEGA   src/gui/inst/segapcm.cpp

    strings["Macros##sgiSEGA"].plurals[0] = "Makra";
    strings["Volume##sgiSEGA"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiSEGA"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiSEGA"].plurals[0] = "Wysokość";
    strings["Panning (left)##sgiSEGA"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiSEGA"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiSEGA"].plurals[0] = "Reset fazy";

    //   sgiSM     src/gui/inst/sm8521.cpp

    strings["Macros##sgiSM"].plurals[0] = "Makra";
    strings["Volume##sgiSM"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiSM"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiSM"].plurals[0] = "Wysokość";
    strings["Waveform##sgiSM"].plurals[0] = "Fala";

    //   sgiSNES   src/gui/inst/snes.cpp

    strings["Use envelope##sgiSNES"].plurals[0] = "Użyj obwiedni";
    strings["Envelope##sgiSNES0"].plurals[0] = "Obwiednia";
    strings["Envelope##sgiSNES1"].plurals[0] = "Obwiednia";
    strings["Sustain/release mode:##sgiSNES"].plurals[0] = "Режим сустейна/релиза:";
    strings["Direct (cut on release)##sgiSNES"].plurals[0] = "Прямой (заглушить на релизе)";
    strings["Effective (linear decrease)##sgiSNES"].plurals[0] = "Эффективный (линейный спад)";
    strings["Effective (exponential decrease)##sgiSNES"].plurals[0] = "Эффективный (экспоненциальный спад)";
    strings["Delayed (write R on release)##sgiSNES"].plurals[0] = "Отложенный (записать R на релизе)";
    strings["Gain Mode##sgiSNES0"].plurals[0] = "Tryb wzmocnienia";
    strings["Gain Mode##sgiSNES1"].plurals[0] = "Tryb wzmocnienia";
    strings["Gain##sgiSNES0"].plurals[0] = "Wzmocnienie";
    strings["Gain##sgiSNES1"].plurals[0] = "Wzmocnienie";
    strings["Direct##sgiSNES"].plurals[0] = "Прямое";
    strings["Decrease (linear)##sgiSNES"].plurals[0] = "Спад (линейный)";
    strings["Decrease (logarithmic)##sgiSNES"].plurals[0] = "Спад (логарифмический)";
    strings["Increase (linear)##sgiSNES"].plurals[0] = "Нарастание (линейное)";
    strings["Increase (bent line)##sgiSNES"].plurals[0] = "Нарастание (изогн. линия)";
    strings["using decrease modes will not produce any sound at all, unless you know what you are doing.\nit is recommended to use the Gain macro for decrease instead.##sgiSNES"].plurals[0] = "использование режимов спада приведёт к отсутствию звука, если вы не понимаете, как это всё работает.\nрекомендуется использовать макрос усиления для спада.";
    strings["Macros##sgiSNES"].plurals[0] = "Makra";
    strings["Volume##sgiSNES"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiSNES"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiSNES"].plurals[0] = "Wysokość";
    strings["Noise Freq##sgiSNES"].plurals[0] = "Wysokość szumu";
    strings["Waveform##sgiSNES"].plurals[0] = "Fala";
    strings["Panning (left)##sgiSNES"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiSNES"].plurals[0] = "Panning (prawo)";
    strings["Special##sgiSNES"].plurals[0] = "Specjalne";
    strings["Gain##sgiSNES2"].plurals[0] = "Wzmocnienie";

    //   sgiPSG    src/gui/inst/std.cpp

    strings["Macros##sgiPSG"].plurals[0] = "Makra";
    strings["Volume##sgiPSG"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiPSG"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiPSG"].plurals[0] = "Wysokość";
    strings["Duty##sgiPSG"].plurals[0] = "Szerokość pulsu";
    strings["Panning##sgiPSG"].plurals[0] = "Panning";
    strings["Phase Reset##sgiPSG"].plurals[0] = "Reset fazy";

    //   sgistru   src/gui/inst/stringsUtil.cpp

    strings["Down Down Down##sgistru"].plurals[0] = "Dół Dół Dół";
    strings["Down.##sgistru"].plurals[0] = "Dół.";
    strings["Down Up Down Up##sgistru"].plurals[0] = "Dół Góra Dół Góra";
    strings["Down UP##sgistru"].plurals[0] = "Dół GÓRA";
    strings["Up Up Up##sgistru"].plurals[0] = "Góra Góra Góra";
    strings["Up.##sgistru"].plurals[0] = "Góra.";
    strings["Up Down Up Down##sgistru"].plurals[0] = "Góra Dół Góra Dół";
    strings["Up DOWN##sgistru"].plurals[0] = "Góra DÓŁ";
    strings["Algorithm##sgistru"].plurals[0] = "Algorytm";
    strings["Feedback##sgistru"].plurals[0] = "Sprz. zwrotne";
    strings["LFO > Freq##sgistru"].plurals[0] = "LFO > częst.";
    strings["LFO > Amp##sgistru"].plurals[0] = "LFO > ampl.";
    strings["Attack##sgistru"].plurals[0] = "Atak";
    strings["Decay##sgistru"].plurals[0] = "Opadanie";
    strings["Decay 2##sgistru"].plurals[0] = "Opadanie 2";
    strings["Release##sgistru"].plurals[0] = "Zwolnienie";
    strings["Sustain##sgistru0"].plurals[0] = "Podtrzymanie";
    strings["Level##sgistru"].plurals[0] = "Poziom";
    strings["EnvScale##sgistru"].plurals[0] = "Skala obw.";
    strings["Multiplier##sgistru"].plurals[0] = "Mnożnik";
    strings["Detune##sgistru0"].plurals[0] = "Rozstrój";
    strings["Detune 2##sgistru"].plurals[0] = "Rozstrój 2";
    strings["SSG-EG##sgistru"].plurals[0] = "SSG-EG";
    strings["AM Depth##sgistru"].plurals[0] = "Głębokość AM";
    strings["Vibrato Depth##sgistru"].plurals[0] = "Głębokość Vibrato";
    strings["Sustained##sgistru0"].plurals[0] = "Сустейн";
    strings["Sustained##sgistru1"].plurals[0] = "Сустейн";
    strings["Level Scaling##sgistru"].plurals[0] = "Масштаб. громкости";
    strings["Sustain##sgistru1"].plurals[0] = "Сустейн";
    strings["Vibrato##sgistru"].plurals[0] = "Vibrato";
    strings["Waveform##sgistru"].plurals[0] = "Fala";
    strings["Scale Rate##sgistru"].plurals[0] = "Измен. коэфф. масш. в зав. от част.";
    strings["OP2 Half Sine##sgistru"].plurals[0] = "Pół-sinusoida na OP2";
    strings["OP1 Half Sine##sgistru"].plurals[0] = "Pół-sinusoida na OP1";
    strings["EnvShift##sgistru"].plurals[0] = "Сдвиг огиб.";
    strings["Reverb##sgistru"].plurals[0] = "Реверб";
    strings["Fine##sgistru0"].plurals[0] = "Точн.";
    strings["LFO2 > Freq##sgistru"].plurals[0] = "LFO2 > częst.";
    strings["LFO2 > Amp##sgistru"].plurals[0] = "LFO2 > ampl.";
    strings["Fine##sgistru1"].plurals[0] = "Точн.";
    strings["Fine##sgistru2"].plurals[0] = "Точн.";
    strings["OP4 Noise Mode##sgistru0"].plurals[0] = "Tryb szumu na OP4";
    strings["Envelope Delay##sgistru"].plurals[0] = "Opóżnienie obwiedni";
    strings["Output Level##sgistru0"].plurals[0] = "Głośność вывода";
    strings["Modulation Input Level##sgistru"].plurals[0] = "Сила модуляции на входе";
    strings["Left Output##sgistru"].plurals[0] = "Вывод звука влево";
    strings["Right Output##sgistru"].plurals[0] = "Вывод звука вправо";
    strings["Coarse Tune (semitones)##sgistru"].plurals[0] = "Грубая расстройка (полутоны)";
    strings["Detune##sgistru1"].plurals[0] = "Rozstrój";
    strings["Fixed Frequency Mode##sgistru"].plurals[0] = "Tryb stałej częstotliwości";
    strings["OP4 Noise Mode##sgistru1"].plurals[0] = "Tryb szumu na OP4";
    strings["Env. Delay##sgistru"].plurals[0] = "Opóżnienie obw.";
    strings["Output Level##sgistru1"].plurals[0] = "Głośność wyjścia";
    strings["ModInput##sgistru"].plurals[0] = "Wyjście mod.";
    strings["Left##sgistru"].plurals[0] = "Lewo";
    strings["Right##sgistru"].plurals[0] = "Prawo";
    strings["Tune##sgistru"].plurals[0] = "Груб. расстр.";
    strings["Detune##sgistru2"].plurals[0] = "Rozstrój";
    strings["Fixed##sgistru0"].plurals[0] = "Фикс. част.";
    strings["Fine##sgistru3"].plurals[0] = "Точн.";
    strings["Fine##sgistru4"].plurals[0] = "Точн.";
    strings["Fine##sgistru5"].plurals[0] = "Точн.";
    strings["User##sgistru0"].plurals[0] = "Użytkownika";
    strings["1. Violin##sgistru"].plurals[0] = "1. Skrzypce";
    strings["2. Guitar##sgistru0"].plurals[0] = "2. Gitara";
    strings["3. Piano##sgistru0"].plurals[0] = "3. Pianino";
    strings["4. Flute##sgistru0"].plurals[0] = "4. Flet";
    strings["5. Clarinet##sgistru0"].plurals[0] = "5. Klarnet";
    strings["6. Oboe##sgistru"].plurals[0] = "6. Obój";
    strings["7. Trumpet##sgistru0"].plurals[0] = "7. Trąbka";
    strings["8. Organ##sgistru"].plurals[0] = "8. Organy";
    strings["9. Horn##sgistru"].plurals[0] = "9. Róg";
    strings["10. Synth##sgistru"].plurals[0] = "10. Syntezator";
    strings["11. Harpsichord##sgistru"].plurals[0] = "11. Klawesyn";
    strings["12. Vibraphone##sgistru0"].plurals[0] = "12. Wibrafon";
    strings["13. Synth Bass##sgistru"].plurals[0] = "13. Syntetyczny Bas";
    strings["14. Acoustic Bass##sgistru"].plurals[0] = "14. Akustyczny Bas";
    strings["15. Electric Guitar##sgistru"].plurals[0] = "15. Gitara Elektryczna";
    strings["Drums##sgistru0"].plurals[0] = "Perkusja";
    strings["User##sgistru1"].plurals[0] = "Użytkownika";
    strings["1. Electric String##sgistru"].plurals[0] = "1. Elektryczny Instr. Strunowy";
    strings["2. Bow wow##sgistru"].plurals[0] = "2. Bow wow";
    strings["3. Electric Guitar##sgistru0"].plurals[0] = "3. Gitara Elektryczna";
    strings["4. Organ##sgistru"].plurals[0] = "4. Organy";
    strings["5. Clarinet##sgistru1"].plurals[0] = "5. Klarnet";
    strings["6. Saxophone##sgistru"].plurals[0] = "6. Saksofon";
    strings["7. Trumpet##sgistru1"].plurals[0] = "7. Trąbka";
    strings["8. Street Organ##sgistru"].plurals[0] = "8. Katarynka ";
    strings["9. Synth Brass##sgistru"].plurals[0] = "9. Синтезаторный медный духовой";
    strings["10. Electric Piano##sgistru"].plurals[0] = "10. Pianino Elektryczne";
    strings["11. Bass##sgistru"].plurals[0] = "11. Bas";
    strings["12. Vibraphone##sgistru1"].plurals[0] = "12. Wibrafon";
    strings["13. Chime##sgistru"].plurals[0] = "13. Dzwonki";
    strings["14. Tom Tom II##sgistru"].plurals[0] = "14. Tom-tom №2";
    strings["15. Noise##sgistru"].plurals[0] = "15. Szum";
    strings["Drums##sgistru1"].plurals[0] = "Perkusja";
    strings["User##sgistru2"].plurals[0] = "Użytkownika";
    strings["1. Strings##sgistru"].plurals[0] = "1. Smyczki";
    strings["2. Guitar##sgistru1"].plurals[0] = "2. Gitara";
    strings["3. Electric Guitar##sgistru1"].plurals[0] = "3. Gitara Elektryczna";
    strings["4. Electric Piano##sgistru"].plurals[0] = "4. Pianono Elektryczne";
    strings["5. Flute##sgistru"].plurals[0] = "5. Flet";
    strings["6. Marimba##sgistru"].plurals[0] = "6. Marimba";
    strings["7. Trumpet##sgistru2"].plurals[0] = "7. Trąbka";
    strings["8. Harmonica##sgistru"].plurals[0] = "8. Harmonijka";
    strings["9. Tuba##sgistru"].plurals[0] = "9. Tuba";
    strings["10. Synth Brass##sgistru"].plurals[0] = "10. Синтезаторный медный духовой";
    strings["11. Short Saw##sgistru"].plurals[0] = "11. Короткая пила";
    strings["12. Vibraphone##sgistru2"].plurals[0] = "12. Wibrafon";
    strings["13. Electric Guitar 2##sgistru"].plurals[0] = "13. Gitara Elektryczna 2";
    strings["14. Synth Bass##sgistru"].plurals[0] = "14. Syntetyczny Bas";
    strings["15. Sitar##sgistru"].plurals[0] = "15. Sitar";
    strings["Drums##sgistru2"].plurals[0] = "Perkusja";
    strings["User##sgistru3"].plurals[0] = "Użytkownika";
    strings["1. Bell##sgistru"].plurals[0] = "1. Dzwon";
    strings["2. Guitar##sgistru2"].plurals[0] = "2. Gitara";
    strings["3. Piano##sgistru1"].plurals[0] = "3. Pianino";
    strings["4. Flute##sgistru1"].plurals[0] = "4. Flet";
    strings["5. Clarinet##sgistru2"].plurals[0] = "5.Klarnet";
    strings["6. Rattling Bell##sgistru"].plurals[0] = "6. Grzechoczący dzwon";
    strings["7. Trumpet##sgistru3"].plurals[0] = "7. Trąbka";
    strings["8. Reed Organ##sgistru"].plurals[0] = "8. Fisharmonia";
    strings["9. Soft Bell##sgistru"].plurals[0] = "9. \"Miękki\" dzwon";
    strings["10. Xylophone##sgistru"].plurals[0] = "10. Ksylofon";
    strings["11. Vibraphone##sgistru"].plurals[0] = "11. Wibrafon";
    strings["12. Brass##sgistru"].plurals[0] = "12. Медный духовой инструмент";
    strings["13. Bass Guitar##sgistru"].plurals[0] = "13. Gitara basowa";
    strings["14. Synth##sgistru"].plurals[0] = "14. Syntezator";
    strings["15. Chorus##sgistru"].plurals[0] = "15. Chór";
    strings["Drums##sgistru3"].plurals[0] = "Perkusja";
    strings["Sine##sgistru0"].plurals[0] = "Sinusoida";
    strings["Half Sine##sgistru0"].plurals[0] = "Połowa sinusoidy";
    strings["Absolute Sine##sgistru0"].plurals[0] = "Модуль синуса";
    strings["Quarter Sine##sgistru"].plurals[0] = "Четверть синуса";
    strings["Squished Sine##sgistru0"].plurals[0] = "Сжатый синус";
    strings["Squished AbsSine##sgistru0"].plurals[0] = "Сж. модуль синуса";
    strings["Square##sgistru0"].plurals[0] = "Меандр";
    strings["Derived Square##sgistru0"].plurals[0] = "Производная от меандра";
    strings["Sine##sgistru1"].plurals[0] = "Sinusoida";
    strings["Half Sine##sgistru1"].plurals[0] = "Połowa sinusoidy";
    strings["Absolute Sine##sgistru1"].plurals[0] = "Модуль синуса";
    strings["Pulse Sine##sgistru"].plurals[0] = "Синус-меандр";
    strings["Sine (Even Periods)##sgistru"].plurals[0] = "Синус (чётные периоды)";
    strings["AbsSine (Even Periods)##sgistru"].plurals[0] = "Мод. синуса (чётн. пер.)";
    strings["Square##sgistru1"].plurals[0] = "Меандр";
    strings["Derived Square##sgistru1"].plurals[0] = "Производная от меандра";
    strings["Sine##sgistru2"].plurals[0] = "Sinusoida";
    strings["Triangle##sgistru"].plurals[0] = "Треуг. волна";
    strings["Cut Sine##sgistru"].plurals[0] = "Обрезанный синус";
    strings["Cut Triangle##sgistru"].plurals[0] = "Обрез. треуг. волна";
    strings["Squished Sine##sgistru1"].plurals[0] = "Сжатый синус";
    strings["Squished Triangle##sgistru"].plurals[0] = "Сжатая треуг. волна";
    strings["Squished AbsSine##sgistru1"].plurals[0] = "Сжатый модуль синуса";
    strings["Squished AbsTriangle##sgistru"].plurals[0] = "Сж. мод. треуг. волны";
    strings["Snare##sgistru0"].plurals[0] = "Рабочий барабан";
    strings["Tom##sgistru"].plurals[0] = "Там-там";
    strings["Top##sgistru0"].plurals[0] = "Talerz";
    strings["HiHat##sgistru0"].plurals[0] = "Hi-hat";
    strings["Normal##sgistru"].plurals[0] = "Zwykły";
    strings["Snare##sgistru1"].plurals[0] = "Werbel";
    strings["HiHat##sgistru1"].plurals[0] = "Hi-hat";
    strings["Top##sgistru1"].plurals[0] = "Talerz";
    strings["Noise disabled##sgistru"].plurals[0] = "Szum wyłączony";
    strings["Square + noise##sgistru"].plurals[0] = "Fala kwadratowa + szum";
    strings["Ringmod from OP3 + noise##sgistru"].plurals[0] = "Кольцевая модуляция от OP3 + szum";
    strings["Ringmod from OP3 + double pitch ModInput\nWARNING - has emulation issues, subject to change##sgistru"].plurals[0] = "Кольцевая модуляция от OP3 + входная модуляция с удвоенной частотой\nUWAGA - występują problemy z emulacją tego trybu, może on ulec zmianie";
    strings["op1##sgistru"].plurals[0] = "op1";
    strings["op2##sgistru"].plurals[0] = "op2";
    strings["op3##sgistru"].plurals[0] = "op3";
    strings["op4##sgistru"].plurals[0] = "op4";
    strings["triangle##sgistru"].plurals[0] = "треуг.";
    strings["saw##sgistru"].plurals[0] = "пила";
    strings["pulse##sgistru"].plurals[0] = "меандр";
    strings["noise##sgistru0"].plurals[0] = "szum";
    strings["tone##sgistru"].plurals[0] = "ton";
    strings["noise##sgistru1"].plurals[0] = "szum";
    strings["envelope##sgistru"].plurals[0] = "obwiednia";
    strings["hold##sgistru"].plurals[0] = "удержание";
    strings["alternate##sgistru"].plurals[0] = "изм. направл.";
    strings["direction##sgistru0"].plurals[0] = "kierunek";
    strings["enable##sgistru0"].plurals[0] = "wł.";
    strings["enabled##sgistru0"].plurals[0] = "wł.";
    strings["mirror##sgistru"].plurals[0] = "отраж.";
    strings["loop##sgistru0"].plurals[0] = "цикл";
    strings["cut##sgistru"].plurals[0] = "обрез.";
    strings["direction##sgistru1"].plurals[0] = "kierunek";
    strings["resolution##sgistru"].plurals[0] = "rozdzielczość";
    strings["fixed##sgistru1"].plurals[0] = "stały";
    strings["N/A##sgistru"].plurals[0] = "-";
    strings["enabled##sgistru1"].plurals[0] = "wł.";
    strings["noise##sgistru2"].plurals[0] = "szum";
    strings["echo##sgistru"].plurals[0] = "echo";
    strings["pitch mod##sgistru"].plurals[0] = "част. мод.";
    strings["invert right##sgistru"].plurals[0] = "инв. справа";
    strings["invert left##sgistru"].plurals[0] = "инв. слева";
    strings["low##sgistru"].plurals[0] = "dolno";
    strings["band##sgistru"].plurals[0] = "środk.";
    strings["high##sgistru"].plurals[0] = "górno";
    strings["ch3off##sgistru"].plurals[0] = "wył. 3 kanał";
    strings["gate##sgistru"].plurals[0] = "старт/стop огиб.";
    strings["sync##sgistru"].plurals[0] = "synchro.";
    strings["ring##sgistru"].plurals[0] = "кольц.";
    strings["test##sgistru"].plurals[0] = "test";
    strings["15kHz##sgistru"].plurals[0] = "15 kHz";
    strings["filter 2+4##sgistru"].plurals[0] = "filtr 2+4";
    strings["filter 1+3##sgistru"].plurals[0] = "filtr 1+3";
    strings["16-bit 3+4##sgistru"].plurals[0] = "16-bitowy. 3+4";
    strings["16-bit 1+2##sgistru"].plurals[0] = "16-bitowy. 1+2";
    strings["high3##sgistru"].plurals[0] = "górno 3";
    strings["high1##sgistru"].plurals[0] = "górno 1";
    strings["poly9##sgistru"].plurals[0] = "wielomian 9";
    strings["int##sgistru"].plurals[0] = "inter.";
    strings["sustain##sgistru2"].plurals[0] = "podtrzymanie";
    strings["square##sgistru2"].plurals[0] = "меандр";
    strings["noise##sgistru3"].plurals[0] = "szum";
    strings["noise##sgistru4"].plurals[0] = "szum";
    strings["invert##sgistru"].plurals[0] = "инверт.";
    strings["surround##sgistru"].plurals[0] = "przestrenny";
    strings["enable##sgistru1"].plurals[0] = "wł.";
    strings["oneshot##sgistru"].plurals[0] = "jednokrotny";
    strings["split L/R##sgistru"].plurals[0] = "разд. лев/прав";
    strings["HinvR##sgistru"].plurals[0] = "HинвR";
    strings["VinvR##sgistru"].plurals[0] = "VинвR";
    strings["HinvL##sgistru"].plurals[0] = "HинвL";
    strings["VinvL##sgistru"].plurals[0] = "VинвL";
    strings["ring mod##sgistru"].plurals[0] = "кольц. мод.";
    strings["low pass##sgistru"].plurals[0] = "dolno";
    strings["high pass##sgistru"].plurals[0] = "środk.";
    strings["band pass##sgistru"].plurals[0] = "górno";
    strings["HP/K2, HP/K2##sgistru"].plurals[0] = "HP/K2, HP/K2";
    strings["HP/K2, LP/K1##sgistru"].plurals[0] = "HP/K2, LP/K1";
    strings["LP/K2, LP/K2##sgistru"].plurals[0] = "LP/K2, LP/K2";
    strings["LP/K2, LP/K1##sgistru"].plurals[0] = "LP/K2, LP/K1";
    strings["right##sgistru"].plurals[0] = "prawy";
    strings["left##sgistru"].plurals[0] = "lewy";
    strings["rear right##sgistru"].plurals[0] = "tylni prawy";
    strings["rear left##sgistru"].plurals[0] = "tylni lewy";
    strings["enable tap B##sgistru"].plurals[0] = "wł. przełącznik B";
    strings["AM with slope##sgistru"].plurals[0] = "AM ze spadkiem";
    strings["invert B##sgistru"].plurals[0] = "odwr. B";
    strings["invert A##sgistru"].plurals[0] = "odwr. A";
    strings["reset B##sgistru"].plurals[0] = "resetuj B";
    strings["reset A##sgistru"].plurals[0] = "resetuj A";
    strings["clip B##sgistru"].plurals[0] = "огран. B";
    strings["clip A##sgistru"].plurals[0] = "огран. A";
    strings["on##sgistru"].plurals[0] = "wł.";
    strings["k1 slowdown##sgistru"].plurals[0] = "spowolnienie k1";
    strings["k2 slowdown##sgistru"].plurals[0] = "spowolnienie k2";
    strings["pause##sgistru"].plurals[0] = "stop";
    strings["reverse##sgistru"].plurals[0] = "реверс";
    strings["high pass##sgistru1"].plurals[0] = "górno-przepustowy";
    strings["ring mod##sgistru1"].plurals[0] = "modulacja kołowa";
    strings["swap counters (noise)##sgistru"].plurals[0] = "помен. счётч. (шум)";
    strings["low pass (noise)##sgistru"].plurals[0] = "ФНЧ (szum)";
    strings["None##sgistru"].plurals[0] = "Нет";
    strings["Invert##sgistru"].plurals[0] = "Инвертировать";
    strings["Add##sgistru"].plurals[0] = "Dodaj";
    strings["Subtract##sgistru"].plurals[0] = "Odejmij";
    strings["Average##sgistru"].plurals[0] = "Uśrednij";
    strings["Phase##sgistru"].plurals[0] = "Временной сдвиг";
    strings["Chorus##sgistru"].plurals[0] = "Chór";
    strings["None (dual)##sgistru"].plurals[0] = "Нет (две таблицы)";
    strings["Wipe##sgistru"].plurals[0] = "Замена";
    strings["Fade##sgistru"].plurals[0] = "Плавный переход";
    strings["Fade (ping-pong)##sgistru"].plurals[0] = "Плавный переход (туда-обратно)";
    strings["Overlay##sgistru"].plurals[0] = "Наложение";
    strings["Negative Overlay##sgistru"].plurals[0] = "Наложение с обратным знаком";
    strings["Slide##sgistru"].plurals[0] = "Zjazd";
    strings["Mix Chorus##sgistru"].plurals[0] = "Микширование с хорусом";
    strings["Phase Modulation##sgistru"].plurals[0] = "Фазовая модуляция";
    strings["Envelope##sgistru"].plurals[0] = "Obwiednia";
    strings["Sweep##sgistru"].plurals[0] = "Sprz. portamento";
    strings["Wait##sgistru0"].plurals[0] = "Ждать";
    strings["Wait for Release##sgistru0"].plurals[0] = "Ждать релиз";
    strings["Loop##sgistru1"].plurals[0] = "Цикл";
    strings["Loop until Release##sgistru0"].plurals[0] = "Цикл до релиза";
    strings["Volume Sweep##sgistru"].plurals[0] = "Изменение громкости";
    strings["Frequency Sweep##sgistru"].plurals[0] = "Изменение частоты";
    strings["Cutoff Sweep##sgistru"].plurals[0] = "Изменение частоты среза";
    strings["Wait##sgistru1"].plurals[0] = "Ждать";
    strings["Wait for Release##sgistru1"].plurals[0] = "Ждать релиз";
    strings["Loop##sgistru2"].plurals[0] = "Цикл";
    strings["Loop until Release##sgistru1"].plurals[0] = "Цикл до релиза";
    strings["Direct##sgistru"].plurals[0] = "Прямое";
    strings["Decrease (linear)##sgistru"].plurals[0] = "Уменьш. (линейное)";
    strings["Decrease (logarithmic)##sgistru"].plurals[0] = "Уменьш. (логарифмическое)";
    strings["Increase (linear)##sgistru"].plurals[0] = "Увелич. (линейное)";
    strings["Increase (bent line)##sgistru"].plurals[0] = "Увелич. (изогн. линия)";
    strings["Fixed##sgistru2"].plurals[0] = "Абсолютное";
    strings["Relative##sgistru"].plurals[0] = "Относительное";
    strings["QSound##sgistru"].plurals[0] = "QSound";
    strings["Bug##sgistru"].plurals[0] = "Błąd";

    //   sgiSU     src/gui/inst/su.cpp

    strings["Sound Unit##sgiSU"].plurals[0] = "Sound Unit";
    strings["Switch roles of frequency and phase reset timer##sgiSU"].plurals[0] = "Zamień rolw częstotliwośći i timera resetu fazy ";
    strings["Hardware Sequence##sgiSU"].plurals[0] = "Sekwencja sprzętowa";
    strings["Tick##sgiSU0"].plurals[0] = "Skok";
    strings["Command##sgiSU0"].plurals[0] = "Komenda";
    strings["Move/Remove##sgiSU0"].plurals[0] = "Przesuń/usuń";
    strings["Period##sgiSU0"].plurals[0] = "Okres";
    strings["Amount##sgiSU0"].plurals[0] = "Ilość";
    strings["Bound##sgiSU0"].plurals[0] = "Granica";
    strings["Up##sgiSU0"].plurals[0] = "Góra";
    strings["Down##sgiSU0"].plurals[0] = "Dół";
    strings["Loop##sgiSU"].plurals[0] = "Zapętl";
    strings["Flip##sgiSU"].plurals[0] = "W obie strony";
    strings["Period##sgiSU1"].plurals[0] = "Okres";
    strings["Amount##sgiSU1"].plurals[0] = "Ilość";
    strings["Bound##sgiSU1"].plurals[0] = "Granica";
    strings["Up##sgiSU1"].plurals[0] = "Góra";
    strings["Down##sgiSU1"].plurals[0] = "Dół";
    strings["Ticks##sgiSU"].plurals[0] = "Skoki";
    strings["Position##sgiSU"].plurals[0] = "Położenie";
    strings["Macros##sgiSU"].plurals[0] = "Makra";
    strings["Volume##sgiSU"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiSU"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiSU"].plurals[0] = "Wysokość";
    strings["Duty/Noise##sgiSU"].plurals[0] = "Szerokość pulsu/szum";
    strings["Waveform##sgiSU"].plurals[0] = "Fala";
    strings["Panning##sgiSU"].plurals[0] = "Panning";
    strings["Phase Reset##sgiSU"].plurals[0] = "Reset fazy";
    strings["Cutoff##sgiSU"].plurals[0] = "Punkt odcięcia";
    strings["Resonance##sgiSU"].plurals[0] = "Rezonans";
    strings["Control##sgiSU"].plurals[0] = "Sterownie";
    strings["Phase Reset Timer##sgiSU"].plurals[0] = "Timer resetu fazy";

    //   sgiSWAN   src/gui/inst/swan.cpp

    strings["Macros##sgiSWAN"].plurals[0] = "Makra";
    strings["Volume##sgiSWAN"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiSWAN"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiSWAN"].plurals[0] = "Wysokość";
    strings["Noise##sgiSWAN"].plurals[0] = "Szum";
    strings["Waveform##sgiSWAN"].plurals[0] = "Fala";
    strings["Phase Reset##sgiSWAN"].plurals[0] = "Reset fazy";

    //   sgiT6W    src/gui/inst/t6w28.cpp

    strings["Macros##sgiT6W"].plurals[0] = "Makra";
    strings["Volume##sgiT6W"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiT6W"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiT6W"].plurals[0] = "Wysokość";
    strings["Panning (left)##sgiT6W"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiT6W"].plurals[0] = "Panning (prawo)";
    strings["Noise Type##sgiT6W"].plurals[0] = "Typ szumu";
    strings["Phase Reset##sgiT6W"].plurals[0] = "Reset fazy";

    //   sgiTED    src/gui/inst/ted.cpp

    strings["Macros##sgiTED"].plurals[0] = "Makra";
    strings["Volume##sgiTED"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiTED"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiTED"].plurals[0] = "Wysokość";
    strings["Square/Noise##sgiTED"].plurals[0] = "Kwadrat/szum";
    strings["Phase Reset##sgiTED"].plurals[0] = "Reset fazy";

    //   sgiTIA    src/gui/inst/tia.cpp

    strings["Macros##sgiTIA"].plurals[0] = "Makra";
    strings["Volume##sgiTIA"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiTIA"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiTIA"].plurals[0] = "Wysokość";
    strings["Waveform##sgiTIA"].plurals[0] = "Kształt fali";

    //   sgiVB     src/gui/inst/vboy.cpp

    strings["Set modulation table (channel 5 only)##sgiVB"].plurals[0] = "Ustaw tablicę modulacji (tylko dla piątego kanału)";
    strings["Hex##MTHex"].plurals[0] = "Hex.##MTHex";
    strings["Dec##MTHex"].plurals[0] = "Dec.##MTHex";
    strings["Macros##sgiVB"].plurals[0] = "Makra";
    strings["Volume##sgiVB"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiVB"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiVB"].plurals[0] = "Wysokość";
    // strings["Noise Length##sgiVB"].plurals[0] = "lugosc szumu";
    strings["Waveform##sgiVB"].plurals[0] = "Fala";
    strings["Panning (left)##sgiVB"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiVB"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiVB"].plurals[0] = "Reset fazy";

    //   sgiVERA   src/gui/inst/vera.cpp

    strings["Macros##sgiVERA"].plurals[0] = "Makra";
    strings["Volume##sgiVERA"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiVERA"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiVERA"].plurals[0] = "Wysokość";
    strings["Duty##sgiVERA"].plurals[0] = "Szerokość pulsu";
    strings["Waveform##sgiVERA"].plurals[0] = "Kształt fali";
    strings["Panning##sgiVERA"].plurals[0] = "Panning";

    //   sgiVIC    src/gui/inst/vic.cpp

    strings["Macros##sgiVIC"].plurals[0] = "Makra";
    strings["Volume##sgiVIC"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiVIC"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiVIC"].plurals[0] = "Wysokość";
    strings["On/Off##sgiVIC"].plurals[0] = "Wl./wyl.";
    strings["Waveform##sgiVIC"].plurals[0] = "Kształt fali";

    //   sgiVRC6   src/gui/inst/vrc6.cpp

    strings["Macros##sgiVRC6"].plurals[0] = "Makra";
    strings["Volume##sgiVRC6"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiVRC6"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiVRC6"].plurals[0] = "Wysokość";
    strings["Duty##sgiVRC6"].plurals[0] = "Szerokość pulsu";
    strings["Waveform##sgiVRC6"].plurals[0] = "Kształt fali";
    strings["Phase Reset##sgiVRC6"].plurals[0] = "Reset fazy";

    //   sgiVRC6S  src/gui/inst/vrc6saw.cpp

    strings["Macros##sgiVRC6S"].plurals[0] = "Makra";
    strings["Volume##sgiVRC6S"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiVRC6S"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiVRC6S"].plurals[0] = "Wysokość";

    //   sgiwave   src/gui/inst/wavetable.cpp

    strings["Wavetable##sgiwave"].plurals[0] = "Synteza tablicowa";
    strings["Enable synthesizer##sgiwave"].plurals[0] = "Włącz syntezator";
    strings["Single-waveform##sgiwave"].plurals[0] = "Pojedyncza fala";
    strings["Dual-waveform##sgiwave"].plurals[0] = "Podwójne fale";
    strings["Wave 1##sgiwave0"].plurals[0] = "Fala 1";
    strings["Wave 2##sgiwave0"].plurals[0] = "Fala 2";
    strings["Result##sgiwave"].plurals[0] = "Rezultat";
    strings["Wave 1 ##sgiwave"].plurals[0] = "Fala 1 ";
    strings["waveform macro is controlling wave 1!\nthis value will be ineffective.##sgiwave"].plurals[0] = "makro kształtu fali steruje falą 1!\nta wartość zostanie zignorowana";
    strings["Wave 1##sgiwave1"].plurals[0] = "Fala 1";
    strings["Wave 2##sgiwave1"].plurals[0] = "Fala 2";
    strings["Resume preview##sgiwave"].plurals[0] = "Wznów podgląd";
    strings["Pause preview##sgiwave"].plurals[0] = "Zatrzymaj podgląd";
    strings["Restart preview##sgiwave"].plurals[0] = "Zrestartuj podgląd";
    strings["too many wavetables!##sgiwave"].plurals[0] = "zbyt wiele tablic fali!";
    strings["Copy to new wavetable##sgiwave"].plurals[0] = "Kopiuj do nowej tablicy fal";
    strings["Update Rate##sgiwave"].plurals[0] = "Współczynnik odświeżania";
    strings["Speed##sgiwave"].plurals[0] = "Prędkośc";
    strings["Amount##sgiwave"].plurals[0] = "Ilość";
    strings["Power##sgiwave"].plurals[0] = "Stopień";
    strings["Global##sgiwave"].plurals[0] = "Globalny";
    strings["wavetable synthesizer disabled.\nuse the Waveform macro to set the wave for this instrument.##sgiwave"].plurals[0] = "syntezator tablicowy wyłączony\nużyj makra fali, aby ustawić tablicę fal dla tego instrumentu";

    //   sgiX1     src/gui/inst/x1_010.cpp

    strings["Macros##sgiX1"].plurals[0] = "Makra";
    strings["Volume##sgiX1"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiX1"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiX1"].plurals[0] = "Wysokość";
    strings["Waveform##sgiX1"].plurals[0] = "Fala";
    strings["Panning (left)##sgiX1"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiX1"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiX1"].plurals[0] = "Reset fazy";
    strings["Envelope##sgiX1"].plurals[0] = "Obwiednia";
    strings["Envelope Mode##sgiX1"].plurals[0] = "Tryb obwiedni";
    strings["AutoEnv Num##sgiX1"].plurals[0] = "Licznik częst. auto-obwiedni.";
    strings["AutoEnv Den##sgiX1"].plurals[0] = "Nianownik częst. auto-obwiedni.";

    //   sgiYMZ    src/gui/inst/ymz280b.cpp

    strings["Macros##sgiYMZ"].plurals[0] = "Makra";
    strings["Volume##sgiYMZ"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiYMZ"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiYMZ"].plurals[0] = "Wysokość";
    strings["Panning##sgiYMZ"].plurals[0] = "Panning";
    strings["Phase Reset##sgiYMZ"].plurals[0] = "Reset fazy";

    // no more instruments

    //   seen    src/engine/engine.cpp

    strings["00xy: Arpeggio##seen"].plurals[0] = "00xy: Arpeggio";
    strings["01xx: Pitch slide up##seen"].plurals[0] = "01xx: Portamento w górę";
    strings["02xx: Pitch slide down##seen"].plurals[0] = "02xx: Portamento w dół";
    strings["03xx: Portamento##seen"].plurals[0] = "03xx: Auto-portamento (do wskazanej nuty)";
    strings["04xy: Vibrato (x: speed; y: depth)##seen"].plurals[0] = "04xy: Vibrato (x: szybkość; y: głebokość)";
    strings["05xy: Volume slide + vibrato (compatibility only!)##seen"].plurals[0] = "05xy: Изменение громкости + вибрато (исключительно в целях совместимости!)";
    strings["06xy: Volume slide + portamento (compatibility only!)##seen"].plurals[0] = "06xy: Изменение громкости + портаменто (исключительно в целях совместимости!)";
    strings["07xy: Tremolo (x: speed; y: depth)##seen"].plurals[0] = "07xy: Тремоло (x: скорость; y: глубина)";
    strings["08xy: Set panning (x: left; y: right)##seen"].plurals[0] = "08xy: Panning (x: лево; y: право)";
    strings["09xx: Set groove pattern (speed 1 if no grooves exist)##seen"].plurals[0] = "09xx: Установить ритм-паттерн (скорость 1 при их отсутствии)";
    strings["0Axy: Volume slide (0y: down; x0: up)##seen"].plurals[0] = "0Axy: Изменение громкости (0y: вниз; x0: вверх)";
    strings["0Bxx: Jump to pattern##seen"].plurals[0] = "0Bxx: Прыжок на паттерн";
    strings["0Cxx: Retrigger##seen"].plurals[0] = "0Cxx: Циклич. перезапуск";
    strings["0Dxx: Jump to next pattern##seen"].plurals[0] = "0Dxx: Przeskocz do nast. wzorca";
    strings["0Fxx: Set speed (speed 2 if no grooves exist)##seen"].plurals[0] = "0Fxx: Установить скорость (скорость 2 при отсутствии ритм-паттернов)";
    strings["80xx: Set panning (00: left; 80: center; FF: right)##seen"].plurals[0] = "80xx: Panning (00: лево; 80: центр; FF: право)";
    strings["81xx: Set panning (left channel)##seen"].plurals[0] = "81xx: Panning (левый канал)";
    strings["82xx: Set panning (right channel)##seen"].plurals[0] = "82xx: Panning (правый канал)";
    strings["88xy: Set panning (rear channels; x: left; y: right)##seen"].plurals[0] = "88xy: Panning (задние каналы; x: левый; y: правый)";
    strings["89xx: Set panning (rear left channel)##seen"].plurals[0] = "89xx: Panning (задний левый канал)";
    strings["8Axx: Set panning (rear right channel)##seen"].plurals[0] = "8Axx: Panning (задний правый канал)";
    strings["Cxxx: Set tick rate (hz)##seen"].plurals[0] = "Cxxx: Установить частоту движка трекера (Гц)";
    strings["E0xx: Set arp speed##seen"].plurals[0] = "E0xx: Установить скорость арпеджио";
    strings["E1xy: Note slide up (x: speed; y: semitones)##seen"].plurals[0] = "E1xy: Портаменто вверх (x: скорость; y: полутонов)";
    strings["E2xy: Note slide down (x: speed; y: semitones)##seen"].plurals[0] = "E2xy: Портаменто вниз (x: скорость; y: полутонов)";
    strings["E3xx: Set vibrato shape (0: up/down; 1: up only; 2: down only)##seen"].plurals[0] = "E3xx: Тип вибрато (0: вверх/вниз; 1: только вверх; 2: только вниз)";
    strings["E4xx: Set vibrato range##seen"].plurals[0] = "E4xx: Установить глубину вибрато";
    strings["E5xx: Set pitch (80: center)##seen"].plurals[0] = "E5xx: Расстройка (80: без расстройки)";
    strings["EAxx: Legato##seen"].plurals[0] = "EAxx: Legato";
    strings["EBxx: Set LEGACY sample mode bank##seen"].plurals[0] = "EBxx: (СОВМЕСТИМОСТЬ) Установить банк сэмплов";
    strings["ECxx: Note cut##seen"].plurals[0] = "ECxx: Заглушить ноту";
    strings["EDxx: Note delay##seen"].plurals[0] = "EDxx: Задержать ноту";
    strings["EExx: Send external command##seen"].plurals[0] = "EExx: Послать внешнюю команду";
    strings["F0xx: Set tick rate (bpm)##seen"].plurals[0] = "F0xx: Установить частоту движка трекера (BPM)";
    strings["F1xx: Single tick note slide up##seen"].plurals[0] = "F1xx: Портаменто вверх (один шаг движка)";
    strings["F2xx: Single tick note slide down##seen"].plurals[0] = "F2xx: Портаменто вниз (один шаг движка)";
    strings["F3xx: Fine volume slide up##seen"].plurals[0] = "F3xx: Точное изменение громкости вверх";
    strings["F4xx: Fine volume slide down##seen"].plurals[0] = "F4xx: Точное изменение громкости вниз";
    strings["F5xx: Disable macro (see manual)##seen"].plurals[0] = "F5xx: Отключить макрос (см. инструкцию)";
    strings["F6xx: Enable macro (see manual)##seen"].plurals[0] = "F6xx: Включить макрос (см. инструкцию)";
    strings["F7xx: Restart macro (see manual)##seen"].plurals[0] = "F7xx: Перезапустить макрос (см. инструкцию)";
    strings["F8xx: Single tick volume slide up##seen"].plurals[0] = "F8xx: Изменение громкости вверх (один шаг движка)";
    strings["F9xx: Single tick volume slide down##seen"].plurals[0] = "F9xx: Изменение громкости вниз (один шаг движка)";
    strings["FAxx: Fast volume slide (0y: down; x0: up)##seen"].plurals[0] = "FAxx: Быстрое изменение громкости (0y: вниз; x0: вверх)";
    strings["FFxx: Stop song##seen"].plurals[0] = "FFxx: Zatrzymaj utwór";
    strings["9xxx: Set sample offset*256##seen"].plurals[0] = "9xxx: Начальное смещение сэмпла (xxx*256 шагов)";

    //   sesd    src/engine/sysDef.cpp

    strings["20xx: Set channel mode (bit 0: square; bit 1: noise; bit 2: envelope)##sesd"].plurals[0] = "20xx: Режим канала (bit 0: меандр; bit 1: szum; bit 2: огибающая)";
    strings["21xx: Set noise frequency (0 to 1F)##sesd"].plurals[0] = "21xx: Частота шума (0-1F)";
    strings["22xy: Set envelope mode (x: shape, y: enable for this channel)##sesd"].plurals[0] = "22xy: Режим огибающей (x: форма, y: включить для этого канала)";
    strings["23xx: Set envelope period low byte##sesd"].plurals[0] = "23xx: Младший байт периода огибающей";
    strings["24xx: Set envelope period high byte##sesd"].plurals[0] = "24xx: Старший байт периода огибающей";
    strings["25xx: Envelope slide up##sesd0"].plurals[0] = "25xx: Portamento obwiedni w górę";
    strings["26xx: Envelope slide down##sesd0"].plurals[0] = "26xx: Portamento obwiedni w dół";
    strings["29xy: Set auto-envelope (x: numerator; y: denominator)##sesd0"].plurals[0] = "29xy: Авто-огибающая (x: числитель; y: знаменатель)";
    strings["2Exx: Write to I/O port A##sesd"].plurals[0] = "2Exx: Запись в порт ввода-вывода A";
    strings["2Fxx: Write to I/O port B##sesd"].plurals[0] = "2Fxx: Запись в порт ввода-вывода B";
    strings["12xx: Set duty cycle (0 to 8)##sesd"].plurals[0] = "12xx: Szerokość pulsu (0-8)";
    strings["27xx: Set noise AND mask##sesd"].plurals[0] = "27xx: Маска шума И";
    strings["28xx: Set noise OR mask##sesd"].plurals[0] = "28xx: Маска шума ИЛИ";
    strings["2Dxx: NOT TO BE EMPLOYED BY THE COMPOSER##sesd"].plurals[0] = "2Dxx: НЕ ДЛЯ ИСПОЛЬЗОВАНИЯ КОМПОЗИТОРОМ";
    strings["30xx: Toggle hard envelope reset on new notes##sesd"].plurals[0] = "30xx: Переключить жёсткий перезапуск огибающей на новой ноте";
    strings["18xx: Toggle extended channel 3 mode##sesd"].plurals[0] = "18xx: Переключить расширенный режим 3-го канала";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd0"].plurals[0] = "17xx: Переключить режим ИКМ (СОВМЕСТИМОСТЬ)";
    strings["DFxx: Set sample playback direction (0: normal; 1: reverse)##sesd0"].plurals[0] = "DFxx: Направление проигрывания сэмпла (0: обычное; 1: обратное)";
    strings["18xx: Toggle drums mode (1: enabled; 0: disabled)##sesd"].plurals[0] = "18xx: Переключить режим ударных (1: включить; 0: выключить)";
    strings["11xx: Set feedback (0 to 7)##sesd0"].plurals[0] = "11xx: Обратная связь (0-7)";
    strings["12xx: Set level of operator 1 (0 highest, 7F lowest)##sesd"].plurals[0] = "12xx: Уровень оператора 1 (0 макс., 7F мин.)";
    strings["13xx: Set level of operator 2 (0 highest, 7F lowest)##sesd"].plurals[0] = "13xx: Уровень оператора 2 (0 макс., 7F мин.)";
    strings["14xx: Set level of operator 3 (0 highest, 7F lowest)##sesd"].plurals[0] = "14xx: Уровень оператора 3 (0 макс., 7F мин.)";
    strings["15xx: Set level of operator 4 (0 highest, 7F lowest)##sesd"].plurals[0] = "15xx: Уровень оператора 4 (0 макс., 7F мин.)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd0"].plurals[0] = "16xy: Множитель частоты (x: оператор (1-4); y: множитель)";
    strings["19xx: Set attack of all operators (0 to 1F)##sesd"].plurals[0] = "19xx: Атака всех операторов (0-1F)";
    strings["1Axx: Set attack of operator 1 (0 to 1F)##sesd"].plurals[0] = "1Axx: Атака оператора 1 (0-1F)";
    strings["1Bxx: Set attack of operator 2 (0 to 1F)##sesd"].plurals[0] = "1Bxx: Атака оператора 2 (0-1F)";
    strings["1Cxx: Set attack of operator 3 (0 to 1F)##sesd"].plurals[0] = "1Cxx: Атака оператора 3 (0-1F)";
    strings["1Dxx: Set attack of operator 4 (0 to 1F)##sesd"].plurals[0] = "1Dxx: Атака оператора 4 (0-1F)";
    strings["50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd0"].plurals[0] = "50xy: Включить АМ (x: оператор 1-4 (0 для всех операторов); y: АМ)";
    strings["51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd0"].plurals[0] = "51xy: Уровень сустейна (x: оператор 1-4 (0 для всех операторов); y: уровень)";
    strings["52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd0"].plurals[0] = "52xy: Релиз (x: оператор 1-4 (0 для всех операторов); y: релиз)";
    strings["53xy: Set detune (x: operator from 1 to 4 (0 for all ops); y: detune where 3 is center)##sesd"].plurals[0] = "53xy: Расстройка (x: оператор 1-4 (0 для всех операторов); y: расстройка (3 - без расстройки))";
    strings["54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd0"].plurals[0] = "54xy: Масш. огиб. (x: оператор 1-4 (0 для всех операторов); y: масш. 0-3)";
    strings["56xx: Set decay of all operators (0 to 1F)##sesd"].plurals[0] = "56xx: Спад всех операторов (0-1F)";
    strings["57xx: Set decay of operator 1 (0 to 1F)##sesd"].plurals[0] = "57xx: Спад оператора 1 (0-1F)";
    strings["58xx: Set decay of operator 2 (0 to 1F)##sesd"].plurals[0] = "58xx: Спад оператора 2 (0-1F)";
    strings["59xx: Set decay of operator 3 (0 to 1F)##sesd"].plurals[0] = "59xx: Спад оператора 3 (0-1F)";
    strings["5Axx: Set decay of operator 4 (0 to 1F)##sesd"].plurals[0] = "5Axx: Спад оператора 4 (0-1F)";
    strings["5Bxx: Set decay 2 of all operators (0 to 1F)##sesd"].plurals[0] = "5Bxx: Спад 2 всех операторов (0-1F)";
    strings["5Cxx: Set decay 2 of operator 1 (0 to 1F)##sesd"].plurals[0] = "5Cxx: Спад 2 оператора 1 (0-1F)";
    strings["5Dxx: Set decay 2 of operator 2 (0 to 1F)##sesd"].plurals[0] = "5Dxx: Спад 2 оператора 2 (0-1F)";
    strings["5Exx: Set decay 2 of operator 3 (0 to 1F)##sesd"].plurals[0] = "5Exx: Спад 2 оператора 3 (0-1F)";
    strings["5Fxx: Set decay 2 of operator 4 (0 to 1F)##sesd"].plurals[0] = "5Fxx: Спад 2 оператора 4 (0-1F)";
    strings["10xx: Set noise frequency (xx: value; 0 disables noise)##sesd"].plurals[0] = "10xx: Частота шума (xx: частота; 0 отключает шум)";
    strings["17xx: Set LFO speed##sesd"].plurals[0] = "17xx: Ustaw prędkość LFO";
    strings["18xx: Set LFO waveform (0 saw, 1 square, 2 triangle, 3 noise)##sesd"].plurals[0] = "18xx: Форма волны ГНЧ (0 пила, 1 меандр, 2 треуг., 3 шум)";
    strings["1Exx: Set AM depth (0 to 7F)##sesd"].plurals[0] = "1Exx: Глубина АМ (0-7F)";
    strings["1Fxx: Set PM depth (0 to 7F)##sesd"].plurals[0] = "1Fxx: Глубина ФМ (0-7F)";
    strings["55xy: Set detune 2 (x: operator from 1 to 4 (0 for all ops); y: detune from 0 to 3)##sesd"].plurals[0] = "55xy: Расстройка 2 (x: оператор 1-4 (0 для всех операторов); y: расстройка 0-3)";
    strings["24xx: Set LFO 2 speed##sesd"].plurals[0] = "24xx: Ustaw prędkość LFO 2";
    strings["25xx: Set LFO 2 waveform (0 saw, 1 square, 2 triangle, 3 noise)##sesd"].plurals[0] = "25xx: Форма волны ГНЧ 2 (0 пила, 1 меандр, 2 треуг., 3 шум)";
    strings["26xx: Set AM 2 depth (0 to 7F)##sesd"].plurals[0] = "26xx: Глубина АМ 2 (0-7F)";
    strings["27xx: Set PM 2 depth (0 to 7F)##sesd"].plurals[0] = "27xx: Глубина ФМ 2 (0-7F)";
    strings["28xy: Set reverb (x: operator from 1 to 4 (0 for all ops); y: reverb from 0 to 7)##sesd"].plurals[0] = "28xy: Реверб (x: оператор 1-4 (0 для всех операторов); y: реверб 0-7)";
    strings["2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 7)##sesd0"].plurals[0] = "2Axy: Форма волны (x: оператор 1-4 (0 для всех операторов); y: форма волны 0-7)";
    strings["2Bxy: Set envelope generator shift (x: operator from 1 to 4 (0 for all ops); y: shift from 0 to 3)##sesd"].plurals[0] = "2Bxy: Сдвиг генератора огибающей (x: оператор 1-4 (0 для всех операторов); y: сдвиг 0-3)";
    strings["2Cxy: Set fine multiplier (x: operator from 1 to 4 (0 for all ops); y: fine)##sesd"].plurals[0] = "2Cxy: Точный множитель (x: оператор 1-4 (0 для всех операторов); y: множитель)";
    strings["3xyy: Set fixed frequency of operator 1 (x: octave from 0 to 7; y: frequency)##sesd"].plurals[0] = "3xyy: Установить фиксированную частоту оператора 1 (x: октава 0-7; y: частота)";
    strings["3xyy: Set fixed frequency of operator 2 (x: octave from 8 to F; y: frequency)##sesd"].plurals[0] = "3xyy: Установить фиксированную частоту оператора 2 (x: октава 8-F; y: частота)";
    strings["4xyy: Set fixed frequency of operator 3 (x: octave from 0 to 7; y: frequency)##sesd"].plurals[0] = "4xyy: Установить фиксированную частоту оператора 3 (x: октава 0-7; y: частота)";
    strings["4xyy: Set fixed frequency of operator 4 (x: octave from 8 to F; y: frequency)##sesd"].plurals[0] = "4xyy: Установить фиксированную частоту оператора 4 (x: октава 8-F; y: частота)";
    strings["10xy: Setup LFO (x: enable; y: speed)##sesd"].plurals[0] = "10xy: Настройка ГНЧ (x: включить; y: скорость)";
    strings["55xy: Set SSG envelope (x: operator from 1 to 4 (0 for all ops); y: 0-7 on, 8 off)##sesd"].plurals[0] = "55xy: Obwiednia SSG (x: оператор 1-4 (0 для всех операторов); y: 0-7 вкл., 8 выкл.)";
    strings["1Fxx: Set ADPCM-A global volume (0 to 3F)##sesd"].plurals[0] = "1Fxx: Глобальная громкость ADPCM-A (0-3F)";
    strings["11xx: Set feedback (0 to 7)##sesd1"].plurals[0] = "11xx: Обратная связь (0-7)";
    strings["12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd0"].plurals[0] = "12xx: Уровень оператора 1 (0 макс., 3F мин.)";
    strings["13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd0"].plurals[0] = "13xx: Уровень оператора 2 (0 макс., 3F мин.)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 2; y: multiplier)##sesd"].plurals[0] = "16xy: Множитель частоты (x: оператор 1-2; y: множитель)";
    strings["19xx: Set attack of all operators (0 to F)##sesd0"].plurals[0] = "19xx: Атака всех операторов (0-F)";
    strings["1Axx: Set attack of operator 1 (0 to F)##sesd0"].plurals[0] = "1Axx: Атака оператора 1 (0-F)";
    strings["1Bxx: Set attack of operator 2 (0 to F)##sesd0"].plurals[0] = "1Bxx: Атака оператора 2 (0-F)";
    strings["50xy: Set AM (x: operator from 1 to 2 (0 for all ops); y: AM)##sesd"].plurals[0] = "50xy: Включить АМ (x: оператор 1-2 (0 для всех операторов); y: АМ)";
    strings["51xy: Set sustain level (x: operator from 1 to 2 (0 for all ops); y: sustain)##sesd"].plurals[0] = "51xy: Уровень сустейна (x: оператор 1-2 (0 для всех операторов); y: сустейн)";
    strings["52xy: Set release (x: operator from 1 to 2 (0 for all ops); y: release)##sesd"].plurals[0] = "52xy: Релиз (x: оператор 1-2 (0 для всех операторов); y: релиз)";
    strings["53xy: Set vibrato (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd"].plurals[0] = "53xy: Вибрато (x: оператор 1-2 (0 для всех операторов); y: вкл.)";
    strings["54xy: Set envelope scale (x: operator from 1 to 2 (0 for all ops); y: scale from 0 to 3)##sesd"].plurals[0] = "54xy: Масш. огиб. (x: оператор 1-2 (0 для всех операторов); y: масш. 0-3)";
    strings["55xy: Set envelope sustain (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd"].plurals[0] = "55xy: Сустейн огибающей (x: оператор 1-2 (0 для всех операторов); y: вкл.)";
    strings["56xx: Set decay of all operators (0 to F)##sesd0"].plurals[0] = "56xx: Спад всех операторов (0-F)";
    strings["57xx: Set decay of operator 1 (0 to F)##sesd0"].plurals[0] = "57xx: Спад оператора 1 (0-F)";
    strings["58xx: Set decay of operator 2 (0 to F)##sesd0"].plurals[0] = "58xx: Спад оператора 2 (0-F)";
    strings["5Bxy: Set whether key will scale envelope (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd"].plurals[0] = "5Bxy: Масштаб. огиб. в зав. от ноты (x: оператор 1-2 (0 для всех операторов); y: вкл.)";
    strings["10xx: Set global AM depth (0: 1dB, 1: 4.8dB)##sesd"].plurals[0] = "10xx: Глобальная глубина АМ (0: 1 дБ, 1: 4.8 дБ)";
    strings["11xx: Set feedback (0 to 7)##sesd2"].plurals[0] = "11xx: Обратная связь (0-7)";
    strings["12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd1"].plurals[0] = "12xx: Уровень оператора 1 (0 макс., 3F мин.)";
    strings["13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd1"].plurals[0] = "13xx: Уровень оператора 2 (0 макс., 3F мин.)";
    strings["14xx: Set level of operator 3 (0 highest, 3F lowest)##sesd0"].plurals[0] = "14xx: Уровень оператора 3 (0 макс., 3F мин.)";
    strings["15xx: Set level of operator 4 (0 highest, 3F lowest)##sesd0"].plurals[0] = "15xx: Уровень оператора 4 (0 макс., 3F мин.)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd1"].plurals[0] = "16xy: Множитель частоты (x: оператор 1-4; y: множитель)";
    strings["17xx: Set global vibrato depth (0: normal, 1: double)##sesd"].plurals[0] = "17xx: Глобальная глубина вибрато (0: нормальная, 1: двойная)";
    strings["19xx: Set attack of all operators (0 to F)##sesd1"].plurals[0] = "19xx: Атака всех операторов (0-F)";
    strings["1Axx: Set attack of operator 1 (0 to F)##sesd1"].plurals[0] = "1Axx: Атака оператора 1 (0-F)";
    strings["1Bxx: Set attack of operator 2 (0 to F)##sesd1"].plurals[0] = "1Bxx: Атака оператора 2 (0-F)";
    strings["1Cxx: Set attack of operator 3 (0 to F)##sesd0"].plurals[0] = "1Cxx: Атака оператора 3 (0-F)";
    strings["1Dxx: Set attack of operator 4 (0 to F)##sesd0"].plurals[0] = "1Dxx: Атака оператора 4 (0-F)";
    strings["2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 3 in OPL2 and 0 to 7 in OPL3)##sesd"].plurals[0] = "2Axy: Форма волны (x: оператор 1-4 (0 для всех операторов); y: форма волны 0-3 для OPL2 и 0-7 для OPL3)";
    strings["50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd1"].plurals[0] = "50xy: Включить АМ (x: оператор 1-4 (0 для всех операторов); y: АМ)";
    strings["51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd1"].plurals[0] = "51xy: Уровень сустейна (x: оператор 1-4 (0 для всех операторов); y: сустейн)";
    strings["52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd1"].plurals[0] = "52xy: Релиз (x: оператор 1-4 (0 для всех операторов); y: релиз)";
    strings["53xy: Set vibrato (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0"].plurals[0] = "53xy: Вибрато (x: оператор 1-4 (0 для всех операторов); y: вкл.)";
    strings["54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd1"].plurals[0] = "54xy: Масш. огиб. (x: оператор 1-4 (0 для всех операторов); y: масш. 0-3)";
    strings["55xy: Set envelope sustain (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0"].plurals[0] = "55xy: Сустейн огибающей (x: оператор 1-4 (0 для всех операторов); y: вкл.)";
    strings["56xx: Set decay of all operators (0 to F)##sesd1"].plurals[0] = "56xx: Спад всех операторов (0-F)";
    strings["57xx: Set decay of operator 1 (0 to F)##sesd1"].plurals[0] = "57xx: Спад оператора 1 (0-F)";
    strings["58xx: Set decay of operator 2 (0 to F)##sesd1"].plurals[0] = "58xx: Спад оператора 2 (0-F)";
    strings["59xx: Set decay of operator 3 (0 to F)##sesd0"].plurals[0] = "59xx: Спад оператора 3 (0-F)";
    strings["5Axx: Set decay of operator 4 (0 to F)##sesd0"].plurals[0] = "5Axx: Спад оператора 4 (0-F)";
    strings["5Bxy: Set whether key will scale envelope (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0"].plurals[0] = "5Bxy: Масштаб. огиб. в зав. от ноты (x: оператор 1-4 (0 для всех операторов); y: вкл.)";
    strings["10xx: Set waveform (bit 0: triangle; bit 1: saw; bit 2: pulse; bit 3: noise)##sesd"].plurals[0] = "10xx: Форма волны (bit 0: треуг.; bit 1: пила; bit 2: меандр; bit 3: шум)";
    strings["11xx: Set coarse cutoff (not recommended; use 4xxx instead)##sesd"].plurals[0] = "11xx: Грубая частота среза (не рекомендуется; используйте 4xxx)";
    strings["12xx: Set coarse pulse width (not recommended; use 3xxx instead)##sesd"].plurals[0] = "12xx: Грубая скважность (не рекомендуется; используйте 3xxx)";
    strings["13xx: Set resonance (0 to F)##sesd"].plurals[0] = "13xx: Резонанс (0-F)";
    strings["14xx: Set filter mode (bit 0: low pass; bit 1: band pass; bit 2: high pass)##sesd"].plurals[0] = "14xx: Режим фильтра (bit 0: ФНЧ; bit 1: ППФ; bit 2: ФВЧ)";
    strings["15xx: Set envelope reset time##sesd"].plurals[0] = "15xx: Установить время ресета огибающей";
    strings["1Axx: Disable envelope reset for this channel (1 disables; 0 enables)##sesd"].plurals[0] = "1Axx: Отключить ресет огибающей для этого канала (1 выкл.; 0 вкл.)";
    strings["1Bxy: Reset cutoff (x: on new note; y: now)##sesd"].plurals[0] = "1Bxy: Сбросить частоту среза (x: на след. ноте; y: сейчас)";
    strings["1Cxy: Reset pulse width (x: on new note; y: now)##sesd"].plurals[0] = "1Cxy: Сбросить скважность (x: на след. ноте; y: сейчас)";
    strings["1Exy: Change other parameters (LEGACY)##sesd"].plurals[0] = "1Exy: Изменить другие параметры (СОВМЕСТИМОСТЬ)";
    strings["20xy: Set attack/decay (x: attack; y: decay)##sesd"].plurals[0] = "20xy: Установить атаку/спад (x: атака; y: спад)";
    strings["21xy: Set sustain/release (x: sustain; y: release)##sesd"].plurals[0] = "21xy: Установить сустейн/релиз (x: сустейн; y: релиз)";
    strings["3xxx: Set pulse width (0 to FFF)##sesd"].plurals[0] = "3xxx: Скважность (0-FFF)";
    strings["4xxx: Set cutoff (0 to 7FF)##sesd"].plurals[0] = "4xxx: Частота среза (0-7FF)";
    strings["10xx: Set waveform##sesd0"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["20xx: Set PCM frequency##sesd"].plurals[0] = "20xx: Ustaw częstotliwość PCM";
    strings["10xy: Set AM depth (x: operator from 1 to 4 (0 for all ops); y: depth (0: 1dB, 1: 4.8dB))##sesd"].plurals[0] = "10xy: Глубина АМ (x: оператор 1-4 (0 для всех операторов); y: глубина (0: 1 дБ, 1: 4.8 дБ))";
    strings["12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd2"].plurals[0] = "12xx: Уровень оператора 1 (0 макс., 3F мин.)";
    strings["13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd2"].plurals[0] = "13xx: Уровень оператора 2 (0 макс., 3F мин.)";
    strings["14xx: Set level of operator 3 (0 highest, 3F lowest)##sesd1"].plurals[0] = "14xx: Уровень оператора 3 (0 макс., 3F мин.)";
    strings["15xx: Set level of operator 4 (0 highest, 3F lowest)##sesd1"].plurals[0] = "15xx: Уровень оператора 4 (0 макс., 3F мин.)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd2"].plurals[0] = "16xy: Множитель частоты (x: оператор 1-4; y: мнжитель)";
    strings["17xy: Set vibrato depth (x: operator from 1 to 4 (0 for all ops); y: depth (0: normal, 1: double))##sesd"].plurals[0] = "17xy: Глубина вибрато (x: оператор 1-4 (0 для всех операторов); y: глубина (0: нормальная, 1: удвоенная))";
    strings["19xx: Set attack of all operators (0 to F)##sesd"].plurals[0] = "19xx: Атака всех операторов (0-F)";
    strings["1Axx: Set attack of operator 1 (0 to F)##sesd2"].plurals[0] = "1Axx: Атака оператора 1 (0-F)";
    strings["1Bxx: Set attack of operator 2 (0 to F)##sesd2"].plurals[0] = "1Bxx: Атака оператора 1 (0-F)";
    strings["1Cxx: Set attack of operator 3 (0 to F)##sesd1"].plurals[0] = "1Cxx: Атака оператора 1 (0-F)";
    strings["1Dxx: Set attack of operator 4 (0 to F)##sesd1"].plurals[0] = "1Dxx: Атака оператора 1 (0-F)";
    strings["20xy: Set panning of operator 1 (x: left; y: right)##sesd"].plurals[0] = "20xy: Panning оператора 1 (x: лево; y: право)";
    strings["21xy: Set panning of operator 2 (x: left; y: right)##sesd"].plurals[0] = "21xy: Panning оператора 2 (x: лево; y: право)";
    strings["22xy: Set panning of operator 3 (x: left; y: right)##sesd"].plurals[0] = "22xy: Panning оператора 3 (x: лево; y: право)";
    strings["23xy: Set panning of operator 4 (x: left; y: right)##sesd"].plurals[0] = "23xy: Panning оператора 4 (x: лево; y: право)";
    strings["24xy: Set output level register (x: operator from 1 to 4 (0 for all ops); y: level from 0 to 7)##sesd"].plurals[0] = "24xy: Регистр выходного уровня (громкости) (x: оператор 1-4 (0 для всех операторов); y: уровень 0-7)";
    strings["25xy: Set modulation input level (x: operator from 1 to 4 (0 for all ops); y: level from 0 to 7)##sesd"].plurals[0] = "25xy: Уровень входной модуляции (x: оператор 1-4 (0 для всех операторов); y: уровень 0-7)";
    strings["26xy: Set envelope delay (x: operator from 1 to 4 (0 for all ops); y: delay from 0 to 7)##sesd"].plurals[0] = "26xy: Задержка огибающей (x: оператор 1-4 (0 для всех операторов); y: задержка 0-7)";
    strings["27xx: Set noise mode for operator 4 (x: mode from 0 to 3)##sesd"].plurals[0] = "27xx: Режим шума для оператора 4 (x: режим 0-3)";
    strings["2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 7)##sesd1"].plurals[0] = "2Axy: Форма волны (x: оператор 1-4 (0 для всех операторов); y: форма волны 0-7)";
    strings["2Fxy: Set fixed frequency block (x: operator from 1 to 4; y: octave from 0 to 7)##sesd"].plurals[0] = "2Fxy: Блок в режиме фиксированной частоты (x: оператор 1-4; y: октава 0-7)";
    strings["40xx: Set detune of operator 1 (80: center)##sesd"].plurals[0] = "40xx: Расстройка оператора 1 (80: без расстройки)";
    strings["41xx: Set detune of operator 2 (80: center)##sesd"].plurals[0] = "41xx: Расстройка оператора 2 (80: без расстройки)";
    strings["42xx: Set detune of operator 3 (80: center)##sesd"].plurals[0] = "42xx: Расстройка оператора 3 (80: без расстройки)";
    strings["43xx: Set detune of operator 4 (80: center)##sesd"].plurals[0] = "43xx: Расстройка оператора 4 (80: без расстройки)";
    strings["50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd2"].plurals[0] = "50xy: Включить АМ (x: оператор 1-4 (0 для всех операторов); y: АМ)";
    strings["51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd2"].plurals[0] = "51xy: Уровень сустейна (x: оператор 1-4 (0 для всех операторов); y: сустейн)";
    strings["52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd2"].plurals[0] = "52xy: Релиз (x: оператор 1-4 (0 для всех операторов); y: релиз)";
    strings["53xy: Set vibrato (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1"].plurals[0] = "53xy: Вибрато (x: оператор 1-4 (0 для всех операторов); y: вкл.)";
    strings["54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd2"].plurals[0] = "54xy: Масш. огиб. (x: оператор 1-4 (0 для всех операторов); y: масш. 0-3)";
    strings["55xy: Set envelope sustain (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1"].plurals[0] = "55xy: Сустейн огибающей (x: оператор 1-4 (0 для всех операторов); y: вкл.)";
    strings["56xx: Set decay of all operators (0 to F)##sesd2"].plurals[0] = "56xx: Спад всех операторов (0-F)";
    strings["57xx: Set decay of operator 1 (0 to F)##sesd2"].plurals[0] = "57xx: Спад оператора 1 (0-F)";
    strings["58xx: Set decay of operator 2 (0 to F)##sesd2"].plurals[0] = "58xx: Спад оператора 2 (0-F)";
    strings["59xx: Set decay of operator 3 (0 to F)##sesd1"].plurals[0] = "59xx: Спад оператора 3 (0-F)";
    strings["5Axx: Set decay of operator 4 (0 to F)##sesd1"].plurals[0] = "5Axx: Спад оператора 4 (0-F)";
    strings["5Bxy: Set whether key will scale envelope (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1"].plurals[0] = "5Bxy: Масштаб. огиб. в зав. от ноты (x: оператор 1-4 (0 для всех операторов); y: вкл.)";
    strings["3xyy: Set fixed frequency F-num of operator 1 (x: high 2 bits from 0 to 3; y: low 8 bits of F-num)##sesd"].plurals[0] = "3xyy: Частота в режиме фиксированной частоты для оператора 1 (x: два старших бита 0-3; y: 8 младших битов частоты)";
    strings["3xyy: Set fixed frequency F-num of operator 2 (x: high 2 bits from 4 to 7; y: low 8 bits of F-num)##sesd"].plurals[0] = "3xyy: Частота в режиме фиксированной частоты для оператора 2 (x: два старших бита 4-7; y: 8 младших битов частоты)";
    strings["3xyy: Set fixed frequency F-num of operator 3 (x: high 2 bits from 8 to B; y: low 8 bits of F-num)##sesd"].plurals[0] = "3xyy: Частота в режиме фиксированной частоты для оператора 3 (x: два старших бита 8-B; y: 8 младших битов частоты)";
    strings["3xyy: Set fixed frequency F-num of operator 4 (x: high 2 bits from C to F; y: low 8 bits of F-num)##sesd"].plurals[0] = "3xyy: Частота в режиме фиксированной частоты для оператора 4 (x: два старших бита C-F; y: 8 младших битов частоты)";
    strings["a chip which found its way inside mobile phones in the 2000's.\nas proprietary as it is, it passed away after losing to MP3 in the mobile hardware battle.##sesd"].plurals[0] = "чип, начавший появляться в мобильных телефонах в 2000-ые.\nнесмотря на проприетарность, он проиграл формату MP3 во время соперничества разных видов мобильного железа.";
    strings["<COMPOUND SYSTEM!>##sesd0"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["<COMPOUND SYSTEM!>##sesd1"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["a square/noise sound chip found on the Sega Master System, ColecoVision, Tandy, TI's own 99/4A and a few other places.##sesd"].plurals[0] = "чип с квадратными волнами и шумом, который был установлен в Sega Master System, ColecoVision, Tandy, собственном устройстве TI 99/4A и некоторых других местах.";
    strings["20xy: Set noise mode (x: preset freq/ch3 freq; y: thin pulse/noise)##sesd"].plurals[0] = "20xy: Режим шума (x: фикс. част./част. 3-го кан.; y: \"тонкая\" прямоуг. аолна/шум)";
    strings["<COMPOUND SYSTEM!>##sesd2"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["the most popular portable game console of the era.##sesd"].plurals[0] = "самая популярная портативная игровая консоль той эпохи.";
    strings["10xx: Set waveform##sesd1"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Set noise length (0: long; 1: short)##sesd"].plurals[0] = "11xx: Длина шума (0: длинный; 1: короткий)";
    strings["12xx: Set duty cycle (0 to 3)##sesd"].plurals[0] = "12xx: Ustaw szerokość pulsu (0-3)";
    strings["13xy: Setup sweep (x: time; y: shift)##sesd"].plurals[0] = "13xy: Сконфигурировать аппаратное портаменто (x: длительность; y: расстояние)";
    strings["14xx: Set sweep direction (0: up; 1: down)##sesd"].plurals[0] = "14xx: Направление аппаратного портаменто (0: вверх; 1: вниз)";
    strings["an '80s game console with a wavetable sound chip, popular in Japan.##sesd"].plurals[0] = "игровая консоль из 80-ых с чипом на волновых таблицах. Была популярна в Японии.";
    strings["10xx: Set waveform##sesd2"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Toggle noise mode##sesd0"].plurals[0] = "11xx: Włącz tryb szumu";
    strings["12xx: Setup LFO (0: disabled; 1: 1x depth; 2: 16x depth; 3: 256x depth)##sesd"].plurals[0] = "12xx: Настроить ГНЧ (0: выкл.; 1: глубина 1x; 2: глубина 16x; 3: глубина 256x)";
    strings["13xx: Set LFO speed##sesd"].plurals[0] = "13xx: Szybkość LFO";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd1"].plurals[0] = "17xx: Włącz tryb PCM (Przestarzały)";
    strings["also known as Famicom in Japan, it's the most well-known game console of the '80s.##sesd"].plurals[0] = "также известная в Японии как Famicom. Самая известная игровая консоль 80-ых.";
    strings["11xx: Write to delta modulation counter (0 to 7F)##sesd"].plurals[0] = "11xx: Запись в регистр дельта-счётчика (0-7F)";
    strings["12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1)##sesd0"].plurals[0] = "12xx: Скважность/режим шума (меандр: 0-3; шум: 0 или 1)";
    strings["13xy: Sweep up (x: time; y: shift)##sesd"].plurals[0] = "13xy: Аппаратное портаменто вверх (x: время; y: сдвиг)";
    strings["14xy: Sweep down (x: time; y: shift)##sesd"].plurals[0] = "14xy: Аппаратное портаменто вниз (x: время; y: сдвиг)";
    strings["15xx: Set envelope mode (0: envelope, 1: length, 2: looping, 3: constant)##sesd"].plurals[0] = "15xx: Режим огибающей (0: огибающая, 1: длина, 2: цикл, 3: постоянная)";
    strings["16xx: Set length counter (refer to manual for a list of values)##sesd"].plurals[0] = "16xx: Счётчик длины (список значений см. в инструкции)";
    strings["17xx: Set frame counter mode (0: 4-step, 1: 5-step)##sesd"].plurals[0] = "17xx: Режим счётчика кадров (0: 4 шага, 1: 5 шагов)";
    strings["18xx: Select PCM/DPCM mode (0: PCM; 1: DPCM)##sesd"].plurals[0] = "18xx: Выбрать режим ИКМ/ДИКМ (0: ИКМ; 1: ДИКМ)";
    strings["19xx: Set triangle linear counter (0 to 7F; 80 and higher halt)##sesd"].plurals[0] = "19xx: Линейный счётчик треуг. волны (0-7F; 80 и выше мгновенно останавливают волну)";
    strings["20xx: Set DPCM frequency (0 to F)##sesd"].plurals[0] = "20xx: Ustaw częstotliwość DPCM (0-F)";
    strings["<COMPOUND SYSTEM!>##sesd3"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["<COMPOUND SYSTEM!>##sesd4"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["this computer is powered by the SID chip, which had synthesizer features like a filter and ADSR.##sesd"].plurals[0] = "в этом компьютере стоит чип SID, который имеет продвинутый функционал, присущий синтезаторам, например, фильтр и ADSR-огибающую.";
    strings["this computer is powered by the SID chip, which had synthesizer features like a filter and ADSR.\nthis is the newer revision of the chip.##sesd"].plurals[0] = "в этом компьютере стоит чип SID, который имеет продвинутый функционал, присущий синтезаторам, например, фильтр и ADSR-огибающую.\nЭто более новая ревизия чипа.";
    strings["<COMPOUND SYSTEM!>##sesd5"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["like Neo Geo, but lacking the ADPCM-B channel since they couldn't connect the pins.##sesd"].plurals[0] = "to samo co Neo Geo, ale bez kanału ADPCM-B, ponieważ podłaczenie pinów ich przerosło.";
    strings["like Neo Geo, but lacking the ADPCM-B channel since they couldn't connect the pins.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.##sesd"].plurals[0] = "to samo co Neo Geo, ale bez kanału ADPCM-B, ponieważ podłaczenie pinów ich przerosło.\njest to układ w trybie rozszerzonego kanału, który zamienia drugi kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.";
    strings["this chip is everywhere! ZX Spectrum, MSX, Amstrad CPC, Intellivision, Vectrex...\nthe discovery of envelope bass helped it beat the SN76489 with ease.##sesd"].plurals[0] = "этот чип везде! ZX Spectrum, MSX, Amstrad CPC, Intellivision, Vectrex...\nОткрытие метода использования огибающей для баса легко позволило этому чипу победить SN76489.";
    strings["a computer from the '80s with full sampling capabilities, giving it a sound ahead of its time.##sesd"].plurals[0] = "komputer z lat 80-tych z pełnymi możliwościami samplingu, nadający mu brzmienie wyprzedzające swoją epokę.";
    strings["10xx: Toggle filter (0 disables; 1 enables)##sesd"].plurals[0] = "10xx: Włącz filtr (0 wył.; 1 wł.)";
    strings["11xx: Toggle AM with next channel##sesd"].plurals[0] = "11xx: Переключить АМ со следующим каналом";
    strings["12xx: Toggle period modulation with next channel##sesd"].plurals[0] = "12xx: Переключить модуляцию периода со следующим каналом";
    strings["13xx: Set waveform##sesd"].plurals[0] = "13xx: Ustaw kształt fali";
    strings["this was Yamaha's first integrated FM chip.\nit was used in several synthesizers, computers and arcade boards.##sesd"].plurals[0] = "układ ten był pierwszym jednoukładowym syntezatorem FM Yamahy\nbył używany w kilku syntezatorach, komputerach i automatach do gier..";
    strings["this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).##sesd"].plurals[0] = "этот чип в основном известен по причине того, что он находился в Sega Genesis (но он также использовался в компьютере FM Towns).";
    strings["it's a challenge to make music on this chip which barely has musical capabilities...##sesd"].plurals[0] = "на этом чипе очень сложно писать музыку, ведь он едва ли обладает музыкальными возможностями...";
    strings["supposedly an upgrade from the AY-3-8910, this was present on the Creative Music System (Game Blaster) and SAM Coupé.##sesd"].plurals[0] = "этот чип, судя по всему, улучшенная версия AY-3-8910, использовался в Creative Music System (Game Blaster) и SAM Coupé.";
    strings["10xy: Set channel mode (x: noise; y: tone)##sesd"].plurals[0] = "10xy: Режим канала (x: шум; y: тон)";
    strings["11xx: Set noise frequency##sesd"].plurals[0] = "11xx: Частота шума";
    strings["12xx: Setup envelope (refer to docs for more information)##sesd"].plurals[0] = "12xx: Настройка огибающей (см. инструкцию)";
    strings["an improved version of the AY-3-8910 with a bigger frequency range, duty cycles, configurable noise and per-channel envelopes!##sesd"].plurals[0] = "улучшенная версия AY-3-8910 с большим диапазоном частот, настройкой скважности, настраиваемым шумом и огибвющей на каждый канал!";
    strings["Commodore's successor to the PET.\nits square wave channels are more than just square...##sesd"].plurals[0] = "Компьютер Commodore, вышедший после PET.\nего каналы квадратных волн могут играть не только лишь квадратные волны...";
    strings["one channel of 1-bit wavetable which is better (and worse) than the PC Speaker.##sesd"].plurals[0] = "один канал 1-битной волновой таблицы, что лучше (или хуже), чем PC Speaker (пищалка).";
    strings["FM? nah... samples! Nintendo's answer to Sega.##sesd"].plurals[0] = "FM? nieee,sample! Odpowiedź Nintendo na sukces Segi.";
    strings["18xx: Enable echo buffer##sesd"].plurals[0] = "18xx: Включить эхо-буфер";
    strings["19xx: Set echo delay (0 to F)##sesd"].plurals[0] = "19xx: Задержка эхо (0-F)";
    strings["1Axx: Set left echo volume##sesd"].plurals[0] = "1Axx: Głośność эхо на левом канале";
    strings["1Bxx: Set right echo volume##sesd"].plurals[0] = "1Bxx: Głośność эхо на правом канале";
    strings["1Cxx: Set echo feedback##sesd"].plurals[0] = "1Cxx: Обратная связь эхо";
    strings["1Exx: Set dry output volume (left)##sesd"].plurals[0] = "1Exx: Głośność канала (лево)";
    strings["1Fxx: Set dry output volume (right)##sesd"].plurals[0] = "1Fxx: Głośność канала (право)";
    strings["30xx: Set echo filter coefficient 0##sesd"].plurals[0] = "30xx: Коэффициент 0 фильтра эхо";
    strings["31xx: Set echo filter coefficient 1##sesd"].plurals[0] = "31xx: Коэффициент 1 фильтра эхо";
    strings["32xx: Set echo filter coefficient 2##sesd"].plurals[0] = "32xx: Коэффициент 2 фильтра эхо";
    strings["33xx: Set echo filter coefficient 3##sesd"].plurals[0] = "33xx: Коэффициент 3 фильтра эхо";
    strings["34xx: Set echo filter coefficient 4##sesd"].plurals[0] = "34xx: Коэффициент 4 фильтра эхо";
    strings["35xx: Set echo filter coefficient 5##sesd"].plurals[0] = "35xx: Коэффициент 5 фильтра эхо";
    strings["36xx: Set echo filter coefficient 6##sesd"].plurals[0] = "36xx: Коэффициент 6 фильтра эхо";
    strings["37xx: Set echo filter coefficient 7##sesd"].plurals[0] = "37xx: Коэффициент 7 фильтра эхо";
    strings["10xx: Set waveform##sesd3"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Toggle noise mode##sesd1"].plurals[0] = "11xx: Переключить режим шума";
    strings["12xx: Toggle echo on this channel##sesd"].plurals[0] = "12xx: Переключить эхо наэтом канале";
    strings["13xx: Toggle pitch modulation##sesd"].plurals[0] = "13xx: Переключить частотную модуляцию";
    strings["14xy: Toggle invert (x: left; y: right)##sesd"].plurals[0] = "14xy: Переключить инвертирование сигнала (x: левый; y: правый)";
    strings["15xx: Set envelope mode (0: ADSR, 1: gain/direct, 2: dec, 3: exp, 4: inc, 5: bent)##sesd"].plurals[0] = "15xx: Режим огибающей (0: ADSR, 1: усиление/прямой, 2: спад, 3: экспоненциальная, 4: нарастание, 5: изогн.)";
    strings["16xx: Set gain (00 to 7F if direct; 00 to 1F otherwise)##sesd"].plurals[0] = "16xx: Усиление (00-7F в прямом режиме; иначе 00-1F)";
    strings["1Dxx: Set noise frequency (00 to 1F)##sesd"].plurals[0] = "1Dxx: Ustaw częstotliwość szumu (00-1F)";
    strings["20xx: Set attack (0 to F)##sesd"].plurals[0] = "20xx: Ustaw atak (0-F)";
    strings["21xx: Set decay (0 to 7)##sesd"].plurals[0] = "21xx: Ustaw opadanie (0-7)";
    strings["22xx: Set sustain (0 to 7)##sesd"].plurals[0] = "22xx: Ustaw podtrzymanie (0-7)";
    strings["23xx: Set release (00 to 1F)##sesd"].plurals[0] = "23xx: Ustaw zwolnienie (00-1F)";
    strings["an expansion chip for the Famicom, featuring a quirky sawtooth channel.##sesd"].plurals[0] = "układ rozszerzający dla Famicoma, zawierający bardzo nietypowy kanał fali piłokształtnej.";
    strings["12xx: Set duty cycle (pulse: 0 to 7)##sesd"].plurals[0] = "12xx: Ustaw szerokość pulsu (puls: 0-7)";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd2"].plurals[0] = "17xx: włącz tryb PCM (PRZESTARZAŁY)";
    strings["cost-reduced version of the OPL with 16 patches and only one of them is user-configurable.##sesd"].plurals[0] = "удешевлённая версия OPL с 16-ю патчами, причём только один из них доступен для настройки пользователем.";
    strings["a disk drive for the Famicom which also contains one wavetable channel.##sesd"].plurals[0] = "stacja dyskietek dla Famicoma, która przy okazji dostarcza jeden kanał syntezy tablicowej";
    strings["10xx: Set waveform##sesd4"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Set modulation depth##sesd"].plurals[0] = "11xx: Глуюина модуляции";
    strings["12xy: Set modulation speed high byte (x: enable; y: value)##sesd"].plurals[0] = "12xy: Старший байт скорости модуляции (x: вкл.; y: значение)";
    strings["13xx: Set modulation speed low byte##sesd"].plurals[0] = "13xx: Младший байт скорости модуляции";
    strings["14xx: Set modulator position##sesd"].plurals[0] = "14xx: Положение модулятора";
    strings["15xx: Set modulator table to waveform##sesd"].plurals[0] = "15xx: Ustaw tablicę modulacji na dany kształt fali";
    strings["an expansion chip for the Famicom, featuring a little-known PCM channel.##sesd"].plurals[0] = "układ rozszerzający dla Famicoma,, posiadający mało znany kanał PCM";
    strings["12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1)##sesd1"].plurals[0] = "12xx: Скважность/режим шума (меандр: 0-3; шум: 0 или 1)";
    strings["an expansion chip for the Famicom, with full wavetable.##sesd"].plurals[0] = "układ rozszerzający dla Famicoma, który jest pełnoprawnym syntezatorem tablicowym.";
    strings["18xx: Change channel limits (0 to 7, x + 1)##sesd"].plurals[0] = "18xx: Изменить лимит каналов (0-7, x + 1)";
    strings["20xx: Load a waveform into memory##sesd"].plurals[0] = "20xx: Wczytaj falę do pamięci";
    strings["21xx: Set position for wave load##sesd"].plurals[0] = "21xx: Задать начальное смещение для загрузки волны";
    strings["10xx: Select waveform##sesd"].plurals[0] = "10xx: Выбрать волну";
    strings["11xx: Set waveform position in RAM##sesd"].plurals[0] = "11xx: Задать положение волны в ОЗУ";
    strings["12xx: Set waveform length in RAM (04 to FC in steps of 4)##sesd"].plurals[0] = "12xx: Задать длину волны в ОЗУ (04-FC с шагом 4)";
    strings["15xx: Set waveform load position##sesd"].plurals[0] = "15xx: Задать положение для загрузки волны";
    strings["16xx: Set waveform load length (04 to FC in steps of 4)##sesd"].plurals[0] = "16xx: Задать длину загружаемой волны (04-FC с шагом 4)";
    strings["cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)##sesd"].plurals[0] = "удешевлённая версия OPM с другим расположением регистров и отсутствием стерео...\n...но у неё внутри AY-3-8910! (на самом деле YM2149)";
    strings["cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies##sesd"].plurals[0] = "удешевлённая версия OPM с другим расположением регистров и отсутствием стерео...\n...но у неё внутри AY-3-8910! (на самом деле YM2149)\nЭто версия в режиме расширенного канала, который превращает третий FM-канал в четыре оператора с независимыми нотами/частотами.";
    strings["cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "удешевлённая версия OPM с другим расположением регистров и отсутствием стерео...\n...но у неё внутри AY-3-8910! (на самом деле YM2149)\nЭто версия в режиме расширенного канала, который превращает третий FM-канал в четыре оператора с независимыми нотами/частотами.\nУ этой версии есть контроль режима CSM для специальных эффектов на третьем канале.";
    strings["OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.##sesd"].plurals[0] = "OPN, но вдвое больше FM-каналов, возвращённое стерео, ритм- и АДИКМ каналы.";
    strings["OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies##sesd"].plurals[0] = "OPN, но вдвое больше FM-каналов, возвращённое стерео, ритм- и АДИКМ каналы.\nЭто версия в режиме расширенного канала, который превращает третий FM-канал в четыре оператора с независимыми нотами/частотами.";
    strings["OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "OPN, но вдвое больше FM-каналов, возвращённое стерео, ритм- и АДИКМ каналы.\nЭто версия в режиме расширенного канала, который превращает третий FM-канал в четыре оператора с независимыми нотами/частотами.\nУ этой версии есть контроль режима CSM для специальных эффектов на третьем канале.";
    strings["OPN, but what if you only had two operators, no stereo, no detune and a lower ADSR parameter range?##sesd"].plurals[0] = "OPN, но что если у него всего два оператора, нет стерео, нет расстройки и меньший диапазон регулировки параметров ADSR?";
    strings["OPL, but what if you had more waveforms to choose than the normal sine?##sesd"].plurals[0] = "OPL, но что если у него есть ещё волны, помимо синусоиды?";
    strings["OPL2, but what if you had twice the channels, 4-op mode, stereo and even more waveforms?##sesd"].plurals[0] = "OPL2, но что если у него вдвое больше каналов, 4-оп режим, стерео и ещё больше волн?";
    strings["how many channels of PCM do you want?\nMultiPCM: yes##sesd"].plurals[0] = "Сколько каналов ИКМ-сэмплов вам нужно?\nMultiPCM: да";
    strings["good luck! you get one square and no volume control.##sesd"].plurals[0] = "удачи! у вас один канал меандра и нет регулировки громкости.";
    strings["please don't use this chip. it was added as a joke.##sesd"].plurals[0] = "пожалуйста, не используйте этот чип. он был добавлен в качестве шутки.";
    strings["TIA, but better and more flexible.\nused in the Atari 8-bit family of computers (400/800/XL/XE).##sesd"].plurals[0] = "TIA, ale lepsze i prostsze w obsłudze\nbył używany w rodzinie 8-bitowych komputerów Atari (400/800/XL/XE).";
    strings["10xx: Set waveform (0 to 7)##sesd0"].plurals[0] = "10xx: Ustaw kształt fali (0-7)";
    strings["11xx: Set AUDCTL##sesd"].plurals[0] = "11xx: Ustaw AUDCTL";
    strings["12xx: Toggle two-tone mode##sesd"].plurals[0] = "12xx: włącz tryb dwóch głosów";
    strings["this is like SNES' sound chip but without interpolation and the rest of nice bits.##sesd"].plurals[0] = "podobny do układu dźwiękowego SNES, ale bez interpolacji i innych fajnych ficzerów";
    strings["developed by the makers of the Game Boy and the Virtual Boy...##sesd"].plurals[0] = "zaprojektowany prze twórcó Game Boy'a i Virtual Boy'a...";
    strings["10xx: Set waveform##sesd5"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Setup noise mode (0: disabled; 1-8: enabled/tap)##sesd"].plurals[0] = "11xx: Skonfiguruj tryb szumu (0: wył.; 1-8: wł./przełączniki)";
    strings["12xx: Setup sweep period (0: disabled; 1-20: enabled/period)##sesd"].plurals[0] = "12xx: Настроить период аппаратного портаменто (0: выкл.; 1-20: вкл./период)";
    strings["13xx: Set sweep amount##sesd"].plurals[0] = "13xx: Скорость аппаратного портаменто";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd3"].plurals[0] = "17xx: Włącz tryb PCM (PRZESTARZAŁY)";
    strings["like OPM, but with more waveforms, fixed frequency mode and totally... undocumented.\nused in the Yamaha TX81Z and some other synthesizers.##sesd"].plurals[0] = "как OPM, но с большим количеством волн, режимом фиксированной частоты, и полным... отсутствием сведений о его устройстве.\nиспользовался в Yamaha TX81Z и некоторых других синтезаторах.";
    strings["2Fxx: Toggle hard envelope reset on new notes##sesd"].plurals[0] = "2Fxx: Переключить жёсткий перезапуск огибающей на новой ноте";
    strings["this one is like PC Speaker but has duty cycles.##sesd"].plurals[0] = "ten układ jest podobny do PC Speakera, ale ma zmienną szerokość fali prostokątnej";
    strings["used in some Sega arcade boards (like OutRun), and usually paired with a YM2151.##sesd"].plurals[0] = "był używany w niektórych automatach do gier Segi (np. OutRun) i był zwykle używany w połączeniu z YM2151.";
    strings["a console which failed to sell well due to its headache-inducing features.##sesd"].plurals[0] = "konsola, która się nie sprzedawałą, ponieważ jej funkcje przyprawiały graczy o ból głowy.";
    strings["10xx: Set waveform##sesd6"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Set noise length (0 to 7)##sesd"].plurals[0] = "11xx: Ustaw długość szumu (0-7)";
    strings["12xy: Setup envelope (x: enabled/loop (1: enable, 3: enable+loop); y: speed/direction (0-7: down, 8-F: up))##sesd"].plurals[0] = "12xy: Skonfiguruj obwiednię (x: wł./zapętla (1: wł., 3: wł.i zapętla); y: prędkość/kierunek (0-7: w dół, 8-F: w górę))";
    strings["13xy: Setup sweep (x: speed; y: shift; channel 5 only)##sesd"].plurals[0] = "13xy: Настройка аппаратного портаменто (x: скорость; y: количество; только для 5-го канала)";
    strings["14xy: Setup modulation (x: enabled/loop (1: enable, 3: enable+loop); y: speed; channel 5 only)##sesd"].plurals[0] = "14xy: Настроить модуляцию (x: вкл./цикл (1: вкл., 3: вкл.+цикл); y: скорость; только для 5-го канала)";
    strings["15xx: Set modulation waveform (x: wavetable; channel 5 only)##sesd"].plurals[0] = "15xx: Ustaw kształt fali modulatora (x: tablica fal; tylko kanał 5)";
    strings["like OPLL, but even more cost reductions applied. three less FM channels, and no drums mode...##sesd"].plurals[0] = "jak OPLL, ale jeszcze bardziej wykastrowany. trzy kanały mniej, brak trybu perkusyjnego...";
    strings["so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.##sesd"].plurals[0] = "a więc Taito poprosiło Yamahę o dodanie do YM2610 dwóch brakujących kanałów FM, a Yamaha z przyjemnością dostarczyła ów układ.";
    strings["the ZX Spectrum only had a basic beeper capable of...\n...a bunch of thin pulses and tons of other interesting stuff!\nFurnace provides a thin pulse system.##sesd"].plurals[0] = "ZX Spectrum miał tylko prosty brzęczyk zdolny do generowania\n...kilku \"wąskich\" fal prostokątnych i wielu innych ciekawych dźwięków!\nFurnace dostarcza silnik z \"wąskimi\" falami prostokątnymi.";
    strings["12xx: Set pulse width##sesd0"].plurals[0] = "12xx: Ustaw szerokość pulsu";
    strings["17xx: Trigger overlay drum##sesd"].plurals[0] = "17xx: Uruchom nakładkę perkusyjną";
    strings["this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.##sesd"].plurals[0] = "układ ten znany jest głównie z tego, że znajduje się w Sega Mega Drive (ale był również używany w komputerze FM Towns).\njest to układ w trybie rozszerzonego kanału, która zamienia trzeci kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.";
    strings["this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "układ ten znany jest głównie z tego, że znajduje się w Sega Mega Drive (ale był również używany w komputerze FM Towns).\nten układ posiada kontrolę trybu CSM dla efektów specjalnych na trzecim kanale.";
    strings["a wavetable chip made by Konami for use with the MSX.\nthe last channel shares its wavetable with the previous one though.##sesd"].plurals[0] = "syntezator tablicowy wyprodukowany przez Konami do użytku z MSX.\nostatni i przedostatni kanał korzystają z tej samej tablicy fal.";
    strings["the OPL chip but with drums mode enabled.##sesd"].plurals[0] = "układ OPL z włączonym trybem perkusji.";
    strings["the OPL2 chip but with drums mode enabled.##sesd"].plurals[0] = "układ OPL2 z włączonym trybem perkusji.";
    strings["the OPL3 chip but with drums mode enabled.##sesd"].plurals[0] = "układ OPL3 z włączonym trybem perkusji.";
    strings["this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.##sesd"].plurals[0] = "układ ten był używany w automatach i konsolach do gier Neo Geo firmy SNK.\njest podobny do OPNA, ale kanały perkusyjne są teraz kanałami ADPCM i brakuje dwóch kanałów FM.";
    strings["this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.##sesd"].plurals[0] = "układ ten był używany w automatach i konsolach do gier Neo Geo firmy SNK.\njest podobny do OPNA, ale kanały perkusyjne są teraz kanałami ADPCM i brakuje dwóch kanałów FM.\njest to układ w trybie rozszerzonego kanału, która zamienia drugi kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.";
    strings["this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 2.##sesd"].plurals[0] = "układ ten był używany w automatach i konsolach do gier Neo Geo firmy SNK.\njest podobny do OPNA, ale kanały perkusyjne są teraz kanałami ADPCM i brakuje dwóch kanałów FM.\njest to układ w trybie rozszerzonego kanału, która zamienia drugi kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.\nten układ posiada kontrolę trybu CSM dla efektów specjalnych na trzecim kanale.";
    strings["the OPLL chip but with drums mode turned on.##sesd"].plurals[0] = "układ OPLL z włączonym trybem perkusji.";
    strings["3xxx: Load LFSR (0 to FFF)##sesd"].plurals[0] = "3xxx: Załaduj LFSR (0-FFF)";
    strings["a portable console made by Atari. it has all of Atari's trademark waveforms.##sesd"].plurals[0] = "przenośna konsola do gier od Atari. posiada wszystkie charakterystyczne dla Atari kształty fal";
    strings["10xx: Set echo feedback level (00 to FF)##sesd"].plurals[0] = "10xx: Ustaw poziom sprzężenia zwrotnego echa (00-FF)";
    strings["11xx: Set channel echo level (00 to FF)##sesd"].plurals[0] = "11xx: Ustaw poziom echa kanału (00-FF)";
    strings["12xx: Toggle QSound algorithm (0: disabled; 1: enabled)##sesd"].plurals[0] = "12xx: Włącz algorytm QSound (0: wył.; 1: wł.)";
    strings["3xxx: Set echo delay buffer length (000 to AA5)##sesd"].plurals[0] = "3xxx: Ustaw długość bufora opóźnienia echo (000-AA5)";
    strings["used in some of Capcom's arcade boards. surround-like sampled sound with echo.##sesd"].plurals[0] = "używany w niektórych automatach do gier Capcomu. samplowany dźwięk z echem i efektami dźwięku przestrzennego.";
    strings["the chip used in a computer design created by The 8-Bit Guy.##sesd"].plurals[0] = "układ używany w projekcie komputera opracowanym przez 8-Bit Guy'a.";
    strings["20xx: Set waveform##sesd"].plurals[0] = "20xx: Ustaw kształt fali";
    strings["22xx: Set duty cycle (0 to 3F)##sesd"].plurals[0] = "22xx: Ustaw szerokość pulsu (0-3F)";
    strings["so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.##sesd"].plurals[0] = "a więc Taito poprosiło Yamahę o dodanie do YM2610 dwóch brakujących kanałów FM, a Yamaha z przyjemnością dostarczyła ów układ.\njest to układ w trybie rozszerzonego kanału, która zamienia trzeci kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.";
    strings["so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "a więc Taito poprosiło Yamahę o dodanie do YM2610 dwóch brakujących kanałów FM, a Yamaha z przyjemnością dostarczyła ów układ.\njest to układ w trybie rozszerzonego kanału, która zamienia trzeci kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.\nten układ posiada kontrolę trybu CSM dla efektów specjalnych na trzecim kanale.";
    strings["this is the same thing as SegaPCM, but only exposes 5 of the channels for compatibility with DefleMask.##sesd"].plurals[0] = "jest to to samo co SegaPCM, ale tylko pięć kanałów jest dostępnych dla kompatybilności z DefleMaskiem.";
    strings["a sound chip used in several Seta/Allumer-manufactured arcade boards with too many channels of wavetable sound, which also are capable of sampled sound.##sesd"].plurals[0] = "układ dźwiękowy używany w kilku automatach go gier firmy Seta/Allumer. posiada stanowczo za dużo kanałów syntezy tablicowej, zdolny również do odtwarzania sampli.";
    strings["10xx: Set waveform##sesd7"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Set envelope shape##sesd"].plurals[0] = "11xx: Ustaw kształt obwiedni";
    strings["12xx: Set sample bank slot (0 to 7)##sesd"].plurals[0] = "12xx: Ustaw slot banków sampli (0-7)";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd4"].plurals[0] = "17xx: Włącz tryb PCM (PRZESTARZAŁY)";
    strings["20xx: Set PCM frequency (1 to FF)##sesd"].plurals[0] = "20xx: Ustaw częstotliwość PCM (1-FF)";
    strings["22xx: Set envelope mode (bit 0: enable; bit 1: one-shot; bit 2: split shape to L/R; bit 3/5: H.invert right/left; bit 4/6: V.invert right/left)##sesd"].plurals[0] = "22xx: Ustaw tryb obwiedni (bit 0: wł.; bit 1: jednokrotny.; bit 2: rozdziel kształt fali na lewo/prawo; bity 3/5: odwróć pionowo na prawo/lewo; bity 4/6: odwróć poziomo na prawo/lewo)";
    strings["23xx: Set envelope period##sesd"].plurals[0] = "23xx: Ustaw okres obwiedni";
    strings["25xx: Envelope slide up##sesd1"].plurals[0] = "25xx: Portamento obwiedni w górę";
    strings["26xx: Envelope slide down##sesd1"].plurals[0] = "26xx: Portamento obwiedni w dół";
    strings["29xy: Set auto-envelope (x: numerator; y: denominator)##sesd1"].plurals[0] = "29xy: Auto-obwiednia (x: licznik; y: mianownik)";
    strings["this is the wavetable part of the Bubble System, which also had two AY-3-8910s.##sesd"].plurals[0] = "jest syntezatorową częścią Bubble Systemu, który również posiadał dwa AY-3-8910.";
    strings["like OPL3, but this time it also has a 24-channel version of MultiPCM.##sesd"].plurals[0] = "to samo co OPL3, ale z 24 kanałami PCM na bazie układu MultiPCM.";
    strings["the OPL4 but with drums mode turned on.##sesd"].plurals[0] = "OPL4 z włączonym trybem perkusji.";
    strings["11xx: Set filter mode (00 to 03)##sesd"].plurals[0] = "11xx: Ustaw tryb filtra (00-03)";
    strings["14xx: Set filter coefficient K1 low byte (00 to FF)##sesd"].plurals[0] = "14xx: Ustaw niski bit współczynnika filtra K1 (00-FF)";
    strings["15xx: Set filter coefficient K1 high byte (00 to FF)##sesd"].plurals[0] = "15xx: Ustaw wysoki bit współczynnika filtra K1 (00-FF)";
    strings["16xx: Set filter coefficient K2 low byte (00 to FF)##sesd"].plurals[0] = "16xx: Ustaw niski bit współczynnika filtra K2 (00-FF)";
    strings["17xx: Set filter coefficient K2 high byte (00 to FF)##sesd"].plurals[0] = "17xx: Ustaw wysoki bit współczynnika filtra K2 (00-FF)";
    strings["18xx: Set filter coefficient K1 slide up (00 to FF)##sesd"].plurals[0] = "18xx: Ustaw zjazd spółczynnika filtra K1 w górę (00-FF)";
    strings["19xx: Set filter coefficient K1 slide down (00 to FF)##sesd"].plurals[0] = "19xx: Ustaw zjazd spółczynnika filtra K1 w dół (00-FF)";
    strings["1Axx: Set filter coefficient K2 slide up (00 to FF)##sesd"].plurals[0] = "1Axx: Ustaw zjazd spółczynnika filtra K2 w górę (00-FF)";
    strings["1Bxx: Set filter coefficient K2 slide down (00 to FF)##sesd"].plurals[0] = "1Bxx: Ustaw zjazd spółczynnika filtra K1 w dół (00 to FF)";
    strings["22xx: Set envelope left volume ramp (signed) (00 to FF)##sesd"].plurals[0] = "22xx: Ustaw narastanie obwiedni głośności lewej strony (ze znakiem) (00-FF)";
    strings["23xx: Set envelope right volume ramp (signed) (00 to FF)##sesd"].plurals[0] = "23xx: Ustaw narastanie obwiedni głośności prawej strony (ze znakiem) (00-FF)";
    strings["24xx: Set envelope filter coefficient k1 ramp (signed) (00 to FF)##sesd"].plurals[0] = "24xx:  Ustaw narastanie obwiedni wspólczynnika filtra K1 (ze znakiem) (00-FF)";
    strings["25xx: Set envelope filter coefficient k1 ramp (signed, slower) (00 to FF)##sesd"].plurals[0] = "25xx: Ustaw narastanie obwiedni wspólczynnika filtra K1 (ze znakiem, wolniej) (00-FF)";
    strings["26xx: Set envelope filter coefficient k2 ramp (signed) (00 to FF)##sesd"].plurals[0] = "26xx: Ustaw narastanie obwiedni wspólczynnika filtra K2 (ze znakiem) (00-FF)";
    strings["27xx: Set envelope filter coefficient k2 ramp (signed, slower) (00 to FF)##sesd"].plurals[0] = "27xx: 25xx: Ustaw narastanie obwiedni wspólczynnika filtra K2 (ze znakiem, wolniej) (00-FF)";
    strings["DFxx: Set sample playback direction (0: normal; 1: reverse)##sesd1"].plurals[0] = "DFxx: Ustaw kieruynek odtwarzania sampla (0: normalny; 1: odwrotny)";
    strings["120x: Set pause (bit 0)##sesd"].plurals[0] = "120x: Ustaw pauzę (bit 0)";
    strings["2xxx: Set envelope count (000 to 1FF)##sesd"].plurals[0] = "2xxx: Ustaw długość obwiedni (000-1FF)";
    strings["3xxx: Set filter coefficient K1 (000 to FFF)##sesd"].plurals[0] = "3xxx: Współczynnik filtra K1 (000-FFF)";
    strings["4xxx: Set filter coefficient K2 (000 to FFF)##sesd"].plurals[0] = "4xxx: Współczynnik filtra K2 (000-FFF)";
    strings["a sample chip made by Ensoniq, which is the basis for the GF1 chip found in Gravis' Ultrasound cards.##sesd"].plurals[0] = "sampler Ensoniqa, który był podstawą układu GF1 używanego w kartach dźwiękowych Gravis Ultrasound..";
    strings["like OPL but with an ADPCM channel.##sesd"].plurals[0] = "OPL, ale z dodatkowym kanałem ADPCM.";
    strings["the Y8950 chip, in drums mode.##sesd"].plurals[0] = "układ Y8950 w trybie perkusji.";
    strings["this is a variant of Konami's SCC chip with the last channel's wavetable being independent.##sesd"].plurals[0] = "wariant układu SCC firmy Konami z niezależną tablicą fal ostatniego kanału.";
    strings["10xx: Set waveform (0 to 7)##sesd1"].plurals[0] = "10xx: Ustaw kształt fali (0-7)";
    strings["12xx: Set pulse width (0 to 7F)##sesd"].plurals[0] = "12xx: Ustaw szerokość pulsu (0-7F)";
    strings["13xx: Set resonance (0 to FF)##sesd"].plurals[0] = "13xx: Ustaw rezonans (0-FF)";
    strings["14xx: Set filter mode (bit 0: ring mod; bit 1: low pass; bit 2: high pass; bit 3: band pass)##sesd"].plurals[0] = "14xx: Ustaw tryb filtra (bit 0: modulacja kołowa; bit 1: dolno-przepustowy; bit 2: środkowo-przepustowy; bit 3: górno-przepustowy)";
    strings["15xx: Set frequency sweep period low byte##sesd"].plurals[0] = "15xx: Ustaw wysoki bajt okresu sprzętowego portamento";
    strings["16xx: Set frequency sweep period high byte##sesd"].plurals[0] = "16xx: Ustaw niski bajt okresu sprzętowego portamento";
    strings["17xx: Set volume sweep period low byte##sesd"].plurals[0] = "17xx: Ustaw wysoki bajt okresu sprzętowej zmiany głośniości";
    strings["18xx: Set volume sweep period high byte##sesd"].plurals[0] = "18xx: Ustaw niski bajt okresu sprzętowej zmiany głośniości";
    strings["19xx: Set cutoff sweep period low byte##sesd"].plurals[0] = "19xx: Ustaw wysoki bajt okresu sprzętowej zmiany punktu odcięcia filtra";
    strings["1Axx: Set cutoff sweep period high byte##sesd"].plurals[0] = "1Axx: Ustaw niski bajt okresu sprzętowej zmiany punktu odcięcia filtra";
    strings["1Bxx: Set frequency sweep boundary##sesd"].plurals[0] = "1Bxx: Ustaw granicę sprzętowego poprtamento";
    strings["1Cxx: Set volume sweep boundary##sesd"].plurals[0] = "1Cxx: Ustaw granicę sprzętowej zmiany głośniości";
    strings["1Dxx: Set cutoff sweep boundary##sesd"].plurals[0] = "1Dxx: Granica sprzętowej zmiany punktu odcięcia filtra";
    strings["1Exx: Set phase reset period low byte##sesd"].plurals[0] = "1Exx: Ustaw niski bajt okresu resetu fazy";
    strings["1Fxx: Set phase reset period high byte##sesd"].plurals[0] = "1Fxx: Ustaw wysoki bajt okresu resetu fazy";
    strings["20xx: Toggle frequency sweep (bit 0-6: speed; bit 7: direction is up)##sesd"].plurals[0] = "20xx: Ustaw sprzętowe portamento (bity 0-6: szybkość; bit 7: kierunek w górę)";
    strings["21xx: Toggle volume sweep (bit 0-4: speed; bit 5: direction is up; bit 6: loop; bit 7: alternate)##sesd"].plurals[0] = "21xx: Włącz sprzętową zmianę głośności (bity 0-4: szybkość; bit 5: kierunek w górę; bit 6: zapętl; bit 7: naprzemiennie góra-dół)";
    strings["22xx: Toggle cutoff sweep (bit 0-6: speed; bit 7: direction is up)##sesd"].plurals[0] = "22xx: Włącz sprzętową zmianę punktu odcięcia filtra (bit 0-6: szybkość; bit 7: kierunek w górę)";
    strings["4xxx: Set cutoff (0 to FFF)##sesd"].plurals[0] = "4xxx: Ustaw punkt odcięcia (0-FFF)";
    strings["tildearrow's fantasy sound chip. put SID, AY and VERA in a blender, and you get this!##sesd"].plurals[0] = "fikcyjny układ dźwiękowy tildearrowa. wsadź SIDa, AY i VERA do blendera i otrzymasz ten układ!";
    strings["an ADPCM sound chip manufactured by OKI and used in many arcade boards.##sesd"].plurals[0] = "układ dźwiękowy ADPCM wyprodukowany przez firmę OKI. używany był w wielu maszynach arcade.";
    strings["20xx: Set chip output rate (0: clock/132; 1: clock/165)##sesd"].plurals[0] = "20xx: Częstotliwość samplowania układu (0: Taktowanie zegara/132; 1: Taktowanie zegara/165)";
    strings["an ADPCM sound chip manufactured by OKI and used in the Sharp X68000.##sesd"].plurals[0] = "układ dźwiękowy ADPCM firmy OKI, używany w Sharpie X68000.";
    strings["20xx: Set frequency divider (0-2)##sesd"].plurals[0] = "20xx: Ustaw dzielnik częstotliwości (0-2)";
    strings["21xx: Select clock rate (0: full; 1: half)##sesd"].plurals[0] = "21xx: Taktowanie zegara (0: pełne; 1: połowiczne)";
    strings["used in some arcade boards. Can play back either 4-bit ADPCM, 8-bit PCM or 16-bit PCM.##sesd"].plurals[0] = "używany w niektórych automatach do gier. może odtwarzać 4-bitowe próbki ADPCM, a także 8-bitowe i 16-bitowe próbki PCM";
    strings["10xx: Set waveform##sesd8"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["10xx: Set waveform##sesd9"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Toggle noise mode##sesd2"].plurals[0] = "11xx: Włącz tryb szumu";
    strings["a wavetable sound chip used in Pac-Man, among other early Namco arcade games.##sesd"].plurals[0] = "prosty syntezator tablicowy używany w automacie Pac-Mana i innych wczesnych grach Namco.";
    strings["successor of the original Namco WSG chip, used in later Namco arcade games.##sesd"].plurals[0] = "kolejny model po Namco WSG, używany w późniejszych automatach do gier Namco.";
    strings["like Namco C15 but with stereo sound.##sesd"].plurals[0] = "to samo co Namco C15, ale z dźwiękiem stereo.";
    strings["a square wave additive synthesis chip made by OKI. used in some arcade machines and instruments.##sesd"].plurals[0] = "układ syntezy addytywnej firmy OKI. używany w niektórych automatach do gier i instrumentach muzycznych.";
    strings["10xy: Set group control (x: sustain; y: part toggle bitmask)##sesd"].plurals[0] = "10xy: Ustaw kontrolę grupy (x: podtrzymanie; y: maska bitowa części)";
    strings["11xx: Set noise mode##sesd0"].plurals[0] = "11xx: Ustaw tryb szumu";
    strings["12xx: Set group attack (0 to 5)##sesd"].plurals[0] = "12xx: Ustaw atak grupy (0-5)";
    strings["13xx: Set group decay (0 to 11)##sesd"].plurals[0] = "13xx: Ustaw opadanie grupy (0-11)";
    strings["this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis system uses software mixing to provide two sample channels.##sesd"].plurals[0] = "układ ten znany jest głównie z tego, że znajduje się w Sega Mega Drive (ale był również używany w komputerze FM Towns).\nw ta wersja wykorzystuje programowe miksowanie sampli, dzięki czemu można odtwarzać dwa kanały sampli na raz.";
    strings["this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis system uses software mixing to provide two sample channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "układ ten znany jest głównie z tego, że znajduje się w Sega Mega Drive (ale był również używany w komputerze FM Towns).\nw ta wersja wykorzystuje programowe miksowanie sampli, dzięki czemu można odtwarzać dwa kanały sampli na raz.\njest to wersja która zamienia trzeci kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.\nta wersja posiada kontrolę trybu CSM dla efektów specjalnych na trzecim kanale";
    strings["an SN76489 derivative used in Neo Geo Pocket, has independent stereo volume and noise channel frequency.##sesd"].plurals[0] = "wariant SN76489 używany w Neo Geo Pocket. Posiada niezależną kontrolę głośności kanału stereo i częstotliwości kanału szumów.";
    strings["20xx: Set noise length (0: short, 1: long)##sesd"].plurals[0] = "20xx: Ustaw długość szumu (0: krótki, 1: długi)";
    strings["as generic sample playback as it gets.##sesd"].plurals[0] = "proste do bólu urządzenie do odtwarzania sampli.";
    strings["this PCM chip was widely used at Konami arcade boards in 1986-1990.##sesd"].plurals[0] = "ten układ PCM był szeroko stosowany w automatach do gier Konami w latach 1986-1990.";
    strings["yet another PCM chip from Irem. like Amiga, but less pitch resolution and no sample loop.##sesd"].plurals[0] = "kolejny układ PCM od firmy Irem. podobny do tego z Amigi, ale z mniejszą rozdzielczością kontroli częstotliwości i bez zapętlania sampli.";
    strings["a SoC with wavetable sound hardware.##sesd"].plurals[0] = "CPU z syntezatorem tablicowym.";
    strings["a game console with 3 channels of square wave. it's what happens after fusing TIA and VIC together.##sesd"].plurals[0] = "konsola do gier z trzema kanałami fali kwadratowej. oto, co otrzymujesz po skrzyżowaniu TIA i VIC.";
    strings["10xx: Set ring modulation (0: disable, 1: enable)##sesd"].plurals[0] = "10xx: Modulacja kołowa (0: wył., 1: wł.)";
    strings["another ZX Spectrum beeper system with full PWM pulses and 3-level volume per channel. it also has a pitchable overlay sample channel.##sesd"].plurals[0] = "kolejny system brzęczyka ZX Spectrum, tym razem zawierający pełnoprawne fale prostokątne z regulowaną szerokością i trzema poziomami głośności dla każdego kanału. ma również nakładający się ma inne kanały kanał sampli z kontrolą częstotliwości.";
    strings["12xx: Set pulse width##sesd1"].plurals[0] = "12xx: Ustaw szerokość pulsu";
    strings["this PCM chip was widely used at Konami arcade boards in 1990-1992.##sesd"].plurals[0] = "ten układ PCM był szeroko stosowany w automatach do gier Konami w latach 1990-1992.";
    strings["DFxx: Set sample playback direction (0: normal; 1: reverse)##sesd2"].plurals[0] = "DFxx: Ustaw kierunek odtwarzania sampli (0: normalny; 1: odwrotny)";
    strings["two square waves (one may be turned into noise). used in the Commodore Plus/4, 16 and 116.##sesd"].plurals[0] = "dwa kanały fali kwadratowej (jeden z nich może odtwarzać szum). używany w Commodore Plus/4, 16 i 116.";
    strings["Namco's first PCM chip from 1987. it's pretty good for being so.##sesd"].plurals[0] = "pierwszy układ PCM Namco z 1987r. Całkiem przyzwoity jak na swoje czasy.";
    strings["Namco's PCM chip used in their NA-1/2 hardware.\nvery similar to C140, but has noise generator.##sesd"].plurals[0] = "Układ PCM firmy Namco używany w urządzeniach NA-1/2.\nbardzo podobny do C140, ale ma generator szumu.";
    strings["11xx: Set noise mode##sesd1"].plurals[0] = "11xx: Ustaw tryb szumu";
    strings["12xy: Set invert mode (x: surround; y: invert)##sesd"].plurals[0] = "12xy: Ustwa tryb odwrotny (x: dźwięk przestrzenny; y: odwrotny.)";
    strings["a unique FM synth featured in PC sound cards.\nbased on the OPL3 design, but with lots of its features extended.##sesd"].plurals[0] = "unikalny układ syntezy FM stosowany w kartach dźwiękowych dla komputerów PC.\nopiera się na OPL3, ale ma znacznie rozszerzone możliwości syntezy.";
    strings["2Exx: Toggle hard envelope reset on new notes##sesd"].plurals[0] = "2Exx: Włącz twardy reset obwiedni przy nowej nucie";
    strings["first Ensoniq chip used in their synths and Apple IIGS computer. Has 32 hard-panned 8-bit wavetable/sample channels, can do oscillator sync (like SID) and amplitude modulation. Can have up to 128 KiB (2 banks of 64 KiB) of memory for wavetables/samples.\nAs Robert Yannes (SID chip creator) said, it's more or less what SID chip could be if he was given enough time for its development.##sesd"].plurals[0] = "pierwszy układ scalony firmy Ensoniq, wykorzystywany w syntezatorach i komputerze Apple IIGS. Posiada 32 kanały syntezy tablicowej / sampli z twardym panningiem, synchronizacją oscylatorów (tak jak SID) i modulacją amplitudy. Może mieć do 128 KiB (2 banki po 64 KiB każdy) pamięci na tablice fal/sample.\nJak powiedział Robert Yannes (twórca układu SID), ES5503 jest mniej więcej tym, czym mógłby być układ SID, gdyby miał wystarczająco dużo czasu na jego opracowanie.";
    strings["11xx: Set number of enabled oscillators (2-1F)##sesd"].plurals[0] = "11xx: Ustaw ilość włączonych oscylatorów (2-1F)";
    strings["12xx: Set oscillator output (0-7, 0=left, 1=right)##sesd"].plurals[0] = "12xx: Ustaw wyjście sygnału oscylatora (0-7, 0=lewo, 1=prawo)";
    strings["13xx: Set wave/sample length (0-7, 0=256, 1=512, 2=1024, etc.)##sesd"].plurals[0] = "13xx: Ustaw długości fali/sampla (0-7, 0=256, 1=512, 2=1024 i.t.d.)";
    strings["14xx: Set wave/sample position in memory (xx*256 offset)##sesd"].plurals[0] = "14xx: Ustaw położenie fali/sampla w pamięci (przesunięcie xx*256)";
    strings["15xx: Set oscillator mode (0-3)##sesd"].plurals[0] = "15xx: Ustaw tryb oscylatora (0-3)";
    strings["a fantasy sound chip designed by jvsTSX and The Beesh-Spweesh!\nused in the Hexheld fantasy console.##sesd"].plurals[0] = "fikcyjny układ dźwiękowy opracowany przez jvsTSX i The Beesh-Spweesh!\nużywany w fikcyjnej konsoli do gier Hexheld.";
    strings["20xx: Load low byte of noise channel LFSR (00 to FF) or slope channel accumulator (00 to 7F)##sesd"].plurals[0] = "20xx: Załaduj najmniej znaczący bajt do LFSRa kanału szumu (00-FF) lub akumulatora kanału spadka (00-7F)";
    strings["21xx: Load high byte of noise channel LFSR (00 to FF)##sesd"].plurals[0] = "21xx: Załaduj wysokiego bajtu do LFSR kanału szumu (00-FF)";
    strings["22xx: Write to I/O port A##sesd"].plurals[0] = "22xx: Zapisz do prtu I/O A";
    strings["23xx: Write to I/O port B##sesd"].plurals[0] = "23xx: Zapisz do portu I/O B";
    strings["this chip was featured in the Enterprise 128 computer. it is similar to POKEY, but with stereo output, more features and frequency precision and the ability to turn left or right (or both) channel into a 6-bit DAC for sample playback.##sesd"].plurals[0] = "Układ ten znajdował się w komputerze Enterprise 128. Jest podobny do POKEY, ale ma dźwięk stereo, więcej funkcji, dokładniejsze dostrajanie częstotliwości i możliwość zamiany lewego lub prawego (lub obu) kanału w 6-bitowy przetwornik cyfrowo-analogowy do odtwarzania sampli.";
    strings["10xx: Set waveform (0 to 4; 0 to 3 on noise)##sesd"].plurals[0] = "10xx: Ustaw kształt fali (0-4; 0-3 na kanale szumu)";
    strings["11xx: Set noise frequency source (0: fixed; 1-3: channels 1 to 3)##sesd"].plurals[0] = "11xx: Ustaw źródło częstotliwości szumu(0: stały, 1-3: kanały 1-3)";
    strings["12xx: Toggle high-pass with next channel##sesd"].plurals[0] = "12xx: Wlacz filtr gornoprzep. na nastepnym kanale";
    strings["13xx: Toggle ring modulation with channel+2##sesd"].plurals[0] = "13xx: Wlacz modulacje kolowa na kanale +2";
    strings["14xx: Toggle swap counters (noise only)##sesd"].plurals[0] = "14xx: Wlacz zamiane licznikow (tylko szum)";
    strings["15xx: Toggle low pass (noise only)##sesd"].plurals[0] = "15xx: Wlacz filtr dolnoprzep. (tylko szum)";
    strings["16xx: Set clock divider (0: /2; 1: /3)##sesd"].plurals[0] = "16xx: Ustaw dzielnik zegara (0: /2; 1: /3)";
    strings["this is a system designed for testing purposes.##sesd"].plurals[0] = "ten system jest przeznaczony do testowania.";

    strings["help! what's going on!"].plurals[0] = "pomocy! co się dzieje?";
    strings["Sunsoft 5B standalone##sesd"].plurals[0] = "Sunsoft 5B oddzielnie";
    strings["Sunsoft 5B standalone (PAL)##sesd"].plurals[0] = "Sunsoft 5B oddzielnie (PAL)";
    strings["Overclocked Sunsoft 5B##sesd"].plurals[0] = "Podkręcony Sunsoft 5B";
    strings["Sega Genesis Extended Channel 3##sesd0"].plurals[0] = "Sega Mega Drive z rozszerzonym kanałem 3";
    strings["NTSC-J Sega Master System + drums##sesd"].plurals[0] = "NTSC-J Sega Master System + perkusja";
    strings["MSX-MUSIC + drums##sesd"].plurals[0] = "MSX-MUSIC + perkusja";
    strings["Commodore 64 with dual 6581##sesd"].plurals[0] = "Commodore 64 z dwoma 6581";
    strings["Commodore 64 with dual 8580##sesd"].plurals[0] = "Commodore 64 z dwoma 8580";
    strings["YM2151 + SegaPCM Arcade (compatibility)##sesd"].plurals[0] = "YM2151 + SegaPCM Arcade (kompatybilny)";
    strings["YM2151 + SegaPCM Arcade##sesd"].plurals[0] = "YM2151 + SegaPCM Arcade";
    strings["Game Boy with AY expansion##sesd"].plurals[0] = "Game Boy z rozszerzeniem AY";
    strings["multi-system##sesd"].plurals[0] = "muti-system";
    strings["Unknown##sesd"].plurals[0] = "Nieznany";
    strings["Sega Genesis Extended Channel 3##sesd1"].plurals[0] = "Sega Mega Drive z rozszerzonym kanałem 3";
    strings["Neo Geo CD Extended Channel 2##sesd"].plurals[0] = "Neo Geo CD z rozszerzonym kanałem 2";
    strings["Famicom Disk System (chip)##sesd"].plurals[0] = "Famicom Disk System (sam chip)";
    strings["Yamaha YM2203 (OPN) Extended Channel 3##sesd"].plurals[0] = "Yamaha YM2203 (OPN) z rozszerzonym kanałem 3";
    strings["Yamaha YM2608 (OPNA) Extended Channel 3##sesd"].plurals[0] = "Yamaha YM2608 (OPNA) z rozszerzonym kanałem 3";
    strings["Yamaha YM2608 (OPNA) Extended Channel 3 and CSM##sesd"].plurals[0] = "Yamaha YM2608 (OPNA) z rozszerzonym kanałem 3 i CSM";
    strings["PC Speaker##sesd"].plurals[0] = "PC Speaker (brzęczyk)";
    strings["ZX Spectrum Beeper##sesd"].plurals[0] = "Brzęczyk ZX Spectrum";
    strings["Yamaha YM2612 (OPN2) Extended Channel 3##sesd"].plurals[0] = "Yamaha YM2612 (OPN2) z rozszerzonym kanałem 3";
    strings["Yamaha YM3526 (OPL) with drums##sesd"].plurals[0] = "Yamaha YM3526 (OPL) (tryb perkusji)";
    strings["Yamaha YM3812 (OPL2) with drums##sesd"].plurals[0] = "Yamaha YM3812 (OPL2) (tryb perkusji)";
    strings["Yamaha YMF262 (OPL3) with drums##sesd"].plurals[0] = "Yamaha YMF262 (OPL3) (tryb perkusji)";
    strings["Yamaha YM2610 (OPNB) Extended Channel 2##sesd"].plurals[0] = "Yamaha YM2610 (OPNB) z rozszerzonym kanałem 2";
    strings["Yamaha YM2413 (OPLL) with drums##sesd"].plurals[0] = "=Yamaha YM2413 (OPLL) (tryb perkusji)";
    strings["Yamaha YM2610B (OPNB2) Extended Channel 3##sesd"].plurals[0] = "Yamaha YM2610B (OPNB2) z rozszerzonym kanałem 3";
    strings["SegaPCM (compatible 5-channel mode)##sesd"].plurals[0] = "SegaPCM (kompatybilny tryb 5-kanałowy)";
    strings["Yamaha YMF278B (OPL4) with drums##sesd"].plurals[0] = "Yamaha YMF278B (OPL4) (tryb perkusji)";
    strings["Yamaha Y8950 with drums##sesd"].plurals[0] = "Yamaha Y8950 (tryb perkusji)";
    strings["Yamaha YM2612 (OPN2) with DualPCM##sesd"].plurals[0] = "Yamaha YM2612 (OPN2) z DualPCM";
    strings["Yamaha YM2612 (OPN2) Extended Channel 3 with DualPCM and CSM##sesd"].plurals[0] = "Yamaha YM2612 (OPN2) z rozszerzonym kanałem 3, DualPCM i CSM";
    strings["Generic PCM DAC##sesd"].plurals[0] = "Typowy przetwornik C/A";
    strings["ZX Spectrum Beeper (QuadTone Engine)##sesd"].plurals[0] = "Brzęczyk ZX Spectrum (silnik QuadTone)";
    strings["ESS ES1xxx series (ESFM)##sesd"].plurals[0] = "ESS serii ES1xxx (ESFM)";
    strings["Dummy System##sesd"].plurals[0] = "System-wydmuszka";
}
