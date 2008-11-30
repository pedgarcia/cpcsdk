/*
 *   $Id$
 *	 CapriceReloded an Amstrad CPC emulator
 *   Copyright (C) 2008  cpcsdk crew
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */  



//
// Caprice32 input manager
//

#include "input.h"
#include "cap32type.h"
#include "config.h"
#include <wx/defs.h>

typedef enum {
	CPC_0,
	CPC_1,
	CPC_2,
	CPC_3,
	CPC_4,
	CPC_5,
	CPC_6,
	CPC_7,
	CPC_8,
	CPC_9,
	CPC_A,
	CPC_B,
	CPC_C,
	CPC_D,
	CPC_E,
	CPC_F,
	CPC_G,
	CPC_H,
	CPC_I,
	CPC_J,
	CPC_K,
	CPC_L,
	CPC_M,
	CPC_N,
	CPC_O,
	CPC_P,
	CPC_Q,
	CPC_R,
	CPC_S,
	CPC_T,
	CPC_U,
	CPC_V,
	CPC_W,
	CPC_X,
	CPC_Y,
	CPC_Z,
	CPC_a,
	CPC_b,
	CPC_c,
	CPC_d,
	CPC_e,
	CPC_f,
	CPC_g,
	CPC_h,
	CPC_i,
	CPC_j,
	CPC_k,
	CPC_l,
	CPC_m,
	CPC_n,
	CPC_o,
	CPC_p,
	CPC_q,
	CPC_r,
	CPC_s,
	CPC_t,
	CPC_u,
	CPC_v,
	CPC_w,
	CPC_x,
	CPC_y,
	CPC_z,
	CPC_AMPERSAND,
	CPC_ASTERISK,
	CPC_AT,
	CPC_BACKQUOTE,
	CPC_BACKSLASH,
	CPC_CAPSLOCK,
	CPC_CLR,
	CPC_COLON,
	CPC_COMMA,
	CPC_CONTROL,
	CPC_COPY,
	CPC_CPY_DOWN,
	CPC_CPY_LEFT,
	CPC_CPY_RIGHT,
	CPC_CPY_UP,
	CPC_CUR_DOWN,
	CPC_CUR_LEFT,
	CPC_CUR_RIGHT,
	CPC_CUR_UP,
	CPC_CUR_ENDBL,
	CPC_CUR_HOMELN,
	CPC_CUR_ENDLN,
	CPC_CUR_HOMEBL,
	CPC_DBLQUOTE,
	CPC_DEL,
	CPC_DOLLAR,
	CPC_ENTER,
	CPC_EQUAL,
	CPC_ESC,
	CPC_EXCLAMATN,
	CPC_F0,
	CPC_F1,
	CPC_F2,
	CPC_F3,
	CPC_F4,
	CPC_F5,
	CPC_F6,
	CPC_F7,
	CPC_F8,
	CPC_F9,
	CPC_FPERIOD,
	CPC_GREATER,
	CPC_HASH,
	CPC_LBRACKET,
	CPC_LCBRACE,
	CPC_LEFTPAREN,
	CPC_LESS,
	CPC_LSHIFT,
	CPC_MINUS,
	CPC_PERCENT,
	CPC_PERIOD,
	CPC_PIPE,
	CPC_PLUS,
	CPC_POUND,
	CPC_POWER,
	CPC_QUESTION,
	CPC_QUOTE,
	CPC_RBRACKET,
	CPC_RCBRACE,
	CPC_RETURN,
	CPC_RIGHTPAREN,
	CPC_RSHIFT,
	CPC_SEMICOLON,
	CPC_SLASH,
	CPC_SPACE,
	CPC_TAB,
	CPC_UNDERSCORE,
	CPC_J0_UP,
	CPC_J0_DOWN,
	CPC_J0_LEFT,
	CPC_J0_RIGHT,
	CPC_J0_FIRE1,
	CPC_J0_FIRE2,
	CPC_J1_UP,
	CPC_J1_DOWN,
	CPC_J1_LEFT,
	CPC_J1_RIGHT,
	CPC_J1_FIRE1,
	CPC_J1_FIRE2,
	CPC_ES_NTILDE,
	CPC_ES_nTILDE,
	CPC_ES_PESETA,
	CPC_FR_eACUTE,
	CPC_FR_eGRAVE,
	CPC_FR_cCEDIL,
	CPC_FR_aGRAVE,
	CPC_FR_uGRAVE
} CPC_KEYS;

