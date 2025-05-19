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
#include "EEPROM.h"
#include "../../include/filesys/load_bin.h"


EEP_DAT::EEP_DAT(){
    for(uint8 i = 0; i < 4; i++) //Init the buffer to all 'false'
        std::fill(this->save_file_buffers[i].secret_star_states.begin(), this->save_file_buffers[i].secret_star_states.end(), 0);
}



Save * EEP_DAT::getCurSave(int save_slot, bool backup){
    return &this->edited->named.Slots.slots2D[save_slot][backup];
}

void EEP_DAT::init(){
    dat = new EEPROM;
    edited = new EEPROM;
    #if 0
    for(uint16 i = 0; i < 512; i++){
        this->dat->array[i] = Empty[i];
    }

    EEPROM* tmp;
    tmp = SAVE_FORMATS::convert(dat, SAVE_FORMATS::N64);
    delete dat;
    dat = tmp;

    edited = (EEPROM*)memcpy(edited, dat, 512);
    #else
        for(uint16 i = 0; i < 512; i++){
            this->dat->array[i] = Empty[i];
            this->edited->array[i] = Empty[i];
        }
    #endif


    for(uint8 i = 0; i < 4; i++){
        this->save_file_buffers[i].secret_star_states.reserve(15);
    }
    
    #if IS_LITTLE_ENDIAN
        if(format == SAVE_FORMATS::N64 || format == SAVE_FORMATS::EMU){
            EEPROM* tmp = SAVE_FORMATS::convert(edited, SAVE_FORMATS::PC);
            delete edited;
            edited = tmp;
        }
    #else
        if(format == SAVE_FORMATS::PC){
            EEPROM* tmp = SAVE_FORMATS::convert(edited, SAVE_FORMATS::N64);
            delete edited;
            edited = tmp;
        }
    #endif

    format = SAVE_FORMATS::detect(this->edited->named.Slots.slots2D[0][0].GoodName.magic.fullBytes, this->edited->named.Slots.slots2D[0][0].GoodName.checksum);
}

void EEP_DAT::load(){

    std::string path = openFile("Please Select a SM64 Rom ...");

    if(path != "" && path != "...END" && path != "NULL"){
        char * save_data = load_bin(path.c_str());
        this->dat = (EEPROM*)memcpy(this->dat, save_data, 512);
        this->edited = (EEPROM*)memcpy(this->edited, save_data, 512);
        free(save_data);
    }
    format = SAVE_FORMATS::detect(this->edited->named.Slots.slots2D[0][0].GoodName.magic.fullBytes, this->edited->named.Slots.slots2D[0][0].GoodName.checksum);
    
    #if IS_LITTLE_ENDIAN
        if(format == SAVE_FORMATS::N64 || format == SAVE_FORMATS::EMU){
            EEPROM* tmp = SAVE_FORMATS::convert(edited, SAVE_FORMATS::PC);
            free(edited);
            edited = tmp;

        }
    #else
        if(format == SAVE_FORMATS::PC){
            EEPROM* tmp = SAVE_FORMATS::convert(edited, SAVE_FORMATS::N64);
            free(edited);
            edited = tmp;
        }
    #endif
}

void EEP_DAT::save(SAVE_FORMATS::FORMAT disired_format, EEPROM* ptr){
    if(ptr == nullptr)
        ptr = this->edited;
    string path = saveFile("Please Select a SM64 Rom Save Location ...");

    for(uint8_t i = 0; i < 4; i++){
        for(uint8_t i1 = 0; i1 < 2; i1++){
            ptr->named.Slots.slots2D[i][i1].GoodName.checksum = calc_checksum((char*)ptr->named.Slots.slots2D[i][i1].array);
        }
    }

    EEPROM* tmp = SAVE_FORMATS::convert(ptr, disired_format);

    if(path != "" && path != "...END" && path != "NULL"){
        write_bin((cstring)path.c_str(), tmp->array, 512);
    }
    free(tmp);
}

void EEP_DAT::updateSecrets(){
    for(uint8 cur_slot = 0; cur_slot < 4; cur_slot++){
        this->save_file_buffers[cur_slot].secret_star_states.clear();
        this->save_file_buffers[cur_slot].secret_star_states.reserve(15);
        //secret_stars.h
        #define SECRET_STARS_ARRAY EEP_DAT::get().edited->named.Slots.slots2D[cur_slot][0].GoodName.castle_secret_stars.array
        for(uint8 i = 0; i < 9;i++){
            this->save_file_buffers[cur_slot].secret_star_states.push_back((SECRET_STARS_ARRAY[i] & 0b1) != 0);
            if(i == 3) //PSS
                this->save_file_buffers[cur_slot].secret_star_states.push_back(((SECRET_STARS_ARRAY[i] >> 1) & 0b1) != 0);   
        }
        #undef SECRET_STARS_ARRAY
        
        //game_flags.h
        uint8 toad_dat = *(uint8*)&EEP_DAT::get().edited->named.Slots.slots2D[cur_slot][0].GoodName.flags.Named.ToadMipsStars;
        
        for(uint8 i = 0; i < 5; i++){
            bool extracted_bit = (toad_dat >> i) & 0b00000001;
            this->save_file_buffers[cur_slot].secret_star_states.push_back(extracted_bit);
        }
    }
}

