/*RenDev#2616 File Selector Tool
    Copyright (C) 2021 RenDev

    Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
    Permission is also granted to not credit the author in any way as long as you do not take credit
    for this piece of software.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    binary, for any purpose, commercial or non-commercial, and by any
    means.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, 
    OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
    DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS 
    ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Contact me at vgngamingnetwork@gmail.com if you need to contact me about this licence*/

#include "FileSelect.h"
#include "utils/FileUtils.h"
#include <string.h>

FileSelect* fsel;

FileSelect::FileSelect(std::string title, v2d<unsigned int> dimentions, bool save_mode, bool isPipe, bool select_mode) : MainWin(title, dimentions){
    this->select_mode = select_mode;
    this->end = false;
    this->isPipe = isPipe;
    show_hidden = false;
    this->usr = fu_get_current_user();

    init_main_buttons();
    fsel = this;
    curdir.cd("home");
    curdir.cd(usr);
    RefreshItemList();
}

void FileSelect::Start(void * ret_data){
    XEvent event;

    while(1) {
        XNextEvent(dis, &event);

        Event(&event);
        if(this->end){
            *((std::string*)ret_data)= ret;
            
            return;
        }
        Redraw();
    }
}

void FileSelect::init_main_buttons(){
    this->AddButton(
        {0,size.y - 25},
        {75,25},
        "<",
        [](void * ptr){   
            fsel->scroll = 0;        
            fsel->curdir.upDirectory();
            fsel->RefreshItemList();
        }
    );

#if 1
(void)0;
#else
    this->AddButton(
        {75,SCREEN_H - 25},
        {75,25},
            "+Fold",
            [](void * ptr){   
                fsel->scroll = 0;        
                fsel->curdir.upDirectory();
                fsel->RefreshItemList();
            }
        
    );
    this->AddButton(
        {75 + 75,SCREEN_H - 25},
        {75,25},
            "+File",
            [](void * ptr){   
                fsel->scroll = 0;        
                fsel->curdir.upDirectory();
                fsel->RefreshItemList();
            }
    );
#endif

    if(select){
        this->AddButton(
            {size.x - 75, size.y - 25},
            {75,25},
            "Select",
            [](void * ptr){
                fsel->end = true;
                fsel->curdir.cd(fsel->dircontents[fsel->selected].name);
                fsel->ret = fsel->curdir.getFullDir();
            }
        );
    }else{
        this->AddButton(
            {size.x - 75, size.y - 25},
            {75,25},
            "Open",
            [](void * ptr){
                if(fsel->dircontents[fsel->selected].type == 2){
                    fsel->scroll = 0;
                    fsel->curdir.cd(fsel->dircontents[fsel->selected].name);
                    fsel->RefreshItemList();
                }else{
                    std::string cmd = "xdg-open \"" + fsel->curdir.getFullDir() + "/" + fsel->dircontents[fsel->selected].name + "\"";
                    system(cmd.c_str());
                }
            }
        );
    }

    this->AddButton(
        {size.x - 75 - 75, size.y - 25},
        {75,25},
        "Cancel",
        [](void * ptr){
            fsel->end = true;
            fsel->ret = "...END";
        }
    );

    this->AddButton(
        {size.x - 75 - 75 - 75 - 50, size.y - 25},
        {75 + 25 + 25,25},
        "Show Hidden",
        [](void * ptr){
            fsel->show_hidden = !fsel->show_hidden;
            fsel->RefreshItemList();
        }
    );




    this->AddButton(
        {0, 0},
        {75,25},
        "Home",
        [](void * ptr){
            fsel->curdir.setDirectory("/home/" + fsel->usr);
            fsel->RefreshItemList();
        }
    );

    this->AddButton(
        {0, 25},
        {75,25},
        "Desktop",
        [](void * ptr){
            fsel->curdir.setDirectory("/home/" + fsel->usr + "/" + ((Button*)ptr)->text);
            fsel->RefreshItemList();
        }
    );

    this->AddButton(
        {0, 25 + 25},
        {75,25},
        "Documents",
        [](void * ptr){
            fsel->curdir.setDirectory("/home/" + fsel->usr + "/" + ((Button*)ptr)->text);
            fsel->RefreshItemList();
        }
    );

    this->AddButton(
        {0, 25 + 25 + 25},
        {75,25},
        "Downloads",
        [](void * ptr){
            fsel->curdir.setDirectory("/home/" + fsel->usr + "/" + ((Button*)ptr)->text);
            fsel->RefreshItemList();
        }
    );

    this->AddButton(
        {0, 25 + 25 + 25 + 25},
        {75,25},
        "Music",
        [](void * ptr){
            fsel->curdir.setDirectory("/home/" + fsel->usr + "/" + ((Button*)ptr)->text);
            fsel->RefreshItemList();
        }
    );

    this->AddButton(
        {0, 25 + 25 + 25 + 25 + 25},
        {75,25},
        "Pictures",
        [](void * ptr){
            fsel->curdir.setDirectory("/home/" + fsel->usr + "/" + ((Button*)ptr)->text);
            fsel->RefreshItemList();
        }
    );

    this->AddButton(
        {0, 25 + 25 + 25 + 25 + 25 + 25},
        {75,25},
        "Videos",
        [](void * ptr){
            fsel->curdir.setDirectory("/home/" + fsel->usr + "/" + ((Button*)ptr)->text);
            fsel->RefreshItemList();
        }
    );

    

    

    static_buttons_count = this->buttons.size();
}



