#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  // Grow capacity if needed
  if (chunk->capacity < chunk->count + 1) {   // Another way of saying chunk->capacity == chunk->count + 1?
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, 
        oldCapacity, chunk->capacity);
    chunk->lines = GROW_ARRAY(int, chunk->lines, 
        oldCapacity, chunk->capacity);
  }

  // Write new instruction to Chunk
  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  ++(chunk->count);
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;  // Return index of value in chunk->constants
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);   // Avoid dangling pointer
}