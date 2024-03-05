#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
  printf("== %s ==\n", name);

  for (int offset = 0; offset < chunk->count;) {
    // disassembleInstruction returns the offset
    // allowing us to find the location of the next
    // instruction in chunk. 
    // The reason for this is that later on, we'll 
    // have instructions that are greater than 1 byte long.
    offset = disassembleInstruction(chunk, offset);
  }
}

static int simpleInstruction(const char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
  uint8_t constantIndex = chunk->code[offset + 1];   
  printf("%-16s %4d '", name, constantIndex);
  printValue(chunk->constants.values[constantIndex]);
  printf("'\n");
  return offset + 2;  // Next instruction is 2 bytes from OP_CONSTANT instruction
}

int disassembleInstruction(Chunk* chunk, int offset) {
  // Print offset telling user where in chunk current instruction is
  printf("%04d ", offset);
  if (offset > 0 &&
      chunk->lines[offset] == chunk->lines[offset - 1]) {
    printf("   | ");    // This bytecode instruction is on the same line as the previous instruction
  } else {
    printf("%4d ", chunk->lines[offset]);
  }
  // Read instruction at offset
  uint8_t instruction = chunk->code[offset];
  // Call utility function for displaying the instruction based on OpCode read
  switch(instruction) {
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    case OP_ADD:
      return simpleInstruction("OP_ADD", offset);
    case OP_SUBTRACT:
      return simpleInstruction("OP_SUBTRACT", offset);
    case OP_MULTIPLY:
      return simpleInstruction("OP_MULTIPLY", offset);
    case OP_DIVIDE:
      return simpleInstruction("OP_DIVIDE", offset);
    case OP_NEGATE:
      return simpleInstruction("OP_NEGATE", offset);
    case OP_CONSTANT:
      return constantInstruction("OP_CONSANT", chunk, offset);
    default:
      printf("Unknown opcode%d\n", instruction);
      return offset + 1;
  }
}