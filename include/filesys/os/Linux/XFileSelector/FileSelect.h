/*RenDev#2616 File Selector Tool
    Copyright (C) 2021 RenDev

    Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
    Permission is also granted to not credit the author in any way as long as you do not take credit
    for this piece of software.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    binary, for any purpose, commercial or non-commercial, and by any
    means.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, 
    OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
    DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS 
    ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Contact me at vgngamingnetwork@gmail.com if you need to contact me about this licence*/

#include "utils/Window.h"
#include <functional>

#define SCREEN_W 500
#define SCREEN_H 500


class FileSelect : public MainWin{
    public:
        FileSelect(std::string title, v2d<unsigned int> dimentions, bool save_mode, bool isPipe = false, bool select_mode = true);

    public:
        void Start(void* ret_string_ptr);

        void Event(XEvent* event);

        void Redraw();

        void ClearItems();

        void AddItems();

        void RefreshItemList();
    public:
        Directory curdir;
        std::string ret;
        unsigned int selected;
        std::string usr;
        

        struct dirnode{std::string name; int type;};
        std::vector<dirnode> dircontents;
        unsigned int static_buttons_count = 0;

    public:
        struct{
            bool end : 1;
            bool select_mode : 1;
            bool show_hidden : 1;
            bool isPipe : 1;
        };
    private:
        

        void init_main_buttons();
};

extern FileSelect* fsel;
