/*RenDev#2616 File Utilites
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

/***********************    README ********************************

  What is this?:
    This is a single file solution to all of your file accessing needs.
  
  Why C?
    Because it can work in both C++ and C code.
  
  How do I use it?
    Define FILE_UTIL_IMP in ONLY one .c/.cpp file. 
    I would recommend that you define it in a separate .c/.cpp file so that if you make changes
    to your other .c files it will not have to recompile this

  How does memory management work?
    For C developers you will have to remember to free up any lists or bin files
    that you have laying around that you are no longer using.
    You can do this by doing
      fu_free_<NAME OF TYPE>(object);

    C++ developers have the advantage because I have added constructors and destructors for
    C++ developers. You can turn this off by defining FU_NO_STRUCT_FUNCTIONS. You can force it by defining FU_USE_STRUCT_FUNCTIONS
    C++ has the folowing upgrades
      - Constructors
      - Destructors
      - wrapper functions for C functions
      - operator[] for fu_List, fu_TextFile, and fu_BinFile

  How do Lists work?
    Lists, Text, and Bin files all use the same struct.
    There are 2 members
      text / bin
      size
    text / bin is a pointer to raw memory
    size is the amount of elements stored at that raw memory.
    for text it will tell you how many lines there are and for
    bin it will tell you how many bytes are in the file.

  Can I use this in multiple files?
    Yes. Because it is a single file solution it can only be defined once but you can include
    this as a header anywhere in your programs.

  Am I allowed to use this without crediting you?
    Yes. Open source all the way. You do not have to credit me but I would appreciate it :)
    If you would like to credit me, either
      Link my GH: github.com/sonich2401
      Link my Discord: RenDev#2616
        or
      Link my email: vgngamingnetwork@gmail.com

*********************************** END OF README ***********************************/


#ifndef FILE_UTILS_H
#define FILE_UTILS_H


#include <sys/stat.h> //File stating, lstat()
#define FU_LIST_END NULL

#include "FileUtilsSettings.h"


#ifndef __cplusplus
  #include <stdbool.h> //bool, true, false
#else
  #ifndef FU_NO_STRUCT_FUNCTIONS
    #define FU_USE_STRUCT_FUNCTIONS
  #else
    #undef FU_USE_STRUCT_FUNCTIONS
  #endif
#endif

#ifdef _WIN32
#undef __restrict__
#define __restrict__ __restrict
#endif

//A special struct to hold a bin file
//fu_List.bin is an array of bytes.
//You can access the data by doing myBinFile.bin[index];
//You can get the number of bytes in the bin file by doing myBinFile.size;
#ifndef FU_USE_STRUCT_FUNCTIONS
typedef struct{
  unsigned long long size;
  char* bin;
}fu_BinFile;
#else
struct fu_BinFile{
  fu_BinFile();
  fu_BinFile(const char* path);
  fu_BinFile(unsigned long long int bsize, char* buffer);

  unsigned long long size;
  char* bin;

  unsigned long long int get_hash();
  char operator[](unsigned long long int index);


  ~fu_BinFile();
};
#endif

//A special struct to hold a list of items. Namely text.
//fu_List.text is a 2D array of text that stores the lines of the list.
//You can access the data by doing myList.text[index];
//You can get the number of items in the list by doing myList.size;
#ifndef FU_USE_STRUCT_FUNCTIONS
  typedef struct {
    unsigned long long size;
    char** text;
  }fu_List;
#else
  struct fu_List {
    fu_List();
    fu_List(const char* path);
    fu_List(unsigned long long int lines, char** items);

    unsigned long long size;
    char** text;

    void load_text_file(const char* path);
    fu_BinFile to_bin();
    char* operator[](unsigned long long int index);

    ~fu_List();
  };
#endif


//A special struct to hold a list of items. Namely text.
//fu_List.text is a 2D array of text that stores the lines of the list.
//You can access the data by doing myList.text[index];
//You can get the number of items in the list by doing myList.size;
typedef fu_List fu_TextFile;


