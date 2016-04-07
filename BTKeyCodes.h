/*
 * Copyright (c) 2015 Evan Kale
 * Email: EvanKale91@gmail.com
 * Website: www.ISeeDeadPixel.com
 *          www.evankale.blogspot.ca
 *
 * This file is part of ArduinoBTPS2.
 *
 * ArduinoBTPS2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef BTKEYCODES_H
#define BTKEYCODES_H

//modifier codes
#define BTMC_NONE 0x00
#define BTMC_CTRL_LEFT 0x01
#define BTMC_SHIFT_LEFT 0x02
#define BTMC_ALT_LEFT 0x04
#define BTMC_GUI_LEFT 0x08
#define BTMC_CTRL_RIGHT 0x10
#define BTMC_SHIFT_RIGHT 0x20
#define BTMC_ALT_RIGHT 0x40
#define BTMC_GUI_RIGHT 0x80

//consumer codes
#define BTCC_NONE 0x0000
#define BTCC_HOME 0x0001
#define BTCC_EMAIL 0x0002
#define BTCC_SEARCH 0x0004
#define BTCC_KEYBOARD_LAYOUT 0x0008
#define BTCC_VOLUME_UP 0x0010
#define BTCC_VOLUME_DOWN 0x0020
#define BTCC_MUTE 0x0040
#define BTCC_PLAY_PAUSE 0x0080
#define BTCC_NEXT_TRACK 0x0100
#define BTCC_PREVIOUS_TRACK 0x0200
#define BTCC_STOP 0x0400
#define BTCC_EJECT 0x0800
#define BTCC_FAST_FORWARD 0x1000
#define BTCC_REWIND 0x2000
#define BTCC_STOP_EJECT 0x4000
#define BTCC_BROWSER 0x8000

//keycodes
#define BTKC_NONE 0x00
#define BTKC_A 0x04
#define BTKC_B 0x05
#define BTKC_C 0x06
#define BTKC_D 0x07
#define BTKC_E 0x08
#define BTKC_F 0x09
#define BTKC_G 0x0A
#define BTKC_H 0x0B
#define BTKC_I 0x0C
#define BTKC_J 0x0D
#define BTKC_K 0x0E
#define BTKC_L 0x0F
#define BTKC_M 0x10
#define BTKC_N 0x11
#define BTKC_O 0x12
#define BTKC_P 0x13
#define BTKC_Q 0x14
#define BTKC_R 0x15
#define BTKC_S 0x16
#define BTKC_T 0x17
#define BTKC_U 0x18
#define BTKC_V 0x19
#define BTKC_W 0x1A
#define BTKC_X 0x1B
#define BTKC_Y 0x1C
#define BTKC_Z 0x1D
#define BTKC_1 0x1E
#define BTKC_2 0x1F
#define BTKC_3 0x20
#define BTKC_4 0x21
#define BTKC_5 0x22
#define BTKC_6 0x23
#define BTKC_7 0x24
#define BTKC_8 0x25
#define BTKC_9 0x26
#define BTKC_0 0x27
#define BTKC_RETURN 0x28
#define BTKC_ESCAPE 0x29
#define BTKC_BACKSPACE 0x2A
#define BTKC_TAB 0x2B
#define BTKC_SPACE 0x2C
#define BTKC_MINUS 0x2D
#define BTKC_EQUAL 0x2E
#define BTKC_BRACKET_LEFT 0x2F
#define BTKC_BRACKET_RIGHT 0x30
#define BTKC_BACKSLASH 0x31
#define BTKC_EUROPE_1 0x32
#define BTKC_SEMICOLON 0x33
#define BTKC_APOSTROPHE 0x34
#define BTKC_GRAVE 0x35
#define BTKC_COMMA 0x36
#define BTKC_PERIOD 0x37
#define BTKC_SLASH 0x38
#define BTKC_CAPS_LOCK 0x39
#define BTKC_F1 0x3A
#define BTKC_F2 0x3B
#define BTKC_F3 0x3C
#define BTKC_F4 0x3D
#define BTKC_F5 0x3E
#define BTKC_F6 0x3F
#define BTKC_F7 0x40
#define BTKC_F8 0x41
#define BTKC_F9 0x42
#define BTKC_F10 0x43
#define BTKC_F11 0x44
#define BTKC_F12 0x45
#define BTKC_PRINT_SCREEN 0x46
#define BTKC_SCROLL_LOCK 0x47
#define BTKC_PAUSE 0x48
#define BTKC_INSERT 0x49
#define BTKC_HOME 0x4A
#define BTKC_PAGE_UP 0x4B
#define BTKC_DELETE 0x4C
#define BTKC_END 0x4D
#define BTKC_PAGE_DOWN 0x4E
#define BTKC_ARROW_RIGHT 0x4F
#define BTKC_ARROW_LEFT 0x50
#define BTKC_ARROW_DOWN 0x51
#define BTKC_ARROW_UP 0x52
#define BTKC_NUM_LOCK 0x53
#define BTKC_KEYPAD_DIVIDE 0x54
#define BTKC_KEYPAD_MULTIPLY 0x55
#define BTKC_KEYPAD_SUBTRACT 0x56
#define BTKC_KEYPAD_ADD 0x57
#define BTKC_KEYPAD_ENTER 0x58
#define BTKC_KEYPAD_1 0x59
#define BTKC_KEYPAD_2 0x5A
#define BTKC_KEYPAD_3 0x5B
#define BTKC_KEYPAD_4 0x5C
#define BTKC_KEYPAD_5 0x5D
#define BTKC_KEYPAD_6 0x5E
#define BTKC_KEYPAD_7 0x5F
#define BTKC_KEYPAD_8 0x60
#define BTKC_KEYPAD_9 0x61
#define BTKC_KEYPAD_0 0x62
#define BTKC_KEYPAD_DECIMAL 0x63
#define BTKC_EUROPE_2 0x64
#define BTKC_APPLICATION 0x65
#define BTKC_POWER 0x66
#define BTKC_KEYPAD_EQUAL 0x67
#define BTKC_F13 0x68
#define BTKC_F14 0x69
#define BTKC_F15 0x6A

//highest bit masked with 1 is a virtual keycode
//ie, 0x80 = 1000000b

//0x80 to 0x87 are modifer keys
// the lower 7 bits defines how much 0x1 is shifted left to get the modifier code
// ie) BTKC_ALT_LEFT = 0x82 (10000010b)
//       lower 7 bits = 0x02 (0000010b)
//       0x1 << 2 = 100b = 0x04 = BTMC_ALT_LEFT
#define BTKC_CTRL_LEFT 0x80
#define BTKC_SHIFT_LEFT 0x81
#define BTKC_ALT_LEFT 0x82
#define BTKC_GUI_LEFT 0x83
#define BTKC_CTRL_RIGHT 0x84
#define BTKC_SHIFT_RIGHT 0x85
#define BTKC_ALT_RIGHT 0x86
#define BTKC_GUI_RIGHT 0x87

//0xC0 to 0xD0 are consumer keys
// the lower 6 bits defines how much 0x1 is shifted left to get the 2 byte consumer code
// ie) BTKC_VOLUME_UP = 0xC4 (11000100b)
//       lower 6 bits = 0x04 (000100b)
//       0x1 << 4 = 10000b = 0x0010 = BTCC_VOLUME_UP
//consumer codes
#define BTKC_HOMEPAGE 0xC0
#define BTKC_EMAIL 0xC1
#define BTKC_SEARCH 0xC2
#define BTKC_KEYBOARD_LAYOUT 0xC3
#define BTKC_VOLUME_UP 0xC4
#define BTKC_VOLUME_DOWN 0xC5
#define BTKC_MUTE 0xC6
#define BTKC_PLAY_PAUSE 0xC7
#define BTKC_NEXT_TRACK 0xC8
#define BTKC_PREVIOUS_TRACK 0xC9
#define BTKC_STOP 0xCA
#define BTKC_EJECT 0xCB
#define BTKC_FAST_FORWARD 0xCD
#define BTKC_REWIND 0xCE
#define BTKC_STOP_EJECT 0xCF
#define BTKC_BROWSER 0xD0

//0xE0 to 0xE2 are system keys
#define BTKC_SYSTEM_POWER 0xE0 //0x81
#define BTKC_SYSTEM_SLEEP 0xE1 //0x82
#define BTKC_SYSTEM_WAKE 0xE2 //0x83


#endif //BTKEYCODES_H
