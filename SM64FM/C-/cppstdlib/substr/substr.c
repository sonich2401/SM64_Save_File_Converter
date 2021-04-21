#include "substr.h"
#include <stdlib.h>
#include <string.h>

string substr(string src, uint16 start, uint16 end){
    string ret = malloc(end - start+ 1);
    memcpy(ret, &src[start], end - start);
    ret[end - start] = 0; //Null terminate
    return ret;
}