void FileSelect::RefreshItemList(){
    this->selected = 0;
    this->ClearItems();
    //this->dircontents = getSubDir(this->curdir.getFullDir(), false);
    fu_List tmp = fu_get_dir_files((char*)this->curdir.getFullDir().c_str(), show_hidden);
    fu_List tmp1 = fu_get_dir_folders((char*)this->curdir.getFullDir().c_str(), show_hidden);
    
    //directory type
    for(int i = 0; i < tmp1.size; i++)
        this->dircontents.push_back({tmp1.text[i], 2});
    //file type
    for(int i = 0; i < tmp.size; i++)
        this->dircontents.push_back({tmp.text[i], 1});

    fu_free_list(tmp);
    fu_free_list(tmp1);
            
    for(unsigned int i =0; i < this->dircontents.size(); i++){
        if(this->dircontents[i].name == "\n")
            this->dircontents.erase(this->dircontents.begin() + i);
        }
            
    this->AddItems();
    XMapRaised(this->dis, this->win);
    this->Clear();
}

void FileSelect::Event(XEvent * event){
    const float SCROLL_SPEED = 20.1f;
    MainWin::Event(event);

    //TODO: Add file creation menu
    /*
    KeySym key;
	char text[255];
    if (event->type==KeyPress && XLookupString(&event->xkey, text, 255, &key,0) == 1) {
		printf("You pressed the %c key!\n",text[0]);
	}
    */

    if(event->type == ButtonPress){
        switch (event->xbutton.button){
            case 0:
            case 1:
            case 2:
            case 3:
                for(unsigned int i = 0; i < static_buttons_count; i++)
                    if(buttons[i].ButtonClick(mouse.x, mouse.y))
                        buttons[i].action(&buttons[i]);
                for(unsigned int i = static_buttons_count; i < buttons.size(); i++)
                    if(buttons[i].ButtonClick(mouse.x, mouse.y - (int)scroll))
                        buttons[i].action(&buttons[i]);
            break;
            case 4:
                scroll -= SCROLL_SPEED;
            break;

            case 5:
                scroll += SCROLL_SPEED;
            break;           
        }
        if(scroll > 0)
            scroll = 0;

        if(dircontents.size() != 0){
            if(buttons.back().y + scroll < 0) //clamp scool values
                scroll = -1 * (int)buttons.back().y;
        }
    }
}

void FileSelect::Redraw(){
    this->Clear();

    //DrawBackground Of selected option if it exists
    if(dircontents.size() != 0 && selected >= 0){
        FillRect(buttons[static_buttons_count].x, scroll + selected * 25, buttons[static_buttons_count].width, 25, Color(40,40,40,40));
    }

    for(unsigned int i = static_buttons_count; i < buttons.size(); i++)
        DrawButton(buttons[i], 0, (int)scroll);

    const int START_Y = size.y - 25;
    FillRect(0, START_Y , size.x, size.y);
    DrawLine(0, START_Y , size.x, START_Y );



    for(unsigned int i = 0; i < static_buttons_count; i++)
        DrawButton(buttons[i]);
    XSetForeground(dis, gc, Color(255, 255, 255, 255).bytes);
}

void FileSelect::ClearItems(){
    this->scroll = 0;
    this->dircontents.clear();
    auto total_iterations = buttons.size() - static_buttons_count; //IDK why but moving it here out of the for loop fixes it
    for(auto i = 0; i < total_iterations; i++){
        buttons.pop_back();
    }
    Clear();
}


void FileSelect::AddItems() {
    #define BUTTON_SIZE 25
    //XFontStruct* font_info = XLoadQueryFont(dis, "fixed");

    int max_size=0;
    // max_size = XTextWidth(font_info, dircontents[i].c_str(), dircontents[i].size());
    for(unsigned int i = 0; i < this->dircontents.size(); i++){
        if(max_size < 7 * dircontents[i].name.size())
            max_size = dircontents[i].name.size() * 7;
    }

    const int BUTTON_W = max_size + (BUTTON_SIZE * 2);
    for(unsigned int i = 0; i < this->dircontents.size(); i++){
        this->AddButton(
            //{(SCREEN_W - BUTTON_W)/2, (int)(i * 25)},
            {75, (int)(i * 25) },
            {(unsigned int)BUTTON_W, 25},
            fsel->dircontents[i].name,
            fsel->dircontents[i].type,
            [](void * ptr){
                Button* b_ptr = (Button*)ptr;
                int index = (((char*)ptr) - ((char*)&fsel->buttons[0])) / sizeof(Button); //Here's a little lesson in trickery          
                index -= fsel->static_buttons_count; //If you want to be a villan number 1
            
                fsel->selected = index; //You have to catch the superhero number 1
                if(b_ptr->clicked){
                    b_ptr->clicked = false;
                    if(fsel->dircontents[fsel->selected].type == 2){
                        fsel->dircontents.clear();
                        fsel->scroll = 0;
                        fsel->curdir.cd(b_ptr->text);
                        fsel->selected = -1;
                        fsel->RefreshItemList();
                    }
                }
                b_ptr->clicked = true;
            }
        );
    }
    #undef BUTTON_SIZE
}


