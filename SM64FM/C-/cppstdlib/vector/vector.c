#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void vector_init(vector * vec, uint16 type_size, void (*child_deconstruct)(void *)){
    vec->type_size = type_size;
    vec->total_data = 0;
    vec->child_deconstruct = child_deconstruct;

    vec->buffer_health = 30;
    vec->dat = malloc(vec->buffer_health * vec->type_size); //Reserve 30 slots for the vector
}


//Allocate a new vector and return the pointer to the new vector
vector * vector_create(uint16 type_size, void (*child_deconstruct)(void *)){
    vector * ret = malloc(sizeof(vector));

    ret->type_size = type_size;
    ret->total_data = 0;
    ret->child_deconstruct = child_deconstruct;

    ret->buffer_health = 30;
    ret->dat = malloc(ret->buffer_health * ret->type_size); //Reserve 30 slots for the vector
    

    return ret;
}


//Checks if the buffer needs to be expanded
void vector_add_check(vector * vec){
    if(vec->buffer_health <= vec->total_data+1){
        printf("BANANA2\n");
        vec->buffer_health += 20;
        vec->dat = realloc(vec->dat,  vec->buffer_health * vec->type_size);
    }
}

//Push a block of data to the end of the vector
void vector_push_back(vector * vec, void * data){
   vector_add_check(vec); //Make sure we have enough memory

   for(uint16 i = 0; i < vec->type_size; i++){
    ((char*)vec->dat)[vec->total_data * vec->type_size + i] = *(char *)(data + i);
   }
   vec->total_data++;
}

//Get the size of the vector
uint64 vector_size(vector * vec){
    return vec->total_data;
}

//Get the value stored at the index in the vector
void * vector_index(vector * vec, uint64 index){
    return vec->dat + (index * vec->type_size);
}

//Cleans up self and children
void vector_deconstruct(vector * vec){
    for(uint64 i = 0; i < vec->total_data; i++){
        if(vec->child_deconstruct == NULL){ //used for int, char, float, etc.
            free(vec->dat);
        }else{ //Structs
            void * tmp;
            memcpy(tmp, vec->dat + (i * vec->type_size), vec->type_size);
            vec->child_deconstruct(tmp);
        }
    }
    free(vec->dat);
    //free(vec);
}