#include <typedefs.h>
#include <stdlib.h>

typedef struct{
    uint64 buffer_health;
    uint64 total_data;

    void * dat;
    uint16 type_size;
    void (*child_deconstruct)(void *);
}vector;

//Initalize a vector
void vector_init(vector * vec, uint16 type_size, void (*child_deconstruct)(void *));

/*Allocate a new vector and return the pointer to the new vector
  Set Child decon to NULL for int, char, float, etc*/
vector * vector_create(uint16 type_size,  void (*child_deconstruct)(void *));

//Push a block of data to the end of the vector
void vector_push_back(vector * vec, void * data);

//Get the value stored at the index in the vector
void * vector_index(vector * vec, uint64 index);

//Get the size of the vector
uint64 vector_size(vector * vec);

//Cleans up self and children
void vector_deconstruct(vector * vec);