//A timestamp that is derived from a file
typedef struct{
  unsigned char hour   : 5;
  unsigned char minute : 7;
  unsigned char second : 7;
  unsigned char day    : 6;
  unsigned char month  : 5;
  unsigned short year;
}Timestamp;

//This union/struct will allow you to get the rwx status of a file. The names are self explainitory
typedef union{
  struct{
    bool exists : 1;
    bool not_accessible : 1;
    bool readable : 1;
    bool writeable : 1;
    bool read_only : 1;
    bool executable : 1;
  };
  unsigned char chr_form;
}FilePerms;

//This struct will contain all information for a given file.
//It includes modified and created time, permissions, file name, and the size of the file

#ifndef FU_USE_STRUCT_FUNCTIONS
typedef struct {
  Timestamp modified;
  Timestamp created;
  char * file_name;
  FilePerms perms;

  unsigned long bytes;
}FileStats;
#else
struct FileStats{
  Timestamp modified;
  Timestamp created;
  char * file_name;
  FilePerms perms;

  unsigned long bytes;

  ~FileStats();
};
#endif


//This function will return a list of all files and folders contained in the directory given.
//Use the `show_hidden` flag to see hidden files
fu_List fu_get_dir_contents(char * __restrict__ folder, bool show_hidden);
//This function will return a list of all files contained in the directory given.
//Use the `show_hidden` flag to see hidden files
fu_List fu_get_dir_files(char * __restrict__ folder, bool show_hidden);
//This function will return a list of all folders contained in the directory given.
//Use the `show_hidden` flag to see hidden files
fu_List fu_get_dir_folders(char * __restrict__ folder, bool show_hidden);

//Get a struct containing all info about a file. See the FileStats struct for more info
FileStats fu_get_file_info(const char * __restrict__ file_path);
//Get a timestamp for when a given file was created
Timestamp fu_get_file_created_time(const char * __restrict__ file_path);
//Get a timestamp for when a given file was modified
Timestamp fu_get_file_modified_time(const char * __restrict__ file_path);
//Get the size of a given file
unsigned long fu_get_file_size(const char * __restrict__ file_path);
//Get file / folder permissions
FilePerms fu_get_file_perms(const char * __restrict__ file_path);

//Load a binary file into a fu_List struct. See fu_List for more info on how to use
fu_BinFile fu_load_bin_file(const char * __restrict__ file_path);
//Load a text file into a fu_List struct. See fu_List for more info on how to use
fu_TextFile fu_load_text_file(const char * __restrict__ file_path);

//Save a binary file to the disk.
void fu_save_bin_file(const char * __restrict__ file_path, fu_BinFile bin);
//Save a text file to the disk.
void fu_save_text_file(const char * __restrict__ file_path, fu_TextFile text);

//Duplicate contents from src to dest
fu_BinFile* fu_memcpy_bin_file(fu_BinFile * dest, fu_BinFile* __restrict__ src);
//Duplicate contents from src to dest
fu_TextFile* fu_memcpy_text_file(fu_TextFile * dest, fu_TextFile* __restrict__ src);
//Duplicate contents from src to dest
fu_List* fu_memcpy_list(fu_List * dest, fu_List* __restrict__ src);

//Duplicate contents from src to dest
fu_BinFile fu_create_bin_copy(fu_BinFile src);
//Duplicate contents from src to dest
fu_TextFile fu_create_text_copy(fu_TextFile src);
//Duplicate contents from src to dest
fu_List fu_create_list_copy(fu_List src);

//Get a hash for a bin file
unsigned long long fu_get_hash(fu_BinFile file);
//Convert a fu_TextFile into a fu_BinFile. This will allocate more memory so make sure to free this
fu_BinFile fu_to_bin(fu_TextFile text_file);

//Free memory inside of a fu_List object
void fu_free_list(fu_List list);
//Free memory inside of a fu_TextFile object
void fu_free_text_file(fu_TextFile txt_file);
//Free memory inside of a fu_BinFile object
void fu_free_bin_file(fu_BinFile bin_file);
//Free memory inside of a FileStats object
void fu_free_FileStats(FileStats filestat);

//Update the modified time of a file and create it if it does not exist
void fu_touch_file(const char * __restrict__ file_path);
//Return a string containing the name of the user.
char* fu_get_current_user();






