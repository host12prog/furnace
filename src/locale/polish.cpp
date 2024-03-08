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
    strings["Kagamiin~ (Portuguese translation)##sgab"].plurals[0] = "Kagamiin~ (tłumaczenie na język portugalski)";
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
    strings["SID2 emulator (modification of reSID) by LTVA##sgab"].plurals[0] = "emulator SID2 (modyfikacja reSID) autorstwa LTVA";

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
    strings["Swap##sgch"].plurals[0] = "Zamień";
    strings["Name##sgch"].plurals[0] = "Nazwa";
    strings["Show in pattern##sgch"].plurals[0] = "Pokaż w oknie wzorców";
    strings["Show in per-channel oscilloscope##sgch"].plurals[0] = "Pokaż w oknie oscyloskopu dla poszczególnych kanałów";
    strings["%s #%d\n(drag to swap channels)##sgch"].plurals[0] = "%s #%d\n(przeciągnij by zamienić miejscami kanały)";

    //src/gui/chanOsc.cpp

    strings["None (0%)##sgco"].plurals[0] = "Brak (0%)";
    strings["None (50%)##sgco"].plurals[0] = "Brak (50%)";
    strings["None (100%)##sgco"].plurals[0] = "Brak (100%)";
    strings["Frequency##sgco"].plurals[0] = "Częstotliwość";
    strings["Volume##sgco"].plurals[0] = "Głośność";
    strings["Channel##sgco"].plurals[0] = "Kanał";
    strings["Brightness##sgco"].plurals[0] = "Jasność";
    strings["Note Trigger##sgco"].plurals[0] = "Nowa nuta";
    strings["Off##sgco"].plurals[0] = "Wył.";
    strings["Mode 1##sgco"].plurals[0] = "Tryb 1";
    strings["Mode 2##sgco"].plurals[0] = "Tryb 2";
    strings["Mode 3##sgco"].plurals[0] = "Tryb 3";

    strings["Columns##sgco"].plurals[0] = "Kolumny";
    strings["Size (ms)##sgco"].plurals[0] = "Rozmiar (w ms)";
    strings["Automatic columns##sgco"].plurals[0] = "Automatyczna ilość kolumn";
    strings["Center waveform##sgco"].plurals[0] = "Centruj falę";
    strings["Randomize phase on note##sgco"].plurals[0] = "Losowa faza przy nowej nucie";
    strings["Amplitude##sgco"].plurals[0] = "Amplituda";
    strings["Line size##sgco"].plurals[0] = "Grubość linii";
    strings["Gradient##sgco"].plurals[0] = "Gradient";
    strings["Color##sgco0"].plurals[0] = "Kolor";
    strings["Distance##sgco"].plurals[0] = "Dystans";
    strings["Spread##sgco"].plurals[0] = "Rozmycie";
    strings["Remove##sgco"].plurals[0] = "Usuń";
    strings["Background##sgco"].plurals[0] = "Kolor tła";
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
            "- %d: numer kanału (zaczynając od 0)\n"
            "- %D: numer kanału (zaczynając od 1)\n"
            "- %n: nuta kanału\n"
            "- %i: nazwa instrumentu\n"
            "- %I: numer instrumentu (dziesietny)\n"
            "- %x: numer instrumentu (szesnastkowy)\n"
            "- %s: nazwa ukladu\n"
            "- %p: numer wewnetrzny ukladu\n"
            "- %S: ID ukladu\n"
            "- %v: Głośność (dziesiętna)\n"
            "- %V: Głośność (w procentach)\n"
            "- %b: Głośność (szesnastkowa)\n"
            "- %l: nowy wiersz\n"
            "- %%: znak procenta";

    strings["Text color##sgco"].plurals[0] = "Kolor tekstu";
    strings["Error!##sgco"].plurals[0] = "Błąd!";
    strings["\nquiet##sgco"].plurals[0] = "\ncicho";

    //   sgcl  src/gui/clock.cpp

    strings["Clock###Clock"].plurals[0] = "Zegar###Clock";

    //   sgcp  src/gui/commandPalette.cpp

    strings["Search...##sgcp"].plurals[0] = "Wyszukuj...";
    strings["Search recent files...##sgcp"].plurals[0] = "Wyszukuj w ostatnio otwartych...";
    strings["Search instruments...##sgcp"].plurals[0] = "Wyszukuj instrumenty...";
    strings["Search samples...##sgcp"].plurals[0] = "Wyszukuj sample...";
    strings["Search instruments (to change to)...##sgcp"].plurals[0] = "Wyszukuj instrumenty (aby zmienić na)...";
    strings["Search chip (to add)...##sgcp"].plurals[0] = "Wyszukuj układ (aby dodać)...";
    strings["Cancel##sgcp"].plurals[0] = "Anuluj";
    strings["cannot add chip! (##sgcp"].plurals[0] = "nie udało się dodać układu! (";
    strings["- None -"].plurals[0] = "- Brak -";

    //   sgcf  src/gui/compatFlags.cpp

    strings["Compatibility Flags###Compatibility Flags"].plurals[0] = "Flagi kompatybilności###Compatibility Flags";
    strings["these flags are designed to provide better DefleMask/older Furnace compatibility.\nit is recommended to disable most of these unless you rely on specific quirks.##sgcf"].plurals[0] = "flagi te zostały zaprojektowane dla lepszej kompatybilności z DefleMaskiem/starszymi wersjami Furnace.\nznaleca się wyłączenie większości z nich, chyba że polegasz na specyfice działania programu, który zapewniają.";
    strings["Game Boy instrument duty is wave volume##sgcf"].plurals[0] = "Makro szerokości fali prostokątnej Game Boy'a kontroluje głośność kanału syntezy tablicowej";
    strings["if enabled, an instrument with duty macro in the wave channel will be mapped to wavetable volume.##sgcf"].plurals[0] = " ";
    strings["Restart macro on portamento##sgcf"].plurals[0] = "Restartuj makro podczas portamento";
    strings["when enabled, a portamento effect will reset the channel's macro if used in combination with a note.##sgcf"].plurals[0] = "gdy ta flaga jest włączona, efekt portamento umieszczony obok nuty spowoduje ponowne uruchomienie makr instrumentu.";
    strings["Ignore duplicate slide effects##sgcf"].plurals[0] = "Ignoruj powtarzające się efekty płynnej zmiany parametrów";
    strings["if this is on, only the first slide of a row in a channel will be considered.##sgcf"].plurals[0] = "gdy ta flaga jest włączona, tylko pierwszy efekt płynnej zmiany parametru w danym wierszu będzie skuteczny.";
    strings["Ignore 0Dxx on the last order##sgcf"].plurals[0] = "Ignoruj 0Dxx w ostatnim wierszu macierzy wzorca";
    strings["if this is on, a jump to next row effect will not take place when it is on the last order of a song.##sgcf"].plurals[0] = "jeśli flaga jest włączona, efekt przeskoczenia do następnego wzorca nie zadziała, jeśli jest odtwarzany ostatni wiersz matrycy wzorców.";
    strings["Don't apply Game Boy envelope on note-less instrument change##sgcf"].plurals[0] = "nie uzywaj obwiedni Game Boya przy zmianie instrumentu bez nuty";
    strings["if this is on, an instrument change will not affect the envelope.##sgcf"].plurals[0] = "gdy ta flaga jest włączona, zmiana instrumentu bez zmiany nuty nie będzie miała wpływu na obwiednię.";
    strings["Ignore DAC mode change outside of intended channel in ExtCh mode##sgcf"].plurals[0] = "Ignoruj przełączanie trybu DAC, poza odpowiednim kanałem, w trybie rozszerzonego kanału 3";
    strings["if this is on, 17xx has no effect on the operator channels in YM2612.##sgcf"].plurals[0] = "gdy ta flaga jest włączona, 17xx nie działa, jeśli jest umieszczony na operatorach rozszerzonego kanału 3 (dla YM2612).";
    strings["SN76489 duty macro always resets phase##sgcf"].plurals[0] = "Makro szumu SN76489 zawsze resetuje faze";
    strings["when enabled, duty macro will always reset phase, even if its value hasn't changed.##sgcf"].plurals[0] = "jeśli ta flaga jest włączona, makro szumu zawsze zresetuje fazę, nawet jeśli wartość makra szumu nie ulegnie zmianie.";
    strings["Don't persist volume macro after it finishes##sgcf"].plurals[0] = "Nie podtrzymuj wartości makra głośności po jego zakończeniu";
    strings["when enabled, a value in the volume column that happens after the volume macro is done will disregard the macro.##sgcf"].plurals[0] = "gdy ta flaga jest włączona, wartość w kolumnie głośności wysatępująca po zakończeniu makra głośności nie będzie uwzględniać wartości makra.";
    strings[".mod import##sgcf"].plurals[0] = "import .mod";
    strings["Don't slide on the first tick of a row##sgcf"].plurals[0] = "Nie wykonuj płynnej zmiany wysokości w pierwszym kroku silnika danego wiersza.";
    strings["simulates ProTracker's behavior of not applying volume/pitch slides on the first tick of a row.##sgcf"].plurals[0] = "symuluje zachowanie ProTrackera, który nie wykonuje zmian głośności i wysokości w pierwszym kroku kolumny.";
    strings["Reset arpeggio position on row change##sgcf"].plurals[0] = "Zresetuj pozycję arpeggio przy zmianie wiersza wzorca.";
    strings["simulates ProTracker's behavior of arpeggio being bound to the current tick of a row.##sgcf"].plurals[0] = "symuluje zachowanie programu ProTracker, który wiąże arpeggio z obecnym skokiem silnika w danym wierszu wzorca.";
    strings["Pitch/Playback##sgcf"].plurals[0] = "Wysokość dźwięku/odtwarzanie";
    strings["Pitch linearity:##sgcf"].plurals[0] = "Liniowość wysokości dźwięku:";
    strings["None##sgcf"].plurals[0] = "Brak (bezpośrednia)";
    strings["like ProTracker/FamiTracker##sgcf"].plurals[0] = "tak jak ProTracker/FamiTracker";
    strings["Full##sgcf"].plurals[0] = "Pełna";
    strings["like Impulse Tracker##sgcf"].plurals[0] = "tak jak Impulse Tracker";
    strings["Pitch slide speed multiplier##sgcf"].plurals[0] = "Mnożnik prędkości płynnej zmiany wysokości";
    strings["Loop modality:##sgcf"].plurals[0] = "Metoda zapętlania:";
    strings["Reset channels##sgcf"].plurals[0] = "Reset kanałów";
    strings["select to reset channels on loop. may trigger a voltage click on every loop!##sgcf"].plurals[0] = "wybierz, aby ponownie uruchomić kanały za każdym razem na początku cyklu. może powodować klikanie przy każdym rozpoczęciu cyklu z powodu zmian napięcia!";
    strings["Soft reset channels##sgcf"].plurals[0] = "Miękki reset kanałów";
    strings["select to turn channels off on loop.##sgcf"].plurals[0] = "wybierz aby wyłączyć kanały na początku cyklu.";
    strings["Do nothing##sgcf"].plurals[0] = "Nie rób nic";
    strings["select to not reset channels on loop.##sgcf"].plurals[0] = "wybierz aby nie wyłączać kanałów na początku cyklu.";
    strings["Cut/delay effect policy:##sgcf"].plurals[0] = "Zachowanie efektów odcinania/opóźniania nut:";
    strings["Strict##sgcf"].plurals[0] = "Ścisłe";
    strings["only when time is less than speed (like DefleMask/ProTracker)##sgcf"].plurals[0] = "tylko wtedy, gdy parametr jest mniejszy niż prędkość (tak jak DefleMask/ProTracker)";
    strings["Lax##sgcf"].plurals[0] = "Luźne";
    strings["no checks##sgcf"].plurals[0] = "bez sprawdzania";
    strings["Simultaneous jump (0B+0D) treatment:##sgcf"].plurals[0] = "Traktowanie równoczesnego skoku (0B+0D):";
    strings["Normal##sgcf"].plurals[0] = "Normalne";
    strings["accept 0B+0D to jump to a specific row of an order##sgcf"].plurals[0] = "przyjmuje 0B+0D jako skok do określonego wiersza wzorca w określonej pozycji macierzy wzorca";
    strings["Other##sgcf"].plurals[0] = "Inne";
    strings["Auto-insert one tick gap between notes##sgcf"].plurals[0] = "Automatycznie wstawia pauzę o długości 1 skoku silnika pomiędzy nutami.";
    strings["when enabled, a one-tick note cut will be inserted between non-legato/non-portamento notes.\nthis simulates the behavior of some Amiga/SNES music engines.\n\nineffective on C64.##sgcf"].plurals[0] = "dy ta flaga jest włączona, pomiędzy nutami zostanie wstawiona nuta wyciszenia o długości jednego kroku bez efektu legato i portamento. Jest to symulacja zachowania niektórych sterowników muzycznych Amigi/SNES.\n\nnie działa na C64";
    strings["Don't reset slides after note off##sgcf"].plurals[0] = "Nie inicjuj ponownie portamento po puszczeniu nuty";
    strings["when enabled, note off will not reset the channel's slide effect.##sgcf"].plurals[0] = "dy ta flaga jest włączona, puszczenie nuty nie zatrzyma portamento na tym kanale.";
    strings["Don't reset portamento after reaching target##sgcf"].plurals[0] = "Nie resetuj portamento po osiągnięciu celu.";
    strings["when enabled, the slide effect will not be disabled after it reaches its target.##sgcf"].plurals[0] = "jeśli ta flaga jest włączona, efekt portamento nie będzie ponownie inicjowany po osiągnięciu wysokości docelowej.";
    strings["Continuous vibrato##sgcf"].plurals[0] = "Ciągłe vibrato";
    strings["when enabled, vibrato phase/position will not be reset on a new note.##sgcf"].plurals[0] = "gdy ta flaga jest włączona, faza/pozycja vibrato nie będzie resetowana przy nowej nucie.";
    strings["Pitch macro is not linear##sgcf"].plurals[0] = "Makro wysokości dźwięku jest nieliniowe";
    strings["when enabled, the pitch macro of an instrument is in frequency/period space.##sgcf"].plurals[0] = "jeśli ta flaga jest włączona, makro częstotliwości będzie działać w odniesieniu do okresu/częstotliwości, a nie ułamków półtonu.";
    strings["Reset arpeggio effect position on new note##sgcf"].plurals[0] = "Reset pozycji efektu arpeggio dla nowej nuty";
    strings["when enabled, arpeggio effect (00xy) position is reset on a new note.##sgcf"].plurals[0] = "włączenie tej flagi resetuje pozycję efektu arpeggio (00xy) dla nowej nuty.";
    strings["Volume scaling rounds up##sgcf"].plurals[0] = "Skalowanie głośności zaokrągla w górę";
    strings["when enabled, volume macros round up when applied\nthis prevents volume scaling from causing vol=0, which is silent on some chips\n\nineffective on logarithmic channels##sgcf"].plurals[0] = "gdy ta flaga jest włączona, wartości makra głośności są zaokrąglane w górę\nzapobiega to sytuacji gdy vol=0 podczas skalowania, która powoduje wyciszenie na niektórych układach.\n\nnie działa na układach z logarytmiczną regulacją głośności";
    strings["Stop NES pulse channels hardware sweep on new note##sgcf"].plurals[0] = "Zatrzymaj sprzętowe portamento na kanałach fal prostokątnych NESa przy nowej nucie";
    strings["Do not stop volume slide after reaching zero or full volume##sgcf"].plurals[0] = "Nie zatrzymuj efektu płynnej zmiany głośności po osiągnięciu zerowej lub pełnej głośności";
    
    //   sgdl  src/gui/dataList.cpp

    strings["Bug!##sgdl"].plurals[0] = "Błąd!";
    strings["Unknown##sgdl"].plurals[0] = "Nieznany typ instrumentu";
    strings["duplicate##sgdl0"].plurals[0] = "duplikuj";
    strings["replace...##sgdl0"].plurals[0] = "zamień...";
    strings["save##sgdl0"].plurals[0] = "zapisz";
    strings["export (.dmp)##sgdl"].plurals[0] = "eksportuj .dmp";
    strings["delete##sgdl0"].plurals[0] = "usuń";
    strings["%.2X: <INVALID>##sgdl"].plurals[0] = "%.2X: <NIEPOPRAWNY>";
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
    strings["load instrument from TX81Z##sgdl"].plurals[0] = "załaduj instrument z TX81Z";
    strings["replace wavetable...##sgdl"].plurals[0] = "zamień tablice fal...";
    strings["replace sample...##sgdl"].plurals[0] = "zamień sampel...";
    strings["import raw sample...##sgdl"].plurals[0] = "importuj surowy sampel...";
    strings["import raw sample (replace)...##sgdl"].plurals[0] = "importuj surowy sampel (zamień)...";
    strings["replace...##sgdl2"].plurals[0] = "zamień...";
    strings["load from TX81Z##sgdl"].plurals[0] = "zaladuj z TX81Z";
    strings["Open (insert; right-click to replace)##sgdl"].plurals[0] = "Otwórz (wstaw; PPM by zastapic)";
    strings["Save##sgdl2"].plurals[0] = "Zapisz";
    strings["save instrument as .dmp...##sgdl"].plurals[0] = "zapisz instrument jako .dmp...";
    strings["save wavetable as .dmw...##sgdl"].plurals[0] = "zapisz tablicę fal jako .dmw...";
    strings["save raw wavetable...##sgdl"].plurals[0] = "zapisz surową tablice fal...";
    strings["save raw sample...##sgdl"].plurals[0] = "zapisz surowy sampel";
    strings["save as .dmp...##sgdl"].plurals[0] = "zapisz jako .dmp...";
    strings["Toggle folders/standard view##sgdl0"].plurals[0] = "Przełącz między widokiem złożonym i normalnym";
    strings["Move up##sgdl0"].plurals[0] = "Przesuń w górę o jedną pozycję";
    strings["Move down##sgdl0"].plurals[0] = "Przesuń w dół o jedną pozycję";
    strings["Create##sgdl0"].plurals[0] = "Stwórz";
    strings["New folder##sgdl0"].plurals[0] = "Nowy folder";
    strings["Preview (right click to stop)##sgdl0"].plurals[0] = "Podgląd (PPM aby zatrzymać)";
    strings["Delete##sgdl2"].plurals[0] = "Usuń";
    strings["Instruments##sgdl"].plurals[0] = "Instrumenty";
    strings["<uncategorized>##sgdl0"].plurals[0] = "<bez kategorii>";
    strings["rename...##sgdl0"].plurals[0] = "zmień nazwę...";
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
    strings["Move up##sgdl1"].plurals[0] = "Przesuń w górę o jedną pozycję";
    strings["Move down##sgdl1"].plurals[0] = "Przesuń w dół o jedną pozycję";
    strings["Create##sgdl1"].plurals[0] = "Stwórz";
    strings["New folder##sgdl1"].plurals[0] = "Nowy folder";
    strings["Delete##sgdl4"].plurals[0] = "Usuń";
    strings["Add##sgdl2"].plurals[0] = "Dodaj";
    strings["Duplicate##sgdl4"].plurals[0] = "Sklonuj";
    strings["Open##sgdl2"].plurals[0] = "Otwórz";
    strings["replace...##sgdl4"].plurals[0] = "zamień...";
    strings["import raw...##sgdl"].plurals[0] = "importuj dane surowe...";
    strings["import raw (replace)...##sgdl"].plurals[0] = "importuj dane surowe (zamień)...";
    strings["Save##sgdl4"].plurals[0] = "Zapisz";
    strings["save raw...##sgdl1"].plurals[0] = "zapisz dane surowe...";
    strings["Toggle folders/standard view##sgdl2"].plurals[0] = "Przełączanie między widokiem złożonym i normalnym";
    strings["Move up##sgdl2"].plurals[0] = "Przesuń w górę o jedną pozycję";
    strings["Move down##sgdl2"].plurals[0] = "Przesuń w dół o jedną pozycję";
    strings["Create##sgdl2"].plurals[0] = "Stwórz";
    strings["New folder##sgdl2"].plurals[0] = "Nowy folder";
    strings["Preview (right click to stop)##sgdl1"].plurals[0] = "Podgląd (PPM by zatrzymać)";
    strings["Delete##sgdl5"].plurals[0] = "Usuń";
    strings["<uncategorized>##sgdl1"].plurals[0] = "<bez kategorii>";
    strings["rename...##sgdl1"].plurals[0] = "zmień nazwę...";
    strings["delete##sgdl6"].plurals[0] = "usuń";
    strings["rename...##sgdl2"].plurals[0] = "zmień nazwę...";
    strings["Delete##sgdl7"].plurals[0] = "Usuń";

    //src/gui/gui.cpp

    strings["Instrument %d##sggu"].plurals[0] = "Instrument %d";
    strings["Sample %d"].plurals[0] = "Sampel %d";
    strings["the song is over!##sggu0"].plurals[0] = "koniec utworu!";
    strings["the song is over!##sggu1"].plurals[0] = "koniec utworu!";
    strings["Open File##sggu"].plurals[0] = "Otwórz plik";
    strings["compatible files##sggu0"].plurals[0] = "kompatybilne pliki";
    strings["all files##sggu0"].plurals[0] = "wszystkie pliki";
    strings["no backups made yet!##sggu"].plurals[0] = "nie utworzono jeszcze żadnych kopii zapasowych";
    strings["Restore Backup##sggu"].plurals[0] = "Wczytaj kopię zapasową";
    strings["Furnace or Furnace-B song##sggu0"].plurals[0] = "Utwór Furnace lub Furnace-B";
    strings["Furnace song##sggu0"].plurals[0] = "Utwór Furnace";
    strings["Save File##sggu0"].plurals[0] = "Zapisz plik";
    strings["DefleMask 1.1.3 module##sggu"].plurals[0] = "moduł DefleMaska 1.1.3";
    strings["Save File##sggu1"].plurals[0] = "Zapisz plik";
    strings["DefleMask 1.0/legacy module##sggu"].plurals[0] = "moduł DefleMaska 1.0/legacy";
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
    strings["compatible files##sggu3"].plurals[0] = "kompatybilne formaty plików";
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
    strings["Export Command Stream##sggu1"].plurals[0] = "Eksportuj strumień komend";
    strings["text file##sggu1"].plurals[0] = "plik tekstowy";
    strings["Export Command Stream##sggu2"].plurals[0] = "Eksportuj strumień komend";
    strings["binary file##sggu"].plurals[0] = "plik binarny";
    strings["Export Furnace song##sggu"].plurals[0] = "Eksportuj utwór Furnace";
    strings["Furnace song##sggu2"].plurals[0] = "Utwór Furnace";
    strings["Coming soon!##sggu"].plurals[0] = "Już wkrótce!";
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
    strings["Select Layout File##sggu"].plurals[0] = "Wybierz plik z ustawieniami układu okna";
    strings[".ini files##sggu0"].plurals[0] = "pliki .ini";
    strings["Export Colors##sggu"].plurals[0] = "eksportuj ustawienia kolorów";
    strings["configuration files##sggu2"].plurals[0] = "pliki konfiguracji";
    strings["Export Keybinds##sggu"].plurals[0] = "Eksportuj przypisania klawiszy";
    strings["configuration files##sggu3"].plurals[0] = "pliki konfiguracji";
    strings["Export Layout##sggu"].plurals[0] = "Eksportuj uklad okna";
    strings[".ini files##sggu1"].plurals[0] = "pliki .ini";
    strings["Load ROM##sggu"].plurals[0] = "Wczytaj ROM";
    strings["compatible files##sggu7"].plurals[0] = "kompatybilne pliki";
    strings["all files##sggu6"].plurals[0] = "wszystkie pliki";
    strings["Play Command Stream##sggu"].plurals[0] = "Odtwarzaj strumień komend";
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
    strings["no instruments available##sggu0"].plurals[0] = "brak dostepnych instrumentów";
    strings["paste with ins (background)##sggu"].plurals[0] = "wklej instrumet na wierzch (zastępując istniejący)";
    strings["no instruments available##sggu1"].plurals[0] = "brak dostępnych instrumentów";
    strings["paste flood##sggu"].plurals[0] = "wstaw z buforem, powtarzając cykl (do końca wzorca)";
    strings["paste overflow##sggu"].plurals[0] = "wstaw (z możliwym przejściem do następnego wzorca)";
    strings["delete##sggu0"].plurals[0] = "usuń";
    strings["select all##sggu"].plurals[0] = "wybierz wszystko";
    strings["operation mask...##sggu"].plurals[0] = "maska operacji...";
    strings["delete##sggu1"].plurals[0] = "usuń";
    strings["pull delete##sggu"].plurals[0] = "usuń z zaciągnięciem następujących wierszy";
    strings["insert##sggu"].plurals[0] = "wstaw pusty wiersz";
    strings["paste##sggu1"].plurals[0] = "wklej";
    strings["transpose (note)##sggu"].plurals[0] = "transponuj nutę";
    strings["transpose (value)##sggu"].plurals[0] = "transponuj (parametry)";
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
    strings["Nibble mode##sggu0"].plurals[0] = "Tryb półbajtów";
    strings["Go ahead##sggu"].plurals[0] = "Zastosuj";
    strings["scale...##sggu"].plurals[0] = "skaluj...";
    strings["Scale##sggu"].plurals[0] = "Skaluj";
    strings["randomize...##sggu"].plurals[0] = "wypełnij losowymi wartościami...";
    strings["Minimum##sggu"].plurals[0] = "Dolna granica";
    strings["Maximum##sggu"].plurals[0] = "Górna granica";
    strings["Nibble mode##sggu1"].plurals[0] = "Tryb półbajtów";
    strings["Randomize##sggu"].plurals[0] = "Losuj";
    strings["invert values##sggu1"].plurals[0] = "odwróć wartości";
    strings["flip selection##sggu"].plurals[0] = "odwróć wybrany obszar";
    strings["collapse/expand amount##CollapseAmount"].plurals[0] = "współczynnik skracania/rozszerzania##CollapseAmount";
    strings["collapse##sggu"].plurals[0] = "skroc";
    strings["expand##sggu"].plurals[0] = "rozszerz";
    strings["collapse pattern##sggu"].plurals[0] = "skróć wzorzec";
    strings["expand pattern##sggu"].plurals[0] = "rozszerz wzorzec";
    strings["collapse song##sggu"].plurals[0] = "skróć utwór";
    strings["expand song##sggu"].plurals[0] = "rozszerz utwór";
    strings["find/replace##sggu"].plurals[0] = "znajdź/zamień";
    strings["Furnace has been started in Safe Mode.\nthis means that:\n\n- software rendering is being used\n- audio output may not work\n- font loading is disabled\n\ncheck any settings which may have made Furnace start up in this mode.\nfont loading is one of these.##sggu"].plurals[0] = "Furnace został uruchomiony w trybie awaryjnym.\noznacza to, że:\n\n- używane jest renderowanie programowe\n- wyjście dźwięku może nie działać\n- wczytywanie czcionek jest wyłączone\n\nnależy sprawdzić, jakie ustawienia mogły spowodować, że program działa w tym trybie.\nczytanie czcionki mogło być jednym z nich.";
    strings["Unsaved changes! Save changes before opening file?##sggu0"].plurals[0] = "Niezapisano zmiany! Zapisać je przed wczytaniem pliku?";
    strings["Unsaved changes! Save changes before opening file?##sggu2"].plurals[0] = "=Unsaved changes! Save changes before opening file?";
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
    strings["export Furnace module...##sggu"].plurals[0] = "eksportuj moduł Furnace...";
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
    strings["add chip...##sggu"].plurals[0] = "dodaj układ...";
    strings["cannot add chip! (##sggu"].plurals[0] = "nie można dodać układu! (";
    strings["configure chip...##sggu"].plurals[0] = "konfiguruj układ...";
    strings["change chip...##sggu"].plurals[0] = "zmień układ...";
    strings["Preserve channel positions##sggu0"].plurals[0] = "Zachowaj pozycję kanałów";
    strings["remove chip...##sggu"].plurals[0] = "usuń układ...";
    strings["Preserve channel positions##sggu1"].plurals[0] = "Zachowaj pozycję kanałów";
    strings["cannot remove chip! (##sggu"].plurals[0] = "nie mozna usunąć ukladu! (";
    strings["cannot change chip! (##sggu"].plurals[0] = "nie można zmienić układu (";
    strings["open built-in assets directory##sggu"].plurals[0] = "otwórz wbudowany folder z zasobami";
    strings["restore backup##sggu"].plurals[0] = "przywróć kopię zapasową";
    strings["exit##sggu"].plurals[0] = "wyjdź";
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
    strings["Are you sure you want to reset the workspace layout?##sggu"].plurals[0] = "Czy jesteś pewien że chcesz zresetować układ okna?";
    strings["switch to mobile view##sggu"].plurals[0] = "przełącz na tryb mobilny";
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
    strings["pattern manager##sggu"].plurals[0] = "menedżer wzorców";
    strings["chip manager##sggu"].plurals[0] = "menedżer ukladów";
    strings["compatibility flags##sggu"].plurals[0] = "flagi kompatybilności";
    strings["song comments##sggu"].plurals[0] = "komentarze do utworu";
    strings["instrument editor##sggu"].plurals[0] = "edytor instrumentów";
    strings["wavetable editor##sggu"].plurals[0] = "edytor tablic fal";
    strings["sample editor##sggu"].plurals[0] = "edytor sampli";
    strings["play/edit controls##sggu"].plurals[0] = "kontrola edycji/odtwarzania";
    strings["piano/input pad##sggu"].plurals[0] = "klawiatura pianina/panel wejściowy";
    strings["oscilloscope (master)##sggu"].plurals[0] = "oscyloskop";
    strings["oscilloscope (per-channel)##sggu"].plurals[0] = "oscyloskop (dla poszczególnych kanałów)";
    strings["oscilloscope (X-Y)##sggu"].plurals[0] = "oscyloskop (X-Y)";
    strings["volume meter##sggu"].plurals[0] = "poziom głośności";
    strings["clock##sggu"].plurals[0] = "zegar";
    strings["register view##sggu"].plurals[0] = "podgląd rejestrów";
    strings["log viewer##sggu"].plurals[0] = "podglad logów";
    strings["statistics##sggu"].plurals[0] = "statystyki";
    strings["memory composition##sggu"].plurals[0] = "zawartość pamięci";
    strings["spoiler##sggu"].plurals[0] = "spoiler";
    strings["Help##menubar"].plurals[0] = "Pomoc##menubar";
    strings["help##menubar"].plurals[0] = "pomoc##menubar";
    strings["effect list##sggu"].plurals[0] = "lista efektów";
    strings["debug menu##sggu"].plurals[0] = "menu debugowania";
    strings["inspector##sggu"].plurals[0] = "menu debugowania ImGUI";
    strings["panic##sggu"].plurals[0] = "panika";
    strings["about...##sggu"].plurals[0] = "o programie...";
    strings["| Speed %d:%d##sggu"].plurals[0] = "| Prędkość %d:%d";
    strings["| Speed %d##sggu"].plurals[0] = "| Prędkość %d";
    strings["| Groove##sggu"].plurals[0] = "| Wzór rytmu";
    strings[" @ %gHz (%g BPM) ##sggu"].plurals[0] = " @ %gHz (%g BPM) ";
    strings["| Order %.2X/%.2X ##sggu"].plurals[0] = "| Wiersz matrycy wzorców %.2X/%.2X ";
    strings["| Order %d/%d ##sggu"].plurals[0] = "| Wiersz matrycy wzorców. %d/%d ";
    strings["| Row %.2X/%.2X ##sggu"].plurals[0] = "| Wiersz %.2X/%.2X ";
    strings["| Row %d/%d ##sggu"].plurals[0] = "| Wiersz %d/%d ";
    strings["Don't you have anything better to do?##sggu"].plurals[0] = "Serio nie masz nic lepszego do roboty?";
    strings["%d years ##sggu"].plurals[0] = "%d rok ";
    strings["%d years ##sggu"].plurals[1] = "%d roku ";
    strings["%d years ##sggu"].plurals[2] = "%d lat ";
    strings["%d months ##sggu"].plurals[0] = "%d miesiąc ";
    strings["%d months ##sggu"].plurals[1] = "%d miesiąca ";
    strings["%d months ##sggu"].plurals[2] = "%d miesięcy ";
    strings["%d days ##sggu"].plurals[0] = "%d dzień ";
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
    strings["could not open file!##sggu"].plurals[0] = "nie udało się otworzyć pliku!";
    strings["Could not write ZSM! (%s)##sggu"].plurals[0] = "nie udało się zapisać pliku ZSM! (%s)";
    strings["could not write text! (%s)##sggu"].plurals[0] = "nie udało się zapisać pliku tekstowego! (%s)";
    strings["could not write command stream! (%s)##sggu"].plurals[0] = "nie udało się zapisać strumienia komend! (%s)";
    strings["could not write tildearrow version Furnace module! (%s)##sggu"].plurals[0] = "nie udało się zapisać moduło dla wersji od tildearrowa! (%s)";
    strings["Error while loading file! (%s)##sggu4"].plurals[0] = "Blad podczas wczytywania pliku! (%s)";
    strings["You opened: %s##sggu"].plurals[0] = "Otwarto: %s";
    strings["You opened:##sggu"].plurals[0] = "Otwarto:";
    strings["You saved: %s##sggu"].plurals[0] = "Zapisano: %s";
    strings["Rendering...###Rendering..."].plurals[0] = "Renderowanie...###Rendering...";
    strings["Please wait...##sggu"].plurals[0] = "Proszę czekać...";
    strings["Abort##sggu"].plurals[0] = "Przerwij";
    strings["New Song###New Song"].plurals[0] = "Nowy Utwór###New Song";
    strings["Export###Export"].plurals[0] = "Eksportuj###Export";
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
    strings["Remove unused samples##sggu"].plurals[0] = "Usuń nieużywane sample";
    strings["Never mind! Cancel##sggu1"].plurals[0] = "Nie ważne! Anuluj";
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
    strings["Starting octave##sggu"].plurals[0] = "Oktawa początkowa";
    strings["too many instruments!##sggu"].plurals[0] = "zbyt wiele instrumentów!";
    strings["too many wavetables!##sggu"].plurals[0] = "zbyt wiele tablic fal!";
    strings["Select Instrument###Select Instrument"].plurals[0] = "Wybierz instrument###Select Instrument";
    strings["this is an instrument bank! select which one to use:##sggu"].plurals[0] = "to jest bank brzmień! wybierz instrument który checsz użyć:";
    strings["this is an instrument bank! select which ones to load:##sggu"].plurals[0] = "to jest bank brzmień! wybierz instrument który checsz wczytać";
    strings["All##sggu"].plurals[0] = "Wszystkie";
    strings["None##sggu"].plurals[0] = "Żadne";
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
    strings["Swap nibbles##sggu"].plurals[0] = "Zamień miejscami półbajty";
    strings["Swap words##sggu"].plurals[0] = "Zamień miejscami słowa maszynowe";
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
    strings["Restore backup##sggc"].plurals[0] = "Przywróć kopię zapasową";
    strings["Save file##sggc"].plurals[0] = "Zapisz plik";
    strings["Save as##sggc"].plurals[0] = "Zapisz jako";
    strings["Export##sggc"].plurals[0] = "Eksportuj";
    strings["Undo##sggc"].plurals[0] = "Cofnij";
    strings["Redo##sggc"].plurals[0] = "Ponów";
    strings["Exit##sggc"].plurals[0] = "Wyjdź";
    strings["Play/Stop (toggle)##sggc"].plurals[0] = "Start/stop (przełącznik)";
    strings["Play##sggc"].plurals[0] = "Odtwarzaj";
    strings["Stop##sggc"].plurals[0] = "Stop";
    strings["Play (from beginning)##sggc"].plurals[0] = "Odtwarzaj (od początku)";
    strings["Play (repeat pattern)##sggc"].plurals[0] = "Odtwarzaj (zapętl bieżący wzorzec)";
    strings["Play from cursor##sggc"].plurals[0] = "Odtwarzaj od kursora";
    strings["Step row##sggc"].plurals[0] = "Zrób jeden krok we wzorzcu";
    strings["Octave up##sggc"].plurals[0] = "Oktawa do góry";
    strings["Octave down##sggc"].plurals[0] = "Oktawa w dół";
    strings["Previous instrument##sggc"].plurals[0] = "Poprzedni instrument";
    strings["Next instrument##sggc"].plurals[0] = "Następny instrument";
    strings["Increase edit step##sggc"].plurals[0] = "Zwiększ krok edtownai";
    strings["Decrease edit step##sggc"].plurals[0] = "Zwiększ krok edytowania";
    strings["Toggle edit mode##sggc"].plurals[0] = "Włącz tryb edytowania";
    strings["Metronome##sggc"].plurals[0] = "Metronom";
    strings["Toggle repeat pattern##sggc"].plurals[0] = "Włącz powtarzanie wzorca";
    strings["Follow orders##sggc"].plurals[0] = "Podążaj za matrycą wzorców";
    strings["Follow pattern##sggc"].plurals[0] = "Podążaj za wzorcem";
    strings["Toggle full-screen##sggc"].plurals[0] = "Włącz tryb pełnoekranowy";
    strings["Request voice from TX81Z##sggc"].plurals[0] = "Poproś o kanał od TX81Z";
    strings["Panic##sggc"].plurals[0] = "Panika";
    strings["Clear song data##sggc"].plurals[0] = "Wyczyść dane utworu";
    strings["Command Palette##sggc"].plurals[0] = "Paleta komend";
    strings["Recent files (Palette)##sggc"].plurals[0] = "Ostatnio otawrte pliki (paleta)";
    strings["Instruments (Palette)##sggc"].plurals[0] = "Instrumenty (paleta)";
    strings["Samples (Palette)##sggc"].plurals[0] = "Sample (paleta)";
    strings["Change instrument (Palette)##sggc"].plurals[0] = "Zmień instrument (paleta)";
    strings["Add chip (Palette)##sggc"].plurals[0] = "Dodaj układ (paleta)";
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
    strings["Memory Composition##sggc"].plurals[0] = "Zawartość pamięci";

    strings["Collapse/expand current window##sggc"].plurals[0] = "Maksymalizuj/minimalizuj obecne okno";
    strings["Close current window##sggc"].plurals[0] = "Zamknij obecne okno";

    strings["---Pattern##sggc"].plurals[0] = "---Pattern";
    strings["Transpose (+1)##sggc"].plurals[0] = "Transponuj (+1)";
    strings["Transpose (-1)##sggc"].plurals[0] = "Transponuj (-1)";
    strings["Transpose (+1 octave)##sggc"].plurals[0] = "Transponuj (+1 oktawa)";
    strings["Transpose (-1 octave)##sggc"].plurals[0] = "Transponuj (-1 oktawa)";
    strings["Increase values (+1)##sggc"].plurals[0] = "Zwieksz wartości (+1)";
    strings["Increase values (-1)##sggc"].plurals[0] = "Zmniejsz wartości (-1)";
    strings["Increase values (+16)##sggc"].plurals[0] = "Zwieksz wartości (+16)";
    strings["Increase values (-16)##sggc"].plurals[0] = "Zmniejsz wartości (-16)";
    strings["Select all##sggc0"].plurals[0] = "Wybierz wszystko";
    strings["Cut##sggc0"].plurals[0] = "Wytnij";
    strings["Copy##sggc0"].plurals[0] = "Kopiuj";
    strings["Paste##sggc0"].plurals[0] = "Wklej";
    strings["Paste Mix (foreground)##sggc"].plurals[0] = "Wklej ponad zawartość";
    strings["Paste Mix (background)##sggc"].plurals[0] = "Wklej nad zawartość (zastąp komórki z zaw.)";
    strings["Paste Flood##sggc"].plurals[0] = "Wstawić z buforem powtarzając cykl (do końca wzorca)";
    strings["Paste Overflow##sggc"].plurals[0] = "Wklej z przepełnieniem";
    strings["Move cursor up##sggc"].plurals[0] = "Kursor w górę";
    strings["Move cursor down##sggc"].plurals[0] = "Kursor w dół";
    strings["Move cursor left##sggc"].plurals[0] = "Kursor w lewo";
    strings["Move cursor right##sggc"].plurals[0] = "Kursor w prawo";
    strings["Move cursor up by one (override Edit Step)##sggc"].plurals[0] = "Przesuń kursor w górę o jeden (ignoruj krok edycji)";
    strings["Move cursor down by one (override Edit Step)##sggc"].plurals[0] = "Przesuń kursor w dół o jeden (ignoruj krok edycji)";
    strings["Move cursor to previous channel##sggc"].plurals[0] = "Przesuń kursor do poprzedniego kanału";
    strings["Move cursor to next channel##sggc"].plurals[0] = "Przesuń kursor do następnego kanału";
    strings["Move cursor to next channel (overflow)##sggc"].plurals[0] = "Przesuń kursor do następnego kanału (z przepełnieniem)";
    strings["Move cursor to previous channel (overflow)##sggc"].plurals[0] = "Przesuń kursor do poprzedniego kanału (z przepełnieniem)";
    strings["Move cursor to beginning of pattern##sggc"].plurals[0] = "Przesuń kursor na początek wzorca";
    strings["Move cursor to end of pattern##sggc"].plurals[0] = "Przesuń kursor na koniec wzorca";
    strings["Move cursor up (coarse)##sggc"].plurals[0] = "Kursor w górę (w przybliżeniu)";
    strings["Move cursor down (coarse)##sggc"].plurals[0] = "Kursor w dół (w przybliżeniu)";
    strings["Expand selection upwards##sggc"].plurals[0] = "Rozszerz zaznaczenie w górę";
    strings["Expand selection downwards##sggc"].plurals[0] = "Rozszerz zaznaczenie w dół";
    strings["Expand selection to the left##sggc"].plurals[0] = "Rozszerz zaznaczenie w lewo";
    strings["Expand selection to the right##sggc"].plurals[0] = "Rozszerz zaznaczenie w prawo";
    strings["Expand selection upwards by one (override Edit Step)##sggc"].plurals[0] = "Rozszerz zaznaczenie w górę o jeden (ignoruj krok edycji)";
    strings["Expand selection downwards by one (override Edit Step)##sggc"].plurals[0] = "Rozszerz zaznaczenie w dół o jeden (ignoruj krok edycji)";
    strings["Expand selection to beginning of pattern##sggc"].plurals[0] = "Rozszerz zaznaczenie do początku wzorca";
    strings["Expand selection to end of pattern##sggc"].plurals[0] = "Rozszerz zaznaczenie do końca wzorca";
    strings["Expand selection upwards (coarse)##sggc"].plurals[0] = "Rozszerz zaznaczenie w górę (z grubsza)";
    strings["Expand selection downwards (coarse)##sggc"].plurals[0] = "Rozszerz zaznaczenie w dół (z grubsza)";
    strings["Delete##sggc"].plurals[0] = "Usuń";
    strings["Pull delete##sggc"].plurals[0] = "Usuń z zaciągnięciem następujących rzędów";
    strings["Insert##sggc"].plurals[0] = "Wstaw z wierszami przesuniętymi w dół";
    strings["Mute channel at cursor##sggc"].plurals[0] = "Wycisz zaznaczony kanał";
    strings["Solo channel at cursor##sggc"].plurals[0] = "Wyizoluj zaznaczony kanał";
    strings["Unmute all channels##sggc"].plurals[0] = "Włącz ponownie wszystkie kanały";
    strings["Go to next order##sggc"].plurals[0] = "Przeskocz do następnego wiersza matrycy wzorców";
    strings["Go to previous order##sggc"].plurals[0] = "Przeskocz do poprzedniego wiersza matrycy wzorców";
    strings["Collapse channel at cursor##sggc"].plurals[0] = "Skróc zaznaczony kursor";
    strings["Increase effect columns##sggc"].plurals[0] = "Dodaj kolumnę efektów";
    strings["Decrease effect columns##sggc"].plurals[0] = "Usuń kolumnę efektów";
    strings["Interpolate##sggc"].plurals[0] = "Interpoluj";
    strings["Fade##sggc"].plurals[0] = "Gradient";
    strings["Invert values##sggc"].plurals[0] = "Odwróć wartości";
    strings["Flip selection##sggc"].plurals[0] = "Odwróć wybrany obszar";
    strings["Collapse rows##sggc"].plurals[0] = "Skróć wiersze";
    strings["Expand rows##sggc"].plurals[0] = "Rozszerz wiersze";
    strings["Collapse pattern##sggc"].plurals[0] = "Skróć wzorzec";
    strings["Expand pattern##sggc"].plurals[0] = "Rozszerz wzorzec";
    strings["Collapse song##sggc"].plurals[0] = "Skróć utwór";
    strings["Expand song##sggc"].plurals[0] = "Rozszerz utwór";
    strings["Set note input latch##sggc"].plurals[0] = "Ustaw bufor wejściowy nut";
    strings["Change mobile scroll mode##sggc"].plurals[0] = "Przełącz na mobilny tryb przewijania";
    strings["Clear note input latch##sggc"].plurals[0] = "Wyczyść bufor wejściowy nut";

    strings["---Instrument list##sggc"].plurals[0] = "---Instrument list";
    strings["Add instrument##sggc0"].plurals[0] = "Dodaj";
    strings["Duplicate instrument##sggc0"].plurals[0] = "Sklonuj";
    strings["Open instrument##sggc0"].plurals[0] = "Otwórz";
    strings["Open (replace current instrument)##sggc0"].plurals[0] = "Otwórz (z zamianą obecnego)";
    strings["Save instrument##sggc0"].plurals[0] = "Zapisz";
    strings["Export instrument (.dmp)##sggc"].plurals[0] = "Eksportuj (.dmp)";
    strings["Move instrument up in list##sggc0"].plurals[0] = "Przesuń w górę";
    strings["Move instrument down in list##sggc0"].plurals[0] = "Przesuń w dół";
    strings["Delete instrument##sggc0"].plurals[0] = "Usuń";
    strings["Edit instrument##sggc0"].plurals[0] = "Edycja";
    strings["Instrument cursor up##sggc0"].plurals[0] = "Kursor w górę";
    strings["Instrument cursor down##sggc0"].plurals[0] = "Kursor w dół";
    strings["Instrument: toggle folders/standard view##sggc0"].plurals[0] = "Przełączaj między widokiem złożonym i normalnym";
    strings["---Wavetable list##sggc"].plurals[0] = "---Wavetable list";
    strings["Add wavetable##sggc1"].plurals[0] = "Dodaj";
    strings["Duplicate wavetable##sggc1"].plurals[0] = "Sklonuj";
    strings["Open wavetable##sggc1"].plurals[0] = "Otwórz";
    strings["Open wavetable (replace current)##sggc1"].plurals[0] = "Otwórz (z zamianą obecnego)";
    strings["Save wavetable##sggc1"].plurals[0] = "Zapisz";
    strings["Save wavetable (.dmw)##sggc"].plurals[0] = "Zapisz (.dmw)";
    strings["Save wavetable (raw)##sggc0"].plurals[0] = "Zapisz (dane surowe)";
    strings["Move wavetable up in list##sggc1"].plurals[0] = "Przesuń w górę";
    strings["Move wavetable down in list##sggc1"].plurals[0] = "Przesuń w dół";
    strings["Delete wavetable##sggc1"].plurals[0] = "Usuń";
    strings["Edit wavetable##sggc1"].plurals[0] = "Edytuj";
    strings["Wavetable cursor up##sggc1"].plurals[0] = "Kursor do góry";
    strings["Wavetable cursor down##sggc1"].plurals[0] = "Kursur w dół";
    strings["Wavetable: toggle folders/standard view##sggc1"].plurals[0] = "Przełączaj między widokiem złożonym i normalnym";
    strings["Paste wavetables from clipboard##sggc"].plurals[0] = "Wklej tablice fal ze schowka";
    strings["Paste local wavetables from clipboard##sggc1"].plurals[0] = "Wklej lokalne tablice fal ze schowka";
    strings["---Sample list##sggc"].plurals[0] = "---Sample list";
    strings["Add sample##sggc2"].plurals[0] = "Dodaj sampel";
    strings["Duplicate sample##sggc2"].plurals[0] = "Klonuj sampel";
    strings["Open sample##sggc2"].plurals[0] = "Klonuj sampel";
    strings["Open sample (replace current)##sggc2"].plurals[0] = "Otwórz sampel (zamień obecny)";
    strings["Import raw sample data##sggc"].plurals[0] = "Importuj surowe dane";
    strings["Import raw sample data (replace current)##sggc"].plurals[0] = "Importuj surowe dane (zamień obecny)";
    strings["Save sample##sggc2"].plurals[0] = "Zapisz sampel";
    strings["Save sample (raw)##sggc1"].plurals[0] = "Zapisz sampel (surowy)";
    strings["Move sample up in list##sggc2"].plurals[0] = "Przesuń sampel w górę na liście";
    strings["Move sample down in list##sggc2"].plurals[0] = "Przesuń sampel w dół na liście";
    strings["Delete sample##sggc2"].plurals[0] = "Usuń sampel";
    strings["Edit sample##sggc2"].plurals[0] = "Edytuj sampel";
    strings["Sample cursor up##sggc2"].plurals[0] = "Kursor w górę";
    strings["Sample cursor down##sggc2"].plurals[0] = "Kursor w dół";
    strings["Sample preview##sggc"].plurals[0] = "Podgląd sampla";
    strings["Stop sample preview##sggc"].plurals[0] = "Zatrzymaj podgląd sampla";
    strings["Samples: Toggle folders/standard view##sggc2"].plurals[0] = "=Sample: Przełączaj pomiędzy widokiem standardowym/folderami";
    strings["Samples: Make me a drum kit##sggc"].plurals[0] = "=Sample: Stwórz mapę perkusyjną";
    strings["---Sample editor##sggc"].plurals[0] = "---Edytor sampli";
    strings["Sample editor mode: Select##sggc"].plurals[0] = "Tryb edytora sampli: Zaznacz";
    strings["Sample editor mode: Draw##sggc"].plurals[0] = "Tryb edytora sampli: Rysuj";
    strings["Sample editor: Cut##sggc1"].plurals[0] = "Edytor sampli: Wytnij";
    strings["Sample editor: Copy##sggc1"].plurals[0] = "Edytor sampli: Kopiuj";
    strings["Sample editor: Paste##sggc1"].plurals[0] = "Edytor sampli: Wklej";
    strings["Sample editor: Paste replace##sggc"].plurals[0] = "Edytor sampli: Wklej i zamień";
    strings["Sample editor: Paste mix##sggc"].plurals[0] = "Edytor sampli: Wklej ponad zawartość";
    strings["Sample editor: Select all##sggc1"].plurals[0] = "Edytor sampli: Wybierz wszystko";
    strings["Sample editor: Resize##sggc"].plurals[0] = "Edytor sampli: Zmień rozmiar";
    strings["Sample editor: Resample##sggc"].plurals[0] = "Edytor sampli: Resample";
    strings["Sample editor: Amplify##sggc"].plurals[0] = "Edytor sampli: Wzmocnij";
    strings["Sample editor: Normalize##sggc"].plurals[0] = "Edytor sampli: Normalizuj";
    strings["Sample editor: Fade in##sggc"].plurals[0] = "Edytor sampli: Fade in";
    strings["Sample editor: Fade out##sggc"].plurals[0] = "Edytor sampli: Fade out";
    strings["Sample editor: Apply silence##sggc"].plurals[0] = "Edytor sampli: Zastosuj ciszę";
    strings["Sample editor: Insert silence##sggc"].plurals[0] = "Edytor sampli: Wstaw ciszę";
    strings["Sample editor: Delete##sggc3"].plurals[0] = "Edytor sampli: Usuń";
    strings["Sample editor: Trim##sggc"].plurals[0] = "Edytor sampli: Przytnij";
    strings["Sample editor: Reverse##sggc"].plurals[0] = "Edytor sampli: Zamień początek z końcem";
    strings["Sample editor: Invert##sggc"].plurals[0] = "Edytor sampli: Odrwóć";
    strings["Sample editor: Signed/unsigned exchange##sggc"].plurals[0] = "Edytor sampli: Konwersja na ze znakiem/bez znaku";
    strings["Sample editor: Apply filter##sggc"].plurals[0] = "Edytor sampli: Zastosuj filtr";
    strings["Sample editor: Crossfade loop points##sggc"].plurals[0] = "Edytor sampli: Crossfade loop points";
    strings["Sample editor: Preview sample##sggc"].plurals[0] = "Edytor sampli: Podgląd sampla";
    strings["Sample editor: Stop sample preview##sggc"].plurals[0] = "Edytor sampli: Zatrzymaj podgląd sampla";
    strings["Sample editor: Zoom in##sggc"].plurals[0] = "Edytor sampli: Przybliż";
    strings["Sample editor: Zoom out##sggc"].plurals[0] = "Edytor sampli: Oddal";
    strings["Sample editor: Toggle auto-zoom##sggc"].plurals[0] = "Edytor sampli: Włącz auto-zoom";
    strings["Sample editor: Create instrument from sample##sggc"].plurals[0] = "Edytor sampli: Stwórz instrument z sampla";
    strings["Sample editor: Set loop to selection##sggc"].plurals[0] = "Edytor sampli: Ustaw pętlę na zaznaczenie";
    strings["Sample editor: Create wavetable from selection##sggc"].plurals[0] = "Edytor sampli: Stwórz tablicę fal z zaznaczenia";
    strings["---Orders##sggc"].plurals[0] = "---Orders";
    strings["Previous order##sggc"].plurals[0] = "Poprzedni wiersz matrycy wzorców";
    strings["Next order##sggc"].plurals[0] = "Następny wiersz matrycy wzorców";
    strings["Order cursor left##sggc"].plurals[0] = "Kursor w lewo";
    strings["Order cursor right##sggc"].plurals[0] = "Kursor w prawo";
    strings["Increase order value##sggc"].plurals[0] = "Zwieksz wartość";
    strings["Decrease order value##sggc"].plurals[0] = "Zmniejsz wartość";
    strings["Switch order edit mode##sggc"].plurals[0] = "Włącz tryb edytowania";
    strings["Order: toggle alter entire row##sggc"].plurals[0] = "Włącz tryb zmiany całego rzędu";
    strings["Add order##sggc3"].plurals[0] = "Dodaj";
    strings["Duplicate order##sggc3"].plurals[0] = "Sklonuj";
    strings["Deep clone order##sggc"].plurals[0] = "Sklonuj gleboko";
    strings["Duplicate order to end of song##sggc"].plurals[0] = "Sklonuj i wstaw na koniec utworu";
    strings["Deep clone order to end of song##sggc"].plurals[0] = "Głęboko sklouj i wstaw na koniec utworu";
    strings["Remove order##sggc"].plurals[0] = "Usuń";
    strings["Move order up##sggc3"].plurals[0] = "Przesuń w górę";
    strings["Move order down##sggc3"].plurals[0] = "Przesuń w dół";
    strings["Replay order##sggc"].plurals[0] = "Powtórz";

    strings["All chips##sggc"].plurals[0] = "Wszystkie uklady";
    strings["Square##sggc"].plurals[0] = "PSG";
    strings["Wavetable##sggc"].plurals[0] = "Syntezatory tablicowe";
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
    strings["Mobile Controls###Mobile Controls"].plurals[0] = "Mobilne menu ustawień###Mobile Controls";
    strings["Mobile Menu###Mobile Menu"].plurals[0] = "Mobilne menu###Mobile Menu";
    strings["Pattern##sgec0"].plurals[0] = "Wzorzec";
    strings["Orders##sgec0"].plurals[0] = "Matryca wzorców";
    strings["Ins##sgec"].plurals[0] = "Instr.";
    strings["Wave##sgec"].plurals[0] = "Tab. fal";
    strings["Sample##sgec"].plurals[0] = "Sampel";
    strings["Song##sgec"].plurals[0] = "Utwór";
    strings["Channels##sgec"].plurals[0] = "Kanały";
    strings["Chips##sgec"].plurals[0] = "Układy";
    strings["Mixer##sgec"].plurals[0] = "Mikser";
    strings["Other##sgec"].plurals[0] = "Inne";
    strings["New##sgec"].plurals[0] = "Nowy";
    strings["Unsaved changes! Save changes before creating a new song?##sgec"].plurals[0] = "Niezapisane zmiany! Zapisać zmiany przed stworzeniem nowego utworu?";
    strings["Open##sgec"].plurals[0] = "Otwórz";
    strings["Save##sgec"].plurals[0] = "Zapisz";
    strings["Save as...##sgec"].plurals[0] = "Zapisz jako...";
    strings["Legacy .dmf##sgec"].plurals[0] = ".dmf (legacy)";
    strings["Export##sgec"].plurals[0] = "Eksportuj";
    strings["Restore Backup##sgec"].plurals[0] = "Przywróć kopię zapasową";
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

            "to NIE jest opcja eksportu do ROM! używaj tylko by\n"
            "upewnić się, że emulator Amigi w Furnace działa poprawnie,\n"
            "porównując dźwięk prawdziwej Amigi i Furnace.";
    strings["Directory##sgec"].plurals[0] = "Folder";
    strings["Bake Data##sgec"].plurals[0] = "Wstaw dane";
    strings["Done! Baked %d files.##sgec"].plurals[0] = "Gotowe! Wstawiono %d piku.";
    strings["Done! Baked %d files.##sgec"].plurals[1] = "Gotowe! Wstawiono %d pliki.";
    strings["Done! Baked %d files.##sgec"].plurals[2] = "Gotowe! Wstawiono %d plików.";
    strings["Play/Edit Controls###Play/Edit Controls"].plurals[0] = "Sterowanie odtw./edycją###Play/Edit Controls";
    strings["Octave##sgec0"].plurals[0] = "Oktawa";
    strings["Edit Step##sgec0"].plurals[0] = "Krok edycji";
    strings["Play##sgec0"].plurals[0] = "Odtwarzaj";
    strings["Stop##sgec0"].plurals[0] = "Stop";
    strings["Edit##sgec0"].plurals[0] = "Edytuj";
    strings["Metronome##sgec0"].plurals[0] = "Metronom";
    strings["Follow##sgec0"].plurals[0] = "Podążaj";
    strings["Orders##sgec1"].plurals[0] = "Matryca wzorców";
    strings["Pattern##sgec1"].plurals[0] = "Wzorzec";
    strings["Repeat pattern##sgec0"].plurals[0] = "Zapętl wzorzec";
    strings["Step one row##sgec0"].plurals[0] = "Zrób jeden krok we wzorcu";
    strings["Poly##PolyInput"].plurals[0] = "Polifonia##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Mono##PolyInput";
    strings["Polyphony##sgec0"].plurals[0] = "Polifonia podglądu";
    strings["Stop##sgec1"].plurals[0] = "Stop";
    strings["Play##sgec1"].plurals[0] = "Odtwarzaj";
    strings["Step one row##sgec1"].plurals[0] = "Zrób jeden krok we wzorcu";
    strings["Repeat pattern##sgec1"].plurals[0] = "Zapętl wzorzec";
    strings["Edit##sgec1"].plurals[0] = "Tryb edycji";
    strings["Metronome##sgec1"].plurals[0] = "Metronom";
    strings["Octave##sgec1"].plurals[0] = "Oktawa";
    strings["Edit Step##sgec1"].plurals[0] = "Krok edycji";
    strings["Follow##sgec1"].plurals[0] = "Podążaj";
    strings["Orders##sgec2"].plurals[0] = "Matryca wzorców";
    strings["Pattern##sgec2"].plurals[0] = "Wzorzec";
    strings["Poly##PolyInput"].plurals[0] = "Polifonia##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Mono##PolyInput";
    strings["Polyphony##sgec1"].plurals[0] = "Polifonia podglądu";
    strings["Play##sgec2"].plurals[0] = "Odtwarzaj";
    strings["Stop##sgec2"].plurals[0] = "Stop";
    strings["Step one row##sgec2"].plurals[0] = "Zrób jeden krok we wzorcu";
    strings["Repeat pattern##sgec2"].plurals[0] = "Zapętl wzorzec";
    strings["Edit##sgec2"].plurals[0] = "Tryb edycji";
    strings["Metronome##sgec2"].plurals[0] = "Metronom";
    strings["Oct.##sgec"].plurals[0] = "Okt.";
    strings["Octave##sgec2"].plurals[0] = "Oktawa";
    strings["Step##sgec0"].plurals[0] = "Krok";
    strings["Foll.##sgec"].plurals[0] = "Pod.";
    strings["Follow##sgec2"].plurals[0] = "Podążaj";
    strings["Ord##FollowOrders"].plurals[0] = "Matr.##FollowOrders";
    strings["Orders##sgec3"].plurals[0] = "Matryca wzorców";
    strings["Pat##FollowPattern"].plurals[0] = "Wz.##FollowPattern";
    strings["Pattern##sgec3"].plurals[0] = "Wzorzec";
    strings["Poly##PolyInput"].plurals[0] = "Polifonia##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Mono##PolyInput";
    strings["Polyphony##sgec2"].plurals[0] = "Polifonia podglądu";
    strings["Play Controls###Play Controls"].plurals[0] = "Sterowanie odtwarzaniem###Play Controls";
    strings["Stop##sgec3"].plurals[0] = "Stop";
    strings["Play##sgec3"].plurals[0] = "Odtwarzaj";
    strings["Play from the beginning of this pattern##sgec"].plurals[0] = "Odtwarzaj od początku wzorca";
    strings["Repeat from the beginning of this pattern##sgec"].plurals[0] = "Zapętlaj od początku tego wzorca";
    strings["Step one row##sgec3"].plurals[0] = "Zrób jeden krok we wzorcu";
    strings["Edit##sgec3"].plurals[0] = "Edytuj";
    strings["Metronome##sgec3"].plurals[0] = "Metronom";
    strings["Repeat pattern##sgec3"].plurals[0] = "Zapętl wzorzec";
    strings["Poly##PolyInput"].plurals[0] = "Polifonia##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Mono##PolyInput";
    strings["Polyphony##sgec3"].plurals[0] = "Polifonia podglądu";
    strings["Edit Controls###Edit Controls"].plurals[0] = "Sterowanie edytowaniem###Edit Controls";
    strings["Octave##sgec3"].plurals[0] = "Oktawa";
    strings["Step##sgec1"].plurals[0] = "Krok";
    strings["Follow orders##sgec"].plurals[0] = "Podążaj za matrycą wzorców";
    strings["Follow pattern##sgec"].plurals[0] = "Podążaj za wzorcem";

    //   sged  src/gui/editing.cpp

    strings["can't collapse any further!##sged"].plurals[0] = "nie da się skrócić jeszcze bardziej!";
    strings["can't expand any further!##sged"].plurals[0] = "nie da się rozzszerzyć jeszcze bardziej!";

    //   sgef  src/gui/effectList.cpp

    strings["Effect List###Effect List"].plurals[0] = "Lista efektów###Effect List";
    strings["Chip at cursor: %s##sgef"].plurals[0] = "Zazanaczony uklad: %s";
    strings["Search##sgef"].plurals[0] = "Szukaj";
    strings["Effect types to show:##sgef"].plurals[0] = "Wyświetlanie typów efektów:";
    strings["All##sgef"].plurals[0] = "Wszystkie";
    strings["None##sgef"].plurals[0] = "Żadnego";
    strings["Name##sgef"].plurals[0] = "Nazwa";
    strings["Description##sgef"].plurals[0] = "Opis";
    strings["ERROR##sgef"].plurals[0] = "BŁĄD";

    //   sgeo  src/gui/exportOptions.cpp

    strings["one file##sgeo"].plurals[0] = "jeden plik";
    strings["multiple files (one per chip)##sgeo"].plurals[0] = "wiele plików (po jednym na układ)";
    strings["multiple files (one per channel)##sgeo"].plurals[0] = "wiele plików (po jednym na kanał)";
    strings["Loops##sgeo"].plurals[0] = "Ilość powtórzeń";
    strings["Fade out (seconds)##sgeo"].plurals[0] = "Zanikanie (w sekundach)";
    strings["Cancel##sgeo0"].plurals[0] = "Anuluj";
    strings["Export##sgeo0"].plurals[0] = "Eksportuj";
    strings["settings:##sgeo"].plurals[0] = "ustawienia:";
    strings["format version##sgeo"].plurals[0] = "wersja formatu";
    strings["loop##sgeo0"].plurals[0] = "zapętlenie";
    strings["loop trail:##sgeo"].plurals[0] = "znacznik końca pętli:";
    strings["auto-detect##sgeo"].plurals[0] = "automatyczny";
    strings["add one loop##sgeo1"].plurals[0] = "dodaj jedną pętlę";
    strings["custom##sgeo"].plurals[0] = "niestandardowy";
    strings["add pattern change hints##sgeo"].plurals[0] = "dodaj znaczniki końca wzorca";
    strings["inserts data blocks on pattern changes.\n"
            "useful if you are writing a playback routine.\n\n"
            "the format of a pattern change data block is:\n"
            "67 66 FE ll ll ll ll 01 oo rr pp pp pp ...\n"
            "- ll: length, a 32-bit little-endian number\n"
            "- oo: order\n"
            "- rr: initial row (a 0Dxx effect is able to select a different row)\n"
            "- pp: pattern index (one per channel)\n\n"
            "pattern indexes are ordered as they appear in the song."].plurals[0] = 

            "wstawia bloki danych przy zmianie wzorca.\n"
            "przydatne podczas pisania programu do odtwarzania.\n\n"
            "format bloku danych zmiany wzorca:\n"
            "67 66 FE ll ll ll ll 01 oo rr pp pp pp ...\n"
            "- ll: długość, liczba 32-bitowa, bezpośrednia kolejność bajtów (little endian)\n"
            "- oo: wiersz matrycy wzorców\n"
            "- rr: początkowy wiersz wzorca (efekt 0Dxx może go zmienić)\n"
            "- pp: indeks wzorca (jeden na kanał)\n\n"
            "indeksy wzorców są posortowane w kolejności, w jakiej się znajdują\n"
            "w piosence\n";
    strings["direct stream mode##sgeo"].plurals[0] = "tryb bezpośredniego strumienia";
    strings["required for DualPCM and MSM6258 export.\n\n"
            "allows for volume/direction changes when playing samples,\n"
            "at the cost of a massive increase in file size."].plurals[0] = 

            "wymagany do eksportu DualPCM i MSM6258.\n\n"
            "umożliwia zmiany głośności/kierunku odtwarzania sampla\n"
            "kosztem znacznego zwiększenia rozmiaru pliku.";
    strings["chips to export:##sgeo"].plurals[0] = "eksportuj następujące układy:";
    strings["this chip is only available in VGM %d.%.2x and higher!##sgeo"].plurals[0] = "ten układ jest dostępny tylko w formacie VGM wersji %d.%.2x i wyższej!";
    strings["this chip is not supported by the VGM format!##sgeo"].plurals[0] = "ten uklad nie jest wspierany przez format VGM!";
    strings["select the chip you wish to export, but only up to %d of each type.##sgeo"].plurals[0] = "wybierz układy, których dane chcesz wyeskportować, ale nie więcej niż %d układ każdego typu.";
    strings["select the chip you wish to export, but only up to %d of each type.##sgeo"].plurals[1] = "wybierz układy, których dane chcesz wyeskportować, ale nie więcej niż %d układów każdego typu.";
    strings["select the chip you wish to export, but only up to %d of each type.##sgeo"].plurals[2] = "wybierz układy, których dane chcesz wyeskportować, ale nie więcej niż %d układów każdego typu.";
    strings["Cancel##sgeo1"].plurals[0] = "Anuluj";
    strings["Export##sgeo1"].plurals[0] = "eksportuj";
    strings["nothing to export##sgeo2"].plurals[0] = "nic do eksportu";
    strings["Cancel##sgeo2"].plurals[0] = "Anuluj";
    strings["Commander X16 Zsound Music File##sgeo"].plurals[0] = "Commander X16 Zsound Music File";
    strings["Tick Rate (Hz)##sgeo"].plurals[0] = "Częstotliwość kroku (Hz)";
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
    strings["this option exports the song to a text file.\n##sgeo"].plurals[0] = "ta opcja eksportuje piosenkę do pliku tekstowego\n";
    strings["Cancel##sgeo7"].plurals[0] = "Anuluj";
    strings["Export##sgeo6"].plurals[0] = "Eksportuj";
    strings["this option exports a text or binary file which\n"
            "contains a dump of the internal command stream\n"
            "produced when playing the song.\n\n"
            "technical/development use only!"].plurals[0] = 

            "ta opcja umożliwia utworzenie pliku tekstowego lub binarnego,\n"
            "który zawiera zrzut wewnętrznego strumienia komend,\n"
            "utworzone podczas odtwarzania utworu.\n\n"
            "używać tylko do celów technicznych/programowania!";
    strings["Cancel##sgeo8"].plurals[0] = "Anuluj";
    strings["Export (binary)##sgeo"].plurals[0] = "Eksportuj (dane binarne)";
    strings["Export (text)##sgeo"].plurals[0] = "Eksportuj (tekst)";
    strings["this option exports a module which is\n"
            "compatible with tildearrow Furnace app.\n\n"

            "not all chips and inst macros will be supported!"].plurals[0] = 

            "ta opcja eksportuje pik modułu,\n"
            "który jest kompatybilny z Furnace od tildearrowa.\n\n"

            "nie wszystkie układy i makra będą wspierane!";
    strings["Cancel##sgeo9"].plurals[0] = "Anuluj";
    strings["Export##sgeo7"].plurals[0] = "Eksportuj";
    strings["Audio##sgeo"].plurals[0] = "Audio";
    strings["DMF (1.0/legacy)##sgeo"].plurals[0] = "DMF (1.0/legacy)";
    strings["Amiga Validation##sgeo"].plurals[0] = "Walidacja Amigi";
    strings["Text##sgeo"].plurals[0] = "Tekst";
    strings["Command Stream##sgeo"].plurals[0] = "Strumień komend";
    strings["Furnace##sgeo"].plurals[0] = "Furnace";
    strings["congratulations! you've unlocked a secret panel.##sgeo"].plurals[0] = "gratulacje! odkryłeś tajny panel.";
    strings["Toggle hidden systems##sgeo"].plurals[0] = "Włącz ukryhte systemy";
    strings["Toggle all instrument types##sgeo"].plurals[0] = "Włącz wszystkie typy instrumentów";
    strings["Set pitch linearity to Partial##sgeo"].plurals[0] = "Ustaw częściową liniowość wysokości dźwięku";
    strings["Enable multi-threading settings##sgeo"].plurals[0] = "Włącz ustawienia wielo-wątkowości";
    strings["Set fat to max##sgeo"].plurals[0] = "Ustaw poizom tłuszczu na maks.";
    strings["Set muscle and fat to zero##sgeo"].plurals[0] = "Pozbądź się wszystkich mięśni i tłuszczu";
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
    strings["order##sgfr0"].plurals[0] = "wiersz matrycy wzorców";
    strings["row##sgfr0"].plurals[0] = "wiersz";
    strings["order##sgfr1"].plurals[0] = "wiersz matrycy wzorców";
    strings["row##sgfr1"].plurals[0] = "wiersz";
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
    strings["Confine to channels##sgfr"].plurals[0] = "Tylko na wybranych kanałach";
    strings["From##sgfr"].plurals[0] = "Od";
    strings["To##sgfr"].plurals[0] = "Do";
    strings["Match effect position:##sgfr"].plurals[0] = "Dopasuj położenie efektu:";
    strings["No##sgfr"].plurals[0] = "Nie";
    strings["match effects regardless of position.##sgfr"].plurals[0] = "dopasuj efekty niezależnie od położenia.";
    strings["Lax##sgfr"].plurals[0] = "Luźno";
    strings["match effects only if they appear in-order.##sgfr"].plurals[0] = "efekty są wykrywane, jeśli są we właściwej kolejności";
    strings["Strict##sgfr"].plurals[0] = "Ściśle";
    strings["match effects only if they appear exactly as specified.##sgfr"].plurals[0] = "efekty są wykrywane, jeśli są w pełni zgodne z żądaniem.";
    strings["Find##sgfr1"].plurals[0] = "Znajdź";
    strings["Replace##sgfr"].plurals[0] = "Zamień";
    strings["Note##sgfr1"].plurals[0] = "Nuta";
    strings["INVALID##sgfr"].plurals[0] = "NIEPOPRAWNY.";
    strings["Ins##sgfr1"].plurals[0] = "Instrument";
    strings["Volume##sgfr1"].plurals[0] = "Głośność";
    strings["Effect##sgfr1"].plurals[0] = "Efekt";
    strings["Value##sgfr1"].plurals[0] = "Parametr";
    strings["Add effect##sgfr1"].plurals[0] = "Dodaj efekt";
    strings["Remove effect##sgfr1"].plurals[0] = "Usuń efekt";
    strings["Effect replace mode:##sgfr"].plurals[0] = "Tryb zastępowania efektów:";
    strings["Replace matches only##sgfr"].plurals[0] = "Zastąp tylko dopasowania";
    strings["Replace matches, then free spaces##sgfr"].plurals[0] = "Zastąp dopasowania i wypełń wolne komórki";
    strings["Clear effects##sgfr"].plurals[0] = "Wyczyść efekty";
    strings["Insert in free spaces##sgfr"].plurals[0] = "Wstaw w wolne miejsca";
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
    strings["clear contents##sgie"].plurals[0] = "wyczyść zawartość";
    strings["offset...##sgie"].plurals[0] = "przesunięcie...";
    strings["offset##sgie"].plurals[0] = "przesunięcie";
    strings["scale...##sgie"].plurals[0] = "skaluj...";
    strings["scale##sgie"].plurals[0] = "skaluj";
    strings["randomize...##sgie"].plurals[0] = "wypełnij losowymi wartościami...";
    strings["Min##sgie"].plurals[0] = "mininum";
    strings["Max##sgie"].plurals[0] = "maksimum";
    strings["randomize##sgie"].plurals[0] = "losuj";

    //   sgmx  src/gui/mixer.cpp

    strings["input##sgmx"].plurals[0] = "wejście";
    strings["output##sgmx"].plurals[0] = "wyjście";
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

    //   sgme  src/gui/memory.cpp

    strings["Memory Composition###Memory Composition"].plurals[0] = "Zawartość pamięci###Memory Composition";

    //   sgor  src/gui/orders.cpp

    strings["Add new order##sgor"].plurals[0] = "Dodaj nowy wiersz matrycy";
    strings["Remove order##sgor"].plurals[0] = "Usuń wiersz matrycy";
    strings["Duplicate order (right-click to deep clone)##sgor"].plurals[0] = "Sklonuj wiersz (PPM by glęboko sklonować)";
    strings["Move order up##sgor"].plurals[0] = "Przenieś wiersz w górę";
    strings["Move order down##sgor"].plurals[0] = "Przenieś wiersz w dół";
    strings["Duplicate order at end of song (right-click to deep clone)##sgor"].plurals[0] = "Sklonuj wiersz i wstaw na koniec utworu (PPM by glęboko sklonować)";
    strings["Order change mode: entire row##sgor"].plurals[0] = "Tryb zmiany: cały wiersz";
    strings["Order change mode: one##sgor"].plurals[0] = "Tryb zmiany: jedna komórka";
    strings["Order edit mode: Select and type (scroll vertically)##sgor"].plurals[0] = "Tryb edycji: Wybierz i wpisz (przewiń w pionie)";
    strings["Order edit mode: Select and type (scroll horizontally)##sgor"].plurals[0] = "Tryb edycji: Wybierz i wpisz (przewiń w poziomie)";
    strings["Order edit mode: Select and type (don't scroll)##sgor"].plurals[0] = "Tryb edycji: Wybierz i wpisz";
    strings["Order edit mode: Click to change##sgor"].plurals[0] = "Tryb edycji: kliknij by zmienić";

    //   sgos  src/gui/osc.cpp

    strings["Oscilloscope###Oscilloscope"].plurals[0] = "Oscyloskop###Oscilloscope";
    strings["zoom: %.2fx (%.1fdB)##sgos"].plurals[0] = "powiększenie: %.2fx (%.1f dB)";
    strings["window size: %.1fms##sgos"].plurals[0] = "rozmiar okna: %.1f ms";
    strings["(-Infinity)dB##sgos"].plurals[0] = "(-nieskończoność) dB";

    //   sgpm  src/gui/patManager.cpp

    strings["Pattern Manager###Pattern Manager"].plurals[0] = "Menedżer wzorców###Pattern Manager";
    strings["Global Tasks:##sgpm"].plurals[0] = "Globalne edytowanie:";
    strings["De-duplicate patterns##sgpm"].plurals[0] = "Usuń zduplikowane wzorce";
    strings["Re-arrange patterns##sgpm"].plurals[0] = "Sortuj wzorce";
    strings["Sort orders##sgpm"].plurals[0] = "Sortuj wiesze matrycy wzorców";
    strings["Make patterns unique##sgpm"].plurals[0] = "Uczyń wzorce unikalnymi";
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
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Blaster 16 dla PC-9800, kompatybilny z PC-9801-26/K; z rozszerzonym kanałem 3)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (z Sound Blasterem 16 dla PC-9800, kompatybilny z PC-9801-26/K; z rozszerzonym kanałem 3 i CSM)";
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
    strings["Williams/Midway Y/T unit w/ADPCM sound board##sgpr"].plurals[0] = "Automat Williams/Midway Y/T z kartą dźwiękową ADPCM";
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
    strings["chips which use frequency modulation (FM) to generate sound.\nsome of these also pack more (like square and sample channels).\nActually \"FM\" here stands for phase modulation,\nbut these two are indistinguishable\nif you use sine waves.##sgpr"].plurals[0] = "układy wykorzystujące modulację częstotliwości (syntezę FM) do generowania dźwięku\nw niektorych z nich stosowane sa również inne metody syntezy dźwięku (kanały fali prostokątnej lub sample).\nW rzeczywistości \"FM\" oznacza tutaj modulację fazy, ale są one nie do odróżnienia od siebie, gdy używają fal sinusoidalnych.";
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
    strings["Yamaha YMF276 (extended channel 3)##sgpr"].plurals[0] = "Yamaha YMF276  z rozszerzonym kanałem 3";
    strings["Yamaha YMF276 with DualPCM##sgpr"].plurals[0] = "Yamaha YMF276 (OPN2L) z DualPCM";
    strings["Yamaha YMF276 (extended channel 3) with DualPCM and CSM##sgpr"].plurals[0] = "Yamaha YMF276 z rozszerzonym kanałem 3, DualPCM i CSM";
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
    strings["Modern/fantasy##sgpr"].plurals[0] = "Nowoczene/nieistniejace";
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

    strings["Register View###Register View"].plurals[0] = "Podglad rejestrów###Register View";
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
    strings["SNES: loop start must be a multiple of 16 (try with %d)##sgse"].plurals[0] = "SNES: początek pętli musi być wielokrotnością 16 (spróbuj %d)";
    strings["SNES: loop end must be a multiple of 16 (try with %d)##sgse"].plurals[0] = "SNES: koniec pętli musi być wielokrotnością 16 (spróbuj %d)";
    strings["SNES: sample length will be padded to multiple of 16##sgse"].plurals[0] = "SNES: długość sampla zostanie dostosowana do wielokrotności 16";
    strings["QSound: loop cannot be longer than 32767 samples##sgse"].plurals[0] = "QSound: pętla nie może być dłuższa niż 32767 sampli";
    strings["QSound: maximum sample length is 65535##sgse"].plurals[0] = "QSound: maksymalna długość sampla: 65535";
    strings["NES: loop point ignored on DPCM (may only loop entire sample)##sgse"].plurals[0] = "NES: punkt pętli jest ignorowany dla sampli DPCM (tylko cały sampel może być zapętlony)";
    strings["NES: maximum DPCM sample length is 32648##sgse"].plurals[0] = "NES: maksymalna długość sampla DPCM wynosi 32648";
    strings["X1-010: samples can't loop##sgse"].plurals[0] = "X1-010: zapętlanie sampli niewspierane";
    strings["X1-010: maximum sample length is 131072##sgse"].plurals[0] = "X1-010: maksymalna długość sampla wynosi 131072";
    strings["GA20: samples can't loop##sgse"].plurals[0] = "GA20: zapętlanie sampli niewspierane";
    strings["YM2608: loop point ignored on ADPCM (may only loop entire sample)##sgse"].plurals[0] = "YM2608: punkt pętli jest ignorowany dla ADPCM (tylko cały sampel może być zapętlony)";
    strings["YM2608: sample length will be padded to multiple of 512##sgse"].plurals[0] = "YM2608: długość sampla zostanie dostosowana do wielokrotności 512";
    strings["YM2610: ADPCM-A samples can't loop##sgse"].plurals[0] = "YM2610: ADPCM-A zapętlanie sampli niewspierane";
    strings["YM2610: loop point ignored on ADPCM-B (may only loop entire sample)##sgse"].plurals[0] = "YM2610: punkt pętli jest ignorowany dla ADPCM-B (tylko cały sampel może być zapętlony)";
    strings["YM2610: sample length will be padded to multiple of 512##sgse"].plurals[0] = "YM2610: długość sampla zostanie dostosowana do wielokrotności 512";
    strings["YM2610: maximum ADPCM-A sample length is 2097152##sgse"].plurals[0] = "YM2610: maksymalna długość sampla ADPCM-A  wynosi 2097152";
    strings["Y8950: loop point ignored on ADPCM (may only loop entire sample)##sgse"].plurals[0] = "Y8950: punkt pętli jest ignorowany dla ADPCM (tylko cały sampel może być zapętlony)";
    strings["Y8950: sample length will be padded to multiple of 512##sgse"].plurals[0] = "Y8950: długość sampla zostanie dostosowana do wielokrotności 512";
    strings["Amiga: loop start must be a multiple of 2##sgse"].plurals[0] = "Amiga: początek pętli musi być wielokrotnością 2";
    strings["Amiga: loop end must be a multiple of 2##sgse"].plurals[0] = "Amiga: koniec pętli musi być wielokrotnością 2";
    strings["Amiga: maximum sample length is 131070##sgse"].plurals[0] = "Amiga: maksymalna długość sampla wynosi 131070";
    strings["SegaPCM: maximum sample length is 65280##sgse"].plurals[0] = "SegaPCM: maksymalna długość sampla wynosi 65280";
    strings["K053260: loop point ignored (may only loop entire sample)##sgse"].plurals[0] = "K053260: punkt pętli jest ignorowany (tylko cały sampel może być zapętlony)";
    strings["K053260: maximum sample length is 65535##sgse"].plurals[0] = "K053260: maksymalna długość sampla wynosi 65535";
    strings["C140: maximum sample length is 65535##sgse"].plurals[0] = "C140: maksymalna długość sampla wynosi 65535";
    strings["C219: loop start must be a multiple of 2##sgse"].plurals[0] = "C219: początek pętli musi być wielokrotnością 2";
    strings["C219: loop end must be a multiple of 2##sgse"].plurals[0] = "C219: koniec pętli musi być wielokrotnością 2";
    strings["C219: maximum sample length is 131072##sgse"].plurals[0] = "C219: maksymalna długość sampla wynosi 131072";
    strings["MSM6295: samples can't loop##sgse"].plurals[0] = "MSM6295: zapętlanie sampli niewspierane";
    strings["MSM6295: maximum bankswitched sample length is 129024##sgse"].plurals[0] = "MSM6295: maksymalna długość sampla przy zmianie banków wynosi 129024";
    strings["ES5506: backward loop mode isn't supported##sgse"].plurals[0] = "ES5506: tryb pętli odwrotnej nie jest obsługiwany";
    strings["backward/ping-pong only supported in Generic PCM DAC\nping-pong also on ES5506##sgse"].plurals[0] = "Tryb odwrócony jest obsługiwany tylko przez uniwersalny przetwornik C/A, a także przez ES5506.";
    strings["Info##sgse"].plurals[0] = "Info";
    strings["Rate##sgse0"].plurals[0] = "Częstotliwość";
    strings["Compat Rate##sgse"].plurals[0] = "Kompat. częstotliwość";
    strings["used in DefleMask-compatible sample mode (17xx), in where samples are mapped to an octave.##sgse"].plurals[0] = "jest używana podczas odtwarzania w trybie zgodności z DefleMaskiem (17xx), w którym sample odpowiadają oktawie.";
    strings["Loop##sgse"].plurals[0] = "Pętla";
    strings["Loop (length: %d)##Loop"].plurals[0] = "Pętla (długość: %d)##Loop";
    strings["changing the loop in a BRR sample may result in glitches!##sgse0"].plurals[0] = "zmiana pętli sampla BRR może powodować problemy!";
    strings["Chips##sgse"].plurals[0] = "Układy";
    strings["Type##sgse"].plurals[0] = "Typ";
    strings["BRR emphasis##sgse"].plurals[0] = "Przetwarzanie końcowe BRR";
    strings["this is a BRR sample.\nenabling this option will muffle it (only affects non-SNES chips).##sgse"].plurals[0] = "jest to sampel BRR.\nwłączenie tej funkcji przytłumi go (na wszystkich układach poza SNES).";
    strings["enable this option to slightly boost high frequencies\nto compensate for the SNES' Gaussian filter's muffle.##sgse"].plurals[0] = "włącz tę opcję, aby lekko podbić wysokie częstotliwości.\naby skompensować filtrowanie interpolacji gaussowskiej, które powoduje, że sampel jest stłumiony.";
    strings["8-bit dither##sgse"].plurals[0] = "8-bitowy dithering";
    strings["dither the sample when used on a chip that only supports 8-bit samples.##sgse"].plurals[0] = "dithering sampla, gdy jest on używany na układzie obsługującym tylko 8-bitowe sample.";
    strings["Note##sgse"].plurals[0] = "Nuta";
    strings["%s"].plurals[0] = "%s";
    strings["Fine##sgse"].plurals[0] = "Rozstrojenie";
    strings["Mode##sgse"].plurals[0] = "Tryb";
    strings["Start##sgse"].plurals[0] = "Start";
    strings["changing the loop in a BRR sample may result in glitches!##sgse1"].plurals[0] = "zmiana pętli sampla BRR może powodować problemy!";
    strings["End##sgse"].plurals[0] = "Koniec";
    strings["changing the loop in a BRR sample may result in glitches!##sgse2"].plurals[0] = "zmiana pętli sampla BRR może powodować problemy!";
    strings["%s\n%d bytes free##sgse"].plurals[0] = "%s\nwolny %d bajt";
    strings["%s\n%d bytes free##sgse"].plurals[1] = "%s\nwolne %d bajty";
    strings["%s\n%d bytes free##sgse"].plurals[2] = "%s\nwolnych%d bajtów";
    strings["%s (%s)\n%d bytes free##sgse"].plurals[0] = "%s (%s)\nwolny %d bajy";
    strings["%s (%s)\n%d bytes free##sgse"].plurals[1] = "%s (%s)\nwolne %d bajty";
    strings["%s (%s)\n%d bytes free##sgse"].plurals[2] = "%s (%s)\nwolnych %d bajtów";
    strings["\n\nnot enough memory for this sample!##sgse"].plurals[0] = "\n\nza mało miejsca w pamięci na tego sampla!";
    strings["Edit mode: Select##sgse"].plurals[0] = "Tryb edycji: zaznaczanie";
    strings["Edit mode: Draw##sgse"].plurals[0] = "Tryb edycji: rysowanie";
    strings["Resize##sgse0"].plurals[0] = "Skaluj";
    strings["Samples##sgse0"].plurals[0] = "Sample (nowy rozmiar)";
    strings["Resize##sgse1"].plurals[0] = "Skaluj";
    strings["couldn't resize! make sure your sample is 8 or 16-bit.##sgse"].plurals[0] = "nie udało się zmienić rozmiaru! upewnij się, że sample są 8 lub 16-bitowe.";
    strings["Resample##sgse0"].plurals[0] = "Zmień częstotliwość samplowania";
    strings["Rate##sgse1"].plurals[0] = "Częstotliwość";
    strings["Factor##sgse"].plurals[0] = "Współczynnik";
    strings["Filter##sgse"].plurals[0] = "Filtr";
    strings["Resample##sgse1"].plurals[0] = "Zmień częstotliwość samplowania";
    strings["couldn't resample! make sure your sample is 8 or 16-bit.##sgse"].plurals[0] = "nie udało się zmienić częstotliwości samplowania! upewnij się, że sampel jest 8- lub 16-bitowy.";
    strings["Undo##sgse"].plurals[0] = "Cofnij";
    strings["Redo##sgse"].plurals[0] = "Ponów";
    strings["Amplify##sgse"].plurals[0] = "Wzmocnij";
    strings["Volume##sgse"].plurals[0] = "Głośność";
    strings["Apply##sgse0"].plurals[0] = "Zastosuj";
    strings["Normalize##sgse"].plurals[0] = "Normalizuj";
    strings["Fade in##sgse"].plurals[0] = "Płynny wzrost";
    strings["Fade out##sgse"].plurals[0] = "Płynne tłumienie";
    strings["Insert silence##sgse"].plurals[0] = "Wstaw ciszę";
    strings["Samples##sgse1"].plurals[0] = "Sample";
    strings["Go##sgse"].plurals[0] = "Zastosuj";
    strings["couldn't insert! make sure your sample is 8 or 16-bit.##sgse"].plurals[0] = "nie udało się wstawić! upewnij się że sampel jest 8- lub 16-bitowy.";
    strings["Apply silence##sgse"].plurals[0] = "Dodaj ciszę";
    strings["Delete##sgse"].plurals[0] = "Usuń";
    strings["Trim##sgse"].plurals[0] = "Obetnij";
    strings["Reverse##sgse"].plurals[0] = "Odwrotność";
    strings["Invert##sgse"].plurals[0] = "Odwróć";
    strings["Signed/unsigned exchange##sgse"].plurals[0] = "Ze znakiem <-> Bez znaku";
    strings["Apply filter##sgse"].plurals[0] = "Zastosuj filtr";
    strings["Cutoff:##sgse"].plurals[0] = "Pukt odcięcia:";
    strings["From##sgse"].plurals[0] = "Od";
    strings["To##sgse"].plurals[0] = "Do";
    strings["Resonance##sgse"].plurals[0] = "Rezonans";
    strings["Power##sgse"].plurals[0] = "Moc filtra";
    strings["Low-pass##sgse"].plurals[0] = "dolno-przepustowy";
    strings["Band-pass##sgse"].plurals[0] = "środkowo-przepustowy";
    strings["High-pass##sgse"].plurals[0] = "górno-przepustowy";
    strings["Apply##sgse1"].plurals[0] = "Zastosuj";
    strings["Crossfade loop points##sgse"].plurals[0] = "Punkty zapętlenia crossfade-u";
    strings["Number of samples##sgse"].plurals[0] = "Ilość sampli";
    strings["Linear <-> Equal power##sgse"].plurals[0] = "Liniowy <-> Ten sam stopień";
    strings["Apply##sgse2"].plurals[0] = "Zastosuj";
    strings["Crossfade: length would go out of bounds. Aborted...##sgse"].plurals[0] = "Crossfade: długość wyjdzie poza granice. Akcja anulowana.";
    strings["Crossfade: length would overflow loopStart. Try a smaller random value.##sgse"].plurals[0] = "Crossfade: długość wykracza poza początek cyklu. Spróbuj użyć mniejszej wartości losowej.";
    strings["Preview sample##sgse"].plurals[0] = "Poglad sampla";
    strings["Stop sample preview##sgse"].plurals[0] = "Zatrzymaj podglad sampla";
    strings["Create instrument from sample##sgse"].plurals[0] = "Stwórz instrument z sampla";
    strings["Zoom##sgse0"].plurals[0] = "Powiększ";
    strings["Zoom##sgse1"].plurals[0] = "Powiększ";
    strings["Auto##sgse"].plurals[0] = "Automatyczny";
    strings["cut##sgse"].plurals[0] = "wytnij";
    strings["copy##sgse"].plurals[0] = "kopiuj";
    strings["paste##sgse"].plurals[0] = "wklej";
    strings["paste (replace)##sgse"].plurals[0] = "wklej i zamień";
    strings["paste (mix)##sgse"].plurals[0] = "wstaw ze zmieszaniem";
    strings["select all##sgse"].plurals[0] = "wybierz wszystko";
    strings["set loop to selection##sgse"].plurals[0] = "ustaw pętlę na zaznaczeniu";
    strings["create wavetable from selection##sgse"].plurals[0] = "stwórz tablicę fal z zaznaczenia";
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
    strings["Tuning (A-4)##sgsi"].plurals[0] = "Tuning (A-4)";

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
    strings["YMF276 (external DAC)##sgsc"].plurals[0] = "YMF276 (zewnętrzny DAC)";
    strings["Disable ExtCh FM macros (compatibility)##sgsc0"].plurals[0] = "Wyłącz makra rozszerzonych kanałów FM (dla kompatybilności)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc0"].plurals[0] = "Zmiana instr. na operatorach 2-4 rozsz. kanału ma wpływ na FB (dla kompatybilności)";
    strings["Clock rate:##sgsc1"].plurals[0] = "Taktowanie zegara:";
    strings["1.79MHz (Half NTSC)##sgsc"].plurals[0] = "1.79 MHz (połowa NTSC)";
    strings["Chip type:##sgsc1"].plurals[0] = "Typ układu:";
    strings["TI SN76489 with Atari-like short noise##sgsc"].plurals[0] = "TI SN76489 z krótkim szumem podobnym do Atari";
    strings["Tandy PSSJ 3-voice sound##sgsc"].plurals[0] = "Trzykanałowe audio Tandy PSSJ";
    strings["Disable noise period change phase reset##sgsc"].plurals[0] = "Wyłącz reset fazy podczas zmiany okresu szumu";
    strings["Disable easy period to note mapping on upper octaves##sgsc0"].plurals[0] = "Wyłącz uproszczone mapowanie okresu na nutę na wyższych oktawach";
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
    strings["Enable echo##sgsc0"].plurals[0] = "Włącz echo";
    strings["Swap echo channels##sgsc"].plurals[0] = "Zamień miejscami kanały echo";
    strings["Echo delay:##sgsc0"].plurals[0] = "Opóźnienie echo:";
    strings["Echo resolution:##sgsc"].plurals[0] = "Rozdzielczość echo:";
    strings["Echo feedback:##sgsc0"].plurals[0] = "Feedback echo:";
    strings["Echo volume:##sgsc0"].plurals[0] = "Głośność echo:";
    strings["Disable anti-click##sgsc1"].plurals[0] = "Wyłącz anty-klikanie";
    strings["Chip revision:##sgsc1"].plurals[0] = "Rewizja konsoli:";
    strings["Original (DMG)##sgsc"].plurals[0] = "Oryginalny (DMG)";
    strings["Game Boy Color (rev C)##sgsc"].plurals[0] = "Game Boy Color (wersja C)";
    strings["Game Boy Color (rev E)##sgsc"].plurals[0] = "Game Boy Color (wersja E)";
    strings["Wave channel orientation:##sgsc"].plurals[0] = "Orientacja koanału syntezy tablicowej";
    strings["Normal##sgsc"].plurals[0] = "Normalna";
    strings["Inverted##sgsc"].plurals[0] = "Odwrócona";
    strings["Exact data (inverted)##sgsc"].plurals[0] = "Te same dane (odwrócona)";
    strings["Exact output (normal)##sgsc"].plurals[0] = "Ten sam dźwięk (normalna)";
    strings["Pretty please one more compat flag when I use arpeggio and my sound length##sgsc"].plurals[0] = "Cóż, proszę o kolejną flagę kompatybilności, gdy używam arpeggio i małej długości dźwięku na kanale szumu";
    strings["Clock rate:##sgsc2"].plurals[0] = "Taktowanie zegara:";
    strings["Arcade (4MHz)##sgsc"].plurals[0] = "Arcade (4 MHz)";
    strings["Half NTSC (1.79MHz)##sgsc"].plurals[0] = "Polowa NTSC (1.79 MHz)";
    strings["Patch set:##sgsc"].plurals[0] = "Zestaw instrumentów:";
    strings["Ignore top/hi-hat frequency changes##sgsc"].plurals[0] = "Ignoruj zmiany częstotliwości talerzy i hi-hatów";
    strings["Apply fixed frequency to all drums at once##sgsc"].plurals[0] = "Stosuj stałą częstotliwość do wszystich instrumentów perkusyjnych";
    strings["Broken pitch macro/slides (compatibility)##sgsc0"].plurals[0] = "Uszkodzone efekty portamento i makra (kompatybilność)";
    strings["Pseudo-PAL##sgsc1"].plurals[0] = "Pseudo-PAL";
    strings["Broken pitch macro/slides (compatibility)##sgsc1"].plurals[0] = "Uszkodzone efekty portamento i makra (kompatybilność)";
    strings["Clock rate:##sgsc20"].plurals[0] = "Taktowanie zegara:";
    strings["DPCM channel mode:##sgsc"].plurals[0] = "Tryb kanału DPCM:";
    strings["DPCM (muffled samples; low CPU usage)##sgsc"].plurals[0] = "DPCM (przytłumione sample, niskie zużycie CPU)";
    strings["PCM (crisp samples; high CPU usage)##sgsc"].plurals[0] = "PCM (czyste sample, wysokie zużycie CPU)";
    strings["Clock rate:##sgsc18"].plurals[0] = "Taktowanie zegara:";
    strings["Clock rate:##sgsc19"].plurals[0] = "Taktowanie zegara:";
    strings["Global parameter priority:##sgsc0"].plurals[0] = "Priorytek globalnych parametrów:";
    strings["Left to right##sgsc0"].plurals[0] = "Z lewej do prawej";
    strings["Last used channel##sgsc0"].plurals[0] = "Ostatni używany kanał";
    strings["Hard reset envelope:##sgsc"].plurals[0] = "OTwardy reset obwiedni:";
    strings["Attack##sgsc"].plurals[0] = "Atak";
    strings["Decay##sgsc"].plurals[0] = "Opadanie";
    strings["Sustain##sgsc"].plurals[0] = "Poodtrzymanie";
    strings["Release##sgsc"].plurals[0] = "Zwolnienie";
    strings["Envelope reset time:##sgsc"].plurals[0] = "Czas resetowania obwiedni:";
    strings["- 0 disables envelope reset. not recommended!\n- 1 may trigger SID envelope bugs.\n- values that are too high may result in notes being skipped.##sgsc"].plurals[0] = "- 0 wyłącza reset obwiedni. nie zalecane!\n- 1 może wywołać błędy obwiedni SIDa.\n- zbyt wysokie wartości mogą powodować pomijanie krótkich nut.";
    strings["Disable 1Exy env update (compatibility)##sgsc"].plurals[0] = "Wyłącz aktualizację obwiedni podczas stosowania efektu 1Exy (kompatybilność)";
    strings["Relative duty and cutoff macros are coarse (compatibility)##sgsc"].plurals[0] = "Makra szerokości fali prost. i punktu odcięcia w trybie względnym mają niższą rozdzielczość (kompatybilność)";
    strings["Disable ExtCh FM macros (compatibility)##sgsc1"].plurals[0] = "Wyłącz makra rozszerzonych kanałów FM (dla kompatybilności)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc1"].plurals[0] = "Zmiana instr. na operatorach 2-4 rozsz. kanału ma wpływ na FB (dla kompatybilności)";
    strings["SSG Volume##sgsc0"].plurals[0] = "Głośność SSG";
    strings["FM/ADPCM Volume##sgsc0"].plurals[0] = "Głośność FM/ADPCM";
    strings["Clock rate:##sgsc3"].plurals[0] = "Taktowanie zegara:";
    strings["0.83MHz (Pre-divided Sunsoft 5B on PAL)##sgsc"].plurals[0] = "0.83 MHz (Sunsoft 5B z już podzielonym taktowaniem, PAL)";
    strings["0.89MHz (Pre-divided Sunsoft 5B)##sgsc"].plurals[0] = "0.89 MHz (Sunsoft 5B z już podzielonym taktowaniem)";
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
    strings["Echo feedback:##sgsc1"].plurals[0] = "Feedback echo:";
    strings["Clock rate:##sgsc5"].plurals[0] = "Taktowanie zegara:";
    strings["Stereo##sgsc1"].plurals[0] = "Stereo";
    strings["Bankswitched (Seta 2)##sgsc"].plurals[0] = "Ze zmieniarką banków (Seta 2)";
    strings["Clock rate:##sgsc6"].plurals[0] = "Taktowanie zegara:";
    strings["Initial channel limit:##sgsc0"].plurals[0] = "Początkowy limit ilości kanałów:";
    strings["Disable hissing##sgsc"].plurals[0] = "Wyłącz trzeszczenie";
    strings["Scale frequency to wave length##sgsc"].plurals[0] = "Skaluj częstotliwość względem długości fali";
    strings["Initial channel limit:##sgsc1"].plurals[0] = "Początkowy limit ilości kanałów:";
    strings["Volume scale:##sgsc0"].plurals[0] = "Skalowanie głośności:";
    strings["Clock rate:##sgsc7"].plurals[0] = "Taktowanie zegara:";
    strings["Output rate:##sgsc0"].plurals[0] = "Częstotliwość audio na wyjściu:";
    strings["FM: clock / 72, SSG: clock / 16##sgsc0"].plurals[0] = "FM: takt. zegara / 72, SSG: takt. zegara / 16";
    strings["FM: clock / 36, SSG: clock / 8##sgsc"].plurals[0] = "FM: takt. zegara / 36, SSG: takt. zegara / 8";
    strings["FM: clock / 24, SSG: clock / 4##sgsc"].plurals[0] = "FM: takt. zegara / 24, SSG: takt. zegara / 4";
    strings["SSG Volume##sgsc1"].plurals[0] = "Głośność SSG";
    strings["FM Volume##sgsc"].plurals[0] = "Głośność FM";
    strings["Disable ExtCh FM macros (compatibility)##sgsc2"].plurals[0] = "Wyłącz makra rozszerzonych kanałów FM (dla kompatybilności)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc2"].plurals[0] = "Zmiana instr. na operatorach 2-4 rozsz. kanału ma wpływ na FB (dla kompatybilności)";
    strings["Clock rate:##sgsc8"].plurals[0] = "Taktowanie zegara:";
    strings["8MHz (Arcade)##sgsc"].plurals[0] = "8 MHz (Arcade)";
    strings["Output rate:##sgsc1"].plurals[0] = "Częstotliwość audio na wyjściu:";
    strings["FM: clock / 144, SSG: clock / 32##sgsc"].plurals[0] = "FM: takt. zegara / 144, SSG: takt. zegara / 32";
    strings["FM: clock / 72, SSG: clock / 16##sgsc1"].plurals[0] = "FM: takt. zegara / 72, SSG: takt. zegara / 16";
    strings["FM: clock / 48, SSG: clock / 8##sgsc"].plurals[0] = "FM: takt. zegara / 48, SSG: takt. zegara / 8";
    strings["SSG Volume##sgsc2"].plurals[0] = "Głośność SSG";
    strings["FM/ADPCM Volume##sgsc1"].plurals[0] = "Głośność FM/ADPCM";
    strings["Disable ExtCh FM macros (compatibility)##sgsc3"].plurals[0] = "Wyłącz makra rozszerzonych kanałów FM (dla kompatybilności)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc3"].plurals[0] = "Zmiana instr. na operatorach 2-4 rozsz. kanału ma wpływ na FB (dla kompatybilności)";
    strings["Clock rate:##sgsc9"].plurals[0] = "Taktowanie zegara:";
    strings["Chip type:##sgsc3"].plurals[0] = "Typ ukłądu:";
    strings["RF5C68 (10-bit output)##sgsc"].plurals[0] = "RF5C68 (10-bitowe audio)";
    strings["RF5C164 (16-bit output)##sgsc"].plurals[0] = "RF5C164 (16-bitowe audio)";
    strings["Clock rate:##sgsc10"].plurals[0] = "Taktowanie zegara:";
    strings["Sample rate table:##sgsc"].plurals[0] = "Tablica częstotliwości audio:";
    strings["divider \\ clock##sgsc"].plurals[0] = "dzielnik zegara";
    strings["full##sgsc"].plurals[0] = "pełna";
    strings["half##sgsc"].plurals[0] = "połowiczna";
    strings["Clock rate:##sgsc11"].plurals[0] = "Taktowanie zegara:";
    strings["Output rate:##sgsc2"].plurals[0] = "Częstotliwość audio na wyjściu:";
    strings["clock / 132##sgsc"].plurals[0] = "takt. zegara / 132";
    strings["clock / 165##sgsc"].plurals[0] = "takt. zegara / 165";
    strings["Bankswitched (NMK112)##sgsc"].plurals[0] = "Ze zmieniarką banków (NMK112)";
    strings["Clock rate:##sgsc12"].plurals[0] = "Taktowanie zegara:";
    strings["1.5MHz (Arcade)##sgsc"].plurals[0] = "1.5 MHz (Arcade)";
    strings["Clock rate:##sgsc13"].plurals[0] = "Taktowanie zegara:";
    strings["Clock rate:##sgsc14"].plurals[0] = "Taktowanie zegara:";
    strings["Chip type:##sgsc4"].plurals[0] = "Typ układu:";
    strings["Compatible panning (0800)##sgsc"].plurals[0] = "Kompatybilny panning (0800)";
    strings["Clock rate:##sgsc15"].plurals[0] = "Taktowanie zegara:";
    strings["Output rate:##sgsc3"].plurals[0] = "Częstotliwość audio na wyjściu:";
    strings["Output bit depth:##sgsc"].plurals[0] = "Rozdzielczość audio na wyjściu:";
    strings["Stereo##sgsc2"].plurals[0] = "Stereo";
    strings["Interpolation:##sgsc"].plurals[0] = "Interpolacja:";
    strings["None##sgsc"].plurals[0] = "Wył.";
    strings["Linear##sgsc"].plurals[0] = "Liniowa";
    strings["Cubic##sgsc"].plurals[0] = "Sześcienna";
    strings["Sinc##sgsc"].plurals[0] = "Sinc";
    strings["Volume scale:##sgsc1"].plurals[0] = "Skalowanie głośności:";
    strings["Left##VolScaleL"].plurals[0] = "Lewo##VolScaleL";
    strings["Right##VolScaleL"].plurals[0] = "Prawo##VolScaleL";
    strings["Enable echo##sgsc1"].plurals[0] = "Włącz echo";
    strings["Initial echo state:##sgsc"].plurals[0] = "Początkowy stan echo:";
    strings["Delay##EchoDelay"].plurals[0] = "Opóźnienie##EchoDelay";
    strings["Feedback##EchoFeedback"].plurals[0] = "Sprz. zwrotne##EchoFeedback";
    strings["Echo volume:##sgsc1"].plurals[0] = "Głośność echo:";
    strings["Left##EchoVolL"].plurals[0] = "Lewe##EchoVolL";
    strings["Right##EchoVolL"].plurals[0] = "Prawe##EchoVolL";
    strings["Echo filter:##sgsc"].plurals[0] = "Filtr echo:";
    strings["Hex##SNESFHex"].plurals[0] = "Heks.##SNESFHex";
    strings["Dec##SNESFHex"].plurals[0] = "Dzies.##SNESFHex";
    strings["sum: %d##sgsc"].plurals[0] = "suma: %d";
    strings["Detune##sgsc"].plurals[0] = "Rozstrojenie";
    strings["Capacitor values (nF):##sgsc"].plurals[0] = "Pojemność kondensatorów (nF):";
    strings["Initial part volume (channel 1-4):##sgsc"].plurals[0] = "Głośnośc początkowa (kanały 1-4):";
    strings["Initial part volume (channel 5-8):##sgsc"].plurals[0] = "Głośnośc początkowa (kanały 5-8):";
    strings["Envelope mode (channel 1-4):##sgsc"].plurals[0] = "Tryb obwiedni(kanały 1-4):";
    strings["Capacitor (attack/decay)##EM00"].plurals[0] = "Kondensator (atak/opadanie)##EM00";
    strings["External (volume macro)##EM01"].plurals[0] = "Zewnętrzna (makro głośności)##EM01";
    strings["Envelope mode (channel 5-8):##sgsc"].plurals[0] = "Tryb obwiedni(kanały 5-8):";
    strings["Capacitor (attack/decay)##EM10"].plurals[0] = "Kondensator (atak/opadanie)##EM10";
    strings["External (volume macro)##EM11"].plurals[0] = "Zewnętrzna (makro głośności)##EM11";
    strings["Global vibrato:##sgsc"].plurals[0] = "Globalne vibrato:";
    strings["Speed##sgsc"].plurals[0] = "Prędkość";
    strings["Depth##sgsc"].plurals[0] = "Głębokość";
    strings["Disable easy period to note mapping on upper octaves##sgsc1"].plurals[0] = "Wyłącz uproszczone mapowanie okresu na nutę na wyższych oktawach";
    strings["Stereo##sgsc3"].plurals[0] = "Stereo";
    strings["Waveform storage mode:##sgsc0"].plurals[0] = "Sposób przechowywania fal:";
    strings["RAM##sgsc"].plurals[0] = "RAM";
    strings["ROM (up to 8 waves)##sgsc"].plurals[0] = "RAM (maks. 8 fal)";
    strings["Compatible noise frequencies##sgsc"].plurals[0] = "Kompatybilne częstotliwości szumu";
    strings["Legacy slides and pitch (compatibility)##sgsc"].plurals[0] = "Przestarzałe wysokości dźwięku i portamento (kompatybilność)";
    strings["Clock rate:##sgsc16"].plurals[0] = "Taktowanie zegara:";
    strings["Clock rate:##sgsc17"].plurals[0] = "Taktowanie zegara:";
    strings["Global parameter priority:##sgsc1"].plurals[0] = "Globalny priorytet parametrów:";
    strings["Left to right##sgsc1"].plurals[0] = "Od lewej do prawej";
    strings["Last used channel##sgsc1"].plurals[0] = "Ostatni używany kanał";
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

    strings["Chip Manager###Chip Manager"].plurals[0] = "Menedżer układów###Chip Manager";
    strings["Preserve channel order##sgsm"].plurals[0] = "Zachowaj kolejność kanałów";
    strings["Clone channel data##sgsm"].plurals[0] = "Klonuj dane kanału";
    strings["Clone at end##sgsm"].plurals[0] = "Sklonuj i wstaw na koniec";
    strings["Name##sgsm"].plurals[0] = "Nazwa";
    strings["Actions##sgsm"].plurals[0] = "Działania";
    strings["(drag to swap chips)##sgsm"].plurals[0] = "(przeciągnij aby zamienić miejscami układy)";
    strings["Clone##SysDup"].plurals[0] = "Klonuj##SysDupl";
    strings["cannot duplicate chip! (##sgsm"].plurals[0] = "nie udało się sklonować układu!";
    strings["max number of systems is %d##sgsm"].plurals[0] = "maksymalna ilość systemów to %d";
    strings["max number of total channels is %d##sgsm"].plurals[0] = "maksymalna ilość kanałów to %d";
    strings["Change##SysChange"].plurals[0] = "Zmień##SysChange";
    strings["Are you sure you want to remove this chip?##sgsm"].plurals[0] = "Czy jesteś pewien że chcesz usunąć ten układ?";
    strings["Remove##sgsm"].plurals[0] = "Usuń";
    strings["cannot add chip! (##sgsm"].plurals[0] = "nie da się dodać układu! (";

    //   sgsa  src/gui/sysPartNumber.cpp

    strings["ZXS Beeper##sgsa"].plurals[0] = "ZXS (brzęczyk)";

    //   sgsp  src/gui/sysPicker.cpp

    strings["Search...##sgsp"].plurals[0] = "Szukaj...";

    // # sgvm  src/gui/volMeter.cpp

    strings["Volume Meter###Volume Meter"].plurals[0] = "Miernik glośności###Volume Meter";

    //   sgwe  src/gui/waveEdit.cpp

    strings["Sine##sgwe0"].plurals[0] = "Sinusoida";
    strings["Triangle##sgwe0"].plurals[0] = "Fala trójkątna";
    strings["Saw##sgwe0"].plurals[0] = "Fala piłokształtna";
    strings["Pulse##sgwe"].plurals[0] = "Fala kwadratowa";

    strings["None##sgwe"].plurals[0] = "Brak";
    strings["Linear##sgwe"].plurals[0] = "Liniowa";
    strings["Cosine##sgwe"].plurals[0] = "Kosinusoidalny";
    strings["Cubic##sgwe"].plurals[0] = "Sześćienny";

    strings["Sine##sgwe1"].plurals[0] = "Sinusoida";
    strings["Rect. Sine##sgwe"].plurals[0] = "Sinusoida rekt.";
    strings["Abs. Sine##sgwe"].plurals[0] = "Moduł sinusoidy";
    strings["Quart. Sine##sgwe"].plurals[0] = "Ćwierć sinusoidy";
    strings["Squish. Sine##sgwe"].plurals[0] = "Spłaszczona sinusoida";
    strings["Abs. Squish. Sine##sgwe"].plurals[0] = "Spł. moduł sinusoidy";
    strings["Square##sgwe"].plurals[0] = "Fala kwadratowa";
    strings["rectSquare##sgwe"].plurals[0] = "Pochodna fali kwadratowej";
    strings["Saw##sgwe1"].plurals[0] = "Fala piłokształtna";
    strings["Rect. Saw##sgwe"].plurals[0] = "Pochodna fali piłokształtnej";
    strings["Abs. Saw##sgwe"].plurals[0] = "Moduł fali piłokształtnej";
    strings["Cubed Saw##sgwe"].plurals[0] = "Fala piłokształtna^3";
    strings["Rect. Cubed Saw##sgwe"].plurals[0] = "Pochodna fali piłokształtnej^3";
    strings["Abs. Cubed Saw##sgwe"].plurals[0] = "Moduł fali piłokształtnej^3";
    strings["Cubed Sine##sgwe"].plurals[0] = "Sinusoida^3";
    strings["Rect. Cubed Sine##sgwe"].plurals[0] = "Pochodna sinusoidy^3";
    strings["Abs. Cubed Sine##sgwe"].plurals[0] = "Moduł sinusoidy^3";
    strings["Quart. Cubed Sine##sgwe"].plurals[0] = "Ćwierć sinusoidy^3";
    strings["Squish. Cubed Sine##sgwe"].plurals[0] = "Spłaszczona sinusoida^3";
    strings["Squish. Abs. Cub. Sine##sgwe"].plurals[0] = "Spł moduł sinusoidy^3";
    strings["Triangle##sgwe1"].plurals[0] = "Fala trójkątna";
    strings["Rect. Triangle##sgwe"].plurals[0] = "Pochodna fali trójkątnej";
    strings["Abs. Triangle##sgwe"].plurals[0] = "Moduł fali trójkątnej";
    strings["Quart. Triangle##sgwe"].plurals[0] = "Ćwierć fali trójkątnej";
    strings["Squish. Triangle##sgwe"].plurals[0] = "Spłaszczona fala trójkątna";
    strings["Abs. Squish. Triangle##sgwe"].plurals[0] = "Spł. moduł. fali trójkątnej";
    strings["Cubed Triangle##sgwe"].plurals[0] = "Fala trójkątna^3";
    strings["Rect. Cubed Triangle##sgwe"].plurals[0] = "Pochodna fali trójkątnej^3";
    strings["Abs. Cubed Triangle##sgwe"].plurals[0] = "Moduł fali trójkątnej^3";
    strings["Quart. Cubed Triangle##sgwe"].plurals[0] = "Ćwierć fali trójkątnej^3";
    strings["Squish. Cubed Triangle##sgwe"].plurals[0] = "Spł. fala trójkątna^3";
    strings["Squish. Abs. Cub. Triangle##sgwe"].plurals[0] = "Spł. moduł fali trójkątnej^3";

    strings["Wavetable Editor###Wavetable Editor"].plurals[0] = "Ebytor tablic fal###Wavetable Editor";
    strings["no wavetable selected##sgwe0"].plurals[0] = "nie wybrano tablicy fal";
    strings["no wavetable selected##sgwe1"].plurals[0] = "nie wybrano tablicy fal";
    strings["select one...##sgwe"].plurals[0] = "wybierz jeden...";
    strings["or##sgwe0"].plurals[0] = "albo";
    strings["Open##sgwe0"].plurals[0] = "Otwórz";
    strings["or##sgwe1"].plurals[0] = "albo";
    strings["Create New##sgwe"].plurals[0] = "Stwórz nowy";
    strings["Open##sgwe1"].plurals[0] = "Otwórz";
    strings["Save##sgwe"].plurals[0] = "Zapisz";
    strings["export .dmw...##sgwe"].plurals[0] = "eksportuj do .dmw...";
    strings["export raw...##sgwe"].plurals[0] = "eksportuj dane surowe...";
    strings["Steps##sgwe"].plurals[0] = "Kroki";
    strings["Lines##sgwe"].plurals[0] = "Linie";
    strings["Width##sgwe"].plurals[0] = "Szerokość";
    strings["use a width of:\n- any on Amiga/N163\n- 32 on Game Boy, PC Engine, SCC, Konami Bubble System, Namco WSG, Virtual Boy and WonderSwan\n- 64 on FDS\n- 128 on X1-010\n- 256 for ES5503\nany other widths will be scaled during playback.##sgwe"].plurals[0] = "stosuj długości fal:\n- dowolna dla Amigi/N163\n- 32 dla Game Boy, PC Engine, SCC, Konami Bubble System, Namco WSG, Virtual Boy i WonderSwan\n- 64 dla FDS\n- 128 dla X1-010\n- 256 dla ES5503\nwszystkie inne długości będą przeskalowane do właściwych podczas odtwarzania.";
    strings["Height##sgwe"].plurals[0] = "Wysokość";
    strings["use a height of:\n- 16 for Game Boy, WonderSwan, Namco WSG, Konami Bubble System, X1-010 Envelope shape and N163\n- 32 for PC Engine\n- 64 for FDS and Virtual Boy\n- 256 for X1-010, SCC and ES5503\nany other heights will be scaled during playback.##sgwe"].plurals[0] = "stosuj wysokości fal:\n- 16 dla Game Boy, WonderSwan, Namco WSG, Konami Bubble System, kształtu obwiedni X1-010 i N163\n- 32 dla PC Engine\n- 64 dla FDS и Virtual Boy\n- 256 dla X1-010, SCC и ES5503\nszystkie inne wyskokości będą przeskalowane do właściwych podczas odtwarzania.";
    strings["Shapes##sgwe"].plurals[0] = "Kształty fal";
    strings["Duty##sgwe"].plurals[0] = "Szerokość fali prost.";
    strings["Exponent##sgwe"].plurals[0] = "Stopień";
    strings["XOR Point##sgwe"].plurals[0] = "Punkt XOR";
    strings["Amplitude/Phase##sgwe"].plurals[0] = "Amplituda/faza";
    strings["Op##sgwe0"].plurals[0] = "Op";
    strings["Level##sgwe"].plurals[0] = "Głośność";
    strings["Mult##sgwe"].plurals[0] = "Mnoznik";
    strings["FB##sgwe"].plurals[0] = "FB";
    strings["Op##sgwe1"].plurals[0] = "Op.";
    strings["Waveform##sgwe"].plurals[0] = "Kształt fali";
    strings["Connection Diagram##sgwe0"].plurals[0] = "Matryca połączeń";
    strings["Connection Diagram##sgwe1"].plurals[0] = "Matryca połączeń";
    strings["Out##sgwe"].plurals[0] = "Wyjście";
    strings["WaveTools##sgwe"].plurals[0] = "Narzędzia tablic fal";
    strings["Scale X##sgwe"].plurals[0] = "Skaluj oś X";
    strings["wavetable longer than 256 samples!##sgwe"].plurals[0] = "tablica fal powyżej 256 sampli!";
    strings["Scale Y##sgwe"].plurals[0] = "Skaluj oś Y";
    strings["Offset X##sgwe"].plurals[0] = "Przesuń X";
    strings["Offset Y##sgwe"].plurals[0] = "Przesuń Y";
    strings["Smooth##sgwe"].plurals[0] = "Wygładź";
    strings["Amplify##sgwe"].plurals[0] = "Wzmocnij";
    strings["Normalize##sgwe"].plurals[0] = "Normalizuj";
    strings["Invert##sgwe"].plurals[0] = "Odrwóć";
    strings["Reverse##sgwe"].plurals[0] = "Odwróć (Oś X)";
    strings["Half##sgwe"].plurals[0] = "Zmniejsz 2x";
    strings["Double##sgwe"].plurals[0] = "Powiększ 2x";
    strings["Convert Signed/Unsigned##sgwe"].plurals[0] = "Konwersja ze znakiem/bez znaku";
    strings["Randomize##sgwe"].plurals[0] = "Losuj wartości";
    strings["Dec##sgwe"].plurals[0] = "Dec.";
    strings["Hex##sgwe"].plurals[0] = "Hex.";
    strings["Signed/Unsigned##sgwe"].plurals[0] = "Ze znakiem <-> bez znaku";

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
    strings["Instruments###Instruments"].plurals[0] = "Instrumenty###Instruments";
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

    strings["Release"].plurals[0] = "Zwolnienie";
    strings["Loop"].plurals[0] = "Pętla";

    strings["HP/K2, HP/K2##sgmu"].plurals[0] = "HP/K2, HP/K2";
    strings["HP/K2, LP/K1##sgmu"].plurals[0] = "HP/K2, LP/K1";
    strings["LP/K2, LP/K2##sgmu"].plurals[0] = "LP/K2, LP/K2";
    strings["LP/K2, LP/K1##sgmu"].plurals[0] = "LP/K2, LP/K1";

    strings["Saw##sgmu"].plurals[0] = "Fala piłokształtna";
    strings["Square##sgmu"].plurals[0] = "Fala kwadratowa";
    strings["Triangle##sgmu"].plurals[0] = "Fala trójkątna";
    strings["Random##sgmu"].plurals[0] = "Szum";

    //src/gui/settings.cpp


    strings["<Use system font>##sgse0"].plurals[0] = "<Używaj czcionki systemowej>";
    strings["<Custom...>##sgse0"].plurals[0] = "<Niestandardowa...>";
    strings["<Use system font>##sgse1"].plurals[0] = "<Używaj czcionki systemowej>";
    strings["<Custom...>##sgse1"].plurals[0] = "<Niestandardowa...>";
    strings["<Use system font>##sgse2"].plurals[0] = "<Używaj czcionki systemowej>";
    strings["<Custom...>##sgse2"].plurals[0] = "<Niestandardowa...>";
    strings["Mono##sgse0"].plurals[0] = "Mono";
    strings["Stereo##sgse"].plurals[0] = "Stereo";
    strings["What?##sgse0"].plurals[0] = "Co?";
    strings["Quadraphonic##sgse"].plurals[0] = "Kwadrofoniczny";
    strings["What?##sgse1"].plurals[0] = "Co?";
    strings["5.1 Surround##sgse"].plurals[0] = "5.1 przestrzenny";
    strings["What?##sgse2"].plurals[0] = "Co?";
    strings["7.1 Surround##sgse"].plurals[0] = "7.1 przestrzenny";
    strings["High##sgse"].plurals[0] = "Wysokie";
    strings["Low##sgse"].plurals[0] = "Niskie";
    strings["ASAP (C++ port)##sgse"].plurals[0] = "ASAP (przepisany na C++)";
    strings["KIOCSOUND on /dev/tty1##sgse"].plurals[0] = "KIOCSOUND na /dev/tty1";
    strings["KIOCSOUND on standard output##sgse"].plurals[0] = "KIOCSOUND na standardowym wyjściu";
    strings["Disabled/custom##sgse0"].plurals[0] = "Wył./niestandardowy";
    strings["Two octaves (0 is C-4, F is D#5)##sgse"].plurals[0] = "Dwie oktawy (0 = C-4, F = D#5)";
    strings["Raw (note number is value)##sgse"].plurals[0] = "Tryb surowy (numer nuty jest wartością)";
    strings["Two octaves alternate (lower keys are 0-9, upper keys are A-F)##sgse"].plurals[0] = "Alternatywne wprowadzanie dwóch oktaw (dolne klawisze 0-9, górne klawisze A-F)";
    strings["Use dual control change (one for each nibble)##sgse0"].plurals[0] = "Użyj podwójnej komendy CC (jedna na półbajt)";
    strings["Use 14-bit control change##sgse0"].plurals[0] = "Użyj 14-bitowej komendy CC";
    strings["Use single control change (imprecise)##sgse0"].plurals[0] = "Użyj pojedynczej komendy CC (niska dokładność)";
    strings["Disabled/custom##sgse1"].plurals[0] = "Wył./niestandardowy";
    strings["Use dual control change (one for each nibble)##sgse1"].plurals[0] = "Użyj podwójnej komendy CC (jedna na półbajt)";
    strings["Use 14-bit control change##sgse1"].plurals[0] = "Użyj 14-bitowej komendy CC";
    strings["Use single control change (imprecise)##sgse1"].plurals[0] = "Użyj pojedynczej komendy CC (niska dokładność)";
    strings["--select--##sgse"].plurals[0] = "--wybierz--";
    strings["Note Off##sgse"].plurals[0] = "Puszczenie klawisza";
    strings["Note On##sgse"].plurals[0] = "Wciśnięcie klawisza";
    strings["Aftertouch##sgse"].plurals[0] = "Aftertouch";
    strings["Control##sgse"].plurals[0] = "Wartość CC";
    strings["Program##sgse0"].plurals[0] = "Program";
    strings["ChanPressure##sgse"].plurals[0] = "Równe naciskanie na kanał MIDI";
    strings["Pitch Bend##sgse"].plurals[0] = "Zmiana wysokości dźwięku";
    strings["SysEx##sgse"].plurals[0] = "SysEx";
    strings["Instrument##sgse0"].plurals[0] = "Instrument";
    strings["Volume##sgse0"].plurals[0] = "Głośność";
    strings["Effect 1 type##sgse"].plurals[0] = "Indeks efektu №1";
    strings["Effect 1 value##sgse"].plurals[0] = "Fala Parametr efektu №1";
    strings["Effect 2 type##sgse"].plurals[0] = "Indeks efektu №2";
    strings["Effect 2 value##sgse"].plurals[0] = "Fala Parametr efektu №2";
    strings["Effect 3 type##sgse"].plurals[0] = "Indeks efektu №3";
    strings["Effect 3 value##sgse"].plurals[0] = "Fala Parametr efektu №3";
    strings["Effect 4 type##sgse"].plurals[0] = "Indeks efektu №4";
    strings["Effect 4 value##sgse"].plurals[0] = "Fala Parametr efektu №4";
    strings["Effect 5 type##sgse"].plurals[0] = "Indeks efektu №5";
    strings["Effect 5 value##sgse"].plurals[0] = "Fala Parametr efektu №5";
    strings["Effect 6 type##sgse"].plurals[0] = "Indeks efektu №6";
    strings["Effect 6 value##sgse"].plurals[0] = "Fala Parametr efektu №6";
    strings["Effect 7 type##sgse"].plurals[0] = "Indeks efektu №7";
    strings["Effect 7 value##sgse"].plurals[0] = "Fala Parametr efektu №7";
    strings["Effect 8 type##sgse"].plurals[0] = "Indeks efektu №8";
    strings["Effect 8 value##sgse"].plurals[0] = "Fala Parametr efektu №8";

    strings["Press key...##sgse"].plurals[0] = "Naciśnij klawisz...";
    strings["Settings###Settings"].plurals[0] = "Ustawienia###Settings";
    strings["Do you want to save your settings?##sgse"].plurals[0] = "Czy chcesz zapisać swoje ustawienia?";

    strings["General##sgse"].plurals[0] = "Ogólne";
    strings["Program##sgse1"].plurals[0] = "Program";
    strings["Render backend##sgse"].plurals[0] = "Biblioteka renderownaia";
    strings["you may need to restart Furnace for this setting to take effect.##sgse0"].plurals[0] = "może być konieczne ponowne uruchomienie Furnace, aby ta opcja została zastosowana";
    strings["Render driver##sgse"].plurals[0] = "Sterownik renderowwania";
    strings["Automatic##sgse0"].plurals[0] = "Automatyczny";
    strings["Automatic##sgse1"].plurals[0] = "Automatyczny";
    strings["you may need to restart Furnace for this setting to take effect.##sgse1"].plurals[0] = "może być konieczne ponowne uruchomienie Furnace, aby ta opcja została zastosowana.";
    strings["Late render clear##sgse"].plurals[0] = "Opóźnione czyszczenie bufora renderowania";
    strings["calls rend->clear() after rend->present(). might reduce UI latency by one frame in some drivers.##sgse"].plurals[0] = "Wywołuje rend->clear() po rend->present(). Może wyeliminować opóźnienie o jedną klatkę w renderowaniu interfejsu przy niektórych sterownikach.";
    strings["Power-saving mode##sgse"].plurals[0] = "Tryb oszczędzania energii";
    strings["saves power by lowering the frame rate to 2fps when idle.\nmay cause issues under Mesa drivers!##sgse"].plurals[0] = "zmniejsza zużycie energii, redukując szybkość renderowania do dwóch klatek na sekundę w trybie czuwania.\nmoże powodować problemy pod sterownikami Mesa!";
    strings["Disable threaded input (restart after changing!)##sgse"].plurals[0] = "Wyłącz przetwarzanie naciśnięć klawiszy w osobnych wątkach (uruchom ponownie program po zmianie!).";
    strings["threaded input processes key presses for note preview on a separate thread (on supported platforms), which reduces latency.\nhowever, crashes have been reported when threaded input is on. enable this option if that is the case.##sgse"].plurals[0] = "przetwarzanie naciśnięć klawiszy dla podglądu instrumentów odbywa się wielowątkowo (na obsługiwanych platformach), co zmniejsza opóźnienia.\nsą jednak doniesienia o zawieszaniu się programu po wyłączeniu tej opcji, w takim przypadku włącz ją.";
    strings["Enable event delay##sgse"].plurals[0] = "Włącz opóźnienie zdarzeń";
    strings["may cause issues with high-polling-rate mice when previewing notes.##sgse"].plurals[0] = "może powodować problemy podczas podglądu instrumentów, jeśli podłączona jest mysz o wysokiej częstotliwości odświeżania.";
    strings["Per-channel oscilloscope threads##sgse"].plurals[0] = "Wielowątkowość oscyloskopu dla poszczególnych kanałów";
    strings["you're being silly, aren't you? that's enough.##sgse"].plurals[0] = "wystarczy.";
    strings["what are you doing? stop!##sgse"].plurals[0] = "stop!";
    strings["it is a bad idea to set this number higher than your CPU core count (%d)!##sgse"].plurals[0] = " ustawianie tej wartości na wyższą niż ilość rdzeni twojego CPU to bardzo zły pomysł (%d)!";
    strings["Oscilloscope rendering engine:##sgse"].plurals[0] = "Silnik renderowania oscyloskopu:";
    strings["ImGui line plot##sgse"].plurals[0] = "Rysunek linii z ImGui";
    strings["render using Dear ImGui's built-in line drawing functions.##sgse"].plurals[0] = "renderuj przy pomocy wbudowanych funkcji Dear ImGui.";
    strings["GLSL/HLSL (if available)##sgse"].plurals[0] = "GLSL/HLSL (jeśli dostępne)";
    strings["render using shaders that run on the graphics card.\nonly available in OpenGL render backend.##sgse"].plurals[0] = "renderowanie przy użyciu shaderów wykonywanych na GPU.\ndostępny wyłącznie na silniku renderowania OpenGL";
    strings["File##sgse"].plurals[0] = "Plik";
    strings["Use system file picker##sgse"].plurals[0] = "Użyj systemowego okna wyboru plików";
    strings["Number of recent files##sgse"].plurals[0] = "Ilość ostatnich plików";
    strings["Compress when saving##sgse"].plurals[0] = "Kompresuj podczas zapisu";
    strings["use zlib to compress saved songs.##sgse"].plurals[0] = "иużywaj biblioteki zlib do kompresji utworów.";
    strings["Save unused patterns##sgse"].plurals[0] = "Zapisuj nieużywane wzorce";
    strings["Use new pattern format when saving##sgse"].plurals[0] = "Używaj nowego formatu wzorców podczas zapisywania";
    strings["use a packed format which saves space when saving songs.\ndisable if you need compatibility with older Furnace and/or tools\nwhich do not support this format.##sgse"].plurals[0] = "użyj skompresowanego formatu do zapisywania wzorców, co zmniejsza rozmiar pliku modułu.\nwyłącz tę opcję, jeśli chcesz zachować kompatybilność ze starszymi wersjami Furnace\n i/lub innymi programami, które nie obsługują nowego formatu.";
    strings["Don't apply compatibility flags when loading .dmf##sgse"].plurals[0] = "Nie stosuj flag kompatybilności podczas wczytywania pliku .dmf";
    strings["do not report any issues arising from the use of this option!##sgse"].plurals[0] = "nie zgłaszaj żadnych problemów występujących po włączeniu tej opcji!";
    strings["Play after opening song:##sgse"].plurals[0] = "Odtawrzaj po otwarciu utworu:";
    strings["No##pol0"].plurals[0] = "Nie##pol0";
    strings["Only if already playing##pol1"].plurals[0] = "Tylko jeśli już jest odtwarzany##pol1";
    strings["Yes##pol0"].plurals[0] = "Tak##pol0";
    strings["Audio export loop/fade out time:##sgse"].plurals[0] = "Liczba cykli odtwarzania i czas wyciszania podczas eksportowania dźwięku:";
    strings["Set to these values on start-up:##fot0"].plurals[0] = "Ustaw te wartości podczas uruchamiania:##fot0";
    strings["Loops##sgse"].plurals[0] = "Pętle";
    strings["Fade out (seconds)##sgse"].plurals[0] = "Wyciszanie (w sekundach)";
    strings["Remember last values##fot1"].plurals[0] = "Zapamiętuj ostatnie wartości##fot1";
    strings["Store instrument name in .fui##sgse"].plurals[0] = "Przechowuj nazwę instrumentu w pliku .fui";
    strings["when enabled, saving an instrument will store its name.\nthis may increase file size.##sgse"].plurals[0] = "po włączeniu tej opcji nazwa instrumentu zostanie zapisana w pliku, co może zwiększyć jego rozmiar.";
    strings["Load instrument name from .fui##sgse"].plurals[0] = "Wczytaj nazwę instrumentu z pliku .fui";
    strings["when enabled, loading an instrument will use the stored name (if present).\notherwise, it will use the file name.##sgse"].plurals[0] = "gdy opcja ta jest włączona, nazwa instrumentu zostanie wczytana z pliku (jeśli w pliku znajduje się nazwa).\nw przeciwnym razie użyta zostanie nazwa pliku.";
    strings["New Song##sgse"].plurals[0] = "Nowy utwór";
    strings["Initial system:##sgse"].plurals[0] = "System domyślny:";
    strings["Current system##sgse"].plurals[0] = "Bieżący";
    strings["Randomize##sgse"].plurals[0] = "Losuj";
    strings["Reset to defaults##sgse"].plurals[0] = "Resetuj ustawienia";
    strings["Name##sgse"].plurals[0] = "Nazwa";
    strings["Invert##sgse0"].plurals[0] = "Odwróć";
    strings["Invert##sgse1"].plurals[0] = "Odwróć";
    strings["Volume##sgse1"].plurals[0] = "Głośność";
    strings["Panning##sgse"].plurals[0] = "Panning";
    strings["Front/Rear##sgse"].plurals[0] = "Przód/tył";
    strings["Configure##sgse"].plurals[0] = "Konfiguruj";
    strings["When creating new song:##sgse"].plurals[0] = "Przy tworzeniu nowego utworu:";
    strings["Display system preset selector##NSB0"].plurals[0] = "Wyświetlaj okno wyboru domyślnego systemu##NSB0";
    strings["Start with initial system##NSB1"].plurals[0] = "Rozpocznij od systemu domyślnego##NSB1";
    strings["Default author name##sgse"].plurals[0] = "Domyślna nazwa autora";
    strings["Start-up##sgse"].plurals[0] = "Uruchamianie";
    strings["Disable fade-in during start-up##sgse"].plurals[0] = "Wyłącz fade-in interfejsu podczas uruchamiania";
    strings["About screen party time##sgse"].plurals[0] = "Impreza na ekranie \"O programie\"";
    strings["Warning: may cause epileptic seizures.##sgse"].plurals[0] = "Uwaga: może wywoływać ataki padaczki.";
    strings["Behavior##sgse"].plurals[0] = "Zachowanie programu";
    strings["New instruments are blank##sgse"].plurals[0] = "Nowe instrumnty są wyzerowane";
    strings["Language##sgse"].plurals[0] = "Język";
    strings["GUI language##sgse"].plurals[0] = "Język GUI";
    strings["Translate channel names in pattern header##sgse"].plurals[0] = "Tłumacz nazwy kanałów w nagłówku wzorca";
    strings["Translate channel names in channel oscilloscope label##sgse"].plurals[0] = "Tłumacz nazwy kanałów na oscyloskopie";
    strings["Translate short channel names (in orders and other places)##sgse"].plurals[0] = "Tłumacz nazwy kanałów (w matrycy wzorców i innych miejscach)";
    strings["Audio##sgse"].plurals[0] = "Audio";
    strings["Output##sgse"].plurals[0] = "Wyjście";
    strings["Backend##sgse"].plurals[0] = "Interfejs";
    strings["Driver##sgse"].plurals[0] = "Sterownik";
    strings["Automatic##sgse2"].plurals[0] = "Automatyczny";
    strings["you may need to restart Furnace for this setting to take effect.##sgse2"].plurals[0] = "może być konieczne ponowne uruchomienie Furnace, aby ta opcja została zastosowana.";
    strings["Device##sgse"].plurals[0] = "Urządzenie wyjściowe";
    strings["<click on OK or Apply first>##sgse"].plurals[0] = "<najpierw kliknij \"OK\" albo \"Zastosuj\">";
    strings["ALERT - TRESPASSER DETECTED##sgse"].plurals[0] = "UWAGA - WYKRYTO INTRUZA";
    strings["you have been arrested for trying to engage with a disabled combo box.##sgse"].plurals[0] = "zostałeś aresztowany za próbę interakcji z wyłączoną listą rozwijaną.";
    strings["<System default>##sgse0"].plurals[0] = "<Domyślny>";
    strings["<System default>##sgse1"].plurals[0] = "<Domyślny>";
    strings["Sample rate##sgse"].plurals[0] = "Częstotliwość samplowania";
    strings["Outputs##sgse"].plurals[0] = "Wyjścia";
    strings["Channels##sgse"].plurals[0] = "Ilość kanałów";
    strings["What?##sgse3"].plurals[0] = "Co?";
    strings["Buffer size##sgse"].plurals[0] = "Rozmiar bufora";
    strings["%d (latency: ~%.1fms)##sgse"].plurals[0] = "%d (latencja: ~%.1f ms)";
    strings["Multi-threaded (EXPERIMENTAL)##sgse"].plurals[0] = "Wielowątkowość (EKSPERYMENTALNA)";
    strings["runs chip emulation on separate threads.\nmay increase performance when using heavy emulation cores.\n\nwarnings:\n- experimental!\n- only useful on multi-chip songs.##sgse"].plurals[0] = "wykonuje emulatory układów w oddzielnych wątkach.\nmoże poprawić wydajność podczas korzystania z ciężkich emulatorów.\n\nostrzeżenie:\n- funkcja eksperymentalna!\n- użyteczna tylko dla utworów, które wykorzystują wiele układów.";
    strings["Number of threads##sgse"].plurals[0] = "Ilość wątków";
    strings["that's the limit!##sgse"].plurals[0] = "to już limit!";
    strings["it is a VERY bad idea to set this number higher than your CPU core count (%d)!##sgse"].plurals[0] = "BARDZO złym pomysłem jest ustawianie tej wartości na wyższą niż liczba rdzeni procesora. (%d)!";
    strings["Low-latency mode##sgse"].plurals[0] = "Tryb niskiej latencji";
    strings["reduces latency by running the engine faster than the tick rate.\nuseful for live playback/jam mode.\n\nwarning: only enable if your buffer size is small (10ms or less).##sgse"].plurals[0] = "zmniejsza latencję, wykonując kod silnika trackera szybciej niż określono w ustawieniach. \nprzydatne w trybie wykonywania w czasie rzeczywistym.\n\n uwaga: włącz tylko wtedy, gdy rozmiar bufora audio jest mały (10 ms lub mniej).";
    strings["Force mono audio##sgse"].plurals[0] = "Wymuś dźwięk mono";
    strings["Exclusive mode##sgse"].plurals[0] = "Tryb wyjątkowy";
    strings["want: %d samples @ %.0fHz (%d %s)##sgse"].plurals[0] = "potrzeba: %d sampli @ %.0f Hz (%d %s)";
    strings["channel##sgse"].plurals[0] = "kanał";
    strings["channel##sgse"].plurals[1] = "kanały";
    strings["channel##sgse"].plurals[2] = "kanałów";
    strings["got: %d samples @ %.0fHz (%d %s)##sgse"].plurals[0] = "otrzymano: %d sampli @ %.0f Hz (%d %s)";
    strings["Mixing##sgse"].plurals[0] = "Miksing";
    strings["Quality##sgse"].plurals[0] = "Jakość";
    strings["Software clipping##sgse"].plurals[0] = "Programowe ograniczenie sygnału";
    strings["DC offset correction##sgse"].plurals[0] = "Korekta przesunięcia DC";
    strings["Metronome##sgse"].plurals[0] = "Metronom";
    strings["Volume##sgse2"].plurals[0] = "Głośność metronomu";
    strings["Sample preview##sgse"].plurals[0] = "Podgląd sampla";
    strings["Volume##sgse3"].plurals[0] = "Głośność";
    strings["MIDI##sgse"].plurals[0] = "MIDI";
    strings["MIDI input##sgse0"].plurals[0] = "Wyjście MIDI";
    strings["MIDI input##sgse1"].plurals[0] = "Wyjście MIDI";
    strings["<disabled>##sgse0"].plurals[0] = "<wył.>";
    strings["<disabled>##sgse1"].plurals[0] = "<wył.>";
    strings["Re-scan MIDI devices##sgse"].plurals[0] = "Skanuj urządzenia MIDI ponownie";
    strings["Note input##sgse0"].plurals[0] = "Wprowadzanie nut";
    strings["Velocity input##sgse"].plurals[0] = "Wprowadzanie prędkości";
    strings["Map MIDI channels to direct channels##sgse"].plurals[0] = "Przypisz kanały MIDI do bezpośrednich kanałów";
    strings["Program change pass-through##sgse"].plurals[0] = "Przekazywanie komunikatów o zmianie programu do wyjścia";
    strings["Map Yamaha FM voice data to instruments##sgse"].plurals[0] = "Przypisz dane głosu FM do instrumentu";
    strings["Program change is instrument selection##sgse"].plurals[0] = "Zmiana programu to wyubór instrumentu";
    strings["Listen to MIDI clock##sgse"].plurals[0] = "Monitoruj częst. zegara MIDI";
    strings["Listen to MIDI time code##sgse"].plurals[0] = "Monitoruj kod czasowy MIDI";
    strings["Value input style##sgse0"].plurals[0] = "Styl wprowadzania wartości";
    strings["Value input style##sgse1"].plurals[0] = "Styl wprowadzania wartości";
    strings["Control##valueCCS"].plurals[0] = "Sterowanie##valueCCS";
    strings["CC of upper nibble##valueCC1"].plurals[0] = "CC wyższego półbajta##valueCC1";
    strings["MSB CC##valueCC1"].plurals[0] = "MSB CC##valueCC1";
    strings["CC of lower nibble##valueCC2"].plurals[0] = "CC niższego półbajta##valueCC2";
    strings["LSB CC##valueCC2"].plurals[0] = "LSB CC##valueCC2";
    strings["Per-column control change##sgse"].plurals[0] = "Zmiana sterowania dla każdej kolumny";
    strings["Control##valueCCS"].plurals[0] = "Sterowanie##valueCCS";
    strings["CC of upper nibble##valueCC1"].plurals[0] = "CC wyższego półbajta##valueCC1";
    strings["MSB CC##valueCC1"].plurals[0] = "MSB CC##valueCC1";
    strings["CC of lower nibble##valueCC2"].plurals[0] = "CC niższego półbajta##valueCC2";
    strings["LSB CC##valueCC2"].plurals[0] = "LSB CC##valueCC2";
    strings["Volume curve##sgse0"].plurals[0] = "Krzywa głośności";
    strings["Volume curve##sgse1"].plurals[0] = "Krzywa głośności";
    strings["Actions:##sgse"].plurals[0] = "Działania:";
    strings["(learning! press a button or move a slider/knob/something on your device.)##sgse"].plurals[0] = "(nasłuchiwanie! naciśnij przycisk lub przesuń coś na urządzeniu.)";
    strings["Type##sgse0"].plurals[0] = "Typ";
    strings["Channel##sgse0"].plurals[0] = "Kanał";
    strings["Note/Control##sgse"].plurals[0] = "Nuta/sterowanie";
    strings["Velocity/Value##sgse"].plurals[0] = "Szybkość/Parametr";
    strings["Action##sgse"].plurals[0] = "Działania";
    strings["Any##sgse0"].plurals[0] = "Każdy";
    strings["Any##sgse1"].plurals[0] = "Każdy";
    strings["Any##sgse2"].plurals[0] = "Każdy";
    strings["Any##sgse3"].plurals[0] = "Każdy";
    strings["--none--##sgse"].plurals[0] = "--żaden--";
    strings["waiting...##BLearn"].plurals[0] = "czekaj...##BLearn";
    strings["Learn##BLearn"].plurals[0] = "Pamięć MIDI##BLearn";
    strings["MIDI output##sgse0"].plurals[0] = "Wyjście MIDI";
    strings["MIDI output##sgse1"].plurals[0] = "Urządzenie wyjścia MIDI";
    strings["<disabled>##sgse2"].plurals[0] = "<wył.>";
    strings["<disabled>##sgse3"].plurals[0] = "<wył.>";
    strings["Output mode:##sgse"].plurals[0] = "Tryb wyjścia:";
    strings["Off (use for TX81Z)##sgse"].plurals[0] = "Wył. (używać przy TX81Z)";
    strings["Melodic##sgse"].plurals[0] = "Melodyczny";
    //strings["Light Show (use for Launchpad)##sgse"].plurals[0] = "Light Show (use for Launchpad)";
    strings["Send Program Change##sgse"].plurals[0] = "Wyślij komendę zmiany programu";
    strings["Send MIDI clock##sgse"].plurals[0] = "Wyślij częstotliwość zegara MIDI";
    strings["Send MIDI timecode##sgse"].plurals[0] = "Wyślij kod czasowy MIDI";
    strings["Timecode frame rate:##sgse"].plurals[0] = "Framerate kodu czasowego:";
    strings["Closest to Tick Rate##sgse"].plurals[0] = "Najbliższy częstotliwości silnika trackera";
    strings["Film (24fps)##sgse"].plurals[0] = "Filmowy (24 fps)";
    strings["PAL (25fps)##sgse"].plurals[0] = "PAL (25 fps)";
    strings["NTSC drop (29.97fps)##sgse"].plurals[0] = "Niestabilne NTSC (29.97 fps";
    strings["NTSC non-drop (30fps)##sgse"].plurals[0] = "Stabilne NTSC (30 fps)";
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
    strings["Keyboard##sgse0"].plurals[0] = "Klawiatura";
    strings["Keyboard##sgse1"].plurals[0] = "Przypisania klawiszy";
    strings["Import##sgse0"].plurals[0] = "Importij";
    strings["Export##sgse0"].plurals[0] = "Eksportuj";
    strings["Reset defaults##sgse0"].plurals[0] = "Resetuj do wart. domyślnych";
    strings["Are you sure you want to reset the keyboard settings?##sgse"].plurals[0] = "Czy jesteś pewien że chcesz zresetować ustawienia klawiszy?";
    strings["Global hotkeys##sgse"].plurals[0] = "Globalne skróty klawiszowe";
    strings["Window activation##sgse"].plurals[0] = "Aktywacja okien";
    strings["Note input##sgse1"].plurals[0] = "Wprowadzanie nut";
    strings["Key##sgse"].plurals[0] = "Klawisz";
    strings["Type##sgse1"].plurals[0] = "Typ";
    strings["Value##sgse"].plurals[0] = "Wartość";
    strings["Remove##sgse"].plurals[0] = "Usuń";
    strings["Macro release##SNType_%d"].plurals[0] = "Puszczenie klawisza (tylko makra)##SNType_%d";
    strings["Note release##SNType_%d"].plurals[0] = "Puszczenie klawisza z zanikaniem obwiedni##SNType_%d";
    strings["Note off##SNType_%d"].plurals[0] = "Puszczenie klawisza##SNType_%d";
    strings["Note##SNType_%d"].plurals[0] = "Nuta##SNType_%d";
    strings["Add...##sgse"].plurals[0] = "Dodaj...";
    strings["Pattern##sgse0"].plurals[0] = "Wzorzec";
    strings["Instrument list##sgse"].plurals[0] = "Lista instrumentów";
    strings["Wavetable list##sgse"].plurals[0] = "Lista tablic fal";
    strings["Local wavetables list##sgse"].plurals[0] = "Lista lokalnych tablic fal";
    strings["Sample list##sgse"].plurals[0] = "Lista sampli";
    strings["Orders##sgse0"].plurals[0] = "Matryca wzorców";
    strings["Sample editor##sgse"].plurals[0] = "Edytor sampli";
    strings["Interface##sgse0"].plurals[0] = "Interfejs";
    strings["Layout##sgse"].plurals[0] = "Rozmieszczenie";
    strings["Workspace layout:##sgse"].plurals[0] = "Układ okien interfejsu:";
    strings["Import##sgse1"].plurals[0] = "Importuj";
    strings["Export##sgse1"].plurals[0] = "Eksportuj";
    strings["Reset##sgse"].plurals[0] = "Resetuj";
    strings["Are you sure you want to reset the workspace layout?##sgse"].plurals[0] = "Czy jesteś pewien że chcesz zresetować układ przestrzeni roboczej?";
    strings["Allow docking editors##sgse"].plurals[0] = "Pozwalaj na dokowanie edytorów";
    strings["Remember window position##sgse"].plurals[0] = "Pamiętaj położenie okien";
    strings["remembers the window's last position on start-up.##sgse"].plurals[0] = "przywraca ostatnią pozycję każdego okna po uruchomieniu programu.";
    strings["Only allow window movement when clicking on title bar##sgse"].plurals[0] = "Zezwalaj na przesuwanie okien tylko po kliknięciu ich paska tytułu.";
    strings["Center pop-up windows##sgse"].plurals[0] = "Centruj wyskakujące okna";
    strings["Play/edit controls layout:##sgse"].plurals[0] = "Układ kontrolek odtwarzania/edycji:";
    strings["Classic##ecl0"].plurals[0] = "Klasyczny##ecl0";
    strings["Compact##ecl1"].plurals[0] = "Kompatowy##ecl1";
    strings["Compact (vertical)##ecl2"].plurals[0] = "Kompaktowy (pionowy)##ecl2";
    strings["Split##ecl3"].plurals[0] = "Podzielony na dwa okna##ecl3";
    strings["Position of buttons in Orders:##sgse"].plurals[0] = "Pozycja przycisków w matrycy wzorców:";
    strings["Top##obp0"].plurals[0] = "Na górze##obp0";
    strings["Left##obp1"].plurals[0] = "Z lewej##obp1";
    strings["Right##obp2"].plurals[0] = "Z prawej##obp2";
    strings["Mouse##sgse"].plurals[0] = "Mysz";
    strings["Double-click time (seconds)##sgse"].plurals[0] = "Czas dwukrotnego kliknięcia myszą (w sekundach)";
    strings["Don't raise pattern editor on click##sgse"].plurals[0] = "Nie wywołuj edytora wzorców po naciśnięciu przycisku";
    strings["Focus pattern editor when selecting instrument##sgse"].plurals[0] = "UStaw skupienie na edyorze wzorców podczas wyboru instrumentu";
    strings["Note preview behavior:##sgse"].plurals[0] = "Ustawienia podglądu nut:";
    strings["Never##npb0"].plurals[0] = "Nigdy##npb0";
    strings["When cursor is in Note column##npb1"].plurals[0] = "Gdy kursor znajduje się w kolumnie nuty##npb1";
    strings["When cursor is in Note column or not in edit mode##npb2"].plurals[0] = "Gdy kursor znajduje się w kolumnie nut lub tryb edycji nie jest włączony##npb2";
    strings["Always##npb3"].plurals[0] = "Zawsze##npb3";
    strings["Allow dragging selection:##sgse"].plurals[0] = "Zezwól na przeniesienie zaznaczenia:";
    strings["No##dms0"].plurals[0] = "Nie##dms0";
    strings["Yes##dms1"].plurals[0] = "Tak##dms1";
    strings["Yes (while holding Ctrl only)##dms2"].plurals[0] = "Tak (tylko przy wciśniętym klawiuszu Ctrl)##dms2";
    strings["Toggle channel solo on:##sgse"].plurals[0] = "Włącz tryb solo dla kanału:";
    strings["Right-click or double-click##soloA"].plurals[0] = "PPM alko podwójne kliknięcie##soloA";
    strings["Right-click##soloR"].plurals[0] = "PPM##soloR";
    strings["Double-click##soloD"].plurals[0] = "Podwójne kliknięcie##soloD";
    strings["Double click selects entire column##sgse"].plurals[0] = "Podwójne kliknięcie wybiera całą kolumnę";
    strings["Cursor behavior##sgse"].plurals[0] = "Zachowanie kursora";
    strings["Insert pushes entire channel row##sgse"].plurals[0] = "Klawisz Insert przesuwa wiersz całego kanału";
    strings["Pull delete affects entire channel row##sgse"].plurals[0] = "Usunięcie z podciąganiem następujących linii wpływa na cały wiersz kanału";
    strings["Push value when overwriting instead of clearing it##sgse"].plurals[0] = "Przenieś wartość komórki do sąsiedniej komórki zamiast ją usuwać podczas nadpisywania";
    strings["Effect input behavior:##sgse"].plurals[0] = "Wprowadzanie efektów:";
    strings["Move down##eicb0"].plurals[0] = "Przesuń w dół##eicb0";
    strings["Move to effect value (otherwise move down)##eicb1"].plurals[0] = "Przejdź do parametru efektu (w przeciwnym razie przejdź w dół)##eicb1";
    strings["Move to effect value/next effect and wrap around##eicb2"].plurals[0] = "Przeskocz do parametru efektu/następnego efektu i przeskocz do początku linii##eicb2";
    strings["Delete effect value when deleting effect##sgse"].plurals[0] = "Usuń parametr efektu podczas usuwania efektu";
    strings["Change current instrument when changing instrument column (absorb)##sgse"].plurals[0] = "Zmień wybranego instrumentu podczas edycji kolumny instrumentu";
    strings["Remove instrument value when inserting note off/release##sgse"].plurals[0] = "Usuń wartość instrumentu podczas wstawiania nut OFF/===";
    strings["Remove volume value when inserting note off/release##sgse"].plurals[0] = "Usuń wartość głośności podczas wstawiania nut OFF/===";
    strings["Cursor movement##sgse"].plurals[0] = "Przemieszczanie kursora";
    strings["Wrap horizontally:##sgse"].plurals[0] = "Przenoszenie w poziomie:";
    strings["No##wrapH0"].plurals[0] = "Nie##wrapH0";
    strings["Yes##wrapH1"].plurals[0] = "Tak##wrapH1";
    strings["Yes, and move to next/prev row##wrapH2"].plurals[0] = "Tak, i przejdź do następnego wiersza##wrapH2";
    strings["Wrap vertically:##sgse"].plurals[0] = "Przenoszenie w pionie:";
    strings["No##wrapV0"].plurals[0] = "Nie##wrapV0";
    strings["Yes##wrapV1"].plurals[0] = "Tak##wrapV1";
    strings["Yes, and move to next/prev pattern##wrapV2"].plurals[0] = "Tak, i przejdź do następnego/poprzedniego wzorca##wrapV2";
    strings["Yes, and move to next/prev pattern (wrap around)##wrapV2"].plurals[0] = "Tak, i przejdź do następnego/poprzedniego wzorca (z przeniesieniem na początek/koniec).##wrapV2";
    strings["Cursor movement keys behavior:##sgse"].plurals[0] = "Zachowanie przesuwanie kursora:";
    strings["Move by one##cmk0"].plurals[0] = "Przesuwaj o jeden##cmk0";
    strings["Move by Edit Step##cmk1"].plurals[0] = "Przesuń o krok edycji##cmk1";
    strings["Move cursor by edit step on delete##sgse"].plurals[0] = "Przesuń kursor o krok edycji podczas usuwania";
    strings["Move cursor by edit step on insert (push)##sgse"].plurals[0] = "Przesuń kursor o krok edycji podczas wklejania";
    strings["Move cursor up on backspace-delete##sgse"].plurals[0] = "Przesuń kursor do góry po naciśnięciu Backspace";
    strings["Move cursor to end of clipboard content when pasting##sgse"].plurals[0] = "Przesuń kursor do końca wklejanej zawartości";
    strings["Scrolling##sgse"].plurals[0] = "Przewijanie";
    strings["Change order when scrolling outside of pattern bounds:##sgse"].plurals[0] = "Zmiana pozycji w matrycy wzorców podczas przewijania poza wzorcami:";
    strings["No##pscroll0"].plurals[0] = "Nie##pscroll0";
    strings["Yes##pscroll1"].plurals[0] = "Tak##pscroll1";
    strings["Yes, and wrap around song##pscroll2"].plurals[0] = "Tak, i przenieś go na początek/koniec utworu.##pscroll2";
    strings["Cursor follows current order when moving it##sgse"].plurals[0] = "Kursor podąża za wierszem matrycy wzorca, gdy ten jest przesuwany";
    strings["applies when playback is stopped.##sgse"].plurals[0] = "jest ważne tylko wtedy, gdy odtwarzanie jest zatrzymane.";
    strings["Don't scroll when moving cursor##sgse"].plurals[0] = "Nie przewijaj podczas przesuwania kursora";
    strings["Move cursor with scroll wheel:##sgse"].plurals[0] = "Przesuwaj kursor za pomocą kółka myszy:";
    strings["No##csw0"].plurals[0] = "Nie##csw0";
    strings["Yes##csw1"].plurals[0] = "Tak##csw1";
    strings["Inverted##csw2"].plurals[0] = "Tak, ale w przeciwnym kierunku##csw2";
    strings["Assets##sgse0"].plurals[0] = "Zasoby";
    strings["Display instrument type menu when adding instrument##sgse"].plurals[0] = "Wyświetlaj menu wyboru typu instrumentu podczas dodawania instrumentu";
    strings["Select asset after opening one##sgse"].plurals[0] = "Wybierz obiekt po jego otwarciu";
    strings["Appearance##sgse"].plurals[0] = "Wygląd";
    strings["Scaling##sgse"].plurals[0] = "Skalowanie";
    strings["Automatic UI scaling factor##sgse"].plurals[0] = "Automatyczny współczynnik skalowania UI";
    strings["UI scaling factor##sgse"].plurals[0] = "Współczynnik skalowania UI";
    strings["Icon size##sgse"].plurals[0] = "Rozmiar ikon";
    strings["Text##sgse"].plurals[0] = "Tekst";
    strings["Font renderer##sgse"].plurals[0] = "Renderer czcionki";
    strings["Main font##sgse"].plurals[0] = "Główna czcionka";
    strings["Size##MainFontSize"].plurals[0] = "Rozmiar##MainFontSize";
    strings["Header font##sgse"].plurals[0] = "Czcionka nagłówków";
    strings["Size##HeadFontSize"].plurals[0] = "Rozmiar##HeadFontSize";
    strings["Pattern font##sgse"].plurals[0] = "Czcionka wzorców";
    strings["Size##PatFontSize"].plurals[0] = "Rozmiar##PatFontSize";
    strings["Anti-aliased fonts##sgse"].plurals[0] = "Wygladzanie czcionek";
    strings["Support bitmap fonts##sgse"].plurals[0] = "Wspieraj bitmapowe czcionki";
    strings["Hinting:##sgse"].plurals[0] = "hINTOWANIE";
    strings["Off (soft)##fh0"].plurals[0] = "Wył. (słabe)##fh0";
    strings["Slight##fh1"].plurals[0] = "Lekkie##fh1";
    strings["Normal##fh2"].plurals[0] = "Normalne##fh2";
    strings["Full (hard)##fh3"].plurals[0] = "Pełne##fh3";
    strings["Auto-hinter:##sgse"].plurals[0] = "Autohintowanie";
    strings["Disable##fah0"].plurals[0] = "Wyłącz##fah0";
    strings["Enable##fah1"].plurals[0] = "Włącz##fah1";
    strings["Force##fah2"].plurals[0] = "Wymuś##fah2";
    strings["Display Japanese characters##sgse"].plurals[0] = "Wyświetlaj japońskie znaki";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "このオプションは、十分なグラフィックメモリがある場合にのみ切り替えてください。\n"
            "これは、Dear ImGuiにダイナミックフォントアトラスが実装されるまでの一時的な解決策です。##sgse"].plurals[0] = 
            
            "Włącz tą opcję tylko wtedy, gdy masz wystarczającą ilość VRAM-u.\n"
            "Jest to rozwiązanie tymczasowe, ponieważ Dear ImGui nie obsługuje obecnie dynamicznego atlasu czcionek.\n\n"
            "このオプションは、十分なグラフィックメモリがある場合にのみ切り替えてください。\n"
            "これは、Dear ImGuiにダイナミックフォントアトラスが実装されるまでの一時的な解決策です。";
    strings["Display Chinese (Simplified) characters##sgse"].plurals[0] = "Wyświetlaj chińskie znaki (uproszczone)";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "请在确保你有足够的显存后再启动此设定\n"
            "这是一个在ImGui实现动态字体加载之前的临时解决方案##sgse"].plurals[0] = 
            
            "Włącz tą opcję tylko wtedy, gdy masz wystarczającą ilość VRAM-u.\n"
            "Jest to rozwiązanie tymczasowe, ponieważ Dear ImGui nie obsługuje obecnie dynamicznego atlasu czcionek.\n\n"
            "请在确保你有足够的显存后再启动此设定\n"
            "这是一个在ImGui实现动态字体加载之前的临时解决方案";
    strings["Display Chinese (Traditional) characters##sgse"].plurals[0] = "Wyświetlaj chińskie znaki (tradycyjne)";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "請在確保你有足夠的顯存后再啟動此設定\n"
            "這是一個在ImGui實現動態字體加載之前的臨時解決方案##sgse"].plurals[0] = 
            
            "Włącz tą opcję tylko wtedy, gdy masz wystarczającą ilość VRAM-u.\n"
            "Jest to rozwiązanie tymczasowe, ponieważ Dear ImGui nie obsługuje obecnie dynamicznego atlasu czcionek.\n\n"
            "請在確保你有足夠的顯存后再啟動此設定\n"
            "這是一個在ImGui實現動態字體加載之前的臨時解決方案";
    strings["Display Korean characters##sgse"].plurals[0] = "Wyświetlaj koreańskie znaki";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "그래픽 메모리가 충분한 경우에만 이 옵션을 선택하십시오.\n"
            "이 옵션은 Dear ImGui에 동적 글꼴 아틀라스가 구현될 때까지 임시 솔루션입니다.##sgse"].plurals[0] = 
            
            "Włącz tą opcję tylko wtedy, gdy masz wystarczającą ilość VRAM-u.\n"
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
    strings["Display chip names instead of \"multi-system\" in title bar##sgse"].plurals[0] = "Wyświetlaj nazwy układów/systemów zamiast \"multi-system\" na pasku tytułu okna";
    strings["Status bar:##sgse"].plurals[0] = "Pasek stanu:";
    strings["Cursor details##sbar0"].plurals[0] = "Informacje o wybranym elemencie##sbar0";
    strings["File path##sbar1"].plurals[0] = "Ścieżka do pliku##sbar1";
    strings["Cursor details or file path##sbar2"].plurals[0] = "Informacje o wybranym elemencie czy ścieżce pliku##sbar2";
    strings["Nothing##sbar3"].plurals[0] = "Brak##sbar3";
    strings["Display playback status when playing##sgse"].plurals[0] = "Wyświetlanie stanu odtwarzania podczas odtwarzania";
    strings["Export options layout:##sgse"].plurals[0] = "Układ opcji eksportu:";
    strings["Sub-menus in File menu##eol0"].plurals[0] = "Menu podrzędne w menu \"Plik\"##eol0";
    strings["Modal window with tabs##eol1"].plurals[0] = "Modalne okno z zakładkami##eol1";
    strings["Modal windows with options in File menu##eol2"].plurals[0] = "Okno modalne z ustawieniami w menu \"Plik\"";
    strings["Capitalize menu bar##sgse"].plurals[0] = "Pozycje paska menu zaczynają się od wielkiej litery";
    strings["Display add/configure/change/remove chip menus in File menu##sgse"].plurals[0] = "Wyświetlanie pozycji: Dodaj/Zmień/Usuń Chip w menu \"Plik\".";
    strings["Orders##sgse1"].plurals[0] = "Matryca wzorców";
    strings["Highlight channel at cursor in Orders##sgse"].plurals[0] = "Podświetl kanał, na którym znajduje się kursor w matrycy wzorców.";
    strings["Orders row number format:##sgse"].plurals[0] = "Format wyświetlania numeru wiersza matrycy wzorców:";
    strings["Decimal##orbD"].plurals[0] = "Dziesiętny##orbD";
    strings["Hexadecimal##orbH"].plurals[0] = "Szesnastkowy##orbH";
    strings["Pattern##sgse1"].plurals[0] = "Wzorzec";
    strings["Center pattern view##sgse"].plurals[0] = "Wyśrodkuj wyświetlane wzorce w oknie";
    strings["Overflow pattern highlights##sgse"].plurals[0] = "Kontynuuj podświetlenie pasków wzorza poza samymi wzorcami";
    strings["Display previous/next pattern##sgse"].plurals[0] = "Wyświetlaj porzedni/następny wozrzec";
    strings["Pattern row number format:##sgse"].plurals[0] = "Format wyświetlania numeru wiersza wzorca:";
    strings["Decimal##prbD"].plurals[0] = "Dziesiętny##prbD";
    strings["Hexadecimal##prbH"].plurals[0] = "Szesnastkowy##prbH";
    strings["Pattern view labels:##sgse"].plurals[0] = "Etykiety komórek wzorca:";
    strings["Note off (3-char)##sgse"].plurals[0] = "Puszczenie klawisza (3 znaki)";
    strings["Note release (3-char)##sgse"].plurals[0] = "Zwolnienie nuty (3 znaki)";
    strings["Macro release (3-char)##sgse"].plurals[0] = "Zwolnienie makra (3 znaki)";
    strings["Empty field (3-char)##sgse"].plurals[0] = "Pusta komórka (3 znaki)";
    strings["Empty field (2-char)##sgse"].plurals[0] = "Pusta komórka (2 znaki)";
    strings["Pattern view spacing after:##sgse"].plurals[0] = "Podział na widoku wzorca po:";
    strings["Note##sgse"].plurals[0] = "Nuta";
    strings["Instrument##sgse1"].plurals[0] = "Instrument";
    strings["Volume##sgse4"].plurals[0] = "Głośność";
    strings["Effect##sgse"].plurals[0] = "Indeks efektu";
    strings["Effect value##sgse"].plurals[0] = "Parametr efektu";
    strings["Single-digit effects for 00-0F##sgse"].plurals[0] = "Jednocyfrowe parametry efektów 00-0F";
    strings["Use flats instead of sharps##sgse"].plurals[0] = "Używaj bemoli zamiast krzyżyków";
    strings["Use German notation##sgse"].plurals[0] = "Używaj niemieckich nazw nut";
    strings["Channel##sgse1"].plurals[0] = "Kanał";
    strings["Channel style:##sgse"].plurals[0] = "Styl nagłówka kanału:";
    strings["Classic##CHS0"].plurals[0] = "Klasyczny##CHS0";
    strings["Line##CHS1"].plurals[0] = "Linia##CHS1";
    strings["Round##CHS2"].plurals[0] = "Zaokrąglony##CHS2";
    strings["Split button##CHS3"].plurals[0] = "Oddzielny przycik wyciszenia##CHS3";
    strings["Square border##CHS4"].plurals[0] = "Prostokątne krawędzie##CHS4";
    strings["Round border##CHS5"].plurals[0] = "Zaokrąglone krawędzie##CHS5";
    strings["Channel volume bar:##sgse"].plurals[0] = "Pasek głośności kanału:";
    strings["Non##CHV0"].plurals[0] = "Brak##CHV0";
    strings["Simple##CHV1"].plurals[0] = "Prosty##CHV1";
    strings["Stereo##CHV2"].plurals[0] = "Stereo##CHV2";
    strings["Real##CHV3"].plurals[0] = "Rzeczywisty##CHV3";
    strings["Real (stereo)##CHV4"].plurals[0] = "Rzeczywisty (stereo)##CHV4";
    strings["Channel feedback style:##sgse"].plurals[0] = "Tryb podświetlenia nagłowka kanału";
    strings["Off##CHF0"].plurals[0] = "Wył.##CHF0";
    strings["Note##CHF1"].plurals[0] = "Nuta##CHF1";
    strings["Volume##CHF2"].plurals[0] = "Głośność##CHF2";
    strings["Active##CHF3"].plurals[0] = "Przy aktywnym kanale##CHF3";
    strings["Channel font:##sgse"].plurals[0] = "Czcionka nagłówka kanału:";
    strings["Regular##CHFont0"].plurals[0] = "Zwykła#CHFont0";
    strings["Monospace##CHFont1"].plurals[0] = "Monospace##CHFont1";
    strings["Center channel name##sgse"].plurals[0] = "Wyśrodkuj nazwę kanału";
    strings["Channel colors:##sgse"].plurals[0] = "Kolory nagłówków kanałów";
    strings["Single##CHC0"].plurals[0] = "Jednolite##CHC0";
    strings["Channel type##CHC1"].plurals[0] = "Zgodne z typem kanału##CHC1";
    strings["Instrument type##CHC2"].plurals[0] = "Zgodne z typem instrumentu##CHC2";
    strings["Channel name colors:##sgse"].plurals[0] = "Kolory nazwy kanału:";
    strings["Single##CTC0"].plurals[0] = "Jednolite##CTC0";
    strings["Channel type##CTC1"].plurals[0] = "Zgodnie z typem kanału##CTC1";
    strings["Instrument type##CTC2"].plurals[0] = "Zgodnie z typem instrumentu##CTC2";
    strings["Assets##sgse1"].plurals[0] = "Prezentacja zasobów modułu";
    strings["Unified instrument/wavetable/sample list##sgse"].plurals[0] = "Połączona lista instrumentów, tablic fal i sampli";
    strings["Horizontal instrument list##sgse"].plurals[0] = "Pozioma lista instrumentów";
    strings["Instrument list icon style:##sgse"].plurals[0] = "Styl ikon listy instrumentów:";
    strings["None##iis0"].plurals[0] = "Nie pokazuj##iis0";
    strings["Graphical icons##iis1"].plurals[0] = "Graficzne ikonki##iis1";
    strings["Letter icons##iis2"].plurals[0] = "Ikony liter##iis2";
    strings["Colorize instrument editor using instrument type##sgse"].plurals[0] = "Zmień kolory edytora instrumentów zgodnie z typem instrumentu";
    strings["Macro Editor##sgse0"].plurals[0] = "Edytor makr";
    strings["Macro editor layout:##sgse"].plurals[0] = "Układ edytora makr:";
    strings["Unified##mel0"].plurals[0] = "Połączony##mel0";
    strings["Grid##mel2"].plurals[0] = "Siatka##mel2";
    strings["Single (with list)##mel3"].plurals[0] = "Pojedyncze okno (z listą)##mel3";
    strings["Use classic macro editor vertical slider##sgse"].plurals[0] = "Użyj klasycznego pionowego paska przewijania";
    strings["Wave Editor##sgse"].plurals[0] = "Edytor fal";
    strings["Use compact wave editor##sgse"].plurals[0] = "Używaj zwartego edyora fal";
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
    strings["Position of Sustain in FM editor:##sgse"].plurals[0] = "Pozycja parametru \"Podtrzymanie\" w edytorze:";
    strings["Between Decay and Sustain Rate##susp0"].plurals[0] = "Między parametrami opadania i zwolnienia##susp0";
    strings["After Release Rate##susp1"].plurals[0] = "Po parametrze zwolnienia##susp1";
    strings["Use separate colors for carriers/modulators in FM editor##sgse"].plurals[0] = "Używaj odmiennych kolorów dla fali nośnych/modulatorów w edytorze FM";
    strings["Unsigned FM detune values##sgse"].plurals[0] = "Bezznakowe wartości rozstrojenia FM";
    strings["Statistics##sgse"].plurals[0] = "Okno statystyk";
    strings["Chip memory usage unit:##sgse"].plurals[0] = "Jednostki wyświatlania obciążenia pamięci układu:";
    strings["Bytes##MUU0"].plurals[0] = "Bajty##MUU0";
    strings["Kilobytes##MUU1"].plurals[0] = "Kilobajty##MUU1";
    strings["Oscilloscope##set"].plurals[0] = "Oscyloskop##set";
    strings["Rounded corners##sgse"].plurals[0] = "Zaokrąglone rogi";
    strings["Border##sgse"].plurals[0] = "Krawędź";
    strings["Mono##sgse1"].plurals[0] = "Nono";
    strings["Anti-aliased##sgse"].plurals[0] = "Z wygładzaniem";
    strings["Fill entire window##sgse"].plurals[0] = "Wypełń całe okno";
    strings["Waveform goes out of bounds##sgse"].plurals[0] = "Fala wychodzi poza okno";
    strings["Line size##sgse"].plurals[0] = "Grubość linii";
    strings["Windows##sgse"].plurals[0] = "Okna";
    strings["Rounded window corners##sgse"].plurals[0] = "Zaokrąglone krawędzie okien";
    strings["Rounded buttons##sgse"].plurals[0] = "Zaokrąglone przyciski";
    strings["Rounded tabs##sgse"].plurals[0] = "Zaokrąglone krawędzie zakładek";
    strings["Rounded scrollbars##sgse"].plurals[0] = "Zaokrąglone paski przewijania";
    strings["Rounded menu corners##sgse"].plurals[0] = "Zaokrąglone krawędzie menu";
    strings["Borders around widgets##sgse"].plurals[0] = "Obrawowania wokół widżetów";
    strings["Misc##sgse"].plurals[0] = "Inne";
    strings["Wrap text##sgse"].plurals[0] = "Zawijaj wiersze";
    strings["Wrap text in song/subsong comments window.##sgse"].plurals[0] = "Zawijaj wiersz w oknach komentarzy do utworu/podutworu";
    strings["Frame shading in text windows##sgse"].plurals[0] = "Cieniowanie ramek w oknach tekstowych";
    strings["Apply frame shading to the multiline text fields\nsuch as song/subsong info/comments.##sgse"].plurals[0] = "Zastosuj gradient w oknie informacji o utworze/komentarzach.";
    strings["Show chip info in chip manager##sgse"].plurals[0] = "Pokazuj informacje o układzie w menedżerze ukłądów";
    strings["Display tooltip in chip manager when hovering over the chip. Tooltip shows chip name and description.##sgse"].plurals[0] = "Wyświetla podpowiedź po najechaniu kursorem na układ. Podpowiedź wyświetla nazwę i opis układu.";
    strings["Color##sgse"].plurals[0] = "Kolor";
    strings["Color scheme##sgse"].plurals[0] = "Schemat kolorów";
    strings["Import##sgse2"].plurals[0] = "Importuj";
    strings["Export##sgse2"].plurals[0] = "Eksportuj";
    strings["Reset defaults##sgse1"].plurals[0] = "Domyślne";
    strings["Are you sure you want to reset the color scheme?##sgse"].plurals[0] = "Czy jesteś pewien że chcesz zresetować schemat kolorów?";
    strings["Interface##sgse1"].plurals[0] = "Interfejs";
    strings["Frame shading##sgse"].plurals[0] = "Cieniowanie ramki";
    strings["Interface (other)##sgse"].plurals[0] = "Interfejs (inne)";
    strings["Miscellaneous##sgse"].plurals[0] = "Inne";
    strings["File Picker (built-in)##sgse"].plurals[0] = "Wbudowany wybierak plików";
    strings["Oscilloscope##sgse"].plurals[0] = "Oscyloskop";
    strings["Wave (non-mono)##sgse"].plurals[0] = "Fala (nie mono)";
    strings["Volume Meter##sgse"].plurals[0] = "Miernik glośśności";
    strings["Orders##sgse2"].plurals[0] = "Matryca wzorców";
    strings["Envelope View##sgse"].plurals[0] = "Podglad obwiedni";
    strings["FM Editor##sgse1"].plurals[0] = "Edytor instrumentow FM";
    strings["Macro Editor##sgse1"].plurals[0] = "Edytor makr";
    strings["Instrument Types##sgse"].plurals[0] = "Typy instrumentów";
    strings["Channel##sgse2"].plurals[0] = "Kanal";
    strings["Pattern##sgse2"].plurals[0] = "Wzorzec";
    strings["Sample Editor##sgse"].plurals[0] = "Edytor sampli";
    strings["Pattern Manager##sgse"].plurals[0] = "Menedżer wzorców";
    strings["Piano##sgse"].plurals[0] = "Klawiatura pianina";
    strings["Clock##sgse"].plurals[0] = "Zegar";
    strings["Patchbay##sgse"].plurals[0] = "Połączenie kanałów";
    strings["Log Viewer##sgse"].plurals[0] = "Podgląd logów";

    // these are messy, but the ##CC_GUI... is required.
    strings["Button##CC_GUI_COLOR_BUTTON"].plurals[0] = "Przycisk##CC_GUI_COLOR_BUTTON";
    strings["Button (hovered)##CC_GUI_COLOR_BUTTON_HOVER"].plurals[0] = "Przycisk (zazn. kursorem)##CC_GUI_COLOR_BUTTON_HOVER";
    strings["Button (active)##CC_GUI_COLOR_BUTTON_ACTIVE"].plurals[0] = "Przycisk (aktywny)##CC_GUI_COLOR_BUTTON_ACTIVE";
    strings["Tab##CC_GUI_COLOR_TAB"].plurals[0] = "Zakładka##CC_GUI_COLOR_TAB";
    strings["Tab (hovered)##CC_GUI_COLOR_TAB_HOVER"].plurals[0] = "Zakładka (zazn. kursorem)##CC_GUI_COLOR_TAB_HOVER";
    strings["Tab (active)##CC_GUI_COLOR_TAB_ACTIVE"].plurals[0] = "Zakładka (aktywna)##CC_GUI_COLOR_TAB_ACTIVE";
    strings["Tab (unfocused)##CC_GUI_COLOR_TAB_UNFOCUSED"].plurals[0] = "Zakładka (nieskupiona)##CC_GUI_COLOR_TAB_UNFOCUSED";
    strings["Tab (unfocused and active)##CC_GUI_COLOR_TAB_UNFOCUSED_ACTIVE"].plurals[0] = "Zakładka (nieskupiona, aktywna)##CC_GUI_COLOR_TAB_UNFOCUSED_ACTIVE";
    strings["ImGui header##CC_GUI_COLOR_IMGUI_HEADER"].plurals[0] = "Nagłówek ImGui##CC_GUI_COLOR_IMGUI_HEADER";
    strings["ImGui header (hovered)##CC_GUI_COLOR_IMGUI_HEADER_HOVER"].plurals[0] = "Nagłówek ImGui (zazn. kursorem)##CC_GUI_COLOR_IMGUI_HEADER_HOVER";
    strings["ImGui header (active)##CC_GUI_COLOR_IMGUI_HEADER_ACTIVE"].plurals[0] = "Nagłówek ImGui (aktywny)##CC_GUI_COLOR_IMGUI_HEADER_ACTIVE";
    strings["Resize grip##CC_GUI_COLOR_RESIZE_GRIP"].plurals[0] = "Uchwyt zmiany rozmiaru##CC_GUI_COLOR_RESIZE_GRIP";
    strings["Resize grip (hovered)##CC_GUI_COLOR_RESIZE_GRIP_HOVER"].plurals[0] = "Uchwyt zmiany rozmiaru (zazn. kursorem)##CC_GUI_COLOR_RESIZE_GRIP_HOVER";
    strings["Resize grip (active)##CC_GUI_COLOR_RESIZE_GRIP_ACTIVE"].plurals[0] = "Uchwyt zmiany rozmiaru (aktywny)##CC_GUI_COLOR_RESIZE_GRIP_ACTIVE";
    strings["Widget background##CC_GUI_COLOR_WIDGET_BACKGROUND"].plurals[0] = "Tło widżetu##CC_GUI_COLOR_WIDGET_BACKGROUND";
    strings["Widget background (hovered)##CC_GUI_COLOR_WIDGET_BACKGROUND_HOVER"].plurals[0] = "Tło widżetu (zazn. kursorem)##CC_GUI_COLOR_WIDGET_BACKGROUND_HOVER";
    strings["Widget background (active)##CC_GUI_COLOR_WIDGET_BACKGROUND_ACTIVE"].plurals[0] = "Tło widżetu (aktywne)##CC_GUI_COLOR_WIDGET_BACKGROUND_ACTIVE";
    strings["Slider grab##CC_GUI_COLOR_SLIDER_GRAB"].plurals[0] = "Chwyt paska przewijania##CC_GUI_COLOR_SLIDER_GRAB";
    strings["Slider grab (active)##CC_GUI_COLOR_SLIDER_GRAB_ACTIVE"].plurals[0] = "Chwyt paska przewijania (aktywny)##CC_GUI_COLOR_SLIDER_GRAB_ACTIVE";
    strings["Title background (active)##CC_GUI_COLOR_TITLE_BACKGROUND_ACTIVE"].plurals[0] = "Tło paska tytułowego (aktywne)##CC_GUI_COLOR_TITLE_BACKGROUND_ACTIVE";
    strings["Checkbox/radio button mark##CC_GUI_COLOR_CHECK_MARK"].plurals[0] = "Oznaczenie pola wyboru i przycisku opcji##CC_GUI_COLOR_CHECK_MARK";
    strings["Text selection##CC_GUI_COLOR_TEXT_SELECTION"].plurals[0] = "Zaznaczenie tekstu##CC_GUI_COLOR_TEXT_SELECTION";
    strings["Line plot##CC_GUI_COLOR_PLOT_LINES"].plurals[0] = "Wykres liniowy##CC_GUI_COLOR_PLOT_LINES";
    strings["Line plot (hovered)##CC_GUI_COLOR_PLOT_LINES_HOVER"].plurals[0] = "Wykres liniowy (zaznaczony)##CC_GUI_COLOR_PLOT_LINES_HOVER";
    strings["Histogram plot##CC_GUI_COLOR_PLOT_HISTOGRAM"].plurals[0] = "Wykres słupkowy##CC_GUI_COLOR_PLOT_HISTOGRAM";
    strings["Histogram plot (hovered)##CC_GUI_COLOR_PLOT_HISTOGRAM_HOVER"].plurals[0] = "Wykres słupkowy (zaznaczony)##CC_GUI_COLOR_PLOT_HISTOGRAM_HOVER";
    strings["Table row (even)##CC_GUI_COLOR_TABLE_ROW_EVEN"].plurals[0] = "Wiersz tabeli (parzysty)##CC_GUI_COLOR_TABLE_ROW_EVEN";
    strings["Table row (odd)##CC_GUI_COLOR_TABLE_ROW_ODD"].plurals[0] = "Wiersz tabeli (nieparzysty)##CC_GUI_COLOR_TABLE_ROW_ODD";

    strings["Background##CC_GUI_COLOR_BACKGROUND"].plurals[0] = "Tło##CC_GUI_COLOR_BACKGROUND";
    strings["Window background##CC_GUI_COLOR_FRAME_BACKGROUND"].plurals[0] = "Tło okna##CC_GUI_COLOR_FRAME_BACKGROUND";
    strings["Sub-window background##CC_GUI_COLOR_FRAME_BACKGROUND_CHILD"].plurals[0] = "Tło podokna##CC_GUI_COLOR_FRAME_BACKGROUND_CHILD";
    strings["Pop-up background##CC_GUI_COLOR_FRAME_BACKGROUND_POPUP"].plurals[0] = "Tło wyskakujących okien##CC_GUI_COLOR_FRAME_BACKGROUND_POPUP";
    strings["Modal backdrop##CC_GUI_COLOR_MODAL_BACKDROP"].plurals[0] = "Cieniowanie po pojawieniu się okna modalnego##CC_GUI_COLOR_MODAL_BACKDROP";
    strings["Header##CC_GUI_COLOR_HEADER"].plurals[0] = "Nagłówek##CC_GUI_COLOR_HEADER";
    strings["Text##CC_GUI_COLOR_TEXT"].plurals[0] = "Tekst##CC_GUI_COLOR_TEXT";
    strings["Text (disabled)##CC_GUI_COLOR_TEXT_DISABLED"].plurals[0] = "Tekst (wyłączony)##CC_GUI_COLOR_TEXT_DISABLED";
    strings["Title bar (inactive)##CC_GUI_COLOR_TITLE_INACTIVE"].plurals[0] = "Pasek tytułowy (nieaktywny)##CC_GUI_COLOR_TITLE_INACTIVE";
    strings["Title bar (collapsed)##CC_GUI_COLOR_TITLE_COLLAPSED"].plurals[0] = "Pasek tytułowy (zwinięty)##CC_GUI_COLOR_TITLE_COLLAPSED";
    strings["Menu bar##CC_GUI_COLOR_MENU_BAR"].plurals[0] = "Pasek menu##CC_GUI_COLOR_MENU_BAR";
    strings["Border##CC_GUI_COLOR_BORDER"].plurals[0] = "Krawędź##CC_GUI_COLOR_BORDER";
    strings["Border shadow##CC_GUI_COLOR_BORDER_SHADOW"].plurals[0] = "Cień krawędzi##CC_GUI_COLOR_BORDER_SHADOW";
    strings["Scroll bar##CC_GUI_COLOR_SCROLL"].plurals[0] = "Pasek przewijania##CC_GUI_COLOR_SCROLL";
    strings["Scroll bar (hovered)##CC_GUI_COLOR_SCROLL_HOVER"].plurals[0] = "Pasek przewijania (zazn. kursorem)##CC_GUI_COLOR_SCROLL_HOVER";
    strings["Scroll bar (clicked)##CC_GUI_COLOR_SCROLL_ACTIVE"].plurals[0] = "Pasek przewijania (wciśnięty)##CC_GUI_COLOR_SCROLL_ACTIVE";
    strings["Scroll bar background##CC_GUI_COLOR_SCROLL_BACKGROUND"].plurals[0] = "Tło paska przewijania##CC_GUI_COLOR_SCROLL_BACKGROUND";
    strings["Separator##CC_GUI_COLOR_SEPARATOR"].plurals[0] = "Separator ##CC_GUI_COLOR_SEPARATOR";
    strings["Separator (hover)##CC_GUI_COLOR_SEPARATOR_HOVER"].plurals[0] = "Separator (zaznaczony)##CC_GUI_COLOR_SEPARATOR_HOVER";
    strings["Separator (active)##CC_GUI_COLOR_SEPARATOR_ACTIVE"].plurals[0] = "Separator (aktywny)##CC_GUI_COLOR_SEPARATOR_ACTIVE";
    strings["Docking preview##CC_GUI_COLOR_DOCKING_PREVIEW"].plurals[0] = "Podgląd dokowania okien##CC_GUI_COLOR_DOCKING_PREVIEW";
    strings["Docking empty##CC_GUI_COLOR_DOCKING_EMPTY"].plurals[0] = "Puste pole dokowania okien##CC_GUI_COLOR_DOCKING_EMPTY";
    strings["Table header##CC_GUI_COLOR_TABLE_HEADER"].plurals[0] = "Nagłówek tabeli##CC_GUI_COLOR_TABLE_HEADER";
    strings["Table border (hard)##CC_GUI_COLOR_TABLE_BORDER_HARD"].plurals[0] = "Krawędź tabeli (twarda)##CC_GUI_COLOR_TABLE_BORDER_HARD";
    strings["Table border (soft)##CC_GUI_COLOR_TABLE_BORDER_SOFT"].plurals[0] = "Krawędź tabeli (miękka)##CC_GUI_COLOR_TABLE_BORDER_SOFT";
    strings["Drag and drop target##CC_GUI_COLOR_DRAG_DROP_TARGET"].plurals[0] = "Cel upuszczania##CC_GUI_COLOR_DRAG_DROP_TARGET";
    strings["Window switcher (highlight)##CC_GUI_COLOR_NAV_WIN_HIGHLIGHT"].plurals[0] = "Przełącznik okien (podświetlony)##CC_GUI_COLOR_NAV_WIN_HIGHLIGHT";
    strings["Window switcher backdrop##CC_GUI_COLOR_NAV_WIN_BACKDROP"].plurals[0] = "Przełącznik okien (kolor cieniowania reszty interfejsu)##CC_GUI_COLOR_NAV_WIN_BACKDROP";

    strings["Toggle on##CC_GUI_COLOR_TOGGLE_ON"].plurals[0] = "Włącznik##CC_GUI_COLOR_TOGGLE_ON";
    strings["Toggle off##CC_GUI_COLOR_TOGGLE_OFF"].plurals[0] = "Wyłącznik##CC_GUI_COLOR_TOGGLE_OFF";
    strings["Playback status##CC_GUI_COLOR_PLAYBACK_STAT"].plurals[0] = "Status odtwarzania##CC_GUI_COLOR_PLAYBACK_STAT";
    strings["Destructive hint##CC_GUI_COLOR_DESTRUCTIVE"].plurals[0] = "Wskazówka usuwania##CC_GUI_COLOR_DESTRUCTIVE";
    strings["Warning hint##CC_GUI_COLOR_WARNING"].plurals[0] = "Wskazówka ostrzeżenia##CC_GUI_COLOR_WARNING";
    strings["Error hint##CC_GUI_COLOR_ERROR"].plurals[0] = "Wskazówka dot. błędu##CC_GUI_COLOR_ERROR";

    strings["Directory##CC_GUI_COLOR_FILE_DIR"].plurals[0] = "Folder##CC_GUI_COLOR_FILE_DIR";
    strings["Song (native)##CC_GUI_COLOR_FILE_SONG_NATIVE"].plurals[0] = "Utwór (natywny)##CC_GUI_COLOR_FILE_SONG_NATIVE";
    strings["Song (import)##CC_GUI_COLOR_FILE_SONG_IMPORT"].plurals[0] = "Utwór (importowany)##CC_GUI_COLOR_FILE_SONG_IMPORT";
    strings["Instrument##CC_GUI_COLOR_FILE_INSTR"].plurals[0] = "Instrument##CC_GUI_COLOR_FILE_INSTR";
    strings["Audio##CC_GUI_COLOR_FILE_AUDIO"].plurals[0] = "Audio##CC_GUI_COLOR_FILE_AUDIO";
    strings["Wavetable##CC_GUI_COLOR_FILE_WAVE"].plurals[0] = "Tablica fal##CC_GUI_COLOR_FILE_WAVE";
    strings["VGM##CC_GUI_COLOR_FILE_VGM"].plurals[0] = "VGM##CC_GUI_COLOR_FILE_VGM";
    strings["ZSM##CC_GUI_COLOR_FILE_ZSM"].plurals[0] = "ZSM##CC_GUI_COLOR_FILE_ZSM";
    strings["Font##CC_GUI_COLOR_FILE_FONT"].plurals[0] = "Czcionka##CC_GUI_COLOR_FILE_FONT";
    strings["Other##CC_GUI_COLOR_FILE_OTHER"].plurals[0] = "Inne##CC_GUI_COLOR_FILE_OTHER";

    strings["Border##CC_GUI_COLOR_OSC_BORDER"].plurals[0] = "Krawędź oscyloskopu##CC_GUI_COLOR_OSC_BORDER";
    strings["Background (top-left)##CC_GUI_COLOR_OSC_BG1"].plurals[0] = "Tło (lewy górny róg)##CC_GUI_COLOR_OSC_BG1";
    strings["Background (top-right)##CC_GUI_COLOR_OSC_BG2"].plurals[0] = "Tło (prawy górny róg)##CC_GUI_COLOR_OSC_BG2";
    strings["Background (bottom-left)##CC_GUI_COLOR_OSC_BG3"].plurals[0] = "Tło (lewy dolny róg)##CC_GUI_COLOR_OSC_BG3";
    strings["Background (bottom-right)##CC_GUI_COLOR_OSC_BG4"].plurals[0] = "Tło (prawy dolny róg)##CC_GUI_COLOR_OSC_BG4";
    strings["Waveform##CC_GUI_COLOR_OSC_WAVE"].plurals[0] = "Kształt fali##CC_GUI_COLOR_OSC_WAVE";
    strings["Waveform (clip)##CC_GUI_COLOR_OSC_WAVE_PEAK"].plurals[0] = "Fala (poza skalą)##CC_GUI_COLOR_OSC_WAVE_PEAK";
    strings["Reference##CC_GUI_COLOR_OSC_REF"].plurals[0] = "Przykład##CC_GUI_COLOR_OSC_REF";
    strings["Guide##CC_GUI_COLOR_OSC_GUIDE"].plurals[0] = "Przewodnik##CC_GUI_COLOR_OSC_GUIDE";

    strings["Waveform (1)##CC_GUI_COLOR_OSC_WAVE_CH0"].plurals[0] = "Kształt fali (1)##CC_GUI_COLOR_OSC_WAVE_CH0";
    strings["Waveform (2)##CC_GUI_COLOR_OSC_WAVE_CH1"].plurals[0] = "Kształt fali (2)##CC_GUI_COLOR_OSC_WAVE_CH1";
    strings["Waveform (3)##CC_GUI_COLOR_OSC_WAVE_CH2"].plurals[0] = "Kształt fali (3)##CC_GUI_COLOR_OSC_WAVE_CH2";
    strings["Waveform (4)##CC_GUI_COLOR_OSC_WAVE_CH3"].plurals[0] = "Kształt fali (4)##CC_GUI_COLOR_OSC_WAVE_CH3";
    strings["Waveform (5)##CC_GUI_COLOR_OSC_WAVE_CH4"].plurals[0] = "Kształt fali (5)##CC_GUI_COLOR_OSC_WAVE_CH4";
    strings["Waveform (6)##CC_GUI_COLOR_OSC_WAVE_CH5"].plurals[0] = "Kształt fali (6)##CC_GUI_COLOR_OSC_WAVE_CH5";
    strings["Waveform (7)##CC_GUI_COLOR_OSC_WAVE_CH6"].plurals[0] = "Kształt fali (7)##CC_GUI_COLOR_OSC_WAVE_CH6";
    strings["Waveform (8)##CC_GUI_COLOR_OSC_WAVE_CH7"].plurals[0] = "Kształt fali (8)##CC_GUI_COLOR_OSC_WAVE_CH7";
    strings["Waveform (9)##CC_GUI_COLOR_OSC_WAVE_CH8"].plurals[0] = "Kształt fali (9)##CC_GUI_COLOR_OSC_WAVE_CH8";
    strings["Waveform (10)##CC_GUI_COLOR_OSC_WAVE_CH9"].plurals[0] = "Kształt fali (10)##CC_GUI_COLOR_OSC_WAVE_CH9";
    strings["Waveform (11)##CC_GUI_COLOR_OSC_WAVE_CH10"].plurals[0] = "Kształt fali (11)##CC_GUI_COLOR_OSC_WAVE_CH10";
    strings["Waveform (12)##CC_GUI_COLOR_OSC_WAVE_CH11"].plurals[0] = "Kształt fali (12)##CC_GUI_COLOR_OSC_WAVE_CH11";
    strings["Waveform (13)##CC_GUI_COLOR_OSC_WAVE_CH12"].plurals[0] = "Kształt fali (13)##CC_GUI_COLOR_OSC_WAVE_CH12";
    strings["Waveform (14)##CC_GUI_COLOR_OSC_WAVE_CH13"].plurals[0] = "Kształt fali (14)##CC_GUI_COLOR_OSC_WAVE_CH13";
    strings["Waveform (15)##CC_GUI_COLOR_OSC_WAVE_CH14"].plurals[0] = "Kształt fali (15)##CC_GUI_COLOR_OSC_WAVE_CH14";
    strings["Waveform (16)##CC_GUI_COLOR_OSC_WAVE_CH15"].plurals[0] = "Kształt fali (16)##CC_GUI_COLOR_OSC_WAVE_CH15";

    strings["Low##CC_GUI_COLOR_VOLMETER_LOW"].plurals[0] = "Niski poziom##CC_GUI_COLOR_VOLMETER_LOW";
    strings["High##CC_GUI_COLOR_VOLMETER_HIGH"].plurals[0] = "Wysoki poziom##CC_GUI_COLOR_VOLMETER_HIGH";
    strings["Clip##CC_GUI_COLOR_VOLMETER_PEAK"].plurals[0] = "Poza skalą##CC_GUI_COLOR_VOLMETER_PEAK";

    strings["Order number##CC_GUI_COLOR_ORDER_ROW_INDEX"].plurals[0] = "Numer wiersza matrycy wz.##CC_GUI_COLOR_ORDER_ROW_INDEX";
    strings["Playing order background##CC_GUI_COLOR_ORDER_ACTIVE"].plurals[0] = "Tło odtwarzaniego wiersza matrycy##CC_GUI_COLOR_ORDER_ACTIVE";
    strings["Song loop##CC_GUI_COLOR_SONG_LOOP"].plurals[0] = "Pętla piosenki##CC_GUI_COLOR_SONG_LOOP";
    strings["Selected order##CC_GUI_COLOR_ORDER_SELECTED"].plurals[0] = "Wybrany wiersz##CC_GUI_COLOR_ORDER_SELECTED";
    strings["Similar patterns##CC_GUI_COLOR_ORDER_SIMILAR"].plurals[0] = "Podobne wzorce##CC_GUI_COLOR_ORDER_SIMILAR";
    strings["Inactive patterns##CC_GUI_COLOR_ORDER_INACTIVE"].plurals[0] = "Nieaktywne wzorce##CC_GUI_COLOR_ORDER_INACTIVE";

    strings["Envelope##CC_GUI_COLOR_FM_ENVELOPE"].plurals[0] = "Obwiednia##CC_GUI_COLOR_FM_ENVELOPE";
    strings["Sustain guide##CC_GUI_COLOR_FM_ENVELOPE_SUS_GUIDE"].plurals[0] = "Wizualizacja podtrzymania##CC_GUI_COLOR_FM_ENVELOPE_SUS_GUIDE";
    strings["Release##CC_GUI_COLOR_FM_ENVELOPE_RELEASE"].plurals[0] = "Zwolnienie##CC_GUI_COLOR_FM_ENVELOPE_RELEASE";

    strings["Algorithm background##CC_GUI_COLOR_FM_ALG_BG"].plurals[0] = "Tło schematu algorytmu##CC_GUI_COLOR_FM_ALG_BG";
    strings["Algorithm lines##CC_GUI_COLOR_FM_ALG_LINE"].plurals[0] = "Linie schematu algorytmu##CC_GUI_COLOR_FM_ALG_LINE";
    strings["Modulator##CC_GUI_COLOR_FM_MOD"].plurals[0] = "Modulator##CC_GUI_COLOR_FM_MOD";
    strings["Carrier##CC_GUI_COLOR_FM_CAR"].plurals[0] = "Fala nośna##CC_GUI_COLOR_FM_CAR";

    strings["SSG-EG##CC_GUI_COLOR_FM_SSG"].plurals[0] = "SSG-EG##CC_GUI_COLOR_FM_SSG";
    strings["Waveform##CC_GUI_COLOR_FM_WAVE"].plurals[0] = "Kształt fali##CC_GUI_COLOR_FM_WAVE";

    strings["Mod. accent (primary)##CC_GUI_COLOR_FM_PRIMARY_MOD"].plurals[0] = "Odcień modulatora (główny)##CC_GUI_COLOR_FM_PRIMARY_MOD";
    strings["Mod. accent (secondary)##CC_GUI_COLOR_FM_SECONDARY_MOD"].plurals[0] = "Odcień modulatora (poboczny)##CC_GUI_COLOR_FM_SECONDARY_MOD";
    strings["Mod. border##CC_GUI_COLOR_FM_BORDER_MOD"].plurals[0] = "Krawędź modulatora##CC_GUI_COLOR_FM_BORDER_MOD";
    strings["Mod. border shadow##CC_GUI_COLOR_FM_BORDER_SHADOW_MOD"].plurals[0] = "Cień krawędzi modulatora##CC_GUI_COLOR_FM_BORDER_SHADOW_MOD";

    strings["Car. accent (primary)##CC_GUI_COLOR_FM_PRIMARY_CAR"].plurals[0] = "Odcień fali nośnej (główny)##CC_GUI_COLOR_FM_PRIMARY_CAR";
    strings["Car. accent (secondary)##CC_GUI_COLOR_FM_SECONDARY_CAR"].plurals[0] = "Odcień fali nośnej (poboczny)##CC_GUI_COLOR_FM_SECONDARY_CAR";
    strings["Car. border##CC_GUI_COLOR_FM_BORDER_CAR"].plurals[0] = "Krawędź fali nośnej##CC_GUI_COLOR_FM_BORDER_CAR";
    strings["Car. border shadow##CC_GUI_COLOR_FM_BORDER_SHADOW_CAR"].plurals[0] = "Cień krawędzi fali nośnej##CC_GUI_COLOR_FM_BORDER_SHADOW_CAR";

    strings["Volume##CC_GUI_COLOR_MACRO_VOLUME"].plurals[0] = "Głośność##CC_GUI_COLOR_MACRO_VOLUME";
    strings["Pitch##CC_GUI_COLOR_MACRO_PITCH"].plurals[0] = "Wysokość##CC_GUI_COLOR_MACRO_PITCH";
    strings["Wave##CC_GUI_COLOR_MACRO_WAVE"].plurals[0] = "Fala##CC_GUI_COLOR_MACRO_WAVE";
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
    strings["VRC6 (saw)##CC_GUI_COLOR_INSTR_VRC6_SAW"].plurals[0] = "VRC6 (piła)##CC_GUI_COLOR_INSTR_VRC6_SAW";
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
    strings["Sound Unit##CC_GUI_COLOR_INSTR_SU"].plurals[0] = "SoundUnit##CC_GUI_COLOR_INSTR_SU";
    strings["Namco WSG##CC_GUI_COLOR_INSTR_NAMCO"].plurals[0] = "Namco WSG##CC_GUI_COLOR_INSTR_NAMCO";
    strings["FM (OPL Drums)##CC_GUI_COLOR_INSTR_OPL_DRUMS"].plurals[0] = "FM (OPL, tryub perkusji)##CC_GUI_COLOR_INSTR_OPL_DRUMS";
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

    strings["Single color (background)##CC_GUI_COLOR_CHANNEL_BG"].plurals[0] = "Jednolity kolor (tło)##CC_GUI_COLOR_CHANNEL_BG";
    strings["Single color (text)##CC_GUI_COLOR_CHANNEL_FG"].plurals[0] = "Jednolity kolor (tekst)##CC_GUI_COLOR_CHANNEL_FG";
    strings["FM##CC_GUI_COLOR_CHANNEL_FM"].plurals[0] = "FM##CC_GUI_COLOR_CHANNEL_FM";
    strings["Pulse##CC_GUI_COLOR_CHANNEL_PULSE"].plurals[0] = "Fala prostokątna##CC_GUI_COLOR_CHANNEL_PULSE";
    strings["Noise##CC_GUI_COLOR_CHANNEL_NOISE"].plurals[0] = "Szum##CC_GUI_COLOR_CHANNEL_NOISE";
    strings["PCM##CC_GUI_COLOR_CHANNEL_PCM"].plurals[0] = "PCM##CC_GUI_COLOR_CHANNEL_PCM";
    strings["Wave##CC_GUI_COLOR_CHANNEL_WAVE"].plurals[0] = "Fala##CC_GUI_COLOR_CHANNEL_WAVE";
    strings["FM operator##CC_GUI_COLOR_CHANNEL_OP"].plurals[0] = "Operator FM##CC_GUI_COLOR_CHANNEL_OP";
    strings["Muted##CC_GUI_COLOR_CHANNEL_MUTED"].plurals[0] = "Wyciszony##CC_GUI_COLOR_CHANNEL_MUTED";

    strings["Playhead##CC_GUI_COLOR_PATTERN_PLAY_HEAD"].plurals[0] = "Wskaźnik odtwarzania##CC_GUI_COLOR_PATTERN_PLAY_HEAD";
    strings["Editing##CC_GUI_COLOR_EDITING"].plurals[0] = "Edytowanie##CC_GUI_COLOR_EDITING";
    strings["Editing (will clone)##CC_GUI_COLOR_EDITING_CLONE"].plurals[0] = "Edytowanie (zostanie sklonowane)##CC_GUI_COLOR_EDITING_CLONE";
    strings["Cursor##CC_GUI_COLOR_PATTERN_CURSOR"].plurals[0] = "Kursor##CC_GUI_COLOR_PATTERN_CURSOR";
    strings["Cursor (hovered)##CC_GUI_COLOR_PATTERN_CURSOR_HOVER"].plurals[0] = "Kursor (zaznaczony)##CC_GUI_COLOR_PATTERN_CURSOR_HOVER";
    strings["Cursor (clicked)##CC_GUI_COLOR_PATTERN_CURSOR_ACTIVE"].plurals[0] = "Kursor (wciśnięty)##CC_GUI_COLOR_PATTERN_CURSOR_ACTIVE";
    strings["Selection##CC_GUI_COLOR_PATTERN_SELECTION"].plurals[0] = "Zaznaczenie##CC_GUI_COLOR_PATTERN_SELECTION";
    strings["Selection (hovered)##CC_GUI_COLOR_PATTERN_SELECTION_HOVER"].plurals[0] = "Zaznaczenie (kursor myszy na zaznaczeniu)##CC_GUI_COLOR_PATTERN_SELECTION_HOVER";
    strings["Selection (clicked)##CC_GUI_COLOR_PATTERN_SELECTION_ACTIVE"].plurals[0] = "Zaznaczenie (wciśnięte)##CC_GUI_COLOR_PATTERN_SELECTION_ACTIVE";
    strings["Highlight 1##CC_GUI_COLOR_PATTERN_HI_1"].plurals[0] = "Podkreślenie 1##CC_GUI_COLOR_PATTERN_HI_1";
    strings["Highlight 2##CC_GUI_COLOR_PATTERN_HI_2"].plurals[0] = "Podkreślenie 2##CC_GUI_COLOR_PATTERN_HI_2";
    strings["Row number##CC_GUI_COLOR_PATTERN_ROW_INDEX"].plurals[0] = "Numer wiersza##CC_GUI_COLOR_PATTERN_ROW_INDEX";
    strings["Row number (highlight 1)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI1"].plurals[0] = "Numer wiersza (podkreślenie 1)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI1";
    strings["Row number (highlight 2)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI2"].plurals[0] = "Numer wiersza (podkreślenie 2)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI2";
    strings["Note##CC_GUI_COLOR_PATTERN_ACTIVE"].plurals[0] = "Nuta##CC_GUI_COLOR_PATTERN_ACTIVE";
    strings["Note (highlight 1)##CC_GUI_COLOR_PATTERN_ACTIVE_HI1"].plurals[0] = "Nuta (podkreślenie 1)##CC_GUI_COLOR_PATTERN_ACTIVE_HI1";
    strings["Note (highlight 2)##CC_GUI_COLOR_PATTERN_ACTIVE_HI2"].plurals[0] = "Nuta (podkreślenie 2)##CC_GUI_COLOR_PATTERN_ACTIVE_HI2";
    strings["Blank##CC_GUI_COLOR_PATTERN_INACTIVE"].plurals[0] = "Pusta komórka##CC_GUI_COLOR_PATTERN_INACTIVE";
    strings["Blank (highlight 1)##CC_GUI_COLOR_PATTERN_INACTIVE_HI1"].plurals[0] = "Pusta komórka (podkreślenie 1)##CC_GUI_COLOR_PATTERN_INACTIVE_HI1";
    strings["Blank (highlight 2)##CC_GUI_COLOR_PATTERN_INACTIVE_HI2"].plurals[0] = "Pusta komórka (podkreślenie 2)##CC_GUI_COLOR_PATTERN_INACTIVE_HI2";
    strings["Instrument##CC_GUI_COLOR_PATTERN_INS"].plurals[0] = "Instrument##CC_GUI_COLOR_PATTERN_INS";
    strings["Instrument (invalid type)##CC_GUI_COLOR_PATTERN_INS_WARN"].plurals[0] = "Instrument (nieprawidłowy typ)##CC_GUI_COLOR_PATTERN_INS_WARN";
    strings["Instrument (out of range)##CC_GUI_COLOR_PATTERN_INS_ERROR"].plurals[0] = "Instrument (niepoprawny indeks)##CC_GUI_COLOR_PATTERN_INS_ERROR";
    strings["Volume (0%)##CC_GUI_COLOR_PATTERN_VOLUME_MIN"].plurals[0] = "Głośność (0%)##CC_GUI_COLOR_PATTERN_VOLUME_MIN";
    strings["Volume (50%)##CC_GUI_COLOR_PATTERN_VOLUME_HALF"].plurals[0] = "Głośność (50%)##CC_GUI_COLOR_PATTERN_VOLUME_HALF";
    strings["Volume (100%)##CC_GUI_COLOR_PATTERN_VOLUME_MAX"].plurals[0] = "Głośność (100%)##CC_GUI_COLOR_PATTERN_VOLUME_MAX";
    strings["Invalid effect##CC_GUI_COLOR_PATTERN_EFFECT_INVALID"].plurals[0] = "Niepoprawny efekt##CC_GUI_COLOR_PATTERN_EFFECT_INVALID";
    strings["Pitch effect##CC_GUI_COLOR_PATTERN_EFFECT_PITCH"].plurals[0] = "Efekt (wysokość dźwięku)##CC_GUI_COLOR_PATTERN_EFFECT_PITCH";
    strings["Volume effect##CC_GUI_COLOR_PATTERN_EFFECT_VOLUME"].plurals[0] = "Efekt (głośność)##CC_GUI_COLOR_PATTERN_EFFECT_VOLUME";
    strings["Panning effect##CC_GUI_COLOR_PATTERN_EFFECT_PANNING"].plurals[0] = "Efekt (panning)##CC_GUI_COLOR_PATTERN_EFFECT_PANNING";
    strings["Song effect##CC_GUI_COLOR_PATTERN_EFFECT_SONG"].plurals[0] = "Efekt (utwór)##CC_GUI_COLOR_PATTERN_EFFECT_SONG";
    strings["Time effect##CC_GUI_COLOR_PATTERN_EFFECT_TIME"].plurals[0] = "Efekt (czas)##CC_GUI_COLOR_PATTERN_EFFECT_TIME";
    strings["Speed effect##CC_GUI_COLOR_PATTERN_EFFECT_SPEED"].plurals[0] = "Efekt (prędkość)##CC_GUI_COLOR_PATTERN_EFFECT_SPEED";
    strings["Primary specific effect##CC_GUI_COLOR_PATTERN_EFFECT_SYS_PRIMARY"].plurals[0] = "Główny efekt układu##CC_GUI_COLOR_PATTERN_EFFECT_SYS_PRIMARY";
    strings["Secondary specific effect##CC_GUI_COLOR_PATTERN_EFFECT_SYS_SECONDARY"].plurals[0] = "Poboczny efekt układu##CC_GUI_COLOR_PATTERN_EFFECT_SYS_SECONDARY";
    strings["Miscellaneous##CC_GUI_COLOR_PATTERN_EFFECT_MISC"].plurals[0] = "Efekt (inne)##CC_GUI_COLOR_PATTERN_EFFECT_MISC";
    strings["External command output##CC_GUI_COLOR_EE_VALUE"].plurals[0] = "Wyświetlanie zewnętrznych komend##CC_GUI_COLOR_EE_VALUE";
    strings["Status: off/disabled##CC_GUI_COLOR_PATTERN_STATUS_OFF"].plurals[0] = "Status: wyłączony##CC_GUI_COLOR_PATTERN_STATUS_OFF";
    strings["Status: off + macro rel##CC_GUI_COLOR_PATTERN_STATUS_REL"].plurals[0] = "Status: wył. + zwolnienie makra##CC_GUI_COLOR_PATTERN_STATUS_REL";
    strings["Status: on + macro rel##CC_GUI_COLOR_PATTERN_STATUS_REL_ON"].plurals[0] = "Status: wł. + zwolnienie makra##CC_GUI_COLOR_PATTERN_STATUS_REL_ON";
    strings["Status: on##CC_GUI_COLOR_PATTERN_STATUS_ON"].plurals[0] = "Status: wł.##CC_GUI_COLOR_PATTERN_STATUS_ON";
    strings["Status: volume##CC_GUI_COLOR_PATTERN_STATUS_VOLUME"].plurals[0] = "Status: głośność##CC_GUI_COLOR_PATTERN_STATUS_VOLUME";
    strings["Status: pitch##CC_GUI_COLOR_PATTERN_STATUS_PITCH"].plurals[0] = "Status: wysokość dźwięku##CC_GUI_COLOR_PATTERN_STATUS_PITCH";
    strings["Status: panning##CC_GUI_COLOR_PATTERN_STATUS_PANNING"].plurals[0] = "Status: panning##CC_GUI_COLOR_PATTERN_STATUS_PANNING";
    strings["Status: chip (primary)##CC_GUI_COLOR_PATTERN_STATUS_SYS1"].plurals[0] = "Status: układ (główny)##CC_GUI_COLOR_PATTERN_STATUS_SYS1";
    strings["Status: chip (secondary)##CC_GUI_COLOR_PATTERN_STATUS_SYS2"].plurals[0] = "Status: układ (poboczny)##CC_GUI_COLOR_PATTERN_STATUS_SYS2";
    strings["Status: mixing##CC_GUI_COLOR_PATTERN_STATUS_MIXING"].plurals[0] = "Status: miksowanie##CC_GUI_COLOR_PATTERN_STATUS_MIXING";
    strings["Status: DSP effect##CC_GUI_COLOR_PATTERN_STATUS_DSP"].plurals[0] = "Status: efekt DSP##CC_GUI_COLOR_PATTERN_STATUS_DSP";
    strings["Status: note altering##CC_GUI_COLOR_PATTERN_STATUS_NOTE"].plurals[0] = "Status: zmiana nuty##CC_GUI_COLOR_PATTERN_STATUS_NOTE";
    strings["Status: misc color 1##CC_GUI_COLOR_PATTERN_STATUS_MISC1"].plurals[0] = "Status: inne (kolor 1)##CC_GUI_COLOR_PATTERN_STATUS_MISC1";
    strings["Status: misc color 2##CC_GUI_COLOR_PATTERN_STATUS_MISC2"].plurals[0] = "Status: inne (kolor 2)##CC_GUI_COLOR_PATTERN_STATUS_MISC2";
    strings["Status: misc color 3##CC_GUI_COLOR_PATTERN_STATUS_MISC3"].plurals[0] = "Status: inne (kolor 3)##CC_GUI_COLOR_PATTERN_STATUS_MISC3";
    strings["Status: attack##CC_GUI_COLOR_PATTERN_STATUS_ATTACK"].plurals[0] = "Status: atak##CC_GUI_COLOR_PATTERN_STATUS_ATTACK";
    strings["Status: decay##CC_GUI_COLOR_PATTERN_STATUS_DECAY"].plurals[0] = "Status: opadanie##CC_GUI_COLOR_PATTERN_STATUS_DECAY";
    strings["Status: sustain##CC_GUI_COLOR_PATTERN_STATUS_SUSTAIN"].plurals[0] = "Status: podtrzymanie##CC_GUI_COLOR_PATTERN_STATUS_SUSTAIN";
    strings["Status: release##CC_GUI_COLOR_PATTERN_STATUS_RELEASE"].plurals[0] = "Status: zwolnienie##CC_GUI_COLOR_PATTERN_STATUS_RELEASE";
    strings["Status: decrease linear##CC_GUI_COLOR_PATTERN_STATUS_DEC_LINEAR"].plurals[0] = "Status: liniowe opadanie##CC_GUI_COLOR_PATTERN_STATUS_DEC_LINEAR";
    strings["Status: decrease exp##CC_GUI_COLOR_PATTERN_STATUS_DEC_EXP"].plurals[0] = "Status: wykładnicze opadanie##CC_GUI_COLOR_PATTERN_STATUS_DEC_EXP";
    strings["Status: increase##CC_GUI_COLOR_PATTERN_STATUS_INC"].plurals[0] = "Status: wzrost##CC_GUI_COLOR_PATTERN_STATUS_INC";
    strings["Status: bent##CC_GUI_COLOR_PATTERN_STATUS_BENT"].plurals[0] = "Status: zakrzywiony##CC_GUI_COLOR_PATTERN_STATUS_BENT";
    strings["Status: direct##CC_GUI_COLOR_PATTERN_STATUS_DIRECT"].plurals[0] = "Status: bezpośreni##CC_GUI_COLOR_PATTERN_STATUS_DIRECT";

    strings["Background##CC_GUI_COLOR_SAMPLE_BG"].plurals[0] = "Tło##CC_GUI_COLOR_SAMPLE_BG";
    strings["Waveform##CC_GUI_COLOR_SAMPLE_FG"].plurals[0] = "Kształt fali##CC_GUI_COLOR_SAMPLE_FG";
    strings["Time background##CC_GUI_COLOR_SAMPLE_TIME_BG"].plurals[0] = "Tło pola czasu##CC_GUI_COLOR_SAMPLE_TIME_BG";
    strings["Time text##CC_GUI_COLOR_SAMPLE_TIME_FG"].plurals[0] = "Tekst pola czasu##CC_GUI_COLOR_SAMPLE_TIME_FG";
    strings["Loop region##CC_GUI_COLOR_SAMPLE_LOOP"].plurals[0] = "Zapętlony region##CC_GUI_COLOR_SAMPLE_LOOP";
    strings["Center guide##CC_GUI_COLOR_SAMPLE_CENTER"].plurals[0] = "Linia środkowa##CC_GUI_COLOR_SAMPLE_CENTER";
    strings["Grid##CC_GUI_COLOR_SAMPLE_GRID"].plurals[0] = "Siatka##CC_GUI_COLOR_SAMPLE_GRID";
    strings["Selection##CC_GUI_COLOR_SAMPLE_SEL"].plurals[0] = "Zaznaczenie##CC_GUI_COLOR_SAMPLE_SEL";
    strings["Selection points##CC_GUI_COLOR_SAMPLE_SEL_POINT"].plurals[0] = "Krawędzie zaznaczenia##CC_GUI_COLOR_SAMPLE_SEL_POINT";
    strings["Preview needle##CC_GUI_COLOR_SAMPLE_NEEDLE"].plurals[0] = "Kursor podglądu odtwarzania##CC_GUI_COLOR_SAMPLE_NEEDLE";
    strings["Playing needles##CC_GUI_COLOR_SAMPLE_NEEDLE_PLAYING"].plurals[0] = "Kursory podglądu odtwarzania##CC_GUI_COLOR_SAMPLE_NEEDLE_PLAYING";
    strings["Loop markers##CC_GUI_COLOR_SAMPLE_LOOP_POINT"].plurals[0] = "Znaczniki zapętlenia##CC_GUI_COLOR_SAMPLE_LOOP_POINT";
    strings["Chip select: disabled##CC_GUI_COLOR_SAMPLE_CHIP_DISABLED"].plurals[0] = "Wybór układu: wył.##CC_GUI_COLOR_SAMPLE_CHIP_DISABLED";
    strings["Chip select: enabled##CC_GUI_COLOR_SAMPLE_CHIP_ENABLED"].plurals[0] = "Wybór układu: wł.##CC_GUI_COLOR_SAMPLE_CHIP_ENABLED";
    strings["Chip select: enabled (failure)##CC_GUI_COLOR_SAMPLE_CHIP_WARNING"].plurals[0] = "Wybór układu: wł. (błąd)##CC_GUI_COLOR_SAMPLE_CHIP_WARNING";

    strings["Unallocated##CC_GUI_COLOR_PAT_MANAGER_NULL"].plurals[0] = "Nieprzypisany##CC_GUI_COLOR_PAT_MANAGER_NULL";
    strings["Unused##CC_GUI_COLOR_PAT_MANAGER_UNUSED"].plurals[0] = "Nieużywany##CC_GUI_COLOR_PAT_MANAGER_UNUSED";
    strings["Used##CC_GUI_COLOR_PAT_MANAGER_USED"].plurals[0] = "Używany##CC_GUI_COLOR_PAT_MANAGER_USED";
    strings["Overused##CC_GUI_COLOR_PAT_MANAGER_OVERUSED"].plurals[0] = "Nadużywany##CC_GUI_COLOR_PAT_MANAGER_OVERUSED";
    strings["Really overused##CC_GUI_COLOR_PAT_MANAGER_EXTREMELY_OVERUSED"].plurals[0] = "Bardzo nadużywany##CC_GUI_COLOR_PAT_MANAGER_EXTREMELY_OVERUSED";
    strings["Combo Breaker##CC_GUI_COLOR_PAT_MANAGER_COMBO_BREAKER"].plurals[0] = "COMBO BREAKER##CC_GUI_COLOR_PAT_MANAGER_COMBO_BREAKER";

    strings["Background##CC_GUI_COLOR_PIANO_BACKGROUND"].plurals[0] = "Tło##CC_GUI_COLOR_PIANO_BACKGROUND";
    strings["Upper key##CC_GUI_COLOR_PIANO_KEY_TOP"].plurals[0] = "Górny klawisz##CC_GUI_COLOR_PIANO_KEY_TOP";
    strings["Upper key (feedback)##CC_GUI_COLOR_PIANO_KEY_TOP_HIT"].plurals[0] = "Górny klawisz (feedback)##CC_GUI_COLOR_PIANO_KEY_TOP_HIT";
    strings["Upper key (pressed)##CC_GUI_COLOR_PIANO_KEY_TOP_ACTIVE"].plurals[0] = "Górny klawisz (wciśnięty)##CC_GUI_COLOR_PIANO_KEY_TOP_ACTIVE";
    strings["Lower key##CC_GUI_COLOR_PIANO_KEY_BOTTOM"].plurals[0] = "Dolny klawisz##CC_GUI_COLOR_PIANO_KEY_BOTTOM";
    strings["Lower key (feedback)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_HIT"].plurals[0] = "Dolny klawisz (feedback)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_HIT";
    strings["Lower key (pressed)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_ACTIVE"].plurals[0] = "Dolny klawisz (wciśnięty)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_ACTIVE";

    strings["Clock text##CC_GUI_COLOR_CLOCK_TEXT"].plurals[0] = "Tekst zegara##CC_GUI_COLOR_CLOCK_TEXT";
    strings["Beat (off)##CC_GUI_COLOR_CLOCK_BEAT_LOW"].plurals[0] = "Beat wył.##CC_GUI_COLOR_CLOCK_BEAT_LOW";
    strings["Beat (on)##CC_GUI_COLOR_CLOCK_BEAT_HIGH"].plurals[0] = "Beat wł.##CC_GUI_COLOR_CLOCK_BEAT_HIGH";

    strings["PortSet##CC_GUI_COLOR_PATCHBAY_PORTSET"].plurals[0] = "Grupa portów##CC_GUI_COLOR_PATCHBAY_PORTSET";
    strings["Port##CC_GUI_COLOR_PATCHBAY_PORT"].plurals[0] = "Port##CC_GUI_COLOR_PATCHBAY_PORT";
    strings["Port (hidden/unavailable)##CC_GUI_COLOR_PATCHBAY_PORT_HIDDEN"].plurals[0] = "Port (ukryty/niedostępny)##CC_GUI_COLOR_PATCHBAY_PORT_HIDDEN";
    strings["Connection (selected)##CC_GUI_COLOR_PATCHBAY_CONNECTION"].plurals[0] = "Połączenie (zaznaczone)##CC_GUI_COLOR_PATCHBAY_CONNECTION";
    strings["Connection (other)##CC_GUI_COLOR_PATCHBAY_CONNECTION_BG"].plurals[0] = "Połączenie (inne)##CC_GUI_COLOR_PATCHBAY_CONNECTION_BG";

    strings["Log level: Error##CC_GUI_COLOR_LOGLEVEL_ERROR"].plurals[0] = "Poziom wpisu dziennika: Błąd##CC_GUI_COLOR_LOGLEVEL_ERROR";
    strings["Log level: Warning##CC_GUI_COLOR_LOGLEVEL_WARNING"].plurals[0] = "Poziom wpisu dziennika: Ostrzeżenie##CC_GUI_COLOR_LOGLEVEL_WARNING";
    strings["Log level: Info##CC_GUI_COLOR_LOGLEVEL_INFO"].plurals[0] = "Poziom wpisu dziennika: Info##CC_GUI_COLOR_LOGLEVEL_INFO";
    strings["Log level: Debug##CC_GUI_COLOR_LOGLEVEL_DEBUG"].plurals[0] = "Poziom wpisu dziennika: Debug##CC_GUI_COLOR_LOGLEVEL_DEBUG";
    strings["Log level: Trace/Verbose##CC_GUI_COLOR_LOGLEVEL_TRACE"].plurals[0] = "Poziom wpisu dziennika: Diagnostyka/Szczegóły##CC_GUI_COLOR_LOGLEVEL_TRACE";

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
    strings["Noise Freq##sgiAY"].plurals[0] = "Częstotliwość szumu";
    strings["Waveform##sgiAY"].plurals[0] = "Kształt fali";
    strings["Raw Period##sgiAY"].plurals[0] = "Okres (absolutny)";
    strings["Raw Envelope Period##sgiAY"].plurals[0] = "Okres obwiedni (absolutny)";
    strings["Phase Reset##sgiAY"].plurals[0]  = "Reset fazy";
    strings["Envelope##sgiAY"].plurals[0] = "Obwiednia";
    strings["AutoEnv Num##sgiAY"].plurals[0] = "Licznik częst. auto-obw.";
    strings["AutoEnv Den##sgiAY"].plurals[0] = "Mianownik częst. auto-obw.";

    //   sgi8930   src/gui/inst/ay8930.cpp

    strings["Macros##sgi8930"].plurals[0] = "Makra";
    strings["Volume##sgi8930"].plurals[0] = "Głośność";
    strings["Arpeggio##sgi8930"].plurals[0] = "Arpeggio";
    strings["Pitch##sgi8930"].plurals[0] = "Wysokość";
    strings["Noise Freq##sgi8930"].plurals[0] = "Częstotliwość szumu";
    strings["Waveform##sgi8930"].plurals[0] = "Kształt fali";
    strings["Raw Period##sgiAY"].plurals[0] = "Okres (absolutny)";
    strings["Raw Envelope Period##sgiAY"].plurals[0] = "Okres obwiedni (absolutny)";
    strings["Phase Reset##sgi8930"].plurals[0]  = "Reset fazy";
    strings["Duty##sgi8930"].plurals[0] = "Szerokość fali prostokątnej";
    strings["Envelope##sgi8930"].plurals[0] = "Obwiednia";
    strings["AutoEnv Num##sgi8930"].plurals[0] = "Licznik. częst. auto-obwiedni";
    strings["AutoEnv Den##sgi8930"].plurals[0] = "Mianownik. częst. auto-obwiedni";
    strings["Noise AND Mask##sgi8930"].plurals[0] = "Maska szumu (logiczne AND)";
    strings["Noise OR Mask##sgi8930"].plurals[0] = "Maska szumu (logiczne OR)";

        //   sgiB      src/gui/inst/beeper.cpp

    strings["Macros##sgiB"].plurals[0] = "Makra";
    strings["Volume##sgiB"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiB"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiB"].plurals[0] = "Wysokość";
    strings["Pulse Width##sgiB"].plurals[0] = "Szerokość fali prostokątnej";

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
    strings["pulse##sgiC64"].plurals[0] = "prostokątna";
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
    strings["Duty##sgiC640"].plurals[0] = "Szerokość fali prost.";
    strings["Ring Modulation##sgiC64"].plurals[0] = "Modulacja kołowa";
    strings["Oscillator Sync##sgiC64"].plurals[0] = "Synchronizacja oscylotorów";
    strings["Enable filter##sgiC64"].plurals[0] = "Włącz filtr";
    strings["Initialize filter##sgiC64"].plurals[0] = "Inicjalizuj filtr";
    strings["Cutoff##sgiC640"].plurals[0] = "Punkt odcięcia";
    strings["Resonance##sgiC640"].plurals[0] = "Rezonans)";
    strings["Filter Mode##sgiC640"].plurals[0] = "typ filtra";
    strings["low##sgiC64"].plurals[0] = "dolno";
    strings["band##sgiC64"].plurals[0] = "środk.";
    strings["high##sgiC64"].plurals[0] = "górno";
    strings["ch3off##sgiC64"].plurals[0] = "wył. kanał 3";
    strings["Absolute Cutoff Macro##sgiC64"].plurals[0] = "Absolutne makro punktu odcięcia";
    strings["Absolute Duty Macro##sgiC64"].plurals[0] = "Absolutne makro szerokości fali prost.";
    strings["Don't test before new note##sgiC64"].plurals[0] = "Nie włączaj bitu testowego przed nową nutą";
    strings["Macros##sgiC64"].plurals[0] = "Makra";
    strings["Volume##sgiC64"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiC64"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiC64"].plurals[0] = "Wysokość";
    strings["Duty##sgiC641"].plurals[0] = "Szerokość fali prost.";
    strings["Waveform##sgiC641"].plurals[0] = "Kształt fali";
    strings["Cutoff##sgiC641"].plurals[0] = "Punkt odcięcia";
    strings["Filter Mode##sgiC641"].plurals[0] = "Typ filtra";
    strings["Filter Toggle##sgiC64"].plurals[0] = "Wł./Wył. filtr";
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
    strings["Noise Freq##sgiDAVE"].plurals[0] = "Częstotliwość szumu";
    strings["Waveform##sgiDAVE"].plurals[0] = "Kształt fali";
    strings["Panning (left)##sgiDAVE"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiDAVE"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiDAVE"].plurals[0] = "Reset fazy";
    strings["Control##sgiDAVE"].plurals[0] = "Sterowanie";
    strings["Raw Frequency##sgiDAVE"].plurals[0] = "Wysokość (absolutna)";

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
    strings["Envelope length##sgiOTTO"].plurals[0] = "Długość obwiedni";
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
    strings["Frequency (F-Num)##sgiESFM"].plurals[0] = "Częstotliwość (F-Num)";
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

    strings["Compatibility mode##sgiFDS"].plurals[0] = "Tryb kompatybilności";
    strings["only use for compatibility with .dmf modules!\n- initializes modulation table with first wavetable\n- does not alter modulation parameters on instrument change##sgiFDS"].plurals[0] = "tylko dla kompatybilności z modułami .dmf!\n- inicjalizuje tablice modulatora wraz z pierwszą tablica fal\n- nie zmienia parametrów modulacji przy zmianie instrumentu";
    strings["Modulation depth##sgiFDS"].plurals[0] = "Głębokość modulacji";
    strings["Modulation speed##sgiFDS"].plurals[0] = "Szybkość modulacji";
    strings["Modulation table##sgiFDS"].plurals[0] = "Tabela modulacji";
    strings["Macros##sgiFDS"].plurals[0] = "Makra";
    strings["Volume##sgiFDS"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiFDS"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiFDS"].plurals[0] = "Wysokość";
    strings["Waveform##sgiFDS"].plurals[0] = "Fala";
    strings["Mod Depth##sgiFDS"].plurals[0] = "Głębokość mod.";
    strings["Mod Speed##sgiFDS"].plurals[0] = "Szybkość mod.";
    strings["Mod Position##sgiFDS"].plurals[0] = "Położenie mod.";

    //   sgifmeu   src/gui/inst/fmEnvUtil.cpp

    strings["left click to restart\nmiddle click to pause\nright click to see algorithm##sgifmeu"].plurals[0] = "LPM aby zrestartować\nSPM żeby zatrzymać\nPPM, aby przełączyć na podgląd algorytmu";
    strings["left click to configure TL scaling\nright click to see FM preview##sgifmeu"].plurals[0] = "LPM by skonfigurować skalowanie TL operatora\nPPM, aby przełączyć na podgląd sygnału FM";
    strings["right click to see FM preview##sgifmeu"].plurals[0] = "PPM, aby przełączyć na podgląd sygnału FM";
    strings["operator level changes with volume?##sgifmeu"].plurals[0] = "poziom operatora ma się zmieniać wraz z głośnością?";
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
    strings["Use software envelope##sgiGB"].plurals[0] = "Używaj obwiedni sprzetowej";
    strings["Initialize envelope on every note##sgiGB"].plurals[0] = "Inicjalizuj obwiednię przy każdej nucie";
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
    strings["Env Length##sgiGB"].plurals[0] = "Długość obwiedni";
    strings["Sound Length##sgiGB1"].plurals[0] = "Długość dzwięku";
    strings["Up##sgiGB1"].plurals[0] = "Góra";
    strings["Down##sgiGB1"].plurals[0] = "Dół";
    strings["Shift##sgiGB"].plurals[0] = "Jak bardzo";
    strings["Speed##sgiGB"].plurals[0] = "Prędkość";
    strings["Up##sgiGB2"].plurals[0] = "Góra";
    strings["Down##sgiGB2"].plurals[0] = "Dół";
    strings["Ticks##sgiGB"].plurals[0] = "Kroki";
    strings["Position##sgiGB"].plurals[0] = "Położenie";
    strings["Macros##sgiGB"].plurals[0] = "Makra";
    strings["Volume##sgiGB2"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiGB"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiGB"].plurals[0] = "Wysokość";
    strings["Duty/Noise##sgiGB"].plurals[0] = "Szerokość fali prost./tryb szumu";
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
    strings["Release##sgimcd"].plurals[0] = "Zwolnienie";
    strings["Bottom##sgimcd1"].plurals[0] = "Min.";
    strings["Top##sgimcd1"].plurals[0] = "Maks.";
    strings["Speed##sgimcd"].plurals[0] = "Prędkość";
    strings["Phase##sgimcd"].plurals[0] = "Faza";
    strings["Shape##sgimcd"].plurals[0] = "Kształt fali";
    strings["Macro type: Sequence##sgimcd"].plurals[0] = "Typ makra: Sekwencja";
    strings["Macro type: ADSR##sgimcd"].plurals[0] = "Typ makra: obwiednia ADSR";
    strings["Macro type: LFO##sgimcd"].plurals[0] = "Typ makra: LFO";
    strings["Macro type: What's going on here?##sgimcd"].plurals[0] = "Typ makra: Co tu się dzieje?";
    strings["Delay/Step Length##sgimcd"].plurals[0] = "Opóźnienie/Długość kroku";
    strings["Step Length (ticks)##IMacroSpeed"].plurals[0] = "Długość kroku (w krokach silnika trackera)##IMacroSpeed";
    strings["Delay##IMacroDelay"].plurals[0] = "Opóźnienie##IMacroDelay";
    strings["Release mode: Active (jump to release pos)##sgimcd"].plurals[0] = "Typ zwolnienia: aktywny (skok do pozycji zwolnienia)";
    strings["Release mode: Passive (delayed release)##sgimcd"].plurals[0] = "Typ zwolnienia: pasywny (opóźnione zwolnienie)";
    strings["Tabs##sgimcd"].plurals[0] = "Zakladki";
    strings["Length##sgimcd"].plurals[0] = "Długość";
    strings["StepLen##sgimcd"].plurals[0] = "Dł. kroku";
    strings["Delay##sgimcd"].plurals[0] = "Opóźnienie";
    strings["The heck? No, this isn't even working correctly...##sgimcd"].plurals[0] = "Co do kurwy?.. Nie, to w ogóle nie działa jak należy...";
    strings["The only problem with that selectedMacro is that it's a bug...##sgimcd"].plurals[0] = "Jedyny problem z tym selectedMacro jest to, że jest to błąd...";
    strings["Single (combo box)##sgimcd"].plurals[0] = "Pojedynczy (lista rozwijana)";

    //   sgiLYNX   src/gui/inst/mikey.cpp

    strings["Macros##sgiLYNX"].plurals[0] = "Makra";
    strings["Volume##sgiLYNX"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiLYNX"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiLYNX"].plurals[0] = "Wysokość";
    strings["Duty/Int##sgiLYNX"].plurals[0] = "Szerokość fali prostokątnej/int.";
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
    strings["Attack Rate##sgiMULPCM"].plurals[0] = "Skala ataku";
    strings["D1R##sgiMULPCM0"].plurals[0] = "D1R";
    strings["D1R##sgiMULPCM1"].plurals[0] = "D1R";
    strings["Decay 1 Rate##sgiMULPCM"].plurals[0] = "Skala opadania 1";
    strings["DL##sgiMULPCM0"].plurals[0] = "DL";
    strings["DL##sgiMULPCM1"].plurals[0] = "D";
    strings["Decay Level##sgiMULPCM"].plurals[0] = "Poziom opadania";
    strings["D2R##sgiMULPCM0"].plurals[0] = "D2R";
    strings["D2R##sgiMULPCM1"].plurals[0] = "D2R";
    strings["Decay 2 Rate##sgiMULPCM"].plurals[0] = "Skala opadania 2";
    strings["RR##sgiMULPCM0"].plurals[0] = "RR";
    strings["RR##sgiMULPCM1"].plurals[0] = "RR";
    strings["Release Rate##sgiMULPCM"].plurals[0] = "Skala zwolnienia";
    strings["RC##sgiMULPCM0"].plurals[0] = "RC";
    strings["RC##sgiMULPCM1"].plurals[0] = "RC";
    strings["Rate Correction##sgiMULPCM"].plurals[0] = "Korekcja skali";
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
    strings["Duty/Noise##sgiNES"].plurals[0] = "Szerokość fali prostokątnej/tryb szumu";
    strings["Phase Reset##sgiNES"].plurals[0] = "Reset fazy";

    //   sgiOPL    src/gui/inst/opl.cpp

    strings["4-op##sgiOPL"].plurals[0] = "4-op";
    strings["Drums##sgiOPL"].plurals[0] = "Perkusja";
    strings["Fixed frequency mode##sgiOPL"].plurals[0] = "Tryb stałej częstotliwości";
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
    strings["Fixed frequency mode##sgiOPLL"].plurals[0] = "Tryb stałej częstotliwosci";
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
    strings["OpMask##sgiOPN"].plurals[0] = "Maska operatorów";
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
    strings["Pulse Width##sgiPMQT"].plurals[0] = "Szerokość fali prostokątnej";

    //   sgiPOKEY  src/gui/inst/pokey.cpp

    strings["16-bit raw period macro##sgiPOKEY"].plurals[0] = "16-bitowe makro absolutnego okresu";
    strings["Macros##sgiPOKEY"].plurals[0] = "Makra";
    strings["Volume##sgiPOKEY"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiPOKEY"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiPOKEY"].plurals[0] = "Wysokość";
    strings["Waveform##sgiPOKEY"].plurals[0] = "Kształt fali";
    strings["Raw Period##sgiPOKEY"].plurals[0] = "Absolutny okres";

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
    strings["Echo Feedback##sgiQ"].plurals[0] = "Feedback echo";
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
    strings["Duty/Noise##sgiSAA"].plurals[0] = "Szerokość fali prostokątnej/szum";
    strings["Waveform##sgiSAA"].plurals[0] = "Kształt fali";
    strings["Panning (left)##sgiSAA"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiSAA"].plurals[0] = "Panning (prawo)";
    strings["Envelope##sgiSAA"].plurals[0] = "Obwiednia";

    //   sgismpd   src/gui/inst/sampleDraw.cpp

    strings["Sample##sgismpd0"].plurals[0] = "Sampel";
    strings["DPCM##sgismpd"].plurals[0] = "DPCM";
    strings["new DPCM features disabled (compatibility)!##sgismpd"].plurals[0] = "nowe funkcje DPCM wyłączone (kompatybilność)!";
    strings["click here to enable them.##sgismpd"].plurals[0] = "klinij tutaj aby je włączyć.";
    strings["none selected##sgismpd"].plurals[0] = "nie wybrano";
    strings["Use sample##sgismpd"].plurals[0] = "Użyj sampla";
    strings["Sample bank slot##BANKSLOT"].plurals[0] = "Numer banka sampli##BANKSLOT";
    strings["Sample##sgismpd1"].plurals[0] = "Sampel";
    strings["Use wavetable (Amiga/SNES/Generic DAC only)##sgismpd"].plurals[0] = "Używaj tablicy fal (tylko dla Amiga/SNES/typowego przetwornika C/A)";
    strings["Width##sgismpd"].plurals[0] = "Szerokość";
    strings["Use sample map##sgismpd"].plurals[0] = "Użyj mapy sampli";
    strings["pitch##sgismpd"].plurals[0] = "wysokość dźwięku";
    strings["loop##sgismpd"].plurals[0] = "pętla";
    strings["delta##sgismpd"].plurals[0] = "delta";
    strings["note##sgismpd"].plurals[0] = "nuta";
    strings["sample name##sgismpd"].plurals[0] = "nazwa sampla";
    strings["L##L%d"].plurals[0] = "L##L%d";
    strings["set entire map to this pitch##sgismpd"].plurals[0] = "ustaw tą wysokość sampla dla całej mapy";
    strings["set entire map to this delta counter value##sgismpd"].plurals[0] = "ustaw tą wartość licznika delta dla całej mapy";
    strings["set entire map to this note##sgismpd"].plurals[0] = "ustaw tą nutę dla całej mapy";
    strings["set entire map to this sample##sgismpd"].plurals[0] = "ustaw ten sampel dla całej mapy";
    strings["reset pitches##sgismpd"].plurals[0] = "zresetuj wysokości dźwięku";
    strings["clear delta counter values##sgismpd"].plurals[0] = "wyczyść wartośći licznika delta";
    strings["reset notes##sgismpd"].plurals[0] = "resetuj nuty";
    strings["clear map samples##sgismpd"].plurals[0] = "wyczyść sample z mapy";

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

     //   sgiSID2   src/gui/inst/sid2.cpp

    strings["Waveform##sgiSID2"].plurals[0] = "Ustaw kształt fali";
    strings["tri##sgiSID2"].plurals[0] = "trójkąt";
    strings["saw##sgiSID2"].plurals[0] = "piła";
    strings["pulse##sgiSID2"].plurals[0] = "fala prost.";
    strings["noise##sgiSID2"].plurals[0] = "szum";
    strings["A##sgiSID2"].plurals[0] = "A";
    strings["D##sgiSID2"].plurals[0] = "D";
    strings["S##sgiSID2"].plurals[0] = "S";
    strings["R##sgiSID2"].plurals[0] = "R";
    strings["VOL##sgiSID2"].plurals[0] = "Gł.";
    strings["Envelope##sgiSID2"].plurals[0] = "Obwiednia";
    strings["Duty##sgiSID2"].plurals[0] = "Szerokość fali prost.";
    strings["Ring Modulation##sgiSID2"].plurals[0] = "Modulacja kołowa";
    strings["Oscillator Sync##sgiSID2"].plurals[0] = "Synchronizacja oscylatorów";
    strings["Enable filter##sgiSID2"].plurals[0] = "Włącz filtr";
    strings["Initialize filter##sgiSID2"].plurals[0] = "Inicjalizuj filtr";
    strings["Cutoff##sgiSID2"].plurals[0] = "Punkt odcięcia";
    strings["Resonance##sgiSID2"].plurals[0] = "Rezonans";
    strings["Filter Mode##sgiSID2"].plurals[0] = "Typ filtru";
    strings["low##sgiSID2"].plurals[0] = "dolno";
    strings["band##sgiSID2"].plurals[0] = "środkowo";
    strings["high##sgiSID2"].plurals[0] = "górno";
    strings["Noise Mode##sgiSID2"].plurals[0] = "Tryb szumu";
    strings["Wave Mix Mode##sgiSID2"].plurals[0] = "Tryb mieszania fali";
    strings["Absolute Cutoff Macro##sgiSID2"].plurals[0] = "Absolutne makro punktu odcięcia";
    strings["Absolute Duty Macro##sgiSID2"].plurals[0] = "Absolutne makro szerokości fali prost.";
    strings["Macros##sgiSID2"].plurals[0] = "Makra";
    strings["Volume##sgiSID2"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiSID2"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiSID2"].plurals[0] = "Wysokość";
    strings["Duty##sgiSID21"].plurals[0] = "Szerokość fali prostokątnej";
    strings["Waveform##sgiSID21"].plurals[0] = "Kształt fali";
    strings["Noise Mode##sgiSID21"].plurals[0] = "Tryb szumu";
    strings["Wave Mix Mode##sgiSID21"].plurals[0] = "Tryb mieszania fali";
    strings["Cutoff##sgiSID21"].plurals[0] = "Punkt odcięcia";
    strings["Filter Mode##sgiSID21"].plurals[0] = "Typ filtra";
    strings["Filter Toggle##sgiSID2"].plurals[0] = "Wł./wył. filtr";
    strings["Resonance##sgiSID21"].plurals[0] = "Rezonans";
    strings["Phase Reset##sgiSID2"].plurals[0] = "Reset fazy";
    strings["Envelope Reset/Key Control##sgiSID2"].plurals[0] = "Reset obwiedni";
    strings["Special##sgiSID2"].plurals[0] = "Specjane";
    strings["Attack##sgiSID2"].plurals[0] = "Atak";
    strings["Decay##sgiSID2"].plurals[0] = "Opadanie";
    strings["Sustain##sgiSID2"].plurals[0] = "Podtrzymanie";
    strings["Release##sgiSID2"].plurals[0] = "Opadanie";

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
    strings["Sustain/release mode:##sgiSNES"].plurals[0] = "Tryb podtrzymania/zwolnienia:";
    strings["Direct (cut on release)##sgiSNES"].plurals[0] = "Bezpośredni (zatrzymaj przy zwolnieniu)";
    strings["Effective (linear decrease)##sgiSNES"].plurals[0] = "Efektywny (liniowe opadanie)";
    strings["Effective (exponential decrease)##sgiSNES"].plurals[0] = "Efektywny (wykładnicze opadanie)";
    strings["Delayed (write R on release)##sgiSNES"].plurals[0] = "Opóźniony (zapis R podczas zwolnienia)";
    strings["Gain Mode##sgiSNES0"].plurals[0] = "Tryb wzmocnienia";
    strings["Gain Mode##sgiSNES1"].plurals[0] = "Tryb wzmocnienia";
    strings["Gain##sgiSNES0"].plurals[0] = "Wzmocnienie";
    strings["Gain##sgiSNES1"].plurals[0] = "Wzmocnienie";
    strings["Direct##sgiSNES"].plurals[0] = "Bezpośrednie";
    strings["Decrease (linear)##sgiSNES"].plurals[0] = "Opadanie (liniowe)";
    strings["Decrease (logarithmic)##sgiSNES"].plurals[0] = "Opadanie (logarytmiczne)";
    strings["Increase (linear)##sgiSNES"].plurals[0] = "Wzrost (liniowy)";
    strings["Increase (bent line)##sgiSNES"].plurals[0] = "Wzrost (zakrzywiony)";
    strings["using decrease modes will not produce any sound at all, unless you know what you are doing.\nit is recommended to use the Gain macro for decrease instead.##sgiSNES"].plurals[0] = "korzystanie z trybów opadania wywoła brak dźwięku, jeśli nie rozumiesz, jak to wszystko działa.\nzaleca się użycie makra wzmocnienia dla opadania.";
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
    strings["Duty##sgiPSG"].plurals[0] = "Szerokość fali prostokątnej";
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
    strings["Sustained##sgistru0"].plurals[0] = "Podtrzymany";
    strings["Sustained##sgistru1"].plurals[0] = "Podtrzymany";
    strings["Level Scaling##sgistru"].plurals[0] = "Skalowanie poziomu";
    strings["Sustain##sgistru1"].plurals[0] = "Podtrzymanie";
    strings["Vibrato##sgistru"].plurals[0] = "Vibrato";
    strings["Waveform##sgistru"].plurals[0] = "Fala";
    strings["Scale Rate##sgistru"].plurals[0] = "Skalowanie stosunku częst.";
    strings["OP2 Half Sine##sgistru"].plurals[0] = "Pół-sinusoida na OP2";
    strings["OP1 Half Sine##sgistru"].plurals[0] = "Pół-sinusoida na OP1";
    strings["EnvShift##sgistru"].plurals[0] = "Przes. obwiedni";
    strings["Reverb##sgistru"].plurals[0] = "Reverb";
    strings["Fine##sgistru0"].plurals[0] = "Dokładne";
    strings["LFO2 > Freq##sgistru"].plurals[0] = "LFO2 > częst.";
    strings["LFO2 > Amp##sgistru"].plurals[0] = "LFO2 > ampl.";
    strings["Fine##sgistru1"].plurals[0] = "Dokładne";
    strings["Fine##sgistru2"].plurals[0] = "Dokładne";
    strings["OP4 Noise Mode##sgistru0"].plurals[0] = "Tryb szumu na OP4";
    strings["Envelope Delay##sgistru"].plurals[0] = "Opóżnienie obwiedni";
    strings["Output Level##sgistru0"].plurals[0] = "Głośność na wyjściu";
    strings["Modulation Input Level##sgistru"].plurals[0] = "Poziom modulacji wyjścia";
    strings["Left Output##sgistru"].plurals[0] = "Lewy kanał";
    strings["Right Output##sgistru"].plurals[0] = "Prawy kanał";
    strings["Coarse Tune (semitones)##sgistru"].plurals[0] = "Przybliżone rozstrojenie (w półtonach)";
    strings["Detune##sgistru1"].plurals[0] = "Rozstrój";
    strings["Fixed Frequency Mode##sgistru"].plurals[0] = "Tryb stałej częstotliwości";
    strings["OP4 Noise Mode##sgistru1"].plurals[0] = "Tryb szumu na OP4";
    strings["Env. Delay##sgistru"].plurals[0] = "Opóżnienie obw.";
    strings["Output Level##sgistru1"].plurals[0] = "Głośność wyjścia";
    strings["ModInput##sgistru"].plurals[0] = "ModInput";
    strings["Left##sgistru"].plurals[0] = "Lewo";
    strings["Right##sgistru"].plurals[0] = "Prawo";
    strings["Tune##sgistru"].plurals[0] = "Strojenie";
    strings["Detune##sgistru2"].plurals[0] = "Rozstrój";
    strings["Fixed##sgistru0"].plurals[0] = "Stały";
    strings["Fine##sgistru3"].plurals[0] = "Dokładne";
    strings["Fine##sgistru4"].plurals[0] = "Dokładne";
    strings["Fine##sgistru5"].plurals[0] = "Dokładne";
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
    strings["9. Synth Brass##sgistru"].plurals[0] = "9. Syntetyczny instrument dęty";
    strings["10. Electric Piano##sgistru"].plurals[0] = "10. Pianino Elektryczne";
    strings["11. Bass##sgistru"].plurals[0] = "11. Bas";
    strings["12. Vibraphone##sgistru1"].plurals[0] = "12. Wibrafon";
    strings["13. Chime##sgistru"].plurals[0] = "13. Dzwonki";
    strings["14. Tom Tom II##sgistru"].plurals[0] = "14. Tom-tom 2";
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
    strings["10. Synth Brass##sgistru"].plurals[0] = "10. Syntetyczny instrument dęty";
    strings["11. Short Saw##sgistru"].plurals[0] = "11. Krótka piła";
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
    strings["12. Brass##sgistru"].plurals[0] = "12. Instrument dęty";
    strings["13. Bass Guitar##sgistru"].plurals[0] = "13. Gitara basowa";
    strings["14. Synth##sgistru"].plurals[0] = "14. Syntezator";
    strings["15. Chorus##sgistru"].plurals[0] = "15. Chór";
    strings["Drums##sgistru3"].plurals[0] = "Perkusja";
    strings["Sine##sgistru0"].plurals[0] = "Sinusoida";
    strings["Half Sine##sgistru0"].plurals[0] = "Połowa sinusoidy";
    strings["Absolute Sine##sgistru0"].plurals[0] = "Moduł sinusoidy";
    strings["Quarter Sine##sgistru"].plurals[0] = "Cwierć sinusoidy";
    strings["Squished Sine##sgistru0"].plurals[0] = "Spłaszczona sinusoida";
    strings["Squished AbsSine##sgistru0"].plurals[0] = "Spł. moduł sinusoidy";
    strings["Square##sgistru0"].plurals[0] = "Fala kwadratowa";
    strings["Derived Square##sgistru0"].plurals[0] = "Pochodna fali kwadratowej";
    strings["Sine##sgistru1"].plurals[0] = "Sinusoida";
    strings["Half Sine##sgistru1"].plurals[0] = "Połowa sinusoidy";
    strings["Absolute Sine##sgistru1"].plurals[0] = "Moduł sinusoidy";
    strings["Pulse Sine##sgistru"].plurals[0] = "Puls sinusoidalny";
    strings["Sine (Even Periods)##sgistru"].plurals[0] = "Sinusoida (parzyste okresy)";
    strings["AbsSine (Even Periods)##sgistru"].plurals[0] = "Moduł sinusoidy (parzyste okresy)";
    strings["Square##sgistru1"].plurals[0] = "Fala kwadratowa";
    strings["Derived Square##sgistru1"].plurals[0] = "Pochodna fali kwadratowej";
    strings["Sine##sgistru2"].plurals[0] = "Sinusoida";
    strings["Triangle##sgistru"].plurals[0] = "Fala trójkątna";
    strings["Cut Sine##sgistru"].plurals[0] = "Obcięta sinusoida";
    strings["Cut Triangle##sgistru"].plurals[0] = "Obc. fala trójkątna";
    strings["Squished Sine##sgistru1"].plurals[0] = "Spłaszczona sinusoida";
    strings["Squished Triangle##sgistru"].plurals[0] = "Spłaszczona fala trójkątna";
    strings["Squished AbsSine##sgistru1"].plurals[0] = "Spł. moduł sinusoidy";
    strings["Squished AbsTriangle##sgistru"].plurals[0] = "Spł. moduł fali trójk.";
    strings["Snare##sgistru0"].plurals[0] = "Werbel";
    strings["Tom##sgistru"].plurals[0] = "Tom-tom";
    strings["Top##sgistru0"].plurals[0] = "Talerz";
    strings["HiHat##sgistru0"].plurals[0] = "Hi-hat";
    strings["Normal##sgistru"].plurals[0] = "Zwykły";
    strings["Snare##sgistru1"].plurals[0] = "Werbel";
    strings["HiHat##sgistru1"].plurals[0] = "Hi-hat";
    strings["Top##sgistru1"].plurals[0] = "Talerz";
    strings["Noise disabled##sgistru"].plurals[0] = "Szum wyłączony";
    strings["Square + noise##sgistru"].plurals[0] = "Fala kwadratowa + szum";
    strings["Ringmod from OP3 + noise##sgistru"].plurals[0] = "Modulacja kołowa od OP3 + szum";
    strings["Ringmod from OP3 + double pitch ModInput\nWARNING - has emulation issues, subject to change##sgistru"].plurals[0] = "Modulacja kołowa od OP3 + ModInput z podwojoną wysokością dźwięku\nUWAGA - występują problemy z emulacją tego trybu, może on ulec zmianie";
    strings["op1##sgistru"].plurals[0] = "op1";
    strings["op2##sgistru"].plurals[0] = "op2";
    strings["op3##sgistru"].plurals[0] = "op3";
    strings["op4##sgistru"].plurals[0] = "op4";
    strings["triangle##sgistru"].plurals[0] = "fala trójkątna";
    strings["saw##sgistru"].plurals[0] = "fala piłokszt.";
    strings["pulse##sgistru"].plurals[0] = "fala kwadratowa";
    strings["noise##sgistru0"].plurals[0] = "szum";
    strings["tone##sgistru"].plurals[0] = "ton";
    strings["noise##sgistru1"].plurals[0] = "szum";
    strings["envelope##sgistru"].plurals[0] = "obwiednia";
    strings["hold##sgistru"].plurals[0] = "podtrzymanie";
    strings["alternate##sgistru"].plurals[0] = "zmiana";
    strings["direction##sgistru0"].plurals[0] = "kierunek";
    strings["enable##sgistru0"].plurals[0] = "wł.";
    strings["enabled##sgistru0"].plurals[0] = "wł.";
    strings["mirror##sgistru"].plurals[0] = "odbicie";
    strings["loop##sgistru0"].plurals[0] = "pętla";
    strings["cut##sgistru"].plurals[0] = "odcięcie";
    strings["direction##sgistru1"].plurals[0] = "kierunek";
    strings["resolution##sgistru"].plurals[0] = "rozdzielczość";
    strings["fixed##sgistru1"].plurals[0] = "stały";
    strings["N/A##sgistru"].plurals[0] = "-";
    strings["enabled##sgistru1"].plurals[0] = "wł.";
    strings["noise##sgistru2"].plurals[0] = "szum";
    strings["echo##sgistru"].plurals[0] = "echo";
    strings["pitch mod##sgistru"].plurals[0] = "mod. wysokości dźw.";
    strings["invert right##sgistru"].plurals[0] = "odwróć prawo";
    strings["invert left##sgistru"].plurals[0] = "odwróć lewo";
    strings["low##sgistru"].plurals[0] = "dolno";
    strings["band##sgistru"].plurals[0] = "środk.";
    strings["high##sgistru"].plurals[0] = "górno";
    strings["ch3off##sgistru"].plurals[0] = "wył. 3 kanał";
    strings["gate##sgistru"].plurals[0] = "bramka obw.";
    strings["sync##sgistru"].plurals[0] = "synchro.";
    strings["ring##sgistru"].plurals[0] = "mod. kołowa";
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
    strings["square##sgistru2"].plurals[0] = "fala kwadratowa";
    strings["noise##sgistru3"].plurals[0] = "szum";
    strings["noise##sgistru4"].plurals[0] = "szum";
    strings["invert##sgistru"].plurals[0] = "inwersja";
    strings["surround##sgistru"].plurals[0] = "przestrzenny";
    strings["enable##sgistru1"].plurals[0] = "wł.";
    strings["oneshot##sgistru"].plurals[0] = "jednokrotny";
    strings["split L/R##sgistru"].plurals[0] = "rozdzielenie lewo./prawo";
    strings["HinvR##sgistru"].plurals[0] = "HinvR";
    strings["VinvR##sgistru"].plurals[0] = "VinvR";
    strings["HinvL##sgistru"].plurals[0] = "HinvL";
    strings["VinvL##sgistru"].plurals[0] = "VinvL";
    strings["ring mod##sgistru"].plurals[0] = "mod. kołowa";
    strings["low pass##sgistru"].plurals[0] = "dolnoprzepustowy";
    strings["high pass##sgistru"].plurals[0] = "górnoprzepustowy";
    strings["band pass##sgistru"].plurals[0] = "środkowoprzepustowy";
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
    strings["clip B##sgistru"].plurals[0] = "przytnij B";
    strings["clip A##sgistru"].plurals[0] = "przytnij A";
    strings["on##sgistru"].plurals[0] = "wł.";
    strings["k1 slowdown##sgistru"].plurals[0] = "spowolnienie k1";
    strings["k2 slowdown##sgistru"].plurals[0] = "spowolnienie k2";
    strings["pause##sgistru"].plurals[0] = "stop";
    strings["reverse##sgistru"].plurals[0] = "odwr. kierunek";
    strings["high pass##sgistru1"].plurals[0] = "górno-przepustowy";
    strings["ring mod##sgistru1"].plurals[0] = "modulacja kołowa";
    strings["swap counters (noise)##sgistru"].plurals[0] = "zamień liczniki (szum)";
    strings["sync##sgistru1"].plurals[0] = "synchro";
    strings["ring##sgistru1"].plurals[0] = "mod. kołowa";
    strings["low##sgistru1"].plurals[0] = "dolnop.";
    strings["band##sgistru1"].plurals[0] = "środkowop.";
    strings["high##sgistru1"].plurals[0] = "górnop.";
    strings["8580 SID##sgistru"].plurals[0] = "8580 SID";
    strings["bitwise AND##sgistru"].plurals[0] = "bitowe AND";
    strings["bitwise OR##sgistru"].plurals[0] = "bitowe OR";
    strings["bitwise XOR##sgistru"].plurals[0] = "bitowe XOR";
    strings["low pass (noise)##sgistru"].plurals[0] = "dolnoprzepustowy (szum)";
    strings["None##sgistru"].plurals[0] = "Brak";
    strings["Invert##sgistru"].plurals[0] = "Odwróć";
    strings["Add##sgistru"].plurals[0] = "Dodaj";
    strings["Subtract##sgistru"].plurals[0] = "Odejmij";
    strings["Average##sgistru"].plurals[0] = "Uśrednij";
    strings["Phase##sgistru"].plurals[0] = "Faza";
    strings["Chorus##sgistru"].plurals[0] = "Chór";
    strings["None (dual)##sgistru"].plurals[0] = "Brak (podwójna tablica)";
    strings["Wipe##sgistru"].plurals[0] = "Wzajemne wymazywanie";
    strings["Fade##sgistru"].plurals[0] = "Transformacja";
    strings["Fade (ping-pong)##sgistru"].plurals[0] = "Transformacja (tam i z powr.)";
    strings["Overlay##sgistru"].plurals[0] = "Nakładanie";
    strings["Negative Overlay##sgistru"].plurals[0] = "Odwrotne nakładanie";
    strings["Slide##sgistru"].plurals[0] = "Zjazd";
    strings["Mix Chorus##sgistru"].plurals[0] = "Miksowanie (chór)";
    strings["Phase Modulation##sgistru"].plurals[0] = "Modulacja fazy";
    strings["Envelope##sgistru"].plurals[0] = "Obwiednia";
    strings["Sweep##sgistru"].plurals[0] = "Sprz. portamento";
    strings["Wait##sgistru0"].plurals[0] = "Czekaj";
    strings["Wait for Release##sgistru0"].plurals[0] = "Czekaj na zwolnienie";
    strings["Loop##sgistru1"].plurals[0] = "Pętla";
    strings["Loop until Release##sgistru0"].plurals[0] = "Zapętlaj aż do zwolnienie";
    strings["Volume Sweep##sgistru"].plurals[0] = "Płynna zmiana głośności";
    strings["Frequency Sweep##sgistru"].plurals[0] = "Płynna zmiana częstotliwości";
    strings["Cutoff Sweep##sgistru"].plurals[0] = "Płynna zmiana punktu odcięcia";
    strings["Wait##sgistru1"].plurals[0] = "Czekaj";
    strings["Wait for Release##sgistru1"].plurals[0] = "Czekaj na zwolnienie";
    strings["Loop##sgistru2"].plurals[0] = "Pętla";
    strings["Loop until Release##sgistru1"].plurals[0] = "Zapętlaj aż do zwolnienie";
    strings["Direct##sgistru"].plurals[0] = "Bezpośrednie";
    strings["Decrease (linear)##sgistru"].plurals[0] = "Opadanie (liniowe)";
    strings["Decrease (logarithmic)##sgistru"].plurals[0] = "Opadanie (logarytmiczne)";
    strings["Increase (linear)##sgistru"].plurals[0] = "Wzrost (liniowy)";
    strings["Increase (bent line)##sgistru"].plurals[0] = "Wzrost (zakrzywiony)";
    strings["Fixed##sgistru2"].plurals[0] = "Stałe";
    strings["Relative##sgistru"].plurals[0] = "Względne";
    strings["QSound##sgistru"].plurals[0] = "QSound";
    strings["Bug##sgistru"].plurals[0] = "Błąd";

    strings["Fixed"].plurals[0] = "Stałe";
    strings["Relative"].plurals[0] = "Względne";
    strings["Local"].plurals[0] = "Lokalne";
    strings["Global"].plurals[0] = "Globalne";

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
    strings["Duty/Noise##sgiSU"].plurals[0] = "Szerokość fali prostokątnej/szum";
    strings["Waveform##sgiSU"].plurals[0] = "Fala";
    strings["Panning##sgiSU"].plurals[0] = "Panning";
    strings["Phase Reset##sgiSU"].plurals[0] = "Reset fazy";
    strings["Cutoff##sgiSU"].plurals[0] = "Punkt odcięcia";
    strings["Resonance##sgiSU"].plurals[0] = "Rezonans";
    strings["Control##sgiSU"].plurals[0] = "Sterowanie";
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
    strings["Raw Period##sgiTIA"].plurals[0] = "Absolutny okres";
    strings["Waveform##sgiTIA"].plurals[0] = "Kształt fali";

    //   sgiVB     src/gui/inst/vboy.cpp

    strings["Set modulation table (channel 5 only)##sgiVB"].plurals[0] = "Ustaw tablicę modulacji (tylko dla piątego kanału)";
    strings["Hex##MTHex"].plurals[0] = "Hex.##MTHex";
    strings["Dec##MTHex"].plurals[0] = "Dec.##MTHex";
    strings["Macros##sgiVB"].plurals[0] = "Makra";
    strings["Volume##sgiVB"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiVB"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiVB"].plurals[0] = "Wysokość";
     strings["Noise Length##sgiVB"].plurals[0] = "Długość szumu";
    strings["Waveform##sgiVB"].plurals[0] = "Fala";
    strings["Panning (left)##sgiVB"].plurals[0] = "Panning (lewo)";
    strings["Panning (right)##sgiVB"].plurals[0] = "Panning (prawo)";
    strings["Phase Reset##sgiVB"].plurals[0] = "Reset fazy";

    //   sgiVERA   src/gui/inst/vera.cpp

    strings["Macros##sgiVERA"].plurals[0] = "Makra";
    strings["Volume##sgiVERA"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiVERA"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiVERA"].plurals[0] = "Wysokość";
    strings["Duty##sgiVERA"].plurals[0] = "Szerokość fali prostokątnej";
    strings["Waveform##sgiVERA"].plurals[0] = "Kształt fali";
    strings["Panning##sgiVERA"].plurals[0] = "Panning";

    //   sgiVIC    src/gui/inst/vic.cpp

    strings["Macros##sgiVIC"].plurals[0] = "Makra";
    strings["Volume##sgiVIC"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiVIC"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiVIC"].plurals[0] = "Wysokość";
    strings["On/Off##sgiVIC"].plurals[0] = "Wł./wył.";
    strings["Waveform##sgiVIC"].plurals[0] = "Kształt fali";

    //   sgiVRC6   src/gui/inst/vrc6.cpp

    strings["Macros##sgiVRC6"].plurals[0] = "Makra";
    strings["Volume##sgiVRC6"].plurals[0] = "Głośność";
    strings["Arpeggio##sgiVRC6"].plurals[0] = "Arpeggio";
    strings["Pitch##sgiVRC6"].plurals[0] = "Wysokość";
    strings["Duty##sgiVRC6"].plurals[0] = "Szerokość fali prostokątnej";
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
    strings["Global##sgiwave1"].plurals[0] = "Globalny";
    strings["Global##sgiwave2"].plurals[0] = "Globalny##jesus";
    strings["wavetable synthesizer disabled.\nuse the Waveform macro to set the wave for this instrument.##sgiwave"].plurals[0] = "syntezator tablicowy wyłączony\nużyj makra fali, aby ustawić tablicę fal dla tego instrumentu";
    strings["Local Waves##sgiwave"].plurals[0] = "Lokalne tablice fal";

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
    strings["05xy: Volume slide + vibrato (compatibility only!)##seen"].plurals[0] = "05xy: Zjazd głośności + vibrato (dla kompatybilności!)";
    strings["06xy: Volume slide + portamento (compatibility only!)##seen"].plurals[0] = "06xy: Zjazd głośności + portamento (dla kompatybilności!)";
    strings["07xy: Tremolo (x: speed; y: depth)##seen"].plurals[0] = "07xy: Tremolo (x: szybkość; y: głębokość)";
    strings["08xy: Set panning (x: left; y: right)##seen"].plurals[0] = "08xy: Ustaw panning (x: lewo; y: prawo)";
    strings["09xx: Set groove pattern (speed 1 if no grooves exist)##seen"].plurals[0] = "09xx: Ustaw wzór rytmu (prędkość nr.1 w przypadku ich nieobecności)";
    strings["0Axy: Volume slide (0y: down; x0: up)##seen"].plurals[0] = "0Axy: Zjazd głośności (0y: góra; x0: dół)";
    strings["0Bxx: Jump to pattern##seen"].plurals[0] = "0Bxx: Przeskocz do wzorca";
    strings["0Cxx: Retrigger##seen"].plurals[0] = "0Cxx: Cykliczny restart nuty";
    strings["0Dxx: Jump to next pattern##seen"].plurals[0] = "0Dxx: Przeskocz do nast. wzorca";
    strings["0Fxx: Set speed (speed 2 if no grooves exist)##seen"].plurals[0] = "0Fxx: Ustaw prędkość (prędkość 2 jeśli nie zdefiniowano wzoru rytmu)";
    strings["80xx: Set panning (00: left; 80: center; FF: right)##seen"].plurals[0] = "80xx: Ustaw panning (00: lewo; 80: środek; FF: prawo)";
    strings["81xx: Set panning (left channel)##seen"].plurals[0] = "81xx: Ustaw panning (lewy kanał)";
    strings["82xx: Set panning (right channel)##seen"].plurals[0] = "82xx: Ustaw panning (prawy kanał)";
    strings["88xy: Set panning (rear channels; x: left; y: right)##seen"].plurals[0] = "88xy: Ustaw panning (tylne kanały; x: lewy; y: prawy)";
    strings["89xx: Set panning (rear left channel)##seen"].plurals[0] = "89xx: Ustaw panning (tylny lewy kanał)";
    strings["8Axx: Set panning (rear right channel)##seen"].plurals[0] = "8Axx: Ustaw panning (tylny prawy kanał)";
    strings["Cxxx: Set tick rate (hz)##seen"].plurals[0] = "Cxxx: Ustaw częstotliwość odświeżania utworu (Hz)";
    strings["E0xx: Set arp speed##seen"].plurals[0] = "E0xx: Ustaw sszybkość arpeggio";
    strings["E1xy: Note slide up (x: speed; y: semitones)##seen"].plurals[0] = "E1xy: Portamento nuty w górę (x: szybkość; y: półtony)";
    strings["E2xy: Note slide down (x: speed; y: semitones)##seen"].plurals[0] = "E2xy: Portamento nuty w dół (x: szybkość; y: półtony)";
    strings["E3xx: Set vibrato shape (0: up/down; 1: up only; 2: down only)##seen"].plurals[0] = "E3xx: Ustaw typ vibrato (0: góra/dół; 1: tylko w górę; 2: tylko w dół)";
    strings["E4xx: Set vibrato range##seen"].plurals[0] = "E4xx: Ustaw zakres vibrato";
    strings["E5xx: Set pitch (80: center)##seen"].plurals[0] = "E5xx: Ustaw rozstrojenie (80: brak rozstrojenia)";
    strings["E6xy: Delayed note transpose (x: 0-7 = up, 8-F = down (after (x % 7) ticks); y: semitones)##seen"].plurals[0] = "E6xy: Opóźnione transponowanie nuty (x: 0-7 = w górę, 8-F = w dół (po (x % 7) krokach); y: półtony)";
    strings["EAxx: Legato##seen"].plurals[0] = "EAxx: Legato";
    strings["EBxx: Set LEGACY sample mode bank##seen"].plurals[0] = "EBxx: (PRZESTARZAŁE) Zdefiniuj bank sampli";
    strings["ECxx: Note cut##seen"].plurals[0] = "ECxx: Obcięcie nuty";
    strings["EDxx: Note delay##seen"].plurals[0] = "EDxx: Opóźnienie nuty";
    strings["EExx: Send external command##seen"].plurals[0] = "EExx: Wyślij zewnętrzną komendę";
    strings["F0xx: Set tick rate (bpm)##seen"].plurals[0] = "F0xx: Ustaw tempo utworu (BPM)";
    strings["F1xx: Single tick note slide up##seen"].plurals[0] = "F1xx: Portamento w górę (jeden krok)";
    strings["F2xx: Single tick note slide down##seen"].plurals[0] = "F2xx: Portamento w dół (jeden krok)";
    strings["F3xx: Fine volume slide up##seen"].plurals[0] = "F3xx: Precyzyjny wzrost głośności w górę";
    strings["F4xx: Fine volume slide down##seen"].plurals[0] = "F4xx: Precyzyjny zjazd głośności w dół";
    strings["F5xx: Disable macro (see manual)##seen"].plurals[0] = "F5xx: Wyłącz makro (patrz: instrukcja)";
    strings["F6xx: Enable macro (see manual)##seen"].plurals[0] = "F6xx: Włącz makro (patrz: instrukcja)";
    strings["F7xx: Restart macro (see manual)##seen"].plurals[0] = "F7xx: Zrestartuj makro (patrz: instrukcja)";
    strings["F8xx: Single tick volume slide up##seen"].plurals[0] = "F8xx:  Wzrost głośności w górę (jeden krok)";
    strings["F9xx: Single tick volume slide down##seen"].plurals[0] = "F9xx: Zjazd głośności w dół (jeden krok)";
    strings["FAxx: Fast volume slide (0y: down; x0: up)##seen"].plurals[0] = "FAxx: Szybki zjazd głośności (0y: w górę; x0: w dół)";
    strings["FFxx: Stop song##seen"].plurals[0] = "FFxx: Zatrzymaj utwór";
    strings["9xxx: Set sample offset*256##seen"].plurals[0] = "9xxx: Ustaw przesunięcie pocz. sampla (xxx*256 kroków)";

    //   sesd    src/engine/sysDef.cpp

    strings["20xx: Set channel mode (bit 0: square; bit 1: noise; bit 2: envelope)##sesd"].plurals[0] = "20xx: Ustaw tryb kanału (bit 0: fala kwadratowa; bit 1: szum; bit 2: obwiednia)";
    strings["21xx: Set noise frequency (0 to 1F)##sesd"].plurals[0] = "21xx: Ustaw częstotliwość szumu (0-1F)";
    strings["22xy: Set envelope mode (x: shape, y: enable for this channel)##sesd"].plurals[0] = "22xy: Ustaw tryb obwiedni (x: kształt, y: włącz dla tego kanału)";
    strings["23xx: Set envelope period low byte##sesd"].plurals[0] = "23xx: Ustaw niski bajt okresu obwiedni";
    strings["24xx: Set envelope period high byte##sesd"].plurals[0] = "24xx: Ustaw wysoki bajt okresu obwiedni";
    strings["25xx: Envelope slide up##sesd0"].plurals[0] = "25xx: Portamento obwiedni w górę";
    strings["26xx: Envelope slide down##sesd0"].plurals[0] = "26xx: Portamento obwiedni w dół";
    strings["29xy: Set auto-envelope (x: numerator; y: denominator)##sesd0"].plurals[0] = "29xy: Ustaw auto-obwiednię (x: licznik; y: mianownik)";
    strings["2Exx: Write to I/O port A##sesd"].plurals[0] = "2Exx: Zapisz do portu A I/O";
    strings["2Fxx: Write to I/O port B##sesd"].plurals[0] = "2Fxx: Zapisz do portu B I/O";
    strings["12xx: Set duty cycle (0 to 8)##sesd"].plurals[0] = "12xx: Ustaw szerokość fali prostokątnej (0-8)";
    strings["16xx: Set raw period higher byte##sesd"].plurals[0] = "16xx: Ustaw wysoki bajt absolutnego okresu";
    strings["27xx: Set noise AND mask##sesd"].plurals[0] = "27xx: Maska szumu (logiczne OR)";
    strings["28xx: Set noise OR mask##sesd"].plurals[0] = "28xx: Maska szumu (logiczne OR)";
    strings["2Dxx: NOT TO BE EMPLOYED BY THE COMPOSER##sesd"].plurals[0] = "2Dxx: NIE DO UŻYTKU PRZEZ KOMPOZYTORA";
    strings["30xx: Toggle hard envelope reset on new notes##sesd"].plurals[0] = "30xx: Włącz twardy reset obwiedni przy nowej nucie";
    strings["18xx: Toggle extended channel 3 mode##sesd"].plurals[0] = "18xx: Włącz rozszerzony kanał 3";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd0"].plurals[0] = "17xx: Włącz tryb PCM (PRZESTARZAŁE)";
    strings["DFxx: Set sample playback direction (0: normal; 1: reverse)##sesd0"].plurals[0] = "DFxx: Set kierunek odtwarzania sampli (0: normalny; 1: odwrotny)";
    strings["18xx: Toggle drums mode (1: enabled; 0: disabled)##sesd"].plurals[0] = "18xx: ПWłącz tryb perkusji (1: włączone; 0: wyłączone)";
    strings["11xx: Set feedback (0 to 7)##sesd0"].plurals[0] = "11xx: Ustaw feedback (0-7)";
    strings["12xx: Set level of operator 1 (0 highest, 7F lowest)##sesd"].plurals[0] = "12xx: Ustaw poziom operatora 1 (0 maks., 7F min.)";
    strings["13xx: Set level of operator 2 (0 highest, 7F lowest)##sesd"].plurals[0] = "13xx: Ustaw poziom operatora 2 (0 maks., 7F min.)";
    strings["14xx: Set level of operator 3 (0 highest, 7F lowest)##sesd"].plurals[0] = "14xx: Ustaw poziom operatora 3 (0 maks., 7F min.)";
    strings["15xx: Set level of operator 4 (0 highest, 7F lowest)##sesd"].plurals[0] = "15xx: Ustaw poziom operatora 4 (0 maks., 7F min.)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd0"].plurals[0] = "16xy: Ustaw mnożnik częst. operatora (x: operator (1-4); y: mnożnik)";
    strings["19xx: Set attack of all operators (0 to 1F)##sesd"].plurals[0] = "19xx: Ustaw atak wszystkich operatorów (0-1F)";
    strings["1Axx: Set attack of operator 1 (0 to 1F)##sesd"].plurals[0] = "1Axx: Ustaw atak operatora 1 (0-1F)";
    strings["1Bxx: Set attack of operator 2 (0 to 1F)##sesd"].plurals[0] = "1Bxx: Ustaw atak operatora 2 (0-1F)";
    strings["1Cxx: Set attack of operator 3 (0 to 1F)##sesd"].plurals[0] = "1Cxx: Ustaw atak operatora 3 (0-1F)";
    strings["1Dxx: Set attack of operator 4 (0 to 1F)##sesd"].plurals[0] = "1Dxx: Ustaw atak operatora 4 (0-1F)";
    strings["50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd0"].plurals[0] = "50xy: Ustaw AM (x: operator 1-4 (0 dla wszystkich operatorów); y: AM)";
    strings["51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd0"].plurals[0] = "51xy: Ustaw poziom podtrzymania (x: operator 1-4 (0 dla wszystkich operatorów); y: poziom)";
    strings["52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd0"].plurals[0] = "52xy: Ustaw opadanie (x: operator 1-4 (0 dla wszystkich operatorów); y: opadanie)";
    strings["53xy: Set detune (x: operator from 1 to 4 (0 for all ops); y: detune where 3 is center)##sesd"].plurals[0] = "53xy: Ustaw rozstrojenie (x: operator 1-4 (0 dla wszystkich operatorów); y: rozstrojenie (3 - brak rozstrojenia))";
    strings["54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd0"].plurals[0] = "54xy:  Ustaw skalowanie obwiedni (x: operator 1-4 (0 dla wszystkich operatorów); y: maks. 0-3)";
    strings["56xx: Set decay of all operators (0 to 1F)##sesd"].plurals[0] = "56xx: Ustaw opadanie wszystkich operatorów (0-1F)";
    strings["57xx: Set decay of operator 1 (0 to 1F)##sesd"].plurals[0] = "57xx: Ustaw opadanie operatora 1 (0-1F)";
    strings["58xx: Set decay of operator 2 (0 to 1F)##sesd"].plurals[0] = "58xx: Ustaw opadanie operatora 2 (0-1F)";
    strings["59xx: Set decay of operator 3 (0 to 1F)##sesd"].plurals[0] = "59xx: Ustaw opadanie operatora 3 (0-1F)";
    strings["5Axx: Set decay of operator 4 (0 to 1F)##sesd"].plurals[0] = "5Axx: Ustaw opadanie operatora 4 (0-1F)";
    strings["5Bxx: Set decay 2 of all operators (0 to 1F)##sesd"].plurals[0] = "5Bxx: Ustaw wtórne opadanie wszystkich operatorów (0-1F)";
    strings["5Cxx: Set decay 2 of operator 1 (0 to 1F)##sesd"].plurals[0] = "5Cxx: Ustaw wtórne opadanie operatora 1 (0-1F)";
    strings["5Dxx: Set decay 2 of operator 2 (0 to 1F)##sesd"].plurals[0] = "5Dxx: Ustaw wtórne opadanie operatora 2 (0-1F)";
    strings["5Exx: Set decay 2 of operator 3 (0 to 1F)##sesd"].plurals[0] = "5Exx: Ustaw wtórne opadanie operatora 3 (0-1F)";
    strings["5Fxx: Set decay 2 of operator 4 (0 to 1F)##sesd"].plurals[0] = "5Fxx: Ustaw wtórne opadanie operatora 4 (0-1F)";
    strings["10xx: Set noise frequency (xx: value; 0 disables noise)##sesd"].plurals[0] = "10xx: Ustaw częstotliwość szumu (xx: wartość; 0 wyłącza szum)";
    strings["17xx: Set LFO speed##sesd"].plurals[0] = "17xx: Ustaw prędkość LFO";
    strings["18xx: Set LFO waveform (0 saw, 1 square, 2 triangle, 3 noise)##sesd"].plurals[0] = "18xx: Ustaw kształt fali LFO (0 fala piłokszt., 1 fala kwadratowa, 2 fala trójkątna, 3 szum)";
    strings["1Exx: Set AM depth (0 to 7F)##sesd"].plurals[0] = "1Exx: Ustaw głębokość AM (0-7F)";
    strings["1Fxx: Set PM depth (0 to 7F)##sesd"].plurals[0] = "1Fxx: Ustaw głębokość PM (0-7F)";
    strings["55xy: Set detune 2 (x: operator from 1 to 4 (0 for all ops); y: detune from 0 to 3)##sesd"].plurals[0] = "55xy: Ustaw roztrojenie 2 (x: operator 1-4 (0 dla wszystkich operatorów); y: roztrojenie 0-3)";
    strings["24xx: Set LFO 2 speed##sesd"].plurals[0] = "24xx: Ustaw prędkość LFO 2";
    strings["25xx: Set LFO 2 waveform (0 saw, 1 square, 2 triangle, 3 noise)##sesd"].plurals[0] = "25xx: Ustaw kształt fali LFO 2 (0 fala piłokszt., 1 fala kwadratowa, 2 fala trójkątna, 3 szum)";
    strings["26xx: Set AM 2 depth (0 to 7F)##sesd"].plurals[0] = "26xx: Ustaw głębokość AM 2 (0-7F)";
    strings["27xx: Set PM 2 depth (0 to 7F)##sesd"].plurals[0] = "27xx: Ustaw głębokość PM 2 (0-7F)";
    strings["28xy: Set reverb (x: operator from 1 to 4 (0 for all ops); y: reverb from 0 to 7)##sesd"].plurals[0] = "28xy: Ustaw reverb (x: operator 1-4 (0 dla wszystkich operatorów); y: reverb 0-7)";
    strings["2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 7)##sesd0"].plurals[0] = "2Axy: Ustaw kształt fali (x: operator 1-4 (0 dla wszystkich operatorów); y: kształt fali 0-7)";
    strings["2Bxy: Set envelope generator shift (x: operator from 1 to 4 (0 for all ops); y: shift from 0 to 3)##sesd"].plurals[0] = "2Bxy: Ustaw przesunięcie generatora obwiedni (x: operator 1-4 (0 dla wszystkich operatorów); y: przesunięcie 0-3)";
    strings["2Cxy: Set fine multiplier (x: operator from 1 to 4 (0 for all ops); y: fine)##sesd"].plurals[0] = "2Cxy: Ustaw mnożnik dokładności(x: operator 1-4 (0 dla wszystkich operatorów); y: mnożnik)";
    strings["3xyy: Set fixed frequency of operator 1 (x: octave from 0 to 7; y: frequency)##sesd"].plurals[0] = "3xyy: Ustaw stalą częstotliwość operatora 1 (x: oktawa 0-7; y: częstotliwość)";
    strings["3xyy: Set fixed frequency of operator 2 (x: octave from 8 to F; y: frequency)##sesd"].plurals[0] = "3xyy: Ustaw stalą częstotliwość operatora operatora 2 (x: oktawa 8-F; y: częstotliwość)";
    strings["4xyy: Set fixed frequency of operator 3 (x: octave from 0 to 7; y: frequency)##sesd"].plurals[0] = "4xyy: Ustaw stalą częstotliwość operatora operatora 3 (x: oktawa 0-7; y: częstotliwość)";
    strings["4xyy: Set fixed frequency of operator 4 (x: octave from 8 to F; y: frequency)##sesd"].plurals[0] = "4xyy: Ustaw stalą częstotliwość operatora operatora 4 (x: oktawa 8-F; y: częstotliwość)";
    strings["10xy: Setup LFO (x: enable; y: speed)##sesd"].plurals[0] = "10xy: Ustaw LFO (x: włączone; y: szybkość)";
    strings["55xy: Set SSG envelope (x: operator from 1 to 4 (0 for all ops); y: 0-7 on, 8 off)##sesd"].plurals[0] = "55xy: Ustaw obwiednię SSG (x: operator 1-4 (0 dla wszystkich operatorów); y: 0-7 wł., 8 wył.)";
    strings["1Fxx: Set ADPCM-A global volume (0 to 3F)##sesd"].plurals[0] = "1Fxx: Ustaw globalną głośność ADPCM-A (0-3F)";
    strings["11xx: Set feedback (0 to 7)##sesd1"].plurals[0] = "11xx: Ustaw feedback (0-7)";
    strings["12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd0"].plurals[0] = "12xx: Ustaw poziom operatora 1 (0 maks., 3F min.)";
    strings["13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd0"].plurals[0] = "13xx: Ustaw poziom operatora 2 (0 maks., 3F min.)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 2; y: multiplier)##sesd"].plurals[0] = "16xy:  Ustaw mnożnik częst. operatora (x: operator 1-2; y: mnożnik)";
    strings["19xx: Set attack of all operators (0 to F)##sesd0"].plurals[0] = "19xx: Ustaw atak wszystkich operatorów (0-F)";
    strings["1Axx: Set attack of operator 1 (0 to F)##sesd0"].plurals[0] = "1Axx: Ustaw atak operatora 1 (0-F)";
    strings["1Bxx: Set attack of operator 2 (0 to F)##sesd0"].plurals[0] = "1Bxx: Ustaw atak operatora 2 (0-F)";
    strings["50xy: Set AM (x: operator from 1 to 2 (0 for all ops); y: AM)##sesd"].plurals[0] = "50xy: Włącz AM (x: operator 1-2 (0 dla wszystkich operatorów); y: AM)";
    strings["51xy: Set sustain level (x: operator from 1 to 2 (0 for all ops); y: sustain)##sesd"].plurals[0] = "51xy: Ustaw poziom podtrzymania (x: operator 1-2 (0 dla wszystkich operatorów); y: podtrzymanie)";
    strings["52xy: Set release (x: operator from 1 to 2 (0 for all ops); y: release)##sesd"].plurals[0] = "52xy: Ustaw zwolnienie (x: operator 1-2 (0 dla wszystkich operatorów); y: zwolnienie)";
    strings["53xy: Set vibrato (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd"].plurals[0] = "53xy: Vibrato (x: operator 1-2 (0 dla wszystkich operatorów); y: wł.)";
    strings["54xy: Set envelope scale (x: operator from 1 to 2 (0 for all ops); y: scale from 0 to 3)##sesd"].plurals[0] = "54xy: Ustaw skalowanie obwiedni (x: operator 1-2 (0 dla wszystkich operatorów); y: skala 0-3)";
    strings["55xy: Set envelope sustain (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd"].plurals[0] = "55xy: Ustaw podtrzymanie obwiedni (x: operator 1-2 (0 dla wszystkich operatorów); y: wł.)";
    strings["56xx: Set decay of all operators (0 to F)##sesd0"].plurals[0] = "56xx: Ustaw opadanie wszystkich operatorów (0-F)";
    strings["57xx: Set decay of operator 1 (0 to F)##sesd0"].plurals[0] = "57xx: Ustaw opadanie operatora 1 (0-F)";
    strings["58xx: Set decay of operator 2 (0 to F)##sesd0"].plurals[0] = "58xx: Ustaw opadanie operatora 2 (0-F)";
    strings["5Bxy: Set whether key will scale envelope (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd"].plurals[0] = "5Bxy: Ustaw skalowanie obwiedni wg. nuty (x: operator 1-2 (0 dla wszystkich operatorów); y: wł.)";
    strings["10xx: Set global AM depth (0: 1dB, 1: 4.8dB)##sesd"].plurals[0] = "10xx: Ustaw globalną głebokość AM (0: 1 dB, 1: 4.8 dB)";
    strings["11xx: Set feedback (0 to 7)##sesd2"].plurals[0] = "11xx: Ustaw sprz. zwrotne (0-7)";
    strings["12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd1"].plurals[0] = "12xx: Ustaw poziom operatora 1 (0 maks., 3F min.)";
    strings["13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd1"].plurals[0] = "13xx: Ustaw poziom operatora 2 (0 maks., 3F min.)";
    strings["14xx: Set level of operator 3 (0 highest, 3F lowest)##sesd0"].plurals[0] = "14xx: Ustaw poziom operatora 3 (0 maks., 3F min.)";
    strings["15xx: Set level of operator 4 (0 highest, 3F lowest)##sesd0"].plurals[0] = "15xx: Ustaw poziom operatora 4 (0 maks., 3F min.)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd1"].plurals[0] = "16xy:  Ustaw mnożnik częst. operatora (x: operator 1-4; y: mnożnik)";
    strings["17xx: Set global vibrato depth (0: normal, 1: double)##sesd"].plurals[0] = "17xx: Ustaw globalną głębokość vibrato (0: normalna, 1: podwójna)";
    strings["19xx: Set attack of all operators (0 to F)##sesd1"].plurals[0] = "19xx: Ustaw atak wszystkich operatorów (0-F)";
    strings["1Axx: Set attack of operator 1 (0 to F)##sesd1"].plurals[0] = "1Axx: Ustaw atak operatora 1 (0-F)";
    strings["1Bxx: Set attack of operator 2 (0 to F)##sesd1"].plurals[0] = "1Bxx: Ustaw atak operatora 2 (0-F)";
    strings["1Cxx: Set attack of operator 3 (0 to F)##sesd0"].plurals[0] = "1Cxx: Ustaw atak operatora 3 (0-F)";
    strings["1Dxx: Set attack of operator 4 (0 to F)##sesd0"].plurals[0] = "1Dxx: Ustaw atak operatora 4 (0-F)";
    strings["2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 3 in OPL2 and 0 to 7 in OPL3)##sesd"].plurals[0] = "2Axy: Ustaw kształt fali (x: operator 1-4 (0 dla wszystkich operatorów); y: kształt fali 0-3 dla OPL2 i 0-7 dla OPL3)";
    strings["50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd1"].plurals[0] = "50xy: Ustaw AM (x: operator 1-4 (0 dla wszystkich operatorów); y: AM)";
    strings["51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd1"].plurals[0] = "51xy: Ustaw poziom podtrzymania (x: operator 1-4 (0 dla wszystkich operatorów); y: podtrzymanie)";
    strings["52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd1"].plurals[0] = "52xy: Ustaw zwolnienie (x: operator 1-4 (0 dla wszystkich operatorów); y: zwolnienie)";
    strings["53xy: Set vibrato (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0"].plurals[0] = "53xy: Ustaw vibrato (x: operator 1-4 (0 dla wszystkich operatorów); y: wł.)";
    strings["54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd1"].plurals[0] = "54xy: Ustaw skalowanie obwiedni (x: operator 1-4 (0 dla wszystkich operatorów); y: skala 0-3)";
    strings["55xy: Set envelope sustain (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0"].plurals[0] = "55xy: Ustaw podtrzymanie obwiedni (x: operator 1-4 (0 dla wszystkich operatorów); y: wł.)";
    strings["56xx: Set decay of all operators (0 to F)##sesd1"].plurals[0] = "56xx: Ustaw opadanie wszystkich operatorów (0-F)";
    strings["57xx: Set decay of operator 1 (0 to F)##sesd1"].plurals[0] = "57xx: Ustaw opadanie operatora 1 (0-F)";
    strings["58xx: Set decay of operator 2 (0 to F)##sesd1"].plurals[0] = "58xx: Ustaw opadanie operatora 2 (0-F)";
    strings["59xx: Set decay of operator 3 (0 to F)##sesd0"].plurals[0] = "59xx: Ustaw opadanie operatora 3 (0-F)";
    strings["5Axx: Set decay of operator 4 (0 to F)##sesd0"].plurals[0] = "5Axx: Ustaw opadanie operatora 4 (0-F)";
    strings["5Bxy: Set whether key will scale envelope (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0"].plurals[0] = "5Bxy: Ustaw skalowanie obwiedni wg. nuty (x: operator 1-4 (0 dla wszystkich operatorów); y: wł.)";
    strings["10xx: Set waveform (bit 0: triangle; bit 1: saw; bit 2: pulse; bit 3: noise)##sesd"].plurals[0] = "10xx: Ustaw kształt fali (bit 0: trójkątna; bit 1: piłokształtna; bit 2: prostokątna; bit 3: szum)";
    strings["11xx: Set coarse cutoff (not recommended; use 4xxx instead)##sesd"].plurals[0] = "11xx: Ustaw przybliżony punkt odcięcia (niezalecane, proszę używać 4xxx)";
    strings["12xx: Set coarse pulse width (not recommended; use 3xxx instead)##sesd"].plurals[0] = "12xx: Ustaw przybliżoną szerokość fali prost. (niezalecane, proszę używać 3xxx)";
    strings["13xx: Set resonance (0 to F)##sesd"].plurals[0] = "13xx: Ustaw rezonans (0-F)";
    strings["14xx: Set filter mode (bit 0: low pass; bit 1: band pass; bit 2: high pass)##sesd"].plurals[0] = "14xx: Ustaw tryb filtra (bit 0: dolno-; bit 1: środkowo-; bit 2: górnoprzepustowy)";
    strings["15xx: Set envelope reset time##sesd"].plurals[0] = "15xx: Ustaw czas resetu obwiedni";
    strings["1Axx: Disable envelope reset for this channel (1 disables; 0 enables)##sesd"].plurals[0] = "1Axx: Wyłącz reset obwiedni dla tego kanału (1 wył.; 0 wł.)";
    strings["1Bxy: Reset cutoff (x: on new note; y: now)##sesd"].plurals[0] = "1Bxy: Zresetuj punkt odcięcia (x: od nowej nuty; y: teraz)";
    strings["1Cxy: Reset pulse width (x: on new note; y: now)##sesd"].plurals[0] = "1Cxy: Zresetuj szerokość fali prost. (x: od nowej nuty; y: teraz)";
    strings["1Exy: Change other parameters (LEGACY)##sesd"].plurals[0] = "1Exy: Zmień inne parametry (PRZESTARZAŁE)";
    strings["20xy: Set attack/decay (x: attack; y: decay)##sesd"].plurals[0] = "20xy: Ustaw atak/opadanie (x: atak; y: opadanie)";
    strings["21xy: Set sustain/release (x: sustain; y: release)##sesd"].plurals[0] = "21xy: Ustaw podtrzymanie/zwolnienie (x: podtrzymanie; y: zwolnienie)";
    strings["22xx: Pulse width slide up##sesd"].plurals[0] = "22xx: Narastanie szerokości fali prostokątnej";
    strings["23xx: Pulse width slide down##sesd"].plurals[0] = "23xx: Opadanie szerokości fali prostokątnej";
    strings["24xx: Cutoff slide up##sesd"].plurals[0] = "24xx: Narastanie punktu odcięcia";
    strings["25xx: Cutoff slide down##sesd"].plurals[0] = "25xx: Opadanie punktu odcięcia";
    strings["3xxx: Set pulse width (0 to FFF)##sesd"].plurals[0] = "3xxx: Ustaw szerokość fali prost. (0-FFF)";
    strings["4xxx: Set cutoff (0 to 7FF)##sesd"].plurals[0] = "4xxx: Ustaw punkt odcięcia (0-7FF)";
    strings["10xx: Set waveform##sesd0"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Set raw period (0-1F)##sesd"].plurals[0] = "11xx: Ustaw absolutny okres (0-1F)";
    strings["11xx: Set waveform (local)##sesd"].plurals[0] = "11xx: Ustaw kształt fali (lokalny)";
    strings["20xx: Set PCM frequency##sesd"].plurals[0] = "20xx: Ustaw częstotliwość PCM";
    strings["10xy: Set AM depth (x: operator from 1 to 4 (0 for all ops); y: depth (0: 1dB, 1: 4.8dB))##sesd"].plurals[0] = "10xy: Ustaw głębokość AM (x: operator 1-4 (0 dla wszystkich operatorów); y: głębokość (0: 1 dB, 1: 4.8 dB))";
    strings["12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd2"].plurals[0] = "12xx: Ustaw poziom operatora 1 (0 maks., 3F min.)";
    strings["13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd2"].plurals[0] = "13xx: Ustaw poziom operatora 2 (0 maks., 3F min.)";
    strings["14xx: Set level of operator 3 (0 highest, 3F lowest)##sesd1"].plurals[0] = "14xx: Ustaw poziom operatora 3 (0 maks., 3F min.)";
    strings["15xx: Set level of operator 4 (0 highest, 3F lowest)##sesd1"].plurals[0] = "15xx: Ustaw poziom operatora 4 (0 maks., 3F min.)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd2"].plurals[0] = "16xy: Ustaw mnożnik operatora (x: operator 1-4; y: mnożnik)";
    strings["17xy: Set vibrato depth (x: operator from 1 to 4 (0 for all ops); y: depth (0: normal, 1: double))##sesd"].plurals[0] = "17xy: Ustaw głębokość vibrato (x: operator 1-4 (0 dla wszystkich operatorów); y: głębokość (0: normalna, 1: podwójna))";
    strings["19xx: Set attack of all operators (0 to F)##sesd"].plurals[0] = "19xx: Ustaw atak wszystkich operatorów (0-F)";
    strings["1Axx: Set attack of operator 1 (0 to F)##sesd2"].plurals[0] = "1Axx: Ustaw atak operatora 1 (0-F)";
    strings["1Bxx: Set attack of operator 2 (0 to F)##sesd2"].plurals[0] = "1Bxx: Ustaw atak operatora 2 (0-F)";
    strings["1Cxx: Set attack of operator 3 (0 to F)##sesd1"].plurals[0] = "1Cxx: Ustaw atak operatora 3 (0-F)";
    strings["1Dxx: Set attack of operator 4 (0 to F)##sesd1"].plurals[0] = "1Dxx: Ustaw atak operatora 4 (0-F)";
    strings["20xy: Set panning of operator 1 (x: left; y: right)##sesd"].plurals[0] = "20xy: Ustaw panning operatora 1 (x: lewo; y: prawo)";
    strings["21xy: Set panning of operator 2 (x: left; y: right)##sesd"].plurals[0] = "21xy: Ustaw panning operatora 2 (x: lewo; y: prawo)";
    strings["22xy: Set panning of operator 3 (x: left; y: right)##sesd"].plurals[0] = "22xy: Ustaw panning operatora 3 (x: lewo; y: prawo)";
    strings["23xy: Set panning of operator 4 (x: left; y: right)##sesd"].plurals[0] = "23xy: Ustaw panning operatora 4 (x: lewo; y: prawo)";
    strings["24xy: Set output level register (x: operator from 1 to 4 (0 for all ops); y: level from 0 to 7)##sesd"].plurals[0] = "24xy: Ustaw rejestr poziomu wyjścia (głośności) (x: operator 1-4 (0 dla wszystkich operatorów); y: poziom 0-7)";
    strings["25xy: Set modulation input level (x: operator from 1 to 4 (0 for all ops); y: level from 0 to 7)##sesd"].plurals[0] = "25xy: Ustaw poziom wejścia modulacji (x: operator 1-4 (0 dla wszystkich operatorów); y: poziom 0-7)";
    strings["26xy: Set envelope delay (x: operator from 1 to 4 (0 for all ops); y: delay from 0 to 7)##sesd"].plurals[0] = "26xy: Ustaw opóźnienie obwiedni (x: operator 1-4 (0 dla wszystkich operatorów); y: opóźnienie 0-7)";
    strings["27xx: Set noise mode for operator 4 (x: mode from 0 to 3)##sesd"].plurals[0] = "27xx: Ustaw tryb szumu operatora 4 (x: tryby 0-3)";
    strings["2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 7)##sesd1"].plurals[0] = "2Axy: Ustaw kształt fali (x: operator 1-4 (0 dla wszystkich operatorów); y: kształt fali 0-7)";
    strings["2Fxy: Set fixed frequency block (x: operator from 1 to 4; y: octave from 0 to 7)##sesd"].plurals[0] = "2Fxy: Ustaw blok stałej częstotiwości (x: operator 1-4; y: oktawa 0-7)";
    strings["40xx: Set detune of operator 1 (80: center)##sesd"].plurals[0] = "40xx: Rozstrojenie operatora 1 (80: brak rozstrojenia)";
    strings["41xx: Set detune of operator 2 (80: center)##sesd"].plurals[0] = "41xx: Rozstrojenie operatora 2 (80: brak rozstrojenia)";
    strings["42xx: Set detune of operator 3 (80: center)##sesd"].plurals[0] = "42xx: Rozstrojenie operatora 3 (80: brak rozstrojenia)";
    strings["43xx: Set detune of operator 4 (80: center)##sesd"].plurals[0] = "43xx: Rozstrojenie operatora 4 (80: brak rozstrojenia)";
    strings["50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd2"].plurals[0] = "50xy: Ustaw AM (x: operator 1-4 (0 dla wszystkich operatorów); y: AM)";
    strings["51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd2"].plurals[0] = "51xy: Ustaw podtrzymanie (x: operator 1-4 (0 dla wszystkich operatorów); y: podtrzymanie)";
    strings["52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd2"].plurals[0] = "52xy: Ustaw zwolnienie (x: operator 1-4 (0 dla wszystkich operatorów); y: zwolnienie)";
    strings["53xy: Set vibrato (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1"].plurals[0] = "53xy: Ustaw vibrato (x: operator 1-4 (0 dla wszystkich operatorów); y: wł.)";
    strings["54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd2"].plurals[0] = "54xy: Ustaw skalowanie obwiedni (x: operator 1-4 (0 dla wszystkich operatorów); y: skala 0-3)";
    strings["55xy: Set envelope sustain (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1"].plurals[0] = "55xy: Ustaw podtrzymanie obwiedni (x: operator 1-4 (0 dla wszystkich operatorów); y: wł.)";
    strings["56xx: Set decay of all operators (0 to F)##sesd2"].plurals[0] = "56xx: Ustaw opadanie wszystkich operatorów (0-F)";
    strings["57xx: Set decay of operator 1 (0 to F)##sesd2"].plurals[0] = "57xx: Ustaw opadanie operatora 1 (0-F)";
    strings["58xx: Set decay of operator 2 (0 to F)##sesd2"].plurals[0] = "58xx: Ustaw opadanie operatora 2 (0-F)";
    strings["59xx: Set decay of operator 3 (0 to F)##sesd1"].plurals[0] = "59xx: Ustaw opadanie operatora 3 (0-F)";
    strings["5Axx: Set decay of operator 4 (0 to F)##sesd1"].plurals[0] = "5Axx: Ustaw opadanie operatora 4 (0-F)";
    strings["5Bxy: Set whether key will scale envelope (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1"].plurals[0] = "5Bxy: Ustaw skalowanie obwiedni wg. nuty (x: operator 1-4 (0 dla wszystkich operatorów); y: wł.)";
    strings["3xyy: Set fixed frequency F-num of operator 1 (x: high 2 bits from 0 to 3; y: low 8 bits of F-num)##sesd"].plurals[0] = "3xyy: Ustaw F-Num stałej częstotliwości dla operatora 1 (x: dwa wysokie bity 0-3; y: 8 niskich bitów F-num)";
    strings["3xyy: Set fixed frequency F-num of operator 2 (x: high 2 bits from 4 to 7; y: low 8 bits of F-num)##sesd"].plurals[0] = "3xyy: Ustaw F-Num stałej częstotliwości dla operatora 2 (x: dwa wysokie bity 4-7; y: 8 niskich bitów F-num)";
    strings["3xyy: Set fixed frequency F-num of operator 3 (x: high 2 bits from 8 to B; y: low 8 bits of F-num)##sesd"].plurals[0] = "3xyy: Ustaw F-Num stałej częstotliwości dla operatora 3 (x: dwa wysokie bity 8-B; y: 8 niskich bitów F-num)";
    strings["3xyy: Set fixed frequency F-num of operator 4 (x: high 2 bits from C to F; y: low 8 bits of F-num)##sesd"].plurals[0] = "3xyy: Ustaw F-Num stałej częstotliwości dla operatora 4 (x:dwa wysokie bity C-F; y: 8 niskich bitów F-num)";
    strings["10xx: Set waveform (bit 0: triangle; bit 1: saw; bit 2: pulse; bit 3: noise)##sesd1"].plurals[0] = "10xx: Ustaw kształt fali (bit 0: trójkątna.; bit 1: piłokształtna; bit 2: prostokątna.; bit 3: szum)";
    strings["11xx: Set resonance (0 to FF)##sesd"].plurals[0] = "11xx: Ustaw rezonans (0-FF)";
    strings["12xx: Set filter mode (bit 0: low pass; bit 1: band pass; bit 2: high pass)##sesd"].plurals[0] = "12xx: Ustaw tryb filtra (bit 0: dolno-; bit 1: środkowo-; bit 2: górnoprzepustowy)";
    strings["13xx: Disable envelope reset for this channel (1 disables; 0 enables)##sesd"].plurals[0] = "13xx: Wyłącz reset obwiedni dla tego kanału (1 wył.; 0 wł.)";
    strings["14xy: Reset cutoff (x: on new note; y: now)##sesd"].plurals[0] = "14xy: Resetuj punkt odcięcia (x: od nowej nuty; y: teraz)";
    strings["15xy: Reset pulse width (x: on new note; y: now)##sesd"].plurals[0] = "15xy: Resetuj szerokość fali prost. (x: od nowej nuty; y: teraz)";
    strings["16xy: Change other parameters##sesd"].plurals[0] = "16xy: Zmień inne parametry";
    strings["17xx: Pulse width slide up##sesd"].plurals[0] = "17xx: Narastanie szerokości fali prostokątnej";
    strings["18xx: Pulse width slide down##sesd"].plurals[0] = "18xx: Opadanie szerokości fali prostokątnej";
    strings["19xx: Cutoff slide up##sesd"].plurals[0] = "19xx: Narastanie punktu odcięcia";
    strings["1Axx: Cutoff slide down##sesd"].plurals[0] = "1Axx: Opadanie punktu odcięcia";
    strings["3xxx: Set pulse width (0 to FFF)##sesd1"].plurals[0] = "3xxx: Ustaw szerokość fali prostokątnej (0-FFF)";
    strings["4xxx: Set cutoff (0 to FFF)##sesd1"].plurals[0] = "4xxx: Ustaw punkt odcięcia (0-FFF)";
    strings["a chip which found its way inside mobile phones in the 2000's.\nas proprietary as it is, it passed away after losing to MP3 in the mobile hardware battle.##sesd"].plurals[0] = "układ, który zaczął pojawiać się w telefonach komórkowych w 2000 r.\n jako iż wykorzystwał zastreżony format, przegrał z formatem MP3 podczas rywalizacji między różnymi typami sprzętu mobilnego.";
    strings["<COMPOUND SYSTEM!>##sesd0"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["<COMPOUND SYSTEM!>##sesd1"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["a square/noise sound chip found on the Sega Master System, ColecoVision, Tandy, TI's own 99/4A and a few other places.##sesd"].plurals[0] = "układ generujący falę prostokątną i szum, który został zastosowany w Sega Master System, ColecoVision, Tandy, własnym urządzeniu 99/4A firmy TI i kilku innych urządzeniach";
    strings["20xy: Set noise mode (x: preset freq/ch3 freq; y: thin pulse/noise)##sesd"].plurals[0] = "20xy: Ustaw tryb szumu (x: stała częst/częst. 3-go kanału; y: \"wąska\" fala prostokątna/szum)";
    strings["<COMPOUND SYSTEM!>##sesd2"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["the most popular portable game console of the era.##sesd"].plurals[0] = "najbardziej popularna przenośna konsola tamtych czasów.";
    strings["10xx: Set waveform##sesd1"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Set noise length (0: long; 1: short)##sesd"].plurals[0] = "11xx: Ustaw długość szumu (0: długi; 1: krótki)";
    strings["12xx: Set duty cycle (0 to 3)##sesd"].plurals[0] = "12xx: Ustaw szerokość fali prost. (0-3)";
    strings["13xy: Setup sweep (x: time; y: shift)##sesd"].plurals[0] = "13xy: Skonfiguruj sprzętowe portamento (x: okres trwania; y: przesunięcie)";
    strings["14xx: Set sweep direction (0: up; 1: down)##sesd"].plurals[0] = "14xx: Ustaw kierunek sprzętowego portamento (0: w górę; 1: w dół)";
    strings["15xx: Set waveform (local)##sesd"].plurals[0] = "15xx: Ustaw kształt fali (lokalny)";
    strings["an '80s game console with a wavetable sound chip, popular in Japan.##sesd"].plurals[0] = "konsola do gier z lat 80. z układem syntezy tablicowej. była popularna w Japonii.";
    strings["10xx: Set waveform##sesd2"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Toggle noise mode##sesd0"].plurals[0] = "11xx: Włącz tryb szumu";
    strings["12xx: Setup LFO (0: disabled; 1: 1x depth; 2: 16x depth; 3: 256x depth)##sesd"].plurals[0] = "12xx: Ustaw LFO (0: wł.; 1: głębokość 1x; 2: głębokość 16x; 3: głębokość 256x)";
    strings["13xx: Set LFO speed##sesd"].plurals[0] = "13xx: Ustaw szybkość LFO";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd1"].plurals[0] = "17xx: Włącz tryb PCM (PRZESTARZAŁY)";
    strings["18xx: Set waveform (local)##sesd"].plurals[0] = "18xx: Ustaw kształt fali (lokalny)";
    strings["also known as Famicom in Japan, it's the most well-known game console of the '80s.##sesd"].plurals[0] = "także znana w Japonii jako Famicom. to najbardziej znana konsola lat 80-tych.";
    strings["11xx: Write to delta modulation counter (0 to 7F)##sesd"].plurals[0] = "11xx: Zapisz do licznika modulacji delta (0-7F)";
    strings["12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1)##sesd0"].plurals[0] = "12xx: Ustaw szerokość fali prost./tryb szumu (fala prost.: 0-3; szum: 0 lub 1)";
    strings["13xy: Sweep up (x: time; y: shift)##sesd"].plurals[0] = "13xy: Sprzętowe portamento w górę (x: czas; y: przesunięcie)";
    strings["14xy: Sweep down (x: time; y: shift)##sesd"].plurals[0] = "14xy: Sprzętowe portamento w dół (x: czas; y: przesunięcie)";
    strings["15xx: Set envelope mode (0: envelope, 1: length, 2: looping, 3: constant)##sesd"].plurals[0] = "15xx: Ustaw tryb obwiedni (0: obwiednia, 1: długość, 2: zapętla, 3: stały)";
    strings["16xx: Set length counter (refer to manual for a list of values)##sesd"].plurals[0] = "16xx: Ustaw długość licznika (lista wartości w instrukcji)";
    strings["17xx: Set frame counter mode (0: 4-step, 1: 5-step)##sesd"].plurals[0] = "17xx: Tryb licznika klatek (0: 4 kroki, 1: 5 kroków)";
    strings["18xx: Select PCM/DPCM mode (0: PCM; 1: DPCM)##sesd"].plurals[0] = "18xx: Wybierz tryb PCM/DPCM (0: PCM; 1: DPCM)";
    strings["19xx: Set triangle linear counter (0 to 7F; 80 and higher halt)##sesd"].plurals[0] = "19xx: Ustaw liniowy licznik kanały fali trójk. (0-7F; 80 w wyżej zatrzymują falę";
    strings["20xx: Set DPCM frequency (0 to F)##sesd"].plurals[0] = "20xx: Ustaw częstotliwość DPCM (0-F)";
    strings["<COMPOUND SYSTEM!>##sesd3"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["<COMPOUND SYSTEM!>##sesd4"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["this computer is powered by the SID chip, which had synthesizer features like a filter and ADSR.##sesd"].plurals[0] = "ten komputer ma układ SID, który ma zaawansowane funkcje typowe dla syntezatorów, takie jak filtr i obwiednia ADSR.";
    strings["this computer is powered by the SID chip, which had synthesizer features like a filter and ADSR.\nthis is the newer revision of the chip.##sesd"].plurals[0] = "ten komputer ma układ SID, który ma zaawansowane funkcje typowe dla syntezatorów, takie jak filtr i obwiednia ADSR.\nto nowsza wersja układu.";
    strings["<COMPOUND SYSTEM!>##sesd5"].plurals[0] = "<SYSTEM ZŁOŻONY!>";
    strings["like Neo Geo, but lacking the ADPCM-B channel since they couldn't connect the pins.##sesd"].plurals[0] = "to samo co Neo Geo, ale bez kanału ADPCM-B, ponieważ podłączenie pinów ich przerosło.";
    strings["like Neo Geo, but lacking the ADPCM-B channel since they couldn't connect the pins.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.##sesd"].plurals[0] = "to samo co Neo Geo, ale bez kanału ADPCM-B, ponieważ podłaczenie pinów ich przerosło.\njest to układ w trybie rozszerzonego kanału, który zamienia drugi kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.";
    strings["this chip is everywhere! ZX Spectrum, MSX, Amstrad CPC, Intellivision, Vectrex...\nthe discovery of envelope bass helped it beat the SN76489 with ease.##sesd"].plurals[0] = "ten układ był wszędzie! ZX Spectrum, MSX, Amstrad CPC, Intellivision, Vectrex...\nodkrycie metody wykorzystania obwiedni dla basów z łatwością pozwoliło temu układowi pokonać SN76489.";
    strings["a computer from the '80s with full sampling capabilities, giving it a sound ahead of its time.##sesd"].plurals[0] = "komputer z lat 80-tych z pełnymi możliwościami samplingu, nadający mu brzmienie wyprzedzające swoją epokę.";
    strings["10xx: Toggle filter (0 disables; 1 enables)##sesd"].plurals[0] = "10xx: Włącz filtr (0 wył.; 1 wł.)";
    strings["11xx: Toggle AM with next channel##sesd"].plurals[0] = "11xx: Włącz AM z następnym kanałem";
    strings["12xx: Toggle period modulation with next channel##sesd"].plurals[0] = "12xx: Włącz modulację okresu z następnym kanałem";
    strings["13xx: Set waveform##sesd"].plurals[0] = "13xx: Ustaw kształt fali";
     strings["14xx: Set waveform (local)##sesd"].plurals[0] = "14xx: Ustaw kształt fali (lokalny)";
    strings["this was Yamaha's first integrated FM chip.\nit was used in several synthesizers, computers and arcade boards.##sesd"].plurals[0] = "układ ten był pierwszym jednoukładowym syntezatorem FM Yamahy\nbył używany w kilku syntezatorach, komputerach i automatach do gier.";
    strings["this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).##sesd"].plurals[0] = "układ ten znany jest głównie z tego, że znajduje się w Sega Mega Drive (ale był również używany w komputerze FM Towns).";
    strings["it's a challenge to make music on this chip which barely has musical capabilities...##sesd"].plurals[0] = "jest to pewne wyzwanie tworzyć komozycje pod układ który praktycznie nie posiada możliwości muzycznych...";
    strings["supposedly an upgrade from the AY-3-8910, this was present on the Creative Music System (Game Blaster) and SAM Coupé.##sesd"].plurals[0] = "ten układ, rzekomo ulepszona wersja AY-3-8910, był używany w Creative Music System (Game Blaster) i SAM Coupé.";
    strings["10xy: Set channel mode (x: noise; y: tone)##sesd"].plurals[0] = "10xy: Ustaw tryb kanału (x: szum; y: ton)";
    strings["11xx: Set noise frequency##sesd"].plurals[0] = "11xx: Częstotliwość szumu";
    strings["12xx: Setup envelope (refer to docs for more information)##sesd"].plurals[0] = "12xx: Ustaw obwiednię (patrz: instrukcja)";
    strings["an improved version of the AY-3-8910 with a bigger frequency range, duty cycles, configurable noise and per-channel envelopes!##sesd"].plurals[0] = "ulepszona wersja AY-3-8910 z większym zakresem częstotliwości, regulowaną szerokościa fali prostokątnej, regulowanym szumem i osobną obwiednią na każdy kanał!";
    strings["Commodore's successor to the PET.\nits square wave channels are more than just square...##sesd"].plurals[0] = "komputer Commodore, który ukazał się po PET.\njego kanały fal prostokątnych mogą odtwarzać więcej niż tylko fale prostokątne...";
    strings["one channel of 1-bit wavetable which is better (and worse) than the PC Speaker.##sesd"].plurals[0] = "1-kanałowy 1-bitow syntezator tablicowy, która jest lepsza (lub gorsza) niż PC Speaker (brzęczyk).";
    strings["FM? nah... samples! Nintendo's answer to Sega.##sesd"].plurals[0] = "FM? nieee, sample! Odpowiedź Nintendo na sukces Segi.";
    strings["18xx: Enable echo buffer##sesd"].plurals[0] = "18xx: Włącz bufor echo";
    strings["19xx: Set echo delay (0 to F)##sesd"].plurals[0] = "19xx: Ustaw opóźnienie echo (0-F)";
    strings["1Axx: Set left echo volume##sesd"].plurals[0] = "1Axx: Ustaw głośność echo na lewym kanale";
    strings["1Bxx: Set right echo volume##sesd"].plurals[0] = "1Bxx: Ustaw głośność echo na prawym kanale";
    strings["1Cxx: Set echo feedback##sesd"].plurals[0] = "1Cxx: Ustaw feedback echo";
    strings["1Exx: Set dry output volume (left)##sesd"].plurals[0] = "1Exx: Ustaw głośność kanału (lewo)";
    strings["1Fxx: Set dry output volume (right)##sesd"].plurals[0] = "1Fxx: Ustaw głośność kanału (prawo)";
    strings["30xx: Set echo filter coefficient 0##sesd"].plurals[0] = "30xx: Ustaw współczynnik 0 filtra echo";
    strings["31xx: Set echo filter coefficient 1##sesd"].plurals[0] = "31xx: Ustaw współczynnik 1 filtra echo";
    strings["32xx: Set echo filter coefficient 2##sesd"].plurals[0] = "32xx: Ustaw współczynnik 2 filtra echo";
    strings["33xx: Set echo filter coefficient 3##sesd"].plurals[0] = "33xx: Ustaw współczynnik 3 filtra echo";
    strings["34xx: Set echo filter coefficient 4##sesd"].plurals[0] = "34xx: Ustaw współczynnik 4 filtra echo";
    strings["35xx: Set echo filter coefficient 5##sesd"].plurals[0] = "35xx: Ustaw współczynnik 5 filtra echo";
    strings["36xx: Set echo filter coefficient 6##sesd"].plurals[0] = "36xx: Ustaw współczynnik 6 filtra echo";
    strings["37xx: Set echo filter coefficient 7##sesd"].plurals[0] = "37xx: Ustaw współczynnik 7 filtra echo";
    strings["10xx: Set waveform##sesd3"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Toggle noise mode##sesd1"].plurals[0] = "11xx: Włącz tryb szumu";
    strings["12xx: Toggle echo on this channel##sesd"].plurals[0] = "12xx: Włącz echo na tym kanale";
    strings["13xx: Toggle pitch modulation##sesd"].plurals[0] = "13xx: Włącz modulację wysokości dźwięku";
    strings["14xy: Toggle invert (x: left; y: right)##sesd"].plurals[0] = "14xy: Włacz odwrócenie sygnału (x: lewo; y: prawo)";
    strings["15xx: Set envelope mode (0: ADSR, 1: gain/direct, 2: dec, 3: exp, 4: inc, 5: bent)##sesd"].plurals[0] = "15xx: Tryb obwiedni (0: ADSR, 1: wzmocnienie/bezpośredni, 2: opadający 3: wykładniczy, 4: wzrastający 5: zakrzywiony)";
    strings["16xx: Set gain (00 to 7F if direct; 00 to 1F otherwise)##sesd"].plurals[0] = "16xx: Ustaw wzmocnienie (00-7F w bezpośrednim trrybie; inaczej 00-1F)";
    strings["17xx: Set waveform (local)##sesd"].plurals[0] = "17xx: Ustaw kształt fali (lokalny)";
    strings["1Dxx: Set noise frequency (00 to 1F)##sesd"].plurals[0] = "1Dxx: Ustaw częstotliwość szumu (00-1F)";
    strings["20xx: Set attack (0 to F)##sesd"].plurals[0] = "20xx: Ustaw atak (0-F)";
    strings["21xx: Set decay (0 to 7)##sesd"].plurals[0] = "21xx: Ustaw opadanie (0-7)";
    strings["22xx: Set sustain (0 to 7)##sesd"].plurals[0] = "22xx: Ustaw podtrzymanie (0-7)";
    strings["23xx: Set release (00 to 1F)##sesd"].plurals[0] = "23xx: Ustaw zwolnienie (00-1F)";
    strings["an expansion chip for the Famicom, featuring a quirky sawtooth channel.##sesd"].plurals[0] = "układ rozszerzający dla Famicoma, zawierający bardzo nietypowy kanał fali piłokształtnej.";
    strings["12xx: Set duty cycle (pulse: 0 to 7)##sesd"].plurals[0] = "12xx: Ustaw szerokość fali prost. (puls: 0-7)";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd2"].plurals[0] = "17xx: włącz tryb PCM (PRZESTARZAŁY)";
    strings["cost-reduced version of the OPL with 16 patches and only one of them is user-configurable.##sesd"].plurals[0] = "tańsza wersja OPL z 16 wbudowanymi instrumentami, z których tylko jeden jest dostępny do dostosowania przez użytkownika.";
    strings["a disk drive for the Famicom which also contains one wavetable channel.##sesd"].plurals[0] = "stacja dyskietek dla Famicoma, która przy okazji dostarcza jeden kanał syntezy tablicowej";
    strings["10xx: Set waveform##sesd4"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Set modulation depth##sesd"].plurals[0] = "11xx: Ustaw głębokość modulacji";
    strings["12xy: Set modulation speed high byte (x: enable; y: value)##sesd"].plurals[0] = "12xy: Ustaw wysoki bajt szybkości modulacji (x: wł.; y: wartość)";
    strings["13xx: Set modulation speed low byte##sesd"].plurals[0] = "13xx: Ustaw niski bajt szybkości modulacji";
    strings["14xx: Set modulator position##sesd"].plurals[0] = "14xx: Położenie modulatora";
    strings["15xx: Set modulator table to waveform##sesd"].plurals[0] = "15xx: Ustaw tablicę modulacji na dany kształt fali";
    strings["16xx: Set waveform (local)##sesd"].plurals[0] = "16xx: Ustaw kształt fali (lokalny)";
    strings["an expansion chip for the Famicom, featuring a little-known PCM channel.##sesd"].plurals[0] = "układ rozszerzający dla Famicoma,, posiadający mało znany kanał PCM";
    strings["12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1)##sesd1"].plurals[0] = "12xx: Ustaw szerokość fali prost./tryb szumu (fala prostokątna: 0-3; szum: 0 lub 1)";
    strings["an expansion chip for the Famicom, with full wavetable.##sesd"].plurals[0] = "układ rozszerzający dla Famicoma, który jest pełnoprawnym syntezatorem tablicowym.";
    strings["18xx: Change channel limits (0 to 7, x + 1)##sesd"].plurals[0] = "18xx: Zmień ilość kanałów (0-7, x + 1)";
    strings["20xx: Load a waveform into memory##sesd"].plurals[0] = "20xx: Wczytaj falę do pamięci";
    strings["21xx: Set position for wave load##sesd"].plurals[0] = "21xx: Ustaw początkowe przesunięcie załadowania fali";
    strings["10xx: Select waveform##sesd"].plurals[0] = "10xx: Wybierz kształt fali";
    strings["11xx: Set waveform position in RAM##sesd"].plurals[0] = "11xx: Ustaw pozycję fali w RAM-ie";
    strings["12xx: Set waveform length in RAM (04 to FC in steps of 4)##sesd"].plurals[0] = "12xx: Ustaw długość fali w RAM-ie (04-FC w odstępach 4)";
    strings["15xx: Set waveform load position##sesd"].plurals[0] = "15xx: Ustaw pozycję ładowania fali";
    strings["16xx: Set waveform load length (04 to FC in steps of 4)##sesd"].plurals[0] = "16xx: Ustaw długość fali do wczytania(04-FC w odstępach 4)";
    strings["17xx: Select waveform (local)##sesd1"].plurals[0] = "17xx: Ustaw kształt fali (lokalny)";
    strings["cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)##sesd"].plurals[0] = "tańsza wersja OPM z innym układem rejestrów i bez stereo...\n...ale za to z wbudowanym AY-3-8910! (tak naprawdę YM2149)";
    strings["cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies##sesd"].plurals[0] = "tańsza wersja OPM z innym układem rejestrów i bez stereo...\n...ale za to z wbudowanym AY-3-8910! (tak naprawdę YM2149)\njest to układ w trybie rozszerzonego kanału, która zamienia trzeci kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami";
    strings["cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "tańsza wersja OPM z innym układem rejestrów i bez stereo...\n...ale za to z wbudowanym AY-3-8910! (tak naprawdę YM2149)\njest to układ w trybie rozszerzonego kanału, która zamienia trzeci kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami\nten układ posiada kontrolę trybu CSM dla efektów specjalnych na trzecim kanale.";
    strings["OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.##sesd"].plurals[0] = "OPN, ale z dwa razy większą ilością kanałów FM, stereo powraca, są też kanały perkusji i ADPCM.";
    strings["OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies##sesd"].plurals[0] = "OPN, ale z dwa razy większą ilością kanałów FM, stereo powrca, są też kanały perkusji i ADPCM.\njest to układ w trybie rozszerzonego kanału, która zamienia trzeci kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.";
    strings["OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "OPN, ale z dwa razy większą ilością kanałów FM, stereo powrca, są też kanały perkusji i ADPCM.\nЭjest to układ w trybie rozszerzonego kanału, która zamienia trzeci kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.\nten układ posiada kontrolę trybu CSM dla efektów specjalnych na trzecim kanale.";
    strings["OPN, but what if you only had two operators, no stereo, no detune and a lower ADSR parameter range?##sesd"].plurals[0] = "OPN, ale co jeśli są tylko dwa operatory na kanał, nie ma stereo, nie ma rozstrajania operatorów, a zakres regulacji parametrów ADSR jest mniejszy?";
    strings["OPL, but what if you had more waveforms to choose than the normal sine?##sesd"].plurals[0] = "OPL, ale co jeśli oferuje inne kształty fal oprócz sinusoidy?";
    strings["OPL2, but what if you had twice the channels, 4-op mode, stereo and even more waveforms?##sesd"].plurals[0] = "OPL2, ale co jeśli ma dwa razy więcej kanałów, tryb 4-op, stereo i jeszcze więcej kształtów fal do wyboru?";
    strings["how many channels of PCM do you want?\nMultiPCM: yes##sesd"].plurals[0] = "ile kanałów PCM chcesz?\nMultiPCM: tak";
    strings["good luck! you get one square and no volume control.##sesd"].plurals[0] = "powodzenia! masz jeden kanał fali kwadratowej i zero regulacji głośności.";
    strings["please don't use this chip. it was added as a joke.##sesd"].plurals[0] = "nie używaj tego układu. został dodany jako żart.";
    strings["TIA, but better and more flexible.\nused in the Atari 8-bit family of computers (400/800/XL/XE).##sesd"].plurals[0] = "TIA, ale lepsze i prostsze w obsłudze\nbył używany w rodzinie 8-bitowych komputerów Atari (400/800/XL/XE).";
    strings["10xx: Set waveform (0 to 7)##sesd0"].plurals[0] = "10xx: Ustaw kształt fali (0-7)";
    strings["11xx: Set AUDCTL##sesd"].plurals[0] = "11xx: Ustaw AUDCTL";
    strings["12xx: Toggle two-tone mode##sesd"].plurals[0] = "12xx: Włącz tryb dwóch głosów";
    strings["13xx: Set raw period##sesd"].plurals[0] = "13xx: Ustaw absolutny okres";
    strings["14xx: Set raw period (higher byte; only for 16-bit mode)##sesd"].plurals[0] = "14xx: Ustaw absolutny okres (wysoki bajt; tylko w trybie 16-bitowym)";
    strings["this is like SNES' sound chip but without interpolation and the rest of nice bits.##sesd"].plurals[0] = "podobny do układu dźwiękowego SNES, ale bez interpolacji i innych fajnych ficzerów";
    strings["developed by the makers of the Game Boy and the Virtual Boy...##sesd"].plurals[0] = "zaprojektowany przez twórców Game Boy'a i Virtual Boy'a...";
    strings["10xx: Set waveform##sesd5"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Setup noise mode (0: disabled; 1-8: enabled/tap)##sesd"].plurals[0] = "11xx: Skonfiguruj tryb szumu (0: wył.; 1-8: wł./przełączniki)";
    strings["12xx: Setup sweep period (0: disabled; 1-20: enabled/period)##sesd"].plurals[0] = "12xx: Włącz okres sprętowego portamento (0: wył.; 1-20: wł./okres)";
    strings["13xx: Set sweep amount##sesd"].plurals[0] = "13xx: Ustaw wielkość sprzętowego portamento";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd3"].plurals[0] = "17xx: Włącz tryb PCM (PRZESTARZAŁY)";
    strings["18xx: Set waveform (local)##sesd1"].plurals[0] = "18xx: Ustaw kształt fali (lokalny)";
    strings["like OPM, but with more waveforms, fixed frequency mode and totally... undocumented.\nused in the Yamaha TX81Z and some other synthesizers.##sesd"].plurals[0] = "jak OPM, ale z większą liczbą fal, trybem stałej częstotliwości i całkowitym... brakiem informacji o jego konstrukcji.\nużywany w Yamaha TX81Z i niektórych innych syntezatorach.";
    strings["2Fxx: Toggle hard envelope reset on new notes##sesd"].plurals[0] = "2Fxx: Włącz twardy reset obwiedni przy nowych nutach";
    strings["this one is like PC Speaker but has duty cycles.##sesd"].plurals[0] = "ten układ jest podobny do PC Speakera, ale ma zmienną szerokość fali prostokątnej";
    strings["used in some Sega arcade boards (like OutRun), and usually paired with a YM2151.##sesd"].plurals[0] = "był używany w niektórych automatach do gier Segi (np. OutRun) i był zwykle używany w połączeniu z YM2151.";
    strings["a console which failed to sell well due to its headache-inducing features.##sesd"].plurals[0] = "konsola, która się nie sprzedawałą, ponieważ jej funkcje przyprawiały graczy o ból głowy.";
    strings["10xx: Set waveform##sesd6"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Set noise length (0 to 7)##sesd"].plurals[0] = "11xx: Ustaw długość szumu (0-7)";
    strings["12xy: Setup envelope (x: enabled/loop (1: enable, 3: enable+loop); y: speed/direction (0-7: down, 8-F: up))##sesd"].plurals[0] = "12xy: Skonfiguruj obwiednię (x: wł./zapętla (1: wł., 3: wł.i zapętla); y: prędkość/kierunek (0-7: w dół, 8-F: w górę))";
    strings["13xy: Setup sweep (x: speed; y: shift; channel 5 only)##sesd"].plurals[0] = "13xy: Skonfiguruj sprzętowe portamento (x: szybkość; y: zakres; tylko kanał 5)";
    strings["14xy: Setup modulation (x: enabled/loop (1: enable, 3: enable+loop); y: speed; channel 5 only)##sesd"].plurals[0] = "14xy: Skonfiguruj modulację (x: wł./zapętla (1: wł, 3: wł.i zapętla); y: szybkość; tylko kanał 5)";
    strings["15xx: Set modulation waveform (x: wavetable; channel 5 only)##sesd"].plurals[0] = "15xx: Ustaw kształt fali modulatora (x: tablica fal; tylko kanał 5)";
    strings["16xx: Set waveform (local)##sesd1"].plurals[0] = "16xx: Ustaw kształt fali (lokalny)";
    strings["like OPLL, but even more cost reductions applied. three less FM channels, and no drums mode...##sesd"].plurals[0] = "jak OPLL, ale jeszcze bardziej wykastrowany. trzy kanały mniej, brak trybu perkusyjnego...";
    strings["so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.##sesd"].plurals[0] = "a więc Taito poprosiło Yamahę o dodanie do YM2610 dwóch brakujących kanałów FM, a Yamaha z przyjemnością dostarczyła ów układ.";
    strings["the ZX Spectrum only had a basic beeper capable of...\n...a bunch of thin pulses and tons of other interesting stuff!\nFurnace provides a thin pulse system.##sesd"].plurals[0] = "ZX Spectrum miał tylko prosty brzęczyk zdolny do generowania\n...kilku \"wąskich\" fal prostokątnych i wielu innych ciekawych dźwięków!\nFurnace dostarcza silnik z \"wąskimi\" falami prostokątnymi.";
    strings["12xx: Set pulse width##sesd0"].plurals[0] = "12xx: Ustaw szerokość fali prost.";
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
    strings["22xx: Set duty cycle (0 to 3F)##sesd"].plurals[0] = "22xx: Ustaw szerokość fali prost. (0-3F)";
    strings["so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.##sesd"].plurals[0] = "a więc Taito poprosiło Yamahę o dodanie do YM2610 dwóch brakujących kanałów FM, a Yamaha z przyjemnością dostarczyła ów układ.\njest to układ w trybie rozszerzonego kanału, która zamienia trzeci kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.";
    strings["so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "a więc Taito poprosiło Yamahę o dodanie do YM2610 dwóch brakujących kanałów FM, a Yamaha z przyjemnością dostarczyła ów układ.\njest to układ w trybie rozszerzonego kanału, która zamienia trzeci kanał FM w cztery operatory z niezależnymi nutami/częstotliwościami.\nten układ posiada kontrolę trybu CSM dla efektów specjalnych na trzecim kanale.";
    strings["this is the same thing as SegaPCM, but only exposes 5 of the channels for compatibility with DefleMask.##sesd"].plurals[0] = "jest to to samo co SegaPCM, ale tylko pięć kanałów jest dostępnych dla kompatybilności z DefleMaskiem.";
    strings["a sound chip used in several Seta/Allumer-manufactured arcade boards with too many channels of wavetable sound, which also are capable of sampled sound.##sesd"].plurals[0] = "układ dźwiękowy używany w kilku automatach go gier firmy Seta/Allumer. posiada stanowczo za dużo kanałów syntezy tablicowej, zdolny również do odtwarzania sampli.";
    strings["10xx: Set waveform##sesd7"].plurals[0] = "10xx: Ustaw kształt fali";
    strings["11xx: Set envelope shape##sesd"].plurals[0] = "11xx: Ustaw kształt obwiedni";
    strings["12xx: Set sample bank slot (0 to 7)##sesd"].plurals[0] = "12xx: Ustaw slot banków sampli (0-7)";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd4"].plurals[0] = "17xx: Włącz tryb PCM (PRZESTARZAŁY)";
    strings["18xx: Set waveform (local)##sesd2"].plurals[0] = "18xx: Ustaw kształt fali (lokalny)";
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
    strings["a sample chip made by Ensoniq, which is the basis for the GF1 chip found in Gravis' Ultrasound cards.##sesd"].plurals[0] = "sampler Ensoniqa, który był podstawą układu GF1 używanego w kartach dźwiękowych Gravis Ultrasound.";
    strings["like OPL but with an ADPCM channel.##sesd"].plurals[0] = "OPL, ale z dodatkowym kanałem ADPCM.";
    strings["the Y8950 chip, in drums mode.##sesd"].plurals[0] = "układ Y8950 w trybie perkusji.";
    strings["this is a variant of Konami's SCC chip with the last channel's wavetable being independent.##sesd"].plurals[0] = "wariant układu SCC firmy Konami z niezależną tablicą fal ostatniego kanału.";
    strings["10xx: Set waveform (0 to 7)##sesd1"].plurals[0] = "10xx: Ustaw kształt fali (0-7)";
    strings["12xx: Set pulse width (0 to 7F)##sesd"].plurals[0] = "12xx: Ustaw szerokość fali prost. (0-7F)";
    strings["13xx: Set resonance (0 to FF)##sesd"].plurals[0] = "13xx: Ustaw rezonans (0-FF)";
    strings["14xx: Set filter mode (bit 0: ring mod; bit 1: low pass; bit 2: high pass; bit 3: band pass)##sesd"].plurals[0] = "14xx: Ustaw tryb filtra (bit 0: modulacja kołowa; bit 1: dolno-; bit 2: środkowo-; bit 3: górnoprzepustowy)";
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
    strings["11xx: Select waveform (local)##sesd1"].plurals[0] = "11xx: Ustaw kształt fali (lokalny)";
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
    strings["12xx: Set pulse width##sesd1"].plurals[0] = "12xx: Ustaw szerokość fali prost.";
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
    strings["12xx: Toggle high-pass with next channel##sesd"].plurals[0] = "12xx: Włącz filtr gornoprzep. na następnym kanale";
    strings["13xx: Toggle ring modulation with channel+2##sesd"].plurals[0] = "13xx: Włącz modulację kołową na kanale +2";
    strings["14xx: Toggle swap counters (noise only)##sesd"].plurals[0] = "14xx: Włącz zamianę liczników (tylko szum)";
    strings["15xx: Toggle low pass (noise only)##sesd"].plurals[0] = "15xx: Włącz filtr dolnoprzep. (tylko szum)";
    strings["16xx: Set clock divider (0: /2; 1: /3)##sesd"].plurals[0] = "16xx: Ustaw dzielnik zegara (0: /2; 1: /3)";
    strings["a fictional sound chip by LTVA. like SID, but with many of its problems fixed. also features extended functionality like more wave mixing modes, tonal noise, filter and volume per channel.##sesd"].plurals[0] = "fikcyjny układ dźwiękowy firmy LTVA. podobny do SID, ale z wieloma naprawionymi problemami. ten układ ma również dodatkowe funkcje, takie jak nowe metody miksowania fal, melodyjny szum, oddzielna regulacja głośności i filtr na każdym kanale.";
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
    strings["15xx: Set raw period##sesd"].plurals[0] = "15xx: Ustaw absolutny okres";
    strings["16xx: Set raw period higher nybble (0-F)##sesd"].plurals[0] = "16xx: Ustaw wyższy półbajt absolutnego okresu (0-F)";
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

     //channel names

    strings["Channel 1##sesd"].plurals[0] = "Kanał 1";
    strings["Channel 2##sesd"].plurals[0] = "Kanał 2";
    strings["Channel 3##sesd"].plurals[0] = "Kanał 3";
    strings["Channel 4##sesd"].plurals[0] = "Kanał 4";
    strings["Channel 5##sesd"].plurals[0] = "Kanał 5";
    strings["Channel 6##sesd"].plurals[0] = "Kanał 6";
    strings["Channel 7##sesd"].plurals[0] = "Kanał 7";
    strings["Channel 8##sesd"].plurals[0] = "Kanał 8";
    strings["Channel 9##sesd"].plurals[0] = "Kanał 9";
    strings["Channel 10##sesd"].plurals[0] = "Kanał 10";
    strings["Channel 11##sesd"].plurals[0] = "Kanał 11";
    strings["Channel 12##sesd"].plurals[0] = "Kanał 12";
    strings["Channel 13##sesd"].plurals[0] = "Kanał 13";
    strings["Channel 14##sesd"].plurals[0] = "Kanał 14";
    strings["Channel 15##sesd"].plurals[0] = "Kanał 15";
    strings["Channel 16##sesd"].plurals[0] = "Kanał 16";
    strings["Channel 17##sesd"].plurals[0] = "Kanał 17";
    strings["Channel 18##sesd"].plurals[0] = "Kanał 18";
    strings["Channel 19##sesd"].plurals[0] = "Kanał 19";
    strings["Channel 20##sesd"].plurals[0] = "Kanał 20";
    strings["Channel 21##sesd"].plurals[0] = "Kanał 21";
    strings["Channel 22##sesd"].plurals[0] = "Kanał 22";
    strings["Channel 23##sesd"].plurals[0] = "Kanał 23";
    strings["Channel 24##sesd"].plurals[0] = "Kanał 24";
    strings["Channel 25##sesd"].plurals[0] = "Kanał 25";
    strings["Channel 26##sesd"].plurals[0] = "Kanał 26";
    strings["Channel 27##sesd"].plurals[0] = "Kanał 27";
    strings["Channel 28##sesd"].plurals[0] = "Kanał 28";
    strings["Channel 29##sesd"].plurals[0] = "Kanał 29";
    strings["Channel 30##sesd"].plurals[0] = "Kanał 30";
    strings["Channel 31##sesd"].plurals[0] = "Kanał 31";
    strings["Channel 32##sesd"].plurals[0] = "Kanał 32";

    strings["Square##sesd"].plurals[0] = "Kwadrat";

    strings["Square 1##sesd"].plurals[0] = "Kwadrat 1";
    strings["Square 2##sesd"].plurals[0] = "Kwadrat 2";
    strings["Square 3##sesd"].plurals[0] = "Kwadrat 3";

    strings["Pulse##sesd"].plurals[0] = "Prostokąt";

    strings["Pulse 1##sesd"].plurals[0] = "Prostokąt 1";
    strings["Pulse 2##sesd"].plurals[0] = "Prostokąt 2";

    strings["Wave##sesd"].plurals[0] = "Fala";
    strings["Wavetable##sesd"].plurals[0] = "Tabl. fali";

    strings["Triangle##sesd"].plurals[0] = "Trójkąt";

    strings["PCM##sesd"].plurals[0] = "PCM";

    strings["PCM 1##sesd"].plurals[0] = "PCM 1";
    strings["PCM 2##sesd"].plurals[0] = "PCM 2";
    strings["PCM 3##sesd"].plurals[0] = "PCM 3";
    strings["PCM 4##sesd"].plurals[0] = "PCM 4";
    strings["PCM 5##sesd"].plurals[0] = "PCM 5";
    strings["PCM 6##sesd"].plurals[0] = "PCM 6";
    strings["PCM 7##sesd"].plurals[0] = "PCM 7";
    strings["PCM 8##sesd"].plurals[0] = "PCM 8";
    strings["PCM 9##sesd"].plurals[0] = "PCM 9";
    strings["PCM 10##sesd"].plurals[0] = "PCM 10";
    strings["PCM 11##sesd"].plurals[0] = "PCM 11";
    strings["PCM 12##sesd"].plurals[0] = "PCM 12";
    strings["PCM 13##sesd"].plurals[0] = "PCM 13";
    strings["PCM 14##sesd"].plurals[0] = "PCM 14";
    strings["PCM 15##sesd"].plurals[0] = "PCM 15";
    strings["PCM 16##sesd"].plurals[0] = "PCM 16";
    strings["PCM 17##sesd"].plurals[0] = "PCM 17";
    strings["PCM 18##sesd"].plurals[0] = "PCM 18";
    strings["PCM 19##sesd"].plurals[0] = "PCM 19";
    strings["PCM 20##sesd"].plurals[0] = "PCM 20";
    strings["PCM 21##sesd"].plurals[0] = "PCM 21";
    strings["PCM 22##sesd"].plurals[0] = "PCM 22";
    strings["PCM 23##sesd"].plurals[0] = "PCM 23";
    strings["PCM 24##sesd"].plurals[0] = "PCM 24";

    strings["DPCM##sesd"].plurals[0] = "DPCM";

    strings["ADPCM##sesd"].plurals[0] = "ADPCM";

    strings["ADPCM 1##sesd"].plurals[0] = "ADPCM 1";
    strings["ADPCM 2##sesd"].plurals[0] = "ADPCM 2";
    strings["ADPCM 3##sesd"].plurals[0] = "ADPCM 3";

    strings["ADPCM-A 1##sesd"].plurals[0] = "ADPCM-A 1";
    strings["ADPCM-A 2##sesd"].plurals[0] = "ADPCM-A 2";
    strings["ADPCM-A 3##sesd"].plurals[0] = "ADPCM-A 3";
    strings["ADPCM-A 4##sesd"].plurals[0] = "ADPCM-A 4";
    strings["ADPCM-A 5##sesd"].plurals[0] = "ADPCM-A 5";
    strings["ADPCM-A 6##sesd"].plurals[0] = "ADPCM-A 6";

    strings["ADPCM-B##sesd"].plurals[0] = "ADPCM-B";

    strings["Sample##sesd"].plurals[0] = "Sampel";

    strings["DAC Left##sesd"].plurals[0] = "DAC Lewy";
    strings["DAC Right##sesd"].plurals[0] = "DAC Prawy";

    strings["Noise##sesd"].plurals[0] = "Szum";

    strings["Noise 1##sesd"].plurals[0] = "Szum 1";
    strings["Noise 2##sesd"].plurals[0] = "Szum 2";
    strings["Noise 3##sesd"].plurals[0] = "Szum 3";

    strings["Slope##sesd"].plurals[0] = "Spadek";

    strings["FM 6/PCM 1##sesd"].plurals[0] = "FM 6/PCM 1";
    strings["CSM Timer##sesd"].plurals[0] = "Timer CSM";

    strings["VRC6 Saw##sesd"].plurals[0] = "Piła VRC6";

    strings["4OP 1##sesd"].plurals[0] = "4OP 1";
    strings["4OP 3##sesd"].plurals[0] = "4OP 3";
    strings["4OP 5##sesd"].plurals[0] = "4OP 5";
    strings["4OP 7##sesd"].plurals[0] = "4OP 7";
    strings["4OP 9##sesd"].plurals[0] = "4OP 9";
    strings["4OP 11##sesd"].plurals[0] = "4OP 11";

    strings["Kick/FM 7##sesd"].plurals[0] = "Stopa/FM7";
    strings["Kick/FM 16##sesd"].plurals[0] = "Stopa/FM16";
    strings["Kick##sesd"].plurals[0] = "Stopa";
    strings["Snare##sesd"].plurals[0] = "Werbel";
    strings["Top##sesd"].plurals[0] = "Talerz";
    strings["HiHat##sesd"].plurals[0] = "Hi-hat";
    strings["Tom##sesd"].plurals[0] = "Tom-tom";
    strings["Rim##sesd"].plurals[0] = "Rimshot";

    // channel short names

    strings["CH1##sesd"].plurals[0] = "KN1";
    strings["CH2##sesd"].plurals[0] = "KN2";
    strings["CH3##sesd"].plurals[0] = "KN3";
    strings["CH4##sesd"].plurals[0] = "KN4";
    strings["CH5##sesd"].plurals[0] = "KN5";
    strings["CH6##sesd"].plurals[0] = "KN6";
    strings["CH7##sesd"].plurals[0] = "KN7";
    strings["CH8##sesd"].plurals[0] = "KN8";
    strings["CH9##sesd"].plurals[0] = "KN9";

    strings["NO##sesd"].plurals[0] = "SZ";
    strings["N1##sesd"].plurals[0] = "SZ1";
    strings["N2##sesd"].plurals[0] = "SZ2";
    strings["N3##sesd"].plurals[0] = "SZ3";

    strings["SL##sesd"].plurals[0] = "SP";

    strings["S1##sesd"].plurals[0] = "P1";
    strings["S2##sesd"].plurals[0] = "P2";
    strings["S3##sesd"].plurals[0] = "P3";
    strings["S4##sesd"].plurals[0] = "P4";
    strings["S5##sesd"].plurals[0] = "P5";
    strings["S6##sesd"].plurals[0] = "P6";

    strings["P1##sesd"].plurals[0] = "SA1";
    strings["P2##sesd"].plurals[0] = "SA2";
    strings["P3##sesd"].plurals[0] = "SA3";
    strings["P4##sesd"].plurals[0] = "SA4";
    strings["P5##sesd"].plurals[0] = "SA5";
    strings["P6##sesd"].plurals[0] = "SA6";
    strings["P7##sesd"].plurals[0] = "SA7";
    strings["P8##sesd"].plurals[0] = "SA8";
    strings["P9##sesd"].plurals[0] = "SA9";
    strings["P10##sesd"].plurals[0] = "SA10";
    strings["P11##sesd"].plurals[0] = "SA11";
    strings["P12##sesd"].plurals[0] = "SA12";
    strings["P13##sesd"].plurals[0] = "SA13";
    strings["P14##sesd"].plurals[0] = "SA14";
    strings["P15##sesd"].plurals[0] = "SA15";
    strings["P16##sesd"].plurals[0] = "SA16";
    strings["P17##sesd"].plurals[0] = "SA17";
    strings["P18##sesd"].plurals[0] = "SA18";
    strings["P19##sesd"].plurals[0] = "SA19";
    strings["P20##sesd"].plurals[0] = "SA20";
    strings["P21##sesd"].plurals[0] = "SA21";
    strings["P22##sesd"].plurals[0] = "SA22";
    strings["P23##sesd"].plurals[0] = "SA23";
    strings["P24##sesd"].plurals[0] = "SA24";

    strings["BD##sesd"].plurals[0] = "BB";
    strings["SD##sesd"].plurals[0] = "WB";
    strings["TP##sesd"].plurals[0] = "TL";
    strings["HH##sesd"].plurals[0] = "HH";
    strings["TM##sesd"].plurals[0] = "TM";
    strings["RM##sesd"].plurals[0] = "RM";

    strings["P##sesd"].plurals[0] = "S";

    strings["VS##sesd"].plurals[0] = "VS";

    strings["TR##sesd"].plurals[0] = "TR";
    strings["DMC##sesd"].plurals[0] = "DMC";

    strings["WA##sesd"].plurals[0] = "FA";
}