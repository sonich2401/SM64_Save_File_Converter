#include "resources.h"
#include "animation/dummy_texture.h"


#define PNG_PATH "./include/resource/png"



#if USE_STATIC_FILES
    #include <incbin.h>
    #define RES_INCBIN(name, path) INCBIN(name, path); extern "C" { const static_file s_ ## name = {g ## name ## Data, g ## name ## Size}; };
#else
    #define INCBIN(name, path) static_file s_ ## name = path;
    #define RES_INCBIN(name, path) INCBIN(name, path);
#endif

#if USE_STATIC_FILES
#else
#undef INCBIN
#undef RES_INCBIN
#define INCBIN(name, path) static_file s_ ## name = path;
#define RES_INCBIN(name, path) INCBIN(name, path);
#endif

#undef RES_INCBIN
#define RES_INCBIN(name, path) INCBIN(name, path);
#include "resource_list.h"

#undef RES_INCBIN
#define RES_INCBIN(name, path) extern "C" { const static_file s_ ## name = {g ## name ## Data, g ## name ## Size}; };
#include "resource_list.h"



    const anipk anipk_bob{
        BOB,
        &s_p_bob,
        TEX_TYPE::STATIC
    };

    const anipk anipk_wf{
        WF ,
        &s_p_wf,
        TEX_TYPE::STATIC
    };

    const anipk anipk_ccm{
        CCM,
        &s_p_ccm,
        TEX_TYPE::STATIC
    };

    const anipk anipk_jrb{
        JRB,
        &s_p_jrb,
        TEX_TYPE::STATIC
    };

    const anipk anipk_wdw{
        WDW,
        &s_p_wdw,
        TEX_TYPE::STATIC
    };

    const anipk anipk_thi{
        THI,
        &s_p_thi,
        TEX_TYPE::STATIC
    };

    const anipk anipk_ttc{
        TTC,
        &s_p_ttc,
        TEX_TYPE::STATIC
    };

    const anipk anipk_rr{
        RR ,
        &s_p_rr,
        TEX_TYPE::STATIC
    };

    const anipk anipk_ttm{
        TTM,
        &s_p_ttm,
        TEX_TYPE::STATIC
    };

    const anipk anipk_lll{
        LLL,
        &s_p_lll,
        TEX_TYPE::STATIC
    };

    const anipk anipk_ssl{
        SSL,
        &s_p_ssl,
        TEX_TYPE::STATIC
    };

    const anipk anipk_hmc{
        HMC,
        &s_p_hmc,
        TEX_TYPE::STATIC
    };

    const anipk anipk_bbh{
        BBH,
        &s_p_bbh,
        TEX_TYPE::STATIC
    };

    const anipk anipk_ddd{
        DDD,
        &s_p_ddd,
        TEX_TYPE::STATIC
    };

    //Swtich assests
    const anipk anipk_sw_blue{
        BLUE,   
        &s_sw_blue,
        TEX_TYPE::STATIC
    };

    const anipk anipk_sw_blue_{
        BLUE_,  
        &s_sw_blue_,
        TEX_TYPE::STATIC
    };

    const anipk anipk_sw_green{
        GREEN,  
        &s_sw_green,
        TEX_TYPE::STATIC
    };

    const anipk anipk_sw_green_{
        GREEN_, 
        &s_sw_green_,
        TEX_TYPE::STATIC
    };

    const anipk anipk_sw_red{
        RED,    
        &s_sw_red,
        TEX_TYPE::STATIC
    };

    const anipk anipk_sw_red_{
        RED_,   
        &s_sw_red_,
        TEX_TYPE::STATIC
    };




    const anipk anipk_cap_vanish {
        BOX_VANISH,
        &s_cap_vanish, 
        TEX_TYPE::STATIC
    };

    const anipk anipk_cap_metal {
        BOX_METAL, 
        &s_cap_metal, 
        TEX_TYPE::STATIC
    };

    const anipk anipk_cap_wing {
        BOX_WING,  
        &s_cap_wing, 
        TEX_TYPE::STATIC
    };

    const anipk anipk_cap_outline {
        BOX_NONE,  
        &s_cap_outline, 
        TEX_TYPE::STATIC
    };

    const anipk anipk_cap_mark {
        BOX_MARK,  
        &s_cap_mark, 
        TEX_TYPE::STATIC
    };




    //Coin animations
    const anipk anipk_coin_img {
        C_IMG,  
        &s_coin_img, 
        TEX_TYPE::STATIC
    };

    const anipk_SprSheet anipk_coin = {
        C_FULL,
        C_IMG,
        TEX_TYPE::SPRITE_SHEET,
        olc::vi2d{100, 66},
        {
        //Walking
            { //ROOT
                0.07f,
                {0, 1, 2, 3, 4, 5, 6, 7}
            },
        }
    };

    //Menu Buttons

    const anipk anipk_A_0{
        A_0,   
        &s_but_a0,
        TEX_TYPE::STATIC
    };

    const anipk anipk_A_1{
        A_1,   
        &s_but_a1,
        TEX_TYPE::STATIC
    };

    const anipk anipk_TRUE{
        _TRUE, 
        &s_but_TRUE,
        TEX_TYPE::STATIC
    };

    const anipk anipk_FALSE{
        _FALSE,
        &s_but_FALSE,
        TEX_TYPE::STATIC
    };

    const anipk anipk_MOD{
        MOD,   
        &s_but_MOD,
        TEX_TYPE::STATIC
    };

    const anipk anipk_TOGGLE{
        TOGGLE,
        &s_but_TOGGLE,
        TEX_TYPE::STATIC
    };

    const anipk anipk_TOP{
        TOP,   
        &s_but_TOP,
        TEX_TYPE::STATIC
    };


    //Cursor
    const anipk anipk_cur_open {
        CUR_OPEN,  
        &s_cur_open,
        TEX_TYPE::STATIC
    };

    const anipk anipk_cur_closed {
        CUR_CLOSED,
        &s_cur_closed,
        TEX_TYPE::STATIC
    };



    //Sparkle Animations
    const anipk anipk_spark_0 {
        SPARK_0,
        &s_s_1,
        TEX_TYPE::STATIC
    };   

    const anipk anipk_spark_1 {
        SPARK_1,
        &s_s_2,
        TEX_TYPE::STATIC
    };

    const anipk anipk_spark_2 {
        SPARK_2,
        &s_s_3,
        TEX_TYPE::STATIC
    };

    const anipk anipk_spark_3 {
        SPARK_3,
        &s_s_4,
        TEX_TYPE::STATIC
    };

    const anipk anipk_spark_4 {
        SPARK_4,
        &s_s_5,
        TEX_TYPE::STATIC
    };   

    const anipk anipk_spark_5 {
        SPARK_5,
        &s_s_6,
        TEX_TYPE::STATIC
    };


    //Icons
    const anipk anipk_icon_bomb {
        BOMB,          
        &s_icon_bomb,
        TEX_TYPE::STATIC
    };

    const anipk anipk_icon_bomb_cov {
        BOMB_,         
        &s_icon_bomb_cov,
        TEX_TYPE::STATIC
    };

    const anipk anipk_icon_bow {
        BOWSER,        
        &s_icon_bow,
        TEX_TYPE::STATIC
    };

    const anipk anipk_icon_door {
        DOOR,          
        &s_icon_door,
        TEX_TYPE::STATIC
    };

    const anipk anipk_icon_star_l {
        STAR_DOOR_L,   
        &s_icon_star_l,
        TEX_TYPE::STATIC
    };

    const anipk anipk_icon_star_r {
        STAR_DOOR_R,   
        &s_icon_star_r,
        TEX_TYPE::STATIC
    };

    const anipk anipk_icon_peach {
        PEACH,         
        &s_icon_peach,
        TEX_TYPE::STATIC
    };

    const anipk anipk_icon_sign {
        SIGN,          
        &s_icon_sign,
        TEX_TYPE::STATIC
    };

    const anipk anipk_icon_mips {
        TOAD_MIPS,     
        &s_icon_mips,
        TEX_TYPE::STATIC
    };

    const anipk anipk_icon_valid {
        SAVE_VALID,    
        &s_icon_valid,
        TEX_TYPE::STATIC
    };

    const anipk anipk_icon_valid_not {
        SAVE_NOT_VALID,
        &s_icon_valid_not,
        TEX_TYPE::STATIC
    };


    //Save Format icons
    const anipk anipk_fmt_emu {
        EMU, 
        &s_fmt_emu, 
        TEX_TYPE::STATIC
    };

    const anipk anipk_fmt_pc {
        PC,  
        &s_fmt_pc, 
        TEX_TYPE::STATIC
    };

    const anipk anipk_fmt_vdoc {
        VDOC,
        &s_fmt_vdoc, 
        TEX_TYPE::STATIC
    };



    //Star frames
    const anipk anipk_star_img {
        STAR_IMG,  
        &s_star_star,
        TEX_TYPE::STATIC
    };

    const anipk anipk_unstar_img {
        UNSTAR_SHEET,
        &s_star_unstar,
        TEX_TYPE::STATIC
    };





    static const std::vector<animation_SprSheet> STAR_ANIMATION = {
        {
            0.05f,
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}
        }
    };



    const anipk_SprSheet anipk_star = {
        STAR_SHEET,
        STAR_IMG,
        TEX_TYPE::SPRITE_SHEET,
        olc::vi2d{298, 273},
        STAR_ANIMATION
    };

    const anipk_SprSheet anipk_unstar = {
        UNSTAR_SHEET,
        UNSTAR_IMG,
        TEX_TYPE::SPRITE_SHEET,
        olc::vi2d{298, 273},
        STAR_ANIMATION
    };




    //Special assets
    const anipk anipk_spc_cake {
        CAKE,        
        &s_spc_cake,
        TEX_TYPE::STATIC
    };

    const anipk anipk_spc_wood_blue {
        WOOD_BLUE,   
        &s_spc_wood_blue,
        TEX_TYPE::STATIC
    };

    const anipk anipk_spc_wood_yellow {
        WOOD_YELLOW, 
        &s_spc_wood_yellow,
        TEX_TYPE::STATIC
    };

    const anipk anipk_spc_wood_green {
        WOOD_GREEN,  
        &s_spc_wood_green,
        TEX_TYPE::STATIC
    };

    const anipk anipk_spc_wood_red {
        WOOD_RED,    
        &s_spc_wood_red,
        TEX_TYPE::STATIC
    };

    const anipk anipk_spc_wood_magenta {
        WOOD_MAGENTA,
        &s_spc_wood_magenta,
        TEX_TYPE::STATIC
    };

    const anipk anipk_spc_peach {
        PEACH_LETTER,
        &s_spc_peach,
        TEX_TYPE::STATIC
    };