dword t_Input::cpc_kbd[3][149] =
{
	{ // original CPC keyboard
		0x40,						// CPC_0
		0x80,						// CPC_1
		0x81,						// CPC_2
		0x71,						// CPC_3
		0x70,						// CPC_4
		0x61,						// CPC_5
		0x60,						// CPC_6
		0x51,						// CPC_7
		0x50,						// CPC_8
		0x41,						// CPC_9
		0x85 | MOD_CPC_SHIFT,		// CPC_A
		0x66 | MOD_CPC_SHIFT,		// CPC_B
		0x76 | MOD_CPC_SHIFT,		// CPC_C
		0x75 | MOD_CPC_SHIFT,		// CPC_D
		0x72 | MOD_CPC_SHIFT,		// CPC_E
		0x65 | MOD_CPC_SHIFT,		// CPC_F
		0x64 | MOD_CPC_SHIFT,		// CPC_G
		0x54 | MOD_CPC_SHIFT,		// CPC_H
		0x43 | MOD_CPC_SHIFT,		// CPC_I
		0x55 | MOD_CPC_SHIFT,		// CPC_J
		0x45 | MOD_CPC_SHIFT,		// CPC_K
		0x44 | MOD_CPC_SHIFT,		// CPC_L
		0x46 | MOD_CPC_SHIFT,		// CPC_M
		0x56 | MOD_CPC_SHIFT,		// CPC_N
		0x42 | MOD_CPC_SHIFT,		// CPC_O
		0x33 | MOD_CPC_SHIFT,		// CPC_P
		0x83 | MOD_CPC_SHIFT,		// CPC_Q
		0x62 | MOD_CPC_SHIFT,		// CPC_R
		0x74 | MOD_CPC_SHIFT,		// CPC_S
		0x63 | MOD_CPC_SHIFT,		// CPC_T
		0x52 | MOD_CPC_SHIFT,		// CPC_U
		0x67 | MOD_CPC_SHIFT,		// CPC_V
		0x73 | MOD_CPC_SHIFT,		// CPC_W
		0x77 | MOD_CPC_SHIFT,		// CPC_X
		0x53 | MOD_CPC_SHIFT,		// CPC_Y
		0x87 | MOD_CPC_SHIFT,		// CPC_Z
		0x85,						// CPC_a
		0x66,						// CPC_b
		0x76,						// CPC_c
		0x75,						// CPC_d
		0x72,						// CPC_e
		0x65,						// CPC_f
		0x64,						// CPC_g
		0x54,						// CPC_h
		0x43,						// CPC_i
		0x55,						// CPC_j
		0x45,						// CPC_k
		0x44,						// CPC_l
		0x46,						// CPC_m
		0x56,						// CPC_n
		0x42,						// CPC_o
		0x33,						// CPC_p
		0x83,						// CPC_q
		0x62,						// CPC_r
		0x74,						// CPC_s
		0x63,						// CPC_t
		0x52,						// CPC_u
		0x67,						// CPC_v
		0x73,						// CPC_w
		0x77,						// CPC_x
		0x53,						// CPC_y
		0x87,						// CPC_z
		0x60 | MOD_CPC_SHIFT,		// CPC_AMPERSAND
		0x35 | MOD_CPC_SHIFT,		// CPC_ASTERISK
		0x32,						// CPC_AT
		0x26 | MOD_CPC_SHIFT,		// CPC_BACKQUOTE
		0x26,						// CPC_BACKSLASH
		0x86,						// CPC_CAPSLOCK
		0x20,						// CPC_CLR
		0x35,						// CPC_COLON
		0x47,						// CPC_COMMA
		0x27,						// CPC_CONTROL
		0x11,						// CPC_COPY
		0x02 | MOD_CPC_SHIFT,		// CPC_CPY_DOWN
		0x10 | MOD_CPC_SHIFT,		// CPC_CPY_LEFT
		0x01 | MOD_CPC_SHIFT,		// CPC_CPY_RIGHT
		0x00 | MOD_CPC_SHIFT,		// CPC_CPY_UP
		0x02,						// CPC_CUR_DOWN
		0x10,						// CPC_CUR_LEFT
		0x01,						// CPC_CUR_RIGHT
		0x00,						// CPC_CUR_UP
		0x02 | MOD_CPC_CTRL,		// CPC_CUR_ENDBL
		0x10 | MOD_CPC_CTRL,		// CPC_CUR_HOMELN
		0x01 | MOD_CPC_CTRL,		// CPC_CUR_ENDLN
		0x00 | MOD_CPC_CTRL,		// CPC_CUR_HOMEBL
		0x81 | MOD_CPC_SHIFT,		// CPC_DBLQUOTE
		0x97,						// CPC_DEL
		0x70 | MOD_CPC_SHIFT,		// CPC_DOLLAR
		0x06,						// CPC_ENTER
		0x31 | MOD_CPC_SHIFT,		// CPC_EQUAL
		0x82,						// CPC_ESC
		0x80 | MOD_CPC_SHIFT,		// CPC_EXCLAMATN
		0x17,						// CPC_F0
		0x15,						// CPC_F1
		0x16,						// CPC_F2
		0x05,						// CPC_F3
		0x24,						// CPC_F4
		0x14,						// CPC_F5
		0x04,						// CPC_F6
		0x12,						// CPC_F7
		0x13,						// CPC_F8
		0x03,						// CPC_F9
		0x07,						// CPC_FPERIOD
		0x37 | MOD_CPC_SHIFT,		// CPC_GREATER
		0x71 | MOD_CPC_SHIFT,		// CPC_HASH
		0x21,						// CPC_LBRACKET
		0x21 | MOD_CPC_SHIFT,		// CPC_LCBRACE
		0x50 | MOD_CPC_SHIFT,		// CPC_LEFTPAREN
		0x47 | MOD_CPC_SHIFT,		// CPC_LESS
		0x25,						// CPC_LSHIFT
		0x31,						// CPC_MINUS
		0x61 | MOD_CPC_SHIFT,		// CPC_PERCENT
		0x37,						// CPC_PERIOD
		0x32 | MOD_CPC_SHIFT,		// CPC_PIPE
		0x34 | MOD_CPC_SHIFT,		// CPC_PLUS
		0x30 | MOD_CPC_SHIFT,		// CPC_POUND
		0x30,						// CPC_POWER
		0x36 | MOD_CPC_SHIFT,		// CPC_QUESTION
		0x51 | MOD_CPC_SHIFT,		// CPC_QUOTE
		0x23,						// CPC_RBRACKET
		0x23 | MOD_CPC_SHIFT,		// CPC_RCBRACE
		0x22,						// CPC_RETURN
		0x41 | MOD_CPC_SHIFT,		// CPC_RIGHTPAREN
		0x25,						// CPC_RSHIFT
		0x34,						// CPC_SEMICOLON
		0x36,						// CPC_SLASH
		0x57,						// CPC_SPACE
		0x84,						// CPC_TAB
		0x40 | MOD_CPC_SHIFT,		// CPC_UNDERSCORE
		0x90,						// CPC_J0_UP
		0x91,						// CPC_J0_DOWN
		0x92,						// CPC_J0_LEFT
		0x93,						// CPC_J0_RIGHT
		0x94,						// CPC_J0_FIRE1
		0x95,						// CPC_J0_FIRE2
		0x60,						// CPC_J1_UP
		0x61,						// CPC_J1_DOWN
		0x62,						// CPC_J1_LEFT
		0x63,						// CPC_J1_RIGHT
		0x64,						// CPC_J1_FIRE1
		0x65,						// CPC_J1_FIRE2
		0xff,						// CPC_ES_NTILDE
		0xff,						// CPC_ES_nTILDE
		0xff,						// CPC_ES_PESETA
		0xff,						// CPC_FR_eACUTE
		0xff,						// CPC_FR_eGRAVE
		0xff,						// CPC_FR_cCEDIL
		0xff,						// CPC_FR_aGRAVE
		0xff,						// CPC_FR_uGRAVE
	},
	{ // French CPC keyboard
		0x40 | MOD_CPC_SHIFT,		// CPC_0
		0x80 | MOD_CPC_SHIFT,		// CPC_1
		0x81 | MOD_CPC_SHIFT,		// CPC_2
		0x71 | MOD_CPC_SHIFT,		// CPC_3
		0x70 | MOD_CPC_SHIFT,		// CPC_4
		0x61 | MOD_CPC_SHIFT,		// CPC_5
		0x60 | MOD_CPC_SHIFT,		// CPC_6
		0x51 | MOD_CPC_SHIFT,		// CPC_7
		0x50 | MOD_CPC_SHIFT,		// CPC_8
		0x41 | MOD_CPC_SHIFT,		// CPC_9
		0x83 | MOD_CPC_SHIFT,		// CPC_A
		0x66 | MOD_CPC_SHIFT,		// CPC_B
		0x76 | MOD_CPC_SHIFT,		// CPC_C
		0x75 | MOD_CPC_SHIFT,		// CPC_D
		0x72 | MOD_CPC_SHIFT,		// CPC_E
		0x65 | MOD_CPC_SHIFT,		// CPC_F
		0x64 | MOD_CPC_SHIFT,		// CPC_G
		0x54 | MOD_CPC_SHIFT,		// CPC_H
		0x43 | MOD_CPC_SHIFT,		// CPC_I
		0x55 | MOD_CPC_SHIFT,		// CPC_J
		0x45 | MOD_CPC_SHIFT,		// CPC_K
		0x44 | MOD_CPC_SHIFT,		// CPC_L
		0x35 | MOD_CPC_SHIFT,		// CPC_M
		0x56 | MOD_CPC_SHIFT,		// CPC_N
		0x42 | MOD_CPC_SHIFT,		// CPC_O
		0x33 | MOD_CPC_SHIFT,		// CPC_P
		0x85 | MOD_CPC_SHIFT,		// CPC_Q
		0x62 | MOD_CPC_SHIFT,		// CPC_R
		0x74 | MOD_CPC_SHIFT,		// CPC_S
		0x63 | MOD_CPC_SHIFT,		// CPC_T
		0x52 | MOD_CPC_SHIFT,		// CPC_U
		0x67 | MOD_CPC_SHIFT,		// CPC_V
		0x87 | MOD_CPC_SHIFT,		// CPC_W
		0x77 | MOD_CPC_SHIFT,		// CPC_X
		0x53 | MOD_CPC_SHIFT,		// CPC_Y
		0x73 | MOD_CPC_SHIFT,		// CPC_Z
		0x83,						// CPC_a
		0x66,						// CPC_b
		0x76,						// CPC_c
		0x75,						// CPC_d
		0x72,						// CPC_e
		0x65,						// CPC_f
		0x64,						// CPC_g
		0x54,						// CPC_h
		0x43,						// CPC_i
		0x55,						// CPC_j
		0x45,						// CPC_k
		0x44,						// CPC_l
		0x35,						// CPC_m
		0x56,						// CPC_n
		0x42,						// CPC_o
		0x33,						// CPC_p
		0x85,						// CPC_q
		0x62,						// CPC_r
		0x74,						// CPC_s
		0x63,						// CPC_t
		0x52,						// CPC_u
		0x67,						// CPC_v
		0x87,						// CPC_w
		0x77,						// CPC_x
		0x53,						// CPC_y
		0x73,						// CPC_z
		0x80,						// CPC_AMPERSAND
		0x21,						// CPC_ASTERISK
		0x26 | MOD_CPC_SHIFT,		// CPC_AT
		0xff,						// CPC_BACKQUOTE
		0x26 | MOD_CPC_CTRL,		// CPC_BACKSLASH
		0x86,						// CPC_CAPSLOCK
		0x20,						// CPC_CLR
		0x37,						// CPC_COLON
		0x46,						// CPC_COMMA
		0x27,						// CPC_CONTROL
		0x11,						// CPC_COPY
		0x02 | MOD_CPC_SHIFT,		// CPC_CPY_DOWN
		0x10 | MOD_CPC_SHIFT,		// CPC_CPY_LEFT
		0x01 | MOD_CPC_SHIFT,		// CPC_CPY_RIGHT
		0x00 | MOD_CPC_SHIFT,		// CPC_CPY_UP
		0x02,						// CPC_CUR_DOWN
		0x10,						// CPC_CUR_LEFT
		0x01,						// CPC_CUR_RIGHT
		0x00,						// CPC_CUR_UP
		0x02 | MOD_CPC_CTRL,		// CPC_CUR_ENDBL
		0x10 | MOD_CPC_CTRL,		// CPC_CUR_HOMELN
		0x01 | MOD_CPC_CTRL,		// CPC_CUR_ENDLN
		0x00 | MOD_CPC_CTRL,		// CPC_CUR_HOMEBL
		0x71,						// CPC_DBLQUOTE
		0x97,						// CPC_DEL
		0x26,						// CPC_DOLLAR
		0x06,						// CPC_ENTER
		0x36,						// CPC_EQUAL
		0x82,						// CPC_ESC
		0x50,						// CPC_EXCLAMATN
		0x17,						// CPC_F0
		0x15,						// CPC_F1
		0x16,						// CPC_F2
		0x05,						// CPC_F3
		0x24,						// CPC_F4
		0x14,						// CPC_F5
		0x04,						// CPC_F6
		0x12,						// CPC_F7
		0x13,						// CPC_F8
		0x03,						// CPC_F9
		0x07,						// CPC_FPERIOD
		0x23 | MOD_CPC_SHIFT,		// CPC_GREATER
		0x23,						// CPC_HASH
		0x31 | MOD_CPC_SHIFT,		// CPC_LBRACKET
		0xff,						// CPC_LCBRACE
		0x61,						// CPC_LEFTPAREN
		0x21 | MOD_CPC_SHIFT,		// CPC_LESS
		0x25,						// CPC_LSHIFT
		0x30,						// CPC_MINUS
		0x34 | MOD_CPC_SHIFT,		// CPC_PERCENT
		0x47 | MOD_CPC_SHIFT,		// CPC_PERIOD
		0x32 | MOD_CPC_SHIFT,		// CPC_PIPE
		0x36 | MOD_CPC_SHIFT,		// CPC_PLUS
		0xff,						// CPC_POUND
		0x32,						// CPC_POWER
		0x46 | MOD_CPC_SHIFT,		// CPC_QUESTION
		0x70,						// CPC_QUOTE
		0x60,						// CPC_RBRACKET
		0xff,						// CPC_RCBRACE
		0x22,						// CPC_RETURN
		0x31,						// CPC_RIGHTPAREN
		0x25,						// CPC_RSHIFT
		0x47,						// CPC_SEMICOLON
		0x37 | MOD_CPC_SHIFT,		// CPC_SLASH
		0x57,						// CPC_SPACE
		0x84,						// CPC_TAB
		0x30 | MOD_CPC_SHIFT,		// CPC_UNDERSCORE
		0x90,						// CPC_J0_UP
		0x91,						// CPC_J0_DOWN
		0x92,						// CPC_J0_LEFT
		0x93,						// CPC_J0_RIGHT
		0x94,						// CPC_J0_FIRE1
		0x95,						// CPC_J0_FIRE2
		0x60,						// CPC_J1_UP
		0x61,						// CPC_J1_DOWN
		0x62,						// CPC_J1_LEFT
		0x63,						// CPC_J1_RIGHT
		0x64,						// CPC_J1_FIRE1
		0x65,						// CPC_J1_FIRE2
		0xff,						// CPC_ES_NTILDE
		0xff,						// CPC_ES_nTILDE
		0xff,						// CPC_ES_PESETA
		0x81,						// CPC_FR_eACUTE
		0x51,						// CPC_FR_eGRAVE
		0x41,						// CPC_FR_cCEDIL
		0x40,						// CPC_FR_aGRAVE
		0x34,						// CPC_FR_uGRAVE
	},
	{ // Spanish CPC keyboard
		0x40,						// CPC_0
		0x80,						// CPC_1
		0x81,						// CPC_2
		0x71,						// CPC_3
		0x70,						// CPC_4
		0x61,						// CPC_5
		0x60,						// CPC_6
		0x51,						// CPC_7
		0x50,						// CPC_8
		0x41,						// CPC_9
		0x85 | MOD_CPC_SHIFT,		// CPC_A
		0x66 | MOD_CPC_SHIFT,		// CPC_B
		0x76 | MOD_CPC_SHIFT,		// CPC_C
		0x75 | MOD_CPC_SHIFT,		// CPC_D
		0x72 | MOD_CPC_SHIFT,		// CPC_E
		0x65 | MOD_CPC_SHIFT,		// CPC_F
		0x64 | MOD_CPC_SHIFT,		// CPC_G
		0x54 | MOD_CPC_SHIFT,		// CPC_H
		0x43 | MOD_CPC_SHIFT,		// CPC_I
		0x55 | MOD_CPC_SHIFT,		// CPC_J
		0x45 | MOD_CPC_SHIFT,		// CPC_K
		0x44 | MOD_CPC_SHIFT,		// CPC_L
		0x46 | MOD_CPC_SHIFT,		// CPC_M
		0x56 | MOD_CPC_SHIFT,		// CPC_N
		0x42 | MOD_CPC_SHIFT,		// CPC_O
		0x33 | MOD_CPC_SHIFT,		// CPC_P
		0x83 | MOD_CPC_SHIFT,		// CPC_Q
		0x62 | MOD_CPC_SHIFT,		// CPC_R
		0x74 | MOD_CPC_SHIFT,		// CPC_S
		0x63 | MOD_CPC_SHIFT,		// CPC_T
		0x52 | MOD_CPC_SHIFT,		// CPC_U
		0x67 | MOD_CPC_SHIFT,		// CPC_V
		0x73 | MOD_CPC_SHIFT,		// CPC_W
		0x77 | MOD_CPC_SHIFT,		// CPC_X
		0x53 | MOD_CPC_SHIFT,		// CPC_Y
		0x87 | MOD_CPC_SHIFT,		// CPC_Z
		0x85,						// CPC_a
		0x66,						// CPC_b
		0x76,						// CPC_c
		0x75,						// CPC_d
		0x72,						// CPC_e
		0x65,						// CPC_f
		0x64,						// CPC_g
		0x54,						// CPC_h
		0x43,						// CPC_i
		0x55,						// CPC_j
		0x45,						// CPC_k
		0x44,						// CPC_l
		0x46,						// CPC_m
		0x56,						// CPC_n
		0x42,						// CPC_o
		0x33,						// CPC_p
		0x83,						// CPC_q
		0x62,						// CPC_r
		0x74,						// CPC_s
		0x63,						// CPC_t
		0x52,						// CPC_u
		0x67,						// CPC_v
		0x73,						// CPC_w
		0x77,						// CPC_x
		0x53,						// CPC_y
		0x87,						// CPC_z
		0x60 | MOD_CPC_SHIFT,		// CPC_AMPERSAND
		0x21 | MOD_CPC_SHIFT,		// CPC_ASTERISK
		0x32,						// CPC_AT
		0x26 | MOD_CPC_SHIFT,		// CPC_BACKQUOTE
		0x26,						// CPC_BACKSLASH
		0x86,						// CPC_CAPSLOCK
		0x20,						// CPC_CLR
		0x34 | MOD_CPC_SHIFT,		// CPC_COLON
		0x47,						// CPC_COMMA
		0x27,						// CPC_CONTROL
		0x11,						// CPC_COPY
		0x02 | MOD_CPC_SHIFT,		// CPC_CPY_DOWN
		0x10 | MOD_CPC_SHIFT,		// CPC_CPY_LEFT
		0x01 | MOD_CPC_SHIFT,		// CPC_CPY_RIGHT
		0x00 | MOD_CPC_SHIFT,		// CPC_CPY_UP
		0x02,						// CPC_CUR_DOWN
		0x10,						// CPC_CUR_LEFT
		0x01,						// CPC_CUR_RIGHT
		0x00,						// CPC_CUR_UP
		0x02 | MOD_CPC_CTRL,		// CPC_CUR_ENDBL
		0x10 | MOD_CPC_CTRL,		// CPC_CUR_HOMELN
		0x01 | MOD_CPC_CTRL,		// CPC_CUR_ENDLN
		0x00 | MOD_CPC_CTRL,		// CPC_CUR_HOMEBL
		0x81 | MOD_CPC_SHIFT,		// CPC_DBLQUOTE
		0x97,						// CPC_DEL
		0x70 | MOD_CPC_SHIFT,		// CPC_DOLLAR
		0x06,						// CPC_ENTER
		0x31 | MOD_CPC_SHIFT,		// CPC_EQUAL
		0x82,						// CPC_ESC
		0x80 | MOD_CPC_SHIFT,		// CPC_EXCLAMATN
		0x17,						// CPC_F0
		0x15,						// CPC_F1
		0x16,						// CPC_F2
		0x05,						// CPC_F3
		0x24,						// CPC_F4
		0x14,						// CPC_F5
		0x04,						// CPC_F6
		0x12,						// CPC_F7
		0x13,						// CPC_F8
		0x03,						// CPC_F9
		0x07,						// CPC_FPERIOD
		0x37 | MOD_CPC_SHIFT,		// CPC_GREATER
		0x71 | MOD_CPC_SHIFT,		// CPC_HASH
		0x21,						// CPC_LBRACKET
		0xff,						// CPC_LCBRACE
		0x50 | MOD_CPC_SHIFT,		// CPC_LEFTPAREN
		0x47 | MOD_CPC_SHIFT,		// CPC_LESS
		0x25,						// CPC_LSHIFT
		0x31,						// CPC_MINUS
		0x61 | MOD_CPC_SHIFT,		// CPC_PERCENT
		0x37,						// CPC_PERIOD
		0x32 | MOD_CPC_SHIFT,		// CPC_PIPE
		0x23 | MOD_CPC_SHIFT,		// CPC_PLUS
		0xff,						// CPC_POUND
		0x30,						// CPC_POWER
		0x36 | MOD_CPC_SHIFT,		// CPC_QUESTION
		0x51 | MOD_CPC_SHIFT,		// CPC_QUOTE
		0x23,						// CPC_RBRACKET
		0xff,						// CPC_RCBRACE
		0x22,						// CPC_RETURN
		0x41 | MOD_CPC_SHIFT,		// CPC_RIGHTPAREN
		0x25,						// CPC_RSHIFT
		0x34,						// CPC_SEMICOLON
		0x36,						// CPC_SLASH
		0x57,						// CPC_SPACE
		0x84,						// CPC_TAB
		0x40 | MOD_CPC_SHIFT,		// CPC_UNDERSCORE
		0x90,						// CPC_J0_UP
		0x91,						// CPC_J0_DOWN
		0x92,						// CPC_J0_LEFT
		0x93,						// CPC_J0_RIGHT
		0x94,						// CPC_J0_FIRE1
		0x95,						// CPC_J0_FIRE2
		0x60,						// CPC_J1_UP
		0x61,						// CPC_J1_DOWN
		0x62,						// CPC_J1_LEFT
		0x63,						// CPC_J1_RIGHT
		0x64,						// CPC_J1_FIRE1
		0x65,						// CPC_J1_FIRE2
		0x35 | MOD_CPC_SHIFT,		// CPC_ES_NTILDE
		0x35,						// CPC_ES_nTILDE
		0x30 | MOD_CPC_SHIFT,		// CPC_ES_PESETA
		0xff,						// CPC_FR_eACUTE
		0xff,						// CPC_FR_eGRAVE
		0xff,						// CPC_FR_cCEDIL
		0xff,						// CPC_FR_aGRAVE
		0xff,						// CPC_FR_uGRAVE
	}
};

