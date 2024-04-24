# FZT sound source

a fakebit software synth engine designed by LTVA. it is used in [Flizzer Tracker](https://github.com/LTVA1/flizzer_tracker).

Furnace-B provides support for both importing and exporting `.fzt` files for the tracker. since tracker engine is different from Furnace-B one, FZT sound source substitues pitch calculation and effects execution with excerpts from Flizzer Tracker code. more on that below.

## effects

- `10xx`: **change wave.** lower 6 bits specify the wave:
  - `bit 0`: noise
  - `bit 1`: pulse
  - `bit 2`: triangle
  - `bit 3`: sawtooth
  - `bit 3`: metallic noise
  - `bit 3`: sine
- `11xy`: **PWM (pulsolo).** `x` is speed and `y` is depth.
- `12xx`: **set pulse width.**
- `13xx`: **pulse width up.**
- `14xx`: **pulse width down.**
- `15xx`: **set filter cutoff.**
- `16xx`: **set volume.**
  - `.fzt` file format does not allow volume in vol column to go higher than `0x80`. this effect allows to go up to `0xFF`.
- `17xx`: **toggle filter.**
  - `xx` = 0 disable, `xx` > 0 enable filter
- `18xx`: **set filter mode.**
  - `xx` is from `0` to `7`
- `19xx`: **phase reset** on tick `xx`
- `1Axx`: **filter cutoff up**
- `1Bxx`: **filter cutoff down**
- `1Cxx`: **set filter resonance**
- `1Dxx`: **filter resonance up**
- `1Exx`: **filter resonance down**
- `1Fxx`: **ring modulation source**
  - `FF` is self-modulation
- `20xx`: **hard sync source**
  - `FF` is self-sync
- `21xx`: **set attack speed**
- `22xx`: **set decay speed**
- `23xx`: **set sustain level**
- `24xx`: **set release speed**
- `25xx`: **restart instrument program**
- `26xx`: **portamento up (semitones)**
- `27xx`: **portamento down (semitones)**
- `28xx`: **absolute arpeggio note**
- `29xx`: **trigger envelope release**

## effects execution

since FZT sound source was made with the primary goal of letting people write music for Flizzer Tracker in Furnace-B, the effects execution was altered so that almost identical song playback is achieved compared to Flizzer Tracker. However, to achieve this, some changes were made:

- **Volume does not persist unless you use volume macro**. this means that you need to specify the volume for *each new note* for FZT sound source.
- **Some effects are no longer continuous.** `01xx`, `02xx` effects are not continuous for FZT sound source. It means that instead of
```
C-4 01 .. ....
... .. .. ....
... .. .. 0280
... .. .. ....
... .. .. ....
... .. .. ....
... .. .. ....
... .. .. 0200
D-4 01 .. ....
```
you need to enter
```
C-4 01 .. ....
... .. .. ....
... .. .. 0280
... .. .. 0280
... .. .. 0280
... .. .. 0280
... .. .. 0280
... .. .. ....
D-4 01 .. ....
```
to achieve the same sound.

## info

this chip uses the [FZT](../4-instrument/fzt.md) instrument editor.
