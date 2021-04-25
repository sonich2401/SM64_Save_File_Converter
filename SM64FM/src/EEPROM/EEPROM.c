#include "EEPROM.h"
#include "EEPROM_Defines.h"

uint8 detect_endian(EEPROM * eep){
   return (((char *)&eep->game_saves[0][0].magic)[0] == 'D');
}

EEPROM init_EEPROM(unsigned char * buffer){
    EEPROM ret;

    if(buffer == NULL){
        memcpy(&ret, Empty, Empty_size);
        return ret;
    }

    memcpy(&ret, buffer, 512);

    return ret;
}

//EEPROM.h
EEPROM * eeprom = NULL;
uint8 * current_save = NULL;

//EEPROM_Defines.h
const course_str_struct str_courses[15] = 
{
    {
        "Bomb-omb Battlefield",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate",
            "100 Coin Star"
        }
    },

    {
        "Whomp's Fortress",
        {
            "Chip off Whomp's Block",
	        "To The Top of The Fortress",
	        "Shoot Into The Wild Blue",
       	    "Red Coins on The Floating Isle",
	        "Fall Onto The Caged Island",
	        "Blast Away The Wall",
            "100 Coin Star"
        }
    },

    {
        "Jolly Rodger Bay",
        {
            "Plunder In The Sunken Ship",
            "Can The EEL Come Out To Play?",
            "Treasure Of The Ocean Cave",
            "Red Coins On The Ship AFloat",
            "Blast To The Stone Pillar",
            "Through The Jet Stream",
            "100 Coin Star"
        }
    },

    {
        "COOL, COOL MOUNTAIN",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },

    {
        "BIG BOO'S HAUNT",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },

    {
        "HAZY MAZE CAVE",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },

    {
        "LETHAL LAVA LAND",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },

    {
        "SHIFTING SAND LAND",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },

    {
        "DIRE, DIRE DOCKS",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },

    {
        "SNOWMAN'S LAND",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },

    {
        "WET-DRY WORLD",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },

    {
        "TALL, TALL MOUNTAIN",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },

    {
        "TINY-HUGE ISLAND",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },

    {
        "TICK TOCK CLOCK",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },

    {
        "RAINBOW RIDE",
        {
            "Big Bob-omb on the Summit",
            "Footrace with Koopa the Quick",
            "Shoot to the Island in the Sky",
            "Find the 8 Red Coins",
            "Mario Wings to the Sky",
            "Behind Chain Chomp's Gate"
        }
    },
};

