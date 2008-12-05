/**
 * Copyright (C) 2008 Ubixum, Inc. 
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **/

#ifndef DELAY_H
#define DELAY_H

#include "fx2types.h"

/**
 * 0-65536 millis
 **/
void delay(WORD millis);

/**
 * See TRM 15-14,15-15
 * some registers (r/w) require syncdelay after
 *
 * up to the programmer to determine which sync is needed.
 * for standard 48mhz clock w/ 48mhz IFCONFIG 3 nops is sufficient.
 *
 * slower clock and faster ifclock require more delay
 *
 * min delay = roof ( 1.5 x (ifclock/clkout + 1) )
 *
 * Minimum IFCLOCK is 5mhz but you have to use an
 * external clock source to go below 30mhz
 * IFCLKSRC 1 = internal, 0=external
 * 3048mhz 0 = 30mhz, 1 = 48mzh
 * figure your own sync delay out if IFCLKSRC=0
 * 
 **/

#define NOP _asm nop _endasm

//ifcfg/clk
// 48/12
// ceil(1.5 * (20.8 / 83.3 + 1)) = 2
#define SYNCDELAY2 NOP; NOP

// 48/24
#define SYNCDELAY3 NOP; NOP; NOP

// 48/48
// also needs 3

// 30/12
// also use 3

// 30/24
// also use 3

// 30/48
#define SYNCDELAY4 NOP; NOP; NOP; NOP

#endif
