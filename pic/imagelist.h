#pragma once
#include <_typedefs.h>

#if !defined(WIN32) && !defined(_WIN32)
#define TRUE _TRUE
#define FALSE _FALSE
#endif

enum PNGS{
    BOB,
    WF,
    CCM,
    JRB,
    WDW,
    THI,
    TTC,
    RR,
    TTM,
    LLL,
    SSL,
    HMC,
    BBH,
    DDD,

    //Swtich assests
    BLUE,
    BLUE_,
    GREEN,
    GREEN_,
    RED,
    RED_,

    BOX_VANISH,
    BOX_METAL,
    BOX_WING,
    BOX_NONE,
    BOX_MARK,


    //Coin animations

    C_0,
    C_1,
    C_2,
    C_3,
    C_4,
    C_5,
    C_6,
    C_7,
    C_FULL,

    //Menu Buttons

    A_0,
    A_1,
    _TRUE,
    _FALSE,
    MOD,
    TOGGLE,
    TOP,

    //Cursor
    CUR_OPEN,
    CUR_CLOSED,

    //Sparkle Animations
    SPARK_0,    
    SPARK_1,
    SPARK_2,
    SPARK_3,
    SPARK_4,    
    SPARK_5,

    //Icons
    BOMB,
    BOMB_,
    BOWSER,
    DOOR,
    STAR_DOOR_L,
    STAR_DOOR_R,
    PEACH,
    SIGN,
    TOAD_MIPS,
    SAVE_VALID,
    SAVE_NOT_VALID,

    //Save Format icons
    EMU,
    PC,
    VDOC,


    //Star frames
    STAR_SHEET,
    UNSTAR_SHEET,

    //Special assets
    CAKE,
    WOOD_BLUE,
    WOOD_YELLOW,
    WOOD_GREEN,
    WOOD_RED,
    WOOD_MAGENTA,
    PEACH_LETTER

};

extern const vector<string>  paths;

