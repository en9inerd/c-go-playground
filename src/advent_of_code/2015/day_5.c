// --- Day 5: Doesn't He Have Intern-Elves For This? ---

// Santa needs help figuring out which strings in his text file are naughty or
// nice.

// A nice string is one with all of the following properties:

//     It contains at least three vowels (aeiou only), like aei, xazegov, or
//     aeiouaeiouaeiou. It contains at least one letter that appears twice in a
//     row, like xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd). It does not
//     contain the strings ab, cd, pq, or xy, even if they are part of one of
//     the other requirements.

// For example:

//     ugknbfddgicrmopn is nice because it has at least three vowels
//     (u...i...o...), a double letter (...dd...), and none of the disallowed
//     substrings. aaa is nice because it has at least three vowels and a double
//     letter, even though the letters used by different rules overlap.
//     jchzalrnumimnmhp is naughty because it has no double letter.
//     haegwjzuvuyypxyu is naughty because it contains the string xy.
//     dvszwmarrgswjxmb is naughty because it contains only one vowel.

// How many strings are nice?

// Your puzzle answer was 258.
// --- Part Two ---

// Realizing the error of his ways, Santa has switched to a better model of
// determining whether a string is naughty or nice. None of the old rules apply,
// as they are all clearly ridiculous.

// Now, a nice string is one with all of the following properties:

//     It contains a pair of any two letters that appears at least twice in the
//     string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not
//     like aaa (aa, but it overlaps). It contains at least one letter which
//     repeats with exactly one letter between them, like xyx, abcdefeghi (efe),
//     or even aaa.

// For example:

//     qjhvhtzxzqqjkmpb is nice because is has a pair that appears twice (qj)
//     and a letter that repeats with exactly one letter between them (zxz).
//     xxyxx is nice because it has a pair that appears twice and a letter that
//     repeats with one between, even though the letters used by each rule
//     overlap. uurcxstgmygtbstg is naughty because it has a pair (tg) but no
//     repeat with a single letter between them. ieodomkazucvgmuy is naughty
//     because it has a repeating letter with one between (odo), but no pair
//     that appears twice.

// How many strings are nice under these new rules?

// Your puzzle answer was 53.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 20

bool has_repeated_pair(const char *str) {
  size_t len = strlen(str);
  for (size_t i = 0; i < len - 1; i++) {
    for (size_t j = i + 2; j < len - 1; j++) {
      if (str[i] == str[j] && str[i + 1] == str[j + 1]) {
        return true;
      }
    }
  }
  return false;
}

bool has_repeating_letter_with_one_between(const char *str) {
  size_t len = strlen(str);
  for (size_t i = 0; i < len - 2; i++) {
    if (str[i] == str[i + 2]) {
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  FILE *file;
  char line[MAX_LINE_LENGTH];
  // const char *disallowed[] = {"ab", "cd", "pq", "xy"};
  // const char *vowels = "aeiou";
  unsigned int niceStrs = 0;

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
    // int vowelsCount = 0;
    // bool doubleCh = false, dis = false;

    // for (size_t i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
    //   if (line[i] == line[i + 1])
    //     doubleCh = true;

    //   if (strchr(vowels, line[i])) {
    //     vowelsCount++;
    //   }

    //   char tmp[] = {line[i], line[i + 1], '\0'};
    //   for (size_t j = 0; j < sizeof(disallowed) / sizeof(disallowed[0]); j++)
    //   {
    //     if (strcmp(tmp, disallowed[j]) == 0) {
    //       dis = true;
    //       break;
    //     }
    //   }
    // }

    // if (!dis && doubleCh && vowelsCount >= 3) {
    //   niceStrs++;
    // }

    line[strcspn(line, "\n")] = 0;

    if (has_repeated_pair(line) &&
        has_repeating_letter_with_one_between(line)) {
      niceStrs++;
    }
  }
  printf("Strings are nice: %d\n", niceStrs);

  fclose(file);
  return 0;
}