int t_Input::kbd_layout[4][KBD_MAX_ENTRIES][2] =
{
	{ // US PC to CPC keyboard layout translation
		{ CPC_0,			SDLK_0 },
		{ CPC_1,			SDLK_1 },
		{ CPC_2,			SDLK_2 },
		{ CPC_3,			SDLK_3 },
		{ CPC_4,			SDLK_4 },
		{ CPC_5,			SDLK_5 },
		{ CPC_6,			SDLK_6 },
		{ CPC_7,			SDLK_7 },
		{ CPC_8,			SDLK_8 },
		{ CPC_9,			SDLK_9 },
		{ CPC_A,			SDLK_a | MOD_PC_SHIFT },
		{ CPC_B,			SDLK_b | MOD_PC_SHIFT },
		{ CPC_C,			SDLK_c | MOD_PC_SHIFT },
		{ CPC_D,			SDLK_d | MOD_PC_SHIFT },
		{ CPC_E,			SDLK_e | MOD_PC_SHIFT },
		{ CPC_F,			SDLK_f | MOD_PC_SHIFT },
		{ CPC_G,			SDLK_g | MOD_PC_SHIFT },
		{ CPC_H,			SDLK_h | MOD_PC_SHIFT },
		{ CPC_I,			SDLK_i | MOD_PC_SHIFT },
		{ CPC_J,			SDLK_j | MOD_PC_SHIFT },
		{ CPC_K,			SDLK_k | MOD_PC_SHIFT },
		{ CPC_L,			SDLK_l | MOD_PC_SHIFT },
		{ CPC_M,			SDLK_m | MOD_PC_SHIFT },
		{ CPC_N,			SDLK_n | MOD_PC_SHIFT },
		{ CPC_O,			SDLK_o | MOD_PC_SHIFT },
		{ CPC_P,			SDLK_p | MOD_PC_SHIFT },
		{ CPC_Q,			SDLK_q | MOD_PC_SHIFT },
		{ CPC_R,			SDLK_r | MOD_PC_SHIFT },
		{ CPC_S,			SDLK_s | MOD_PC_SHIFT },
		{ CPC_T,			SDLK_t | MOD_PC_SHIFT },
		{ CPC_U,			SDLK_u | MOD_PC_SHIFT },
		{ CPC_V,			SDLK_v | MOD_PC_SHIFT },
		{ CPC_W,			SDLK_w | MOD_PC_SHIFT },
		{ CPC_X,			SDLK_x | MOD_PC_SHIFT },
		{ CPC_Y,			SDLK_y | MOD_PC_SHIFT },
		{ CPC_Z,			SDLK_z | MOD_PC_SHIFT },
		{ CPC_a,			'A' },
		{ CPC_b,			'B' },
		{ CPC_c,			'C' },
		{ CPC_d,			'D' },
		{ CPC_e,			'E' },
		{ CPC_f,			'F' },
		{ CPC_g,			'G' },
		{ CPC_h,			'H' },
		{ CPC_i,			'I' },
		{ CPC_j,			'J' },
		{ CPC_k,			'K' },
		{ CPC_l,			'L' },
		{ CPC_m,			'M' },
		{ CPC_n,			'N' },
		{ CPC_o,			'O' },
		{ CPC_p,			'P' },
		{ CPC_q,			'Q' },
		{ CPC_r,			'R' },
		{ CPC_s,			'S' },
		{ CPC_t,			'T' },
		{ CPC_u,			'U' },
		{ CPC_v,			'V' },
		{ CPC_w,			'W' },
		{ CPC_x,			'X' },
		{ CPC_y,			'Y' },
		{ CPC_z,			'Z' },
		{ CPC_AMPERSAND,	SDLK_7 | MOD_PC_SHIFT },
		{ CPC_ASTERISK,		SDLK_8 | MOD_PC_SHIFT },
		{ CPC_AT,			SDLK_2 | MOD_PC_SHIFT },
		{ CPC_BACKQUOTE,	SDLK_BACKQUOTE },
		{ CPC_BACKSLASH,	SDLK_BACKSLASH },
		{ CPC_CAPSLOCK,		SDLK_CAPSLOCK },
		{ CPC_CLR,			SDLK_DELETE },
		{ CPC_COLON,		SDLK_SEMICOLON | MOD_PC_SHIFT },
		{ CPC_COMMA,		SDLK_COMMA },
		{ CPC_CONTROL,		SDLK_LCTRL },
		{ CPC_COPY,			SDLK_LALT },
		{ CPC_CPY_DOWN,		SDLK_DOWN | MOD_PC_SHIFT },
		{ CPC_CPY_LEFT,		SDLK_LEFT | MOD_PC_SHIFT },
		{ CPC_CPY_RIGHT,	SDLK_RIGHT | MOD_PC_SHIFT },
		{ CPC_CPY_UP,		SDLK_UP | MOD_PC_SHIFT },
		{ CPC_CUR_DOWN,		SDLK_DOWN },
		{ CPC_CUR_LEFT,		SDLK_LEFT },
		{ CPC_CUR_RIGHT,	SDLK_RIGHT },
		{ CPC_CUR_UP,		SDLK_UP },
		{ CPC_CUR_ENDBL,	SDLK_END | MOD_PC_CTRL },
		{ CPC_CUR_HOMELN,	SDLK_HOME },
		{ CPC_CUR_ENDLN,	SDLK_END },
		{ CPC_CUR_HOMEBL,	SDLK_HOME | MOD_PC_CTRL },
		{ CPC_DBLQUOTE,		SDLK_QUOTE | MOD_PC_SHIFT },
		{ CPC_DEL,			SDLK_BACKSPACE },
		{ CPC_DOLLAR,		SDLK_4 | MOD_PC_SHIFT },
		{ CPC_ENTER,		SDLK_KP_ENTER },
		{ CPC_EQUAL,		SDLK_EQUALS },
		{ CPC_ESC,			SDLK_ESCAPE },
		{ CPC_EXCLAMATN,	SDLK_1 | MOD_PC_SHIFT },
		{ CPC_F0,			SDLK_KP0 },
		{ CPC_F1,			SDLK_KP1 },
		{ CPC_F2,			SDLK_KP2 },
		{ CPC_F3,			SDLK_KP3 },
		{ CPC_F4,			SDLK_KP4 },
		{ CPC_F5,			SDLK_KP5 },
		{ CPC_F6,			SDLK_KP6 },
		{ CPC_F7,			SDLK_KP7 },
		{ CPC_F8,			SDLK_KP8 },
		{ CPC_F9,			SDLK_KP9 },
		{ CPC_FPERIOD,		SDLK_KP_PERIOD },
		{ CPC_GREATER,		SDLK_PERIOD | MOD_PC_SHIFT },
		{ CPC_HASH,			SDLK_3 | MOD_PC_SHIFT },
		{ CPC_LBRACKET,		SDLK_LEFTBRACKET },
		{ CPC_LCBRACE,		SDLK_LEFTBRACKET | MOD_PC_SHIFT },
		{ CPC_LEFTPAREN,	SDLK_9 | MOD_PC_SHIFT },
		{ CPC_LESS,			SDLK_COMMA | MOD_PC_SHIFT },
		{ CPC_LSHIFT,		SDLK_LSHIFT },
		{ CPC_MINUS,		SDLK_MINUS },
		{ CPC_PERCENT,		SDLK_5 | MOD_PC_SHIFT },
		{ CPC_PERIOD,		SDLK_PERIOD },
		{ CPC_PIPE,			SDLK_BACKSLASH | MOD_PC_SHIFT },
		{ CPC_PLUS,			SDLK_EQUALS | MOD_PC_SHIFT },
		{ CPC_POUND,		0 },
		{ CPC_POWER,		SDLK_6 | MOD_PC_SHIFT },
		{ CPC_QUESTION,		SDLK_SLASH | MOD_PC_SHIFT },
		{ CPC_QUOTE,		SDLK_QUOTE },
		{ CPC_RBRACKET,		SDLK_RIGHTBRACKET },
		{ CPC_RCBRACE,		SDLK_RIGHTBRACKET | MOD_PC_SHIFT },
		{ CPC_RETURN,		SDLK_RETURN },
		{ CPC_RIGHTPAREN,	SDLK_0 | MOD_PC_SHIFT },
		{ CPC_RSHIFT,		SDLK_RSHIFT },
		{ CPC_SEMICOLON,	SDLK_SEMICOLON },
		{ CPC_SLASH,		SDLK_SLASH },
		{ CPC_SPACE,		SDLK_SPACE },
		{ CPC_TAB,			SDLK_TAB },
		{ CPC_UNDERSCORE,	SDLK_MINUS | MOD_PC_SHIFT },
		{ CAP32_EXIT,		SDLK_F10 },
		{ CAP32_FPS,		SDLK_F12 | MOD_PC_CTRL },
		{ CAP32_FULLSCRN,	SDLK_F1 },
		{ CAP32_JOY,		SDLK_F8 | MOD_PC_CTRL },
		{ CAP32_LOADDRVA,	SDLK_F6 },
		{ CAP32_LOADDRVB,	SDLK_F7 },
		{ CAP32_LOADSNAP,	SDLK_F2 },
		{ CAP32_LOADTAPE,	SDLK_F3 },
		{ CAP32_MF2RESET,	SDLK_F5 | MOD_PC_CTRL },
		{ CAP32_MF2STOP,	SDLK_F11 },
		{ CAP32_OPTIONS,	SDLK_F8 },
		{ CAP32_PAUSE,		SDLK_BREAK },
		{ CAP32_RESET,		SDLK_F5 },
		{ CAP32_SAVESNAP,	SDLK_F4 },
		{ CAP32_SCRNSHOT,	SDLK_PRINT },
		{ CAP32_SPEED,		SDLK_F12 },
		{ CAP32_TAPEPLAY,	SDLK_F3 | MOD_PC_CTRL },
		{ CAP32_DEBUG,		SDLK_F9}
	},
	{ // French PC to CPC keyboard layout translation
 		{ CPC_0,			192 /*SDLK_WORLD_64*/ | MOD_PC_SHIFT }, // _
 		{ CPC_1,			SDLK_AMPERSAND | MOD_PC_SHIFT },
 		{ CPC_2,			201/*SDLK_WORLD_73*/ | MOD_PC_SHIFT},
 		{ CPC_3,			SDLK_QUOTEDBL | MOD_PC_SHIFT },
 		{ CPC_4,			SDLK_QUOTE | MOD_PC_SHIFT },
 		{ CPC_5,			SDLK_LEFTPAREN | MOD_PC_SHIFT },
 		{ CPC_6,			'-' /*SDLK_MINUS*/ | MOD_PC_SHIFT },
 		{ CPC_7,			200 /*SDLK_WORLD_72*/ | MOD_PC_SHIFT },
 		{ CPC_8,			SDLK_UNDERSCORE | MOD_PC_SHIFT },
 		{ CPC_9,			199 /*SDLK_WORLD_71*/ | MOD_PC_SHIFT },
/*		{ CPC_0,			SDLK_0			| MOD_PC_SHIFT	},
		{ CPC_1,			SDLK_1			| MOD_PC_SHIFT	},
		{ CPC_2,			SDLK_2			| MOD_PC_SHIFT	},
		{ CPC_3,			SDLK_3			| MOD_PC_SHIFT	},
		{ CPC_4,			SDLK_4			| MOD_PC_SHIFT	},
		{ CPC_5,			SDLK_5			| MOD_PC_SHIFT	},
		{ CPC_6,			SDLK_6			| MOD_PC_SHIFT	},
		{ CPC_7,			SDLK_7			| MOD_PC_SHIFT	},
		{ CPC_8,			SDLK_8			| MOD_PC_SHIFT	},
		{ CPC_9,			SDLK_9			| MOD_PC_SHIFT	},
		{ CPC_A,			SDLK_q			| MOD_PC_SHIFT	},
		{ CPC_B,			SDLK_b			| MOD_PC_SHIFT	},
		{ CPC_C,			SDLK_c			| MOD_PC_SHIFT	},
		{ CPC_D,			SDLK_d			| MOD_PC_SHIFT	},
		{ CPC_E,			SDLK_e			| MOD_PC_SHIFT	},
		{ CPC_F,			SDLK_f			| MOD_PC_SHIFT	},
		{ CPC_G,			SDLK_g			| MOD_PC_SHIFT	},
		{ CPC_H,			SDLK_h			| MOD_PC_SHIFT	},
		{ CPC_I,			SDLK_i			| MOD_PC_SHIFT	},
		{ CPC_J,			SDLK_j			| MOD_PC_SHIFT	},
		{ CPC_K,			SDLK_k			| MOD_PC_SHIFT	},
		{ CPC_L,			SDLK_l			| MOD_PC_SHIFT	},
		{ CPC_M,			SDLK_m			| MOD_PC_SHIFT	},
		{ CPC_N,			SDLK_n			| MOD_PC_SHIFT	},
		{ CPC_O,			SDLK_o			| MOD_PC_SHIFT	},
		{ CPC_P,			SDLK_p			| MOD_PC_SHIFT	},
		{ CPC_Q,			SDLK_a			| MOD_PC_SHIFT	},
		{ CPC_R,			SDLK_r			| MOD_PC_SHIFT	},
		{ CPC_S,			SDLK_s			| MOD_PC_SHIFT	},
		{ CPC_T,			SDLK_t			| MOD_PC_SHIFT	},
		{ CPC_U,			SDLK_u			| MOD_PC_SHIFT	},
		{ CPC_V,			SDLK_v			| MOD_PC_SHIFT	},
		{ CPC_W,			SDLK_z			| MOD_PC_SHIFT	},
		{ CPC_X,			SDLK_x			| MOD_PC_SHIFT	},
		{ CPC_Y,			SDLK_y			| MOD_PC_SHIFT	},
		{ CPC_Z,			SDLK_w			| MOD_PC_SHIFT	},
		{ CPC_a,			SDLK_q							},
		{ CPC_b,			SDLK_b							},
		{ CPC_c,			SDLK_c							},
		{ CPC_d,			SDLK_d							},
		{ CPC_e,			SDLK_e							},
		{ CPC_f,			SDLK_f							},
		{ CPC_g,			SDLK_g							},
		{ CPC_h,			SDLK_h							},
		{ CPC_i,			SDLK_i							},
		{ CPC_j,			SDLK_j							},
		{ CPC_k,			SDLK_k							},
		{ CPC_l,			SDLK_l							},
		{ CPC_m,			SDLK_m							},
		{ CPC_n,			SDLK_n							},
		{ CPC_o,			SDLK_o							},
		{ CPC_p,			SDLK_p							},
		{ CPC_q,			SDLK_a							},
		{ CPC_r,			SDLK_r							},
		{ CPC_s,			SDLK_s							},
		{ CPC_t,			SDLK_t							},
		{ CPC_u,			SDLK_u							},
		{ CPC_v,			SDLK_v							},
		{ CPC_w,			SDLK_z							},
		{ CPC_x,			SDLK_x							},
		{ CPC_y,			SDLK_y							},
		{ CPC_z,			SDLK_w							},
*/		{ CPC_A,			'A'			| MOD_PC_SHIFT	},
		{ CPC_B,			'B'			| MOD_PC_SHIFT	},
		{ CPC_C,			'C'			| MOD_PC_SHIFT	},
		{ CPC_D,			'D'			| MOD_PC_SHIFT	},
		{ CPC_E,			'E'			| MOD_PC_SHIFT	},
		{ CPC_F,			'F'			| MOD_PC_SHIFT	},
		{ CPC_G,			'G'			| MOD_PC_SHIFT	},
		{ CPC_H,			'H'			| MOD_PC_SHIFT	},
		{ CPC_I,			'I'			| MOD_PC_SHIFT	},
		{ CPC_J,			'J'			| MOD_PC_SHIFT	},
		{ CPC_K,			'K'			| MOD_PC_SHIFT	},
		{ CPC_L,			'L'			| MOD_PC_SHIFT	},
		{ CPC_M,			'M'			| MOD_PC_SHIFT	},
		{ CPC_N,			'N'			| MOD_PC_SHIFT	},
		{ CPC_O,			'O'			| MOD_PC_SHIFT	},
		{ CPC_P,			'P'			| MOD_PC_SHIFT	},
		{ CPC_Q,			'Q'			| MOD_PC_SHIFT	},
		{ CPC_R,			'R'			| MOD_PC_SHIFT	},
		{ CPC_S,			'S'			| MOD_PC_SHIFT	},
		{ CPC_T,			'T'			| MOD_PC_SHIFT	},
		{ CPC_U,			'U'			| MOD_PC_SHIFT	},
		{ CPC_V,			'V'			| MOD_PC_SHIFT	},
		{ CPC_W,			'Y'			| MOD_PC_SHIFT	},
		{ CPC_X,			'X'			| MOD_PC_SHIFT	},
		{ CPC_Y,			'Y'			| MOD_PC_SHIFT	},
		{ CPC_Z,			'Z'			| MOD_PC_SHIFT	},
		{ CPC_a,			'A' },
		{ CPC_b,			'B' },
		{ CPC_c,			'C' },
		{ CPC_d,			'D' },
		{ CPC_e,			'E' },
		{ CPC_f,			'F' },
		{ CPC_g,			'G' },
		{ CPC_h,			'H' },
		{ CPC_i,			'I' },
		{ CPC_j,			'J' },
		{ CPC_k,			'K' },
		{ CPC_l,			'L' },
		{ CPC_m,			'M' },
		{ CPC_n,			'N' },
		{ CPC_o,			'O' },
		{ CPC_p,			'P' },
		{ CPC_q,			'Q' },
		{ CPC_r,			'R' },
		{ CPC_s,			'S' },
		{ CPC_t,			'T' },
		{ CPC_u,			'U' },
		{ CPC_v,			'V' },
		{ CPC_w,			'W' },
		{ CPC_x,			'X' },
		{ CPC_y,			'Y' },
		{ CPC_z,			'Z' },
		{ CPC_AMPERSAND,	SDLK_AMPERSAND					},
		{ CPC_ASTERISK,		SDLK_ASTERISK					},
		{ CPC_AT,		192 /*SDLK_WORLD_64 | MOD_PC_MODE*/	},
		{ CPC_BACKQUOTE,	200 /*SDLK_WORLD_73 | MOD_PC_MODE*/	},
		{ CPC_BACKSLASH,	SDLK_UNDERSCORE	| MOD_PC_MODE	},
		{ CPC_CAPSLOCK,		WXK_CAPITAL /*SDLK_CAPSLOCK*/	},
		{ CPC_CLR,		SDLK_DELETE						},
		{ CPC_COLON,		SDLK_COLON						},
		{ CPC_COMMA,		SDLK_COMMA						},
		{ CPC_CONTROL,		WXK_CONTROL /*SDLK_LCTRL*/		},
		{ CPC_COPY,		307 /*WXK_MENU*/ /*SDLK_LALT*/		},
		{ CPC_CPY_DOWN,		WXK_DOWN /*SDLK_DOWN*/	| MOD_PC_SHIFT	},
		{ CPC_CPY_LEFT,		WXK_LEFT /*SDLK_LEFT*/	| MOD_PC_SHIFT	},
		{ CPC_CPY_RIGHT,	WXK_RIGHT /*SDLK_RIGHT*/| MOD_PC_SHIFT	},
		{ CPC_CPY_UP,		WXK_UP /*SDLK_UP*/	| MOD_PC_SHIFT	},
		{ CPC_CUR_DOWN,		WXK_DOWN /*SDLK_DOWN*/			},
		{ CPC_CUR_LEFT,		WXK_LEFT /*SDLK_LEFT*/			},
		{ CPC_CUR_RIGHT,	WXK_RIGHT /*SDLK_RIGHT*/		},
		{ CPC_CUR_UP,		WXK_UP	/*SDLK_UP*/			},
		{ CPC_CUR_ENDBL,	WXK_END /*SDLK_END*/	| MOD_PC_CTRL	},
		{ CPC_CUR_HOMELN,	WXK_HOME /*SDLK_HOME*/			},
		{ CPC_CUR_ENDLN,	WXK_END /*SDLK_END*/			},
		{ CPC_CUR_HOMEBL,	WXK_HOME /*SDLK_HOME*/	| MOD_PC_CTRL	},
		{ CPC_DBLQUOTE,		SDLK_QUOTEDBL				},
		{ CPC_DEL,			SDLK_BACKSPACE			},
		{ CPC_DOLLAR,		SDLK_DOLLAR				},
		{ CPC_ENTER,		SDLK_KP_ENTER /* UNCHECKED */		},
		{ CPC_EQUAL,		SDLK_EQUALS				},
		{ CPC_ESC,		SDLK_ESCAPE				},
		{ CPC_EXCLAMATN,	SDLK_EXCLAIM				},
		{ CPC_F0,		WXK_NUMPAD0 /*SDLK_KP0*/		},
		{ CPC_F1,		WXK_NUMPAD1 /*SDLK_KP1*/		},
		{ CPC_F2,		WXK_NUMPAD2 /*SDLK_KP2*/		},
		{ CPC_F3,		WXK_NUMPAD3 /*SDLK_KP3*/		},
		{ CPC_F4,		WXK_NUMPAD4 /*SDLK_KP4*/		},
		{ CPC_F5,		WXK_NUMPAD5 /*SDLK_KP5*/		},
		{ CPC_F6,		WXK_NUMPAD6 /*SDLK_KP6*/		},
		{ CPC_F7,		WXK_NUMPAD7 /*SDLK_KP7*/		},
		{ CPC_F8,		WXK_NUMPAD8 /*SDLK_KP8*/		},
		{ CPC_F9,		WXK_NUMPAD9 /*SDLK_KP9*/		},
		{ CPC_FR_aGRAVE,	0 /*SDLK_WORLD_64*/			},
		{ CPC_FR_cCEDIL,	199 /*SDLK_WORLD_71*/			},
		{ CPC_FR_eACUTE,	201 /*SDLK_WORLD_72*/			},
		{ CPC_FR_eGRAVE,	200 /* SDLK_WORLD_73*/			},
		{ CPC_FR_uGRAVE,	217 /*SDLK_WORLD_89*/			},
		{ CPC_FPERIOD,		385 /*SDLK_KP_PERIOD*/			},
		{ CPC_GREATER,		SDLK_LESS		| MOD_PC_SHIFT	},
		{ CPC_HASH,		SDLK_QUOTEDBL		| MOD_PC_MODE	},
		{ CPC_LBRACKET,		SDLK_LEFTPAREN		| MOD_PC_MODE	},
		{ CPC_LCBRACE,		SDLK_QUOTE		| MOD_PC_MODE	},
		{ CPC_LEFTPAREN,	SDLK_LEFTPAREN				},
		{ CPC_LESS,		SDLK_LESS				},
		{ CPC_LSHIFT,		WXK_SHIFT /*SDLK_LSHIFT*/		},
		{ CPC_MINUS,		SDLK_MINUS				},
		{ CPC_PERCENT,		217 /*SDLK_WORLD_89*/	| MOD_PC_SHIFT	},
		{ CPC_PERIOD,		SDLK_SEMICOLON		| MOD_PC_SHIFT	},
		{ CPC_PIPE,		SDLK_MINUS		| MOD_PC_MODE	},
		{ CPC_PLUS,		SDLK_EQUALS		| MOD_PC_SHIFT	},
		{ CPC_POUND,		SDLK_DOLLAR		| MOD_PC_SHIFT	},
		{ CPC_POWER,		188 /*SDLK_CARET*/}, // This is � but ^ is a deadkey we cant get it
		{ CPC_QUESTION,		SDLK_COMMA		| MOD_PC_SHIFT	},
		{ CPC_QUOTE,		SDLK_QUOTE				},
		{ CPC_RBRACKET,		SDLK_RIGHTPAREN		| MOD_PC_MODE	},
		{ CPC_RCBRACE,		SDLK_EQUALS		| MOD_PC_MODE	},
		{ CPC_RETURN,		SDLK_RETURN				},
		{ CPC_RIGHTPAREN,	SDLK_RIGHTPAREN				},
		{ CPC_RSHIFT,		WXK_SHIFT /*SDLK_RSHIFT*/		},
		{ CPC_SEMICOLON,	SDLK_SEMICOLON				},
		{ CPC_SLASH,		SDLK_COLON		| MOD_PC_SHIFT	},
		{ CPC_SPACE,		SDLK_SPACE				},
		{ CPC_TAB,		SDLK_TAB				},
		{ CPC_UNDERSCORE,	SDLK_UNDERSCORE				},
		{ CAP32_EXIT,		SDLK_F10				},
		{ CAP32_FPS,		SDLK_F12		| MOD_PC_CTRL	},
		{ CAP32_FULLSCRN,	SDLK_F1					},
		{ CAP32_JOY,		SDLK_F8			| MOD_PC_CTRL	},
		{ CAP32_LOADDRVA,	SDLK_F6					},
		{ CAP32_LOADDRVB,	SDLK_F7					},
		{ CAP32_LOADSNAP,	SDLK_F2					},
		{ CAP32_LOADTAPE,	SDLK_F3					},
		{ CAP32_MF2RESET,	SDLK_F5			| MOD_PC_CTRL	},
		{ CAP32_MF2STOP,	SDLK_F11				},
		{ CAP32_OPTIONS,	SDLK_F8					},
		{ CAP32_PAUSE,		WXK_PAUSE /*SDLK_BREAK*/		},
		{ CAP32_RESET,		SDLK_F5					},
		{ CAP32_SAVESNAP,	SDLK_F4					},
		{ CAP32_SCRNSHOT,	SDLK_PRINT				},
		{ CAP32_SPEED,		SDLK_F12				},
		{ CAP32_TAPEPLAY,	SDLK_F3			| MOD_PC_CTRL	},
		{ CAP32_DEBUG,		SDLK_F9					}
	},
	{ // Spanish PC to CPC keyboard layout translation
		{ CPC_0, 			SDLK_0 },
		{ CPC_1, 			SDLK_1 },
		{ CPC_2, 			SDLK_2 },
		{ CPC_3, 			SDLK_3 },
		{ CPC_4, 			SDLK_4 },
		{ CPC_5, 			SDLK_5 },
		{ CPC_6, 			SDLK_6 },
		{ CPC_7, 			SDLK_7 },
		{ CPC_8, 			SDLK_8 },
		{ CPC_9, 			SDLK_9 },
		{ CPC_A, 			SDLK_a | MOD_PC_SHIFT },
		{ CPC_B, 			SDLK_b | MOD_PC_SHIFT },
		{ CPC_C, 			SDLK_c | MOD_PC_SHIFT },
		{ CPC_D, 			SDLK_d | MOD_PC_SHIFT },
		{ CPC_E, 			SDLK_e | MOD_PC_SHIFT },
		{ CPC_F, 			SDLK_f | MOD_PC_SHIFT },
		{ CPC_G, 			SDLK_g | MOD_PC_SHIFT },
		{ CPC_H, 			SDLK_h | MOD_PC_SHIFT },
		{ CPC_I, 			SDLK_i | MOD_PC_SHIFT },
		{ CPC_J, 			SDLK_j | MOD_PC_SHIFT },
		{ CPC_K, 			SDLK_k | MOD_PC_SHIFT },
		{ CPC_L, 			SDLK_l | MOD_PC_SHIFT },
		{ CPC_M, 			SDLK_m | MOD_PC_SHIFT },
		{ CPC_N, 			SDLK_n | MOD_PC_SHIFT },
		{ CPC_O, 			SDLK_o | MOD_PC_SHIFT },
		{ CPC_P, 			SDLK_p | MOD_PC_SHIFT },
		{ CPC_Q, 			SDLK_q | MOD_PC_SHIFT },
		{ CPC_R, 			SDLK_r | MOD_PC_SHIFT },
		{ CPC_S, 			SDLK_s | MOD_PC_SHIFT },
		{ CPC_T, 			SDLK_t | MOD_PC_SHIFT },
		{ CPC_U, 			SDLK_u | MOD_PC_SHIFT },
		{ CPC_V, 			SDLK_v | MOD_PC_SHIFT },
		{ CPC_W, 			SDLK_w | MOD_PC_SHIFT },
		{ CPC_X, 			SDLK_x | MOD_PC_SHIFT },
		{ CPC_Y, 			SDLK_y | MOD_PC_SHIFT },
		{ CPC_Z, 			SDLK_z | MOD_PC_SHIFT },
		{ CPC_a, 			SDLK_a },
		{ CPC_b, 			SDLK_b },
		{ CPC_c, 			SDLK_c },
		{ CPC_d, 			SDLK_d },
		{ CPC_e, 			SDLK_e },
		{ CPC_f, 			SDLK_f },
		{ CPC_g, 			SDLK_g },
		{ CPC_h, 			SDLK_h },
		{ CPC_i, 			SDLK_i },
		{ CPC_j, 			SDLK_j },
		{ CPC_k, 			SDLK_k },
		{ CPC_l, 			SDLK_l },
		{ CPC_m, 			SDLK_m },
		{ CPC_n, 			SDLK_n },
		{ CPC_o, 			SDLK_o },
		{ CPC_p, 			SDLK_p },
		{ CPC_q, 			SDLK_q },
		{ CPC_r, 			SDLK_r },
		{ CPC_s, 			SDLK_s },
		{ CPC_t, 			SDLK_t },
		{ CPC_u, 			SDLK_u },
		{ CPC_v, 			SDLK_v },
		{ CPC_w, 			SDLK_w },
		{ CPC_x, 			SDLK_x },
		{ CPC_y, 			SDLK_y },
		{ CPC_z, 			SDLK_z },
		{ CPC_AMPERSAND,	SDLK_7 | MOD_PC_SHIFT },
		{ CPC_ASTERISK,		SDLK_8 | MOD_PC_SHIFT },
		{ CPC_AT,			SDLK_2 | MOD_PC_SHIFT },
		{ CPC_BACKQUOTE,	SDLK_BACKQUOTE },
		{ CPC_BACKSLASH,	SDLK_BACKSLASH },
		{ CPC_CAPSLOCK,		SDLK_CAPSLOCK },
		{ CPC_CLR,			SDLK_DELETE },
		{ CPC_COLON, 		SDLK_SEMICOLON | MOD_PC_SHIFT },
		{ CPC_COMMA, 		SDLK_COMMA },
		{ CPC_CONTROL,		SDLK_LCTRL },
		{ CPC_COPY,		SDLK_LALT },
		{ CPC_CPY_DOWN,		SDLK_DOWN | MOD_PC_SHIFT },
		{ CPC_CPY_LEFT,		SDLK_LEFT | MOD_PC_SHIFT },
		{ CPC_CPY_RIGHT,	SDLK_RIGHT | MOD_PC_SHIFT },
		{ CPC_CPY_UP,		SDLK_UP | MOD_PC_SHIFT },
		{ CPC_CUR_DOWN,		SDLK_DOWN },
		{ CPC_CUR_LEFT,		SDLK_LEFT },
		{ CPC_CUR_RIGHT,	SDLK_RIGHT },
		{ CPC_CUR_UP,		SDLK_UP },
		{ CPC_CUR_ENDBL,	SDLK_END | MOD_PC_CTRL },
		{ CPC_CUR_HOMELN,	SDLK_HOME },
		{ CPC_CUR_ENDLN,	SDLK_END },
		{ CPC_CUR_HOMEBL,	SDLK_HOME | MOD_PC_CTRL },
		{ CPC_DBLQUOTE,		SDLK_QUOTE | MOD_PC_SHIFT },
		{ CPC_DEL,			SDLK_BACKSPACE },
		{ CPC_DOLLAR,		SDLK_4 | MOD_PC_SHIFT },
		{ CPC_ENTER, 		SDLK_KP_ENTER },
		{ CPC_EQUAL, 		SDLK_EQUALS },
		{ CPC_ESC,			SDLK_ESCAPE },
		{ CPC_EXCLAMATN,	SDLK_1 | MOD_PC_SHIFT },
		{ CPC_F0,			SDLK_KP0 },
		{ CPC_F1,			SDLK_KP1 },
		{ CPC_F2,			SDLK_KP2 },
		{ CPC_F3,			SDLK_KP3 },
		{ CPC_F4,			SDLK_KP4 },
		{ CPC_F5,			SDLK_KP5 },
		{ CPC_F6,			SDLK_KP6 },
		{ CPC_F7,			SDLK_KP7 },
		{ CPC_F8,			SDLK_KP8 },
		{ CPC_F9,			SDLK_KP9 },
		{ CPC_FPERIOD,		SDLK_KP_PERIOD },
		{ CPC_GREATER,		SDLK_PERIOD | MOD_PC_SHIFT },
		{ CPC_HASH,			SDLK_3 | MOD_PC_SHIFT },
		{ CPC_LBRACKET,		SDLK_LEFTBRACKET },
		{ CPC_LCBRACE,		SDLK_LEFTBRACKET | MOD_PC_SHIFT },
		{ CPC_LEFTPAREN,	SDLK_9 | MOD_PC_SHIFT },
		{ CPC_LESS,			SDLK_COMMA | MOD_PC_SHIFT },
		{ CPC_LSHIFT,		WXK_SHIFT /*SDLK_LSHIFT*/ },
		{ CPC_MINUS, 		SDLK_MINUS },
		{ CPC_PERCENT,		SDLK_5 | MOD_PC_SHIFT },
		{ CPC_PERIOD,		SDLK_PERIOD },
		{ CPC_PIPE,			SDLK_BACKSLASH | MOD_PC_SHIFT },
		{ CPC_PLUS,			SDLK_EQUALS | MOD_PC_SHIFT },
		{ CPC_POUND, 		0 },
		{ CPC_POWER, 		SDLK_6 | MOD_PC_SHIFT },
		{ CPC_QUESTION,		SDLK_SLASH | MOD_PC_SHIFT },
		{ CPC_QUOTE, 		SDLK_QUOTE },
		{ CPC_RBRACKET,		SDLK_RIGHTBRACKET },
		{ CPC_RCBRACE,		SDLK_RIGHTBRACKET | MOD_PC_SHIFT },
		{ CPC_RETURN,		SDLK_RETURN },
		{ CPC_RIGHTPAREN,	SDLK_0 | MOD_PC_SHIFT },
		{ CPC_RSHIFT,		WXK_SHIFT /*SDLK_RSHIFT*/ },
		{ CPC_SEMICOLON,	SDLK_SEMICOLON },
		{ CPC_SLASH, 		SDLK_SLASH },
		{ CPC_SPACE, 		SDLK_SPACE },
		{ CPC_TAB,			SDLK_TAB },
		{ CPC_UNDERSCORE,	SDLK_MINUS | MOD_PC_SHIFT },
		{ CAP32_EXIT,		SDLK_F10 },
		{ CAP32_FPS, 		SDLK_F12 | MOD_PC_CTRL },
		{ CAP32_FULLSCRN,	SDLK_F1 },
		{ CAP32_JOY, 		SDLK_F8 | MOD_PC_CTRL },
		{ CAP32_LOADDRVA,	SDLK_F6 },
		{ CAP32_LOADDRVB,	SDLK_F7 },
		{ CAP32_LOADSNAP,	SDLK_F2 },
		{ CAP32_LOADTAPE,	SDLK_F3 },
		{ CAP32_MF2RESET,	SDLK_F5 | MOD_PC_CTRL },
		{ CAP32_MF2STOP,	SDLK_F11 },
		{ CAP32_OPTIONS,	SDLK_F8 },
		{ CAP32_PAUSE,		SDLK_BREAK },
		{ CAP32_RESET,		SDLK_F5 },
		{ CAP32_SAVESNAP,	SDLK_F4 },
		{ CAP32_SCRNSHOT,	SDLK_PRINT },
		{ CAP32_SPEED,		SDLK_F12 },
		{ CAP32_TAPEPLAY,	SDLK_F3 | MOD_PC_CTRL },
		{ CAP32_DEBUG,		SDLK_F9}
	}
};

