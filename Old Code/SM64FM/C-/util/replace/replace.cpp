#include "replace.h"

/*
uint8 countInstances(string src, string count){
    uint8 ret=0;
    uint16 next_pos = 0;

    while((next_pos = rfind(src,count,next_pos + 1)) != -1){
        if(next_pos == 65535){break;}
        printf("N%i\n",next_pos);
        ret++;
    }

    return ret;
}

//Will replace all instances of a given string with a replacement string and will return a new string
string replace(string src, string filter, string replace){
    uint8 instances = countInstances(src, filter);
    string ret = malloc(instances * strlen(replace) + (strlen(src) - (strlen(filter) * instances)) + 1 ); //Give us a string that can hold the new string
    uint16 next_replace = -1;
    
    int32 start_pos = -1;
    int32 last_pos = 0;
    do {
        start_pos = rfind(src, filter, start_pos + 1);
        printf("NO: %i\n",start_pos);
        memcpy(ret + last_pos, src, start_pos - last_pos);
        memcpy(ret + start_pos, replace, strlen(replace));
        start_pos += strlen(replace) + (start_pos - last_pos); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        last_pos = start_pos;

    }while(rfind(src, filter, start_pos + 1) != rfind_FAIL);

    return ret;
}
*/


cstring replace(cstring src, cstring filter, cstring replacement){
    uint16 srclen = strlen(src);
    uint16 filterlen = strlen(filter);
    uint16 replacementlen = strlen(filter);

    uint16 instances = 0;

    //Count the ammount of times we used the filter
    for(uint16 i = 0; i < srclen; i++){
        if(strstr(&src[i], filter) == &src[i]){ //Have we found the same string at the same position?
            instances++;
            i += filterlen - 1; 
        }
    }

    //For clarity I made this macros that undefine themselfs
    #define AMOUNT_SAVED_SRC (srclen - (filterlen * instances))
    #define AMOUNT_PASTED_REPLACEMENT (instances * replacementlen)

    cstring ret = (cstring)malloc(AMOUNT_PASTED_REPLACEMENT + AMOUNT_SAVED_SRC + 1 ); //Give us a string that can hold the new string

    uint32 i = 0;
    while(*src){
        if(strstr(src, filter) == src){ //Have we found the same string at the same position?
        
            strcpy(ret + i, replacement);
            
            i += replacementlen - 1;
            src += filterlen;
            
        }else{
            ret[i++] = *src++;
        }
    }
    ret[i] = '\0';
    
    
    return ret;
}




#undef AMOUNT_SAVED_SRC
#undef AMOUNT_PASTED_REPLACEMENT