#ifdef FILE_UTIL_IMP
#include <string.h> //malloc(), strcpy(), free()
#include <time.h> //time struct, localtime()
#include <stdlib.h> 
#include <sys/types.h>
#ifndef _WIN32
    #include <unistd.h> //access()
    #include <dirent.h> //dirent, opendir(), closedir(), readdir()
    #include <errno.h> //errno
#else
    #include <Windows.h>
    #define random rand
    #define srandom srand
#endif

#include <stdio.h> //perror(), printf(), fopen(), fseek(), fwrite(), ftell()

struct stat futil__st;
FileStats futil__last_stat;

void fu_helper__init_timestamp(Timestamp * __restrict__ ts){
  ts->day = 0;
  ts->month = 0;
  ts->year = 0;
  ts->hour = 0;
  ts->minute = 0;
  ts->second = 0;
}

void fu_helper__init_fstat(FileStats * __restrict__ fstat){
  fstat->bytes = 0;
  fu_helper__init_timestamp(&fstat->created);
  fu_helper__init_timestamp(&fstat->modified);
  fstat->file_name = (char*)malloc(1);
  fstat->file_name[0] = '\0';
}

void fu_helper__set_timestamp(Timestamp * ts, int sec, int min, int h){
  ts->second = sec;
  ts->minute = min;
  ts->hour = h;
}

#ifndef _WIN32
char fu_helper__isDir(struct dirent* __restrict__ dir){
  //printf("TYPE = %i, TEST = %i, NAME = \"%s\", BOOL = %i\n", dir->d_type, DT_DIR, dir->d_name, dir->d_type == DT_DIR);
  return dir->d_type == DT_DIR || dir->d_type == DT_LNK;
}

char fu_helper__isFile(struct dirent* __restrict__ dir){
  //printf("TYPE = %i, TEST = %i, NAME = \"%s\", BOOL = %i\n", dir->d_type, DT_REG, dir->d_name, dir->d_type == DT_REG);
  return dir->d_type == DT_REG;
}
#endif


#ifndef _WIN32
FileStats * fu_helper__update(const char * __restrict__ file_path){
  lstat(file_path, &futil__st);

  free(futil__last_stat.file_name);
  futil__last_stat.file_name = (char*)malloc(strlen(file_path));
  futil__last_stat.file_name = strcpy(futil__last_stat.file_name, file_path);
  futil__last_stat.bytes = futil__st.st_size;

  struct tm *conv_tm = (struct tm*)localtime(&futil__st.st_mtim.tv_sec);

  futil__last_stat.modified.second = conv_tm->tm_sec;
  futil__last_stat.modified.minute = conv_tm->tm_min;
  futil__last_stat.modified.hour = conv_tm->tm_hour;

  futil__last_stat.modified.day = conv_tm->tm_mday;
  futil__last_stat.modified.month = conv_tm->tm_mon;
  futil__last_stat.modified.year = conv_tm->tm_year + 1900;

  return &futil__last_stat;
}

//If folder is true then include folders in the list
//If files is true then include files in the list
//if show_hidden is true then show the hidden files
fu_List fu_helper__get_dir_contents(char * __restrict__ folder, bool folders, bool files, bool show_hidden){
  char ** ret = NULL;
  DIR * d = opendir(folder);
  struct dirent* dir;
  unsigned long long element_count = 0;

  char* p;

  while((dir = readdir(d)) != NULL){
    //Get rid of "." and ".." directory entries
    if(dir->d_name[0] == '.'){
      if(!show_hidden)
        continue;
      if(strlen(dir->d_name) == 1)
        continue;
      if(dir->d_name[1] == '.'){
        if(strlen(dir->d_name) == 2)
          continue;
      }
    }
    if(fu_helper__isDir(dir) & !folders){
      continue;
    }
    if(fu_helper__isFile(dir) & !files){
      continue;
    }

    if(ret == NULL){
      ret = (char**)malloc(sizeof(char*));
    }else{
      ret = (char**)realloc(ret, sizeof(char*) * (element_count + 1));
    }
    p = ret[0];
    //printf("ELEMENT %i\n", element_count);
    ret[element_count] = (char*)malloc(256);
    strcpy(ret[element_count], dir->d_name);
    element_count++;
  }

  closedir(d);

  fu_List return_struct;
  return_struct.size = (unsigned long long)element_count;
  return_struct.text = ret;
  return return_struct;
}

