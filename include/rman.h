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
#pragma once
#include <Sprite.h>
#include <_typedefs.h>
#include <string>
#include <assert.h>
#include "../pic/imagelist.h"

enum R_TYPES{
    SPR,
    REN,
    ANI_REN
};

#if 1
#define ADD_REN(id) rman::get().add(id)
#define ADD_STATIC_REN(id) rman::get().add(id, true)

#define ADD_ANIREN(ptr, id) rman::get().add<ANI_REN, pge::aniren>(ptr, id)
#define ADD_STATIC_ANIREN(ptr, id) rman::get().add<ANI_REN, pge::aniren>(ptr, id, true)

#define ADD_SPRSHEET(ptr, id) rman::get().add<SPR, pge::SprSheet>(ptr, id)
#define ADD_STATIC_SPRSHEET(ptr, id) rman::get().add<SPR, pge::SprSheet>(ptr, id, true)
#else


#define ADD_REN(ptr, str) rman::get().add<REN, pge::ren>(ptr, str)
#define ADD_STATIC_REN(ptr, str) rman::get().add<RENpge::ren>(ptr, str, true)

#define ADD_ANIREN(ptr, str) rman::get().add<ANI_REN pge::aniren>(ptr, str)
#define ADD_STATIC_ANIREN(ptr, str) rman::get().add<ANI_REN pge::aniren>(ptr, str, true)

#define ADD_SPRSHEET(ptr, str) rman::get().add<SPR, pge::SprSheet>(ptr, str)
#define ADD_STATIC_SPRSHEET(ptr, str) rman::get().add<SPR pge::SprSheet>(ptr, str, true)
#endif

struct R_PACK{
    R_PACK(){
    }
    R_PACK(R_TYPES t, void* ptr) : R_PACK(){
        first = t;
        second = ptr;
    }
    R_PACK(R_TYPES t, void* ptr, bool s) :  R_PACK(t, ptr){
        third = s;
    }
    R_PACK(R_TYPES t, void* ptr, bool s, unsigned int id) : R_PACK(t, ptr, s){
        forth = id;
    }
    R_TYPES first;
    void* second;
    bool third;
    int forth;
};


class rman{
    public:
        static rman& get(){
            static rman in;
            return in;
        }

        template<R_TYPES RT, typename T>
        T* add(T * ptr, unsigned int id, bool __static__ = false){
            if (__static__) {
                for (auto& res : rsrc)
                    if (res.forth == id) {
                        delete ptr;
                        return (T*)res.second;
                    }
            }

            R_PACK tmp = {RT, (void*)ptr, __static__, id};
            this->rsrc.push_back(tmp);
            return ptr;
        }

        pge::ren* add(unsigned int id, bool __static__ = false) {
            if (__static__)
                for (auto& res : rsrc)
                    if (res.forth == id)
                        return (pge::ren*)res.second;
            R_PACK tmp = { REN, (void*)new pge::ren(paths[id]), __static__,id };
            this->rsrc.push_back(tmp);
            return (pge::ren*)tmp.second;
        }

        void clear(){
            //std::vector<unsigned int> mark_for_delete;

            for(unsigned int i = 0; i < rsrc.size(); i++){
                if(!rsrc[i].third){
                    //mark_for_delete.push_back((unsigned int)i);
                    switch(rsrc[i].first){ 
                        case R_TYPES::SPR:
                            delete ((pge::SprSheet*)rsrc[i].second);
                        break;
                        case R_TYPES::REN:
                            delete ((pge::ren*)rsrc[i].second);
                        break;
                        case R_TYPES::ANI_REN:
                            delete ((pge::aniren*)rsrc[i].second);
                        break;
                    };
                    rsrc.erase(rsrc.begin() + i);
                    i--;
                }
            }

            //for(auto& i : mark_for_delete){
            //    rsrc.erase(rsrc.begin() + i);
            //    for(auto& i1 : mark_for_delete)
            //        --i1;
            //}
            
        }
    private:
        std::vector<R_PACK> rsrc;
};