#pragma once
#include "Gui.h"

enum GUI_API Key {

    Empty = 0x00,

    Backspace = 0x08,   // BACKSPACE key
    Tab = 0x09,   // TAB key

    Enter = 0x0D,   // ENTER key
    Esc = 0x1B,   // ESC key

    PageUp = 0x21,   // PAGE UP key
    PageDown = 0x22,   // PAGE DOWN key
    End = 0x23,   // END key
    Home = 0x24,   // HOME key
    LeftArrow = 0x25,   // LEFT ARROW key
    RightArrow = 0x27,   // RIGHT ARROW key
    UpArrow = 0x26,   // UP ARROW key
    DownArrow = 0x28,   // DOWN ARROW key

    Insert = 0x2D,   // INS key
    Delete = 0x2E,   // DEL key

    F1 = 0x70,   // F1 key
    F2 = 0x71,   // F2 key
    F3 = 0x72,   // F3 key
    F4 = 0x73,   // F4 key
    F5 = 0x74,   // F5 key
    F6 = 0x75,   // F6 key
    F7 = 0x76,   // F7 key
    F8 = 0x77,   // F8 key
    F9 = 0x78,   // F9 key
    F10 = 0x79,   // F10 key
    F11 = 0x7A,   // F11 key
    F12 = 0x7B    // F12 key
};

enum GUI_API KeyFlag {

    NoKey = 0x00,   // No key flag
    Shift = 0x01,   // Shift key
    Ctrl = 0x02,   // Control key
    Alt = 0x03    // Alt key
};