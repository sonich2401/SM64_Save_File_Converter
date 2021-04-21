#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typedefs.h>

typedef struct {
  uint32 linec;
  string fn;
  string * dat;
  uint32 buff_size;
}rFile;


rFile * loadTextFile(string file_path);

string loadTextLineFile(string file_path);




//Erases  a line from a file and moves all of the data upwards
void eraseFileLine(rFile * file, uint32 line);

//Checks to see if the string table needs to be expanded
void checkFileBufferHeath(rFile * file);

void setFileLine(rFile * file, uint32 line, string new_line);

void insertFileLine(rFile * file, uint32 line, string new_line);

void appendFileLine(rFile * file, uint32 line, string new_line);