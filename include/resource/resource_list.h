#ifndef PATHS
#define PATHS

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

#endif


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


RES_INCBIN(p_bob, PAINTING_PATH "/BOB.png");
RES_INCBIN(p_wf,  PAINTING_PATH "/WF.png" );
RES_INCBIN(p_ccm, PAINTING_PATH "/CCM.png");
RES_INCBIN(p_jrb, PAINTING_PATH "/JRB.png");
RES_INCBIN(p_wdw, PAINTING_PATH "/WDW.png");
RES_INCBIN(p_thi, PAINTING_PATH "/THI.png");
RES_INCBIN(p_ttc, PAINTING_PATH "/TTC.png");
RES_INCBIN(p_rr , PAINTING_PATH "/RR.png" );
RES_INCBIN(p_ttm, PAINTING_PATH "/TTM.png");
RES_INCBIN(p_lll, PAINTING_PATH "/LLL.png");
RES_INCBIN(p_ssl, PAINTING_PATH "/SSL.png");
RES_INCBIN(p_hmc, PAINTING_PATH "/HMC.png");
RES_INCBIN(p_bbh, PAINTING_PATH "/BBH.png");
RES_INCBIN(p_ddd, PAINTING_PATH "/DDD.png");


    //Swtich assests
RES_INCBIN(sw_blue , SWITCH_PATH "/BLUE.png");
RES_INCBIN(sw_blue_, SWITCH_PATH "/BLUE_.png");
RES_INCBIN(sw_green , SWITCH_PATH "/GREEN.png");
RES_INCBIN(sw_green_, SWITCH_PATH "/GREEN_.png");
RES_INCBIN(sw_red , SWITCH_PATH "/RED.png");
RES_INCBIN(sw_red_, SWITCH_PATH "/RED_.png");

RES_INCBIN(cap_vanish , CAP_BOXES_PATH "/vanish.png");
RES_INCBIN(cap_metal , CAP_BOXES_PATH "/metal.png");
RES_INCBIN(cap_wing , CAP_BOXES_PATH "/wing.png");
RES_INCBIN(cap_outline , CAP_BOXES_PATH "/outline.png");
RES_INCBIN(cap_mark , CAP_BOXES_PATH "/mark.png");


    //Coin animations
/*
RES_INCBIN(coin_0, COIN_PATH "/C_0.png");
RES_INCBIN(coin_1, COIN_PATH "/C_1.png");
RES_INCBIN(coin_2, COIN_PATH "/C_2.png");
RES_INCBIN(coin_3, COIN_PATH "/C_3.png");
RES_INCBIN(coin_4, COIN_PATH "/C_4.png");
RES_INCBIN(coin_5, COIN_PATH "/C_5.png");
RES_INCBIN(coin_6, COIN_PATH "/C_6.png");
RES_INCBIN(coin_7, COIN_PATH "/C_7.png");
*/
RES_INCBIN(coin_img, COIN_PATH "/full_.png");

    //Menu Buttons

RES_INCBIN(but_a0, BUTTON_PATH "/A_0.png");
RES_INCBIN(but_a1, BUTTON_PATH "/A_1.png");
RES_INCBIN(but_TRUE, BUTTON_PATH "/TRUE.png");
RES_INCBIN(but_FALSE, BUTTON_PATH "/FALSE.png");
RES_INCBIN(but_MOD, BUTTON_PATH "/MOD.png");
RES_INCBIN(but_TOGGLE, BUTTON_PATH "/TOGGLE.png");
RES_INCBIN(but_TOP, BUTTON_PATH "/TOP.png");

//Cursor
RES_INCBIN(cur_open, CURSOR_PATH "/open.png");
RES_INCBIN(cur_closed, CURSOR_PATH "/closed.png");

//Sparkle Animations
RES_INCBIN(s_1, CURSOR_PATH "/s1.png");   
RES_INCBIN(s_2, CURSOR_PATH "/s2.png");   
RES_INCBIN(s_3, CURSOR_PATH "/s3.png");   
RES_INCBIN(s_4, CURSOR_PATH "/s4.png");   
RES_INCBIN(s_5, CURSOR_PATH "/s5.png");    
RES_INCBIN(s_6, CURSOR_PATH "/s6.png");

//Icons
RES_INCBIN(icon_bomb, ICONS_PATH "/Bomb.png");
RES_INCBIN(icon_bomb_cov, ICONS_PATH "/Bomb_cov.png");
RES_INCBIN(icon_bow, ICONS_PATH "/Bowser.png");
RES_INCBIN(icon_door, ICONS_PATH "/Door.png");
RES_INCBIN(icon_star_l, ICONS_PATH "/star_left.png");
RES_INCBIN(icon_star_r, ICONS_PATH "/star_right.png");
RES_INCBIN(icon_peach, ICONS_PATH "/peach.png");
RES_INCBIN(icon_sign, ICONS_PATH "/sign.png");
RES_INCBIN(icon_mips, ICONS_PATH "/TOAD_MIPS.png");
RES_INCBIN(icon_valid, ICONS_PATH "/valid.png");
RES_INCBIN(icon_valid_not, ICONS_PATH "/valid_not.png");

//Save Format icons
RES_INCBIN(fmt_emu, FORMATS_ICONS_PATH "/emu.png");
RES_INCBIN(fmt_pc, FORMATS_ICONS_PATH "/PC.png");
RES_INCBIN(fmt_vdoc, FORMATS_ICONS_PATH "/vdoc.png");


//Star frames
RES_INCBIN(star_star, PNG_PATH "/starSheet.png");
RES_INCBIN(star_unstar, PNG_PATH "/unstarSheet.png");

//Special assets
RES_INCBIN(spc_cake, SPECIAL_PATH "/cake.png");
RES_INCBIN(spc_wood_blue, SPECIAL_PATH "/wood_blue.png");
RES_INCBIN(spc_wood_yellow, SPECIAL_PATH "/wood_yellow.png");
RES_INCBIN(spc_wood_green, SPECIAL_PATH "/wood_green.png");
RES_INCBIN(spc_wood_red, SPECIAL_PATH "/wood_red.png");
RES_INCBIN(spc_wood_magenta, SPECIAL_PATH "/wood_magenta.png");
RES_INCBIN(spc_peach, SPECIAL_PATH "/PeachLetter.png");