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
        #define colstr(printf_instr, text_color) \
        printf(text_color); \
        printf_instr; \
        printf(T_RESET);
    #else
        #define colstr(printf_instr, text_color) printf_instr;
    #endif