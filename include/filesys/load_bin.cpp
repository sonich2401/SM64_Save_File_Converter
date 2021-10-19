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
#include "load_bin.h"
#include <string.h>
#include "os/Linux/XFileSelector/utils/FileUtils.h"

char * load_bin(const cstring file_path, bool zero){
    fu_BinFile file = fu_load_bin_file(file_path);
    char* buffer = (char*)malloc(file.size);
    buffer = (char*)memcpy(buffer, file.bin, file.size);
    fu_free_bin_file(file);
    return (char*)buffer;
}

char * load_bin(const char * file_path, bool zero){
    return load_bin((cstring)file_path, zero);
}

void write_bin(const cstring fn, unsigned char * buffer, uint32 buffer_size){
    fu_BinFile ret;
    ret.bin = (char*)buffer;
    ret.size = buffer_size;
    fu_save_bin_file(fn, ret);
    return;
}