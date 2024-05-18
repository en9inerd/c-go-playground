// --- Day 4: The Ideal Stocking Stuffer ---

// Santa needs help mining some AdventCoins (very similar to bitcoins) to use as
// gifts for all the economically forward-thinking little girls and boys.

// To do this, he needs to find MD5 hashes which, in hexadecimal, start with at
// least five zeroes. The input to the MD5 hash is some secret key (your puzzle
// input, given below) followed by a number in decimal. To mine AdventCoins, you
// must find Santa the lowest positive number (no leading zeroes: 1, 2, 3, ...)
// that produces such a hash.

// For example:

//     If your secret key is abcdef, the answer is 609043, because the MD5 hash
//     of abcdef609043 starts with five zeroes (000001dbbfa...), and it is the
//     lowest such number to do so. If your secret key is pqrstuv, the lowest
//     number it combines with to make an MD5 hash starting with five zeroes is
//     1048970; that is, the MD5 hash of pqrstuv1048970 looks like
//     000006136ef....

// Your puzzle answer was 117946.
// --- Part Two ---

// Now find one that starts with six zeroes.

// Your puzzle answer was 3938038.

#include <CommonCrypto/CommonDigest.h> // it only works with macOS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ZEROES 6
#define MD5_DIGEST_LENGTH 16

int starts_with_zeroes(const unsigned char *md5) {
  for (int i = 0; i < NUM_ZEROES / 2; ++i) {
    if (md5[i] != 0) {
      return 0;
    }
  }
  if (NUM_ZEROES % 2 != 0 && (md5[NUM_ZEROES / 2] & 0xF0) != 0) {
    return 0;
  }
  return 1;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <secret_key>\n", argv[0]);
    return 1;
  }

  const char *secret_key = argv[1];
  int result;
  char input[100];
  unsigned char md5[MD5_DIGEST_LENGTH];

  for (int i = 1;; ++i) {
    sprintf(input, "%s%d", secret_key, i);
    CC_MD5(input, (CC_LONG)strlen(input), md5);
    if (starts_with_zeroes(md5)) {
      result = i;
      break;
    }
  }
  printf("Lowest positive number: %d\n", result);

  return 0;
}

#pragma clang diagnostic pop
