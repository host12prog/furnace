//  ---------------------------------------------------------------------------
//  This file is part of reSID, a MOS6581_2 SID2 emulator engine.
//  Copyright (C) 2004  Dag Lem <resid@nimrod.no>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//  ---------------------------------------------------------------------------

#include "siddefs.h"

// ----------------------------------------------------------------------------
// The audio output stage in a Commodore 64 consists of two STC networks,
// a low-pass filter with 3-dB frequency 16kHz followed by a high-pass
// filter with 3-dB frequency 16Hz (the latter provided an audio equipment
// input impedance of 1kOhm).
// The STC networks are connected with a BJT supposedly meant to act as
// a unity gain buffer, which is not really how it works. A more elaborate
// model would include the BJT, however DC circuit analysis yields BJT
// base-emitter and emitter-base impedances sufficiently low to produce
// additional low-pass and high-pass 3dB-frequencies in the order of hundreds
// of kHz. This calls for a sampling frequency of several MHz, which is far
// too high for practical use.
// ----------------------------------------------------------------------------
class ExternalFilter2
{
public:
  ExternalFilter2();

  void enable_filter(bool enable);
  void set_chip_model(chip_model2 model);

  RESID_INLINE void clock(sound_sample Vi);
  void reset();

  // Audio output (20 bits).
  RESID_INLINE sound_sample output();

protected:
  // Filter2 enabled.
  bool enabled;

  // Maximum mixer DC offset.
  sound_sample mixer_DC;

  // State of filters.
  sound_sample Vlp; // lowpass
  sound_sample Vhp; // highpass
  sound_sample Vo;

  // Cutoff frequencies.
  sound_sample w0lp;
  sound_sample w0hp;

friend class SID2;
};


// ----------------------------------------------------------------------------
// Inline functions.
// The following functions are defined inline because they are called every
// time a sample is calculated.
// ----------------------------------------------------------------------------

#if RESID_INLINING || defined(__EXTFILT_CC__)

// ----------------------------------------------------------------------------
// SID2 clocking - 1 cycle.
// ----------------------------------------------------------------------------
RESID_INLINE
void ExternalFilter2::clock(sound_sample Vi)
{
  Vo = Vi;
}


// ----------------------------------------------------------------------------
// Audio output (19.5 bits).
// ----------------------------------------------------------------------------
RESID_INLINE
sound_sample ExternalFilter2::output()
{
  return Vo;
}

#endif // RESID_INLINING || defined(__EXTFILT_CC__)
