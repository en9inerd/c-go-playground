// --- Day 7: Some Assembly Required ---

// This year, Santa brought little Bobby Tables a set of wires and bitwise logic
// gates! Unfortunately, little Bobby is a little under the recommended age
// range, and he needs help assembling the circuit.

// Each wire has an identifier (some lowercase letters) and can carry a 16-bit
// signal (a number from 0 to 65535). A signal is provided to each wire by a
// gate, another wire, or some specific value. Each wire can only get a signal
// from one source, but can provide its signal to multiple destinations. A gate
// provides no signal until all of its inputs have a signal.

// The included instructions booklet describes how to connect the parts
// together: x AND y -> z means to connect wires x and y to an AND gate, and
// then connect its output to wire z.

// For example:

//     123 -> x means that the signal 123 is provided to wire x.
//     x AND y -> z means that the bitwise AND of wire x and wire y is provided
//     to wire z. p LSHIFT 2 -> q means that the value from wire p is
//     left-shifted by 2 and then provided to wire q. NOT e -> f means that the
//     bitwise complement of the value from wire e is provided to wire f.

// Other possible gates include OR (bitwise OR) and RSHIFT (right-shift). If,
// for some reason, you'd like to emulate the circuit instead, almost all
// programming languages (for example, C, JavaScript, or Python) provide
// operators for these gates.

// For example, here is a simple circuit:

// 123 -> x
// 456 -> y
// x AND y -> d
// x OR y -> e
// x LSHIFT 2 -> f
// y RSHIFT 2 -> g
// NOT x -> h
// NOT y -> i

// After it is run, these are the signals on the wires:

// d: 72
// e: 507
// f: 492
// g: 114
// h: 65412
// i: 65079
// x: 123
// y: 456

// In little Bobby's kit's instructions booklet (provided as your puzzle input),
// what signal is ultimately provided to wire a?

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 50
#define MAX_WIRES 1000
#define MAX_INSTRUCTIONS 350

typedef enum { ASSIGN, AND, OR, LSHIFT, RSHIFT, NOT } Operation;

typedef struct {
  Operation operation;
  char *input1;
  char *input2;
  char *output;
  bool isCalculated;
} Instruction;

typedef struct {
  char *name;
  uint16_t value;
} Wire;

void parse_instruction(char *line, Instruction *instruction) {
  char *token;
  char *operation;
  char *input1;
  char *input2;
  char *output;

  token = strtok(line, " ");
  if (strcmp(token, "NOT") == 0) {
    operation = token;
    input1 = strtok(NULL, " ");
    output = strtok(NULL, " ");
  } else {
    input1 = token;
    operation = strtok(NULL, " ");
    if (strcmp(operation, "->") == 0) {
      output = strtok(NULL, " ");
    } else {
      input2 = strtok(NULL, " ");
      output = strtok(NULL, " ");
    }
  }

  instruction->input1 = input1;
  instruction->input2 = input2;
  instruction->output = output;
  instruction->isCalculated = false;

  if (strcmp(operation, "AND") == 0) {
    instruction->operation = AND;
  } else if (strcmp(operation, "OR") == 0) {
    instruction->operation = OR;
  } else if (strcmp(operation, "LSHIFT") == 0) {
    instruction->operation = LSHIFT;
  } else if (strcmp(operation, "RSHIFT") == 0) {
    instruction->operation = RSHIFT;
  } else if (strcmp(operation, "NOT") == 0) {
    instruction->operation = NOT;
  } else {
    instruction->operation = ASSIGN;
  }
}

uint16_t get_wire_value(char *name, Wire *wires, uint16_t wiresCount) {
  for (uint16_t i = 0; i < wiresCount; i++) {
    if (strcmp(wires[i].name, name) == 0) {
      return wires[i].value;
    }
  }
  return 0;
}

// recursive function to calculate the value of a wire
void calculate_wire_value(Instruction *instructions, Wire *wires,
                          uint16_t instructionsCount, uint16_t wiresCount) {}

int main(int argc, char *argv[]) {
  Instruction instructions[MAX_INSTRUCTIONS];
  Wire wires[MAX_WIRES];
  uint16_t instructionsCount = 0, wiresCount = 0;

  FILE *file;
  char line[MAX_LINE_LENGTH];

  if (argc < 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Error: cannot open file %s\n", argv[1]);
    return 1;
  }

  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    Instruction instruction;
    parse_instruction(line, &instruction);
    instructions[instructionsCount++] = instruction;
  }

  fclose(file);
  return 0;
}
