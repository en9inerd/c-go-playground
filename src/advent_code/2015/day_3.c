// --- Day 3: Perfectly Spherical Houses in a Vacuum ---

// Santa is delivering presents to an infinite two-dimensional grid of houses.

// He begins by delivering a present to the house at his starting location, and
// then an elf at the North Pole calls him via radio and tells him where to move
// next. Moves are always exactly one house to the north (^), south (v), east
// (>), or west (<). After each move, he delivers another present to the house
// at his new location.

// However, the elf back at the north pole has had a little too much eggnog, and
// so his directions are a little off, and Santa ends up visiting some houses
// more than once. How many houses receive at least one present?

// For example:

//     > delivers presents to 2 houses: one at the starting location, and one to
//     the east.
//     ^>v< delivers presents to 4 houses in a square, including twice to the
//     house at his starting/ending location. ^v^v^v^v^v delivers a bunch of
//     presents to some very lucky children at only 2 houses.

// Your puzzle answer was 2565.
// --- Part Two ---

// The next year, to speed up the process, Santa creates a robot version of
// himself, Robo-Santa, to deliver presents with him.

// Santa and Robo-Santa start at the same location (delivering two presents to
// the same starting house), then take turns moving based on instructions from
// the elf, who is eggnoggedly reading from the same script as the previous
// year.

// This year, how many houses receive at least one present?

// For example:

//     ^v delivers presents to 3 houses, because Santa goes north, and then
//     Robo-Santa goes south.
//     ^>v< now delivers presents to 3 houses, and Santa and Robo-Santa end up
//     back where they started. ^v^v^v^v^v now delivers presents to 11 houses,
//     with Santa going one direction and Robo-Santa going the other.

// Your puzzle answer was 2639.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTABLE_SIZE 10000

unsigned int hash(int x, int y) {
  return ((unsigned int)x * 73856093u) ^ ((unsigned int)y * 19349663u);
}

// Structure for storing unique coordinates in the hash table
typedef struct {
  int x;
  int y;
} Coordinate;

// Node structure for handling collisions in hash table
typedef struct Node {
  Coordinate coord;
  struct Node *next;
} Node;

// Hash table structure
typedef struct {
  Node **table;
  size_t size;
} HashTable;

HashTable *create_table(size_t size) {
  HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
  hashTable->table = (Node **)malloc(sizeof(Node *) * size);
  hashTable->size = size;
  for (size_t i = 0; i < size; i++) {
    hashTable->table[i] = NULL;
  }
  return hashTable;
}

int insert(HashTable *hashTable, int x, int y) {
  unsigned int index = hash(x, y) % hashTable->size;
  Node *node = hashTable->table[index];
  while (node) {
    if (node->coord.x == x && node->coord.y == y) {
      return 0;
    }
    node = node->next;
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->coord.x = x;
  newNode->coord.y = y;
  newNode->next = hashTable->table[index];
  hashTable->table[index] = newNode;
  return 1;
}

void free_table(HashTable *hashTable) {
  for (size_t i = 0; i < hashTable->size; i++) {
    Node *node = hashTable->table[i];
    while (node) {
      Node *temp = node;
      node = node->next;
      free(temp);
    }
  }
  free(hashTable->table);
  free(hashTable);
}

int main(int argc, char *argv[]) {
  FILE *file;

  if (argc < 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Error: cannot open file %s\n", argv[1]);
    return 1;
  }

  char directions[HASHTABLE_SIZE];
  fscanf(file, "%s", directions);
  fclose(file);

  HashTable *hashTable = create_table(HASHTABLE_SIZE);

  int santaX1 = 0, santaY1 = 0, santaX2 = 0, santaY2 = 0;

  insert(hashTable, santaX1, santaY1);
  unsigned int uniqueHouses = 1;

  for (size_t i = 0; i < strlen(directions); i++) {
    char direction = directions[i];
    switch (direction) {
    case '^':
      if (i % 2 == 0)
        santaY1++;
      else
        santaY2++;
      break;
    case 'v':
      if (i % 2 == 0)
        santaY1--;
      else
        santaY2--;
      break;
    case '>':
      if (i % 2 == 0)
        santaX1++;
      else
        santaX2++;
      break;
    case '<':
      if (i % 2 == 0)
        santaX1--;
      else
        santaX2--;
      break;
    }
    if (insert(hashTable, santaX1, santaY1) ||
        insert(hashTable, santaX2, santaY2)) {
      uniqueHouses++;
    }
  }

  printf("Unique houses visited: %d\n", uniqueHouses);

  free_table(hashTable);
  return 0;
}
