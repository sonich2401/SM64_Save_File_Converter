#include "loadfile.h"


#define LOAD_FILE_MAX_LINES 500
#define LOAD_FILE_MAX_CHARS 300




rFile * loadTextFile(cstring file_path){
  
    rFile * rret;
    rret = malloc(sizeof(rFile));
    rret->fn = malloc(strlen(file_path)+1);
    strcpy(rret->fn, file_path);

    string * ret;
    unsigned long max_line = LOAD_FILE_MAX_LINES;
    unsigned long cur_line = 0;
    ret = malloc(sizeof(string) * max_line );

   FILE *file = fopen (  file_path, "r" );
   if ( file != NULL )
   {
      char line [ LOAD_FILE_MAX_CHARS ]; 

      while ( fgets ( line, sizeof(line), file ) != NULL)
      {
        if(feof(file)){break;}//Check if end of file

        if(cur_line+1 >= max_line){
          max_line += 50;
          ret = realloc(ret, max_line * sizeof(string)); 
        }
        ret[cur_line] = malloc(strlen(line)+1);
        strcpy(ret[cur_line++],line);
      }
      fclose ( file );
   }
  rret->buff_size = max_line;
  rret->linec = cur_line;
  rret->dat = ret;
  rret;
}

#undef LOAD_FILE_MAX_LINES
#undef LOAD_FILE_MAX_CHARS

//Erases  a line from a file and moves all of the data upwards
void eraseFileLine(rFile * file, uint32 line){
  file->linec--;
  for(uint32 i = line; i < file->linec; i++){
    file->dat[i] = file->dat[i+1];
  }
  free(file->dat[file->linec]);
  file->dat[file->linec] = NULL;
}

//Checks to see if the string table needs to be expanded
void checkFileBufferHeath(rFile * file){
  if(file->buff_size <= file->linec + 1){ //Check if we need to resize the string table
    file->buff_size += 50;
    file->dat = realloc(file->dat, file->buff_size * sizeof(string));
  }
}

void setFileLine(rFile * file, uint32 line, cstring new_line){

  if(file->dat[file->linec] != NULL){ //Make sure we dont have memory leaks
    free(file->dat[file->linec]);
  }

  file->dat[file->linec] = malloc(strlen(new_line)+1);
  strcpy(file->dat[line],new_line); //Copy the new string into the slot
}

void insertFileLine(rFile * file, uint32 line, cstring new_line){

  checkFileBufferHeath(file); //Make sure we have enough memory

  for(uint32 i = file->linec; i >= line; i--){ //Move everything up a slot
    file->dat[i + 1] = file->dat[i];
  }

  setFileLine(file, line, new_line);

  file->linec++;
}

void appendFileLine(rFile * file, uint32 line, cstring new_line){
  checkFileBufferHeath(file); //Make sure we have enough memory
  setFileLine(file, file->linec, new_line);
}



cstring loadTextLineFilec(string file_path){
  string ret = " ";
  return ret;
}