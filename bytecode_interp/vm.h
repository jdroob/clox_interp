#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

/**
 * Recall that a real compiler translates source code to real, honest-to-goodness
 * machine code (e.g. x86, ARM, RISC-V, MIPS, etc.)
 * 
 * As we've discussed, a bytecode interpreter translates source code to fake,
 * dishonest, "virtual" machine code (i.e. there is no real machine that runs this code!)
 * 
 * But like a real machine, we're going to hand our virtual machine (VM) some
 * (virtual) machine code and it is going to run it! :)
*/

typedef struct {
  Chunk* chunk;
  uint8_t* ip;    // instruction pointer: points to the instruction about to be exec'd
  Value stack[STACK_MAX];
  Value* stackTop;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);    // TODO: Compare this logic to that in execute.c
void push(Value value);
Value pop();

#endif