fu_List fu_get_dir_contents(char * __restrict__ folder, bool show_hidden){
  return fu_helper__get_dir_contents(folder, 1, 1, show_hidden);
}

fu_List fu_get_dir_files(char * __restrict__ folder, bool show_hidden){
  return fu_helper__get_dir_contents(folder, 0, 1, show_hidden);
}

fu_List fu_get_dir_folders(char * __restrict__ folder, bool show_hidden){
  return fu_helper__get_dir_contents(folder, 1, 0, show_hidden);
}
#endif

void fu_free_list(fu_List list){
  for(unsigned long long i = 0; i < list.size; i++){
    free(list.text[i]);
  }
  list.text = NULL;
}

void fu_free_text_file(fu_TextFile txt_file){
  fu_free_list(txt_file);
}

void fu_free_bin_file(fu_BinFile bin_file){
  #ifdef FU_USE_STRUCT_FUNCTIONS
    if(bin_file.bin == nullptr)
      return;
  #endif
  free(bin_file.bin);
}


void fu_free_FileStats(FileStats filestat){
  free(filestat.file_name);
}


#ifndef _WIN32
FileStats fu_get_file_info(const char * __restrict__ file_path){
  return *fu_helper__update(file_path);
}

Timestamp fu_get_file_created_time(const char * __restrict__ file_path){
  return fu_helper__update(file_path)->created;
}

Timestamp fu_get_file_modified_time(const char * __restrict__ file_path){
  return fu_helper__update(file_path)->modified;
}

unsigned long fu_get_file_size(const char * __restrict__ file_path){
  return fu_helper__update(file_path)->bytes;
}
#endif


char* fu_helper__resolve_tabs(char* __restrict__ str){
  const int TAB_SIZE = 4;
  char* og_str = str;

  unsigned long long int tab_count = 0;
  for(unsigned long long int i = 0; i < strlen(str); i++){
    tab_count += str[i] == '\t';
  }

  unsigned long long int new_size = strlen(str) - tab_count + (tab_count * TAB_SIZE) + 1;
  char* new_buff = (char*)malloc(new_size);
  char* new_buff_og = new_buff;
  for(unsigned long long int i = 0; i <= new_size; i++){
    if(str > og_str + strlen(og_str)){
      break;
    }
    if(*str == '\t'){
      for(unsigned char i1 = 0; i1 < TAB_SIZE; i1++){
        *new_buff = ' ';
        new_buff++;
      }
      str++;
    }else{
      *new_buff = *str;
      new_buff++;
      str++;
    }
  }
  new_buff_og[new_size - 1] = '\0';

  free(og_str);
  return new_buff_og;
}

fu_BinFile fu_load_bin_file(const char * __restrict__ file_path){
  FILE *f = fopen(file_path, "r");
  if(f == NULL){
    printf("ERR: fu_load_bin_file(): Couldn't load file \"%s\"\n", file_path);
    exit(-1);
  }
  fseek(f, 0, SEEK_END);
  int fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  if(fsize <= 0){
    printf("ERR: fu_load_bin_file(): File size = 0!\n");
    fclose(f);
    exit(-1);
  }

  #if 0
    char buffer[1000];
    char* ret_buffer = NULL;
    long long int f1size = 0;
    while (fgets(buffer, sizeof buffer, f) != NULL) {
      f1size += strlen(buffer);
      if(ret_buffer == NULL){
        ret_buffer = (char*)malloc(f1size);
        strcpy(ret_buffer, buffer);
      }else{
        realloc(ret_buffer, f1size);
        strcat(ret_buffer, buffer);
      }
    }
    
    //fread(buffer, fsize, fsize, f);
  #else
    char* ret_buffer = (char*)malloc(fsize);
    fread(ret_buffer, fsize, fsize, f);
  #endif

  fclose(f);

  fu_BinFile ret;
  ret.bin = ret_buffer;
  ret.size = fsize;
  return ret;
}

