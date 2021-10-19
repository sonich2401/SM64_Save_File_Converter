#include "imagelist.h"





#define MENU_PATH PNG_PATH "/Menu"

#define PAINTING_PATH PNG_PATH "/Paintings"

//Cap paths
#define CAP_PATH MENU_PATH "/Caps"
#define SWITCH_PATH CAP_PATH "/SWITCH"
#define CAP_BOXES_PATH CAP_PATH "/BOX"

//Menu icons
#define BUTTON_PATH MENU_PATH "/Buttons"
#define CURSOR_PATH MENU_PATH "/Cursor"
#define SPECIAL_PATH MENU_PATH "/Special"
#define ICONS_PATH MENU_PATH "/Icons"
#define FORMATS_ICONS_PATH ICONS_PATH "/SaveFormats"
#define COIN_PATH PNG_PATH "/Coin"


/*    BOB,
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

    //Menu Buttons

    A_0,
    A_1,
    TRUE,
    FALSE,
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
*/


const vector<string> paths ={
    PAINTING_PATH "/BOB.png",
    PAINTING_PATH "/WF.png",
    PAINTING_PATH "/CCM.png",
    PAINTING_PATH "/JRB.png",
    PAINTING_PATH "/WDW.png",
    PAINTING_PATH "/THI.png",
    //PAINTING_PATH "/SML.png",
    PAINTING_PATH "/TTC.png",
    PAINTING_PATH "/RR.png",
    PAINTING_PATH "/TTM.png",
    PAINTING_PATH "/LLL.png",
    PAINTING_PATH "/SSL.png",
    PAINTING_PATH "/HMC.png",
    PAINTING_PATH "/BBH.png",
    PAINTING_PATH "/DDD.png",


    //Swtich assests
    SWITCH_PATH "/BLUE.png",
    SWITCH_PATH "/BLUE_.png",
    SWITCH_PATH "/GREEN.png",
    SWITCH_PATH "/GREEN_.png",
    SWITCH_PATH "/RED.png",
    SWITCH_PATH "/RED_.png",

    CAP_BOXES_PATH "/vanish.png",
    CAP_BOXES_PATH "/metal.png",
    CAP_BOXES_PATH "/wing.png",
    CAP_BOXES_PATH "/outline.png",
    CAP_BOXES_PATH "/mark.png",


    //Coin animations

    COIN_PATH "/C_0.png",
    COIN_PATH "/C_1.png",
    COIN_PATH "/C_2.png",
    COIN_PATH "/C_3.png",
    COIN_PATH "/C_4.png",
    COIN_PATH "/C_5.png",
    COIN_PATH "/C_6.png",
    COIN_PATH "/C_7.png",
    COIN_PATH "/full_.png",

    //Menu Buttons

    BUTTON_PATH "/A_0.png",
    BUTTON_PATH "/A_1.png",
    BUTTON_PATH "/TRUE.png",
    BUTTON_PATH "/FALSE.png",
    BUTTON_PATH "/MOD.png",
    BUTTON_PATH "/TOGGLE.png",
    BUTTON_PATH "/TOP.png",

    //Cursor
    CURSOR_PATH "/open.png",
    CURSOR_PATH "/closed.png",

    //Sparkle Animations
    CURSOR_PATH "/s1.png",   
    CURSOR_PATH "/s2.png",   
    CURSOR_PATH "/s3.png",   
    CURSOR_PATH "/s4.png",   
    CURSOR_PATH "/s5.png",    
    CURSOR_PATH "/s6.png",

    //Icons
    ICONS_PATH "/Bomb.png",
    ICONS_PATH "/Bomb_cov.png",
    ICONS_PATH "/Bowser.png",
    ICONS_PATH "/Door.png",
    ICONS_PATH "/star_left.png",
    ICONS_PATH "/star_right.png",
    ICONS_PATH "/peach.png",
    ICONS_PATH "/sign.png",
    ICONS_PATH "/TOAD_MIPS.png",
    ICONS_PATH "/valid.png",
    ICONS_PATH "/valid_not.png",

    //Save Format icons
    FORMATS_ICONS_PATH "/emu.png",
    FORMATS_ICONS_PATH "/PC.png",
    FORMATS_ICONS_PATH "/vdoc.png",


    //Star frames
    PNG_PATH "/starSheet.png",
    PNG_PATH "/unstarSheet.png",

    //Special assets
    SPECIAL_PATH "/cake.png",
    SPECIAL_PATH "/wood_blue.png",
    SPECIAL_PATH "/wood_yellow.png",
    SPECIAL_PATH "/wood_green.png",
    SPECIAL_PATH "/wood_red.png",
    SPECIAL_PATH "/wood_magenta.png",
    SPECIAL_PATH "/PeachLetter.png",
};