#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

/**
 * Maintain a constant pool (an array of constant values)
 * 
 * Instructions to load a constant look up the value by index in the array
*/
typedef struct {
  int capacity;
  int count;
  Value* values;
} ValueArray;

/**
 * Declare functions for initializing a new Value,
 * writing value(s) to the ValueArray, and freeing up
 * a Value Array that is no longer needed.
*/
void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif