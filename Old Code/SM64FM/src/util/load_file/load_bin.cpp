#include "load_bin.h"


//https://stackoverflow.com/questions/22059189/read-a-file-as-byte-array
unsigned char * load_bin(cstring file_path){
    FILE *fileptr;
    char *buffer;
    size_t filelen;

    fileptr = fopen(file_path, "rb");  // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(fileptr);             // Get the current byte offset in the file
    rewind(fileptr);                      // Jump back to the beginning of the file

    buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    //Reuse filelen to make compiler happy
    filelen = fread(buffer, filelen, 1, fileptr); // Read in the entire file
    fclose(fileptr); // Close the file

    return (unsigned char*)buffer;
}
//

//made by me
void write_bin(cstring fn, unsigned char * buffer, uint32 buffer_size){
    FILE * file = fopen(fn, "wb");

    fwrite(buffer, 1, buffer_size, file);

    fclose(file);
    return;
}