/*
COURSE_ACTS(COURSE_BOB, _(" 1 BOB-OMB BATTLEFIELD"),
       _("BIG BOB-OMB ON THE SUMMIT")     , _("FOOTRACE WITH KOOPA THE QUICK") , _("SHOOT TO THE ISLAND IN THE SKY"),
       _("FIND THE 8 RED COINS")          , _("MARIO WINGS TO THE SKY")        , _("BEHIND CHAIN CHOMP'S GATE"))

COURSE_ACTS(COURSE_WF, _(" 2 WHOMP'S FORTRESS"),
       _("CHIP OFF WHOMP'S BLOCK")        , _("TO THE TOP OF THE FORTRESS")    , _("SHOOT INTO THE WILD BLUE"),
       _("RED COINS ON THE FLOATING ISLE"), _("FALL ONTO THE CAGED ISLAND")    , _("BLAST AWAY THE WALL"))

COURSE_ACTS(COURSE_JRB, _(" 3 JOLLY ROGER BAY"),
       _("PLUNDER IN THE SUNKEN SHIP")    , _("CAN THE EEL COME OUT TO PLAY?") , _("TREASURE OF THE OCEAN CAVE"),
       _("RED COINS ON THE SHIP AFLOAT")  , _("BLAST TO THE STONE PILLAR")     , _("THROUGH THE JET STREAM"))

COURSE_ACTS(COURSE_CCM, _(" 4 COOL, COOL MOUNTAIN"),
       _("SLIP SLIDIN' AWAY")             , _("LI'L PENGUIN LOST")             , _("BIG PENGUIN RACE"),
       _("FROSTY SLIDE FOR 8 RED COINS")  , _("SNOWMAN'S LOST HIS HEAD")       , _("WALL KICKS WILL WORK"))

COURSE_ACTS(COURSE_BBH, _(" 5 BIG BOO'S HAUNT"),
       _("GO ON A GHOST HUNT")            , _("RIDE BIG BOO'S MERRY-GO-ROUND") , _("SECRET OF THE HAUNTED BOOKS"),
       _("SEEK THE 8 RED COINS")          , _("BIG BOO'S BALCONY")             , _("EYE TO EYE IN THE SECRET ROOM"))

COURSE_ACTS(COURSE_HMC, _(" 6 HAZY MAZE CAVE"),
       _("SWIMMING BEAST IN THE CAVERN")  , _("ELEVATE FOR 8 RED COINS")       , _("METAL-HEAD MARIO CAN MOVE!"),
       _("NAVIGATING THE TOXIC MAZE")     , _("A-MAZE-ING EMERGENCY EXIT")     , _("WATCH FOR ROLLING ROCKS"))

COURSE_ACTS(COURSE_LLL, _(" 7 LETHAL LAVA LAND"),
       _("BOIL THE BIG BULLY")            , _("BULLY THE BULLIES")             , _("8-COIN PUZZLE WITH 15 PIECES"),
       _("RED-HOT LOG ROLLING")           , _("HOT-FOOT-IT INTO THE VOLCANO")  , _("ELEVATOR TOUR IN THE VOLCANO"))

COURSE_ACTS(COURSE_SSL, _(" 8 SHIFTING SAND LAND"),
       _("IN THE TALONS OF THE BIG BIRD") , _("SHINING ATOP THE PYRAMID")      , _("INSIDE THE ANCIENT PYRAMID"),
       _("STAND TALL ON THE FOUR PILLARS"), _("FREE FLYING FOR 8 RED COINS")   , _("PYRAMID PUZZLE"))

COURSE_ACTS(COURSE_DDD, _(" 9 DIRE, DIRE DOCKS"),
       _("BOARD BOWSER'S SUB")            , _("CHESTS IN THE CURRENT")         , _("POLE-JUMPING FOR RED COINS"),
       _("THROUGH THE JET STREAM")        , _("THE MANTA RAY'S REWARD")        , _("COLLECT THE CAPS..."))

COURSE_ACTS(COURSE_SL, _("10 SNOWMAN'S LAND"),
       _("SNOWMAN'S BIG HEAD")            , _("CHILL WITH THE BULLY")          , _("IN THE DEEP FREEZE"),
       _("WHIRL FROM THE FREEZING POND")  , _("SHELL SHREDDIN' FOR RED COINS") , _("INTO THE IGLOO"))

COURSE_ACTS(COURSE_WDW, _("11 WET-DRY WORLD"),
       _("SHOCKING ARROW LIFTS!")         , _("TOP O' THE TOWN")               , _("SECRETS IN THE SHALLOWS & SKY"),
       _("EXPRESS ELEVATOR--HURRY UP!")   , _("GO TO TOWN FOR RED COINS")      , _("QUICK RACE THROUGH DOWNTOWN!"))

COURSE_ACTS(COURSE_TTM, _("12 TALL, TALL MOUNTAIN"),
       _("SCALE THE MOUNTAIN")            , _("MYSTERY OF THE MONKEY CAGE")    , _("SCARY 'SHROOMS, RED COINS"),
       _("MYSTERIOUS MOUNTAINSIDE")       , _("BREATHTAKING VIEW FROM BRIDGE") , _("BLAST TO THE LONELY MUSHROOM"))

COURSE_ACTS(COURSE_THI, _("13 TINY-HUGE ISLAND"),
       _("PLUCK THE PIRANHA FLOWER")      , _("THE TIP TOP OF THE HUGE ISLAND"), _("REMATCH WITH KOOPA THE QUICK"),
       _("FIVE ITTY BITTY SECRETS")       , _("WIGGLER'S RED COINS")           , _("MAKE WIGGLER SQUIRM"))

COURSE_ACTS(COURSE_TTC, _("14 TICK TOCK CLOCK"),
       _("ROLL INTO THE CAGE")            , _("THE PIT AND THE PENDULUMS")     , _("GET A HAND"),
       _("STOMP ON THE THWOMP")           , _("TIMED JUMPS ON MOVING BARS")    , _("STOP TIME FOR RED COINS"))

COURSE_ACTS(COURSE_RR, _("15 RAINBOW RIDE"),
       _("CRUISER CROSSING THE RAINBOW")  , _("THE BIG HOUSE IN THE SKY")      , _("COINS AMASSED IN A MAZE"),
       _("SWINGIN' IN THE BREEZE")        , _("TRICKY TRIANGLES!")             , _("SOMEWHERE OVER THE RAINBOW"))

SECRET_STAR(COURSE_BITDW, _("   BOWSER IN THE DARK WORLD"))
SECRET_STAR(COURSE_BITFS, _("   BOWSER IN THE FIRE SEA"))
SECRET_STAR(COURSE_BITS, _("   BOWSER IN THE SKY"))
SECRET_STAR(COURSE_PSS, _("   THE PRINCESS'S SECRET SLIDE"))
SECRET_STAR(COURSE_COTMC, _("   CAVERN OF THE METAL CAP"))
SECRET_STAR(COURSE_TOTWC, _("   TOWER OF THE WING CAP"))
SECRET_STAR(COURSE_VCUTM, _("   VANISH CAP UNDER THE MOAT"))
SECRET_STAR(COURSE_WMOTR, _("   WING MARIO OVER THE RAINBOW"))
SECRET_STAR(COURSE_SA, _("   THE SECRET AQUARIUM"))
SECRET_STAR(COURSE_CAKE_END, _(""))
*/



