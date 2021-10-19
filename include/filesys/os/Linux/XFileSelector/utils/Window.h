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
#pragma once
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xcms.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <functional>



std::vector<std::string> split(std::string str, std::string term);


#include <iostream>
#include <stdexcept>
#include <stdio.h>

#define MAX_OUTPUT 300

#ifdef WIN32
	#define popen _popen
	#define pclose _pclose
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif

std::vector<std::string> getSubDir(std::string rootDir, bool fullPath);

std::vector<std::string> getDirFiles(std::string rootDir, std::string fileType, bool fullPath);


time_t getFileModifiedTime(std::string filePath);

time_t getFileModifiedTime(char * filePath);

time_t getFileModifiedTime(const char * filePath);


union Color{
    Color();
    Color(std::string fn, Display * dis, Window win);
    Color(unsigned char r, unsigned char g, unsigned char b);
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    struct{
        //unsigned char a, b, g, r;   //Big endian
        unsigned char r, g, b, a;   //litte endian
    }rgba;

    long bytes;

    XColor xcolor;

    XcmsColor xcmsColor;
};

template<typename T>
struct v2d{
    T x, y;
};


struct Directory;

struct Directory {
    Directory();
    
	Directory * last = nullptr;
	std::string dir;
	Directory * next = nullptr;

	void cd(std::string new_dir);

	std::string getFullDir();

    void upDirectory();

    void setDirectory(std::string dir);

    void clear();

    Directory* copy(Directory*rlast = nullptr);
};


typedef void (*Callback)(void *);

struct Button{
    Button(std::string text, unsigned int x, unsigned int y, int width, int height, void (*action)(void*));
    Button(std::string text, int type, unsigned int x, unsigned int y, int width, int height, void (*action)(void*));
    std::string text;
	unsigned int x,y;
	int width, height;
    int type;
    bool clicked;
	//Callback action;
    std::function<void(void*)> action;

    bool ButtonClick(unsigned int clickx, unsigned int clicky);
};

class MainWin{
    public:
        MainWin(std::string title, v2d<unsigned int> dimentions);

        virtual void Redraw();

        virtual void Event(XEvent * event);

        virtual void Start(void * ret_data = nullptr);

    public:
        Display *dis;
        int screen;
        Window win;
        GC gc;

    public:
        float scroll;
        v2d<unsigned int> mouse;
        v2d<unsigned int> size;
        std::vector<Button> buttons;


    void DrawRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Color c = Color(255, 255, 255, 255));

    void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Color c = Color(57, 57, 58, 1));

    void DrawString(long int x, long int y, char * text, Color c = Color(255, 255, 255, 255));

    void DrawLine(unsigned int x, unsigned int y, unsigned int x1, unsigned int y1);

    void DrawButton(Button& bt);

    void DrawButton(Button& bt, int offx, int offy);

    void AddButton(v2d<int> pos, v2d<unsigned int> wh, std::string text, void (*func)(void*));

    void AddButton(v2d<int> pos, v2d<unsigned int> wh, std::string text, int type,  void (*func)(void*));
  
    void Clear();

    public:
        ~MainWin();
};
