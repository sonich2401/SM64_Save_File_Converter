#pragma once
#include <olcPixelGameEngine.h>
#include <_typedefs.h>
#include <animation/aniren.h>
#include <animation/ren.h>
#include <animation/SprSheet.h>
#include "screendef.h"
#include "screensize.h"
#include "EEPROM/EEPROM.h"

class screen;

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
    screen * cur_screen = nullptr;
    pge::ren * cursor[2];

private:
    bool change_state = false;
    int8 next_state = -1;

public:
	Example();
    void ChangeGamestate(uint8 state);

    uint8 current_slot;

public:
	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;
};