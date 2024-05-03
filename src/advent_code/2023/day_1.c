// --- Day 1: Trebuchet?! ---

// Something is wrong with global snow production, and you've been selected to
// take a look. The Elves have even given you a map; on it, they've used stars
// to mark the top fifty locations that are likely to be having problems.

// You've been doing this long enough to know that to restore snow operations,
// you need to check all fifty stars by December 25th.

// Collect stars by solving puzzles. Two puzzles will be made available on each
// day in the Advent calendar; the second puzzle is unlocked when you complete
// the first. Each puzzle grants one star. Good luck!

// You try to ask why they can't just use a weather machine ("not powerful
// enough") and where they're even sending you ("the sky") and why your map
// looks mostly blank ("you sure ask a lot of questions") and hang on did you
// just say the sky ("of course, where do you think snow comes from") when you
// realize that the Elves are already loading you into a trebuchet ("please hold
// still, we need to strap you in").

// As they're making the final adjustments, they discover that their calibration
// document (your puzzle input) has been amended by a very young Elf who was
// apparently just excited to show off her art skills. Consequently, the Elves
// are having trouble reading the values on the document.

// The newly-improved calibration document consists of lines of text; each line
// originally contained a specific calibration value that the Elves now need to
// recover. On each line, the calibration value can be found by combining the
// first digit and the last digit (in that order) to form a single two-digit
// number.

// For example:

// 1abc2
// pqr3stu8vwx
// a1b2c3d4e5f
// treb7uchet

// In this example, the calibration values of these four lines are 12, 38, 15,
// and 77. Adding these together produces 142.

// Consider your entire calibration document. What is the sum of all of the
// calibration values?

// Your puzzle answer was 54953.
// --- Part Two ---

// Your calculation isn't quite right. It looks like some of the digits are
// actually spelled out with letters: one, two, three, four, five, six, seven,
// eight, and nine also count as valid "digits".

// Equipped with this new information, you now need to find the real first and
// last digit on each line. For example:

// two1nine
// eightwothree
// abcone2threexyz
// xtwone3four
// 4nineeightseven2
// zoneight234
// 7pqrstsixteen

// In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76.
// Adding these together produces 281.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]) {
  FILE *file;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *wordDigit = NULL;
  int sum = 0;

  if (argc < 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Error: cannot open file %s\n", argv[1]);
    return 1;
  }

  while ((read = getline(&line, &len, file)) != -1) {
    int first_digit = -1;
    int last_digit = -1;
    int i = 0;
    int two_digit_number = 0;

    while (i < read) {
      if (line[i] >= '0' && line[i] <= '9') {
        if (wordDigit != NULL) {
          free(wordDigit);
          wordDigit = NULL;
        }

        if (first_digit == -1) {
          first_digit = line[i] - '0';
        }
        last_digit = line[i] - '0';
      } else if (line[i] == '\n') {
        if (wordDigit != NULL) {
          free(wordDigit);
          wordDigit = NULL;
        }
        break;
      } else {
        if (wordDigit == NULL) {
          wordDigit = malloc(sizeof(char) * MAX_LINE_LENGTH);
        }
        strncat(wordDigit, &line[i], 1);

        if (wordDigit != NULL && strlen(wordDigit) >= 3) {
          char *numbers[] = {"one", "two",   "three", "four", "five",
                             "six", "seven", "eight", "nine"};
          int digit = -1;

          for (int j = 0; j < 9; j++) {
            int pos = strlen(wordDigit) - strlen(numbers[j]);
            if (pos >= 0 && strcmp(&wordDigit[pos], numbers[j]) == 0) {
              digit = j + 1;
              break;
            }
          }

          if (digit != -1) {
            if (first_digit == -1) {
              first_digit = digit;
            }
            last_digit = digit;
          }
        }
      }
      i++;
    }

    if (first_digit != -1 && last_digit != -1) {
      two_digit_number = first_digit * 10 + last_digit;
      sum += two_digit_number;
      printf("%d, ", two_digit_number);
    }
  }

  printf("\nSum of all two-digit numbers is %d\n", sum);

  fclose(file);
  if (line) {
    free(line);
  }

  return 0;
}
