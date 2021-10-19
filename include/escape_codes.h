/*RenDev#2616 SM64SFM
    Copyright (C) 2021 RenDev

    Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
    Permission is also granted to not credit the author in any way as long as you do not take credit
    for this piece of software.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, 
    OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
    DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS 
    ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Contact me at vgngamingnetwork@gmail.com if you need to contact me about this licence*/
#ifndef USE_COLORS
    #define USE_COLORS 1
#endif



#if (USE_COLORS == 1)
    #define T_RESET "\033[0m"
    #define T_BLACK "\033[0;30m"
    #define T_RED "\033[0;31m"
    #define T_GREEN "\033[0;32m"
    #define T_YELLOW "\033[0;33m"
    #define T_BLUE "\033[0;34m"
    #define T_MAGENTA "\033[0;35m"
    #define T_CYAN "\033[0;36m"
    #define T_WHITE "\033[0;37m"

    #define B_BLACK "\033[0;40m"
    #define B_RED "\033[0;41m"
    #define B_GREEN "\033[0;42m"
    #define B_YELLOW "\033[0;43m"
    #define B_BLUE "\033[0;44m"
    #define B_MAGENTA "\033[0;45m"
    #define B_CYAN "\033[0;46m"
    #define B_WHITE "\033[0;47m"


#endif

    #if defined(__linux__) || defined(__MINGW32__) || defined(__EMSCRIPTEN__) || defined(__FreeBSD__)
        #define OS Linux
        #define colstr(printf_instr, text_color) \
        printf(text_color); \
        printf_instr; \
        printf(T_RESET);
    #else
        #define OS Win
        #define colstr(printf_instr, text_color) printf_instr;
    #endif