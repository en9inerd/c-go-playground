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

//   --- Part Two ---

// Now, take the signal you got on wire a, override wire b to that signal, and
// reset the other wires (including wire a). What new signal is ultimately
// provided to wire a?

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 50
#define MAX_WIRES 1000
#define MAX_INSTRUCTIONS 350
#define MAX_NAME_LENGTH 5

typedef enum { ASSIGN, AND, OR, LSHIFT, RSHIFT, NOT } Operation;

typedef struct {
  Operation op;
  char input1[MAX_NAME_LENGTH];
  char input2[MAX_NAME_LENGTH];
  char output[MAX_NAME_LENGTH];
  int shiftValue;
} Instruction;

typedef struct {
  char name[MAX_NAME_LENGTH];
  int value;
  bool resolved;
} Wire;

Instruction instructions[MAX_INSTRUCTIONS];
Wire wires[MAX_WIRES];
int instructionsCount = 0, wiresCount = 0;

int add_wire(const char *name);
void parse_instruction(char *line);
int find_wire(const char *name);
int get_wire_value(const char *name);
void resolve_instruction(Instruction *inst);

int find_wire(const char *name) {
  for (int i = 0; i < wiresCount; i++) {
    if (strcmp(wires[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}

int add_wire(const char *name) {
  if (find_wire(name) == -1) {
    strcpy(wires[wiresCount].name, name);
    wires[wiresCount].resolved = false;
    wires[wiresCount].value = 0;
    return wiresCount++;
  }
  return find_wire(name);
}

void parse_instruction(char *line) {
  Instruction instruction;

  if (strstr(line, "AND") != NULL) {
    instruction.op = AND;
    sscanf(line, "%s AND %s -> %s", instruction.input1, instruction.input2,
           instruction.output);
  } else if (strstr(line, "OR") != NULL) {
    instruction.op = OR;
    sscanf(line, "%s OR %s -> %s", instruction.input1, instruction.input2,
           instruction.output);
  } else if (strstr(line, "LSHIFT") != NULL) {
    instruction.op = LSHIFT;
    sscanf(line, "%s LSHIFT %d -> %s", instruction.input1,
           &instruction.shiftValue, instruction.output);
  } else if (strstr(line, "RSHIFT") != NULL) {
    instruction.op = RSHIFT;
    sscanf(line, "%s RSHIFT %d -> %s", instruction.input1,
           &instruction.shiftValue, instruction.output);
  } else if (strstr(line, "NOT") != NULL) {
    instruction.op = NOT;
    sscanf(line, "NOT %s -> %s", instruction.input1, instruction.output);
  } else {
    instruction.op = ASSIGN;
    sscanf(line, "%s -> %s", instruction.input1, instruction.output);
  }

  add_wire(instruction.output);
  instructions[instructionsCount++] = instruction;
}

int get_wire_value(const char *name) {
  if (isdigit(name[0])) {
    return (int)atoi(name);
  }
  int index = find_wire(name);
  if (index == -1) {
    printf("Error: Wire %s not found.\n", name);
    exit(EXIT_FAILURE);
  }
  if (!wires[index].resolved) {
    for (int i = 0; i < instructionsCount; i++) {
      if (strcmp(instructions[i].output, name) == 0) {
        resolve_instruction(&instructions[i]);
        break;
      }
    }
  }
  return wires[index].value;
}

void resolve_instruction(Instruction *inst) {
  int val1 = 0, val2 = 0;
  if (inst->op != NOT && inst->op != ASSIGN) {
    val1 = get_wire_value(inst->input1);
  }
  if (inst->op == AND || inst->op == OR) {
    val2 = get_wire_value(inst->input2);
  } else if (inst->op == LSHIFT || inst->op == RSHIFT) {
    val2 = (int)inst->shiftValue;
  } else if (inst->op == NOT) {
    val1 = get_wire_value(inst->input1);
  } else if (inst->op == ASSIGN) {
    val1 = get_wire_value(inst->input1);
  }

  int result = 0;
  switch (inst->op) {
  case AND:
    result = val1 & val2;
    break;
  case OR:
    result = val1 | val2;
    break;
  case LSHIFT:
    result = val1 << val2;
    break;
  case RSHIFT:
    result = val1 >> val2;
    break;
  case NOT:
    result = ~val1;
    break;
  case ASSIGN:
    result = val1;
    break;
  default:
    printf("Error: Unknown op.\n");
    exit(EXIT_FAILURE);
  }

  int index = find_wire(inst->output);
  wires[index].value = result;
  wires[index].resolved = true;
}

int main(int argc, char *argv[]) {
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
    line[strcspn(line, "\n")] = '\0';

    parse_instruction(line);
  }
  fclose(file);

  int value = get_wire_value("a");
  printf("The signal ultimately provided to wire a is %d\n", value);

  int index = find_wire("b");
  wires[index].value = value;

  // reset all wires except b
  for (int i = 0; i < wiresCount; i++) {
    wires[i].resolved = false;
  }
  wires[index].resolved = true;

  value = get_wire_value("a");
  printf("The new signal ultimately provided to wire a is %d\n", value);

  return 0;
}
