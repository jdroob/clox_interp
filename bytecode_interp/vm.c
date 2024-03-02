#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

static void resetStack() {
  vm.stackTop = vm.stack;   // point stackTop to first entry in stack (indicating empty)
}

void initVM() {
  resetStack();
}

void freeVM() {
  while (vm.stackTop != vm.stack) pop();
}

void push(Value value) {
  *vm.stackTop = value;
  ++(vm.stackTop);
}

Value pop() {
  --(vm.stackTop);
  return *vm.stackTop;
}

static InterpretResult run() {
  #define READ_BYTE() (*vm.ip++)    // READ_BYTE() reads the instruction currently pointed to by ip, then advances ip
  #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()]) // Note that after READ_BYTE() is called in the for loop, if the next instruction to be exec'd is OP_CONSTANT, READ_BYTE() bumps ip to point to the constant. In READ_CONSTANT(), READ_BYTE() is called a second time which returns the index of the constant value and bumps ip to the next instruction

  for (;;) {
  #ifndef DEBUG_TRACE_EXECUTION     // print instruction
    printf("        ");
    printf("CURRENT STACK STATE BITCH");
    printf("        ");
    for (Value* slot = vm.stack; slot < vm.stackTop; ++slot) {    // Loop through the stack (starting from the bottom) and print the values
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));  // vm.ip is a pointer, vm.chunk->code is a pointer
  #endif
    uint8_t instruction;
    switch(instruction = READ_BYTE()) {
      case OP_CONSTANT: {
        Value constant = READ_CONSTANT();
        push(constant);
        break;
      }
      case OP_RETURN: {
        printValue(pop());
        printf("\n");
        return INTERPRET_OK;
      }
    }
  }

  #undef READ_BYTE
  #undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;       // "Load" the chunk to be exec'd into the VM
  vm.ip = vm.chunk->code; // Set the instruction pointer to the top of the code chunk
  return run();           // run the bytecode instructions
}
