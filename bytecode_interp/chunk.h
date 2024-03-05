#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

/**
 * Here is where we will define the bytecode instruction set
*/
typedef enum {
  OP_CONSTANT,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NEGATE,
  OP_RETURN,
} OpCode;

/**
 * This data structure points to a 'chunk' of bytecode instructions.
 * For now, let's define a 'chunk' as 0 or more bytecode instructions.
 * This data structure also maintains the count (# of instructions in chunk),
 * and the capacity (total # of instructions that can currently fit in dynamic
 * array).
*/
typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  int* lines;
  ValueArray constants;
} Chunk;

/**
 * Declare functions for initializing a new Chunk,
 * writing to a Chunk, and freeing up
 * a Chunk that is no longer needed.
*/
void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);
void freeChunk(Chunk* chunk);

#endif