fu_TextFile fu_load_text_file(const char * __restrict__ file_path){
  fu_BinFile binfile = fu_load_bin_file(file_path);
  char* buffer = binfile.bin;
  char* og_buffer_ptr = buffer;

  //Get total amount of lines
  unsigned long long nline_count = 1;
  unsigned long long nline_last = -1;
  for(unsigned long long i = 0; i < strlen(buffer); i++){
    if(buffer[i] == '\n'){
      nline_count++;
      nline_last = i;
    }
  }
  //was there text at the end that we missed?
  if(buffer[strlen(buffer) - 1] != '\n')
    nline_count++;
  

  //create string array
  char** ret_buff = (char**)malloc(sizeof(char*) * nline_count);
  unsigned long long int chars_processed = 0;
  for(unsigned long long i = 0; i + 1 < nline_count; i++){
    unsigned long long nline_strlen = 0;
    unsigned long long i1 = 0;
    while(1){
      if(chars_processed + 1 < binfile.size){
        if(buffer[i1] == '\n')
          break;
        nline_strlen++;
        i1++;
        chars_processed++;
        continue;
      }
      break;
    }

    ret_buff[i] = (char*)malloc(nline_strlen + 1);
    memcpy(ret_buff[i], buffer, nline_strlen);
    ret_buff[i][nline_strlen] = '\0';
    ret_buff[i] = fu_helper__resolve_tabs(ret_buff[i]);

    buffer += (nline_strlen + 1);
  }

  #ifndef FU_USE_STRUCT_FUNCTIONS
    fu_free_bin_file(binfile);
  #endif

  fu_TextFile ret;
  ret.text = ret_buff;
  ret.size = nline_count - 1;
  return ret;
}

#ifndef _WIN32
FilePerms fu_get_file_perms(const char * __restrict__ file_path){
  FilePerms ret;
  ret.chr_form = 0;
  errno = 0;

  int opcode = access(file_path, F_OK);
  ret.exists = (opcode == 0) && (errno != ENOENT);
  ret.not_accessible = (errno == EACCES);

  opcode = access(file_path, R_OK);
  ret.readable = (opcode == 0);
  
  opcode = access(file_path, W_OK);
  ret.writeable = (opcode == 0) && (errno != EACCES);
  ret.read_only = (opcode != 0) && (errno == EROFS);

  opcode = access(file_path, X_OK);
  ret.executable = (opcode == 0) && (errno != EACCES);

  return ret;
}
#endif

void fu_save_bin_file(const char * __restrict__ file_path, fu_BinFile bin){
  FILE* f = fopen(file_path, "wb");
  if(!f){
    perror("ERR: File could not open (fu_save_bin_file)");
    exit(-1);
  }

  fwrite(bin.bin, sizeof(char), bin.size, f);
  fclose(f);
}

void fu_save_text_file(const char * __restrict__ file_path, fu_TextFile text){
  FILE* f = fopen(file_path, "wb");
  if(!f){
    perror("ERR: File could not open (fu_save_text_file)");
    exit(-1);
  }

  for(unsigned long long int i = 0; i < text.size; i++){
    fwrite(text.text[i], sizeof(char), strlen(text.text[i]), f);
    fwrite("\n", sizeof(char), 1, f);
  }
  fclose(f);
}

fu_BinFile* fu_memcpy_bin_file(fu_BinFile * dest, fu_BinFile* __restrict__ src){
  dest->size = src->size;
  dest->bin = (char*)malloc(src->size);
  dest->bin = (char*)memcpy(dest->bin, src->bin, src->size);
  return dest;
}

fu_TextFile* fu_memcpy_text_file(fu_TextFile * dest, fu_TextFile* __restrict__ src){
  dest->size = src->size;

  dest->text = (char**)malloc(sizeof(char*) * src->size);
  for(unsigned long long int i = 0; i < src->size; i++){
    dest->text[i] = (char*)malloc(strlen(src->text[i]) + 1);
    strcpy(dest->text[i], src->text[i]);
  }
  return dest;
}