void EEP_DAT::update(){
    //Check if we need to set this as a valid file
    for(unsigned char i = 0; i < 8; i++){
        switch(format){
            case SAVE_FORMATS::VDOC:
            case SAVE_FORMATS::N64:
            case SAVE_FORMATS::EMU:
                
                edited->named.Slots.slotsArray[i].GoodName.flags.Named.ProgressFlags.ValidGame = calc_checksum((char*)&edited->named.Slots.slotsArray[i]) != PC_CHKSM;
            break;
            case SAVE_FORMATS::PC:
                edited->named.Slots.slotsArray[i].GoodName.flags.Named.ProgressFlags.ValidGame = calc_checksum((char*)&edited->named.Slots.slotsArray[i]) != N64_CHKSM;
            break;
        };
    }

    auto getToadMips = [this](int index){
        int star_count = 0;
        //Toad Mips
       
        uint8 toad_mips_dat = *(uint8*)&this->edited->named.Slots.CombinedSlots[index].primary.GoodName.flags.Named.ToadMipsStars;
        for(uint16 i = 0; i < 8; i++){ //Check all bits
            star_count += (bool)(toad_mips_dat & (1 << i));
        }
        return star_count;
    };

    auto getSecret = [this, getToadMips](int index){
        int star_count = 0;
        
        //Secret stars
        for(uint8 i = 0; i < 10; i++){
            uint8 val = this->edited->named.Slots.CombinedSlots[index].primary.GoodName.castle_secret_stars.array[i];
            star_count += (val != 0);
            star_count += ((val >> 1) != 0); //PSS 20sec checker;
        }
        
        star_count += getToadMips(index);
        return star_count;
    };

    auto getStars = [this, getSecret](int index){
        int star_count = 0;
        for(uint8 i = 0; i < 15; i++){
            uint8 lvl_dat = this->edited->named.Slots.CombinedSlots[index].primary.GoodName.level_data.levels_indexed[i].byte;
            for(uint8 i1 = 0; i1 < 7; i1++){
                star_count += (lvl_dat & (1 << i1)) >> i1;
            }
        }
        star_count += getSecret(index);
        return star_count;
    };


    for(uint8 file_slot = 0; file_slot < 4; file_slot++){
        this->save_file_buffers[file_slot].stars = getStars(file_slot);
        this->save_file_buffers[file_slot].secret_stars = getSecret(file_slot);
        this->save_file_buffers[file_slot].toad_stars = getToadMips(file_slot);
        this->save_file_buffers[file_slot].valid = this->edited->named.Slots.CombinedSlots[file_slot].primary.GoodName.flags.Named.ProgressFlags.ValidGame;
    }
}

uint16_t EEP_DAT::calc_checksum(char * save){
    uint16_t ret = 0;            
    for(uint16_t i = 0; i < 0x38 - 2; i++){
        //printf("CALC: %X\n", *((uint8_t*)(&save[i])));
        ret += *((uint8_t*)(&save[i]));
    }
    //sputs("~~~~~~~~~~~~~~~");
    return ret;
}

bool EEP_DAT::isCorrupted(){
    for(unsigned int i = 0; i < 8; i++){
        uint16_t tmp = uint16_t(edited->named.Slots.slotsArray[i].GoodName.checksum);
        if(tmp != calc_checksum((char*)&edited->named.Slots.slotsArray[i])){
            #ifdef DEBUG
                puts("Not matching Checksum");
                printf("%X, %X\n", tmp, calc_checksum((char*)&edited->named.Slots.slotsArray[i]));
            #endif
            return true;
        }
        if(edited->named.Slots.slots2D[i/2][0].GoodName.magic.fullBytes != edited->named.Slots.slots2D[i/2][1].GoodName.magic.fullBytes){
            #ifdef DEBUG
                puts("Not matching Magic");
            #endif
            return true;
        }

        
        if(!edited->named.Slots.slotsArray[i].GoodName.flags.Named.ProgressFlags.ValidGame){
            bool isStars = false;
            for(uint8_t level = 0; level < 15; level++){
                isStars |= (bool)edited->named.Slots.slotsArray[i].GoodName.level_data.levels_indexed[level].byte;
            }
            if(isStars){
                #ifdef DEBUG
                    puts("Not valid but has stars");
                #endif
                return true;
            }
        }
    }
    return false;
}

void EEP_DAT::fix_corruption(){
    for(int i = 0; i < 8; i++){
        if(!edited->named.Slots.slotsArray[i].GoodName.flags.Named.ProgressFlags.ValidGame){
            bool isStars = false;
            for(uint8_t level = 0; level < 15; level++){
                isStars |= (bool)edited->named.Slots.slotsArray[i].GoodName.level_data.levels_indexed[level].byte;
            }

            edited->named.Slots.slotsArray[i].GoodName.flags.Named.ProgressFlags.ValidGame = isStars;
        }

        //Magic was corrupted. Restore from backup if possible
        if(edited->named.Slots.slotsArray[i].GoodName.magic.fullBytes != N64_MAGIC && edited->named.Slots.slotsArray[i].GoodName.magic.fullBytes != PC_MAGIC){
            if(i % 2 == 0 && i + 1 < 8){
                edited->named.Slots.slotsArray[i].GoodName.magic.fullBytes = edited->named.Slots.slotsArray[i + 1].GoodName.magic.fullBytes;
            }else{
                edited->named.Slots.slotsArray[i].GoodName.magic.fullBytes = N64_MAGIC;
            }
        }
        uint16_t tmp = calc_checksum((char*)&edited->named.Slots.slotsArray[i]);
        
        #if IS_LITTLE_ENDIAN
            //byte_swap<uint16_t>(&tmp);
        #endif
        edited->named.Slots.slotsArray[i].GoodName.checksum = tmp;
    }
}



EEP_DAT::~EEP_DAT(){
    delete dat;
    delete edited;
}