int t_Input::joy_layout[12][2] =
{
	{ CPC_J0_UP,		SDLK_UP },
	{ CPC_J0_DOWN,		SDLK_DOWN },
	{ CPC_J0_LEFT,		SDLK_LEFT },
	{ CPC_J0_RIGHT,		SDLK_RIGHT },
	{ CPC_J0_FIRE1,		SDLK_z },
	{ CPC_J0_FIRE2,		SDLK_x },
	{ CPC_J1_UP,		0 },
	{ CPC_J1_DOWN,		0 },
	{ CPC_J1_LEFT,		0 },
	{ CPC_J1_RIGHT,		0 },
	{ CPC_J1_FIRE1,		0 },
	{ CPC_J1_FIRE2,		0 }
};

void t_Input::Reset()
{
	// clear CPC keyboard matrix
	memset(keyboard_matrix, 0xff, sizeof(keyboard_matrix));
}

void t_Input::input_swap_joy (t_CPC &CPC)
{
	dword n, pc_idx, val;

	for (n = 0; n < 6; n++)
	{
		// get the PC key to change the assignment for
		pc_idx = joy_layout[n][1];
		if (pc_idx)
		{
			// keep old value
			val = keyboard_normal[pc_idx];
			// assign new function
			keyboard_normal[pc_idx] = cpc_kbd[CPC.keyboard][joy_layout[n][0]];
			// store old value
			cpc_kbd[CPC.keyboard][joy_layout[n][0]] = val;
		}
	}
}