fu_List* fu_memcpy_list(fu_List * dest, fu_List* __restrict__ src){
  return (fu_List*)(void*)fu_memcpy_text_file(dest, src);
}

fu_BinFile fu_create_bin_copy(fu_BinFile src){
  fu_BinFile ret;
  fu_memcpy_bin_file(&ret, &src);
  return ret;
}

fu_TextFile fu_create_text_copy(fu_TextFile src){
  return (fu_TextFile)fu_create_list_copy(src);
}

fu_List fu_create_list_copy(fu_List src){
  fu_List ret;
  fu_memcpy_list(&ret, &src);
  return ret;
}


unsigned long long fu_get_hash(fu_BinFile file){
  unsigned long long ret = 0x12345;
  for(unsigned long long int i = 0; i < file.size; i++){
    srandom(ret - i);
    ret = (ret + (random() % (file.bin[i] | 1))) << (random() % ((i | 1) % 100));
    ret |= ret + 0x20;
    ret -= file.bin[i];
  }
  return ret;
}

fu_BinFile fu_to_bin(fu_TextFile text_file){
  unsigned long long int byte_buffer_size = 0;
  for(unsigned long long i = 0; i < text_file.size; i++){
    byte_buffer_size += strlen(text_file.text[i]) + (i + 1 < text_file.size);
  }

  fu_BinFile ret;
  ret.size = byte_buffer_size;
  ret.bin = (char*)malloc(byte_buffer_size);

  char* buffer = ret.bin;
  for(unsigned long long i = 0; i < text_file.size; i++){
    memcpy(buffer, text_file.text[i], strlen(text_file.text[i]));
    if(i + 1 < text_file.size){
      buffer[strlen(text_file.text[i])] = '\n';
    }
    buffer +=  strlen(text_file.text[i]) + (i + 1 < text_file.size);
  }
  return ret;
}

void fu_touch_file(const char * __restrict__ file_path){
  #define CMD_STR "touch \""
  char * cmd = (char*)malloc(strlen(CMD_STR) + strlen(file_path) + 1);
  strcat(cmd, file_path);
  strcat(cmd, "\"");
  system(cmd);
  free(cmd);
}

char* fu_get_current_user(){
  return getenv("USER");
}


#ifdef FU_USE_STRUCT_FUNCTIONS //CPP features


//fu_BinFile
fu_BinFile::fu_BinFile(){
  this->size = 0;
  this->bin = nullptr;
}

fu_BinFile::fu_BinFile(unsigned long long int bsize, char* buffer){
  this->size = 0;
  this->bin = nullptr;
}

fu_BinFile::fu_BinFile(const char* path){
  *this = fu_load_bin_file(path);
}

unsigned long long int fu_BinFile::get_hash(){
  return fu_get_hash(*this);
}

char fu_BinFile::operator[](unsigned long long int index){
  return this->bin[index];
}

fu_BinFile::~fu_BinFile(){
  if(this->bin == nullptr){
    free(this->bin);
    this->bin = nullptr;
  }
}


//fu_List
fu_List::fu_List(){
  this->size = 0;
  this->text = nullptr;
}

fu_List::fu_List(const char* path){
  this->load_text_file(path);
}

fu_List::fu_List(unsigned long long int lines, char** items){
  this->size = lines;
  this->text = items;
}

void fu_List::load_text_file(const char* path){
  if(this->text != nullptr){
    fu_free_list(*this);
  }
  fu_List tmp = fu_load_text_file(path);
  *this = tmp;
  tmp.text = nullptr;
}

fu_BinFile fu_List::to_bin(){
  fu_List& reference = *this;
  return fu_to_bin(reference);
}

char* fu_List::operator[](unsigned long long int index){
  return this->text[index];
}

/*fu_List::~fu_List(){
  if(this->text != nullptr){
    fu_List& reference = *this;
    fu_free_list(reference);
    reference.text = nullptr;
  }
}*/


//FileStats
FileStats::~FileStats(){
  if(file_name != nullptr)
    free(this->file_name);
}
#endif


#endif

#endif