const anipk* RESOURCES[RESOURCES_SIZE] = {
    nullptr,

    &anipk_bob,
    &anipk_wf,
    &anipk_ccm,
    &anipk_jrb,
    &anipk_wdw,
    &anipk_thi,
    &anipk_ttc,
    &anipk_rr,
    &anipk_ttm,
    &anipk_lll,
    &anipk_ssl,
    &anipk_hmc,
    &anipk_bbh,
    &anipk_ddd,

    //Swtich assests
    &anipk_sw_blue,
    &anipk_sw_blue_,
    &anipk_sw_green,
    &anipk_sw_green_,
    &anipk_sw_red,
    &anipk_sw_red_,
    &anipk_cap_vanish,
    &anipk_cap_metal,
    &anipk_cap_wing,
    &anipk_cap_outline,
    &anipk_cap_mark,




    //Coin animations
    &anipk_coin_img,
    &anipk_coin,

    //Menu Buttons

    &anipk_A_0,
    &anipk_A_1,
    &anipk_TRUE,
    &anipk_FALSE,
    &anipk_MOD,
    &anipk_TOGGLE,
    &anipk_TOP,


    //Cursor
    &anipk_cur_open,
    &anipk_cur_closed,


    //Sparkle Animations
    &anipk_spark_0,
    &anipk_spark_1,
    &anipk_spark_2,
    &anipk_spark_3,
    &anipk_spark_4,
    &anipk_spark_5,


    //Icons
    &anipk_icon_bomb,
    &anipk_icon_bomb_cov,
    &anipk_icon_bow,
    &anipk_icon_door,
    &anipk_icon_star_l,
    &anipk_icon_star_r,
    &anipk_icon_peach,
    &anipk_icon_sign,
    &anipk_icon_mips,
    &anipk_icon_valid,
    &anipk_icon_valid_not,


    //Save Format icons
    &anipk_fmt_emu,
    &anipk_fmt_pc,
    &anipk_fmt_vdoc,



    //Star frames
    &anipk_star_img,
    &anipk_star,
    &anipk_unstar_img,
    &anipk_unstar,

    //Special assets
    &anipk_spc_cake,
    &anipk_spc_wood_blue,
    &anipk_spc_wood_yellow,
    &anipk_spc_wood_green,
    &anipk_spc_wood_red,
    &anipk_spc_wood_magenta,
    &anipk_spc_peach,

    nullptr
};