const flag_str_struct str_flags[STR_FLAGS_SIZE] ={
    {
        "Toad 1",
        0x8,
        0
    },
    {
        "Toad 2",
        0x8,
        2
    },
    {
        "Toad 3",
        0x8,
        3
    },
    {
        "MIPS 1",
        0x8,
        1
    },
    {
        "MIPS 2",
        0x8,
        4
    },
    {
        "Snow",
        0x9,
        0
    },
    {
        "Monkey",
        0x9,
        2
    },
    {
        "Bird",
        0x9,
        1
    },
    {
        "Star 1",
        0xA,
        6
    },
    {
        "Star 2",
        0xA,
        7
    },

    {
        "Star 3",
        0x8,
        4
    },
    {
        "Upstairs",
        0xB,
        7
    },
    {
        "Basement",
        0xB,
        6
    },
    {
        "CCM",
        0xA,
        4
    },
    {
        "WF",
        0xA,
        3
    },
    {
        "CCM",
        0xA,
        4
    },
    {
        "PSS",
        0xA,
        2
    },
    {
        "JRB",
        0xA,
        5
    },
    {
        "Key 1",
        0xB,
        4
    },
    {
        "Key 2",
        0xB,
        5
    },

    {
        "DDD",
        0xA,
        0
    },
    {
        "Moat",
        0xA,
        1
    },
    {
        "Valid",
        0xB,
        0
    },
    {
        "Wing",
        0xB,
        1
    },
    {
        "Metal",
        0xB,
        2
    },
    {
        "Invis",
        0xB,
        3
    },
};



const flag_str_struct str_secret[STR_SECRET_SIZE] = {
  {
    "PSS [!]",
    3,
    0
  },
  {
    "PSS 20",
    3,
    1
  },
  {
    "Aqua",
    8,
    0
  },
  {
    "Bow 1",
    0,
    0
  },
  {
    "Bow 2",
    1,
    0
  },
  {
    "Bow 3",
    2,
    0
  },
  {
    "Wing",
    5,
    0
  },
  {
    "Metal",
    4,
    0
  },
  {
    "Invis",
    6,
    0
  },
  {
    "Rain",
    7,
    0
  }
};