int t_Input::input_init (t_CPC &CPC)
{
	dword n, pc_key, pc_idx, cpc_idx, cpc_key;

	memset(keyboard_normal, 0xff, sizeof(keyboard_normal));
	memset(keyboard_shift, 0xff, sizeof(keyboard_shift));
	memset(keyboard_ctrl, 0xff, sizeof(keyboard_ctrl));
	memset(keyboard_mode, 0xff, sizeof(keyboard_mode));

	for (n = 0; n < KBD_MAX_ENTRIES; n++)
	{
		// PC key assigned to CPC key
		pc_key = kbd_layout[CPC.kbd_layout][n][1];
		if (pc_key)
		{
			// strip off modifier
			pc_idx = pc_key & 0xffff;
			cpc_idx = kbd_layout[CPC.kbd_layout][n][0];

			if (cpc_idx & MOD_EMU_KEY)
			{
				cpc_key = cpc_idx;
			}
			else
			{
				cpc_key = cpc_kbd[CPC.keyboard][cpc_idx];
			}

			// key + SHIFT?
			if (pc_key & MOD_PC_SHIFT)
			{
				// copy CPC key matrix value to SHIFT table
				keyboard_shift[pc_idx] = cpc_key;
			}
			// key + CTRL?
			else if (pc_key & MOD_PC_CTRL)
			{
				// copy CPC key matrix value to CTRL table
				keyboard_ctrl[pc_idx] = cpc_key;
			}
			// key + AltGr?
			else if (pc_key & MOD_PC_MODE)
			{
				// copy CPC key matrix value to AltGr table
				keyboard_mode[pc_idx] = cpc_key;
			}
			else
			{
				// copy CPC key matrix value to normal table
				keyboard_normal[pc_idx] = cpc_key;

				// not an emulator function key?
				if (!(cpc_key & MOD_EMU_KEY))
				{
					// SHIFT table entry has no value yet?
					if (keyboard_shift[pc_idx] == 0xffffffff)
					{
						// duplicate entry in SHIFT table
						keyboard_shift[pc_idx] = cpc_key;
					}

					// CTRL table entry has no value yet?
					if (keyboard_ctrl[pc_idx] == 0xffffffff)
					{
						// duplicate entry in CTRL table
						keyboard_ctrl[pc_idx] = cpc_key | MOD_CPC_CTRL;
					}

					// AltGr table entry has no value yet?
					if (keyboard_mode[pc_idx] == 0xffffffff)
					{
						// duplicate entry in AltGr table
						keyboard_mode[pc_idx] = cpc_key;
					}
				}
			}
		}
	}

	// enable keyboard joystick emulation?
	if (CPC.joysticks)
	{
		input_swap_joy(CPC);
	}

	return 0;
}
