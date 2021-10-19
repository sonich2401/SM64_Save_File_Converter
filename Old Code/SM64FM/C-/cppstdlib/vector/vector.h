#include <stdlib.h>

typedef struct{
    unsigned long int buffer_health;
    unsigned long int total_data;

    void * dat;
    unsigned short type_size;
    void (*child_deconstruct)(void *);
}vector;

//Initalize a vector
void vector_init(vector * vec, unsigned short type_size, void (*child_deconstruct)(void *));

/*Allocate a new vector and return the pointer to the new vector
  Set Child decon to NULL for int, char, float, etc*/
vector * vector_create(unsigned short type_size,  void (*child_deconstruct)(void *));

//Push a block of data to the end of the vector
void vector_push_back(vector * vec, void * data);

//Get the value stored at the index in the vector
void * vector_index(vector * vec, unsigned long int index);

//Get the size of the vector
unsigned long int vector_size(vector * vec);

//Cleans up self and children
void vector_deconstruct(vector * vec);
