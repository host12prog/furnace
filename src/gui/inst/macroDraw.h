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

#pragma once

#include "../gui.h"
#include "../guiConst.h"
#include "IconsFontAwesome4.h"
#include "furIcons.h"

#define P(x) if (x) { \
  MARK_MODIFIED; \
  e->notifyInsChange(curIns); \
  updateFMPreview=true; \
}

#define PARAMETER MARK_MODIFIED; e->notifyInsChange(curIns); updateFMPreview=true;

#define WAVE_MACRO_MAX (MAX(MAX(1,e->song.waveLen-1), MAX(1, ((int)e->song.ins[curIns]->std.local_waves.size() - 1))))

String genericGuide(float value);
int deBit30(const int val);
bool enBit30(const int val);
String macroHoverNote(int id, float val, void* u);
String macroHover(int id, float val, void* u);
String macroHoverLoop(int id, float val, void* u);
String macroHoverBit30Arp(int id, float val, void* u);
String macroHoverBit30Wave(int id, float val, void* u);

char* int_to_char_array(int num);
String macroHoverGain(int id, float val, void* u);
String macroHoverES5506FilterMode(int id, float val, void* u);
String macroLFOWaves(int id, float val, void* u);