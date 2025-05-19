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
#include "Window.h"


std::vector<std::string> split_c(std::string str, char term){
    std::vector<std::string> ret;
    std::string cur_line = "";

    for(unsigned int i = 0; i < str.size(); i++){
        if(str[i] == term){
            ret.push_back(cur_line);
            cur_line = "";
            continue;
        }
        cur_line += str[i];
    }

    if(cur_line != "")
        ret.push_back(cur_line);
    return ret;
}

std::vector<std::string> split(std::string str, std::string term){
    std::vector<std::string> ret;
    std::string cur_line = "";

    for(unsigned int i = 0; i < str.size(); i++){
        if(i + term.size() < str.size()){
            if(str.substr(i, term.size()) != term)
                cur_line += str[i];
            else{
                i += term.size();
                ret.push_back(cur_line);
                cur_line = "";
            }
        }
    }
    if(cur_line != "")
        ret.push_back(cur_line);
    return ret;
}


time_t getFileModifiedTime(std::string filePath){
    return getFileModifiedTime(filePath.c_str());
}

time_t getFileModifiedTime(char * filePath){
    return getFileModifiedTime((const char *)(void*)filePath);
}


time_t getFileModifiedTime(const char * filePath){
    struct stat fileInfo;

    assert(!stat(filePath, &fileInfo));

    return fileInfo.st_mtime;
}




Color::Color(){
    this->bytes = 0;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b){
    this->xcmsColor.spec.RGB.red = r;
    this->xcmsColor.spec.RGB.green = g;
    this->xcmsColor.spec.RGB.blue = b;
}

Color::Color(std::string fn, Display * dis){
    int s = DefaultScreen(dis);
    Colormap colormap = DefaultColormap(dis, s);
    XColor used, unused;
    XAllocNamedColor(dis, colormap, fn.c_str(),  &used, &unused);
    this->bytes = used.pixel;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
    this->rgba.r = r;
    this->rgba.g = g;
    this->rgba.b = b;
    this->rgba.a = a;
    
}



Directory::Directory(){
    
}

void Directory::cd(std::string new_dir){
    if(next != nullptr){ 
        next->cd(new_dir);
        return;
    }

	this->next = new Directory();
	this->next->last = this;
	this->next->dir = new_dir;
    this->next->next = nullptr;
    
}

std::string Directory::getFullDir(){
    std::string ret = "/" + this->dir;
    if(this->dir == "/")
        ret = "";
    if(this->next != nullptr)
        return ret + this->next->getFullDir();
    if(this->last == nullptr)
        return "/";
    return ret;
}

void Directory::upDirectory(){
    if(this->next != nullptr){
        if(this->next->next == nullptr){
            delete this->next;
            this->next = nullptr;
            return;
        }
        this->next->upDirectory();
    }
}

void Directory::setDirectory(std::string dir){
    std::vector<std::string> foldernames = split_c(dir, '/');

    this->dir = foldernames[0];
    if(this->dir == "")
        this->dir = "/";
    foldernames.erase(foldernames.begin() + 0);

    this->clear();

    for(std::string& fname : foldernames){
        this->cd(fname);
    }
}

void Directory::clear(){
    if(this->next != nullptr)
        this->next->clear();
    delete this->next;
    this->next = nullptr;
}

Directory* Directory::copy(Directory* rlast){
    Directory* node_copy = new Directory();
    node_copy->dir = this->dir;
    node_copy->last = rlast;
    node_copy->next = nullptr;
    if(this->next != nullptr){
        node_copy->next = copy(node_copy);
    }
    return node_copy;
}



Button::Button(std::string text, unsigned int x, unsigned int y, int width, int height, void (*_action)(void*)){
    this->text = text;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->action = _action;
    this->clicked = false;
}

Button::Button(std::string text, int type, unsigned int x, unsigned int y, int width, int height, void (*_action)(void*)){
    this->text = text;
    this->type = type;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->action = _action;
    this->clicked = false;
}

bool Button::ButtonClick(unsigned int clickx, unsigned int clicky){
    return clickx > this->x && 
           clickx < this->x + this->width &&
           clicky > this->y &&
           clicky < this->y + this->height;
}


