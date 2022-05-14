/* FCE Ultra - NES/Famicom Emulator
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "share.h"

static uint32 lcdCompZapperStrobe[2];

typedef struct {
    uint32 trigger;
    uint32 detect;
} ZAPPER;

static ZAPPER ZD[2];

static uint8 FP_FASTAPASS(1) ReadLCDCompZapper(int w)
{
    uint8 ret = 0;
    if (ZD[w].trigger)
        ret |= 0x10;
    if (!ZD[w].detect)
        ret |= 0x8;
    return ret;
}

static void FP_FASTAPASS(1) StrobeLCDCompZapper(int w)
{
    lcdCompZapperStrobe[w] = 0;
}

void FP_FASTAPASS(3) UpdateLCDCompZapper(int w, void *data, int arg)
{
     uint32* ptr = (uint32*)data;

    ZD[w].trigger = ptr[0];
    ZD[w].detect = ptr[1];
}

static INPUTC LCDCompZapperCtrl = { ReadLCDCompZapper,0,StrobeLCDCompZapper,UpdateLCDCompZapper,0,0 };

INPUTC *FCEU_InitLCDCompZapper(int w)
{
    memset(&ZD[w], 0, sizeof(ZAPPER));
    return(&LCDCompZapperCtrl);
}